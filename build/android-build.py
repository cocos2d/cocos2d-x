#!/usr/bin/python
# android-build.py
# Build android

import sys
import os, os.path
from optparse import OptionParser

CPP_SAMPLES = ['cpp-empty-test', 'cpp-tests', 'game-controller-test']
LUA_SAMPLES = ['lua-empty-test', 'lua-tests', 'lua-game-controller-test']
JS_SAMPLES = ['js-tests']
ALL_SAMPLES = CPP_SAMPLES + LUA_SAMPLES + JS_SAMPLES

def calculate_built_samples(args):
    ''' Calculate build targets from the list of targets passed on command line.
    'all' for all tests
    'cpp' for all c++ tests
    'lua' for all lua tests
    'js' for all javascript tests
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
    if 'js' in args:
        targets += JS_SAMPLES
        args.remove('js')

    targets += args

    # remove duplicate elements, for example
    # python android-build.py cpp hellocpp
    targets = set(targets)
    return list(targets)

def do_build(app_android_root, build_mode, app_abi, platform):

    command = 'cocos compile -p android -s %s --ndk-mode %s --app-abi %s' % (app_android_root, build_mode, app_abi)
    if platform:
        command += ' --ap %s' % platform
    print command

    if os.system(command) != 0:
        raise Exception("Build dynamic library for project [ " + app_android_root + " ] failed!")

def build_samples(target, build_mode, app_abi, api_level):

    if build_mode is None:
        build_mode = 'debug'
    elif build_mode != 'release':
        build_mode = 'debug'

    if app_abi is None:
        app_abi = 'armeabi-v7a'

    if api_level:
        platform = 'android-%s' % api_level
    else:
        platform = None

    build_targets = calculate_built_samples(target)

    app_android_root = ''

    target_proj_path_map = {
        "cpp-empty-test": "tests/cpp-empty-test",
        "game-controller-test": "tests/game-controller-test",
        "cpp-tests": "tests/cpp-tests",
        "lua-empty-test": "tests/lua-empty-test",
        "lua-tests": "tests/lua-tests",
        "lua-game-controller-test": "tests/lua-game-controller-test",
        "js-tests": "tests/js-tests"
    }

    cocos_root = os.path.join(os.path.dirname(os.path.realpath(__file__)), "..")

    for target in build_targets:
        if target in target_proj_path_map:
            app_android_root = os.path.join(cocos_root, target_proj_path_map[target])
        else:
            print 'unknown target: %s' % target
            continue

        do_build(app_android_root, build_mode, app_abi, platform)

# -------------- main --------------
if __name__ == '__main__':

    #parse the params
    usage = '''%prog [options] [cpp-empty-test|cpp-tests|lua-empty-test|lua-tests|js-tests|cpp|lua|js|all...]

    This script is mainly used for building tests built-in with cocos2d-x.

    If you are new to cocos2d-x, we recommend you to start with cpp-empty-test or lua-empty-test.

    You can combine targets like this:

    python android-build.py cpp-empty-test lua-empty-test'''

    parser = OptionParser(usage=usage)
    parser.add_option('-n', '--ndk', dest='app_abi',
                      help='Specifies Android ABI (default is armeabi-v7a).')
    parser.add_option('-p', '--platform', dest='api_level',
                      help='Specifies Android API Level.')
    parser.add_option('-b', '--build', dest='build_mode',
                      help='The build mode for java project,debug[default] or release. ' +
                      'To get more information, please refer to ' +
                      'http://developer.android.com/tools/building/building-cmdline.html')
    (opts, args) = parser.parse_args()

    if len(args) == 0:
        parser.print_help()
        sys.exit(1)
    else:
        try:
            build_samples(args, opts.build_mode, opts.app_abi, opts.api_level)
        except Exception as e:
            print e
            sys.exit(1)
