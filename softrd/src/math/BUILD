package(default_visibility = ["//visibility:public"])

cc_library(
    name = "vector",
    hdrs = ["vector.h"],
)

cc_library(
    name = "plane",
    hdrs = ["plane.h"],
)

cc_library(
    name = "matrix",
    hdrs = ["matrix.h"],
)

cc_library(
    name = "math_lib",
    hdrs = ["math_lib.h"],
    deps = [
        "//src/math:matrix",
        "//src/math:plane",
    ]
)
