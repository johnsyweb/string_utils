AC_PREREQ([2.68])
AC_INIT(string_utils, 0.2, paj-github@johnsy.com)
AM_INIT_AUTOMAKE(string_utils, 0.2)
AC_CONFIG_SRCDIR([src/string_utils.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(unittest++, [main])

# This is C++, not C
AC_LANG(C++)

# Checks for header files.
AC_CHECK_HEADER([unittest++/UnitTest++.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT(Makefile src/Makefile)
