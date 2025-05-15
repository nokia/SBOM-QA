cmake_minimum_required(VERSION 3.9)
project(cli)

set(APP_SOURCES "${APPS_DIR}/cli/main.cpp")

include_directories(${VENDOR_DIR})
include_directories(${INCLUDE_DIR})

add_executable(cli ${APP_SOURCES})
target_link_libraries(cli math strings ${CONAN_LIBS})