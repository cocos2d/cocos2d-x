<?php

require_once(__DIR__ . '/init.php');

class ApkBuilder
{
    const BUILD_NATIVE_SH = '/build_native.sh';
    const BUILD_NATIVE_BAT = 'build_native.bat';
    const BUILD_NATIVE_SH_RELEASE = '/build_native_release.sh';
    const BUILD_NATIVE_BAT_RELEASE = 'build_native_release.bat';

    private $config;
    private $split_char;
    private $build_bin;

    private $java_home;
    private $java_bin_path;
    private $java_version;

    private $quick_root;

    private $sdk_root;
    private $build_tools_path;
    private $tools_aapt;
    private $tools_dx;
    private $platform_path;
    private $boot_class_path;
    private $class_path;
    private $keystore_file;
    private $keystore_password;
    private $keystore_alias;
    private $timestamp;

    private $ndk_root;

    private $apkFilename;
    private $unsignFilename;

    function __construct($config)
    {
        $this->config = $config;
        // $this->options = $options;
    }

    function check_win32()
    {
        $build_mode = $this->config['build_mode'];
        echo "*******************build mode: $build_mode\n";
        if (DS == '/')
        {
            $this->java_home = '';
            $this->java_bin_path = '';
            $this->split_char =  ':';
            if ($build_mode == 'debug')
            {
                $this->build_bin =  self::BUILD_NATIVE_SH;
            }
            else
            {
                $this->build_bin =  self::BUILD_NATIVE_SH_RELEASE;
            }
            return true;
        }

        $this->java_home = $_ENV["JAVA_HOME"];
        if (!$this->java_home)
        {
            print("\nError: Path JAVA_HOME not found!\n\n");
            return(false);
        }
        $this->java_bin_path = $this->java_home . '\\bin\\';

        {
            $this->split_char =  ';';
            if ($build_mode == 'debug')
            {
                $this->build_bin =  self::BUILD_NATIVE_BAT;
            }
            else
            {
                $this->build_bin =  self::BUILD_NATIVE_BAT_RELEASE;
            }
        }

        return true;
    }

    function check_java()
    {
        $out = array();
        $ret = $this->exec_sys_cmd("java -version");
        if ($ret) {
            return false;
        }

        if ($this->config['java_ver']) 
        {
            $this->java_version = $this->config['java_ver'];
        }
        else
        {
            $this->java_version = '1.6';
        }
        return true;
    }

    function exec_cmd($cmd_str, array & $out)
    {
        echo "exec: $cmd_str\n";
        $last = exec($cmd_str, $out, $retval);
        echo "===================\n" . $last;
        return $retval;
    }

    function exec_sys_cmd($cmd_str)
    {
        echo "exec: $cmd_str\n";
        system($cmd_str, $retval);
        echo "*******************\n";
        return $retval;
    }

    function getBuildToolsPath($dir)
    {
        $dir = rtrim($dir, "/\\") . DS;
        $dh = opendir($dir);
        if ($dh == false) return;

        while (($file = readdir($dh)) !== false)
        {
            if ($file{0} == '.') { continue; }

            $path = $dir . $file;
            if (is_dir($path))
            {
                $retdir = $path;
                break;
            }
        }
        closedir($dh);
        return $retdir;
    }

    function setKeystore()
    {
        $proj_dir = $this->config['project_dir'];
        $json_file = $proj_dir . '/../../../config.json';
        $json = json_decode(file_get_contents($json_file), true);
        $projectName = $json['init_cfg']['name'];
        date_default_timezone_set("Asia/Chongqing");
        $datestr = date('Ymd-His');
        $this->apkFilename = sprintf("%s-%s.apk", $projectName, $datestr);
        $this->unsignFilename = sprintf("%s-%s-unsigned.apk", $projectName, $datestr);

        if ($this->config['nosign'])
        {
            return true;
        }

        if ($this->config['keystore'])
        {
            $this->keystore_file = $this->config['keystore'];
        }
        else
        {
            $this->keystore_file = $this->quick_root . '/quick/bin/android/quickv3.keystore';
        }
        if (!file_exists($this->keystore_file))
        {
            print("\nError: $this->keystore_file not found!\n\n");
            return(false);
        }

        if ($this->config['storepass'])
        {
            $this->keystore_password = $this->config['storepass'];
        }
        else
        {
            $this->keystore_password = '123456';
        }

        if ($this->config['storealias'])
        {
            $this->keystore_alias = $this->config['storealias'];
        }
        else
        {
            $this->keystore_alias = 'quickv3.keystore';
        }

        return true;
    }

