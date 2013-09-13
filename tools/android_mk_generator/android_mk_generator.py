#!/usr/bin/python

import sys
import os
import os.path
import cStringIO
import re

try:
    import PathUtils
except ImportError, e:
    sys.path.append(os.path.abspath(os.path.join(os.curdir, "../pylib")))
    import PathUtils

COCOS_ROOT = "../../"

COCOS_ROOT = os.path.abspath(os.path.join(os.curdir, COCOS_ROOT))

def gen_android_mk(mkfile, pathes, suffix = ("c", "cpp",), exclude = ()):
    utils = PathUtils.PathUtils(COCOS_ROOT)
    filelst = utils.find_files(pathes, suffix, exclude)

    # generate file list string
    filestrio = cStringIO.StringIO()
    for filename in filelst:
        filestrio.write(' \\\n')
        filestrio.write(os.path.relpath(filename, os.path.dirname(os.path.join(COCOS_ROOT, mkfile))))
    filestrio.write('\n')
    
    # read mk file
    file = open(os.path.join(COCOS_ROOT, mkfile))
    mkstrio = cStringIO.StringIO()
    rep = re.compile("\s*LOCAL_SRC_FILES\s*:=")
    try:
        # read lines before encounter "LOCAL_EXPORT_C_INCLUDES"
        for line in file:
            if rep.match(line):
                mkstrio.write("LOCAL_SRC_FILES :=")
                break
            else:
                mkstrio.write(line)
    #mkstrio.write('\n')

        # write file list
        mkstrio.write(filestrio.getvalue())

        # write remaining lines
        delete = True if line[len(line) - 2] == '\\' else False
        for line in file:
            if delete:
                delete = True if line[len(line) - 2] == '\\' else False
            else:
                mkstrio.write(line)
#mkstrio.write('\n')
    finally:
        file.close()



    file = open(os.path.join(COCOS_ROOT, mkfile), "w")
    file.write(mkstrio.getvalue())
    file.close()

    filestrio.close()
    mkstrio.close()

def main():
    config = open("./config.py")
    params = eval(config.read())
    config.close()
    
    for param in params:
        gen_android_mk(**param)

if __name__ == "__main__":
    sys.exit(main())