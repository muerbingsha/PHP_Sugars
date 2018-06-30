PHP_FUNCTION(st_callback) {
    zval *obj = NULL;       //类名
    zval *func;             //函数名
    zval *param1 = NULL;    //一个参量
    zval retval;            //返回值
    
    zval args[1];           //参量数组
    
#ifndef FAST_ZPP
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &obj, &func, &param1) == FAILURE) {
        return;
    }
#else
    ZEND_PARSE_PARAMETERS_START(3, 3);
        Z_PARAM_ZVAL(obj)
        Z_PARAM_ZVAL(func)
        Z_PARAM_ZVAL(param1)
    ZEND_PARSE_PARAMETERS_END();
#endif
    
    args[0] = *param1;

    if (Z_TYPE_P(obj) == IS_NULL || obj == NULL){
        call_user_function_ex(EG(function_table),   //方法表
                              NULL,                 //类（对象），全剧函数填null
                              func,                 //函数名
                              &retval,               //返回值
                              1,                    //参数个数
                              args,                 //参数值，zval数组
                              0,                    //参数是否分离
                              NULL                  //符号表，一般为NULL
                              );
    } else {
        call_user_function_ex(EG(function_table), obj, func, &retval, 1, args, 0, NULL);
    }
    
    RETURN_ZVAL(&retval, 0, 1);

}

/* php
function print_msg($msg){
    echo "input msg: ". $msg;
}
st_callback(NULL, "print_msg", "hello my friend!");
*/
