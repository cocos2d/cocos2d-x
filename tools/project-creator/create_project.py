#!/usr/bin/python
# create_project.py
# Create cross-platform cocos2d-x project
# Copyright (c) 2012 cocos2d-x.org
# Author: WangZhe

# define global variables
context = {
"language"          : "undefined",
"src_project_name"  : "undefined",
"src_package_name"  : "undefined", 
"dst_project_name"  : "undeifned",
"dst_package_name"  : "undefined",
"src_project_path"  : "undefined",
"dst_project_path"  : "undefined",
"script_dir"        : "undefined",
}
platforms_list = []

# begin
import sys
import os, os.path
import shutil # for copy folders and files

def dumpUsage():
    print "Usage: create-project.py -project PROJECT_NAME -package PACKAGE_NAME -language PROGRAMING_LANGUAGE"
    print "Options:"
    print "  -project   PROJECT_NAME          Project name, for example: MyGame"
    print "  -package   PACKAGE_NAME          Package name, for example: com.MyCompany.MyAwesomeGame"
    print "  -language  PROGRAMING_LANGUAGE   Major programing lanauge you want to used, should be [cpp | lua | javascript]"
    print ""
    print "Sample 1: ./create_project.py -project MyGame -package com.MyCompany.AwesomeGame"
    print "Sample 2: ./create_project.py -project MyGame -package com.MyCompany.AwesomeGame -language javascript"
    print ""

def checkParams(context):
    # generate our internal params
    context["script_dir"] = os.getcwd() + "/"
    global platforms_list
    
    # invalid invoke, tell users how to input params
    if len(sys.argv) < 7:
        dumpUsage()
        sys.exit()
    
    # find our params
    for i in range(1, len(sys.argv)):
        if "-project" == sys.argv[i]:
            # read the next param as project_name
            context["dst_project_name"] = sys.argv[i+1]
            context["dst_project_path"] = os.getcwd() + "/../../projects/" + context["dst_project_name"]
        elif "-package" == sys.argv[i]:
            # read the next param as g_PackageName
            context["dst_package_name"] = sys.argv[i+1]
        elif "-language" == sys.argv[i]:
            # choose a scripting language
            context["language"] = sys.argv[i+1]
    
    # pinrt error log our required paramters are not ready
    raise_error = False
    if context["dst_project_name"] == "undefined":
        print "Invalid -project parameter"
        raise_error = True
    if context["dst_package_name"] == "undefined":
        print "Invalid -package parameter"
        raise_error = True
    if context["language"] == "undefined":
        print "Invalid -language parameter"
        raise_error = True
    if raise_error != False:
        sys.exit()
                                 
    # fill in src_project_name and src_package_name according to "language"
    if ("cpp" == context["language"]):
        context["src_project_name"] = "HelloCpp"
        context["src_package_name"] = "org.cocos2dx.hellocpp"
        context["src_project_path"] = os.getcwd() + "/../../template/multi-platform-cpp"
        platforms_list = ["ios",
                          "android",
                          "win32",
                          "mac",
                          "blackberry",
                          "linux",
                          "marmalade"]
    elif ("lua" == context["language"]):
        context["src_project_name"] = "HelloLua"
        context["src_package_name"] = "org.cocos2dx.hellolua"
        context["src_project_path"] = os.getcwd() + "/../../template/multi-platform-lua"
        platforms_list = ["ios",
                          "android",
                          "win32"]
    elif ("javascript" == context["language"]):
        context["src_project_name"] = "HelloJavascript"
        context["src_package_name"] = "org.cocos2dx.hellojavascript"
        context["src_project_path"] = os.getcwd() + "/../../template/multi-platform-js"
        platforms_list = ["ios",
                          "android",
                          "win32"]
# end of checkParams(context) function


# -------------- main --------------
# dump argvs
# print sys.argv

# prepare valid "context" dictionary
checkParams(context)
# import pprint
# pprint.pprint(context)

# copy "lauguage"(cpp/lua/javascript) platform.proj into cocos2d-x/projects/<project_name>/folder
if (os.path.exists(context["dst_project_path"]) == True):
    print "Error:" + context["dst_project_path"] + " folder is already existing"
    print "Please remove the old project or choose a new PROJECT_NAME in -project parameter"
    sys.exit()
else:
    shutil.copytree(context["src_project_path"], context["dst_project_path"], True)

# call process_proj from each platform's script folder          
for platform in platforms_list:
    exec "import %s.handle_project_files" % (platform)
    exec "%s.handle_project_files.handle_project_files(context)" % (platform)

print "New project has been created in this path: " + context["dst_project_path"].replace("/tools/project-creator/../..", "")
print "Have Fun!"

