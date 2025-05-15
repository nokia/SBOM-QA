include(GNUInstallDirs)
include(Doxygen)

if(EXISTS "${PROJECT_SOURCE_DIR}/README.md")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/README.md")
endif()

# enable doxygen documentaion with the "awesome-sidebar" theme
enable_doxygen("awesome-sidebar")

add_custom_command(
    TARGET doxygen-docs
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/html/images
    COMMENT "Copying image files to Doxygen HTML output directory"
    VERBATIM
)

install(
    DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
    COMPONENT Coronan_Development
)
