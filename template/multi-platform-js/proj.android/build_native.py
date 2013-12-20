#!/usr/bin/python
# build_native.py
# Build native codes


import sys
import os, os.path
import shutil


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

def do_build(cocos_root, ndk_root, app_android_root):

    ndk_path = os.path.join(ndk_root, "ndk-build")

    # windows should use ";" to seperate module paths
    platform = sys.platform
    if platform == 'win32':
        ndk_module_path = 'NDK_MODULE_PATH=%s;%s/external;%s/cocos' % (cocos_root, cocos_root, cocos_root)
    else:
        ndk_module_path = 'NDK_MODULE_PATH=%s:%s/external:%s/cocos' % (cocos_root, cocos_root, cocos_root)

    ndk_build_param = sys.argv[1:]
    if len(ndk_build_param) == 0:
        command = '%s -C %s %s' % (ndk_path, app_android_root, ndk_module_path)
    else:
        command = '%s -C %s %s %s' % (ndk_path, app_android_root, ''.join(str(e) for e in ndk_build_param), ndk_module_path)
    os.system(command)

def copy_files(src, dst):

    for item in os.listdir(src):
        path = os.path.join(src, item)
        # Android can not package the file that ends with ".gz"
        if not item.startswith('.') and not item.endswith('.gz') and os.path.isfile(path):
            shutil.copy(path, dst)
        if os.path.isdir(path):
            new_dst = os.path.join(dst, item)
            os.mkdir(new_dst)
            copy_files(path, new_dst)

def copy_resources(app_android_root):

    # remove app_android_root/assets if it exists
    assets_dir = os.path.join(app_android_root, "assets")
    if os.path.isdir(assets_dir):
        shutil.rmtree(assets_dir)

    # copy resources
    os.mkdir(assets_dir)
    resources_dir = os.path.join(app_android_root, "../Resources")
    if os.path.isdir(resources_dir):
        copy_files(resources_dir, assets_dir)

    # jsb project should copy javascript files and resources(shared with cocos2d-html5)
    resources_dir = os.path.join(app_android_root, "../../../cocos/scripting/javascript/script")
    copy_files(resources_dir, assets_dir)

def build():

    ndk_root = check_environment_variables()
    select_toolchain_version()

    current_dir = os.path.dirname(os.path.realpath(__file__))
    cocos_root = os.path.join(current_dir, "../../..")

    app_android_root = current_dir
    copy_resources(app_android_root)
    do_build(cocos_root, ndk_root, app_android_root)

# -------------- main --------------
if __name__ == '__main__':

    build()
