# Copyright 2023 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Auto generated by tools/codegen/core/gen_experiments.py

"""Dictionary of tags to experiments so we know when to test different experiments."""

EXPERIMENT_ENABLES = {
    "backoff_cap_initial_at_max": "backoff_cap_initial_at_max",
    "call_tracer_in_transport": "call_tracer_in_transport",
    "chaotic_good_legacy_protocol": "chaotic_good_legacy_protocol",
    "disable_buffer_hint_on_high_memory_pressure": "disable_buffer_hint_on_high_memory_pressure",
    "event_engine_application_callbacks": "event_engine_application_callbacks",
    "event_engine_callback_cq": "event_engine_application_callbacks,event_engine_callback_cq",
    "event_engine_client": "event_engine_client",
    "event_engine_dns": "event_engine_dns",
    "event_engine_dns_non_client_channel": "event_engine_dns_non_client_channel",
    "event_engine_listener": "event_engine_listener",
    "free_large_allocator": "free_large_allocator",
    "local_connector_secure": "local_connector_secure",
    "max_pings_wo_data_throttle": "max_pings_wo_data_throttle",
    "monitoring_experiment": "monitoring_experiment",
    "multiping": "multiping",
    "pick_first_new": "pick_first_new",
    "posix_ee_skip_grpc_init": "posix_ee_skip_grpc_init",
    "prioritize_finished_requests": "prioritize_finished_requests",
    "promise_based_http2_client_transport": "promise_based_http2_client_transport",
    "promise_based_http2_server_transport": "promise_based_http2_server_transport",
    "promise_based_inproc_transport": "promise_based_inproc_transport",
    "retry_in_callv3": "retry_in_callv3",
    "rq_fast_reject": "rq_fast_reject",
    "schedule_cancellation_over_write": "schedule_cancellation_over_write",
    "tcp_frame_size_tuning": "tcp_frame_size_tuning",
    "tcp_rcv_lowat": "tcp_rcv_lowat",
    "time_caching_in_party": "time_caching_in_party",
    "trace_record_callops": "trace_record_callops",
    "unconstrained_max_quota_buffer_size": "unconstrained_max_quota_buffer_size",
    "work_serializer_dispatch": "work_serializer_dispatch",
}

EXPERIMENT_POLLERS = [
    "event_engine_client",
    "event_engine_dns",
    "event_engine_dns_non_client_channel",
    "event_engine_listener",
]

EXPERIMENTS = {
    "windows": {
        "dbg": {
        },
        "off": {
            "core_end2end_test": [
                "chaotic_good_legacy_protocol",
                "event_engine_dns_non_client_channel",
                "local_connector_secure",
                "posix_ee_skip_grpc_init",
                "retry_in_callv3",
            ],
            "cpp_end2end_test": [
                "posix_ee_skip_grpc_init",
            ],
            "endpoint_test": [
                "tcp_frame_size_tuning",
                "tcp_rcv_lowat",
            ],
            "flow_control_test": [
                "multiping",
                "tcp_frame_size_tuning",
                "tcp_rcv_lowat",
            ],
            "resource_quota_test": [
                "free_large_allocator",
                "unconstrained_max_quota_buffer_size",
            ],
        },
        "on": {
            "cancel_ares_query_test": [
                "event_engine_dns",
            ],
            "core_end2end_test": [
                "event_engine_client",
                "event_engine_listener",
                "work_serializer_dispatch",
            ],
            "cpp_end2end_test": [
                "work_serializer_dispatch",
            ],
            "cpp_lb_end2end_test": [
                "pick_first_new",
            ],
            "event_engine_client_test": [
                "event_engine_client",
            ],
            "event_engine_listener_test": [
                "event_engine_listener",
            ],
            "lb_unit_test": [
                "pick_first_new",
                "work_serializer_dispatch",
            ],
            "resolver_component_tests_runner_invoker": [
                "event_engine_dns",
            ],
            "xds_end2end_test": [
                "pick_first_new",
                "work_serializer_dispatch",
            ],
        },
    },
    "ios": {
        "dbg": {
        },
        "off": {
            "core_end2end_test": [
                "chaotic_good_legacy_protocol",
                "event_engine_dns_non_client_channel",
                "local_connector_secure",
                "posix_ee_skip_grpc_init",
                "retry_in_callv3",
            ],
            "cpp_end2end_test": [
                "posix_ee_skip_grpc_init",
            ],
            "endpoint_test": [
                "tcp_frame_size_tuning",
                "tcp_rcv_lowat",
            ],
            "flow_control_test": [
                "multiping",
                "tcp_frame_size_tuning",
                "tcp_rcv_lowat",
            ],
            "resource_quota_test": [
                "free_large_allocator",
                "unconstrained_max_quota_buffer_size",
            ],
        },
        "on": {
            "core_end2end_test": [
                "work_serializer_dispatch",
            ],
            "cpp_end2end_test": [
                "work_serializer_dispatch",
            ],
            "cpp_lb_end2end_test": [
                "pick_first_new",
            ],
            "lb_unit_test": [
                "pick_first_new",
                "work_serializer_dispatch",
            ],
            "xds_end2end_test": [
                "pick_first_new",
                "work_serializer_dispatch",
            ],
        },
    },
    "posix": {
        "dbg": {
        },
        "off": {
            "core_end2end_test": [
                "chaotic_good_legacy_protocol",
                "event_engine_dns_non_client_channel",
                "local_connector_secure",
                "posix_ee_skip_grpc_init",
                "retry_in_callv3",
            ],
            "cpp_end2end_test": [
                "posix_ee_skip_grpc_init",
            ],
            "endpoint_test": [
                "tcp_frame_size_tuning",
                "tcp_rcv_lowat",
            ],
            "flow_control_test": [
                "multiping",
                "tcp_frame_size_tuning",
                "tcp_rcv_lowat",
            ],
            "resource_quota_test": [
                "free_large_allocator",
                "unconstrained_max_quota_buffer_size",
            ],
        },
        "on": {
            "cancel_ares_query_test": [
                "event_engine_dns",
            ],
            "core_end2end_test": [
                "event_engine_client",
                "event_engine_listener",
                "work_serializer_dispatch",
            ],
            "cpp_end2end_test": [
                "work_serializer_dispatch",
            ],
            "cpp_lb_end2end_test": [
                "pick_first_new",
            ],
            "event_engine_client_test": [
                "event_engine_client",
            ],
            "event_engine_listener_test": [
                "event_engine_listener",
            ],
            "lb_unit_test": [
                "pick_first_new",
                "work_serializer_dispatch",
            ],
            "resolver_component_tests_runner_invoker": [
                "event_engine_dns",
            ],
            "xds_end2end_test": [
                "pick_first_new",
                "work_serializer_dispatch",
            ],
        },
    },
}
