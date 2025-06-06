// Copyright 2024 gRPC authors.
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

#include "src/core/ext/transport/chaotic_good/control_endpoint.h"

#include <grpc/grpc.h>

#include "src/core/ext/transport/chaotic_good/tcp_frame_header.h"
#include "test/core/call/yodel/yodel_test.h"
#include "test/core/transport/util/mock_promise_endpoint.h"

namespace grpc_core {

class ControlEndpointTest : public YodelTest {
 protected:
  using YodelTest::YodelTest;
};

#define CONTROL_ENDPOINT_TEST(name) YODEL_TEST(ControlEndpointTest, name)

namespace {
grpc_event_engine::experimental::Slice TcpFrameHeader(
    chaotic_good::FrameType type, uint32_t stream_id, uint32_t payload_length,
    uint64_t payload_tag) {
  std::vector<uint8_t> buffer(chaotic_good::TcpFrameHeader::kFrameHeaderSize);
  chaotic_good::TcpFrameHeader{{type, stream_id, payload_length}, payload_tag}
      .Serialize(buffer.data());
  return grpc_event_engine::experimental::Slice::FromCopiedBuffer(
      buffer.data(), buffer.size());
}

}  // namespace

CONTROL_ENDPOINT_TEST(CanWrite) {
  util::testing::MockPromiseEndpoint ep(1234);
  chaotic_good::ControlEndpoint control_endpoint(
      std::move(ep.promise_endpoint),
      MakeRefCounted<chaotic_good::TransportContext>(event_engine(), nullptr),
      std::make_shared<chaotic_good::TcpZTraceCollector>());
  ep.ExpectWrite(
      {grpc_event_engine::experimental::Slice::FromCopiedString("hello")},
      nullptr);
  SpawnTestSeqWithoutContext(
      "write",
      control_endpoint.Write(SliceBuffer(Slice::FromCopiedString("hello"))));
  WaitForAllPendingWork();
}

CONTROL_ENDPOINT_TEST(CanWriteSecurityFrame) {
  util::testing::MockPromiseEndpoint ep(1234);
  chaotic_good::ControlEndpoint control_endpoint(
      std::move(ep.promise_endpoint),
      MakeRefCounted<chaotic_good::TransportContext>(event_engine(), nullptr),
      std::make_shared<chaotic_good::TcpZTraceCollector>());
  ep.ExpectWrite({TcpFrameHeader(chaotic_good::FrameType::kTcpSecurityFrame, 0,
                                 strlen("security_frame_bytes"), 0),
                  grpc_event_engine::experimental::Slice::FromCopiedString(
                      "security_frame_bytes")},
                 nullptr);
  SliceBuffer security_frame_bytes(
      Slice::FromCopiedString("security_frame_bytes"));
  control_endpoint.SecureFrameWriterCallback()(&security_frame_bytes);
  WaitForAllPendingWork();
}

}  // namespace grpc_core
