#!/usr/bin/python

import os

genbindings_dirs = ['tojs', 'tolua']
for item in genbindings_dirs:
    os.chdir("tools/" + item)
    os.system('python genbindings.py')
    os.chdir("../..")
