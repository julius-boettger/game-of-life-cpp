{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    systems.url = "github:nix-systems/default"; # can run on all systems
  };

  outputs = { self, nixpkgs, systems, ... }:
  let
    eachSystem = fn: nixpkgs.lib.genAttrs (import systems) (system: fn system (import nixpkgs {
      inherit system;
    }));
  in
  {
    packages = eachSystem (system: pkgs: rec {
      default = game-of-life;
      game-of-life = pkgs.stdenv.mkDerivation {
        pname = "game-of-life";
        version = "0.1";
        src = ./.;

        nativeBuildInputs = with pkgs; [ meson ninja pkg-config ];
              buildInputs = with pkgs; [ ftxui ];

        meta = with pkgs.lib; {
          homepage = "https://github.com/julius-boettger/game-of-life-cpp";
          license = licenses.gpl3;
          platforms = platforms.all;
        };
      };
    });

    devShells = eachSystem (system: pkgs: {
      default = pkgs.mkShell {
        inherit (self.packages.${system}.default) nativeBuildInputs buildInputs;
      };
    });
  };
}