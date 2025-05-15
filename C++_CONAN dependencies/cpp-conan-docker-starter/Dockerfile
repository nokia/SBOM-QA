FROM gcc:9.3.0

RUN apt-get update; \
	apt-get install -y --no-install-recommends \
    python3-dev \
    python3-setuptools \
    python3-pip

# Install CMake 3.12
RUN wget -q https://cmake.org/files/v3.12/cmake-3.12.0.tar.gz -O- \
    | tar -C /tmp -xz && cd /tmp/cmake-3.12.0/ && ./bootstrap && \
    make && make install && cd && rm -rf /tmp/cmake-3.12.0

RUN pip3 install wheel
RUN pip3 install conan

RUN mkdir -p /root/.conan/profiles 
COPY profiles/default /root/.conan/profiles/default

RUN mkdir -p /usr/project/build
WORKDIR /usr/project
COPY conanfile.txt ./

WORKDIR /usr/project/build
RUN conan install ..  -s build_type=Release --build

COPY . /usr/project
RUN cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
RUN cmake --build .
WORKDIR /usr/project

EXPOSE 8080 8181 5000 3000
ENTRYPOINT ["./entrypoint.sh"]
CMD ["bash"]