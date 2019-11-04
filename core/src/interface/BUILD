package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "libSoftrdAPI.so",
    deps = [
        "//src/interface:renderer_api",
    ],
    linkshared = True
)

cc_library(
    name = "renderer_api",
    hdrs = ["renderer_api.h"],
    srcs = ["renderer_api.cc"],
    deps = [
        "//src/renderer:rendering_pipeline"
    ]
)
