package(default_visibility = ["//visibility:public"])

cc_library(
    name = "vertex_shader",
    hdrs = ["vertex_shader.h"],
    srcs = ["vertex_shader.cc"],
    deps = [
        "//src/math:vector",
        "//src/math:matrix",
        "//src/common:vertex",
    ]
)

cc_library(
    name = "vertex_loader",
    hdrs = ["vertex_loader.h"],
    srcs = ["vertex_loader.cc"],
    deps = [
        "//src/common:vertex",
    ]
)

cc_library(
    name = "per_sample_processing",
    hdrs = ["per_sample_processing.h"],
    srcs = ["per_sample_processing.cc"],
    deps = [
        "//src/utils:util",
        "//src/modules:fragment_shader",
    ]
)

cc_library(
    name = "fragment_shader",
    hdrs = ["fragment_shader.h"],
    srcs = ["fragment_shader.cc"],
    deps = [
        "//src/common:fragment",
        "//src/common:texture",
        "//src/common:light",
        "//src/common:material",
    ]
)

cc_library(
    name = "clipping",
    hdrs = ["clipping.h"],
    srcs = ["clipping.cc"],
    deps = [
        "//src/common:primitive",
        "//src/math:math_lib",
    ]
)

cc_library(
    name = "primitive_assembly",
    hdrs = ["primitive_assembly.h"],
    srcs = ["primitive_assembly.cc"],
    deps = [
        "//src/common:primitive",
        ":vertex_shader",
        ":clipping",
        "//src/utils:util",
    ]
)

cc_library(
    name = "rasterizer",
    hdrs = ["rasterizer.h"],
    srcs = ["rasterizer.cc"],
    deps = [
        ":primitive_assembly",
        "//src/math:math_lib",
        "//src/common:fragment",
        "//src/common:camera",
    ]
)