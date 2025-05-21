#!/bin/bash
set -e

# Define help message
show_help() {
  echo """
  Commands
  ---------------------------------------------------------
  bash          : run bash
  eval          : eval shell command
  install       : install conan dependancies 
  build         : build the app 
  run           : run the application 
  test          : run test 
  """
}

build(){
    mkdir -p build && cd build
    cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    cmake --build .
}

case "$1" in

  bash )
    bash
  ;;

  eval )
    eval "${@:2}"
  ;;

  install )
    mkdir -p build && cd build
    conan install ..
  ;;

  build )
    build "${@:2}"
  ;;

  run )
    ./build/bin/cli
  ;;

  test )
    ./build/bin/tests
  ;;

  * )
    show_help
  ;;

esac