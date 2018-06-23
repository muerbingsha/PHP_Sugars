
dnl $Id$
dnl config.m4 for extension zdeng

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:






dnl [Shark] 要include头，第一步打开这个，第二步打开PHP_ADD_INCLUDE
dnl --with-libName 是加载其它库

PHP_ARG_WITH(zdeng, for zdeng support,
Make sure that the comment is aligned:
[  --with-zdeng             Include zdeng support])





dnl [Shark] 打开功能，PHP_ARG_ENABLE(feature, help-string, [./configure --help], $PHP_ default value；是否是拓展名，一般为0）
dnl feature取名最好是如elf-debug形式，这样以$PHP_ELF_DEBUG获取是否设置

PHP_ARG_ENABLE(zdeng, whether to enable zdeng support,
Make sure that the comment is aligned:
[  --enable-zdeng           Enable zdeng support])










if test "$PHP_ZDENG" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-zdeng -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/zdeng.h"  # you most likely want to change this
  dnl if test -r $PHP_ZDENG/$SEARCH_FOR; then # path given as parameter
  dnl   ZDENG_DIR=$PHP_ZDENG
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for zdeng files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ZDENG_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ZDENG_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the zdeng distribution])
  dnl fi




  //加载头文件，需要开启PHP_ARG_WOTH
  //include是自动生成的文件夹，来放头文件
  dnl # --with-zdeng -> add include path
  PHP_ADD_INCLUDE($ZDENG_DIR/include)








  dnl # --with-zdeng -> check for lib and symbol presence
  dnl LIBNAME=zdeng # you may want to change this
  dnl LIBSYMBOL=zdeng # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ZDENG_DIR/$PHP_LIBDIR, ZDENG_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ZDENGLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong zdeng lib version or lib not found])
  dnl ],[
  dnl   -L$ZDENG_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ZDENG_SHARED_LIBADD)









  dnl [Shark] 等号两边不能有空格！细节问题，不然模块无法编译
  dnl 要编译的c文件
  zdeng_src="zdeng.c \
	z_websocket.c \
	src/core/array.c \
	src/core/base.c"
  PHP_NEW_EXTENSION(zdeng, $zdeng_src, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
