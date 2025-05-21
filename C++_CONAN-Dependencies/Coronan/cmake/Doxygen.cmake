find_package(Doxygen OPTIONAL_COMPONENTS dot)
if(Doxygen_FOUND)
    option(ENABLE_DOXYGEN "Enable doxygen doc builds of source" ON)
endif()

function(enable_doxygen DOXYGEN_THEME)
    set(DOXYGEN_CALLER_GRAPH YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
    set(DOXYGEN_DOT_IMAGE_FORMAT svg)
    set(DOXYGEN_DOT_TRANSPARENT YES)
    set(DOXYGEN_EXCLUDE "${CMAKE_BINARY_DIR}")

    if("${DOXYGEN_THEME}" STREQUAL "")
        set(DOXYGEN_THEME "awesome-sidebar")
    endif()

    if("${DOXYGEN_THEME}" STREQUAL "awesome" OR "${DOXYGEN_THEME}" STREQUAL "awesome-sidebar")
        if(POLICY CMP0135)
            cmake_policy(SET CMP0135 NEW)
        endif()

        include(FetchContent)

        FetchContent_Declare(
            _doxygen_theme URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v2.3.4.zip
        )

        FetchContent_MakeAvailable(_doxygen_theme)

        if("${DOXYGEN_THEME}" STREQUAL "awesome" OR "${DOXYGEN_THEME}" STREQUAL "awesome-sidebar")
            set(DOXYGEN_HTML_EXTRA_STYLESHEET "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome.css")
        endif()

        if("${DOXYGEN_THEME}" STREQUAL "awesome-sidebar")
            set(DOXYGEN_HTML_EXTRA_STYLESHEET ${DOXYGEN_HTML_EXTRA_STYLESHEET}
                                              "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome-sidebar-only.css"
            )
        endif()
    else()
        # use the original doxygen theme
    endif()

    message(STATUS "Adding `doxygen-docs` target that builds the documentation.")

    # Must be defined after setting the DOXYGEN_GENERATE_* flags
    doxygen_add_docs(
        doxygen-docs ALL ${PROJECT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen - entry file: ${CMAKE_CURRENT_BINARY_DIR}/html/index.html"
    )
endfunction()
