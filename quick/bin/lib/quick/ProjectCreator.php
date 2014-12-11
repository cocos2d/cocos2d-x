<?php

require_once(__DIR__ . '/init.php');

class ProjectCreator
{
    private $config;
    private $options;
    private $validated = false;
    private $vars = array();

    function __construct(array $config, array $options)
    {
        $this->config = $config;
        $this->options = $options;
    }

    function validateConfig()
    {
        $isLite = $this->config['lite'];
        // check template
        $templatePath = rtrim($this->config['template'], "/\\");
        if ($isLite)
        {
            $templatePath = $templatePath . '-lite';
        }
        $templatePath = $templatePath . DS;
        if (!is_dir($templatePath))
        {
            printf("ERROR: invalid template path \"%s\"\n", $templatePath);
            return false;
        }
        if (!file_exists($templatePath . '../cocos2dx_files.json'))
        {
            printf("ERROR: not found cocos2dx_files.json in template path \"%s/..\"\n", $templatePath);
            return false;
        }
        $cocos_files = file_get_contents($templatePath . '../cocos2dx_files.json');
        $cocos_files = json_decode($cocos_files, true);
        if (!is_array($cocos_files) || empty($cocos_files['common']))
        {
            printf("ERROR: not found cocos2dx_files.json in template path \"%s/..\"\n", $templatePath);
            return false;
        }
        $this->config['template'] = $templatePath;
        $this->config['cocos_files'] = $cocos_files;

        // check package name
        $packageName = str_replace('-', '_', strtolower($this->config['package']));
        $parts = explode('.', $packageName);
        $packageName = array();
        for ($i = 0; $i < count($parts); $i++)
        {
            $parts[$i] = preg_replace('/[^a-z0-9_]/', '', $parts[$i]);
            if (!empty($parts[$i])) $packageName[] = $parts[$i];
        }
        if (count($packageName) < 2)
        {
            printf("ERROR: invalid package name \"%s\"\n", implode('.', $packageName));
            return false;
        }

        $lastname = $packageName[count($packageName) - 1];
        array_pop($packageName);
        $packageName = implode('.', $packageName);
        $this->config['package'] = $packageName . '.' . $lastname;
        $this->config['packageLastName'] = $lastname;
        $this->config['packageFullName'] = $packageName . '.' . $lastname;
        $this->config['packageModuleName'] = $packageName;

        // check output path
        if (empty($this->config['output']))
        {
            $curpath = rtrim(getcwd(), '/\\');
            $this->config['output'] = $curpath . DS . $lastname . DS;
            $this->config['cocos_output'] = $curpath;
            $this->config['cocos_project'] = $lastname;
        }
        else
        {
            $outpath = rtrim($this->config['output'], '/\\');
            $this->config['output'] = $outpath . DS;
            $pos = strrpos($outpath, DS);
            if ($pos != false)
            {
                $this->config['cocos_output'] = substr($outpath, 0, $pos);
                $this->config['cocos_project'] = substr($outpath, $pos+1);
            }
            else
            {
                $this->config['cocos_output'] = $outpath;
                $this->config['cocos_project'] = $lastname;
            }
        }
        if (!$this->config['force'] && (is_dir($this->config['output']) || file_exists($this->config['output'])))
        {
            printf("ERROR: project path \"%s\" exists\n", $this->config['output']);
            return false;
        }

        // check screen orientation
        $orientation = strtolower($this->config['orientation']);
        if ($orientation != 'landscape' && $orientation != 'portrait')
        {
            printf("ERROR: invalid screen orientation \"%s\"\n", $orientation);
            return false;
        }
        $this->config['orientation'] = $orientation;

        // check more configs
        if ($this->config['noproj'] && $this->config['onlyproj'])
        {
            print("ERROR: noproj and onlyproj cannot enable at the same time\n");
            return false;
        }

        if ($this->options['extracmd'])
        {
            $this->config['extracmd'] = $this->options['extracmd'];
        }

        if (!$this->config['quiet'])
        {
            dumpConfig($this->config, $this->options);
        }
        $this->validated = true;
        return true;
    }