    function checkToolsRootPath()
    {
        $this->quick_root = $_ENV["QUICK_V3_ROOT"];
        if (!$this->quick_root)
        {
            print("\nError: Path QUICK_V3_ROOT not found!\n\n");
            return(false);
        }

        $this->sdk_root = $_ENV["ANDROID_SDK_ROOT"];
        if (!$this->sdk_root)
        {
            print("\nError: Path ANDROID_SDK_ROOT not found!\n\n");
            return(false);
        }
        $this->platform_path = $this->sdk_root . '/platforms/android-' . $this->config['api_ver'];
        $this->boot_class_path = $this->platform_path . '/android.jar';
        if (!file_exists($this->boot_class_path))
        {
            print("\nError: $this->boot_class_path not found!\n\n");
            return(false);
        }
        $this->class_path = $this->quick_root . '/quick/bin/android/libcocos2dx.jar';
        if (!file_exists($this->class_path))
        {
            print("\nError: $this->class_path not found!\n\n");
            return(false);
        }
        if ($this->config['classpath']) {
            $this->class_path = $this->class_path . $this->split_char . $this->config['classpath'];
        }

        if (!$this->setKeystore())
        {
            return(false);
        }

        if ($this->config['timestamp'])
        {
            $this->timestamp = $this->config['timestamp'];
        }
        else if($this->java_version != '1.6')
        {
            $this->timestamp = 'http://tsa.starfieldtech.com';
        }

        $this->build_tools_path = $this->sdk_root . '/build-tools';
        if (!is_dir($this->build_tools_path))
        {
            print("\nError: Path $this->build_tools_path not found!\n\n");
            return(false);
        }
        if ($this->config['buildtools']) 
        {
            $this->build_tools_path = $this->build_tools_path . '/' . $this->config['buildtools'];
        }
        else
        {
            $this->build_tools_path = $this->getBuildToolsPath($this->build_tools_path);
        }
        if (!is_dir($this->build_tools_path))
        {
            print("\nError: Path $this->build_tools_path not found!\n\n");
            return(false);
        }
        $this->tools_aapt = $this->build_tools_path . '/aapt';

        $this->ndk_root = $_ENV["ANDROID_NDK_ROOT"];
        if (!$this->ndk_root)
        {
            print("\nError: Path ANDROID_NDK_ROOT not found!\n\n");
            return(false);
        }

        return true;
    }

    function buildNative()
    {
        $retval = $this->exec_sys_cmd($this->config['project_dir'] . $this->build_bin);

        return $retval;
    }

    function appt_res()
    {
        $projPath = $this->config['project_dir'];
        $genPath = $projPath . '/gen';
        if (!is_dir($genPath))
        {
            mkdir($genPath);
        }

        $cmd_str = $this->tools_aapt 
            . ' package -f -m -J ' . $genPath
            . ' -S ' . $projPath . '/res'
            . ' -M ' . $projPath . '/AndroidManifest.xml'
            . ' -I ' . $this->boot_class_path;

        $retval = $this->exec_sys_cmd($cmd_str);

        return $retval;
    }

    function compile_java()
    {
        $projPath = $this->config['project_dir'];
        $binPath = $projPath . '/bin';
        if (!is_dir($binPath))
        {
            mkdir($binPath);
        }

        $classesPath = $binPath . '/classes';
        if (!is_dir($classesPath))
        {
            mkdir($classesPath);
        }

        $files = array();
        findFiles($projPath . '/src', $files);
        findFiles($projPath . '/gen', $files);

        $cmd_str = 'javac -encoding utf8 -target '. $this->java_version
            . ' -source ' . $this->java_version
            . ' -bootclasspath ' . $this->boot_class_path 
            . ' -d ' . $classesPath;
        foreach ($files as $file)
        {
            $cmd_str = $cmd_str . ' ' . $file;
        }
        $cmd_str = $cmd_str . ' -classpath ' . $this->class_path;

        $retval = $this->exec_sys_cmd($cmd_str);
        return $retval;
    }

