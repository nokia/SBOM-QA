include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)

# Only build the following QT submodules:
set(QT_BUILD_SUBMODULES
    "qtbase;qtcharts"
    CACHE STRING "Qt6 Submodules to build"
)
set(QT_VERSION
    "v6.8.2"
    CACHE STRING "Qt6 git version"
)
set(QT_WILL_BUILD_TOOLS ON)

# Disable some unnecessary QT features to reduce the build time.
set(QT_FEATURE_sql OFF)
set(QT_FEATURE_network OFF)
set(QT_FEATURE_dbus OFF)
set(QT_FEATURE_testlib OFF)
set(QT_FEATURE_opengl OFF)
set(QT_FEATURE_opengles2 OFF)
set(QT_FEATURE_opengles3 OFF)
set(QT_FEATURE_charts ON)
set(QT_BUILD_STANDALONE_TESTS OFF)
set(QT_BUILD_EXAMPLES OFF)
set(QT_BUILD_EXAMPLES_BY_DEFAULT OFF)
set(QT_BUILD_TESTS OFF)
set(QT_BUILD_DOCS OFF)

set(QT_MODULES Core Widgets Charts)
set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
    qt6
    GIT_REPOSITORY "https://github.com/qt/qt5.git"
    GIT_TAG "${QT_VERSION}"
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    GIT_SUBMODULES ${QT_BUILD_SUBMODULES}
)

FetchContent_MakeAvailable(qt6)

# Qt needs to be compiled in a mode that enables `INT128`
set_target_properties(Core PROPERTIES CXX_EXTENSIONS ON)
