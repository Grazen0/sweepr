{pkgs ? import <nixpkgs> {}}:
pkgs.stdenv.mkDerivation {
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
    homepage = "https://github.com/Grazen0/sweepr";
    license = licenses.mit;
  };
}
