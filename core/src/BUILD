
cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        "//src:renderer",
    ]
)

cc_library(
    name = "renderer",
    hdrs = ["renderer.h"],
    srcs = ["renderer.cc"],
    deps = [
        "//src/components:camera",
        "//src/modules:vertex_shader",
        "//src/modules:rasterizer",
        "//src/modules:fragment_shader",
        "//src/modules:per_sample_processing",
        "//src/devices:device",
        "//src/components:model",
        "//src/utils:util",
        "//src/inputs:input",
        "//src/modules:vertex_loader",
    ]
)


cc_binary(
    name = "test_api",
    srcs = ["test_api.cc"],
    deps = [
        "//src/interface:renderer_api",
    ]
)
