dnl $Id$
dnl config.m4 for extension jieba

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(jieba, for jieba support,
Make sure that the comment is aligned:
[  --with-jieba             Include jieba support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(jieba, whether to enable jieba support,
Make sure that the comment is aligned:
[  --enable-jieba           Enable jieba support])

if test "$PHP_JIEBA" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-jieba -> check with-path
  SEARCH_PATH="/usr/local /usr"     # you might want to change this
  SEARCH_FOR="/include/jieba/Jieba.hpp"  # you most likely want to change this
  if test -r $PHP_JIEBA/$SEARCH_FOR; then # path given as parameter
     JIEBA_DIR=$PHP_JIEBA
  else # search default path list
     AC_MSG_CHECKING([for jieba files in default path])
     for i in $SEARCH_PATH ; do
       if test -r $i/$SEARCH_FOR; then
         JIEBA_DIR=$i
         AC_MSG_RESULT(found in $i)
       fi
     done
   fi
  
  if test -z "$JIEBA_DIR"; then
     AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Please reinstall the jieba distribution])
  fi

  dnl # --with-jieba -> add include path
  PHP_ADD_INCLUDE($JIEBA_DIR/include)

  dnl # --with-jieba -> check for lib and symbol presence
  dnl LIBNAME=jieba # you may want to change this
  dnl LIBSYMBOL=jieba # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $JIEBA_DIR/$PHP_LIBDIR, JIEBA_SHARED_LIBADD)
  dnl AC_DEFINE(HAVE_JIEBALIB,1,[ ])
  dnl ],[
  dnl AC_MSG_ERROR([wrong jieba lib version or lib not found])
  dnl ],[
  dnl	-L$JIEBA_DIR/$PHP_LIBDIR -lm
  dnl ])
  
  PHP_SUBST(JIEBA_SHARED_LIBADD)
  PHP_REQUIRE_CXX() 
  PHP_ADD_LIBRARY(stdc++, 1, EXTRA_LDFLAGS)
  PHP_NEW_EXTENSION(jieba, jieba.cpp, $ext_shared)
fi
