<details>
<summary>Project State</summary>

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![version](https://img.shields.io/badge/version-v1.0.0-blue)
![GitHub last commit](https://img.shields.io/github/last-commit/bbvch/Coronan)


[![Linux Builds](https://github.com/bbvch/Coronan/actions/workflows/ci-linux.yml/badge.svg)](https://github.com/bbvch/Coronan/actions/workflows/ci-linux.yml)
[![Nix Builds](https://github.com/bbvch/Coronan/actions/workflows/nix.yml/badge.svg)](https://github.com/bbvch/Coronan/actions/workflows/nix.yml)

[![MacOS Builds](https://github.com/bbvch/Coronan/actions/workflows/ci-macos.yml/badge.svg)](https://github.com/bbvch/Coronan/actions/workflows/ci-macos.yml)

[![Windows Builds](https://github.com/bbvch/Coronan/actions/workflows/ci-windows.yml/badge.svg)](https://github.com/bbvch/Coronan/actions/workflows/ci-windows.yml)
[![Build status Appveyor](https://ci.appveyor.com/api/projects/status/3eure0j9ae8dijhj/branch/master?svg=true)](https://ci.appveyor.com/project/meshell/coronan/branch/master)

[![API Documentation](https://github.com/bbvch/Coronan/actions/workflows/api-doc.yml/badge.svg)](https://github.com/bbvch/Coronan/actions/workflows/api-doc.yml)

[![Codacy Security Scan](https://github.com/bbvch/Coronan/actions/workflows/codacy-analysis.yml/badge.svg)](https://github.com/bbvch/Coronan/actions/workflows/codacy-analysis.yml)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/96483b3b9dff405195f7ef0c9c823484)](https://app.codacy.com/gh/bbvch/Coronan/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)

[![CodeQL Analysis](https://github.com/bbvch/Coronan/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/bbvch/Coronan/actions/workflows/codeql-analysis.yml)

[![Coverity Scan](https://github.com/bbvch/Coronan/actions/workflows/coverity-scan.yml/badge.svg)](https://github.com/bbvch/Coronan/actions/workflows/coverity-scan.yml)
[![Coverity Scan](https://img.shields.io/coverity/scan/22882.svg)](https://scan.coverity.com/projects/bbvch-coronan)

[![codecov](https://codecov.io/gh/bbvch/Coronan/branch/master/graph/badge.svg)](https://codecov.io/gh/bbvch/Coronan)

[![SonarQube Cloud](https://sonarcloud.io/images/project_badges/sonarcloud-dark.svg)](https://sonarcloud.io/summary/new_code?id=bbvch_Coronan)

[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=bbvch_Coronan&metric=bugs)](https://sonarcloud.io/summary/new_code?id=bbvch_Coronan)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=bbvch_Coronan&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=bbvch_Coronan)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=bbvch_Coronan&metric=coverage)](https://sonarcloud.io/summary/new_code?id=bbvch_Coronan)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=bbvch_Coronan&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=bbvch_Coronan)



[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/bbvch/Coronan)


### IMPORTANT NOTE
Co\[ro\]nan was written during the pandemic of the Corona Virus. The [The About Corona Covid-19 API](https://about-corona.net/documentation) used for the first version is no longer available. However with [COVID-19 Statistics API](https://covid-api.com/) an alternative was found. Unfortunately the [COVID-19 Statistics API](https://covid-api.com/api/) does have a different data structure, and retrieving data is much slower, because the API does not support timeline data, i.e. every data for specific date requires a GET. But at least the application works again. And the name didn't have to change.

</details>

# Documentation for Co\[ro\]nan

Co\[ro\]nan is an example C++20 CLI and Qt project using [conan](https://conan.io/) and [CMake](https://cmake.org/).
It reads the latest data of Corona (Covid-19) cases for a country from the [COVID-19 Statistics API](https://covid-api.com/).


_The COVID-19 Statistics API_ provides statistics via REST API from the [Johns Hopkins CSSE](https://github.com/CSSEGISandData/COVID-19).


![Screenshot of the qt application](images/Screenshot-qt.png)


## Table of content

<details>
<summary>Expand contents</summary>

- [Project Features](#project-features)
- [Development](#development)
  - [How to build](#how-to-build)
  - [Source Code Formatting](#source-code-formatting)
  - [CMake options](#cmake-options)
- [Pre-Commit Hooks](#pre-commit-hooks)
- [gitpod](#gitpod)
- [direnv & nix](#direnv--nix)

</details>

## Project Features

This projects is a C++ project template. It includes everything a "Modern" C++ project possibly needs:
* C++ 20 Standard
  * [GCC](https://gcc.gnu.org/) _(>= gcc-12)_
  * [Clang](https://clang.llvm.org/) _(>= clang-13)_
  * Visual Studio 2022

* [conan](https://conan.io/) package Manager

* Dependencies:
  * to install:
    * [Qt6](https://www.qt.io/) _(minimal version required: 6.4)_
  * with conan:
    * [Poco](https://pocoproject.org/) Networking library
    * [RapidJSON](https://rapidjson.org/)
    * [Lyra](https://github.com/bfgroup/Lyra) command line arguments parser
    * [{fmt}](https://github.com/fmtlib/fmt) formatting library _(std::print is C++23 and therefore not used yet)_
    * [date](https://github.com/HowardHinnant/date) date and time library _(std::chrono::year_month_day is not fully supported in older c++20 compilers (gcc 12, 13 and clang 13-16) therefor it is not used yet)_
    * [Catch2](https://github.com/catchorg/Catch2) _(for unittests)__

* Unittests with Coverage using [Catch2](https://github.com/catchorg/Catch2)

* CMake with [CMakePresets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html) _(CMake >= 3.23)_

* CPack packaging:
  * tar gzip archive
  * Debian package
  * [Qt Installer Framework](https://doc.qt.io/qtinstallerframework/)
  * [WIX](https://wixtoolset.org/)

* Build Caching support:
  * [ccache](https://ccache.dev/)
  * [sccache](https://github.com/mozilla/sccache)

* Static Analyzer support:
  * [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
  * [cppcheck](http://cppcheck.sourceforge.net/)
  * [include-what-you-use](https://include-what-you-use.org/)
  * [link-what-you-use](https://cmake.org/cmake/help/latest/prop_tgt/LINK_WHAT_YOU_USE.html)

* Sanitizers support:
  * [Address Sanitizer](https://clang.llvm.org/docs/AddressSanitizer.html)
  * [Leak Sanitizer](https://clang.llvm.org/docs/LeakSanitizer.html)
  * [Undefined Behavior Sanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html)
  * [Thread Sanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html)
  * [Memory Sanitizer](https://clang.llvm.org/docs/MemorySanitizer.html)

* Documentation Generation using
  * [Doxygen](https://www.doxygen.nl/index.html) using the _"doxygen-awesome-sidebar-only"_ theme by
  * [doxygen-awesome-css](https://github.com/jothepro/doxygen-awesome-css) by default

* Code formatting:
  * [clang-format](https://clang.llvm.org/docs/ClangFormat.html) for C++ files
  * [cmake-format](https://pypi.org/project/cmake-format/) for CMake files

* [Pre-commit-hooks](https://github.com/pre-commit/pre-commit-hooks) support

* [Nix](https://nixos.org) environment support

* [gitpod](https://www.gitpod.io/) support

* Continuous integration (CI):
  * GitHub Action

    * Mac OS X
      * 13 _(AppleClang 14)_
      * 14 _(AppleClang 15)_
      * 15 _(AppleClang 15)_

    * Ubuntu 22.04
      * GCC 12
      * Clang 13, 14 & 15

    * Ubuntu 24.04
      * GCC 13 & 14
      * Clang 16, 17 & 18

    * Windows
      * Visual Studio 2022

    * Nix
      * GCC 14
      * Clang 18

    * [Codacy Security Scan](https://github.com/marketplace/actions/codacy-analysis-cli)

    * [CodeQL Static Analysis](https://github.com/github/codeql-action)

    * [Coverity Scan Static Analysis](https://scan.coverity.com/)

    * [Codecov](https://codecov.io) Coverage Reporter

    * [Sonar Cloud Static Analysis](https://www.sonarsource.com/products/sonarcloud/)

  * [AppVeyor](https://www.appveyor.com/)
    * Windows Visual Studio 2019

## Development

To build the project you need python and a recent [conan version](https://conan.io/), a recent version of [CMake](https://cmake.org/) (>= 3.23), a modern C++ compiler (C++20 support) and [Qt6](https://www.qt.io/) with [QtCharts](https://doc.qt.io/qt-6/qtcharts-index.html).

To install all python requirements for documentation generation, build and coverage generation (including conan and cmake) use:

```bash
pip3 install -r py-requirements.txt
```

### How to build

You have the following options to build the project

__Use build script__:

In a linux shell you can build the project with the provided `build.sh` script. E.g. to build in folder `build` execute:

```bash
./build.sh ./build
```

See `./build.sh -h` for more options

__CMake__:

You can also build it yourself using CMake and conan

* __Install dependencies with conan__

  ```bash
  conan install . --build=missing --settings=build_type=Debug
  ```
  Because the conan [cmake_layout](https://docs.conan.io/2/reference/tools/cmake/cmake_layout.html#) and the  [`CMakeDeps`](https://docs.conan.io/2/reference/tools/cmake/cmakedeps.html) generator is used, the necessary cmake files used with `find_packages()` are generated into `build\<build_type>\generators`. `CMAKE_PREFIX_PATH` is adapted accordingly in the root `CMakeLists.txt`.

* __Without CMake Presets__

  ```bash
  cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug
  cmake --build ./build
  ```
* __With CMake Presets__

  ```bash
  cmake -S . --preset=linux-gcc-debug
  cmake --build --preset=gcc-debug
  ```

  or any other [CMakePresets](CMakePresets.json).

### Source Code Formatting

For source code formatting [clang-format](https://clang.llvm.org/docs/ClangFormat.html) for C++ files and [cmake-format](https://pypi.org/project/cmake-format/) for the CMake files are used. Run `format_source_files.sh` to format all C++ and CMake files.

_Note: Delete the build directory before formatting, otherwise all CMake files in the build folder will be formatted as well, what may take a while._

### CMake options

* `DOWNLOAD_QT6`: Download and build Qt6 otherwise use installed. _Default: `OFF`_
* `ENABLE_TESTING`: Build (and run) unittests. _Default: `ON`_
* `ENABLE_BUILD_WITH_TIME_TRACE`: Enable [Clang Time Trace Feature](https://www.snsystems.com/technology/tech-blog/clang-time-trace-feature). _Default: `OFF`_
* `ENABLE_PCH`: Enable [Precompiled Headers](https://en.wikipedia.org/wiki/Precompiled_header). _Default: `OFF`_
* `ENABLE_CACHE`: Enable caching if available, e.g. [ccache](https://ccache.dev/) or [sccache](https://github.com/mozilla/sccache). _Default: `ON`_
* `ENABLE_COVERAGE`: Enable coverage reporting for gcc/clang. _Default: `OFF`_
* `ENABLE_DOXYGEN`: Enable doxygen documentation build ([Doxygen](https://www.doxygen.nl/index.html) must be installed). _Default: `ON` if Doxygen is installed `OFF` otherwise._
* `ENABLE_SANITIZERS`: Enable supported sanitizers. _Default: `OFF`_
    * `ENABLE_SANITIZER_ADDRESS`: Enable [address sanitizer](https://clang.llvm.org/docs/AddressSanitizer.html). _Default: `ON` if supported by the compiler and `ENABLE_SANITIZERS` is `ON` otherwise `OFF`._
    * `ENABLE_SANITIZER_LEAK`: Enable [leak sanitizer](https://clang.llvm.org/docs/LeakSanitizer.html). _Default: `OFF`_
    * `ENABLE_SANITIZER_UNDEFINED_BEHAVIOR`: Enable [undefined behavior sanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html). _Default: `ON` if supported by the compiler and `ENABLE_SANITIZERS` is `ON` otherwise `OFF`._
    * `ENABLE_SANITIZER_THREAD`: Enable [thread sanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html). _Default: `OFF`_
    * `ENABLE_SANITIZER_MEMORY`: Enable [memory sanitizer](https://clang.llvm.org/docs/MemorySanitizer.html). _Default: `OFF`_
* `ENABLE_IPO`: Enable intermodular optimization, aka [Link Time Optimization (LTO)](https://llvm.org/docs/LinkTimeOptimization.html). _Default: `OFF`_
* `ENABLE_CPPCHECK`: Enable static analysis with [cppcheck](http://cppcheck.sourceforge.net/). _Default: `ON` if cppcheck is installed `OFF` otherwise._
* `ENABLE_CLANG_TIDY`: Enable static analysis with [clang-tidy](https://clang.llvm.org/extra/clang-tidy/). _Default: `ON` if clang-tidy is installed `OFF` otherwise._
* `ENABLE_INCLUDE_WHAT_YOU_USE`: Enable static analysis with [include-what-you-use](https://include-what-you-use.org/). _Default: `ON` if include-what-you-use is installed `OFF` otherwise_.
* `ENABLE_LINK_WHAT_YOU_USE` : Enable _link what you use_ cmake built-in static analysis. _Default: `OFF`
* `WARNINGS_AS_ERRORS`: Treat compiler warnings as errors. _Default: `OFF`

## Pre-Commit Hooks

The following [Pre-commit-hooks](https://github.com/pre-commit/pre-commit-hooks) are used to check and format files before committing:

* `check-added-large-files`: Prevent giant files (> 500kB) from being committed.
* `fix-byte-order-marker`: Forbid files which have a UTF-8 byte-order marker
* `check-case-conflict`: Check for files with names that would conflict on a case-insensitive filesystem like MacOS HFS+ or Windows FAT.
* `check-merge-conflict`: Check for files that contain merge conflict strings.
* `check-symlinks`: Checks for symlinks which do not point to anything.
* `check-yaml`: Attempts to load all yaml files to verify syntax.
* `check-json`: Attempts to load all json files to verify syntax.
* `check-toml`: Attempts to load all TOML files to verify syntax.
* `check-executables-have-shebangs`: Checks that non-binary executables have a proper shebang.
* `end-of-file-fixer`: Makes sure files end in a newline and only a newline.
* `mixed-line-ending`: Replaces or checks mixed line ending.
* `trailing-whitespace`: Trims trailing whitespace in markdown
* `clang-format`: Format C++ files using clang-format
* `cmake-format`: Format CMake files using cmake-format
* `yamllint`: Linter for yaml files
* `yamlfmt`: Format yaml files

Please install pre-commit hooks before committing any code.

```bash
pre-commit install -f --hook-type pre-commit
```

To manually check all files run:
```bash
pre-commit run --all-files
```

## gitpod

To start right away without installing anything on your local machine, you can simply use the <img src="https://gitpod.io/button/open-in-gitpod.svg" height="15"> button in the Project State section at the top of this README.

## direnv & nix

If you have [direnv](https://direnv.net/) and [nix](https://nixos.org/) installed everything should be setup to start upon entering the project folder, if `use nix` is not commented out in [.envrc](.envrc). gcc (gcc14) is set as default C and C++ compiler. If you prefer clang (clang_18) change it in [.envrc](.envrc)

You can also use `nix-shell` directly to build when `use nix` is disabled, e.g.:

  ```bash
  nix-shell --command "conan profile detect"
  nix-shell --command "conan install . --build=missing --settings=build_type=Debug"
  nix-shell --command "cmake -S . --preset=linux-debug-ninja
  nix-shell --command "cmake --build --preset=ninja-debug
  ```

When using nix, a new cmake is available and therefore configure and build [CMakePresets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html) can be used.
