#!/usr/bin/python
# obfuscate.py
# Create Ant buildfile to obfuscate game source code
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
    print "Usage: %s -input INPUT_PATH -output OUTPUT_PATH -cocos2d COCOS2D_ROOT_PATH" % (os.path.basename(__file__))
    print "Options:"
    print "  -input     INPUT_PATH            The path to javascript files directory"
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
        "path_to_cocos2d": context["cocos2d"],
        "path_to_output": context["output"] + "game.js",
        "path_to_js_sources": context["input"],
        "js_sources": "",
    }
        
    files = getFiles( context["input"] )
            
    for item in files["js"]:
        # use item.filepath and item.filename
        fullpath = item.filepath.replace(config["path_to_js_sources"], "")
        if (len(fullpath) != 0):
            fullpath += "/"
        # end of if len(tmp)
        fullpath += item.filename
        config["js_sources"] += "<file name=\"" + fullpath + "\"/>" + "\n\t\t\t\t" 
    
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
    content = s.substitute( PATH_TO_COCOS2D      = config["path_to_cocos2d"],
                            PATH_TO_COMPILER     = "${basedir}/tools/closure-compiler/compiler.jar",
                            PATH_TO_OUTPUT       = config["path_to_output"],
                            PATH_TO_EXCLUSIONS   = "${basedir}/scripting/javascript/bindings/obfuscate",
                            PATH_TO_JS_FRAMEWORK = "${basedir}/scripting/javascript/bindings/js/",
                            PATH_TO_JS_SOURCES   = os.getcwd() + "/" + config["path_to_js_sources"],
                            JS_SOURCES           = config["js_sources"] )

    f2 = open(context["output"] + "obfuscate.xml", "wb")
    f2.write(content)
    f2.close()
# end of generateXmlForCompiler

# main
checkParams()
generateXmlForCompiler()
# print "running ant to generate obfuscated main.js"
# os.popen("ant -buildfile obfuscate.xml")
print "Successful! obfuscate.xml generated."
print "Note: Please reorder the file's sequence in obfuscate.xml, keep it the same order as javascript \"require\" instruction,"
print "then call \"ant -buildfile obfuscate.xml\" to obfuscate your js code."

