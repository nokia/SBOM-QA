with builtins;
let lock = fromTOML (readFile ./nix-lock.toml);
in rec {
  nixpkgs = import (fetchTarball {
    name = "nixpkgs";
    url = "https://github.com/nixos/nixpkgs/tarball/${lock.nixpkgs.rev}";
    sha256 = "${lock.nixpkgs.sha256}";
  }) {
    config = { };
    overlays = [ ];
  };
}
