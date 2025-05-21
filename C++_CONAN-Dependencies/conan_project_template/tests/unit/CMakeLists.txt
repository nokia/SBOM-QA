# required minimum version of cmake
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# set the path to the additional cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/modules)

# TODO add your header files here
set(UNITTEST_HEADER_FILES
    )

source_group("Header Files" FILES ${UNITTEST_HEADER_FILES})

# set report and documentation output paths
if(NOT REPORT_DIR)
  set(REPORT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../reports CACHE PATH "Reports directory")
endif(NOT REPORT_DIR)
if(NOT COVERAGE_REPORT_DIR)
  set(COVERAGE_REPORT_DIR ${REPORT_DIR}/coverage CACHE PATH "Coverage reports output directory")
endif(NOT COVERAGE_REPORT_DIR)
if(NOT TESTS_REPORT_DIR)
  set(TESTS_REPORT_DIR ${REPORT_DIR}/tests CACHE PATH "Testresult output directory")
endif(NOT TESTS_REPORT_DIR)

# create report and documentation output directories
file(MAKE_DIRECTORY
    ${REPORT_DIR}
    ${COVERAGE_REPORT_DIR}
    ${TESTS_REPORT_DIR}
    )

if(NOT RUNTIME_OUTPUT_DIRECTORY)
  set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../bin)
endif()

set(TEST_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY}/tests)

file(MAKE_DIRECTORY
    ${RUNTIME_OUTPUT_DIRECTORY}
    ${TEST_RUNTIME_OUTPUT_DIRECTORY}
    )

# Check for clang compiler
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
  set(CMAKE_COMPILER_IS_CLANGCXX 1)
endif()

#########################################################################
# Create test executables for every testclass (no coverage measurement) #
#########################################################################

find_package(GMock REQUIRED)

if(NOT TARGET internal::projectlib)
  include(${CMAKE_CURRENT_SOURCE_DIR}/../../project-export.cmake)
endif()

function(register_test TEST_FILE)
  get_filename_component(TEST_NAME ${TEST_FILE} NAME)
  message(STATUS "Adding " ${TEST_NAME})
  add_executable(${TEST_NAME} ${TEST_FILE}.cpp)
  target_link_libraries(${TEST_NAME}
      internal::projectlib ${ARGN}
      GMock::GMock
      GMock::Main
      )

  if(CMAKE_COMPILER_IS_CLANGCXX)
    target_compile_options(${TEST_NAME}
        PRIVATE
        -Wno-global-constructors
        )
  endif(CMAKE_COMPILER_IS_CLANGCXX)

  #    gtest_add_tests(${TEST_NAME} "" ${TEST_FILE}.cpp)
  set(UNITTEST_SOURCES ${UNITTEST_SOURCES} ${TEST_FILE}.cpp PARENT_SCOPE)
endfunction()

# TODO add here all your tests (source file name without extension)
register_test(src/dummy_test)
register_test(src/gmock_test)

######################################
# Create a single test executable.   #
# Without coverage measurement       #
######################################

add_executable(unittests
    ${UNITTEST_SOURCES}
    ${UNITTEST_HEADER_FILES}
    )
add_executable(tests::unit ALIAS unittests)

set_target_properties(unittests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${TEST_RUNTIME_OUTPUT_DIRECTORY}"
    )

target_link_libraries(unittests
    internal::projectlib ${ARGN}
    GMock::GMock
    GMock::Main
    )

if(CMAKE_COMPILER_IS_CLANGCXX)
  target_compile_options(unittests
      PRIVATE
      -Wno-global-constructors
      )
endif(CMAKE_COMPILER_IS_CLANGCXX)

add_test(AllUnittests unittests)

# Target: run gtest unit tests
add_custom_target(run_unittests
    ALL # run the test always for target all
    unittests --gtest_shuffle
    )

add_dependencies(run_unittests
    tests::unit
    )

# Target: run gtest unit tests with xunit output
add_custom_target(run_unittests_xunit
    unittests --gtest_output=xml:${TESTS_REPORT_DIR}/unittests.xml
    )

add_dependencies(run_unittests_xunit
    tests::unit
    )

######################################
# Create a single test executable.   #
# With coverage measurement          #
######################################
if(UNIX AND CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE MATCHES Debug)
  include(CodeCoverage)
  add_executable(unittests-cov
      EXCLUDE_FROM_ALL
      ${UNITTEST_SOURCES}
      ${UNITTEST_HEADER_FILES}
      )

  set_target_properties(unittests-cov
      PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${TEST_RUNTIME_OUTPUT_DIRECTORY}"
      )

  target_link_libraries(unittests-cov
      internal::projectlib-cov ${ARGN}
      GMock::GMock
      GMock::Main
      )

  if(CMAKE_COMPILER_IS_CLANGCXX)
    target_compile_options(unittests-cov
        PRIVATE
        -Wno-global-constructors
        )
  endif(CMAKE_COMPILER_IS_CLANGCXX)

  setup_target_for_coverage_cobertura(coverage_unittests
      unittests-cov
      ${COVERAGE_REPORT_DIR}/unittests
      "--gtest_output='xml:${TESTS_REPORT_DIR}/unittests.xml'"
      )
endif(UNIX AND CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE MATCHES Debug)
