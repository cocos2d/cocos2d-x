#!/usr/bin/python
# create_project.py
# Create cross-platform cocos2d-x project
# Copyright (c) 2012 cocos2d-x.org
# Author: WangZhe

# define global variables
context = {
    "input"        : "undefined",
    "output"       : "undefined",
    "cocos2d"      : "undefined",
}

# begin
import sys
import os, os.path

def dumpUsage():
    print "Usage: generate-config.py -input INPUT_PATH -output OUTPUT_PATH -cocos2d COCOS2D_ROOT_PATH"
    print "Options:"
    print "  -intput    INPUT_PATH            The path to javscript files directory"
    print "  -output    OUTPUT_PATH           The path to the obfuscated javascript file"
    print "  -cocos2d   COCOS2D_ROOT_PATH     The root path of cocos2d-x, e.g. /workspace/cocos2d-x"
    print ""

def checkParams():
    # generate our internal params
    context["script_path"] = os.getcwd() + "/"
    
    if len(sys.argv) < 4:
        dumpUsage()
        sys.exit()
        
    # fine params
    for i in range(1, len(sys.argv)):
        if "-input" == sys.argv[i]:
            context["input"] = sys.argv[i+1]
        elif "-output" == sys.argv[i]:
            context["output"] = os.getcwd() + "/" + sys.argv[i+1] 
        elif "-cocos2d" == sys.argv[i]:
            context["cocos2d"] = sys.argv[i+1]
            
    # pinrt error log our required paramters are not ready
    raise_error = False
    if context["input"] == "undefined":
        print "Invalid -input parameter"
        raise_error = True
    if context["output"] == "undefined":
        print "Invalid -output parameter"
        raise_error = True
    if context["cocos2d"] == "undefined":
        print "Invalid -cocos2d parameter"
        raise_error = True
    if raise_error != False:
        sys.exit()
# end of checkParams

class FileInfo:
    def __init__(self, filename, filepath):
        self.filename = filename
        self.filepath = filepath

def getFiles(currentDir):
    files = {
        "js"    : [],
        "other" : [],
    }
    for root, dirs, file_list in os.walk(currentDir): # Walk directory tree
        for f in file_list:
            if f.find(".js") != -1:
                files["js"].append(FileInfo(f, root))
            else:
                files["other"].append(FileInfo(f, root))
    return files
# end of getInfos

def prepareConfigs():
    config = {
        "path_to_compiler": "undefiend",
        "path_to_excludes": "undefined",
        "path_to_sources": "undefined",
        "sources": [],
    }
    
    config["path_to_compiler"] = context["cocos2d"] + "/tools/closure-compiler/compiler.jar"
    config["path_to_excludes"] = context["cocos2d"] + "/scripting/javascript/bindings/obfuscate"
    config["path_to_sources"] = "./" # don't use context["input"] here
    config["path_to_output"] = context["output"] + "main.js"
    config["js_files"] = ""
    
    files = getFiles( context["input"] )
            
    for item in files["js"]:
        config["js_files"] += "<file name=\"" + item.filepath + "/" + item.filename + "\"/>" + "\n\t\t\t\t" 
    
    return config
# end of prepareConfigs

def generateXmlForCompiler():    
    print "preparing configs..."
    config = prepareConfigs()
    print "generating obfuscate.xml for google closure compiler"
    f1 = open(context["cocos2d"] + "tools/closure-compiler/template.xml", "rb")
    tmp = f1.read()
    f1.close()
    from string import Template
    s = Template(tmp)
    content = s.substitute( PATH_TO_COMPILER = config["path_to_compiler"],
                            PATH_TO_EXCLUDES = config["path_to_excludes"],
                            PATH_TO_OUTPUT   = config["path_to_output"],
                            PATH_TO_SOURCES  = config["path_to_sources"],
                            JS_FILES         = config["js_files"] )

    f2 = open(context["output"] + "obfuscate.xml", "wb")
    f2.write(content)
    f2.close()
# end of generateXmlForCompiler

# main
checkParams()
generateXmlForCompiler()
print "running ant to generate obfuscated main.js"
os.popen("ant -buildfile obfuscate.xml")
print "done!"

