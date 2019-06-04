cc_library(
    name = "pcc",
    srcs = glob(
        ["src/**/*.c"],
        exclude = ["src/main.c"],
    ),
    hdrs = glob(["src/**/*.h"]),
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "main",
    srcs = ["src/main.c"],
    deps = [":pcc"],
)