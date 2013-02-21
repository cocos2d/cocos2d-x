#!/usr/bin/python
# handle_project_files.py for Mac OS X
# Copyright (c) 2012 cocos2d-x.org
# Author: WangZhe

# Mac OS X

import os
import shutil

def handle_project_files(context):
    # determine proj_path
    proj_path = context["dst_project_path"] + "/proj.mac/"
        
    # rename files and folders
    os.rename(proj_path + context["src_project_name"] + ".xcodeproj",
              proj_path + context["dst_project_name"] + ".xcodeproj" )
              
    # remove useless files.
    removes = [
        context["dst_project_name"] + ".xcodeproj/project.xcworkspace",
        context["dst_project_name"] + ".xcodeproj/xcuserdata",
    ]
    for i in range(0, len(removes)):
        if (os.path.exists(proj_path + removes[i]) == True):
            shutil.rmtree(proj_path + removes[i])
 
    # replaceString function is implemented in ../create-project.py
    import replaces
    # package_name should be replaced at first. Don't change this sequence
    replaces.replaceString(proj_path + "Info.plist",
                           context["src_package_name"], context["dst_package_name"])
    replaces.replaceString(proj_path + context["dst_project_name"] + ".xcodeproj/project.pbxproj",
                           context["src_project_name"], context["dst_project_name"])
    replaces.replaceString(proj_path + "Info.plist",
                           context["src_project_name"], context["dst_project_name"])

    # done!
    print "proj.mac         : Done!"