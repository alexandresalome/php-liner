<?php

ini_set('php_liner.output_dir', __DIR__);

$coverageFile = php_liner_start("Run on ".date('Y-m-d H:i:s'));

function hello($who)
{
    return sprintf(
        "Hello, %s\n",
        $who
    );
}

echo hello('world');

php_liner_stop();
echo "Coverage file: $coverageFile";
