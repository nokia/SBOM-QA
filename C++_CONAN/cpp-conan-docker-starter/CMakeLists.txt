cmake_minimum_required(VERSION 3.9)
project(CPP_PROJECT)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake.modules/")
include("./cmake.modules/macros.cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})


set(BUILD_FOLDER "./build")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(APPS_DIR "${PROJECT_SOURCE_DIR}/apps")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor")


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(tests)

enable_testing()

#enable_testing()
#include_directories(include)
#include_directories(${SOURCE_DIR})
#add_executable(app main.cc)
#target_link_libraries(app ${CONAN_LIBS})