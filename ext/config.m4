PHP_ARG_ENABLE(php_liner, whether to enable php-liner support, [  --enable-php-liner           Enable php-liner support])
PHP_NEW_EXTENSION(php_liner,
    php-liner.c \
    random.c \
    stringutils.c \
    writer.c \
, $ext_shared)
