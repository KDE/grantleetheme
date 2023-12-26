#! /bin/sh
$XGETTEXT `find . -name '*.cpp' -o -name '*.h'` -o $podir/libgrantleetheme6.pot
rm -f rc.cpp
