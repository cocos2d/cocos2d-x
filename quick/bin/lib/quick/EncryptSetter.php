<?php

require_once(__DIR__ . '/init.php');

$lopcodes_str = array(
'OP_MOVE /*  A B R(A) := R(B)                    */' ,
'OP_LOADK /* A Bx    R(A) := Kst(Bx)                 */' ,
'OP_LOADBOOL /*  A B C   R(A) := (Bool)B; if (C) pc++            */' ,
'OP_LOADNIL /*   A B R(A) := ... := R(B) := nil          */' ,
'OP_GETUPVAL /*  A B R(A) := UpValue[B]              */' ,
'OP_GETGLOBAL /* A Bx    R(A) := Gbl[Kst(Bx)]                */' ,
'OP_GETTABLE /*  A B C   R(A) := R(B)[RK(C)]             */' ,
'OP_SETGLOBAL /* A Bx    Gbl[Kst(Bx)] := R(A)                */' ,
'OP_SETUPVAL /*  A B UpValue[B] := R(A)              */' ,
'OP_SETTABLE /*  A B C   R(A)[RK(B)] := RK(C)                */' ,
'OP_NEWTABLE /*  A B C   R(A) := {} (size = B,C)             */' ,
'OP_SELF /*  A B C   R(A+1) := R(B); R(A) := R(B)[RK(C)]     */' ,
'OP_ADD /*   A B C   R(A) := RK(B) + RK(C)               */' ,
'OP_SUB /*   A B C   R(A) := RK(B) - RK(C)               */' ,
'OP_MUL /*   A B C   R(A) := RK(B) * RK(C)               */' ,
'OP_DIV /*   A B C   R(A) := RK(B) / RK(C)               */' ,
'OP_MOD /*   A B C   R(A) := RK(B) % RK(C)               */' ,
'OP_POW /*   A B C   R(A) := RK(B) ^ RK(C)               */' ,
'OP_UNM /*   A B R(A) := -R(B)                   */' ,
'OP_NOT /*   A B R(A) := not R(B)                */' ,
'OP_LEN /*   A B R(A) := length of R(B)              */' ,
'OP_CONCAT /*    A B C   R(A) := R(B).. ... ..R(C)           */' ,
'OP_JMP /*   sBx pc+=sBx                 */' ,
'OP_EQ /*    A B C   if ((RK(B) == RK(C)) ~= A) then pc++        */' ,
'OP_LT /*    A B C   if ((RK(B) <  RK(C)) ~= A) then pc++        */' ,
'OP_LE /*    A B C   if ((RK(B) <= RK(C)) ~= A) then pc++        */' ,
'OP_TEST /*  A C if not (R(A) <=> C) then pc++           */' , 
'OP_TESTSET /*   A B C   if (R(B) <=> C) then R(A) := R(B) else pc++ */' , 
'OP_CALL /*  A B C   R(A), ... ,R(A+C-2) := R(A)(R(A+1), ... ,R(A+B-1)) */' ,
'OP_TAILCALL /*  A B C   return R(A)(R(A+1), ... ,R(A+B-1))      */' ,
'OP_RETURN /*    A B return R(A), ... ,R(A+B-2)  (see note)  */' ,
'OP_FORLOOP /*   A sBx   R(A)+=R(A+2);
            if R(A) <?= R(A+1) then { pc+=sBx; R(A+3)=R(A) }*/' ,
'OP_FORPREP /*   A sBx   R(A)-=R(A+2); pc+=sBx               */' ,
'OP_TFORLOOP /*  A C R(A+3), ... ,R(A+2+C) := R(A)(R(A+1), R(A+2)); 
                        if R(A+3) ~= nil then R(A+2)=R(A+3) else pc++   */' ,
'OP_SETLIST /*   A B C   R(A)[(C-1)*FPF+i] := R(A+i), 1 <= i <= B    */' ,
'OP_CLOSE /* A   close all variables in the stack up to (>=) R(A)*/' ,
'OP_CLOSURE /*   A Bx    R(A) := closure(KPROTO[Bx], R(A), ... ,R(A+n))  */' ,
'OP_VARARG/* A B R(A), R(A+1), ..., R(A+B-1) = vararg        */' ,
);

