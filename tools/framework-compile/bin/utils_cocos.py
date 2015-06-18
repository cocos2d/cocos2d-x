#!/usr/bin/python
#-*- coding: UTF-8 -*-

import os
import sys
import shutil

if sys.platform == 'win32':
    import _winreg

def execute_command(cmdstring, cwd=None, timeout=None, shell=True):
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

    #if os_is_win32():
    #    cmdstring = convert_to_python_path(cmdstring)

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

def get_required_vs_version(proj_file):
        # Now VS2012 is the mini version required
        return "11.0"

def get_vs_cmd_path(vs_reg, proj_path, vs_version):
    # get required vs version
    required_vs_version = get_required_vs_version(proj_path)
    if required_vs_version is None:
        raise Exception("Can't parse the sln file to find required VS version")

    # get the correct available VS path
    needUpgrade = False
    vsPath = None

    if vs_version is None:
        i = 0
        try:
            while True:
                version = _winreg.EnumKey(vs_reg, i)
                try:
                    if float(version) >= float(required_vs_version):
                        key = _winreg.OpenKey(vs_reg, r"SxS\VS7")
                        vsPath, type = _winreg.QueryValueEx(key, version)

                        if float(version) > float(required_vs_version):
                            needUpgrade = True

                        key.close()
                        break
                except:
                    pass
                i += 1
        except WindowsError:
            pass
    else:
        if vs_version == 2012:
            vs_ver = "11.0"
            needUpgrade = False
        else:
            vs_ver = "12.0"
            needUpgrade = True

        try:
            key = _winreg.OpenKey(vs_reg, r"SxS\VS7")
            vsPath, type = _winreg.QueryValueEx(key, vs_ver)
        except:
            raise Exception("Can't find VS%d" % vs_version)

    if vsPath is None:
        message = "Can't find correct Visual Studio's path in the regedit"
        raise Exception(message)

    commandPath = os.path.join(vsPath, "Common7", "IDE", "devenv")
    return (commandPath, needUpgrade)

def rmdir(folder):
    if os.path.exists(folder):
        if sys.platform == 'win32':
            execute_command("rd /s/q %s" % folder)
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



