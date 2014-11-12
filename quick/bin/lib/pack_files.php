<?php

ini_set('memory_limit','256M');
require_once(__DIR__ . '/quick/FilesPacker.php');

$options = array(
    array('h',   'help',       0,      false,       'show help'),
    array('i',   'src',        1,      null,        'source files directory'),
    array('o',   'output',     1,      null,        'output filename | output directory'),
    array('p',   'prefix',     1,      '',          'package prefix name'),
    array('x',   'excludes',   1,      null,        'excluded packages'),
    array('m',   'pack',    1,      'files',       'pack mode'),
    #array('e',   'encrypt',    1,      null,        'encrypt mode'),
    array('ek',  'key',        1,      null,        'encrypt key'),
    array('es',  'sign',       1,      null,        'encrypt sign'),
    #array('ex',  'extname',    1,      'pb',       'encrypted file extension name (default is "lua"), only valid for xxtea_chunk'),
    array('c',   'config',     1,      null,        'load options from config file'),
    array('q',   'quiet',      0,      false,       'quiet'),
);

function errorhelp()
{
    print("\nshow help:\n    pack_files -h\n\n");
}

function help()
{
    global $options;

    echo <<<EOT

usage: pack_files -i src -o output ...

options:

EOT;

    for ($i = 0; $i < count($options); $i++)
    {
        $o = $options[$i];
        printf("    -%s %s\n", $o[0], $o[4]);
    }

    echo <<<EOT

pack mode:
    -m zip                  package all files to a ZIP archive file and encrypt.
    -m files (default)  save encrypted files to separate files. -o specifies output dir.
                        * default encrypt sign is "XXTEA"

config file format:

    return array(
        'src'      => source files directory,
        'output'   => output filename or output directory,
        'prefix'   => package prefix name,
        'excludes' => excluded packages,
        'pack'  => pack mode,
        'key'      => encrypt key,
        'sign'     => encrypt sign,
    );

examples:

    # encrypt res/*.* to resnew/, with XXTEA, specifies sign
    pack_files -i res -o resnew -es XXTEA -ek tsts

    # package res/*.* to game.zip
    pack_files -i res -o game.zip -m zip

    # package scripts/*.* to game.zip, encrypt game.zip with XXTEA, specifies sign
    pack_files -i scripts -o game.zip -m zip -es XXTEA -ek tsts

    # load options from config file
    pack_files -c my_config.lua


EOT;

}

// ----

print("\n");
if ($argc < 2)
{
    help();
    return(1);
}

$config = fetchCommandLineArguments($argv, $options, 4);
if (!$config)
{
    errorhelp();
    return(1);
}

if ($config['help'])
{
    help();
    return(0);
}

if ($config['config'])
{
    $configFilename = $config['config'];
    if (file_exists($configFilename))
    {
        $config = @include($configFilename);
    }
    else
    {
        $config = null;
    }

    if (!is_array($config))
    {
        printf("ERR: invalid config file, %s\n", $configFilename);
        errorhelp();
        return(1);
    }
}

$packer = new FilesPacker($config, $options);
if ($packer->validateConfig())
{
    return($packer->run());
}
else
{
    errorhelp();
    return(1);
}