    function run()
    {
        if (!$this->validated)
        {
            print("ERR: invalid config\n");
            return false;
        }

        // create project dir
        // if (!is_dir($this->config['output'])) mkdir($this->config['output']);
        // if (!is_dir($this->config['output']))
        // {
        //     printf("ERROR: create project dir \"%s\" failure\n", $this->config['output']);
        //     return false;
        // }

        // prepare contents
        $this->vars['__TEMPLATE_PATH__'] = $this->config['template'];
        $this->vars['__PROJECT_COCOS_NAME__'] = $this->config['cocos_project'];
        $this->vars['__PROJECT_PACKAGE_MODULE_NAME__'] = $this->config['packageModuleName'];
        $this->vars['__PROJECT_PACKAGE_MODULE_NAME_L__'] = strtolower($this->config['packageModuleName']);
        $this->vars['__PROJECT_PACKAGE_FULL_NAME__'] = $this->config['packageFullName'];
        $this->vars['__PROJECT_PACKAGE_FULL_NAME_L__'] = strtolower($this->config['packageFullName']);
        $this->vars['__PROJECT_PACKAGE_LAST_NAME__'] = $this->config['packageLastName'];
        $this->vars['__PROJECT_PACKAGE_LAST_NAME_L__'] = strtolower($this->config['packageLastName']);
        $this->vars['__PROJECT_PACKAGE_LAST_NAME_UF__'] = ucfirst(strtolower($this->config['packageLastName']));
        $this->vars['__PROJECT_PATH__'] = $this->config['output'];
        $this->vars['__SCREEN_ORIENTATION__'] = $this->config['orientation'];
        $this->vars['__SCREEN_ORIENTATION_L__'] = strtolower($this->config['orientation']);
        $this->vars['__SCREEN_ORIENTATION_UF__'] = ucfirst(strtolower($this->config['orientation']));
        if ($this->config['orientation'] == 'landscape')
        {
            $this->vars['__SCREEN_WIDTH__'] = '960';
            $this->vars['__SCREEN_HEIGHT__'] = '640';
            $this->vars['__SCREEN_ORIENTATION_QUICK__'] = 'FIXED_HEIGHT';
        }
        else
        {
            $this->vars['__SCREEN_WIDTH__'] = '640';
            $this->vars['__SCREEN_HEIGHT__'] = '960';
            $this->vars['__SCREEN_ORIENTATION_QUICK__'] = 'FIXED_WIDTH';
        }

        if ($this->config['orientation'] == 'landscape')
        {
            $this->vars['__SCREEN_ORIENTATION_IOS__'] = "<string>UIInterfaceOrientationLandscapeRight</string>\n<string>UIInterfaceOrientationLandscapeLeft</string>";
        }
        else
        {
            $this->vars['__SCREEN_ORIENTATION_IOS__'] = '<string>UIInterfaceOrientationPortrait</string>';
        }

        if ($this->config['orientation'] == 'landscape')
        {
            $this->vars['__SCREEN_ORIENTATION_CONFIG_JSON__'] = 'true';
        }
        else
        {
            $this->vars['__SCREEN_ORIENTATION_CONFIG_JSON__'] = 'false';
        }

        // $consoleDir = $_ENV['COCOS_CONSOLE_ROOT'];
        // // call cocos to create new project
        // $cmd_str = $consoleDir . "/cocos new " . $this->config['cocos_project']
        //             . " -p " . $this->vars['__PROJECT_PACKAGE_FULL_NAME__']
        //             . " -l lua -t runtime -d " . $this->config['cocos_output'];
        // if ($this->config['extracmd'])
        // {
        //     $cmd_str = $cmd_str . ' ' . str_replace('#', ' ', $this->config['extracmd']);
        // }
        // $this->exec_sys_cmd($cmd_str);

        // copy files
        $paths = $this->getPaths($this->config['template']);
        foreach ($paths as $sourcePath)
        {
            $sourceFilename = substr($sourcePath, strlen($this->config['template']));
            if ($sourceFilename == 'cocos-project-template.json') continue;
            if ($this->config['noproj'])
            {
                if (substr($sourceFilename, 0, 5) == 'proj.' || substr($sourceFilename, 0, 8) == 'sources/')
                {
                    continue;
                }
            }
            else if ($this->config['onlyproj'])
            {
                if (substr($sourceFilename, 0, 5) != 'proj.' && substr($sourceFilename, 0, 8) != 'sources/' && substr($sourceFilename, 0, 10) != 'run-mac.sh' )
                {
                    continue;
                }
            }
            if (!$this->copyFile($sourcePath)) return false;
        }

        $this->copyTemplateSharedFiles();
        $this->copyFrameworkFiles();
        // $this->copyRuntimeSources();
        if (!$this->config['lite'])
        {
            $this->copyCocosFiles();
            $this->copyQuickSources();
            $this->fixFiles();
            $this->replaceFiles();
        }
        // $this->modifyFiles();

        print("\n\n");

        return true;
    }

