dnl Process this file with autoconf to produce a configure script.

AC_INIT(indicator-keylock, 3.1.0)
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

AM_PROG_CC_C_O
AC_STDC_HEADERS
AC_PROG_INSTALL

AC_PROG_INTLTOOL([0.23])

GETTEXT_PACKAGE="$PACKAGE_NAME"
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE([GETTEXT_PACKAGE], [], ["Define to the name of this package used by gettext"])
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE")

ALL_LINGUAS=""
AM_GLIB_GNU_GETTEXT

pkglocaledir='${prefix}/${DATADIRNAME}/locale'
AC_SUBST(pkglocaledir)

PKG_CHECK_MODULES(glib, [glib-2.0 >= 2.24.0])
PKG_CHECK_MODULES(gtk, [gtk+-3.0 >= 3.2.0])
PKG_CHECK_MODULES(appindicator, [appindicator3-0.1 >= 0.4.1])
PKG_CHECK_MODULES(unique, [unique-3.0 >= 3.0.0])
PKG_CHECK_MODULES(libnotify, [libnotify >= 0.7.4])
PKG_CHECK_MODULES(x11, [x11 >= 1.0])

PACKAGE_CFLAGS="$glib_CFLAGS $gtk_CFLAGS $appindicator_CFLAGS $unique_CFLAGS $libnotify_CFLAGS $x11_CFLAGS"
PACKAGE_LIBS="$glib_LIBS $gtk_LIBS $appindicator_LIBS $unique_LIBS $libnotify_LIBS $x11_LIBS"
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)

GLIB_GSETTINGS

AM_CONFIG_HEADER(config.h)

AC_OUTPUT([
Makefile
src/Makefile
pixmaps/Makefile
pixmaps/hicolor/Makefile
pixmaps/elementary/Makefile
pixmaps/Humanity/Makefile
pixmaps/Humanity-Dark/Makefile
pixmaps/ubuntu-mono-dark/Makefile
pixmaps/ubuntu-mono-light/Makefile
po/Makefile.in
])
