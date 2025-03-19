cmake_minimum_required(VERSION 3.25.0)
set(CMAKE_C_COMPILER gcc.exe)
project(CREST VERSION 0.0.1 LANGUAGES C)

# file globbing

file(GLOB_RECURSE sources "src/*.c")

add_executable(CREST ${sources})

target_include_directories(CREST PRIVATE src)
target_link_libraries(CREST PRIVATE microhttpd)
target_compile_options(CREST PRIVATE -g)

set_target_properties(CREST PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)