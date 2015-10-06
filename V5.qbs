import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    files: [
        "main.cpp",
        "src/arguments.cpp",
        "src/arguments.h",
        "src/lexicalparser.cpp",
        "src/lexicalparser.h",
        "src/object.cpp",
        "src/object.h",
        "src/return.cpp",
        "src/return.h",
        "src/token.cpp",
        "src/token.h",
        "src/v5.h",
        "src/v5parser.cpp",
        "src/v5parser.h",
        "src/variant.cpp",
        "src/variant.h",
    ]

    cpp.cxxFlags:"-std=c++11"

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

