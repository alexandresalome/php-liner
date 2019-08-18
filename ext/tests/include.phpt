--TEST--
Simple test
--FILE--
<?php
$coverageFile = php_liner_start();

include(__DIR__.'/include_lib.php');
some();

php_liner_stop();
echo file_get_contents($coverageFile);
?>
--EXPECTF--
+%s/ext/tests/include.php
2
4
+%s/ext/tests/include_lib.php
3
8
11
+%s/ext/tests/include.php
5
+%s/ext/tests/include_lib.php
5
+%s/ext/tests/include.php
7
