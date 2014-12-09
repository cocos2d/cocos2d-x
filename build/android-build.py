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

class BUILD_CONSTANT:
    SDK_ROOT = None
    COCOS_ROOT = None
    NDK_BUILD_COMMAND = None
    
def initBuildConstant(ndk_build_param, build_mode):
    ''' Checking the environment NDK_ROOT, which will be used for building
    '''
    try:
        ndk_root = os.environ['NDK_ROOT']
        ndk_build_path = os.path.join(ndk_root, "ndk-build")
    except Exception:
        print "NDK_ROOT not defined. Please define NDK_ROOT in your environment"
        sys.exit(1)
    
    toolchainVersion = '4.8'
    try:
        versionFile = open(os.path.join(ndk_root, "RELEASE.TXT"))
        firstLine = versionFile.readline()
        if firstLine :
            ndkVersion = firstLine[firstLine.index('r') : firstLine.index(' ')]
            ndkVersionValue = int(filter(str.isdigit,ndkVersion))
            if ndkVersionValue < 10 or cmp(ndkVersion,'r10c') < 0 :
                print '''Please use NDK r10c above.
If you do not,your application may crash or freeze on Android L(5.0) when use BMFont and HttpClient.
For More information:
    https://github.com/cocos2d/cocos2d-x/issues/9114
    https://github.com/cocos2d/cocos2d-x/issues/9138\n'''
            else:
                toolchainVersion = '4.9'
        versionFile.close()
    except Exception:
        print "Can not be determined your NDK version"
        
    if toolchainVersion == '4.8':
        print 'NDK_TOOLCHAIN_VERSION is 4.8,your application may crash on Androud when use c++ 11 regular\n'
        
    current_dir = os.path.dirname(os.path.realpath(__file__))
    cocos_root = os.path.join(current_dir, "..")
    BUILD_CONSTANT.COCOS_ROOT = cocos_root
    
    # windows should use ";" to seperate module paths
    platform = sys.platform
    if platform == 'win32':
        ndk_module_path = 'NDK_MODULE_PATH=%s;%s/external;%s/cocos' % (cocos_root, cocos_root, cocos_root)
    else:
        ndk_module_path = 'NDK_MODULE_PATH=%s:%s/external:%s/cocos' % (cocos_root, cocos_root, cocos_root)
    
    ''' The build process can be accelerated by running multiple concurrent job processes using the -j-option.
    '''
    try:
        import multiprocessing
        num_of_cpu = multiprocessing.cpu_count()
    except Exception:
        print "Can't know cpuinfo, use default 1 cpu"
        num_of_cpu = 1
        
    if ndk_build_param == None:
        BUILD_CONSTANT.NDK_BUILD_COMMAND = '%s -j%d NDK_DEBUG=%d %s NDK_TOOLCHAIN_VERSION=%s' % (ndk_build_path, num_of_cpu, build_mode=='debug', ndk_module_path, toolchainVersion)
    else:
        BUILD_CONSTANT.NDK_BUILD_COMMAND = '%s -j%d NDK_DEBUG=%d %s %s NDK_TOOLCHAIN_VERSION=%s' % (ndk_build_path, num_of_cpu, build_mode=='debug', ndk_build_param, ndk_module_path, toolchainVersion)
    
def check_environment_variables_sdk():
    ''' Checking the environment ANDROID_SDK_ROOT, which will be used for building
    '''

    try:
        BUILD_CONSTANT.SDK_ROOT = os.environ['ANDROID_SDK_ROOT']
    except Exception:
        print "ANDROID_SDK_ROOT not defined. Please define ANDROID_SDK_ROOT in your environment"
        sys.exit(1)

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

def do_build(app_android_root, android_platform, build_mode):
    command = '%s -C %s' % (BUILD_CONSTANT.NDK_BUILD_COMMAND, app_android_root)
    print command
    if os.system(command) != 0:
        raise Exception("Build dynamic library for project [ " + app_android_root + " ] fails!")
    elif android_platform is not None:
        sdk_tool_path = os.path.join(BUILD_CONSTANT.SDK_ROOT, "tools/android")
        cocoslib_path = os.path.join(BUILD_CONSTANT.COCOS_ROOT, "cocos/platform/android/java")
        command = '%s update lib-project -t %s -p %s' % (sdk_tool_path,android_platform,cocoslib_path)
        if os.system(command) != 0:
            raise Exception("update cocos lib-project [ " + cocoslib_path + " ] fails!")
        command = '%s update project -t %s -p %s -s' % (sdk_tool_path,android_platform,app_android_root)
        if os.system(command) != 0:
            raise Exception("update project [ " + app_android_root + " ] fails!")
        buildfile_path = os.path.join(app_android_root, "build.xml")
        command = 'ant clean %s -f %s -Dsdk.dir=%s' % (build_mode,buildfile_path,BUILD_CONSTANT.SDK_ROOT)
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

def copy_file(src_file, dst):
    if not src_file.startswith('.') and not src_file.endswith('.gz') and os.path.isfile(src_file):
        shutil.copy(src_file, dst)

