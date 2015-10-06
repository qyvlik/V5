import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    files: [
        "main.cpp",
        "src/arguments.cpp",
        "src/arguments.h",
        "src/object.cpp",
        "src/object.h",
        "src/return.cpp",
        "src/return.h",
        "src/v5.h",
        "src/variant.cpp",
        "src/variant.h",
    ]

    cpp.cxxFlags:"-std=c++11"

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

