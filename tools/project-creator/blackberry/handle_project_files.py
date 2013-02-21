#!/usr/bin/python
# handle_project_files.py for BlackBerry
# Copyright (c) 2012 cocos2d-x.org
# Author: Zhe WANG

# BlackBerry

import os
import shutil

def handle_project_files(context):    
    # determine proj_path
    proj_path = context["dst_project_path"] + "/proj.blackberry/"
                        
    # replaceString function is implemented in ../create-project.py
    import replaces

    replaces.replaceString(proj_path + "bar-descriptor.xml", context["src_package_name"], context["dst_package_name"]) 
    
    replaces.replaceString(proj_path + ".cproject", context["src_project_name"], context["dst_project_name"]) 
    replaces.replaceString(proj_path + ".project",  context["src_project_name"], context["dst_project_name"])
    replaces.replaceString(proj_path + "bar-descriptor.xml",  context["src_project_name"], context["dst_project_name"])

    # done!
    print "proj.blackberry  : Done!"
