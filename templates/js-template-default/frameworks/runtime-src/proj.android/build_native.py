#!/usr/bin/python

'''
build_native.py

This script will copy resources to assets and build native code with NDK.
'''
import sys
import os, os.path
import shutil
from optparse import OptionParser

def get_num_of_cpu():
    ''' The build process can be accelerated by running multiple concurrent job processes using the -j-option.
    '''
    try:
        platform = sys.platform
        if platform == 'win32':
            if 'NUMBER_OF_PROCESSORS' in os.environ:
                return int(os.environ['NUMBER_OF_PROCESSORS'])
            else:
                return 1
        else:
            from numpy.distutils import cpuinfo
            return cpuinfo.cpu._getNCPUs()
    except Exception:
        print "Can't know cpuinfo, use default 1 cpu"
        return 1

def check_environment_variables():
    ''' Checking the environment NDK_ROOT, which will be used for building
    '''

    try:
        NDK_ROOT = os.environ['NDK_ROOT']
    except Exception:
        print "NDK_ROOT not defined. Please define NDK_ROOT in your environment"
        sys.exit(1)

    return NDK_ROOT

def select_toolchain_version(ndk_root):
    ret_version = "4.8"

    version_file_path = os.path.join(ndk_root, "RELEASE.TXT")
    try:
        versionFile = open(version_file_path)
        lines = versionFile.readlines()
        versionFile.close()

        version_num = None
        version_char = None
        pattern = r'^[a-zA-Z]+(\d+)(\w)'
        for line in lines:
            str_line = line.lstrip()
            match = re.match(pattern, str_line)
            if match:
                version_num = int(match.group(1))
                version_char = match.group(2)
                break

        if version_num is None:
            print("Parse NDK version from file %s failed." % version_file_path)
        else:
            version_char = version_char.lower()
            if version_num > 10 or (version_num == 10 and cmp(version_char, 'c') >= 0):
                ret_version = "4.9"

    except:
        print("Parse NDK version from file %s failed." % version_file_path)

    print("NDK_TOOLCHAIN_VERSION: %s" % ret_version)
    if ret_version == "4.8":
        print(
            "Your application may crash when using c++ 11 regular expression with NDK_TOOLCHAIN_VERSION %s" % ret_version)

    return ret_version

def do_build(cocos_root, ndk_root, app_android_root, ndk_build_param,sdk_root,build_mode):

    ndk_path = os.path.join(ndk_root, "ndk-build")
    ndk_toolchain_version = select_toolchain_version(ndk_root)

    # windows should use ";" to seperate module paths
    platform = sys.platform
    if platform == 'win32':
        ndk_module_path = 'NDK_MODULE_PATH=%s/..;%s;%s/external;%s/cocos NDK_TOOLCHAIN_VERSION=%s' % (cocos_root, cocos_root, cocos_root, cocos_root, ndk_toolchain_version)
    else:
        ndk_module_path = 'NDK_MODULE_PATH=%s/..:%s:%s/external:%s/cocos NDK_TOOLCHAIN_VERSION=%s' % (cocos_root, cocos_root, cocos_root, cocos_root, ndk_toolchain_version)

    num_of_cpu = get_num_of_cpu()
    if ndk_build_param == None:
        command = '%s -j%d -C %s NDK_DEBUG=%d %s' % (ndk_path, num_of_cpu, app_android_root, build_mode=='debug', ndk_module_path)
    else:
        command = '%s -j%d -C %s NDK_DEBUG=%d %s %s' % (ndk_path, num_of_cpu, app_android_root, build_mode=='debug', ndk_build_param, ndk_module_path)
    print command
    if os.system(command) != 0:
        raise Exception("Build dynamic library for project [ " + app_android_root + " ] fails!")

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

    assets_res_dir = assets_dir + "/res";
    assets_scripts_dir = assets_dir + "/src";
    assets_jsb_dir = assets_dir + "/script";
    os.mkdir(assets_res_dir);
    os.mkdir(assets_scripts_dir);
    os.mkdir(assets_jsb_dir);


    shutil.copy(os.path.join(app_android_root, "../../../main.js"), assets_dir)
    shutil.copy(os.path.join(app_android_root, "../../../project.json"), assets_dir)

    resources_dir = os.path.join(app_android_root, "../../../res")
    copy_files(resources_dir, assets_res_dir)

    resources_dir = os.path.join(app_android_root, "../../../src")
    copy_files(resources_dir, assets_scripts_dir)

    resources_dir = os.path.join(app_android_root, "../../../frameworks/cocos2d-x/cocos/js-bindings/bindings/script")
    copy_files(resources_dir, assets_jsb_dir)

def build(targets,ndk_build_param,build_mode):

    ndk_root = check_environment_variables()
    sdk_root = None

    project_root = os.path.dirname(os.path.realpath(__file__))
    cocos_root = os.path.join(project_root, "..", "..", "cocos2d-x")

    print cocos_root

    if build_mode is None:
        build_mode = 'debug'
    elif build_mode != 'release':
        build_mode = 'debug'

    copy_resources(project_root)
    do_build(cocos_root, ndk_root, project_root,ndk_build_param,sdk_root,build_mode)

# -------------- main --------------
if __name__ == '__main__':

    parser = OptionParser()
    parser.add_option("-n", "--ndk", dest="ndk_build_param",
    help='Parameter for ndk-build')
    parser.add_option("-b", "--build", dest="build_mode",
    help='The build mode for NDK project, debug or release')
    (opts, args) = parser.parse_args()

    try:
        build(args, opts.ndk_build_param,opts.build_mode)
    except Exception as e:
        print e
        sys.exit(1)
