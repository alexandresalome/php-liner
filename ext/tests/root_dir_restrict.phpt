--TEST--
Simple test
--INI--
--FILE--
<?php
ini_set('php_liner.root_dir', __DIR__.'/lib');

$coverageFile = php_liner_start();
include(__DIR__.'/lib/math.php');
$x = plus(2, 3);
php_liner_stop();
echo file_get_contents($coverageFile);
?>
--EXPECT--
+/math.php
3
8
12
5
