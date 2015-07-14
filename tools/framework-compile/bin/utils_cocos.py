#!/usr/bin/python
#-*- coding: UTF-8 -*-

import os
import sys
import shutil

if sys.platform == 'win32':
    import _winreg

def os_is_win32():
    return sys.platform == 'win32'

def is_32bit_windows():
    arch = os.environ['PROCESSOR_ARCHITECTURE'].lower()
    archw = os.environ.has_key("PROCESSOR_ARCHITEW6432")
    return (arch == "x86" and not archw)

def os_is_mac():
    return sys.platform == 'darwin'

def convert_to_python_path(path):
    return path.replace("\\","/")

def execute_command(cmdstring, cwd=None, timeout=None, shell=True, use_py_path=True):
    """ 执行一个SHELL命令
        封装了subprocess的Popen方法, 支持超时判断，支持读取stdout和stderr
        参数:
        cwd: 运行命令时更改路径，如果被设定，子进程会直接先更改当前路径到cwd
        timeout: 超时时间，秒，支持小数，精度0.1秒
        shell: 是否通过shell运行
        Returns: return_code
        Raises:  Exception: 执行超时
    """

    import shlex
    import datetime
    import subprocess
    import time

    if os_is_win32() and use_py_path:
        cmdstring = convert_to_python_path(cmdstring)

    print("")
    print("Execute command:")
    print(cmdstring)
    print("")

    if shell:
        cmdstring_list = cmdstring
    else:
        cmdstring_list = shlex.split(cmdstring)
    if timeout:
        end_time = datetime.datetime.now() + datetime.timedelta(seconds=timeout)

    # 没有指定标准输出和错误输出的管道,因此会打印到屏幕上
    sub = None
    try:
        sub = subprocess.Popen(cmdstring_list, cwd=cwd, stdin=subprocess.PIPE, shell=shell, bufsize=4096)
    except Exception as e:
        print("execute command fail:%s" % cmdstring)
        raise e

    # subprocess.poll()方法：检查子进程是否结束了，如果结束了，设定并返回码，放在subprocess.returncode变量中
    while sub.poll() is None:
        time.sleep(0.1)
        if timeout:
            if end_time <= datetime.datetime.now():
                raise Exception("Timeout：%s"%cmdstring)

    if 0 != sub.returncode :
        errStr = "[ERROR] execute command fail:%s" % cmdstring
        print(errStr)
        raise Exception(errStr)

    return sub.returncode

def get_vs_cmd_path(vs_version):
    if vs_version == 2013:
        vs_ver = "12.0"
    elif vs_version == 2015:
        vs_ver = "14.0"
    else:
        # not supported VS version
        return None

    # If the system is 64bit, find VS in both 32bit & 64bit registry
    # If the system is 32bit, only find VS in 32bit registry
    if is_32bit_windows():
        reg_flag_list = [ _winreg.KEY_WOW64_32KEY ]
    else:
        reg_flag_list = [ _winreg.KEY_WOW64_64KEY, _winreg.KEY_WOW64_32KEY ]

    # Find VS path
    msbuild_path = None
    for reg_flag in reg_flag_list:
        try:
            vs = _winreg.OpenKey(
                _winreg.HKEY_LOCAL_MACHINE,
                r"SOFTWARE\Microsoft\MSBuild\ToolsVersions\%s" % vs_ver,
                0,
                _winreg.KEY_READ | reg_flag
            )
            msbuild_path, type = _winreg.QueryValueEx(vs, 'MSBuildToolsPath')
        except:
            continue

        if msbuild_path is not None and os.path.exists(msbuild_path):
            break

    # generate devenv path
    if msbuild_path is not None:
        commandPath = os.path.join(msbuild_path, "MSBuild.exe")
    else:
        commandPath = None

    return commandPath

def rmdir(folder):
    if os.path.exists(folder):
        if sys.platform == 'win32':
            execute_command("rd /s/q \"%s\"" % folder)
        else:
            shutil.rmtree(folder)

def mkdir(folder):
    if not os.path.exists(folder):
        os.makedirs(folder)

def cpdir(source, dest):
    source_dir = source
    dest_dir = dest

    if not os.path.exists(source_dir):
        raise Exception("cpdir source_dir (%s) not exists" % source_dir)

    mkdir(dest_dir)

    for f in os.listdir(source_dir):
        path = os.path.join(source_dir, f)
        if os.path.isfile(path):
            shutil.copy(path, dest_dir)
        elif os.path.isdir(path):
            new_dest = os.path.join(dest_dir, f)
            cpdir(path, new_dest)

def win2unix(filePath):
    try:
        oldfile = open(filePath, "rb+")
        path, name = os.path.split(filePath)
        newfile = open(path + '$' + name, "wb+")

        old = b'\r'
        new = b''

        data = b''
        while (True):
            data = oldfile.read(200)
            newData = data.replace(old, new)
            newfile.write(newData)
            if len(data) < 200:
                break
        newfile.close()
        oldfile.close()

        os.remove(filePath)
        os.rename(path + '$' + name, filePath)
    except IOError as e:
        print(e)

def copy_files_with_cb(src, dst, cb):
    for item in os.listdir(src):
        path = os.path.join(src, item)
        if os.path.isfile(path):
            if cb is None:
                shutil.copy(path, dst)
            else:
                cb(path, dst)
        if os.path.isdir(path):
            new_dst = os.path.join(dst, item)
            if not os.path.isdir(new_dst):
                os.makedirs(new_dst)
            copy_files_with_cb(path, new_dst, cb)



