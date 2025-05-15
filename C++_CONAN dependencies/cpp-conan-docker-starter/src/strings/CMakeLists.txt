cmake_minimum_required(VERSION 3.9)
project(strings)

file(GLOB SOURCE_FILES "./*.cpp")

include_directories(${VENDOR_DIR})
include_directories(${INCLUDE_DIR})

add_library(strings SHARED STATIC  ${SOURCE_FILES})
# target_compile_options(math PRIVATE -fvisibility=hidden)
target_link_libraries(strings ${CONAN_LIBS})

install(TARGETS strings DESTINATION ${BUILD_FOLDER})