#!/usr/bin/python

import sys
import os
import os.path
import cStringIO
import re

def get_cur_dir():
    path = sys.path[0]
    if os.path.isdir(path):
        return path
    elif os.path.isfile(path):
        return os.path.dirname(path)

CUR_DIR = get_cur_dir()
COCOS_ROOT = os.path.abspath(os.path.join(CUR_DIR, "../../"))
CONFIG = os.path.abspath(os.path.join(CUR_DIR, "./config.py"))
# print 'CONFIG:' + CONFIG
# print 'COCOS_ROOT:' + COCOS_ROOT

try:
    import PathUtils
except ImportError, e:
    sys.path.append(os.path.abspath(os.path.join(CUR_DIR, "../pylib")))
    import PathUtils



def gen_android_mk(mkfile, pathes, suffix = ("c", "cpp",), exclude = ()):
    utils = PathUtils.PathUtils(COCOS_ROOT)
    filelst = utils.find_files(pathes, suffix, exclude)

    # generate file list string
    filestrio = cStringIO.StringIO()
    mkfilepath = os.path.dirname(os.path.join(COCOS_ROOT, mkfile))
    for filename in filelst:
        filestrio.write(' \\\n')
        filepath = os.path.relpath(filename, mkfilepath)
        filestrio.write(filepath.replace('\\', '/'))
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
    config = open(CONFIG)
    params = eval(config.read())
    config.close()
    
    for param in params:
        gen_android_mk(**param)

if __name__ == "__main__":
    from optparse import OptionParser

    parser = OptionParser()

    parser.add_option('-c', '--config',
                      type='string',
                      dest='config',
                      help="config file path.")

    parser.add_option('-r', '--rootpath',
                      action='store',
                      dest='rootpath',
                      help='class root path for mkfile, pathes, exclude.')

    options, args = parser.parse_args()

    if options.config:
        CONFIG = os.path.abspath(os.path.join(os.curdir, options.config))

    if options.rootpath:
        COCOS_ROOT = os.path.abspath(os.path.join(os.curdir, options.rootpath))

    # print 'CONFIG:', CONFIG
    # print 'COCOS_ROOT:', COCOS_ROOT

    error = ''
    if not os.path.isfile(CONFIG):
        error+='config must be file.\n'

    if not os.path.isdir(COCOS_ROOT):
        error+='rootpath must be directory.\n'

    if error != '':
        parser.exit(2, "{exception}".format(exception=error))
    
    sys.exit(main())
