//
// Copyright 2017 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <memory>
#include <optional>

#include "gtest/gtest.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {
// Tests transparent retries when the call was never sent out on the wire.
// This is similar to retry_transparent_not_sent_on_wire, except that
// instead of simulating the response with a filter, we actually have
// the transport behave the right way.  We create a server with
// MAX_CONCURRENT_STREAMS set to 1.  We start a call on the server, and
// then start a second call, which will get queued in the transport.
// Then, before the first call finishes, the server is shut down and
// restarted.  The second call will fail in that transport instance and
// will be transparently retried after the server starts up again.
CORE_END2END_TEST(RetryHttp2Tests, RetryTransparentMaxConcurrentStreams) {
  const auto server_args =
      DefaultServerArgs()
          .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS, 1)
          .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS_OVERLOAD_PROTECTION, false);
  InitServer(server_args);
  InitClient(ChannelArgs());
  auto c =
      NewClientCall("/service/method").Timeout(Duration::Minutes(1)).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  IncomingMessage server_message;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendMessage("foo")
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvMessage(server_message)
      .RecvStatusOnClient(server_status);
  // Server should get a call.
  auto s = RequestCall(101);
  Expect(101, true);
  Step();
  EXPECT_EQ(s.method(), "/service/method");
  // Client starts a second call.
  // We set wait_for_ready for this call, so that if it retries before
  // the server comes back up, it stays pending.
  auto c2 =
      NewClientCall("/service/method").Timeout(Duration::Minutes(1)).Create();
  IncomingStatusOnClient server_status2;
  IncomingMetadata server_initial_metadata2;
  IncomingMessage server_message2;
  c2.NewBatch(2)
      .SendInitialMetadata({}, GRPC_INITIAL_METADATA_WAIT_FOR_READY)
      .SendMessage("bar")
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata2)
      .RecvMessage(server_message2)
      .RecvStatusOnClient(server_status2);
  // Start server shutdown.
  ShutdownServerAndNotify(102);
  // Server handles the first call.
  IncomingMessage client_message;
  s.NewBatch(103).RecvMessage(client_message);
  Expect(103, true);
  Step();
  IncomingCloseOnServer client_close;
  s.NewBatch(104)
      .RecvCloseOnServer(client_close)
      .SendInitialMetadata({})
      .SendMessage("baz")
      .SendStatusFromServer(GRPC_STATUS_OK, "xyz", {});
  // Server completes first call and shutdown.
  // Client completes first call.
  Expect(104, true);
  Expect(102, true);
  Expect(1, true);
  Step();
  // Clean up from first call.
  EXPECT_EQ(client_message.payload(), "foo");
  EXPECT_FALSE(client_close.was_cancelled());
  EXPECT_EQ(server_message.payload(), "baz");
  EXPECT_EQ(server_status.status(), GRPC_STATUS_OK);
  EXPECT_EQ(server_status.message(), IsErrorFlattenEnabled() ? "" : "xyz");
  // Destroy server and then restart it.
  // TODO(hork): hack to solve PosixEventEngine Listener's async shutdown issue.
  absl::SleepFor(absl::Milliseconds(250));
  InitServer(server_args);
  // Server should get the second call.
  auto s2 = RequestCall(201);
  Expect(201, true);
  // Give enough time for the handshake to timeout, and a new handshake to start
  // if needed. (b/333896115)
  // TODO(yashykt): Remove the extra duration on fixing b/362326480.
  Step(Duration::Seconds(30));
  EXPECT_EQ(s2.method(), "/service/method");
  // Make sure the "grpc-previous-rpc-attempts" header was NOT sent, since
  // we don't do that for transparent retries.
  EXPECT_EQ(s2.GetInitialMetadata("grpc-previous-rpc-attempts"), std::nullopt);
  // Server handles the second call.
  IncomingMessage client_message2;
  IncomingCloseOnServer client_close2;
  s2.NewBatch(202).RecvMessage(client_message2);
  Expect(202, true);
  Step();
  s2.NewBatch(203)
      .RecvCloseOnServer(client_close2)
      .SendInitialMetadata({})
      .SendMessage("qux")
      .SendStatusFromServer(GRPC_STATUS_OK, "xyz", {});
  // Second call completes.
  Expect(203, true);
  Expect(2, true);
  Step();
  // Clean up from second call.
  EXPECT_EQ(client_message2.payload(), "bar");
  EXPECT_FALSE(client_close.was_cancelled());
  EXPECT_EQ(server_message2.payload(), "qux");
  EXPECT_EQ(server_status2.status(), GRPC_STATUS_OK);
  EXPECT_EQ(server_status2.message(), IsErrorFlattenEnabled() ? "" : "xyz");
}
}  // namespace
}  // namespace grpc_core
