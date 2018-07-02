
float minit_time;
PHP_MINIT_FUNCTION(zdeng)
{
    /* If you have INI entries, uncomment these lines
     REGISTER_INI_ENTRIES();
     */

    
    /* 开始计时，启动时间 */
    minit_time = time(NULL);
    
    
    return SUCCESS;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(zdeng)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
    
    FILE *fp=fopen("sd_m.txt","a+");
    float delta = time(NULL) - minit_time;
    fprintf(fp, "%f\n", delta);
    fclose(fp);
    
    
	return SUCCESS;
}


float rinit_time;

PHP_RINIT_FUNCTION(zdeng)
{
#if defined(COMPILE_DL_ZDENG) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
    
    rinit_time = time(NULL);
    
	return SUCCESS;
}



PHP_RSHUTDOWN_FUNCTION(zdeng)
{
    FILE *fp = fopen("sd_r.txt", "a+");
    float delta = time(NULL) - rinit_time;
    fprintf(fp, "%f\n", delta);
    fclose(fp);
    
	return SUCCESS;
}

PHP_MINFO_FUNCTION(zdeng)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "zdeng support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}

PHP_GINIT_FUNCTION  初始化全局变量时 
PHP_GSHUTDOWN_FUNCTION  释放全局变量时
