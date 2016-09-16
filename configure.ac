AC_PREREQ([2.63])
AC_INIT(
	[module_vtun],
	m4_esyscmd_s([cat project.properties | grep VERSION    | cut -d'=' -f2 | xargs printf "%s"]),
	m4_esyscmd_s([cat project.properties | grep MAINTAINER | cut -d'=' -f2 | xargs printf "%s"]))
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# load env-file with each make invocation
if test -n "$SOURCE_ENV"; then
   echo "loading $SOURCE_ENV"
   source $SOURCE_ENV
fi

# Checks for programs.
AM_PROG_AR
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_LN_S
AC_PROG_MAKE_SET

if test -z "$MAKE"; then
   MAKE=make
fi
# expand path with each make invocation
if test -n "$TOOLCHAIN"; then
   MAKE="$MAKE PATH=$TOOLCHAIN:$PATH"
   PATH=$TOOLCHAIN:$PATH
fi
# load env-file with each make invocation
if test -n "$SOURCE_ENV"; then
   echo "loading $SOURCE_ENV"
   source $SOURCE_ENV
   MAKE="source $SOURCE_ENV; $MAKE"
fi
if test -n "$MAKE"; then
   SET_MAKE="MAKE := $MAKE"
fi
AC_SUBST(SET_MAKE)

# setup rmpm
RMPM_ARCH
m4_esyscmd([scripts/m4_deps.py])
RM_FIND_LN_FROM_ENV

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h termios.h sys/syscall.h process.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strdup pthread_setname_np gettid])

# Checks for library functions.
AC_CHECK_LIB(dl, dlopen, DL_LIBS="-ldl", DL_LIBS=)
AC_SUBST(DL_LIBS)

INSTALL_DATA="${INSTALL} -p -m 644"

AC_CONFIG_FILES([
	Makefile
	src/main/cpp/Makefile
        module_vtun.pc
	share/ln/module_vtun.inc.lnc
])


AC_OUTPUT

