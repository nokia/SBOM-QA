cmake_minimum_required(VERSION 3.22)

project(
    coronan
    VERSION 0.1
    LANGUAGES CXX
)

set(HEADER_LIST
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/coronan/http_client.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/coronan/corona-api_datatypes.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/coronan/corona-api_parser.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/coronan/corona-api_client.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/coronan/ssl_client.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/coronan/ssl_context.hpp"
)

add_library(coronan STATIC ${HEADER_LIST})

add_library(coronan::library ALIAS coronan)

target_include_directories(
    coronan PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
                   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_sources(
    coronan
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/corona-api_parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ssl_client.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/http_client.cpp
        $<IF:$<BOOL:${WIN32}>,${CMAKE_CURRENT_SOURCE_DIR}/ssl_context-win.cpp,${CMAKE_CURRENT_SOURCE_DIR}/ssl_context-linux.cpp>
)

find_package(Poco REQUIRED CONFIG)
find_package(RapidJSON REQUIRED CONFIG)
find_package(fmt REQUIRED CONFIG)
find_package(date REQUIRED CONFIG)

target_link_libraries(
    coronan
    PUBLIC Poco::Poco
    PUBLIC fmt::fmt
    PUBLIC date::date
    PRIVATE rapidjson
    PRIVATE coronan::compile_warnings
    PRIVATE coronan::compile_options
)

# allow for static analysis options
include(StaticAnalyzers)
enable_static_analysis(coronan)

# IDE stuff
source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}/../include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)

set_target_properties(coronan PROPERTIES CXX_EXTENSIONS OFF)

install(
    TARGETS coronan project_warnings project_options
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Coronan_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Coronan_Development
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Coronan_Development
)

install(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE coronan::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    COMPONENT Coronan_Development
)
