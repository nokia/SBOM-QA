function(enable_coverage project_name)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" OFF)

        if(ENABLE_COVERAGE)
            target_compile_options(
                ${project_name} INTERFACE --coverage -O0 -g -fno-inline -fno-elide-constructors
                                          -fprofile-update=prefer-atomic
            )
            target_link_libraries(${project_name} INTERFACE --coverage)
        endif()
    endif()
endfunction()
