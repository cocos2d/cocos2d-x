<?php

ini_set('memory_limit','256M');
require_once(__DIR__ . '/quick/ProjectCreator.php');

$options = array(
    array('h',   'help',        0,      false,       'show help'),
    array('p',   'package',     1,      null,        'package name'),
    array('o',   'output',      1,      '',          'project path (default is "current_dir/last_package_name")'),
    array('r',   'orientation', 1,      'portrait',  'screen orientation (default is "portrait")'),
    array('np',  'noproj',      0,      false,       'dont create project files for platform'),
    array('op',  'onlyproj',    0,      false,       'only create project files'),
    array('f',   'force',       0,      false,       'overwrite exists files'),
    array('c',   'config',      1,      null,        'load options from config file'),
    array('q',   'quiet',       0,      false,       'quiet'),
    array('t',   'template',    1,      '',          'template dir'),
    array('lt',  'lite',        0,      false,       'use template-lite'),
);

$extrawork = array(
    "FilesNeedModify" => array(
            // array(
            //     "/cocos/platform/win32/CCFileUtils-win32.cpp",
            //     's_resourcePath.append("/");',
            //     's_resourcePath.append("/../../");',
            //     ),
        ),

    "FilesNeedReplace" => array(
            // array(
            //     'cocos2d.cpp',
            //     "/cocos/cocos2d.cpp",
            //     ),
        ),
);

function errorhelp()
{
    print("\nshow help:\n    create_project -h\n\n");
}

function help()
{
    global $options;

    echo <<<EOT

usage: create_project -p package_name

options:

EOT;

    for ($i = 0; $i < count($options); $i++)
    {
        $o = $options[$i];
        printf("    -%s %s\n", $o[0], $o[4]);
    }

    echo <<<EOT

screen orientation:
    -r portrait (default)
    -r landscape

config file format:

    return array(
        'package'       => package name,
        'output'        => project path,
        'orientation'   => screen orientation,
        'noproj'        => dont create project files for platform,
        'onlyproj'      => only create project files,
        'force'         => overwrite exists files,
        'quiet'         => quiet,
    );

examples:

    # create new project folder "hello", package name is com.quick2dx.samples.hello
    create_project -p com.quick2dx.samples.hello

    # create project files in exists folder "hello"
    create_project -op -p com.quick2dx.samples.hello

    # load options from config file
    create_project -c my_proj_create_config.php


EOT;

}

// ----

print("\n");
if ($argc < 2)
{
    help();
    exit(1);
}

$config = fetchCommandLineArguments($argv, $options, 4);
if (!$config)
{
    errorhelp();
    exit(1);
}

if ($config['help'])
{
    help();
    exit(0);
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
        exit(1);
    }
}

$config['extrawork'] = $extrawork;
$creator = new ProjectCreator($config, $options);
if ($creator->validateConfig())
{
    if ($creator->run() == true)
    {
        exit(0);
    }
    else
    {
        exit(1);
    }
    // return($creator->run());
}
else
{
    errorhelp();
    exit(1);
}
