# conan_project_template
C++ Project Template using conan and CMake

## Description
This is a CMake based C++ project template that uses the [Conan](https://conan.io) C/C++ Package Manager to install/build the dependencies used. It can be used as starting point for C++ projects and includes:
* A Dummy [google test](http://code.google.com/p/googletest/) unit test
* A Dummy BDD Style (Gherkin) feature test using [Cucumber](http://cukes.info/) and [Cucumber-cpp](https://github.com/cucumber/cucumber-cpp)
* CMake targets to build, run tests and measure metrics.


## Dependencies
---------------
Building the Project requires
* a recent Version of [CMake](http://www.cmake.org/) (3.2.x). See CMake documentation for more information about building using CMake.
* [Conan](https://conan.io)
* a recent C++ compiler supporting C++11 (tested on gcc 4.8, 4.9, 5.4, 6.2, clang 3.5)

The external dependencies are handles with Conan C/C++ Package Manager.

## Howto
--------------
### Create a build folder, install dependencies and configure the project
    $ mkdir build && pushd build
    $ conan install ..
    $ cmake ..
    $ popd

```conan install``` installs all dependencies and generates the files conanbuildinfo.txt and conanbuildinfo.cmake with all the paths and variables that you need to link with your dependencies.
Please refer to the [Conan docu](http://docs.conan.io/en/latest/manage_deps/conanfile_txt.html#installing-dependencies) for more informations.

### Build the project using CMake
    $ cmake --build build --target all --config Debug

### Run tests
#### Unittests
    $ cmake --build build --target run_unittests

#### Featuretests
##### Linux
    $ cmake --build build --target run_feature_test
    $ cmake --build build --target run_feature_test
    $ cmake --build build --target run_wip_features

##### Windows
Start wireserver:
    >cmake --build build --target start_wireserver

and in folder tests/feature run cucumber:
    >cucumber features

or
    >cucumber -p wip features
