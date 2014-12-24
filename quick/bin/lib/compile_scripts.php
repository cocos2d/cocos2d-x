<?php

require_once(__DIR__ . '/quick/ScriptsCompiler.php');

$options = array(
    array('h',   'help',       0,      false,       'show help'),
    array('i',   'src',        1,      null,        'source files directory'),
    array('o',   'output',     1,      null,        'output filename | output directory'),
    array('p',   'prefix',     1,      '',          'package prefix name'),
    array('x',   'excludes',   1,      null,        'excluded packages'),
    array('m',   'compile',    1,      'zip',       'compile mode'),
    array('e',   'encrypt',    1,      null,        'encrypt mode'),
    array('ek',  'key',        1,      null,        'encrypt key'),
    array('es',  'sign',       1,      null,        'encrypt sign'),
    array('ex',  'extname',    1,      'lua',       'encrypted file extension name (default is "lua"), only valid for xxtea_chunk'),
    array('c',   'config',     1,      null,        'load options from config file'),
    array('q',   'quiet',      0,      false,       'quiet'),
    array('jit', 'jit',        0,      false,       'using luajit compile framework'),
);

function errorhelp()
{
    print("\nshow help:\n    compile_scripts -h\n\n");
}

function help()
{
    global $options;

    echo <<<EOT

usage: compile_scripts -i src -o output ...

options:

EOT;

    for ($i = 0; $i < count($options); $i++)
    {
        $o = $options[$i];
        printf("    -%s %s\n", $o[0], $o[4]);
    }

    echo <<<EOT

compile mode:
    -m zip (default)    package all scripts bytecodes to a ZIP archive file.
    -m c                package all scripts bytecodes to a C source file.
    -m files            save bytecodes to separate files. -o specifies output dir.

encrypt mode:
    -e xxtea_zip        encrypt ZIP archive file with XXTEA algorithm,
    -e xxtea_chunk      encrypt every bytecodes chunk with XXTEA algorithm.
                        * default encrypt sign is "XXTEA"
                        * output file extension name is "bytes"

config file format:

    return array(
        'src'      => source files directory,
        'output'   => output filename or output directory,
        'prefix'   => package prefix name,
        'excludes' => excluded packages,
        'compile'  => compile mode,
        'encrypt'  => encrypt mode,
        'key'      => encrypt key,
        'sign'     => encrypt sign,
        'extname'  => encrypted file extension name,
    );

examples:

    # package scripts/*.lua bytecodes to game.zip
    compile_scripts -i scripts -o game.zip

    # excluding package "tests.*" and "server.*"
    compile_scripts -i scripts -x tests,server -o game.zip

    # encrypt with XXTEA, use default sign
    compile_scripts -i scripts -o game.zip -e xxtea_zip -ek MYKEY

    # encrypt with XXTEA, specifies sign
    compile_scripts -i scripts -o game.zip -e xxtea_zip -ek MYKEY -es XT

    # encrypt with XXTEA, specifies encrypted file extension name
    compile_scripts -i scripts -o game.zip -e xxtea_zip -ek MYKEY -ex lua

    # encrypt with XXTEA, package all bytecodes to C source file
    compile_scripts -i scripts -o game.c -m c -e xxtea_chunks -ek MYKEY

    # load options from config file
    compile_scripts -c my_proj_compile_config.php


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

$compiler = new ScriptsCompiler($config, $options);
if ($compiler->validateConfig())
{
    return($compiler->run());
}
else
{
    errorhelp();
    return(1);
}
