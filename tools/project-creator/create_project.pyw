#!/usr/bin/python
# create_project.py
#coding=utf-8
# Create cross-platform cocos2d-x project
# Copyright (c) 2012 cocos2d-x.org
# Author: chuanwei

import sys

# ------------ main --------------
if __name__ == '__main__':
    """
    There have double ways to create cocos project.
    1.UI
    2.console
        #create_project.py --help
        #create_project.py -n MyGame -k com.MyCompany.AwesomeGame -l javascript -p c:/mycompany
    """
    if len(sys.argv)==1:
        from module.ui import createTkCocosDialog
        createTkCocosDialog()
    else:
        from module.core import CocosProject
        project = CocosProject()
        name, package, language, path = project.checkParams()
        project.createPlatformProjects(name, package, language, path)

