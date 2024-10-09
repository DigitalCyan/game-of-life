{
  description = "A dev enviornment for my game of life clone";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/24.05";
  };

  outputs = { self, nixpkgs, ... }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          pkg-config
          SDL2
          SDL2_ttf
        ];
      };

      packages.${system}.default = pkgs.stdenv.mkDerivation {
        name = "game-of-life";
        src = ./.;

        nativeBuildInputs = with pkgs; [
          pkg-config
          gcc
          SDL2
          SDL2_ttf
        ];

        buildPhase = ''
          gcc src/*.c -I src/include -o game-of-life $(pkg-config --cflags --libs sdl2 SDL2_ttf)
        '';

        installPhase = ''
          mkdir -p $out/bin
          cp game-of-life $out/bin
          cp -r assets $out/bin
        '';
      };
    };
}
