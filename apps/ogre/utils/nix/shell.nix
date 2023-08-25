################################################################################
# License: The Unlicense (https://unlicense.org)
# vim:et:ts=2
################################################################################
{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = [
    pkgs.cmake
  ];
  nativeBuildInputs = [
    pkgs.doctest
    pkgs.fmt
  ];
}
