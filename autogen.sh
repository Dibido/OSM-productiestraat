#!/bin/sh

echo "Generating Autotools files"

echo "Fixing line endings in configure.ac"
cp configure.ac configure.ac.bak
tr -d '\r' <configure.ac.bak>configure.ac
rm configure.ac.bak

echo "Generating libtoolize files"
libtoolize --force --copy

echo "Generating aclocal files"
aclocal -I ./m4

#autoheader

echo "Generating autoconf files"
autoconf -I ./m4

echo "Generating automake files"
automake --force-missing --copy --add-missing --foreign

echo "Done generating Autotools files"