#!/usr/bin/python
# handle_project_files.py for Android
# Copyright (c) 2012 cocos2d-x.org
# Author: WangZhe

# Android

import os

def handle_project_files(context):    
    # determine proj_path
    proj_path = context["dst_project_path"] + "/proj.android/"
    
    # determine src_package_name & dst_package_name
    if ("cpp" == context["language"]):
        context["src_package_name"] = "org.cocos2dx.hellocpp"
    elif ("lua" == context["language"]):
        context["src_package_name"] = "org.cocos2dx.hellolua"
    elif ("javascript" == context["language"]):
        context["src_package_name"] = "org.cocos2dx.hellojavascript"
                  
    # rename files and folders
    src_pkg = context["src_package_name"].split('.')
    dst_pkg = context["dst_package_name"].split('.')

    os.rename(proj_path + "src/" + src_pkg[0],
              proj_path + "src/" + dst_pkg[0])
    os.rename(proj_path + "src/" + dst_pkg[0] + "/" + src_pkg[1],
              proj_path + "src/" + dst_pkg[0] + "/" + dst_pkg[1])
    os.rename(proj_path + "src/" + dst_pkg[0] + "/" + dst_pkg[1] + "/" + src_pkg[2],
              proj_path + "src/" + dst_pkg[0] + "/" + dst_pkg[1] + "/" + dst_pkg[2])
    os.rename(proj_path + "src/" + dst_pkg[0] + "/" + dst_pkg[1] + "/" + dst_pkg[2] + "/HelloJavascript.java",
              proj_path + "src/" + dst_pkg[0] + "/" + dst_pkg[1] + "/" + dst_pkg[2] + "/" + context["dst_project_name"] + ".java")

    dst_java_file_path = proj_path + "src/" + dst_pkg[0] + "/" + dst_pkg[1] + "/" + dst_pkg[2] + "/" + context["dst_project_name"] + ".java"
      
    
    # remove useless files.
    os.popen("rm -rf " + proj_path + "assets")
    os.popen("rm -rf " + proj_path + "bin")
    os.popen("rm -rf " + proj_path + "gen")
    os.popen("rm -rf " + proj_path + "obj")

    # replaceString function is implemented in ../create-project.py
    import replaces
    # package_name should be replaced at first. Don't change this sequence
    replaces.replaceString(proj_path + "AndroidManifest.xml",   context["src_package_name"], context["dst_package_name"])
    replaces.replaceString(proj_path + "ndkgdb.sh",             context["src_package_name"], context["dst_package_name"])
    replaces.replaceString(dst_java_file_path,  context["src_package_name"], context["dst_package_name"])     
     
    replaces.replaceString(proj_path + ".project",              context["src_project_name"], context["dst_project_name"])
    replaces.replaceString(proj_path + "AndroidManifest.xml",   context["src_project_name"], context["dst_project_name"])
    replaces.replaceString(proj_path + "build.xml",             context["src_project_name"], context["dst_project_name"])
    replaces.replaceString(proj_path + "build_native.sh",       context["src_project_name"], context["dst_project_name"])
    replaces.replaceString(proj_path + "ndkgdb.sh",             context["src_project_name"], context["dst_project_name"])
    replaces.replaceString(proj_path + "res/values/strings.xml",context["src_project_name"], context["dst_project_name"])
    replaces.replaceString(dst_java_file_path,  context["src_project_name"], context["dst_project_name"])
    # done!
    print "proj.android     : Done!"
