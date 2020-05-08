package(default_visibility = ["//visibility:public"])

cc_library(
    name = "rendering_pipeline",
    hdrs = ["rendering_pipeline.h"],
    srcs = ["rendering_pipeline.cc"],
    deps = [
        "//src/common:camera",
        "//src/modules:vertex_shader",
        "//src/modules:rasterizer",
        "//src/modules:fragment_shader",
        "//src/modules:per_sample_processing",
        "//src/common:model",
        "//src/utils:util",
        "//src/modules:vertex_loader",
    ]
)
