cmake_minimum_required(VERSION 3.22)

project(
    coronan_tests
    VERSION 0.1
    LANGUAGES CXX
)

add_executable(cli_unittests ${CMAKE_CURRENT_LIST_DIR}/argument_parser_test.cpp)

add_executable(coronan_cli::unittests ALIAS cli_unittests)

find_package(Catch2 REQUIRED CONFIG)

target_link_libraries(
    cli_unittests
    PRIVATE Catch2::Catch2WithMain
    PRIVATE coronan_cli::arg_parser
    PRIVATE coronan::compile_warnings
    PRIVATE coronan::compile_options
)

include(Catch)

catch_discover_tests(
    cli_unittests
    TEST_PREFIX
    "unittest."
    REPORTER
    XML
    OUTPUT_DIR
    .
    OUTPUT_PREFIX
    "unittest."
    OUTPUT_SUFFIX
    .xml
)

add_custom_target(
    run_cli_unittests ALL
    COMMAND $<TARGET_FILE:coronan_cli::unittests>
    COMMENT "Run cli unittests"
)
