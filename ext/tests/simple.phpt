--TEST--
Simple test
--SKIPIF--
<?php if (!extension_loaded("php-liner")) print "skip"; ?>
--FILE--
<?php
$dt = new \DateTime();
$dt = new \DateTime();
$dt = new \DateTime();
echo php_liner();
?>
--EXPECT--
3
