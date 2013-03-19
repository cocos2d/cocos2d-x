#!/usr/bin/python
# create_project.py
# Create cross-platform cocos2d-x project
# Copyright (c) 2012 cocos2d-x.org
# Author: WangZhe

# define global variables
context = {
    "input"        : "/workspace/cocos2d-x/samples/Javascript/Shared/tests",
    "output"       : "/workspace/cocos2d-x/samples/Javascript/TestJavascript/main.js",
    "cocos2d"      : "/workspace/cocos2d-x",
}

# begin
import sys
import os, os.path

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
    config["path_to_sources"] = context["input"]
    config["path_to_output"] = context["output"]
    config["js_files"] = ""
    
    files = getFiles( context["input"] )
            
    for item in files["js"]:
        folder = item.filepath.lstrip(config["path_to_sources"])
        if folder == "":
            tmp = "<file name=\"" + item.filename + "\"/>" + "\n\t\t\t\t"
        else:
            tmp = "<file name=\"" + folder + "/" + item.filename + "\"/>" + "\n\t\t\t\t"
            
        config["js_files"] += tmp
    
    return config
# end of prepareConfigs

def generateXmlForCompiler():    
    config = prepareConfigs()
    
    f1 = open(os.getcwd() + "/config_template.xml", "rb")
    content = ""
    for line in f1:
        if "$PATH_TO_COMPILER" in line:
            content += line.replace("$PATH_TO_COMPILER", config["path_to_compiler"])
        elif "$PATH_TO_EXCLUDES" in line:
            content += line.replace("$PATH_TO_EXCLUDES", config["path_to_excludes"])
        elif "$PATH_TO_OUTPUT_FILE" in line:
            content += line.replace("$PATH_TO_OUTPUT_FILE", config["path_to_output"])
        elif "$PATH_TO_SOURCES" in line:
            content += line.replace("$PATH_TO_SOURCES", config["path_to_sources"])
        elif "$JS_FILES" in line:
            content += line.replace("$JS_FILES", config["js_files"])
        else:
            content += line
    
    f1.close()
    f2 = open(os.getcwd() + "/obfuscate.xml", "wb")
    f2.write(content)
    f2.close()

# end of dump

generateXmlForCompiler()