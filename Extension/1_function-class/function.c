
/* 修改deng.c， php_deng.h不需要动 */

/*定义函数*/
PHP_FUNCTION(sum)
{
    int x, y, z;
    
    int argc = ZEND_NUM_ARGS();
    
    if (zend_parse_parameters(argc TSRMLS_CC, "ll", &x, &y) == FAILURE)
        return;
    z = x + y;
    RETURN_LONG(z);
}

/*函数声明*/
const zend_function_entry deng_functions[] = {
	PHP_FE(confirm_deng_compiled,	NULL)		/* For testing, remove later. */
    PHP_FE(sum, NULL)
	PHP_FE_END	/* Must be the last line in deng_functions[] */
};