    private function copyFile($sourcePath)
    {
        // check filename
        $sourceFilename = substr($sourcePath, strlen($this->config['template']));
        $destinationFilename = $sourceFilename;

        foreach ($this->vars as $key => $value)
        {
            $value = str_replace('.', DS, $value);
            $destinationFilename = str_replace($key, $value, $destinationFilename);
        }

        printf("create file \"%s\" ... ", $destinationFilename);
        $dirname = pathinfo($destinationFilename, PATHINFO_DIRNAME);
        $destinationDir = $this->config['output'] . $dirname;

        if (!is_dir($destinationDir))
        {
            mkdir($destinationDir, 0777, true);
        }
        if (!is_dir($destinationDir))
        {
            printf("ERROR: mkdir failure\n");
            return false;
        }

        $destinationPath = $this->config['output'] . $destinationFilename;
        $contents = file_get_contents($sourcePath);
        if ($contents == false)
        {
            printf("ERROR: file_get_contents failure\n");
            return false;
        }
        $stat = stat($sourcePath);

        foreach ($this->vars as $key => $value)
        {
            $contents = str_replace($key, $value, $contents);
        }

        if (file_put_contents($destinationPath, $contents) == false)
        {
            printf("ERROR: file_put_contents failure\n");
            return false;
        }
        chmod($destinationPath, $stat['mode']);

        printf("OK\n");
        return true;
    }

    private function getPaths($dir)
    {
        $files = array();
        $dir = rtrim($dir, "/\\") . DS;
        $dh = opendir($dir);
        if ($dh == false)
        {
            return $files;
        }

        while (($file = readdir($dh)) !== false)
        {
            if ($file == "." || $file == ".." || $file == ".DS_Store")
            {
                continue;
            }

            $path = $dir . $file;
            if (is_dir($path))
            {
                $files = array_merge($files, $this->getPaths($path));
            }
            elseif (is_file($path))
            {
                $files[] = $path;
            }
        }
        closedir($dh);
        return $files;
    }

    function exec_sys_cmd($cmd_str)
    {
        echo "exec: $cmd_str\n";
        system($cmd_str, $retval);
        echo "*******************\n";
        return $retval;
    }

    // function modifyFiles()
    // {
    //     $projectPath = $this->config['output'];
    //     $files = array();
    //     findFiles($projectPath, $files);
    //     foreach ($files as $src) 
    //     {
    //         $contents = file_get_contents($src);
    //         if ($contents == false)
    //         {
    //             continue;
    //         }
    //         $flagReplace = false;
    //         foreach ($this->vars as $key => $value)
    //         {
    //             $pos = strpos($contents, $key);
    //             if ($pos==false)
    //             {
    //                 continue;
    //             }
    //             $contents = str_replace($key, $value, $contents);
    //             $flagReplace = true;
    //         }
    //         if (!$flagReplace)
    //         {
    //             continue;
    //         }
    //         printf("modify file \"%s\" ... ", $src);
    //         $stat = stat($src);
    //         if (file_put_contents($src, $contents) == false)
    //         {
    //             printf("ERROR: file_put_contents failure\n");
    //             continue;
    //         }
    //         chmod($src, $stat['mode']);

    //         printf("OK\n");
    //     }
    // }

    private function fixFiles()
    {
        $cocosPath = $this->config['output'] . 'frameworks/cocos2d-x';
        $files = $this->config['extrawork']["FilesNeedModify"];
        foreach ($files as $file) 
        {
            $src = $cocosPath . $file[0];
            printf("fix file \"%s\" ... ", $src);
            $contents = file_get_contents($src);
            if ($contents == false)
            {
                printf("ERROR: file_get_contents failure\n");
                continue;
            }
            // $stat = stat($src);

            $contents = str_replace($file[1], $file[2], $contents);

            if (file_put_contents($src, $contents) == false)
            {
                printf("ERROR: file_put_contents failure\n");
                continue;
            }
            // chmod($dest, $stat['mode']);

            printf("OK\n");
        }

        return true;
    }

