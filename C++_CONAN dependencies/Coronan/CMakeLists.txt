cmake_minimum_required(VERSION 3.22)

# Only set the cxx_standard if it is not set by someone else
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example when
# compiling with PCH enabled
# https://github.com/cpp-best-practices/cmake_template/blob/main/CMakeLists.txt
set(CMAKE_CXX_EXTENSIONS OFF)

project(
    Coronan
    VERSION 1.0.0
    DESCRIPTION "Conan example project showing Covid-19 cases."
    LANGUAGES CXX
)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/StandardProjectSettings.cmake)

option(ENABLE_TESTING "Enable Test Builds" ON)

# conan cmake_layout puts files used for find_package into specific place. Add
# it to CMAKE_PREFIX_PATH
if(CMAKE_CONFIGURATION_TYPES)
    # Multi-configuration generator (e.g. Visual Studio)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_BINARY_DIR}/generators")
else()
    # Single-configuration generator
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/generators")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
add_library(coronan::compile_options ALIAS project_options)
target_compile_features(project_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if(ENABLE_BUILD_WITH_TIME_TRACE)
        target_compile_options(project_options INTERFACE -ftime-trace)
    endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
add_library(coronan::compile_warnings ALIAS project_warnings)

# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

option(ENABLE_SANITIZERS "Enable sanitizer" OFF)

if(ENABLE_SANITIZERS)
    # sanitizer options if supported by compiler
    include(cmake/Sanitizers.cmake)
    enable_sanitizers(project_options)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(cmake/Doxygen.cmake)

    if(ENABLE_DOXYGEN)
        set_property(GLOBAL PROPERTY USE_FOLDERS ON)
        add_subdirectory(docs)
    endif()
endif()

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)

    if(ENABLE_CLANG_TIDY)
        message(WARNING "Using ENABLE_CLANG_TIDY together with ENABLE_PCH will give compiler errors.")
    endif(ENABLE_CLANG_TIDY)
    # This sets a global PCH parameter, each project will build its own PCH,
    # which is a good idea if any #define's change
    #
    target_precompile_headers(project_options INTERFACE <vector> <string>)
endif()

# enable coverage if supported by compiler
include(cmake/Coverage.cmake)
enable_coverage(project_options)

# configure files based on CMake configuration options
add_subdirectory(configured_files)

add_subdirectory(src)

if(NOT PROJECT_IS_TOP_LEVEL)
    return()
endif()

include(CTest)

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(apps/cli)
add_subdirectory(apps/qt)

# If MSVC is being used, and ASAN is enabled, we need to set the debugger
# environment so that it behaves well with MSVC's debugger, and we can run the
# target from visual studio
if(MSVC)
    get_all_installable_targets(all_targets)
    message("all_targets=${all_targets}")
    set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()

# set the startup project for the "play" button in MSVC
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT coronan_gui)

if(CMAKE_SKIP_INSTALL_RULES)
    return()
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/Coronan.cmake.in ${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}/cmake
    NO_SET_AND_CHECK_MACRO NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

if(NOT WIN32 AND CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(CMAKE_INSTALL_PREFIX "/opt/bbv.ch/${PROJECT_NAME}")
endif()

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
          ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    COMPONENT Coronan_Development
)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT Coronan_Development
)

install(
    FILES LICENSE
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
    COMPONENT Coronan_Development
)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    include(cmake/CPackConfig.cmake)
endif()
