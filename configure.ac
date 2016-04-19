AC_PREREQ([2.63])
AC_INIT([module_vtun], [4.0.0], [florian.schmidt@dlr.de])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

m4_ifdef([RMPM_ENV], [RMPM_ENV])
m4_ifdef([RMPM_ARCH], [RMPM_ARCH])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_INSTALL
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_PROG_LIBTOOL
AC_PROG_LN_S
m4_ifdef([PKG_PROG_PKG_CONFIG], [PKG_PROG_PKG_CONFIG])
m4_ifdef([PKG_INSTALLDIR], [PKG_INSTALLDIR], [pkgconfigdir='${libdir}/pkgconfig' AC_SUBST([pkgconfigdir])])

PKG_CHECK_MODULES([ROBOTKERNEL], [robotkernel], [], [
                    RMPM_CHECK_MODULES([ROBOTKERNEL], [robotkernel.robotkernel-4.0])
                   ])

PKG_CHECK_MODULES([LIBSTRING_UTIL], [libstring_util], [], [RMPM_CHECK_MODULES([LIBSTRING_UTIL], [software.libstring_util])])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h termios.h sys/syscall.h process.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strdup pthread_setname_np gettid])

# Checks for library functions.
AC_CHECK_LIB(dl, dlopen, DL_LIBS="-ldl", DL_LIBS=)
AC_SUBST(DL_LIBS)

AC_CONFIG_FILES([
	Makefile
	src/Makefile
        module_vtun.pc
	share/ln/module_vtun.inc.lnc
])
AC_CONFIG_FILES([module_vtun.pt], [cp module_vtun.pt ${ac_abs_top_srcdir}])

AC_OUTPUT

