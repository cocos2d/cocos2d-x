#!/usr/bin/python
# replaces.py
# Copyright (c) 2012 cocos2d-x.org
# Author: WangZhe

def replaceString(filepath, src_string, dst_string):
    content = ""
    f1 = open(filepath, "r")
    for line in f1:
        if src_string in line:
            content += line.replace(src_string, dst_string)
        else:
            content += line
    f1.close()
    f2 = open(filepath, "w")
    f2.write(content)
    f2.close()
# end of replaceString(filepath, src, dst) function

