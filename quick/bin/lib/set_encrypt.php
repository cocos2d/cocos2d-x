<?php

require_once(__DIR__ . '/quick/EncryptSetter.php');

$options = array(
    array('h',   'help',        0,      false,       'show help'),
    array('p',   'project',     1,      null,        'project path (available after v3.3-final)'),
);

function errorhelp()
{
    print("\nshow help:\n    set_encrypt -h\n\n");
}

function help()
{
    global $options;

    echo <<<EOT

usage: set_encrypt
       set_encrypt -p project_path

CAUTION: "-p" is only available after v3.3-final

EOT;

}

// ----

print("\n");
// if ($argc < 2)
// {
//     help();
//     return(1);
// }

$config = fetchCommandLineArguments($argv, $options);
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

$creator = new EncryptSetter($config, $options);
if ($creator->validateConfig())
{
    return($creator->run());
}
else
{
    errorhelp();
    return(1);
}
