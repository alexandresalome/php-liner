--TEST--
Simple test
--FILE--
<?php
$coverageFile = php_liner_start();
$x = 3;
php_liner_stop();
echo file_get_contents($coverageFile);
?>
--EXPECTF--
+%s/ext/tests/simple.php
2
3
4