$lopmodes_str = array(
'opmode(0, 1, OpArgR, OpArgN, iABC)        /* OP_MOVE */' ,
'opmode(0, 1, OpArgK, OpArgN, iABx)        /* OP_LOADK */' ,
'opmode(0, 1, OpArgU, OpArgU, iABC)        /* OP_LOADBOOL */' ,
'opmode(0, 1, OpArgR, OpArgN, iABC)        /* OP_LOADNIL */' ,
'opmode(0, 1, OpArgU, OpArgN, iABC)        /* OP_GETUPVAL */' ,
'opmode(0, 1, OpArgK, OpArgN, iABx)        /* OP_GETGLOBAL */' ,
'opmode(0, 1, OpArgR, OpArgK, iABC)        /* OP_GETTABLE */' ,
'opmode(0, 0, OpArgK, OpArgN, iABx)        /* OP_SETGLOBAL */' ,
'opmode(0, 0, OpArgU, OpArgN, iABC)        /* OP_SETUPVAL */' ,
'opmode(0, 0, OpArgK, OpArgK, iABC)        /* OP_SETTABLE */' ,
'opmode(0, 1, OpArgU, OpArgU, iABC)        /* OP_NEWTABLE */' ,
'opmode(0, 1, OpArgR, OpArgK, iABC)        /* OP_SELF */' ,
'opmode(0, 1, OpArgK, OpArgK, iABC)        /* OP_ADD */' ,
'opmode(0, 1, OpArgK, OpArgK, iABC)        /* OP_SUB */' ,
'opmode(0, 1, OpArgK, OpArgK, iABC)        /* OP_MUL */' ,
'opmode(0, 1, OpArgK, OpArgK, iABC)        /* OP_DIV */' ,
'opmode(0, 1, OpArgK, OpArgK, iABC)        /* OP_MOD */' ,
'opmode(0, 1, OpArgK, OpArgK, iABC)        /* OP_POW */' ,
'opmode(0, 1, OpArgR, OpArgN, iABC)        /* OP_UNM */' ,
'opmode(0, 1, OpArgR, OpArgN, iABC)        /* OP_NOT */' ,
'opmode(0, 1, OpArgR, OpArgN, iABC)        /* OP_LEN */' ,
'opmode(0, 1, OpArgR, OpArgR, iABC)        /* OP_CONCAT */' ,
'opmode(0, 0, OpArgR, OpArgN, iAsBx)       /* OP_JMP */' ,
'opmode(1, 0, OpArgK, OpArgK, iABC)        /* OP_EQ */' ,
'opmode(1, 0, OpArgK, OpArgK, iABC)        /* OP_LT */' ,
'opmode(1, 0, OpArgK, OpArgK, iABC)        /* OP_LE */' ,
'opmode(1, 1, OpArgR, OpArgU, iABC)        /* OP_TEST */' ,
'opmode(1, 1, OpArgR, OpArgU, iABC)        /* OP_TESTSET */' ,
'opmode(0, 1, OpArgU, OpArgU, iABC)        /* OP_CALL */' ,
'opmode(0, 1, OpArgU, OpArgU, iABC)        /* OP_TAILCALL */' ,
'opmode(0, 0, OpArgU, OpArgN, iABC)        /* OP_RETURN */' ,
'opmode(0, 1, OpArgR, OpArgN, iAsBx)       /* OP_FORLOOP */' ,
'opmode(0, 1, OpArgR, OpArgN, iAsBx)       /* OP_FORPREP */' ,
'opmode(1, 0, OpArgN, OpArgU, iABC)        /* OP_TFORLOOP */' ,
'opmode(0, 0, OpArgU, OpArgU, iABC)        /* OP_SETLIST */' ,
'opmode(0, 0, OpArgN, OpArgN, iABC)        /* OP_CLOSE */' ,
'opmode(0, 1, OpArgU, OpArgN, iABx)        /* OP_CLOSURE */' ,
'opmode(0, 1, OpArgU, OpArgN, iABC)        /* OP_VARARG */' ,
);

class EncryptSetter
{
    private $config;
    private $options;
    private $validated = false;
    private $dateString;

    function __construct(array $config, array $options)
    {
        $this->config = $config;
        $this->options = $options;
    }

