#!/usr/bin/env python2.7
# coding=utf-8

from xml.etree import ElementTree
import json
import os
import sys

def setAndroidOrientation(orientation):
        dir_path = os.path.dirname(__file__)
        filePath = os.path.join(dir_path,"frameworks/runtime-src/proj.android/AndroidManifest.xml")
        try:
            androidNS = "http://schemas.android.com/apk/res/android"
            ElementTree.register_namespace("android", androidNS)
            tree = ElementTree.parse(filePath)
            print tree
            root = tree.getroot()
            #androidNS = root.nsmap["android"]
            screenOrientation = "{%s}screenOrientation" %(androidNS)
            for element in root.getiterator("activity"):
                print element.attrib
                if orientation:
                    element.attrib[screenOrientation] = "landscape"
                else:
                    element.attrib[screenOrientation] = "portrait"

            tree.write(filePath, encoding = "utf-8", xml_declaration = True)
        except Exception:
            print("parser %s file failure" % filePath)

def setConfigJson(name,viewWith,viewHeight):
    dir_path = os.path.dirname(__file__)
    filePath = os.path.join(dir_path,"res/config.json")
    try:
        f = open(filePath)
        cfg_content = json.load(f)
        f.close()
        if cfg_content.has_key("init_view"):
            if name:
                cfg_content["init_view"]["name"] = name
            if viewWith:
                cfg_content["init_view"]["width"] = viewWith
            if viewHeight:
                cfg_content["init_view"]["height"] = viewHeight
        else:
            initViewObject={}
            if name:
                initViewObject["name"] = name
            if viewWith:
                initViewObject["width"] = viewWith
            if viewHeight:
                initViewObject["height"] = viewHeight
            cfg_content["init_view"] = initViewObject
        f = open(filePath,"w")
        json.dump(cfg_content,f,indent=4)
        f.close()

    except Exception:
        if f is not None:
            f.close()
        print("parser %s file failure!" % filePath)

 # parse arguments
def parse_args():
        """Custom and check param list.
        """
        from argparse import ArgumentParser
        parser = ArgumentParser(description="Init project configure", epilog="This is a epilog of %(prog)s")
        parser.add_argument("-n", "--name", metavar="VIEW_NAME", help="Set view name")
        parser.add_argument("-w", "--width", metavar="VIEW_WIDTH", help="Init view size for width")
        parser.add_argument("-i", "--hight", metavar="VIEW_HEIGHT", help="Init view size for height")
        parser.add_argument("--landscape", action="store_true", dest="no_native", help="Set screen Orientation")
        args = parser.parse_args()

        setConfigJson(args.name,args.width,args.hight)
        setAndroidOrientation(args.landscape)

if __name__ == '__main__':
    parse_args()



