



/* class methods define */
ZEND_METHOD(myclass, public_method)
{
    php_printf("我是public_method方法\n");
}
ZEND_METHOD(myclass, __construct)
{
    php_printf("我是构造方法\n");
}

/* class methods declare 
 * for define body can be put later */
PHP_METHOD(myclass, public_method);
PHP_METHOD(myclass, __construct);


static zend_function_entry myclass_methods[] =
{
    ZEND_ME(myclass, public_method, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(myclass, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    {NULL, NULL, NULL}
};
 

PHP_MINIT_FUNCTION(deng)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
    
    //类容器，名字随便取，把类名和类方法打包。
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "myclass", myclass_methods);
  
    //类指针
    zend_class_entry *ce_ptr  
    myclass_ce = zend_register_internal_class(&ce TSRMLS_CC);//这步必须做，不然类会注册失败
    
    /* define class property
     * 3 infos are needed: name, value, visit_level
     * ----visit_level 6----
     * #define ZEND_ACC_STATIC      0x01    static
     * #define ZEND_ACC_PUBLIC      0x100   public
     * #define ZEND_ACC_PROTECTED   0x200   protected
     * #define ZEND_ACC_PRIVATE     8x400   private
     * #define ZEND_ACC_CTOR                __construct
     * #define ZEND_ACC_DTOR                __destruct
     * ----value----
     * zend_declare_property_null   null
     * zend_declare_property_string string
     */
    zend_declare_property_null(myclass_ce, "public_var", strlen("public_var"), ZEND_ACC_PUBLIC TSRMLS_CC);
    
    /* define class constant */
    zend_declare_class_constant_string(myclass_ce, "CONSTANT_VAR", strlen("CPNSTANT_VAR"), "boygirl88.com" TSRMLS_CC);
    
    
    
	return SUCCESS;
}

/*
B——3）测试

<?php
echo confirm_deng_compiled("okok");
echo "\n";


echo  sum(1, 2);
echo "\n";

$gameObject = new myclass();

echo "\n";

var_dump($gameObject);

?>

*/