    function validateConfig()
    {
        // check system
        if (DS == '/')
        {
            $luacFile = 'bin' . DS . 'mac' . DS . 'luac';
            $frameworkPacker = 'bin' . DS . 'make_framework_package.sh';
        }
        else
        {
            $luacFile = 'bin' . DS . 'win32' . DS . 'luac.exe';
            $frameworkPacker = 'bin' . DS . 'make_framework_package.bat';
        }

        // check quick path
        $quickPath = dirname(BIN_DIR) . DS;
        if (!file_exists($quickPath . 'VERSION'))
        {
            $quickPath = dirname($quickPath) . DS;
            if (!file_exists($quickPath . 'VERSION'))
            {
                printf("File not found in quick's path: VERSION\n");
                printf("ERROR: invalid quick path !!\n");
                return false;
            }
            $luacFile = $quickPath . 'quick' . DS . $luacFile;
            $filePath = $quickPath . 'external/lua/lua/';
        }
        else
        {
            $luacFile = $quickPath . $luacFile;
            $filePath = $quickPath . 'lib/cocos2d-x/scripting/lua/lua/lua-5.1.5/src/';
            $this->config['packer'] = $quickPath . $frameworkPacker;
        }
        if (!file_exists($luacFile))
        {
            printf("File not found: " . $luacFile . "\n");
            printf("ERROR: invalid quick path !!\n");
            return false;
        }

        // check project path
        $defFile = array(
            'lopcodes.def',
            'lopmodes.def',
            );
        $this->config['dst_files'] = array();
        if ($this->config['project'])
        {
            $projPath = rtrim($this->config['project'], "/\\") . DS;
            if (!is_dir($projPath))
            {
                printf("ERROR: invalid project path \"%s\"\n", $projPath);
                return false;
            }
            $filePath = $projPath . 'frameworks/cocos2d-x/external/lua/lua/';
        }
        foreach ($defFile as $i => $f)
        {
            $file = $filePath . $f;
            if (!file_exists($file))
            {
                printf("File not found: " . $file . "\n");
                printf("ERROR: invalid work path !!");
                return false;
            }
            $this->config['dst_files'][$i] = $file;
        }
        $this->config['luac_file'] = $luacFile;
        $this->config['work_path'] = $filePath;
        $this->config['quick_path'] = $quickPath;

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

        // print("file1: " . $this->config['dst_files'][0] . "\n");
        // print("file2: " . $this->config['dst_files'][1] . "\n");
        // print("luac: " . $this->config['luac_file'] . "\n");
        $rnvalue = $this->generateNewDefFiles();

        if ($rnvalue)
        {
            $rnvalue = $this->compileLuac();
        }

        if (!$rnvalue)
        {
            $this->restoreFiles();
            print("\nSorry for failure, please check error logs.\n");
        }
        elseif ($this->config['packer'])
        {
            system($this->config['packer'], $rnvalue);
            print("\nSuccess!\n");
        }

        print("\n\n");

        return $rnvalue;
    }

    function generateNewDefFiles()
    {
        global $lopcodes_str;
        global $lopmodes_str;
        $num = count($lopcodes_str);
        $indexNumbers = range(0, $num-2); //OP_VARARG must be end
        shuffle($indexNumbers);
        $indexNumbers[$num-1] = $num-1;
        $n = $indexNumbers[0];
        $content = array(
            " " . $lopcodes_str[$n],
            " " . $lopmodes_str[$n],
            );
        for ($i=1; $i<$num; $i++)
        { 
            $n = $indexNumbers[$i];
            $content[0] = $content[0] . "\n," . $lopcodes_str[$n];
            $content[1] = $content[1] . "\n," . $lopmodes_str[$n];
        }

        // print($content[0]);
        // print("\n---------\n");
        // print($content[1]);
        // print("\n---------\n");

        date_default_timezone_set("Asia/Chongqing");
        $datestr = date('Ymd-His');

        $this->config['bak_files'] = array();
        for ($i=0; $i<2; $i++)
        { 
            $dstFile = $this->config['dst_files'][$i];
            $bakFile = $dstFile . '_bak_' . $datestr;
            if (rename($dstFile, $bakFile) == false)
            {
                printf("ERROR: rename failure: " . $dstFile . "\n");
                return false;
            }
            $this->config['bak_files'][$i] = $bakFile;

            if (file_put_contents($dstFile, $content[$i]) == false)
            {
                printf("ERROR: file_put_contents failure: " . $dstFile . "\n");
                return false;
            }
        }

        $this->dateString = $datestr;
        return true;
    }

    function compileLuac()
    {
        $workPath = $this->config['work_path'];
        if (DS == '/')
        {
            $build = $workPath . 'build.sh';
            $clean = $workPath . 'clean.sh';
            $target = $workPath . 'luac';
        }
        else
        {
            $build = $workPath . 'build.bat';
            $clean = $workPath . 'clean.bat';
            $target = $workPath . 'luac.exe';
        }
        system($build, $retval);
        if ($retval!=0)
        {
            print("\nError: build error!!\n");
            return false;
        }
        if (!file_exists($target))
        {
            printf("File not found : %s\n", $target);
            print("Error: build error!!\n");
            return false;
        }
        $contents = file_get_contents($target);
        if ($contents == false)
        {
            printf("ERROR: file_get_contents failure for %s\n", $target);
            return false;
        }
        $stat = stat($target);

        $dstFile = $this->config['luac_file'];
        $bakFile = $dstFile . '_bak_' . $this->dateString;
        if (rename($dstFile, $bakFile) == false)
        {
            printf("ERROR: rename failure: %s\n", $dstFile);
            return false;
        }
        $n = count($this->config['dst_files']);
        $this->config['dst_files'][$n] = $dstFile;
        $this->config['bak_files'][$n] = $bakFile;

        if (file_put_contents($dstFile, $contents) == false)
        {
            printf("ERROR: file_put_contents failure: %s\n", $dstFile);
            return false;
        }
        chmod($dstFile, $stat['mode']);

        system($clean, $retval);
        return true;
    }

    function restoreFiles()
    {
        foreach ($this->config['bak_files'] as $i => $file)
        {
            $dstFile = $this->config['dst_files'][$i];
            print("Restore file: " . $dstFile . " from " . $file);
            unlink($dstFile);
            rename($file, $dstFile);
            print("\n");
        }
    }
}
