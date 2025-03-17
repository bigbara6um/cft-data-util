cmake_minimum_required(VERSION 3.30.0)
project(data-util VERSION 0.0.1 LANGUAGES C)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(GenerateExportHeader)

# Build sources
set(
    data_lib_src
    "src/data_util.c"
)

add_library(data_lib STATIC ${data_lib_src})

generate_export_header(data_lib)

target_include_directories(data_lib
    PUBLIC "include/")

file(GLOB data_lib_headers "include/*.h")

set_target_properties(data_lib
    PROPERTIES
        PUBLIC_HEADER "${data_lib_headers}"
)

add_executable(data-util "main.c")
target_link_libraries(data-util PUBLIC data_lib)

add_executable(test-util "test.c")
target_link_libraries(test-util PUBLIC data_lib)
