#!/bin/bash

set -e

SELF_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

find "${SELF_DIR}" -name '*.hpp' -o -name '*.h' -o -name '*.cpp' | xargs clang-format -i -style=file
find "${SELF_DIR}" -name 'CMakeLists.txt' -o -name '*.cmake' | xargs cmake-format -i
