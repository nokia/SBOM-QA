# A C++ docker base project
This docker image will serve as your base c++ project structure.
It uses cmake with the conan package manager, all your compilation and test will be run inside a docker image base on GCC 9.3.0  

## Registry

https://bintray.com/conan/conan-center

## Included Libraries

- boost: https://www.boost.org/
- poco: https://pocoproject.org
- json: https://github.com/nlohmann/json
- fmt: https://github.com/fmtlib/fmt
- zlib: https://www.zlib.net/
- asio: https://think-async.com/Asio
- catch2: https://github.com/catchorg/Catch2
- sqlite3: https://www.sqlite.org

- crow: https://github.com/ipkn/crow
- cxxopts: https://github.com/jarro2783/cxxopts
- spdlog: https://github.com/gabime/spdlog


## How to run
Run using docker or docker-compose, also refer to `entrypoint.sh` for available script.
```bash
docker-compose up 
```

```bash
docker build -t cppimage .
docker run -it -v "$PWD":"/usr/project" cppimage bash
```

```bash
docker run -v "$PWD":"/usr/project" cppimage build
conan install ..  -s build_type=Release --build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
``` 


