package(default_visibility = ["//visibility:public"])

cc_library(
    name = "vertex_shader",
    hdrs = ["vertex_shader.h"],
    srcs = ["vertex_shader.cc"],
    deps = [
        "//src/math:vector",
        "//src/math:matrix",
        "//src/components:vertex",
    ]
)

cc_library(
    name = "vertex_loader",
    hdrs = ["vertex_loader.h"],
    srcs = ["vertex_loader.cc"],
    deps = [
        "//src/components:vertex",
    ]
)

cc_library(
    name = "per_sample_processing",
    hdrs = ["per_sample_processing.h"],
    srcs = ["per_sample_processing.cc"],
    deps = [
        "//src/utils:util",
    ]
)

cc_library(
    name = "fragment_shader",
    hdrs = ["fragment_shader.h"],
    srcs = ["fragment_shader.cc"],
    deps = [
        "//src/components:fragment",
        "//src/components:texture",
        "//src/components:light",
        "//src/components:material",
    ]
)

cc_library(
    name = "clipping",
    hdrs = ["clipping.h"],
    srcs = ["clipping.cc"],
    deps = [
        "//src/components:primitive",
        "//src/math:math_lib",
    ]
)

cc_library(
    name = "primitive_assembly",
    hdrs = ["primitive_assembly.h"],
    srcs = ["primitive_assembly.cc"],
    deps = [
        "//src/components:primitive",
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
        "//src/components:fragment",
        "//src/components:camera",
    ]
)