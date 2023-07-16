{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = [
    pkgs.clang-tools_16
    pkgs.cmake
    pkgs.cppcheck
    pkgs.gcc
    pkgs.include-what-you-use
  ];
  nativeBuildInputs = [
    pkgs.doctest
    pkgs.fmt
  ];
}
