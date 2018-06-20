/* start resource test */
/* API in zend_list.c */
//resouce_type
int le_person;

// resource name
#define PERSON_RES_NAME "Shark"

typedef struct _person {
    char *name;
    int name_len;
    long age;
} person;


/* 2 创建资源 */
PHP_FUNCTION(new_person);
ZEND_FUNCTION(new_person)
{
    person *p;
    
    char *name;
    int name_len;
    long age;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &name, &name_len, &age) == FAILURE){
        RETURN_FALSE;
    }
    
    if (name_len < 0) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "no name give, person resource create failed" );
        RETURN_FALSE;
    }
    
    if (age< 0 || age > 255){
        php_error_docref(NULL, E_WARNING, "invalid age");
        RETURN_FALSE;
    }
    
    p = emalloc(sizeof(person));
    p->name = estrndup(name, name_len);
    p->name_len = name_len;
    p->age = age;
    
    //把资源装进return_value
    zend_register_resource(p, le_person);
}


PHP_FUNCTION(person_greet);
ZEND_FUNCTION(person_greet)
{
    person *p;
    zval *zp;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zp) == FAILURE) {
        RETURN_FALSE;
    }
    
    zend_fetch_resource(Z_RES_P(zp), PERSON_RES_NAME, le_person);
    
    php_printf("Hello ");
    PHPWRITE(p->name, p->name_len);
    php_printf("\n You are %d years old", p->age);
    
    RETURN_TRUE;
}


PHP_MINIT_FUNCTION(zdeng)
{
    //module_number is in expanded PHP_MINIT, your PHP extension number
    //注册资源
    le_person = zend_register_list_destructors_ex(NULL, NULL, PERSON_RES_NAME, module_number);
  
    RETURN SUCCESS;
}
/* end resource test */
