#!/usr/bin/python
# android-build.py
# Build android samples

# You can use


# begin
import sys
import os, os.path
from optparse import OptionParser

CPP_SAMPLES = ['hellocpp', 'testcpp', 'simplegame', 'assetsmanager']
LUA_SAMPLES = ['hellolua', 'testlua']
JSB_SAMPLES = ['cocosdragon', 'crystalcraze', 'moonwarriors', 'testjavascript', 'watermelonwithme']
ALL_SAMPLES = CPP_SAMPLES + LUA_SAMPLES + JSB_SAMPLES


def usage():

    print "%prog [-n ndk-build-parameter] target\n\
    valid target are [hellocpp|testcpp|simplegame|assetsmanager|hellolua|testlua|cocosdragon\
|crystalcraze|moonwarriors|testjavascript|watermelonwithme], of course you can use 'cpp'\
to build all cpp samples, 'lua' to build all lua samples, 'jsb' to build all javascript samples,\
 and 'all' for all samples" 

def check_environment_variables():
    ''' Checking the environment NDK_ROOT, which will be used for building
    '''

    try:
        NDK_ROOT = os.environ['NDK_ROOT']
    except Exception:
        print "NDK_ROOT not defined. Please define NDK_ROOT in your environment"
        sys.exit(1)

    return NDK_ROOT

def select_toolchain_version():
    '''Because ndk-r8e uses gcc4.6 as default. gcc4.6 doesn't support c++11. So we should select gcc4.7 when
    using ndk-r8e. But gcc4.7 is removed in ndk-r9, so we should determine whether gcc4.7 exist.
    Conclution:
    ndk-r8e  -> use gcc4.7
    ndk-r9   -> use gcc4.8
    '''

    ndk_root = check_environment_variables()
    if os.path.isdir(os.path.join(ndk_root,"toolchains/arm-linux-androideabi-4.8")):
        os.environ['NDK_TOOLCHAIN_VERSION'] = '4.8'
        print "The Selected NDK toolchain version was 4.8 !"
    elif os.path.isdir(os.path.join(ndk_root,"toolchains/arm-linux-androideabi-4.7")):
        os.environ['NDK_TOOLCHAIN_VERSION'] = '4.7'
        print "The Selected NDK toolchain version was 4.7 !"
    else:
        print "Couldn't find the gcc toolchain."
        exit(1)

def caculate_built_samples(args):
    ''' Compute the sampels to be built
    'cpp' for short of all cpp samples
    'lua' for short of all lua smpleas
    'jsb' for short of all javascript samples
    '''

    if 'all' == args:
        return ALL_SAMPLES

    targets = []
    if 'cpp' in args:
        targets += CPP_SAMPLES
        args.remove('cpp')
    if 'lua' in args:
        targets += LUA_SAMPLES
        args.remove('lua')
    if 'jsb' in args:
        targets += JSB_SAMPLES
        args.remove('jsb')

    targets += args

    # remove duplicate elements, for example
    # python android-build.py cpp hellocpp
    targets = set(targets)
    return list(targets)

def do_build(cocos_root, ndk_root, app_android_root, ndk_build_param):

    ndk_path = os.path.join(ndk_root, "ndk-build")

    # windows should use ";" to seperate module paths
    platform = sys.platform
    if platform == 'win32':
        ndk_module_path = 'NDK_MODULE_PATH=%s;%s/external;%s/cocos' % (cocos_root, cocos_root, cocos_root)
    else:
        ndk_module_path = 'NDK_MODULE_PATH=%s:%s/external:%s/cocos' % (cocos_root, cocos_root, cocos_root)

    if ndk_build_param == None:
        command = '%s -C %s %s' % (ndk_path, app_android_root, ndk_module_path)
    else:
        command = '%s -C %s %s %s' % (ndk_path, app_android_root, ndk_build_param, ndk_module_path)
    os.system(command)

def build_samples(target,ndk_build_param):

    ndk_root = check_environment_variables()
    select_toolchain_version()
    build_targets = caculate_built_samples(target)

    current_dir = os.getcwd()
    cocos_root = os.path.join(current_dir, "..")

    app_android_root = ''
    for target in build_targets:
        if target == 'hellocpp':
            app_android_root = os.path.join(cocos_root, 'samples/Cpp/HelloCpp/proj.android')
        elif target == 'testcpp':
            app_android_root = os.path.join(cocos_root, 'samples/Cpp/TestCpp/proj.android')
        elif target == 'simplegame':
            app_android_root = os.path.join(cocos_root, 'samples/Cpp/SimpleGame/proj.android')
        elif target == 'assetsmanager':
            app_android_root = os.path.join(cocos_root, 'samples/Cpp/AssetsManager/proj.android')
        elif target == 'hellolua':
            app_android_root = os.path.join(cocos_root, 'samples/Lua/HelloLua/proj.android')
        elif target == 'testlua':
            app_android_root = os.path.join(cocos_root, 'samples/Lua/TestLua/proj.android')
        elif target == 'cocosdragon':
            app_android_root = os.path.join(cocos_root, 'samples/JavaScript/CocosDragonJS/proj.android')
        elif target == 'crystalcraze':
            app_android_root = os.path.join(cocos_root, 'samples/JavaScript/CrystalCraze/proj.android')
        elif target == 'moonwarriors':
            app_android_root = os.path.join(cocos_root, 'samples/JavaScript/MoonWarriors/proj.android')
        elif target == 'testjavascript':
            app_android_root = os.path.join(cocos_root, 'samples/JavaScript/TestJavascript/proj.android')
        elif target == 'watermelonwithme':
            app_android_root = os.path.join(cocos_root, 'samples/JavaScript/WatermelonWithMe/proj.android')
        else:
            print 'unknown target %s, pass it', target
            continue

        do_build(cocos_root, ndk_root, app_android_root, ndk_build_param)

# -------------- main --------------
if __name__ == '__main__':

    #parse the params
    parser = OptionParser()
    parser.add_option("-n", "--ndk", dest="ndk_build_param", help='parameter for ndk-build')
    (opts, args) = parser.parse_args()

    if len(args) == 0:
        usage()
    else:
        build_samples(args, opts.ndk_build_param)
