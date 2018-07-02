
PHP_FUNCTION(array_concat)
{
    zval *arr, *prefix; //两个数组
    zval *arr_val, *prefix_val, final_val; //数组值，范型，所以为zval
    zend_string *string_key, *result;//字符串键
    zend_ulong num_key; //数组健（哈希值or数字键）
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "aa", &arr, &prefix) == FAILURE) {
        return;
    }
    
    //Z_ARRVAL_P(arr) 获得数组
    array_init_size(return_value, zend_hash_num_elements(Z_ARRVAL_P(arr)));
    
    
    ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(arr), num_key, string_key, arr_val) {
        //1 - prefix存在
        
        //字符串键
        if (string_key && zend_hash_exists(Z_ARRVAL_P(prefix), string_key)) {
            prefix_val = zend_hash_find(Z_ARRVAL_P(prefix), string_key);
            
            if (Z_TYPE_P(arr_val) == IS_STRING && prefix_val != NULL && Z_TYPE_P(prefix_val) == IS_STRING) {
                
                //把字符串拼在一起，@param1：字符长度
                result = strpprintf(0, "%s%s", Z_STRVAL_P(prefix_val), Z_STRVAL_P(arr_val));
                
                //zend_string -> zval
                ZVAL_STR(&final_val, result);
                
                zend_hash_update(Z_ARRVAL_P(return_value), string_key, &final_val);
            }
        
        //数字键
        } else if (string_key == NULL && zend_hash_index_exists(Z_ARRVAL_P(prefix), num_key)){
            prefix_val = zend_hash_index_find(Z_ARRVAL_P(prefix), num_key);
            if (Z_TYPE_P(arr_val) == IS_STRING && prefix_val != NULL && Z_TYPE_P(prefix_val) == IS_STRING) {
                result = strpprintf(0, "%s%s", Z_STRVAL_P(prefix_val), Z_STRVAL_P(arr_val));
                ZVAL_STR(&final_val, result);
                zend_hash_index_update(Z_ARRVAL_P(return_value), num_key, &final_val);
            }
            
        //2 - prefix不存在
        //字符串键
        } else if (string_key) {
            zend_hash_update(Z_ARRVAL_P(return_value), string_key, arr_val);
            zval_add_ref(arr_val);
        //数字键
        } else  {
            zend_hash_index_update(Z_ARRVAL_P(return_value), num_key, arr_val);
            zval_add_ref(arr_val);
        }
    }ZEND_HASH_FOREACH_END();
    
}



/* php
 function array_concat1 ($arr, $prefix) {
        foreach($arr as $key => $val) {
            if (isset($prefix[$key]) && is_string($val) && is_string($prefix[$key])) {
                $arr[$key] = $prefix[$key].$val;
            }
        }
        return $arr;
    }

    $arr = array(
        0 => '0',
        1 => '123',
        'a' => 'abc',
    );
    $prefix = array(
        1 => '456',
        'a' => 'def',
    );

   // var_dump(array_concat1($arr, $prefix));
    var_dump(array_concat($arr, $prefix));
    */
