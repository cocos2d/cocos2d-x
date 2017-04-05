#!/usr/bin/python

import os
import sys

ret = 0
genbindings_dirs = ['tolua', 'tojs']
for item in genbindings_dirs:
    os.chdir("tools/" + item)
    ret = os.system('python genbindings.py')
    os.chdir("../..")
    if(ret != 0):
        ret = 1
        break

sys.exit(ret)
