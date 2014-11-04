<?php

// $quick_path = __DIR__ . "/../../..";
// $cocos_path = file_get_contents($quick_path . "/.COCOS_ROOT_PATH");
// $consoleDir = $cocos_path . '/tools/cocos2d-console/bin';
$consoleDir = $_ENV['COCOS_CONSOLE_ROOT'];
// call cocos to compile
$cmd_str = $consoleDir . "/cocos compile";
$i = 1;
while ($i < count($argv))
{
	$cmd_str = $cmd_str . ' ' . $argv[$i];
	$i = $i + 1;
}

echo "exec: $cmd_str\n";
system($cmd_str, $retval);
echo "*******************\n";
return $retval;
