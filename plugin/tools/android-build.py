#!/usr/bin/python
# android-build.py
# Build android samples

import sys
import os, os.path
import shutil
from optparse import OptionParser

CPP_SAMPLES = ["HelloPlugins"]
ALL_SAMPLES = CPP_SAMPLES

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
    'jsb' for short of all javascript samples
    '''

    if 'all' in args:
        return ALL_SAMPLES

    if 'jsb' in args:
        return JSB_SAMPLES

    if 'cpp' in args:
        return CPP_SAMPLES

    targets = []
    targets += args

    # remove duplicate elements, for example
    # python android-build.py cpp hellocpp
    targets = set(targets)
    return list(targets)

def do_build(plugin_root, cocos_root, ndk_root, app_android_root, ndk_build_param):

    ndk_path = os.path.join(ndk_root, "ndk-build")

    # windows should use ";" to seperate module paths
    platform = sys.platform
    if platform == 'win32':
        ndk_module_path = 'NDK_MODULE_PATH=%s/publish;%s;%s/external;%s/cocos' % (plugin_root, cocos_root, cocos_root, cocos_root)
    else:
        ndk_module_path = 'NDK_MODULE_PATH=%s/publish:%s:%s/external:%s/cocos' % (plugin_root, cocos_root, cocos_root, cocos_root)

    if ndk_build_param == None:
        command = '%s -C %s %s' % (ndk_path, app_android_root, ndk_module_path)
    else:
        command = '%s -C %s %s %s' % (ndk_path, app_android_root, ndk_build_param, ndk_module_path)
    os.system(command)

def copy_files(src, dst):

    for item in os.listdir(src):
        path = os.path.join(src, item)
        # Android can not package the file that ends with ".gz"
        if not item.startswith('.') and not item.endswith('.gz') and os.path.isfile(path):
            shutil.copy(path, dst)
        if os.path.isdir(path):
            new_dst = os.path.join(dst, item)
            if not os.path.exists(new_dst):
                os.mkdir(new_dst)
            copy_files(path, new_dst)

def copy_resources(target, app_android_root, plugin_root):

    # remove app_android_root/assets if it exists
    assets_dir = os.path.join(app_android_root, "assets")
    if os.path.isdir(assets_dir):
        shutil.rmtree(assets_dir)

    # copy resources(cpp samples and lua samples)
    os.mkdir(assets_dir)
    resources_dir = os.path.join(app_android_root, "../Resources")
    if os.path.isdir(resources_dir):
        copy_files(resources_dir, assets_dir)

    # jsb samples should copy javascript files and resources(shared with cocos2d-html5)
    # if target in JSB_SAMPLES:
    #     resources_dir = os.path.join(app_android_root, "../../../../cocos/scripting/javascript/script")
    #     copy_files(resources_dir, assets_dir)
    #     resources_dir = os.path.join(plugin_root, "jsbindings/js")
    #     copy_files(resources_dir, assets_dir)

    # copy plugin resources to the assets
    plugins_dir = os.path.join(plugin_root, "publish" + os.path.sep + "plugins")
    for item in os.listdir(plugins_dir):
        src = os.path.join(plugins_dir, item + os.path.sep + "android" + os.path.sep + "ForAssets")
        if os.path.isdir(src):
            copy_files(src, assets_dir)

def copy_clibs(app_android_root, plugin_root):
    target_cpath = os.path.join(app_android_root, "libs")
    plugins_dir = os.path.join(plugin_root, "publish" + os.path.sep + "plugins")
    for item in os.listdir(plugins_dir):
        src = os.path.join(plugins_dir, item + os.path.sep + "android" + os.path.sep + "CLibs")
        if os.path.isdir(src):
            if not os.path.exists(target_cpath):
                os.mkdir(target_cpath)
            copy_files(src, target_cpath)

def build_samples(target,ndk_build_param):

    ndk_root = check_environment_variables()
    select_toolchain_version()
    build_targets = caculate_built_samples(target)

    current_dir = os.path.dirname(os.path.realpath(__file__))
    cocos_root = os.path.join(current_dir, "../../")
    plugin_root = os.path.join(current_dir, "..")

    app_android_root = ''
    for target in build_targets:
        app_android_root = os.path.join(plugin_root, "samples" + os.path.sep + target + os.path.sep + "proj.android")

        copy_resources(target, app_android_root, plugin_root)
        do_build(plugin_root, cocos_root, ndk_root, app_android_root, ndk_build_param)
        copy_clibs(app_android_root, plugin_root)

# -------------- main --------------
if __name__ == '__main__':

    usage = "usage: %prog all"

    #parse the params
    parser = OptionParser(usage=usage)
    parser.add_option("-n", "--ndk", dest="ndk_build_param", 
    help='parameter for ndk-build')
    (opts, args) = parser.parse_args()

    if len(args) == 0:
        parser.print_help()
    else:
        build_samples(args, opts.ndk_build_param)
