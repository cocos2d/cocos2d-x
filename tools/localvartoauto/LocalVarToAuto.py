#!/usr/bin/python
# LocalVarToAuto.py
# Change the class name in local variable assignment to auto
# Copyright (c) 2013 cocos2d-x.org
# Author: YuBo

# This script is used for change the class name in local variable assignment to auto.
# Right now there is some poblems you might want notice:
# To start we will assume we has a class A.
# 
# 1. If you have classes like this:
# class B : public A{}; 
# class C : public A{};
# And you write code like this:
# A* b = a_bclass_ptr;
# C* c = new C();
# ...
# b = c;
# We will change it to:
# auto b = a_bclass_ptr;
# auto c = new C();
# It will cause a compile error because you assign pointer with type C to different pointer
# with type B. You must edit it manually.
#
# 2. If your function has default params with class A, we will change it to auto you might
# unexpected. For example:
# void f(A* a = new A()){} or void f(A a = A()){}
#
# 3. If you have define macro like this:
# #define ANOTHER_A_NAME A
# and use it like this:
# ANOTHER_A_NAME* a = new A();
# We will not convert it to auto for you.

import sys
import os.path
import re
import types
import fileinput
import cStringIO

try:
    import PathUtils
except ImportError, e:
    import os.path
    sys.path.append(os.path.abspath("../pylib"))
    import PathUtils

# The cocos root entry. We will aspect it as parent dictionary, all other file or dictionary
# relative path are base on this.
COCOS_ROOT = "../../"
# The class declaration dictionaries, we will search the class declaration with .h files in it.
H_DIR = ("cocos2dx", "CocosDenshion", "extensions")
# The src files you want to edit, we will search the .cpp and .mm files in it.
CXX_DIR = ("Samples",)
# The dictionaries and files with class declaration you don't want to search, you can exclude some third party
# dictionaries in here
EXCLUDE = ("cocos2dx/platform/third_party/",)
# The macroes use with declare class, like "class CC_DLL A{}"
MACROES_WITH_CLASS = ("CC_DLL",)
# The strings represent the null pointer, because you set a point to null, we will not change that
# variable to auto.
NULL_PTR = ("0", "NULL", "nullptr")

# normalize the path
COCOS_ROOT = os.path.abspath(os.path.join(os.curdir, COCOS_ROOT))

def collect_class_name(filename, st):
    "collect all class name appear in the file"
	
    #generate the rep
    if not hasattr(collect_class_name, "rep"):
        repString = cStringIO.StringIO()
        repString.write("(?:\s+|^)class\s+")
        for word in MACROES_WITH_CLASS:
            repString.write(word + "\s+")
        repString.write("(?P<cls_name>\w+)")

        collect_class_name.rep = re.compile(repString.getvalue())
        repString.close()
	
    f = open(os.path.join(COCOS_ROOT, filename))
    try:
        for line in f:
            res = collect_class_name.rep.match(line)
            if res:
                if type(st) == type(set()):
                    st.add(res.group("cls_name"))
    finally:
        f.close()

def change_local_classvarname_to_auto(filename, rep, change):
    "change all local class variable name to auto"
    f = open(filename)
	
    content = None
    changed = False
    # read the file, change it, and save it to content
    try:
        content = cStringIO.StringIO()
        changed = False

        for line in f:
            i = 0
            #start to replace
            while True:
                result = rep.match(line, i)
                # founded
                if result:
                    changed = True
                    #find the matched string where to start
                    startIndex = line.index(result.group(0))
                    #replace the change part
                    line = line.replace(result.group(change), "auto ", startIndex)
                    i += 1
                else:
                    break
            #write the result to content
            content.write(line)
    finally:
        f.close()
        if changed:
            f = open(filename, "w")
            f.write(content.getvalue())
            f.close()
        content.close()

def main():

    print ".......VARIABLES......."
    print "COCOS_ROOT:",
    print COCOS_ROOT
    print "H_DIR:",
    print H_DIR
    print "CXX_DIR:",
    print CXX_DIR
    print "EXCLUDE:",
    print EXCLUDE
    print ".......VARIABLES END......"

    utils = PathUtils.PathUtils(COCOS_ROOT)
    # save the .h file for search
    hfiles = utils.find_files(H_DIR, ("h",), EXCLUDE)
    # save the .cpp and .mm file for search
    cxxfiles = utils.find_files(CXX_DIR, ("cpp", "mm"))

    print "search class declarations"
    # the class set, ignore the namespace
    classes = set()
    for file in hfiles:
        collect_class_name(file, classes)
    print "search end"

    # generate example rep:
    # (\W+|^)(?P<keyWord>\S*(?:Class1|Class2|class3)\s*(?:\*+|\s+)\s*)\w+\s*=(?!\s*(?:0|NULL|nullptr)\s*\W)
    # examples:
    # Class1* c = new Class1() ; //match
    # Class1* c;                 //not match
    # Class1* c = nullptr;       //not match
    # Class1* c = nullptrabc;    //match
    # Class1 c;                  //not match
    # Class1 c = Class1();       //match
    def gen_rep(keyWord):
        s = cStringIO.StringIO()
        s.write("(?:\W+|^)(?P<")
        s.write(keyWord)
        s.write(">(?:")

        # add classes want to match
        first = True
        for cls in classes:
            if first:
                first = False
            else:
                s.write("|")

            s.write(cls)

        s.write(")\s*(?:\*+|\s+)\s*)\w+\s*=(?!\s*(?:")

        # let nullptr assignment not to convert
        first = True
        for nullptr in NULL_PTR:
            if first:
                first = False
            else:
                s.write("|")

            s.write(nullptr)

        s.write(")\s*\W)")

        result = s.getvalue()
        s.close()

        print "generated regular expression is:"
        print result
        return re.compile(result)
	
    repWord = "change"
    rep = gen_rep(repWord)


    print "scan and edit the .cxx files..."
    # scan the cxx files
    for file in cxxfiles:
        change_local_classvarname_to_auto(os.path.join(COCOS_ROOT, file), rep, repWord)
 	
    print "success!"
	

if __name__ == "__main__":
    main()

