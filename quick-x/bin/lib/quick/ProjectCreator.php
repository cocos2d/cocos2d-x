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
        // check template
        $templatePath = rtrim($this->config['template'], "/\\") . DS;
        if (!is_dir($templatePath))
        {
            printf("ERROR: invalid template path \"%s\"\n", $templatePath);
            return false;
        }
        if (!file_exists($templatePath . 'TEMPLATE_INFO.json'))
        {
            printf("ERROR: not found TEMPLATE_INFO.json in template path \"%s\"\n", $templatePath);
            return false;
        }
        $info = file_get_contents($templatePath . 'TEMPLATE_INFO.json');
        $info = json_decode($info, true);
        if (!is_array($info) || empty($info['name']))
        {
            printf("ERROR: invalid TEMPLATE_INFO.json in template path \"%s\"\n", $templatePath);
            return false;
        }
        $this->config['template'] = $templatePath;

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
            $this->config['output'] = rtrim(getcwd(), '/\\') . DS . $lastname . DS;
        }
        else
        {
            $this->config['output'] = rtrim($this->config['output'], '/\\') . DS;
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
        if (!is_dir($this->config['output'])) mkdir($this->config['output']);
        if (!is_dir($this->config['output']))
        {
            printf("ERROR: create project dir \"%s\" failure\n", $this->config['output']);
            return false;
        }

        // prepare contents
        $this->vars['__TEMPLATE_PATH__'] = $this->config['template'];
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

        // copy files
        $paths = $this->getPaths($this->config['template']);
        foreach ($paths as $sourcePath)
        {
            $sourceFilename = substr($sourcePath, strlen($this->config['template']));
            if ($sourceFilename == 'TEMPLATE_INFO.json') continue;
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
            if ($file{0} == '.')
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

}
