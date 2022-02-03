# Copyright 2020 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
licenses(["notice"])

cc_library(
    name = "mediums",
    srcs = [
        "ble.cc",
        "bluetooth_classic.cc",
        "bluetooth_radio.cc",
        "mediums.cc",
        "uuid.cc",
        "webrtc.cc",
        "wifi_lan.cc",
    ],
    hdrs = [
        "ble.h",
        "bluetooth_classic.h",
        "bluetooth_radio.h",
        "lost_entity_tracker.h",
        "mediums.h",
        "uuid.h",
        "webrtc.h",
        "wifi_lan.h",
    ],
    visibility = [
        "//connections/implementation:__subpackages__",
    ],
    deps = [
        ":utils",
        "//connections:core_types",
        "//connections/implementation/mediums/ble_v2",
        "//connections/implementation/mediums/webrtc",
        "//connections/implementation/mediums/webrtc:data_types",
        "//connections/implementation/proto:offline_wire_formats_portable_proto",
        "//internal/platform:base",
        "//internal/platform:cancellation_flag",
        "//internal/platform:comm",
        "//internal/platform:logging",
        "//internal/platform:types",
        "//proto/mediums:web_rtc_signaling_frames_cc_proto",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/functional:bind_front",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/time",
        "//webrtc/api:libjingle_peerconnection_api",
    ],
)

cc_library(
    name = "utils",
    srcs = [
        "utils.cc",
        "webrtc_peer_id.cc",
    ],
    hdrs = [
        "utils.h",
        "webrtc_peer_id.h",
        "webrtc_socket.h",
    ],
    visibility = [
        "//connections/implementation:__pkg__",
        "//connections/implementation/mediums:__pkg__",
        "//connections/implementation/mediums/webrtc:__pkg__",
    ],
    deps = [
        "//connections/implementation/mediums/webrtc:data_types",
        "//connections/implementation/proto:offline_wire_formats_portable_proto",
        "//internal/platform:base",
        "//internal/platform:types",
        "@com_google_absl//absl/strings",
    ],
)

cc_test(
    name = "core_internal_mediums_test",
    size = "small",
    srcs = [
        "ble_test.cc",
        "bluetooth_classic_test.cc",
        "bluetooth_radio_test.cc",
        "lost_entity_tracker_test.cc",
        "uuid_test.cc",
        "wifi_lan_test.cc",
    ],
    shard_count = 16,
    deps = [
        ":mediums",
        ":utils",
        "//internal/platform:base",
        "//internal/platform:comm",
        "//internal/platform:test_util",
        "//internal/platform:types",
        "//internal/platform/implementation/g3",  # build_cleaner: keep
        "@com_google_googletest//:gtest_main","@com_github_protobuf_matchers//protobuf-matchers:protobuf-matchers",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
    ],
)

cc_test(
    name = "core_internal_mediums_webrtc_test",
    size = "small",
    srcs = [
        "webrtc_peer_id_test.cc",
        "webrtc_test.cc",
    ],
    shard_count = 16,
    tags = [
        "notsan",  # NOTE(b/139734036): known data race in usrsctplib.
        "requires-net:external",
    ],
    deps = [
        ":mediums",
        ":utils",
        "//internal/platform:base",
        "//internal/platform:test_util",
        "//internal/platform:types",
        "//internal/platform/implementation/g3",  # build_cleaner: keep
        "@com_google_googletest//:gtest_main","@com_github_protobuf_matchers//protobuf-matchers:protobuf-matchers",
    ],
)