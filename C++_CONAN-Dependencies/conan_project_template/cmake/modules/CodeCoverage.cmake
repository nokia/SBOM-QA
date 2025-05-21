# - Enable Code Coverage
#
# 2012-01-31, Lars Bilke
# 2013-07-11, Michel Estermann (modified)
#
# USAGE:
# 1. Copy this file into your cmake modules path
# 2. Add the following line to your CMakeLists.txt:
#      INCLUDE(CodeCoverage)
# 
# 3. Use the function SETUP_TARGET_FOR_COVERAGE to create a custom make target
#    which runs your test executable and produces a lcov code coverage report.
#

if(CMAKE_COMPILER_IS_GNUCXX)
    # Determine the gcc version
    execute_process(COMMAND
            ${CMAKE_CXX_COMPILER} -dumpversion
            OUTPUT_VARIABLE
            GCC_VERSION
            )
endif(CMAKE_COMPILER_IS_GNUCXX)

if(NOT CMAKE_COMPILER_IS_GNUCXX)
    message(FATAL_ERROR "Compiler is not GNU gcc! Aborting...")
endif(NOT CMAKE_COMPILER_IS_GNUCXX)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(WARNING "Code coverage results with an optimised (non-Debug) build may be misleading")
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")

find_program(PYTHON_EXECUTABLE python)
if(NOT PYTHON_EXECUTABLE)
    message(FATAL_ERROR "Python not found! Aborting...")
endif(NOT PYTHON_EXECUTABLE)

find_program(GCOVR_EXE gcovr PATHS ${CMAKE_SOURCE_DIR}/scripts)
if(NOT GCOVR_EXE)
    message(FATAL_ERROR "gcovr not found! Aborting...")
endif(NOT GCOVR_EXE)

set(COVERAGE_EXCLUDE "")
if(EXISTS ${PROJECT_SOURCE_DIR}/tests/coverage.ignore)
    file(READ ${PROJECT_SOURCE_DIR}/tests/coverage.ignore CONTENT)
    string(REGEX REPLACE "\n" ";" CONTENT "${CONTENT}")
    foreach(LINE ${CONTENT})
        set(COVERAGE_EXCLUDE -e '${LINE}' ${COVERAGE_EXCLUDE})
    endforeach(LINE)
endif()


# Param _targetname     The name of new the custom make target
# Param _testrunner     The name of the target which runs the tests
# Param _outputname     cobertura output is generated as _outputname.xml
# Optional fourth parameter is passed as arguments to _testrunner
# Optional fifth parameter is passed as arguments to gcovr
#   Pass them in list form, e.g.: "-j;2" for -j 2
function(SETUP_TARGET_FOR_COVERAGE_COBERTURA _targetname _testrunner _outputname)
    target_link_libraries(${_testrunner} gcov)
    target_compile_options(${_testrunner}
            PUBLIC
            -fprofile-arcs
            -ftest-coverage
            )

    add_custom_target(${_targetname}
            # Run tests
            ${_testrunner} ${ARGV3}

            # Running gcovr
            COMMAND ${GCOVR_EXE} -x -r ${CMAKE_SOURCE_DIR} -o ${_outputname}.xml ${COVERAGE_EXCLUDE} ${ARGV4}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running gcovr to produce Cobertura code coverage report."
            )

    # Show info where to find the report
    add_custom_command(TARGET ${_targetname} POST_BUILD
            COMMAND ;
            COMMENT "Cobertura code coverage report saved in ${_outputname}.xml."
            )
endfunction() # SETUP_TARGET_FOR_COVERAGE_COBERTURA

