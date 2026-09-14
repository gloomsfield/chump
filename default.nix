{ pkgs ? import <nixpkgs> {}, ... }:
pkgs.stdenv.mkDerivation {
	name = "chump";
	pname = "chump";

	outputs = [ "out" "dev" ];

	src = ./src;

	buildPhase = ''
		mkdir -p $out/lib
		gcc -c $src/chump.c -o $out/lib/libchump.a
	'';

	installPhase = ''
		mkdir -p $dev/include
		cp $src/chump.h $dev/include
	'';	
}
