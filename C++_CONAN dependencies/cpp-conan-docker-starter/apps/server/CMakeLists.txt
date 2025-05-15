cmake_minimum_required(VERSION 3.9)
project(server)

file(GLOB MAIN_SOURCE_FILES "./*.cpp")

include_directories(${VENDOR_DIR})
include_directories(${INCLUDE_DIR})

add_executable(server ${MAIN_SOURCE_FILES})
target_link_libraries(server ${CONAN_LIBS})

install(TARGETS server DESTINATION ${BUILD_FOLDER})