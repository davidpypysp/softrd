package(default_visibility = ["//visibility:public"])

cc_library(
    name = "vertex",
    hdrs = ["vertex.h"],
    deps = [
        "//src/math:vector",
    ]
)

cc_library(
    name = "fragment",
    hdrs = ["fragment.h"],
    deps = [
        "//src/math:vector",
    ]
)

cc_library(
    name = "primitive",
    hdrs = ["primitive.h"],
    deps = [
        "//src/modules:vertex_shader",
    ]
)

cc_library(
    name = "mesh",
    hdrs = ["mesh.h"],
    deps = [
        "//src/components:vertex",
    ]
)

cc_library(
    name = "camera",
    hdrs = ["camera.h"],
    deps = [
        "//src/math:math_lib",
    ]
)

cc_library(
    name = "texture",
    hdrs = ["texture.h"],
    deps = [
        "//src/math:math_lib",
        "@soil//:soil_lib",
    ]
)

cc_library(
    name = "material",
    hdrs = ["material.h"],
    deps = [
        "//src/components:texture",
    ]
)

cc_library(
    name = "model",
    hdrs = ["model.h"],
    srcs = ["model.cc"],
    deps = [
        "//src/components:mesh",
        "@assimp//:assimp_lib",
    ]
)

cc_library(
    name = "light",
    hdrs = ["light.h"],
    deps = [
        "//src/components:material",
        "//src/math:vector",
    ]
)



