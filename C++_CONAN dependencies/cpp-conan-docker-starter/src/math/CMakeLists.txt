cmake_minimum_required(VERSION 3.9)
project(math)

file(GLOB_RECURSE SOURCE_FILES "./*.cpp")

include_directories(${VENDOR_DIR})
include_directories(${INCLUDE_DIR})

add_library(math SHARED STATIC ${SOURCE_FILES})
# target_compile_options(math PRIVATE -fvisibility=hidden)
target_link_libraries(math ${CONAN_LIBS})

install(TARGETS math DESTINATION ${BUILD_FOLDER})



# include_directories(${VENDOR_DIR})
# include_directories(${SOURCE_DIR})
# install(TARGETS core DESTINATION ${BUILD_FOLDER})
# install(FILES ${HEADER_FILES} DESTINATION include/core)