    function make_dex()
    {
        $projPath = $this->config['project_dir'];
        $libs = str_replace($this->split_char, ' ', $this->class_path);
        $cmd_str = $this->build_tools_path . '/dx'
            . ' --dex --output=' . $projPath . '/bin/classes.dex ' . $projPath . '/bin/classes '
            . $libs;

        $retval = $this->exec_sys_cmd($cmd_str);

        return $retval;
    }

    function make_resources()
    {
        $projPath = $this->config['project_dir'];
        $cmd_str = $this->tools_aapt 
            . ' package -f -S ' . $projPath . '/res'
            . ' -A ' . $projPath . '/assets'
            . ' -M ' . $projPath . '/AndroidManifest.xml'
            . ' -I ' . $this->boot_class_path
            . ' -F ' . $projPath . '/bin/resources.ap_';

        $retval = $this->exec_sys_cmd($cmd_str);

        return $retval;
    }

    function make_apk()
    {
        $projPath = $this->config['project_dir'];
        $cmd_str = 'java -classpath ' . $this->sdk_root . '/tools/lib/sdklib.jar'
            . ' com.android.sdklib.build.ApkBuilderMain'
            . ' ' . $projPath . '/' . $this->unsignFilename
            . ' -u -z ' . $projPath . '/bin/resources.ap_'
            . ' -f ' . $projPath . '/bin/classes.dex'
            . ' -rf ' . $projPath . '/src'
            . ' -nf ' . $projPath . '/libs'
            . ' -rj ' . $projPath . '/libs';

        $retval = $this->exec_sys_cmd($cmd_str);

        return $retval;
    }

    function sign_apk()
    {
        if ($this->config['nosign'])
        {
            return 0;
        }
        $projPath = $this->config['project_dir'];

        $cmd_str = 'jarsigner -keystore ' . $this->keystore_file
            . ' -storepass ' . $this->keystore_password
            . ' -signedjar ' . $projPath . '/' . $this->apkFilename;
        if($this->timestamp)
        {
            $cmd_str = $cmd_str . ' -tsa ' . $this->timestamp;
        }
        $cmd_str = $cmd_str 
                    . ' ' . $projPath . '/' . $this->unsignFilename 
                    . ' ' . $this->keystore_alias;

        $retval = $this->exec_sys_cmd($cmd_str);

        if ($this->config['output'])
        {
            $cmd_str = 'cp ' . $projPath . '/' . $this->apkFilename . ' ' . $this->config['output'];
            $this->exec_sys_cmd($cmd_str);
        }

        return $retval;
    }

    function run()
    {
        $retval = 0;

        if (!$this->check_win32())
        {
            return(-1);
        }

        if (!$this->check_java())
        {
            return(-1);
        }

        if (!$this->checkToolsRootPath())
        {
            return(-1);
        }

        $retval = $this->buildNative();
        if ($retval!=0)
        {
            print("\nError: Build native lib failed!\n\n");
            return($retval);
        }

        $retval = $this->appt_res();
        if ($retval!=0)
        {
            print("\nError: Build resources failed!\n\n");
            return($retval);
        }

        $retval = $this->compile_java();
        if ($retval!=0)
        {
            print("Error: javac error!!\n");
            return($retval);
        }

        $retval = $this->make_dex();
        if ($retval!=0)
        {
            print("Error: make bin/classes.dex error!!\n");
            return($retval);
        }

        $retval = $this->make_resources();
        if ($retval!=0)
        {
            print("Error: make bin/resources.ap_ error!!\n");
            return($retval);
        }

        $retval = $this->make_apk();
        if ($retval!=0)
        {
            print("Error: make bin/unsigner.apk error!!\n");
            return($retval);
        }

        $retval = $this->sign_apk();
        if ($retval!=0)
        {
            print("Error: sign apk file error!!\n");
            return($retval);
        }

        return($retval);
    }

}
