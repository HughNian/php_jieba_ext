/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: niansong                                                     |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_JIEBA_H
#define PHP_JIEBA_H

extern zend_module_entry jieba_module_entry;
#define phpext_jieba_ptr &jieba_module_entry

#define PHP_JIEBA_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_JIEBA_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_JIEBA_API __attribute__ ((visibility("default")))
#else
#	define PHP_JIEBA_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#include "Jieba.hpp"
using namespace cppjieba;

PHP_MINIT_FUNCTION(jieba);
PHP_MSHUTDOWN_FUNCTION(jieba);
PHP_RINIT_FUNCTION(jieba);
PHP_RSHUTDOWN_FUNCTION(jieba);
PHP_MINFO_FUNCTION(jieba);

PHP_FUNCTION(jieba_cut);
PHP_FUNCTION(jieba_insert_word);
PHP_FUNCTION(jieba_cut_nhmm);
PHP_FUNCTION(jieba_cut_all);
PHP_FUNCTION(jieba_cut_search);

ZEND_BEGIN_MODULE_GLOBALS(jieba)
    //long  global_value;
    Jieba *jieba_g;
ZEND_END_MODULE_GLOBALS(jieba)

/* In every utility function you add that needs to use variables 
   in php_jieba_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as JIEBA_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define JIEBA_G(v) TSRMG(jieba_globals_id, zend_jieba_globals *, v)
#else
#define JIEBA_G(v) (jieba_globals.v)
#endif

#endif	/* PHP_JIEBA_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
