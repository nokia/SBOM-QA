#!/bin/bash

set -e

BUILD_DIR="build"
CMAKE=cmake
COVERAGE=false
COVERAGE_OUT=""
BUILD_TYPE=Debug
BUILD_TARGET="--target all"
CXX_COMPILER="g++"
C_COMPILER="gcc"
COMPILER_VERSION="$(g++ -dumpversion)"
CLEAR_BUILD=false
CONAN=conan


print_usage() {
cat << EOM
Usage: build.sh [options] [build_dir]
  Available options:
    -h|--help          Print this help
    --cov=output_dir   Build debug version with coverage enabled.
    -c|--clear         Delete <build_dir> if it exists
    -r|--release       Build release version.
                       Note: is ignored when --cov is set
    --cmake=path       Path to cmake (default is the system cmake)
    --conan=path       Path to conan (default is the system conan)
    -i                 Install
    -p                 Create package
    --clang=version    Build with clang (ver: version).
    --gnu=version      Build with gnu compiler (ver: version).
    build_dir:         Directory to build in (default: build)
EOM
}

if [ $# -ge 1 ]; then
    while [[ $# -gt 0 ]] ; do
        key="$1"

        case "$key" in
        --cov=*)
            COVERAGE=true
            COVERAGE_OUT="${key#*=}"
            shift # past argument=value
            ;;
        -r|--release)
            BUILD_TYPE=Release
            shift # past argument
            ;;
        -c|--clear)
            CLEAR_BUILD=true
            shift # past argument
            ;;
        --clang=*)
            CXX_COMPILER="clang++"
            C_COMPILER="clang"
            COMPILER_VERSION="${key#*=}"
            shift # past argument=value
            ;;
        --gnu=*)
            CXX_COMPILER="g++"
            C_COMPILER="gcc"
            COMPILER_VERSION="${key#*=}"
            shift # past argument=value
            ;;
        --cmake=*)
            CMAKE="${key#*=}"
            shift # past argument=value
            ;;
        --conan=*)
            CONAN="${key#*=}"
            shift # past argument=value
            ;;
        -h|--help)
            print_usage
            exit 1
            ;;
        -i)
            BUILD_TARGET="--target install"
            shift # past argument
            ;;
        -p)
            BUILD_TARGET="--target package"
            shift # past argument
            ;;
        *)
            BUILD_DIR=$key
            shift # past argument=value
            ;;
        esac
    done
fi

export CXX=${CXX_COMPILER}-${COMPILER_VERSION}
export CC=${C_COMPILER}-${COMPILER_VERSION}

if [ "${COVERAGE}" = true -a -z "${COVERAGE_OUT}" ] ; then
    echo "Error: Please specify the coverage output_file."
    echo ""
    print_usage
    exit 1
fi

if [[ $(command -v ninja) ]] ; then
    echo "Ninja found. Use it."
    CMAKE_GENERATOR="-G Ninja"
fi

if [[ "${CLEAR_BUILD}" = true ]] ; then
    rm -rf "${BUILD_DIR}"
fi

echo "run conan install"
"${CONAN}" install . --build=missing --settings=build_type="${BUILD_TYPE}" --settings=compiler="${C_COMPILER}" --settings=compiler.version="${COMPILER_VERSION}" --settings=compiler.cppstd=17

if [[ "${COVERAGE}" = true ]] ; then
    "${CMAKE}" -S . -B "${BUILD_DIR}" "${CMAKE_GENERATOR}" -DENABLE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
else
    "${CMAKE}" -S . -B "${BUILD_DIR}" "${CMAKE_GENERATOR}" -DENABLE_COVERAGE=OFF -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"
fi

num_threads=$(grep -c '^processor' /proc/cpuinfo)
"${CMAKE}" --build "${BUILD_DIR}" "${BUILD_TARGET}" --parallel "${num_threads}"

if [[ "${COVERAGE}" = true ]] ; then
    echo "generate coverage dat to ${COVERAGE_OUT}"
    lcov --no-external --capture --directory . --output-file "/tmp/${COVERAGE_OUT}.info"
    lcov --remove "/tmp/${COVERAGE_OUT}.info" '/usr/*' --output-file "/tmp/${COVERAGE_OUT}.info"
    genhtml --ignore-errors source "/tmp/${COVERAGE_OUT}.info" --legend --output-directory="${COVERAGE_OUT}"
fi

exit 0
