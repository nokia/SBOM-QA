#!/bin/bash

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    if which pyenv > /dev/null; then
        eval "$(pyenv init -)"
    fi
    pyenv activate conan
fi
mkdir build && pushd build
conan install .. --build missing -s compiler=${compiler} -s compiler.version=${COMPILER_VERSION}
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
popd

cmake --build build --target all --config ${BUILD_TYPE}
cmake --build build --target run_feature_test --config ${BUILD_TYPE}
if [ "${COVERAGE}" == '1' ] ; then cmake --build build --target coverage --config ${BUILD_TYPE} ; fi
