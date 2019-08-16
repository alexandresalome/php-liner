#ifndef PHP_COUNTER_H
#define PHP_COUNTER_H

#define PHP_LINER_EXTNAME "php-liner"
#define PHP_LINER_VERSION "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

ZEND_BEGIN_MODULE_GLOBALS(php_liner)
    long        coverage_count;
ZEND_END_MODULE_GLOBALS(php_liner)

#define LG(v) ZEND_MODULE_GLOBALS_ACCESSOR(php_liner, v)

#endif
