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
   | Author:niansong                                                      |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_jieba.hpp"
#include "jieba_logo.hpp"

using namespace std;

//If you declare any globals in php_jieba.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(jieba)

/* True global resources - no need for thread safety here */
static int le_jieba;
static Jieba jieba("/usr/local/dict/jieba.dict.utf8", 
		    "/usr/local/dict/hmm_model.utf8", 
		    "/usr/local/dict/user.dict.utf8");

/* {{{ jieba_functions[]
 *
 * Every user visible function must have an entry in jieba_functions[].
 */
const zend_function_entry jieba_functions[] = {
	PHP_FE(jieba_cut, NULL)
        PHP_FE(jieba_insert_word, NULL)
	PHP_FE(jieba_cut_nhmm, NULL)
	PHP_FE(jieba_cut_all, NULL)
	PHP_FE(jieba_cut_search, NULL)
	PHP_FE_END
};
/* }}} */

/* {{{ jieba_module_entry
 */
zend_module_entry jieba_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"jieba",
	jieba_functions,
	PHP_MINIT(jieba),
	PHP_MSHUTDOWN(jieba),
	PHP_RINIT(jieba),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(jieba),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(jieba),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_JIEBA_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_JIEBA
ZEND_GET_MODULE(jieba)
#endif

	/* {{{ PHP_INI
	 */
	/* Remove comments and fill if you need to have entries in php.ini
	   PHP_INI_BEGIN()
	   STD_PHP_INI_ENTRY("jieba.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_jieba_globals, jieba_globals)
	   STD_PHP_INI_ENTRY("jieba.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_jieba_globals, jieba_globals)
	   PHP_INI_END()
	 */
	/* }}} */

/* {{{ php_jieba_init_globals */
// Uncomment this function if you have INI entries
static void php_jieba_init_globals(zend_jieba_globals *jieba_globals)
{
    //jieba_globals->jieba = &jieba;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION*/
PHP_MINIT_FUNCTION(jieba)
{
    ZEND_INIT_MODULE_GLOBALS(jieba,php_jieba_init_globals,NULL);
    //REGISTER_INI_ENTRIES();
    JIEBA_G(jieba_g) = &jieba;
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(jieba)
{
    /* uncomment this line if you have INI entries
      UNREGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(jieba)
{
    JIEBA_G(jieba_g) = &jieba;
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(jieba)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(jieba)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "jieba support", JIEBA_LOGO_IMG"enabled");
    php_info_print_table_row(2, "Version", JIEBA_VERSION);
    php_info_print_table_row(2, "Author", JIEBA_EXT_AUTHOR);
    php_info_print_table_end();
}
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_jieba_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(jieba_cut)
{
    char *arg = NULL;
    int arg_len, len;
    char *strg;
    int arg_count = ZEND_NUM_ARGS();
    int tag;   
    Jieba *jieba_obj;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &arg, &arg_len, &tag) == FAILURE) {
        return;
    }

    vector<string> words;
    string result;
	
    jieba_obj = JIEBA_G(jieba_g);	
    jieba_obj->Cut(arg, words, true);

    if(tag == 1){
	jieba_obj->Cut(arg, words, true);
    } else if(tag == 2) {
	jieba_obj->Cut(arg, words, false);
    } else if(tag == 3){
	jieba_obj->CutAll(arg, words);
    } else if(tag == 4){
	jieba_obj->CutForSearch(arg, words);
    }

    result = limonp::Join(words.begin(), words.end(), "/");	    
    RETURN_STRINGL(result.c_str(), result.length(), 1);

}
/* }}} */

/* 
The previous line is meant for vim and emacs, so it can correctly fold and 
unfold functions in source code. See the corresponding marks just before 
function definition, where the functions purpose is also documented. Please 
follow this convention for the convenience of others editing your code.
*/

//cut without hmm
PHP_FUNCTION(jieba_cut_nhmm)
{
    int argc = ZEND_NUM_ARGS();
    char *arg = NULL;
    int arg_len;    
    Jieba *jieba_obj;

    if (zend_parse_parameters(argc TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        return;
    }
    
    vector<string> words;
    string result;
	
    jieba_obj = JIEBA_G(jieba_g);	
    jieba_obj->Cut(arg, words, false);	
	
    result = limonp::Join(words.begin(), words.end(), "/");	    
    RETURN_STRINGL(result.c_str(), result.length(), 1);
}

//cut all
PHP_FUNCTION(jieba_cut_all)
{
    int argc = ZEND_NUM_ARGS();
    char *arg = NULL;
    int arg_len;    
    Jieba *jieba_obj;

    if (zend_parse_parameters(argc TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        return;
    }
    
    vector<string> words;
    string result;
	
    jieba_obj = JIEBA_G(jieba_g);	
    jieba_obj->CutAll(arg, words);	
	
    result = limonp::Join(words.begin(), words.end(), "/");	    
    RETURN_STRINGL(result.c_str(), result.length(), 1);
}

//cut for search
PHP_FUNCTION(jieba_cut_search)
{
    int argc = ZEND_NUM_ARGS();
    char *arg = NULL;
    int arg_len;    
    Jieba *jieba_obj;

    if (zend_parse_parameters(argc TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        return;
    }
    
    vector<string> words;
    string result;
	
    jieba_obj = JIEBA_G(jieba_g);	
    jieba_obj->CutForSearch(arg, words);	
	
    result = limonp::Join(words.begin(), words.end(), "/");	    
    RETURN_STRINGL(result.c_str(), result.length(), 1);
}


//插入新词
PHP_FUNCTION(jieba_insert_word)
{
    int argc = ZEND_NUM_ARGS();
    char* arg = NULL;
    int arg_len;    
    
    if (zend_parse_parameters(argc TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        return;
    }
    
    JIEBA_G(jieba_g)->InsertUserWord(arg);
	
    RETURN_TRUE;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
