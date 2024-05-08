# Description:
# Diff library in C++ of tokens of arbitrary type using random-access iterators.
# Derived from the "Diff" third of the DiffMatchPatch library C++ implementation
# in google3/third_party/diff_match_patch/cpp/diff_match_patch.cpp
# written by Neil Fraser (fraser@google.com) and described in
# http://wiki.corp.google.com/twiki/bin/view/Main/DiffMatchPatch

load("//tools/build_defs/license:license.bzl", "license")

package(
    default_applicable_licenses = ["//third_party/diff:license"],
    default_visibility = ["//visibility:public"],
)

license(
    name = "license",
    package_name = "diff",
)

# For license choices, see go/thirdpartylicenses
licenses(["notice"])

exports_files(["LICENSE"])

cc_library(
    name = "diff",
    hdrs = ["diff.h"],
)

cc_test(
    name = "diff_test",
    size = "small",
    srcs = [
        "diff_test.cc",
    ],
    deps = [
        ":diff",
        "//base",
        "//testing/base/public:gunit_main",
        "//third_party/absl/strings",
    ],
)

cc_test(
    name = "diff_fuzzer",
    srcs = ["diff_fuzzer.cc"],
    tags = [
        "componentid:80116",
        "hotlists:1918093",
    ],
    deps = [
        ":diff",
        "//testing/base/public:gunit_main",
        "//testing/fuzzing:fuzztest",
        "//third_party/absl/strings",
    ],
)
