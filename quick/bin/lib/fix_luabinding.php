<?php

function help()
{
    echo <<<EOT

Fix luabinding, use CLASS_HASH_CODE for type mapping.

Usage:
    fix_luabinding input_filename


EOT;

    exit(1);
}

if (!isset($argv))
{
    echo "\nERR: PHP \$argv not declared.\n";
    help();
}

if (count($argv) < 1)
{
    help();
}

$path = $argv[1];

if (!file_exists($path))
{
    echo "\nERR: file {$path} not found.\n";
    help();
}

$contents = file_get_contents($path);
$contents = str_replace('CCNodeRGBA', 'CCNode', $contents);
$contents = preg_replace('/tolua_usertype\(tolua_S,"(\w+)"\);/', 'tolua_usertype(tolua_S,"\1"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(\1)), "\1");', $contents);
file_put_contents($path, $contents);

echo "\nDONE.\n";

