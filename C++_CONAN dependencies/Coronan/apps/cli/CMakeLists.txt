cmake_minimum_required(VERSION 3.22)

project(
    coronan_cli
    VERSION 0.2.0
    LANGUAGES CXX
)

set(HEADER_LIST "${CMAKE_CURRENT_LIST_DIR}/src/argument_parser.hpp")

add_library(cli_arg_parser STATIC ${CMAKE_CURRENT_LIST_DIR}/src/argument_parser.cpp ${HEADER_LIST})

add_library(coronan_cli::arg_parser ALIAS cli_arg_parser)

find_package(lyra REQUIRED CONFIG)
find_package(fmt REQUIRED CONFIG)
find_package(date REQUIRED CONFIG)

target_link_libraries(
    cli_arg_parser
    PUBLIC bfg::lyra
    PUBLIC date::date
    PRIVATE fmt::fmt
    PRIVATE coronan::compile_warnings
    PRIVATE coronan::compile_options
)

target_include_directories(
    cli_arg_parser PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# allow for static analysis options
include(StaticAnalyzers)
enable_static_analysis(cli_arg_parser)

# IDE stuff
source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)

add_executable(coronan_cli ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp)

add_executable(coronan::coronan_cli ALIAS coronan_cli)
set_target_properties(coronan_cli PROPERTIES CXX_EXTENSIONS OFF OUTPUT_NAME coronan)

target_link_libraries(
    coronan_cli
    PRIVATE coronan_cli::arg_parser
    PRIVATE fmt::fmt
    PRIVATE coronan::library
    PRIVATE coronan::compile_warnings
    PRIVATE coronan::compile_options
)

include(StaticAnalyzers)
enable_static_analysis(coronan_cli)

include(CTest)

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS coronan_cli RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Coronan_Runtime_CLI)
