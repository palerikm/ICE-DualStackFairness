#!/bin/sh
mkdir m4 build-aux

aclocal
autoconf
automake --add-missing --force-missing


##autoreconf --install