    private function replaceFiles()
    {
        $quickPath = $_ENV['QUICK_V3_ROOT'];
        $cocosPath = $this->config['output'] . 'frameworks/cocos2d-x';
        $files = $this->config['extrawork']["FilesNeedReplace"];
        foreach ($files as $file) 
        {
            $src = $quickPath . "/quick/lib/hotfix/" . $file[0];
            $dst = $cocosPath . $file[1];
            $this->replaceFile($src, $dst, "replace", false);

            printf("OK\n");
        }

        return true;
    }

    private function replaceFile($src, $dest, $cmd, $flagCheck)
    {
        foreach ($this->vars as $key => $value)
        {
            $value = str_replace('.', DS, $value);
            $dest = str_replace($key, $value, $dest);
        }
        printf($cmd . " file \"%s\" ... ", $dest);
        $destinationDir = pathinfo($dest, PATHINFO_DIRNAME);

        if (!is_dir($destinationDir))
        {
            mkdir($destinationDir, 0777, true);
        }
        if (!is_dir($destinationDir))
        {
            printf("ERROR: mkdir failure\n");
            return false;
        }

        $contents = file_get_contents($src);
        if ($contents == false)
        {
            printf("ERROR: file_get_contents failure\n");
            return false;
        }
        $stat = stat($src);

        if ($flagCheck)
        {
            foreach ($this->vars as $key => $value)
            {
                $contents = str_replace($key, $value, $contents);
            }
        }

        if (file_put_contents($dest, $contents) == false)
        {
            printf("ERROR: file_put_contents failure\n");
            return false;
        }
        chmod($dest, $stat['mode']);

        printf("OK\n");
        return true;
    }

    private function copyCocosFiles()
    {
        $quickPath = $_ENV['QUICK_V3_ROOT'];
        $cocosPath = $this->config['output'] . 'frameworks/cocos2d-x';
        $files = array_merge( $this->config['cocos_files']['common'], 
                               $this->config['cocos_files']['lua'] );
        foreach ($files as $file) 
        {
            $src = $quickPath . "/" . $file;
            if (!file_exists($src)) continue;
            $dst = $cocosPath . "/" . $file;
            $this->replaceFile($src, $dst, "create", false);
        }

        return true;
    }

    private function copyDir($srcPath, $dstPath, $flagCheck)
    {
        $files = array();
        findFiles($srcPath, $files);
        foreach ($files as $src) 
        {
            $dest = str_replace($srcPath, $dstPath, $src);
            $this->replaceFile($src, $dest, "create", $flagCheck);
        }
    }

    private function copyTemplateSharedFiles()
    {
        $quickPath = $_ENV['QUICK_V3_ROOT'] . "/quick/templates/shared";
        $cocosPath = $this->config['output'];

        $dirname = "/res";
        $src = $quickPath . $dirname;
        $dst = $cocosPath . $dirname;
        $this->copyDir($src, $dst, true);

        $dirname = "/src";
        $src = $quickPath . $dirname;
        $dst = $cocosPath . $dirname;
        $this->copyDir($src, $dst, true);

        $dirname = "/frameworks";
        $src = $quickPath . $dirname;
        $dst = $cocosPath . $dirname;
        $this->copyDir($src, $dst, true);

        return true;
    }

    private function copyFrameworkFiles()
    {
        $quickPath = $_ENV['QUICK_V3_ROOT'] . "/quick";
        $cocosPath = $this->config['output'] . "src";

        $dirname = "/cocos";
        $src = $quickPath . $dirname;
        $dst = $cocosPath . $dirname;
        $this->copyDir($src, $dst, false);

        $dirname = "/framework";
        $src = $quickPath . $dirname;
        $dst = $cocosPath . $dirname;
        $this->copyDir($src, $dst, false);

        return true;
    }

    // private function copyRuntimeSources()
    // {
    //     $quickSrcPath = $_ENV['QUICK_V3_ROOT'] . "/quick/lib/runtime-src";
    //     $cocosPath = $this->config['output'] . "/frameworks/runtime-src";

    //     $dirname = "/Classes";
    //     $src = $quickSrcPath . $dirname;
    //     $dst = $cocosPath . $dirname;
    //     $this->copyDir($src, $dst, false);

    //     return true;
    // }

    private function copyQuickSources()
    {
        $quickSrcPath = $_ENV['QUICK_V3_ROOT'] . "/quick/lib";
        $cocosPath = $this->config['output'] . "/frameworks/runtime-src/Classes";

        $dirname = "/quick-src";
        $src = $quickSrcPath . $dirname;
        $dst = $cocosPath . $dirname;
        $this->copyDir($src, $dst, false);

        return true;
    }
}
