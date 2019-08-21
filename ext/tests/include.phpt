--TEST--
Simple test
--FILE--
<?php
$coverageFile = php_liner_start();

include(__DIR__.'/lib/math.php');
$x = plus(3, 4);

php_liner_stop();
echo file_get_contents($coverageFile);
?>
--EXPECTF--
+%s/ext/tests/include.php
2
4
+%s/ext/tests/lib/math.php
3
8
12
+%s/ext/tests/include.php
5
+%s/ext/tests/lib/math.php
5
+%s/ext/tests/include.php
5
7
