# general settings
set(CPACK_PACKAGE_NAME "Coronan")
set(CPACK_PACKAGE_VENDOR "bbv Software Services AG")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Present the current data of Corona (Covid-19) cases for a country.")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set(CPACK_VERBATIM_VARIABLES YES)
set(CPACK_ARCHIVE_THREADS 0)
set(CPACK_SOURCE_GENERATOR TGZ)
set(CPACK_SOURCE_IGNORE_FILES
    \\.git/
    build/
    \\.devcontainer/
    \\.github/
    \\.venv/
    \\.vscode/
    \\.cache/
    appveyor.yml
    \\.gitpod.yml
    \\.codecov.yml
)

# WIX installer needs a licence file with .txt ending
configure_file(${PROJECT_SOURCE_DIR}/LICENSE ${CMAKE_CURRENT_BINARY_DIR}/LICENSE.txt COPYONLY)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_BINARY_DIR}/LICENSE.txt)

# versions
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

if(WIN32)
    # WIX config CPACK_WIX_UPGRADE_GUID should be explicitly set to a constant
    # generated globally unique identifier (GUID) to allow your installers to
    # replace existing installations that use the same GUID.
    set(CPACK_WIX_UPGRADE_GUID "e2b63053-6f9d-4bd1-97b6-97ec70b70a7d")
    set(CPACK_GENERATOR ZIP WIX)
    set(CPACK_SOURCE_GENERATOR ZIP)
elseif(APPLE)
    set(CPACK_GENERATOR TGZ productbuild)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CPACK_GENERATOR TGZ)
else()
    set(CPACK_GENERATOR TGZ)
endif()

find_program(DPKG_PROGRAM dpkg)
if(DPKG_PROGRAM)
    list(APPEND CPACK_GENERATOR DEB)
    find_program(SHLIBDEPS_PROGRAMM dpkg-shlibdeps)
    if(SHLIBDEPS_PROGRAMM)
        set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    else()
        message(WARNING "dpkg-shlibdeps not found, skipping shlibdeps")
    endif()
    # DEB package config
    set(CPACK_DEBIAN_PACKAGE_NAME "coronan")

    set(CPACK_PACKAGE_CONTACT "michel.estermann@bbv.ch")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Michel Estermann <michel.estermann@bbv.ch>")
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/bbvch/Coronan")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt6widgets6 (>=6.2.4),libqt6charts6 (>=6.2.4)")
endif(DPKG_PROGRAM)

find_program(
    BINARYCREATOR_EXECUTABLE
    NAMES binarycreator
    HINTS ${CPACK_IFW_ROOT}/bin
)
if(BINARYCREATOR_EXECUTABLE)
    message(STATUS "Found binarycreator: ${BINARYCREATOR_EXECUTABLE}")
    list(APPEND CPACK_GENERATOR IFW)
    # IFW (Qt Installer Framework) config
    set(CPACK_IFW_VERBOSE ON)
    set(CPACK_IFW_PACKAGE_TITLE "Co[ro]nan")
    include(CPackIFW)
endif()

include(CPack)

cpack_add_component(
    Coronan_Development DISABLED
    DISPLAY_NAME "coronan SDK"
    DESCRIPTION "Development components"
    INSTALL_TYPES Full Developer
)

cpack_add_component(
    Coronan_Runtime_GUI
    DISPLAY_NAME "coronan Qt App"
    DESCRIPTION "Gui executables"
    INSTALL_TYPES Full Developer
)

cpack_add_component(
    Coronan_Runtime_CLI DISABLED
    DISPLAY_NAME "coronan command line interface"
    DESCRIPTION "Gui executables"
    INSTALL_TYPES Full Developer Minimal
)

if(BINARYCREATOR_EXECUTABLE)
    # Only allow to install qt application
    cpack_ifw_configure_component(Coronan_Development VIRTUAL)
    cpack_ifw_configure_component(Coronan_Runtime_GUI ESSENTIAL)
    cpack_ifw_configure_component(Coronan_Runtime_CLI VIRTUAL)
endif()

cpack_add_install_type(Full)
cpack_add_install_type(Minimal)
cpack_add_install_type(Developer DISPLAY_NAME "SDK Development")
