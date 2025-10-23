load("//tools:cpplint.bzl", "cpplint")
load("//tools:apollo_package.bzl", "apollo_cc_library", "apollo_package")

package(default_visibility = ["//visibility:public"])

apollo_cc_library(
    name = "multilocalization_gflags",
    srcs = ["multilocalization_gflags.cc",
            "utility.cpp",
            "file_utils.cpp",
    ],
    hdrs = [
        "multilocalization_gflags.h",
        "utility.h",
        "concurrent_deque.h",
        "common_utils.h",
        "file_utils.h",
    ],
    deps = ["@com_github_gflags_gflags//:gflags"],
)

apollo_package()

cpplint()
