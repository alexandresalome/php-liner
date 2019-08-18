#ifndef PHP_COUNTER_H
#define PHP_COUNTER_H

#define PHP_LINER_EXTNAME "php-liner"
#define PHP_LINER_VERSION "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "writer.h"

#include <stdio.h>

ZEND_BEGIN_MODULE_GLOBALS(php_liner)
    // Configuration
    char* output_dir;
    char* root_dir;
    char* exclude_dirs;

    // Runtime
    int enabled;
    pl_stream output;
    char *current_file;
    int current_line;
ZEND_END_MODULE_GLOBALS(php_liner)

// Macro used to reference a module global variable
#define LG(v) ZEND_MODULE_GLOBALS_ACCESSOR(php_liner, v)

#endif
