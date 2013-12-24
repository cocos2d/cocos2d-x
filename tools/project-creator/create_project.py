#!/usr/bin/python
# create_project.py
#coding=utf-8
# Create cross-platform cocos2d-x project
# Copyright (c) 2012 cocos2d-x.org
# Author: chuanwei

import sys
from module.ui import TkProjectDialog
from module.core import CocosProject

# ------------ main --------------
if __name__ == '__main__':
    if len(sys.argv)==1:
        TkProjectDialog()
    else:
        project = CocosProject()
        name, package, language, path = project.checkParams()
        project.createPlatformProjects(name, package, language, path)

