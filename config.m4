dnl $Id$
dnl config.m4 for extension sprof

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(sprof, for sprof support,
dnl Make sure that the comment is aligned:
dnl [  --with-sprof             Include sprof support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(sprof, whether to enable sprof support,
dnl Make sure that the comment is aligned:
[  --enable-sprof          Enable sprof support])

if test "$PHP_SPROF" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-sprof -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/sprof.h"  # you most likely want to change this
  dnl if test -r $PHP_SPROF/$SEARCH_FOR; then # path given as parameter
  dnl   SPROF_DIR=$PHP_SPROF
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for sprof files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SPROF_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SPROF_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the sprof distribution])
  dnl fi

  dnl # --with-sprof -> add include path
  dnl PHP_ADD_INCLUDE($SPROF_DIR/include)

  dnl # --with-sprof -> check for lib and symbol presence
  dnl LIBNAME=sprof # you may want to change this
  dnl LIBSYMBOL=sprof # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SPROF_DIR/$PHP_LIBDIR, SPROF_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SPROFLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong sprof lib version or lib not found])
  dnl ],[
  dnl   -L$SPROF_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(SPROF_SHARED_LIBADD)

  PHP_NEW_EXTENSION(sprof, sprof.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
