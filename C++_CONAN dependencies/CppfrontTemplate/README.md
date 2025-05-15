# Cppfront project template

This is a template repository for C++ projects that use `cppfront`, `CMake`, `conan` and `fmt` library as usage example.

[![.github/workflows/Build.yml](https://github.com/SavenkovIgor/cpp-template/actions/workflows/Build.yml/badge.svg)](https://github.com/SavenkovIgor/cpp-template/actions/workflows/Build.yml)

## Project structure

```bash
├── .github/workflows/Build.yml # Github actions build script
├── src/main.cpp2               # Main cpp2 file
├── CMakeLists.txt              # Cmake file
├── conanfile.py                # Conan file with cppfront dependency
└── project.py                  # Main project script
```

## Getting Started

To use this template, click the "Use this template" button at the top of the repository.

## Dependencies

- Conan2
- Cmake
- Cppfront
- fmt (9.0.0) - just for example. You can remove it from `conanfile.py` and `main.cpp2` if you don't need it.

## :hammer_and_wrench: Build

To run this project you can use a script

```bash
./project.py --install --build --run
```

or you can run commands from script manually:

```bash
# Install dependencies
conan install -of ./conanfiles -pr:h=./conan_profile/default -pr:b=./conan_profile/default --build=missing ./

# Build project
conan build -of ./conanfiles ./

# Run resulting binary
./conanfiles/build/Release/cpp_template
```

## Contributing

If you would like to contribute to this project, please fork the repository and submit a pull request.
