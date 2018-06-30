PHP_FUNCTION(myCallback){
    zval *function_name;
    zval ret;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &function_name) == FAILURE ){
        return;
    }
    
    if(Z_TYPE_P(function_name) != IS_STRING) {
        php_printf("reqire 1 string argument \n");
        return;
    }
    
    if (call_user_function_ex(EG(function_table),        //HashTable *function_table 函数在哈希表中的位置
                              NULL,                      //zval **object_pp
                              function_name,             //zval *function_name
                              &ret,                      //zval **retval_ptr_ptr
                              0,                         //zval_uint param_count
                              NULL,                      //zval **params[]
                              0,                         //int no_seperation
                              NULL TSRMLS_CC) == FAILURE)//HashTable *symbol_table
    {
        php_printf("failed to call user func \n");
        return;
    }
    
    *return_value = ret;
    zval_copy_ctor(return_value);
    zval_ptr_dtor(&ret);
}
