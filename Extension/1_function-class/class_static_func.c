zend_class_entry myClass_ce;
zend_class_entry *myClass_ptr;


/* ZEND_METHOD 展开
 * Zend/zend_API.h
 * #define ZEND_METHOD(classname, name)     ZEND_NAMED_FUNCTION(ZEND_MN(classname##_##name))
 * #define ZEND_NAMED_FUNCTION(name)        void name(INTERNAL_FUNCTION_PARAMETERS)
 */
void zim_myClass_print_author(zend_execute_data *data, zval *return_value)
{
    //TRACE("my_print_author");
    char *s = "author=SharkDeng \n";
    //PHPAPI size_t php_output_write_unbuffered(const char *str, size_t len) //不带缓存
    //PHPAPI size_t php_output_write(const char *str, size_t len)    //带缓存
    php_output_write(s, strlen(s));  //php echo()
    ZVAL_BOOL(return_value, 1);
}



/* ZEND_ME展开
 * Zend/zend_API.h
 * #define ZEND_ME(classname, name, arg_info, flags)     ZEND_FENTRY(name, ZEND_MN(classname##_##name), arg_info, flags)
 * #define ZEND_MN(name)                                 zim_##name
 * #define ZEND_FENTRY(zend_name, name, arg_info, flags) {#zend_name, name, arg_info, ---, flags}
 */
zend_function_entry myClass_methods[] = {
    //ZEND_ME(myClass, __construct, NULL, ZEND_ACC_PUBLIC)
    
    //fname,        handler,      arg_info, num_args, flags
    //{"__construct", zim_myClass_construct, NULL, 0, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR},
    //{"version",     zim_myClass_version,   NULL, 0, ZEND_ACC_PUBLIC},
    {"print_author", zim_myClass_print_author, NULL, 0, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC},
    {NULL, NULL, NULL}
};


//ZEND_FUCNTION 展开后
void zif_test_object(zend_execute_data *data, zval *return_value)
{
    php_printf("good \n");
    //TRACE("zif_test_object");
    
    //转换str为zend_string
    zend_string *myClass_classname = zend_string_init("myClass", sizeof("myClass") - 1, 0);
    
    //得到zend_class_entry *myClass_ptr = zend_register_internal_class(&myClass_ce);
    myClass_ptr = zend_lookup_class(myClass_classname);
    zend_string_release(myClass_classname);
    assert(myClass_ptr == myClass_class_handle);
    
    zval retval;
    /* zend_fcall_info
     * Zend/zend_API.h
     * typedef struct _zend_fcall_info {
     *  size_t size;
     *  zval function_name;
     *  zval *retval;
     *  zval *params;
     *  zend_object *object;
     *  zend_bool no_separation;
     *  uint32_t param_count;
     * }zend_fcall_info
     */
    zend_fcall_info fci = {
        .size = sizeof(zend_fcall_info),
        .retval = &retval,
        .params = NULL,
        .object = NULL, //静态方法
        .no_separation = 1,
        .param_count = 0
    };
    ZVAL_UNDEF(&fci.function_name);
    
    
    /* zend_fcall_info_cache
     * Zend/zend_API.h
     * typedef struct _zend_fcall_info_cache {
     *  zend_bool initialized;
     *  zend_function *function_handler;
     *  zend_class_entry *calling_scope;
     *  zend_class_entry *called_scope;
     *  zend_object *object;
     * }zend_fcall_info_cache;
     */
    zval *print_author_func = zend_hash_str_find(&(myClass_ptr->function_table), "print_author", sizeof("print_author") - 1);
    zend_fcall_info_cache fcic = {
        .initialized = 1,
        .function_handler = print_author_func->value.func,
        .calling_scope = myClass_ptr,//调用函数所属的类
        .called_scope = NULL, //当前所处类, 全剧函数填NULL
        .object = NULL,
    };
    
    
    /* 调用函数
     * Zend/zend_execute_API.h
     * int zend_call_function(zend_fcall_info *fci, zend_fcall_info_cache *fcic);
     */
    assert(zend_call_function(&fci, &fcic)  == SUCCESS); //调用成功，但不会有结果
    
    if(zend_call_function(&fci, &fcic) == SUCCESS ) {
        php_printf("call class static func good \n");
    };
     
    assert(Z_TYPE_P(&retval) == IS_TRUE);
    
    zval myClass_obj;
    assert(object_init_ex(&myClass_obj, myClass_ptr) == SUCCESS);
    
    php_printf("\n the end \n");
    
}





/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(zdeng)
{
    /* If you have INI entries, uncomment these lines
     REGISTER_INI_ENTRIES();
     */
   
    
    
    INIT_CLASS_ENTRY(myClass_ce, "myClass", myClass_methods);
    myClass_ptr = zend_register_internal_class(&myClass_ce TSRMLS_CC);
    
    return SUCCESS;
}
/* }}} */
