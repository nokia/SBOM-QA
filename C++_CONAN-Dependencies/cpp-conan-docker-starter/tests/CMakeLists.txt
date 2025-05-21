cmake_minimum_required(VERSION 3.9)
project(tests)

include_directories(${VENDOR_DIR})
include_directories(${INCLUDE_DIR})

set(PROJECTS_SOURCE_FILES "")

subdirlist(PROJECTS_MODULES ${SOURCE_DIR})
foreach(MODULE_DIR ${PROJECTS_MODULES})
    if(MODULE_DIR STREQUAL "main")
        continue()
    endif()
    set(files "")
    file(GLOB_RECURSE files "${SOURCE_DIR}/${MODULE_DIR}/*.cpp")
    list(APPEND PROJECTS_SOURCE_FILES ${files})
endforeach()

file(GLOB_RECURSE TESTS_SOURCE_FILES "./*.cpp")

add_executable(tests ${TESTS_SOURCE_FILES} ${PROJECTS_SOURCE_FILES})
install(TARGETS tests DESTINATION ${BUILD_FOLDER})