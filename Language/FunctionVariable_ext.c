PHP_FUNCTION(myDefault)
{
    zend_string *type;  //php的string
    zval *value = NULL; //swift的Any?= NULL
    
#ifdef FAST_ZPP
    //大写S， 小写s会出错！
    if(zend_parse_parameters(ZEND_NUM_ARGS(), "S|z", &type, &value) == FAILURE) {
        return;
    }
#else
    ZEND_PARSE_PARAMETERS_START(1, 2)//1个必须赋值，2个变量
        Z_PARAM_STR(type)            // S
        Z_PARAM_OPTIONAL             // |
        Z_PARAM_ZVAL_EX(value, 0, 1) // z (0, 1)是打开两个specific，暂不明白什么意思
    ZEND_PARSE_PARAMETERS_END()
#endif
    
    //                         type == "int"
    if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "int", 3) == 0 && value == NULL){
        RETURN_FALSE;
    } else if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "int", 3) == 0 && value != NULL) {
        RETURN_ZVAL(value, 0, 1);
        
    } else if (ZSTR_LEN(type) == 4 && strncmp(ZSTR_VAL(type), "bool", 4) == 0 && value == NULL) {
        RETURN_FALSE;
    } else if (ZSTR_LEN(type) == 4 && strncmp(ZSTR_VAL(type), "bool", 4) == 0 && value != NULL) {
        RETURN_ZVAL(value, 0, 1);
        
    } else if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "str", 3) == 0 && value == NULL) {
        RETURN_EMPTY_STRING();
    } else if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "str", 3) == 0 && value != NULL) {
        RETURN_ZVAL(value, 0, 1);
    }
    
    RETURN_NULL();
}


/* php test 
var_dump(myDefault("int"));
var_dump(myDefault("int", 1));
var_dump(myDefault("bool"));
var_dump(myDefault("bool", true));
var_dump(myDefault("str","A"));
var_dump(myDefault("str"));
*/
