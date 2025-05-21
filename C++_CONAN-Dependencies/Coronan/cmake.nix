with builtins;
with (import ./sources.nix);

let
  lock = fromTOML (readFile ./nix-lock.toml);
  pkgs = nixpkgs;
in {
  cmake = pkgs.gcc10Stdenv.mkDerivation {
    pname = "cmake";
    version = "${lock.cmake.rev}";

    src = fetchurl {
      url =
        "https://github.com/Kitware/CMake/releases/download/v${lock.cmake.rev}/cmake-${lock.cmake.rev}.tar.gz";
      sha256 = "${lock.cmake.sha256}";
    };

    buildInputs = [ pkgs.cmake pkgs.openssl pkgs.libGL pkgs.libGLU ];
    configureFlags = [ ];
    doCheck = false;

  };
}
