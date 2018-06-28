
/* 1 创建 zend_zdeng_globals 结构体 */
/* ZDENG_G()获取该线程池/全局空间（非线程）的值 */
ZEND_BEGIN_MODULE_GLOBALS(zdeng)
    zend_long global_value;
    char *global_string;
    zend_long greeting;
ZEND_END_MODULE_GLOBALS(zdeng)

	
/* ZDENG_G */
/* Always refer to the globals in your function as ZDENG_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define ZDENG_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(zdeng, v)

#if defined(ZTS) && defined(COMPILE_DL_ZDENG)
ZEND_TSRMLS_CACHE_EXTERN()
#endif
	
	
	
	
	
/* 2 实例化 zend_zdeng_globals */
/* If you declare any globals in php_zdeng.h uncomment this: */
ZEND_DECLARE_MODULE_GLOBALS(zdeng)


/* 3 给php.ini注册配置项并赋初值 */
/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini */
//added by Shark
//PHP_INI_ALL 指令在任何地方修改
//PHP_INI_USER 在用户脚本修改
//PHP_INI_SYSTEM 在php.ini / httpd.conf
//PHP_INI_PERDIR， 指令在php.ini / httpd.conf / .htaccess
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("zdeng.global_value",  "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_zdeng_globals, zdeng_globals)
    STD_PHP_INI_ENTRY("zdeng.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_zdeng_globals, zdeng_globals)
    STD_PHP_INI_ENTRY("zdeng.greeting", "8", PHP_INI_ALL, OnUpdateLong, greeting, zend_zdeng_globals, zdeng_globals)
PHP_INI_END()
/* }}} */


/* 4 初始化php.ini配置项的初始值 */
/* {{{ php_zdeng_init_globals
 */
/* Uncomment this function if you have INI entries */
static void php_zdeng_init_globals(zend_zdeng_globals *zdeng_globals)
{
    zdeng_globals->global_value = 0;
    zdeng_globals->global_string = NULL;
    zdeng_globals->greeting = 18;
}

/* }}} */


/ * 5 */
PHP_MINIT_FUNCTION(zdeng)
{
    /* If you have INI entries, uncomment these lines */
    ZEND_INIT_MODULE_GLOBALS(zdeng, php_zdeng_init_globals, NULL); //打开4初始值
    REGISTER_INI_ENTRIES(); //打开3初始值，最后面的起作用。
	
    RETURN SUCCESS;
}
  
 
/* 6 */
/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(zdeng)
{
	/* uncomment this line if you have INI entries */
	UNREGISTER_INI_ENTRIES();
	
	return SUCCESS;
}
/* }}} */


/* 7 */获取全局值
PHP_FUNCTION(getGreeting){
	php_printf("%s \n", ZDENG_G(greeting));
	php_printf("%d \n", ZDENG_G(global_value));
	php_printf("%s \n", ZDENG_G(global_string));
	RETURN_LONG(ZDENG_G(global_value));
}


