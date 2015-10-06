import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    files: [
        "main.cpp",
        "src/argument.cpp",
        "src/argument.h",
        "src/internal/lexicalparser.cpp",
        "src/internal/lexicalparser.h",
        "src/internal/token.cpp",
        "src/internal/token.h",
        "src/object.cpp",
        "src/object.h",
        "src/return.cpp",
        "src/return.h",
        "src/v5.h",
        "src/v5parser.cpp",
        "src/v5parser.h",
        "src/variant.cpp",
        "src/variant.h",
        "src/variant_p.cpp",
        "src/variant_p.h",
    ]

    cpp.cxxFlags:"-std=c++11"

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

