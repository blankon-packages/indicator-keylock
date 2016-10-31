#!/bin/bash

PKG_CONFIG="pkg-config"
LIBTOOLIZE="libtoolize"
INTLTOOLIZE="intltoolize"
GLIB_GETTEXTIZE="glib-gettextize"
ACLOCAL="aclocal"
AUTOCONF="autoconf"
AUTOHEADER="autoheader"
AUTOMAKE="automake"

if grep -q "^PKG_CHECK_MODULES" configure.ac ; then
	$PKG_CONFIG --version &>/dev/null
	if [ $? -ne 0 ]; then
		echo "ERROR: $PKG_CONFIG needed, but not found."
		exit 1
	fi
fi

if grep -q "^A[CM]_PROG_LIBTOOL" configure.ac || grep -q "^LT_INIT" configure.ac ; then
	$LIBTOOLIZE --force --copy --install
	EXITCODE=$?
	if [ $EXITCODE -ne 0 ]; then
		echo "ERROR: $LIBTOOLIZE failed."
		exit $EXITCODE
	fi
fi

if grep -q "^AM_GLIB_GNU_GETTEXT" configure.ac ; then
	$GLIB_GETTEXTIZE --copy --force
	EXITCODE=$?
	if [ $EXITCODE -ne 0 ]; then
		echo "ERROR: $GETTEXTIZE failed."
		exit $EXITCODE
	fi
fi

if grep -q "^AC_PROG_INTLTOOL" configure.ac ; then
	$INTLTOOLIZE --copy --force --automake
	EXITCODE=$?
	if [ $EXITCODE -ne 0 ]; then
		echo "ERROR: $INTLTOOLIZE failed."
		exit $EXITCODE
	fi
fi

$ACLOCAL --force
EXITCODE=$?
if [ $EXITCODE -ne 0 ]; then
	echo "ERROR: $ACLOCAL failed."
	exit $EXITCODE
fi

$AUTOCONF --force
EXITCODE=$?
if [ $EXITCODE -ne 0 ]; then
	echo "ERROR: $AUTOCONF failed."
	exit $EXITCODE
fi

if grep -q "^A[CM]_CONFIG_HEADER" configure.ac ; then
	$AUTOHEADER --force
	EXITCODE=$?
	if [ $EXITCODE -ne 0 ]; then
		echo "ERROR: $AUTOHEADER failed."
		exit $EXITCODE
	fi
fi

$AUTOMAKE --add-missing --copy --force-missing
EXITCODE=$?
if [ $EXITCODE -ne 0 ]; then
	echo "ERROR: $AUTOMAKE failed."
	exit $EXITCODE
fi

./configure "$@"

echo "Now run \"make\"."
