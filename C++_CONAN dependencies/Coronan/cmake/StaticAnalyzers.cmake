find_program(CPPCHECK cppcheck)
if(CPPCHECK)
    option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" ON)
endif()
find_program(
    CLANGTIDY
    NAMES
    NAMES clang-tidy clang-tidy-11 clang-tidy-10 clang-tidy-9 clang-tidy-8
)
if(CLANGTIDY)
    option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" ON)
endif()

find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
if(INCLUDE_WHAT_YOU_USE)
    option(ENABLE_INCLUDE_WHAT_YOU_USE "Enable static analysis with include-what-you-use" ON)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    option(ENABLE_LINK_WHAT_YOU_USE "Enable link what you use" OFF)
endif()

function(enable_static_analysis project_name)

    if(ENABLE_CPPCHECK)
        set(CPPCHECK_PROPERTIES "${CPPCHECK}" "--suppress=missingInclude" "--enable=all" "--std=c++17" "--inline-suppr"
                                "--inconclusive"
        )
        set_target_properties(${project_name} PROPERTIES CXX_CPPCHECK "${CPPCHECK_PROPERTIES}")
        message(STATUS "cppcheck static analysis enabled for ${project_name} (cppcheck: ${CPPCHECK})")
    endif()

    if(ENABLE_CLANG_TIDY)
        set(CLANG_TIDY_PROPERTIES "${CLANGTIDY}" "-p=${PROJECT_BINARY_DIR}" "-extra-arg-before=-std=c++17"
                                  "-extra-arg=-Wno-unknown-warning-option"
        )
        set_target_properties(${project_name} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_PROPERTIES}")
        message(STATUS "clang-tidy static analysis enabled for ${project_name} (clang-tidy: ${CLANGTIDY})")
    endif()

    if(ENABLE_INCLUDE_WHAT_YOU_USE)
        set_target_properties(${project_name} PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE})
        message(STATUS "include-what-you-use static analysis enabled for ${project_name}")
    endif()

    if(ENABLE_LINK_WHAT_YOU_USE)
        set_target_properties(${project_name} PROPERTIES LINK_WHAT_YOU_USE ${ENABLE_LINK_WHAT_YOU_USE})
        message(STATUS "link-what-you-use static analysis enabled for ${project_name}")
    endif()

endfunction()
