#!/usr/bin/python
# handle_project_files.py for iOS
# Copyright (c) 2012 cocos2d-x.org
# Author: WangZhe

# iOS

import os

def handle_project_files(context):
    # determine proj_path
    proj_path = context["dst_project_path"] + "/proj.ios/"
    
    # determine src_package_name & dst_package_name
    if ("cpp" == context["language"]):
        context["src_package_name"] = "org.cocos2d-x.HelloCpp"
    elif ("lua" == context["language"]):
        context["src_package_name"] = "org.cocos2d-x.HelloLua"
    elif ("javascript" == context["language"]):
        context["src_package_name"] = "org.cocos2d-x.HelloJavascript"
    
    # rename files and folders
    os.rename(proj_path + context["src_project_name"] + ".xcodeproj",
              proj_path + context["dst_project_name"] + ".xcodeproj" )
              
    # remove useless files.
    os.popen("rm -rf " + proj_path + context["dst_project_name"] + ".xcodeproj/project.xcworkspace")
    os.popen("rm -rf " + proj_path + context["dst_project_name"] + ".xcodeproj/xcuserdata" )
    os.popen("rm -rf " + proj_path + "build" )

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
    print "proj.ios         : Done!"