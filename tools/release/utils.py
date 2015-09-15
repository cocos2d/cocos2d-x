#!/usr/bin/env python
# -*- coding: utf-8 -*-
__author__ = 'Bill Zhang'

import shlex
import datetime
import subprocess
import time
import os
import re
import zipfile

def execute_command(cmdstring, cwd=None, timeout=None, shell=True):

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

    return str(sub.returncode)

def get_src_engine_version(engine_path):
    file_path = os.path.join(engine_path, "cocos/cocos2d.cpp")
    pattern = r".*return[ \t]+\"(.*)\";"

    # restore the version of engine
    ver = ""
    f = open(file_path)
    for line in f.readlines():
        match = re.match(pattern, line)
        if match:
            ver = match.group(1)
            break
    f.close()

    if len(ver) <= 0:
        raise Exception("Can't find version in %s" % file_path)

    return ver

def zip_dir(dirname, zipfilename):
    print("zip directory %s to file %s" % (dirname, zipfilename))
    filelist = []
    if os.path.isfile(dirname):
        filelist.append(dirname)
    else :
        for root, dirs, files in os.walk(dirname):
            for name in files:
                filelist.append(os.path.join(root, name))

    zf = zipfile.ZipFile(zipfilename, "w", zipfile.zlib.DEFLATED)
    for tar in filelist:
        arcname = tar[len(dirname):]
        zf.write(tar,arcname)
    zf.close()
