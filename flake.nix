{
  description = "A dev enviornment for my game of life clone";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
  };

  outputs = { self, nixpkgs, ... }: 
  let 
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in 
  {
    devShells.${system}.default = pkgs.mkShell {
      inputsFrom = with pkgs; [
        gcc
        cmake
      ];
    };
  };
}