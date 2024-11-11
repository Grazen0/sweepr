{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
  }: let
    forAllSystems = nixpkgs.lib.genAttrs [
      "aarch64-linux"
      "i686-linux"
      "x86_64-linux"
      "aarch64-darwin"
      "x86_64-darwin"
    ];
  in {
    packages = forAllSystems (system: let
      pkgs = nixpkgs.legacyPackages.${system};
    in rec {
      default = sweepr;

      sweepr = pkgs.stdenv.mkDerivation {
        pname = "sweepr";
        version = "0.1.0";

        src = ./.;

        nativeBuildInputs = with pkgs; [cmake];
        buildInputs = with pkgs; [gcc];

        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Release"
        ];

        buildPhase = ''
          cmake . -B build $cmakeFlags
          cmake --build build
        '';

        installPhase = ''
          mkdir -p $out/bin
          cp build/sweepr $out/bin/
        '';

        meta = with pkgs.lib; {
          description = "Funky Minesweeper game for the terminal";
          license = licenses.mit;
        };
      };
    });

    devShells = forAllSystems (system: import ./shell.nix {pkgs = nixpkgs.legacyPackages.${system};});
  };
}
