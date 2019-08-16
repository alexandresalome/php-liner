#include "php-liner.h"

ZEND_DECLARE_MODULE_GLOBALS(php_liner)

PHP_FUNCTION(php_liner)
{
    RETURN_LONG(LG(coverage_count));
}

extern zend_module_entry php_liner_module_entry;

static zend_function_entry php_liner_functions[] = {
    PHP_FE(php_liner, NULL)
    {NULL, NULL, NULL}
};

int handle_new(zend_execute_data *execute_data)
{
    zend_op_array *op_array = &execute_data->func->op_array;
    const zend_op *cur_opcode;
    int      lineno;
    char    *file;

    cur_opcode = execute_data->opline;
    lineno = cur_opcode->lineno;
    file = (char*) op_array->filename->val;

    LG(coverage_count)++;

    // Continue normal execution
    return ZEND_USER_OPCODE_DISPATCH;
}

PHP_MINIT_FUNCTION(php_liner)
{
    zend_set_user_opcode_handler(ZEND_NEW, handle_new);
}

zend_module_entry php_liner_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_LINER_EXTNAME,
    php_liner_functions,
    PHP_MINIT(php_liner),
    NULL, // MSHUTDOWN
    NULL, // RINIT
    NULL, // RSHUTDOWN
    NULL, // MINFO
    PHP_LINER_VERSION,
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(php_liner)
