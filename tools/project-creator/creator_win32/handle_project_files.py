#!/usr/bin/python
# handle_project_files.py for Win32
# Copyright (c) 2012 cocos2d-x.org
# Author: WangZhe

# Win32

import os

def handle_project_files(context):    
    # determine proj_path
    proj_path = context["dst_project_path"] + "/proj.win32/"
                      
    # rename files and folders
    os.rename(proj_path + context["src_project_name"] + ".vcxproj",
              proj_path + context["dst_project_name"] + ".vcxproj")
    os.rename(proj_path + context["src_project_name"] + ".vcxproj.filters",
              proj_path + context["dst_project_name"] + ".vcxproj.filters")
    os.rename(proj_path + context["src_project_name"] + ".vcxproj.user",
              proj_path + context["dst_project_name"] + ".vcxproj.user")
    
    # replaceString function is implemented in ../create-project.py
    import replaces
    # package_name should be replaced at first. Don't change this sequence
    replaces.replaceString(proj_path + context["dst_project_name"] + ".vcxproj",         context["src_project_name"], context["dst_project_name"])
    replaces.replaceString(proj_path + context["dst_project_name"] + ".vcxproj.filters", context["src_project_name"], context["dst_project_name"])
    replaces.replaceString(proj_path + context["dst_project_name"] + ".vcxproj.user",    context["src_project_name"], context["dst_project_name"])
    replaces.replaceString(proj_path + "main.cpp",    context["src_project_name"], context["dst_project_name"])
    # done!
    print "proj.win32       : Done!"
