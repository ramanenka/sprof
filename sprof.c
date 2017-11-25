/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_sprof.h"

/* If you declare any globals in php_sprof.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(sprof)
*/

/* True global resources - no need for thread safety here */
static int le_sprof;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("sprof.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_sprof_globals, sprof_globals)
    STD_PHP_INI_ENTRY("sprof.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_sprof_globals, sprof_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_sprof_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_sprof_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "sprof", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

PHP_FUNCTION(sprof_start)
{
	puts("sprof started");
}

PHP_FUNCTION(sprof_stop)
{
	RETURN_STRING("sprof stop get");
}

/* {{{ php_sprof_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_sprof_init_globals(zend_sprof_globals *sprof_globals)
{
	sprof_globals->global_value = 0;
	sprof_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sprof)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sprof)
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
PHP_RINIT_FUNCTION(sprof)
{
#if defined(COMPILE_DL_SPROF) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(sprof)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(sprof)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "sprof support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ sprof_functions[]
 *
 * Every user visible function must have an entry in sprof_functions[].
 */
const zend_function_entry sprof_functions[] = {
	PHP_FE(confirm_sprof_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(sprof_start, NULL)
	PHP_FE(sprof_stop, NULL)
	PHP_FE_END	/* Must be the last line in sprof_functions[] */
};
/* }}} */

/* {{{ sprof_module_entry
 */
zend_module_entry sprof_module_entry = {
	STANDARD_MODULE_HEADER,
	"sprof",
	sprof_functions,
	PHP_MINIT(sprof),
	PHP_MSHUTDOWN(sprof),
	PHP_RINIT(sprof),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(sprof),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(sprof),
	PHP_SPROF_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SPROF
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(sprof)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
