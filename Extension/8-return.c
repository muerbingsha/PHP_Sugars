//ZEND_FUNCTION展开
//php7

//<Zend/zend_API.h>
//#define ZEND_FUNCTION(name) ZEND_NAMED_FUNCTION(ZEND_FN(name))
//ZEND_FN(name) zif_##name
//ZEND_NAMED_FUNCTION(name) void name(INTERNAL_FUNCTION_PARAMETERS)

//zend.h
//#define INTERNAL_FUNCTION_PARAMETERS zend_execute_data *execute_data, zval *return_value
ZEND_FUNCTION(sample_long_internal)
{
    
    RETURN_LONG(88);
    
    //展开1
    //RETVAL_LONG(88); //改变return_value的值
    //return;
    
    //展开2
    //ZVAL_LONG(return_value, 88); //改变某数的值，该数为return_value
    
    //展开3
    //Z_TYPE_P(return_value) = IS_LONG
    //Z_LVAL_P(return_value) = 88
    
}

/* php

function sample_long(){
    return 88;
}

echo sample_long();

echo sample_long_internal();

*/
