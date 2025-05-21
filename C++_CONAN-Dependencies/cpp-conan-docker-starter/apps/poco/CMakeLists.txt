cmake_minimum_required(VERSION 3.9)
project(poco)

file(GLOB MAIN_SOURCE_FILES "./*.cpp")

include_directories(${VENDOR_DIR})
include_directories(${INCLUDE_DIR})

add_executable(poco ${MAIN_SOURCE_FILES})
target_link_libraries(poco ${CONAN_LIBS})

install(TARGETS poco DESTINATION ${BUILD_FOLDER})