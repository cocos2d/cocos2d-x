#!/usr/bin/env python

# android-build.py
# Build android

import sys
import os, os.path

CPP_SAMPLES = ['cpp-empty-test', 'cpp-tests', 'game-controller-test']
LUA_SAMPLES = ['lua-empty-test', 'lua-tests', 'lua-game-controller-test']
JS_SAMPLES = ['js-tests']
ALL_SAMPLES = CPP_SAMPLES + LUA_SAMPLES + JS_SAMPLES


def calculate_build_targets(args):
    ''' Calculate build targets from list of targets passed on command line.
    'all' for all tests
    'cpp' for all c++ tests
    'lua' for all lua tests
    'js' for all javascript tests
    '''

    targets = []
    for arg in args:
        if arg == 'all':
            targets += ALL_SAMPLES
        elif arg == 'cpp':
            targets += CPP_SAMPLES
        elif arg == 'lua':
            targets += LUA_SAMPLES
        elif arg == 'js':
            targets += JS_SAMPLES
        else:
            targets.append(arg)

    # remove duplicates
    targets = set(targets)
    return targets


def do_build(app_android_root, build_mode, app_abi, platform):

    command = 'cocos compile -p android -s %s --ndk-mode %s --app-abi %s' % (app_android_root, build_mode, app_abi)
    if platform:
        command += ' --ap %s' % platform
    print command

    if os.system(command) != 0:
        raise Exception('Build dynamic library for project [ %s ] failed!' % app_android_root)


def build_targets(targets, build_mode, app_abi, api_level):

    if api_level:
        platform = 'android-%s' % api_level
    else:
        platform = None

    build_targets = calculate_build_targets(targets)

    app_android_root = ''

    cocos_root = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..')

    for target in build_targets:
        app_android_root = os.path.join(cocos_root, 'tests', target)
        do_build(app_android_root, build_mode, app_abi, platform)


def main():
    from argparse import ArgumentParser, RawTextHelpFormatter

    description = '''
    This script is mainly used for building tests built-in with cocos2d-x.

    If you are new to cocos2d-x, we recommend you to start with cpp-empty-test or lua-empty-test.'''

    parser = ArgumentParser(description=description, formatter_class=RawTextHelpFormatter)
    parser.add_argument('-n', '--ndk', dest='app_abi', default='armeabi-v7a',
                        help='specifies Android ABI')
    parser.add_argument('-p', '--platform', dest='api_level',
                        help='specifies Android API Level')
    parser.add_argument('-b', '--build', dest='build_mode', metavar='BUILD_MODE', default='debug', choices=['debug', 'release'],
                        help='the build mode for java project, debug (default) or release. ' +
                        'To get more information, please refer to ' +
                        'http://developer.android.com/tools/building/building-cmdline.html')
    parser.add_argument('targets', nargs='+', metavar='targets',
                        help='targets to build. A target is one of [cpp-empty-test|cpp-tests|lua-empty-test|lua-tests|js-tests|cpp|lua|js|all]',
                        choices=['cpp-empty-test', 'cpp-tests', 'lua-empty-test', 'lua-tests', 'js-tests', 'cpp', 'lua', 'js', 'all'])
    args = parser.parse_args()

    try:
        build_targets(args.targets, args.build_mode, args.app_abi, args.api_level)
    except Exception as e:
        print e
        sys.exit(1)


if __name__ == '__main__':
    main()
