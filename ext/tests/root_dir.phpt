--TEST--
Simple test
--INI--
--FILE--
<?php
ini_set('php_liner.root_dir', __DIR__);

$coverageFile = php_liner_start();
$x = 3;
php_liner_stop();
echo file_get_contents($coverageFile);
?>
--EXPECT--
+/root_dir.php
4
5
6
