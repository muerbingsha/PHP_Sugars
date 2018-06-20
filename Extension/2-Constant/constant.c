
PHP_MINIT_FUNCTION
{
    //注册常量
    //REGISTER_STRING_CONSTANT(char *name, char *value, int flags)
    //REGISTER_STRINGL_CONSTANT(char *name, char *value, int value_len, int flags)
    //REGISTER_LONG_CONSTANT(char *name, long lval, int flags)
    //REGISTER_DOUBLE_CONSTANT(char *name, double dval, int flags)
    //CONST_PERSISTENT 持久常量，MSHUTDOWN才销毁
    /* uage php 里调用 */
    REGISTER_STRING_CONSTANT("D_SWOOLE_BASE", "Single good", CONST_CS | CONST_PERSISTENT);
    
    RETURN SUCCESS;
}
