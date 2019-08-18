#include <stdio.h>
#include "php-liner.h"
#include "writer.h"
#include "random.h"

//
// Globals definition
//

ZEND_DECLARE_MODULE_GLOBALS(php_liner)

//
// PHP functions
//

ZEND_BEGIN_ARG_INFO_EX(arginfo_php_liner_start, 0, 0, 1)
    ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

PHP_FUNCTION(php_liner_start)
{
    zend_string *trace_name;
    char *output_dir, filename[512];

    ZEND_PARSE_PARAMETERS_START(0, 1);
        Z_PARAM_OPTIONAL;
        Z_PARAM_STR(trace_name);
    ZEND_PARSE_PARAMETERS_END();

    output_dir = LG(output_dir);

    if (output_dir == NULL) {
        php_error(E_ERROR, "No output directory configured for php-liner (php_liner.output_dir in php.ini).");

        return;
    }

    char random_hash[16];
    rand_str(random_hash, 15);

    char time_text[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(time_text, sizeof(time_text)-1, "%Y-%m-%d-%H-%M-%S", t);

    sprintf(filename, "%s/%s.%s", output_dir, time_text, random_hash);

    LG(output) = pl_stream_create(filename);
    LG(enabled) = 1;

    if (trace_name != NULL) {
        pl_stream_write_trace_name(LG(output), ZSTR_VAL(trace_name));
    }

    RETURN_STRING(filename);
}

PHP_FUNCTION(php_liner_stop)
{
    // Copied to RSHUTDOWN
    if (LG(enabled) == 1) {
        pl_stream_close(LG(output));
        LG(enabled) = 0;
    }
}

//
// Coverage capture
//

int coverage_handler(zend_execute_data *execute_data)
{
    // If the capture is not enabled, ignore
    if (LG(enabled) == 0) {
        return ZEND_USER_OPCODE_DISPATCH;
    }

    zend_op_array *op_array = &execute_data->func->op_array;
    const zend_op *cur_opcode;

    int   lineno;
    char *file;

    cur_opcode = execute_data->opline;
    lineno = cur_opcode->lineno;
    file = (char*) op_array->filename->val;

    if (file != LG(current_file)) {
        pl_stream_write_file_name(LG(output), file);
        LG(current_file) = file;
        LG(current_line) = -1;
    }

    if (lineno != LG(current_line)) {
        pl_stream_write_line_number(LG(output), lineno);
        LG(current_line) = lineno;
    }

    // Continue normal execution
    return ZEND_USER_OPCODE_DISPATCH;
}

//
// Module configuration
//

ZEND_INI_MH(php_liner_ini_modify_handler)
{
    LG(output_dir) = INI_STR("php_liner.output_dir");
}

/* {{{ INI Settings */
PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("php_liner.output_dir",   "/tmp/php_liner.traces", PHP_INI_ALL, php_liner_ini_modify_handler, output_dir, zend_php_liner_globals, php_liner_globals)
PHP_INI_END()
/* }}} */

//
// Module setup
//

extern zend_module_entry php_liner_module_entry;

static zend_function_entry php_liner_functions[] = {
    PHP_FE(php_liner_start, arginfo_php_liner_start)
    PHP_FE(php_liner_stop, NULL)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(php_liner)
{
    REGISTER_INI_ENTRIES();

    for (int i = 0; i < 256; i++) {
        zend_set_user_opcode_handler(i, coverage_handler);
    }
}

PHP_MSHUTDOWN_FUNCTION(php_liner)
{
    UNREGISTER_INI_ENTRIES();
}

PHP_MINFO_FUNCTION(php_liner)
{
    DISPLAY_INI_ENTRIES();
}

PHP_RINIT_FUNCTION(php_liner)
{
    LG(enabled) = 0;
}

PHP_RSHUTDOWN_FUNCTION(php_liner)
{
    // Copied from php_liner_stop
    if (LG(enabled) == 1) {
        pl_stream_close(LG(output));
        LG(enabled) = 0;
    }
}

zend_module_entry php_liner_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_LINER_EXTNAME,
    php_liner_functions,
    PHP_MINIT(php_liner),
    PHP_MSHUTDOWN(php_liner),
    PHP_RINIT(php_liner),
    PHP_RSHUTDOWN(php_liner),
    PHP_MINFO(php_liner),
    PHP_LINER_VERSION,
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(php_liner)
