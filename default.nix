{ pkgs ? import <nixpkgs> {} }:
pkgs.stdenv.mkDerivation {
	name = "chump";

	outputs = [ "out" ];

	src = ./src;

	buildPhase = ''
		mkdir -p build
		gcc -c $src/chump.c -o build/chump.o
	'';

	installPhase = ''
		mkdir -p $out/lib
		cp build/chump.o $out/lib

		mkdir -p $out/include
		cp -r $src/chump.h $out/include
	'';
}