def copy_resources(target, app_android_root):

    # remove app_android_root/assets if it exists
    assets_dir = os.path.join(app_android_root, "assets")
    if os.path.isdir(assets_dir):
        shutil.rmtree(assets_dir)

    os.mkdir(assets_dir)

    # copy resources(cpp samples)
    if target in CPP_SAMPLES:
        resources_dir = os.path.join(app_android_root, "../Resources")
        if os.path.isdir(resources_dir):
            copy_files(resources_dir, assets_dir)


    # lua samples should copy lua script
    if target in LUA_SAMPLES:
        resources_dir = os.path.join(app_android_root, "../../res")
        assets_res_dir = os.path.join(assets_dir, "res")
        os.mkdir(assets_res_dir)

        if target != "lua-tests":
            copy_files(resources_dir, assets_res_dir)

        src_dir = os.path.join(app_android_root, "../../src")
        assets_src_dir = os.path.join(assets_dir, "src")
        os.mkdir(assets_src_dir)
        copy_files(src_dir, assets_src_dir)

        common_script_dir = os.path.join(app_android_root, "../../../../cocos/scripting/lua-bindings/script/")
        cocos_src_dir = os.path.join(assets_src_dir,"cocos")
        if os.path.exists(cocos_src_dir):
            shutil.rmtree(cocos_src_dir)
        os.mkdir(cocos_src_dir)
        copy_files(common_script_dir, cocos_src_dir)

        luasocket_script_dir = os.path.join(app_android_root, "../../../../external/lua/luasocket")
        for root, dirs, files in os.walk(luasocket_script_dir):
            for f in files:
                if os.path.splitext(f)[1] == '.lua':
                    fall = os.path.join(root, f)
                    shutil.copy(fall, assets_dir)

        # lua-tests shared resources with cpp-tests
        if target == "lua-tests":
            resources_cocosbuilder_res_dir = os.path.join(resources_dir, "cocosbuilderRes")
            assets_cocosbuilder_res_dir = os.path.join(assets_res_dir, "cocosbuilderRes")
            os.mkdir(assets_cocosbuilder_res_dir)
            copy_files(resources_cocosbuilder_res_dir, assets_cocosbuilder_res_dir)

            resources_dir = os.path.join(app_android_root, "../../../cpp-tests/Resources")
            copy_files(resources_dir, assets_res_dir)
        if target == "lua-game-controller-test":
            print("coming generator game controller")
            resources_dir = os.path.join(app_android_root, "../../../game-controller-test/Resources")
            copy_files(resources_dir, assets_res_dir)

def build_samples(target,ndk_build_param,android_platform,build_mode):

    if build_mode is None:
        build_mode = 'debug'
    elif build_mode != 'release':
        build_mode = 'debug'
        
    initBuildConstant(ndk_build_param, build_mode)
    
    build_targets = caculate_built_samples(target)
    
    if android_platform is not None:
        check_environment_variables_sdk()
        if android_platform.isdigit():
            android_platform = 'android-'+android_platform
        else:
            print 'please use vaild android platform'
            exit(1)

    app_android_root = ''

    target_proj_path_map = {
        "cpp-empty-test": "tests/cpp-empty-test/proj.android",
        "game-controller-test": "tests/game-controller-test/proj.android",
        "cpp-tests": "tests/cpp-tests/proj.android",
        "lua-empty-test": "tests/lua-empty-test/project/proj.android",
        "lua-tests": "tests/lua-tests/project/proj.android",
        "lua-game-controller-test": "tests/lua-game-controller-test/project/proj.android"
    }

    for target in build_targets:
        if target in target_proj_path_map:
            app_android_root = os.path.join(BUILD_CONSTANT.COCOS_ROOT, target_proj_path_map[target])
        else:
            print 'unknown target: %s' % target
            continue

        copy_resources(target, app_android_root)
        do_build(app_android_root, android_platform, build_mode)

# -------------- main --------------
if __name__ == '__main__':

    #parse the params
    usage = """
    This script is mainy used for building tests built-in with cocos2d-x.

    Usage: %prog [options] [cpp-empty-test|cpp-tests|lua-empty-test|lua-tests|cpp|lua|all]

    If you are new to cocos2d-x, I recommend you start with cpp-empty-test, lua-empty-test.

    You can combine these targets like this:

    python android-build.py -p 10 cpp-empty-test lua-empty-test


    Note: You should install ant to generate apk while building the andriod tests. But it is optional. You can generate apk with eclipse.
    """

    parser = OptionParser(usage=usage)
    parser.add_option("-n", "--ndk", dest="ndk_build_param",
    help='Parameter for ndk-build')
    parser.add_option("-p", "--platform", dest="android_platform",
    help='Parameter for android-update. Without the parameter,the script just build dynamic library for the projects. Valid android-platform are:[10|11|12|13|14|15|16|17|18|19]')
    parser.add_option("-b", "--build", dest="build_mode",
    help='The build mode for java project,debug[default] or release. Get more information,please refer to http://developer.android.com/tools/building/building-cmdline.html')
    (opts, args) = parser.parse_args()
    
    print "We will use cocos console to build tests built-in with cocos2d-x and remove this script next version.\n"
    if len(args) == 0:
        parser.print_help()
        sys.exit(1)
    else:
        try:
            build_samples(args, opts.ndk_build_param,opts.android_platform,opts.build_mode)
        except Exception as e:
            print e
            sys.exit(1)
