#!/usr/bin/python
# create_project.py
# Create cross-platform cocos2d-x project
# Copyright (c) 2012 cocos2d-x.org
# Author: WangZhe

# define global variables
PLATFORMS = {
    "cpp" : ["ios", "android", "win32", "mac", "linux"],
    "lua" : ["ios", "android", "win32", "mac","linux"],
    "javascript" : ["ios", "android", "win32"]
}


# begin
import sys
import os, os.path
import json
import shutil

def checkParams():
    from optparse import OptionParser
    
    # set the parser to parse input params
    # the correspond variable name of "-x, --xxx" is parser.xxx
    parser = OptionParser(usage="Usage: ./%prog -p <PROJECT_NAME> -k <PACKAGE_NAME> -l <cpp|lua|javascript>\nSample: ./%prog -p MyGame -k com.MyCompany.AwesomeGame -l javascript")
    parser.add_option("-p", "--project", metavar="PROJECT_NAME", help="Set a project name")
    parser.add_option("-k", "--package", metavar="PACKAGE_NAME", help="Set a package name for project")
    parser.add_option("-l", "--language",
                      metavar="PROGRAMMING_NAME",
                      type="choice",
                      choices=["cpp", "lua", "javascript"],
                      help="Major programing language you want to used, should be [cpp | lua | javascript]")
    
    #parse the params
    (opts, args) = parser.parse_args()

    # generate our internal params
    context = {}.fromkeys(("language", "src_project_name", "src_package_name", "dst_project_name", "dst_package_name", "src_project_path", "dst_project_path", "script_dir"))
    platforms_list = []

    context["script_dir"] = os.path.abspath(os.path.dirname(__file__))
    
    if opts.project:
        context["dst_project_name"] = opts.project
        context["dst_project_path"] = os.path.abspath(os.path.join(context["script_dir"], "..", "..", "projects", context["dst_project_name"]))
    else:
        parser.error("-p or --project is not specified")

    if opts.package:
        context["dst_package_name"] = opts.package
    else:
        parser.error("-k or --package is not specified")

    if opts.language:
        context["language"] = opts.language
    else:
        parser.error("-l or --language is not specified")
                                 
    # fill in src_project_name and src_package_name according to "language"
    template_dir = os.path.abspath(os.path.join(context["script_dir"], "..", "..", "template"))
    if ("cpp" == context["language"]):
        context["src_project_name"] = "HelloCpp"
        context["src_package_name"] = "org.cocos2dx.hellocpp"
        context["src_project_path"] = os.path.join(template_dir, "multi-platform-cpp")
    elif ("lua" == context["language"]):
        context["src_project_name"] = "HelloLua"
        context["src_package_name"] = "org.cocos2dx.hellolua"
        context["src_project_path"] = os.path.join(template_dir, "multi-platform-lua")
    elif ("javascript" == context["language"]):
        context["src_project_name"] = "HelloJavascript"
        context["src_package_name"] = "org.cocos2dx.hellojavascript"
        context["src_project_path"] = os.path.join(template_dir, "multi-platform-js")
    platforms_list = PLATFORMS.get(context["language"], [])
    return context, platforms_list
# end of checkParams(context) function

def replaceString(filepath, src_string, dst_string):
	content = ""
	f1 = open(filepath, "rb")
	for line in f1:
		strline = line.decode('utf8')
		if src_string in strline:
			content += strline.replace(src_string, dst_string)
		else: 
			content += strline
	f1.close()
	f2 = open(filepath, "wb")
	f2.write(content.encode('utf8'))
	f2.close()
# end of replaceString

def processPlatformProjects(context, platform):
    # determine proj_path
    proj_path = os.path.join(context["dst_project_path"], "proj." + platform)
    java_package_path = ""

    # read json config file for the current platform
    conf_path = os.path.join(context["script_dir"], "%s.json" % platform)
    f = open(conf_path)
    data = json.load(f)

    # rename package path, like "org.cocos2dx.hello" to "com.company.game". This is a special process for android
    if platform == "android":
        src_pkg = context["src_package_name"].split('.')
        dst_pkg = context["dst_package_name"].split('.')

        java_package_path = os.path.join(*dst_pkg)

    # remove useless files and folders
    for item in data["remove"]:
        dst = item.replace("PROJECT_NAME", context["dst_project_name"])
        if os.path.exists(os.path.join(proj_path, dst)):
            shutil.rmtree(os.path.join(proj_path, dst))
    
    # rename package_name. This should be replaced at first. Don't change this sequence
    for item in data["replace_package_name"]:
        tmp = item.replace("PACKAGE_PATH", java_package_path)
        dst = tmp.replace("PROJECT_NAME", context["dst_project_name"])
        if os.path.exists(os.path.join(proj_path, dst)):
            replaceString(os.path.join(proj_path, dst), context["src_package_name"], context["dst_package_name"])
    
    # rename project_name
    for item in data["replace_project_name"]:
        tmp = item.replace("PACKAGE_PATH", java_package_path)
        dst = tmp.replace("PROJECT_NAME", context["dst_project_name"])
        if os.path.exists(os.path.join(proj_path, dst)):
            replaceString(os.path.join(proj_path, dst), context["src_project_name"], context["dst_project_name"])
                  
    # done!
    print ("proj.%s\t\t: Done!" % platform)
# end of processPlatformProjects

def createPlatformProjects(): 
    # prepare valid "context" dictionary
    context, platforms_list  = checkParams()
    # print context, platforms_list

    # copy "lauguage"(cpp/lua/javascript) platform.proj into cocos2d-x/projects/<project_name>/folder
    if os.path.exists(context["dst_project_path"]):
        print ("Error:" + context["dst_project_path"] + " folder is already existing")
        print ("Please remove the old project or choose a new PROJECT_NAME in -project parameter")
        sys.exit()
    else:
        shutil.copytree(context["src_project_path"], context["dst_project_path"], True)

    # call process_proj from each platform's script folder          
    for platform in platforms_list:
        processPlatformProjects(context, platform)
    #    exec "import %s.handle_project_files" % (platform)
    #    exec "%s.handle_project_files.handle_project_files(context)" % (platform)

    print ("New project has been created in this path: " + context["dst_project_path"].replace("/tools/project-creator/../..", ""))
    print ("Have Fun!")





# -------------- main --------------
# dump argvs
# print sys.argv
if __name__ == '__main__':
    createPlatformProjects()

