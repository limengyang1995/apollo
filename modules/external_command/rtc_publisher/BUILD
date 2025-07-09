# Copyright 2017 gRPC authors.
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

package(default_visibility = ["//visibility:public"])

load("//tools/install:install.bzl", "install", "install_files", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
load("//tools:apollo_package.bzl", "apollo_cc_binary", "apollo_cc_library", "apollo_cc_test", "apollo_component", "apollo_package")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")

# The following three rules demonstrate the usage of the cc_grpc_library rule in
# in a mode compatible with the native proto_library and cc_proto_library rules.
proto_library(
    name = "rtc_publisher_proto",
    srcs = ["protos/rtc_publisher.proto"],
)

cc_proto_library(
    name = "rtc_publisher_cc_proto",
    deps = [":rtc_publisher_proto"],
)

cc_grpc_library(
    name = "rtc_publisher_cc_grpc",
    srcs = [":rtc_publisher_proto"],
    grpc_only = True,
    deps = [":rtc_publisher_cc_proto"],
)

proto_library(
    name = "protos/rtc_publisher_proto",
    srcs = ["protos/rtc_publisher.proto"],
)

apollo_cc_library(
    name = "rtc_publisher_client",
    srcs = ["client/rtc_publisher_client.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":rtc_publisher_cc_grpc",
        "//:grpc++",
    ],
)

# apollo_cc_binary(
#     name = "rtc_publisher_server",
#     srcs = ["server/rtc_publisher_server.cc"],
#     defines = ["BAZEL_BUILD"],
#     deps = [
#         ":rtc_publisher_cc_grpc",
#         "//:grpc++",
#         "//:grpc++_reflection",
#     ],
# )

cpplint()
apollo_package()
