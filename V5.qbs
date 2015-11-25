import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    files: [
        "main.cpp",
        "src/parser/scanner.cpp",
        "src/parser/scanner.h",
        "src/parser/token.cpp",
        "src/parser/token.h",
    ]

    cpp.cxxFlags:"-std=c++11"

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

