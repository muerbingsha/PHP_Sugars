ZEND_FUNCTION(sample_array)
{
    
    
    array_init(return_value);
    //php
    //$ret = array();
    //return $ret;
    
    add_assoc_long(return_value, "life", 88);       //$ret["lift"] =  88
    add_index_bool(return_value, 123, 1);           //$ret[123] = true
    add_next_index_double(return_value, 3.14159);   //$ret[124] = 3.14159
    
    /* string, dup by php */
    add_next_index_string(return_value, "Foo");
    
    /* string, dup manually */
    add_next_index_string(return_value, estrdup("Bar"));
    
    
    
    /* add array */
    /*zval 使用栈内存 */
    //php5
    //zval *subarray; MAKE_STD_ZVAL(subarray); //动态在堆上分配内存
    //php7
    zval subarray;
    
    array_init(&subarray);
    
    add_next_index_long(&subarray, 598);
    add_next_index_long(&subarray, 8);
    add_next_index_long(&subarray, 6);
    add_next_index_long(&subarray, 18);
    
    add_index_zval(return_value, 26, &subarray);
}

/* php */
//var_dump(sample_array());
