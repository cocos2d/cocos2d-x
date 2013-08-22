#!/usr/bin/python

import sys
import os
import os.path
import cStringIO

try:
    import PathUtils
except ImportError, e:
    import os.path
    sys.path.append(os.path.abspath("../pylib"))
    import PathUtils

COCOS_ROOT = "../../"

COCOS_ROOT = os.path.abspath(os.path.join(os.curdir, COCOS_ROOT))

def gen_android_mk(tplfile, outfile, pathes, suffix = ("cpp",), exclude = ()):
    ""
    utils = PathUtils.PathUtils(os.path.abspath(COCOS_ROOT))
    filelst = utils.find_files(pathes, suffix, exclude)

    filestr = cStringIO.StringIO()
    for filename in filelst:
        filestr.write(' \\\n')
        filestr.write(os.path.relpath(filename, os.path.dirname(os.path.join(COCOS_ROOT, outfile))))

    file = open(tplfile)
    template = file.read()
    file.close()

    file = open(os.path.join(COCOS_ROOT, outfile), "w")
    print >>file, template %(filestr.getvalue())
    file.close()

    filestr.close()

def main():
    #generate cocos2d
    gen_android_mk("./cocos2d_template.mk", "cocos2dx/Android.mk", ["cocos2dx/"], ["c",  "cpp"], ["cocos2dx/platform/android", "cocos2dx/platform/emscripten", "cocos2dx/platform/ios", "cocos2dx/platform/linux", "cocos2dx/platform/mac", "cocos2dx/platform/nacl", "cocos2dx/platform/qt5", "cocos2dx/platform/tizen", "cocos2dx/platform/win32", "cocos2dx/label_nodes/CCFontCache.cpp", "cocos2dx/base_nodes/CCGLBufferedNode.cpp","cocos2dx/support/user_default/CCUserDefault.cpp"])
    #generate cpptest
    gen_android_mk("./cpptest_template.mk", "samples/Cpp/TestCpp/Android.mk", ["samples/Cpp/TestCpp/Classes"])
    #generate extensions
    gen_android_mk("./extensions_template.mk", "extensions/Android.mk", ["extensions/"], ["cpp"], ["extensions/proj.win32", "extensions/proj.emscripten", "extensions/proj.ios", "extensions/proj.linux", "extensions/proj.mac", "extensions/proj.nacl", "extensions/proj.qt5", "extensions/proj.tizen", ])

if __name__ == "__main__":
    sys.exit(main())