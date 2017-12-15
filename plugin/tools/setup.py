#!/usr/bin/python
#coding=utf-8

import sys
import os

def _check_python_version():
    major_ver = sys.version_info[0]
    if major_ver > 2:
        print ("The python version is %d.%d. But python 2.x is required. (Version 2.7 is well tested)\n"
               "Download it here: https://www.python.org/" % (major_ver, sys.version_info[1]))
        return False

    return True

def create_env_file(path):
	NDK_ROOT = os.environ.get('NDK_ROOT')
	ANDROID_SDK_ROOT = os.environ.get('ANDROID_SDK_ROOT')
	ANT_ROOT = os.environ.get('ANT_ROOT')

	f = file(path, "w+")
	f.write("export ANDROID_NDK_ROOT=" + NDK_ROOT + "\n")
	f.write("export ANDROID_SDK_ROOT=" + ANDROID_SDK_ROOT + "\n")
	f.write("export ANT_PATH=" + ANT_ROOT + "\n")
	f.write("export INPUT_SDK_PATH=" + ANDROID_SDK_ROOT + "\n")
	f.close()

def setup_env():
	# check if environment.sh exists
	env_file = "./toolsForPublish/environment.sh"

	if not os.path.isfile(env_file):
		create_env_file(env_file)

if __name__ == '__main__':
    if not _check_python_version():
        exit()

    setup_env()
