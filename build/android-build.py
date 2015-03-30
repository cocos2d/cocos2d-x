#!/usr/bin/python
# android-build.py
# Build android

import sys
import os, os.path
import shutil
from optparse import OptionParser

CPP_SAMPLES = ['cpp-empty-test', 'cpp-tests', 'game-controller-test']
LUA_SAMPLES = ['lua-empty-test', 'lua-tests', 'lua-game-controller-test']
ALL_SAMPLES = CPP_SAMPLES + LUA_SAMPLES

def caculate_built_samples(args):
    ''' Compute the sampels to be built
    'cpp' for short of all cpp tests
    'lua' for short of all lua tests
    '''

    if 'all' in args:
        return ALL_SAMPLES

    targets = []
    if 'cpp' in args:
        targets += CPP_SAMPLES
        args.remove('cpp')
    if 'lua' in args:
        targets += LUA_SAMPLES
        args.remove('lua')

    targets += args

    # remove duplicate elements, for example
    # python android-build.py cpp hellocpp
    targets = set(targets)
    return list(targets)

def do_build(app_android_root, build_mode):
     
    command = 'cocos compile -p android -s %s --ndk-mode %s' % (app_android_root, build_mode) 
    print command

    if os.system(command) != 0:
        raise Exception("Build dynamic library for project [ " + app_android_root + " ] fails!")

def build_samples(target, build_mode):

    if build_mode is None:
        build_mode = 'debug'
    elif build_mode != 'release':
        build_mode = 'debug'
    
    build_targets = caculate_built_samples(target)

    app_android_root = ''

    target_proj_path_map = {
        "cpp-empty-test": "tests/cpp-empty-test",
        "game-controller-test": "tests/game-controller-test",
        "cpp-tests": "tests/cpp-tests",
        "lua-empty-test": "tests/lua-empty-test",
        "lua-tests": "tests/lua-tests",
        "lua-game-controller-test": "tests/lua-game-controller-test"
    }

    cocos_root = os.path.join(os.path.dirname(os.path.realpath(__file__)), "..")

    for target in build_targets:
        if target in target_proj_path_map:
            app_android_root = os.path.join(cocos_root, target_proj_path_map[target])
        else:
            print 'unknown target: %s' % target
            continue

        do_build(app_android_root, build_mode)

# -------------- main --------------
if __name__ == '__main__':

    #parse the params
    usage = """
    This script is mainy used for building tests built-in with cocos2d-x.

    Usage: %prog [options] [cpp-empty-test|cpp-tests|lua-empty-test|lua-tests|cpp|lua|all]

    If you are new to cocos2d-x, I recommend you start with cpp-empty-test, lua-empty-test.

    You can combine these targets like this:

    python android-build.py cpp-empty-test lua-empty-test

    """

    parser = OptionParser(usage=usage)
    parser.add_option("-n", "--ndk", dest="ndk_build_param",
    help='It is not used anymore, because cocos console does not support it.')
    parser.add_option("-p", "--platform", dest="android_platform",
    help='This parameter is not used any more, just keep compatible.')
    parser.add_option("-b", "--build", dest="build_mode",
    help='The build mode for java project,debug[default] or release. Get more information,please refer to http://developer.android.com/tools/building/building-cmdline.html')
    (opts, args) = parser.parse_args()
    
    if len(args) == 0:
        parser.print_help()
        sys.exit(1)
    else:
        try:
            build_samples(args, opts.build_mode)
        except Exception as e:
            print e
            sys.exit(1)
