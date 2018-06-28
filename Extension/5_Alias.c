//构造函数
ZEND_BEGIN_ARG_INFO_EX(arginfo_d_swoole_server__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, host)
    ZEND_ARG_INFO(0, port)
    ZEND_ARG_INFO(0, mode)
    ZEND_ARG_INFO(0, sock_type)
ZEND_END_ARG_INFO()

PHP_METHOD(d_swoole_server, __construct);
ZEND_METHOD(d_swoole_server, __construct)
{
    php_printf("d_swoole_server __construct");
}




//food()
//d_swoole_server类的foo() -->PHP_FALIAS
ZEND_BEGIN_ARG_INFO_EX(arginfo_food, 0, 0, 1)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

PHP_FUNCTION(food);
ZEND_FUNCTION(food)
{
    char *name;
    size_t name_len;
    char buf[20]={0};
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE){
        return;
    }
    snprintf(buf, sizeof(buf) - 1, name);
    php_printf("%s", name);
}




//d_swoole_server类的listener --> PHP_MALIAS
ZEND_BEGIN_ARG_INFO_EX(arginfo_d_swoole_server_listener, 0, 0, 1)
    ZEND_ARG_INFO(0, port)
ZEND_END_ARG_INFO()

ZEND_METHOD(d_swoole_server, listener)
{
    php_printf("listerner");
}





static zend_function_entry d_swoole_server_methods[] = {
    ZEND_ME(d_swoole_server, __construct, arginfo_d_swoole_server__construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    
    ZEND_ME(d_swoole_server, listener, arginfo_d_swoole_server_listener, ZEND_ACC_PUBLIC)
    ZEND_MALIAS(d_swoole_server, addListener, listener, arginfo_d_swoole_server_listener, ZEND_ACC_PUBLIC)
    
    PHP_FALIAS(foo, food, arginfo_food)
    {NULL, NULL, NULL}
};
//ZEND_ME = PHP_ME
//ZEND_fUNCTION = PHP_FUNCTION
//ZEND_METHOD = PHP_METHOD
