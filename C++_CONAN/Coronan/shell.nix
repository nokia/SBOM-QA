with (import ./sources.nix);
with nixpkgs;
let
  gcc = gcc14;
  clang = clang_18;
  cmake_331 = (import ./cmake.nix).cmake;

  gcovr = python3.withPackages(ps: [
    ps.gcovr
  ]);

in stdenvNoCC.mkDerivation {
  name = "shell";
  hardeningDisable = [ "all" ];
  LOCALE_ARCHIVE_2_27 = "${glibcLocales}/lib/locale/locale-archive";
  buildInputs = [
    gcc
    cmake_331
    cmake
    glibcLocales
    ninja
    clang
    binutils
    clang-tools
    include-what-you-use
    cppcheck
    dpkg
    ccache
    libGLU
    libGL
    qt6.qtbase
    qt6.qtcharts
    lcov
    gcovr
    perl
    doxygen
    graphviz
    pkg-config
    pre-commit
    python3
    cmake-format
    python3Packages.setuptools
    python3Packages.pip
    python3Packages.virtualenv
  ];

  shellHook = ''
    pre-commit install -f --hook-type pre-commit
    virtualenv venv
    source venv/bin/activate
    python3 -m pip install -r py-requirements.txt
  '';
}
