import os
import sys

def check_ret(ret):
    if(ret != 0):
        os.system('git checkout -B develop remotes/origin/develop')
        os.system('git clean -xdf -f')
        sys.exit(1)

branchs = ['develop', 'master']
for item in branchs:
    os.system('git clean -xdf -f')
    os.system('git checkout -B ' + item + ' remotes/origin/' + item)
    os.system('git clean -xdf -f')
    ret = os.system('git pull origin')
    check_ret(ret)
    ret = os.system('git submodule update --init --force')
    check_ret(ret)

#back to develop
os.system('git checkout -B develop remotes/origin/develop')
os.system('git clean -xdf -f')
