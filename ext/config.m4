PHP_ARG_ENABLE(php_liner, whether to enable php-liner support, [  --enable-php-liner           Enable php-liner support])
PHP_NEW_EXTENSION(php_liner, php-liner.c, $ext_shared)
