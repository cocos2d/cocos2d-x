#!/usr/bin/python
#-*- coding: UTF-8 -*-

import os
import sys
import time
import shutil
import excopy
import json
import utils_cocos

from custom_error import CustomError
from custom_error import Logging
from argparse import ArgumentParser


class CocosLibsCompiler(object):
    CFG_FILE = 'gen_libs_config.json'

    KEY_LIBS_OUTPUT = 'libs_output_dir'
    KEY_XCODE_PROJS_INFO = 'xcode_projs_info'
    KEY_VS_PROJS_INFO = 'vs_projs_info'
    KEY_SUPPORT_VS_VERSIONS = 'support_vs_versions'
    CHECK_KEYS = [
        KEY_LIBS_OUTPUT,
        KEY_XCODE_PROJS_INFO,
        KEY_VS_PROJS_INFO,
        KEY_SUPPORT_VS_VERSIONS
    ]

    KEY_XCODE_TARGETS = 'targets'
    KEY_VS_BUILD_TARGETS = 'build_targets'
    KEY_VS_RENAME_TARGETS = 'rename_targets'

    def __init__(self, args):
        print("Compiler init function")
        self.cur_dir = os.path.realpath(os.path.dirname(__file__))
        self.cfg_file_path = os.path.join(self.cur_dir, CocosLibsCompiler.CFG_FILE)
        self.parse_config()

        # arguments check and set
        self.clean = args.clean
        self.build_win = args.win
        self.build_mac = args.mac
        self.build_android = args.android
        self.disable_strip = args.disable_strip
        self.repo_x = args.repo_x
        self.vs_version = args.vs_version
        self.use_incredibuild = False
        if args.all:
            self.build_win = True
            self.build_mac = True
            self.build_android = True

        if args.app_abi is None:
            self.app_abi = 'armeabi'
        else:
            self.app_abi = args.app_abi

        self.repo_x = os.path.realpath(self.repo_x)
        self.lib_dir = os.path.normpath(os.path.join(self.repo_x, self.cfg_info[CocosLibsCompiler.KEY_LIBS_OUTPUT]))

    def parse_config(self):
        if not os.path.isfile(self.cfg_file_path):
            raise CustomError('%s is not a valid config file.' % self.cfg_file_path, CustomError.ERROR_PATH_NOT_FOUND)

        try:
            f = open(self.cfg_file_path)
            self.cfg_info = json.load(f)
            f.close()
        except:
            raise CustomError('Parse %s failed.' % self.cfg_file_path, CustomError.ERROR_PARSE_FILE)

        for k in CocosLibsCompiler.CHECK_KEYS:
            if k not in self.cfg_info.keys():
                raise CustomError('%s is not found in %s' % (k, self.cfg_file_path), CustomError.ERROR_WRONG_CONFIG)

    def get_cfg_info(self):
        return self.cfg_info

    def compile(self):
        print("compile function")
        if self.clean:
            self.clean_libs()
        if self.build_win:
            self.compile_win()
        if self.build_mac:
            self.compile_mac_ios()
        if self.build_android:
            self.compile_android("lua")
            self.compile_android("js")


    def build_win32_proj(self, cmd_path, sln_path, proj_name, mode):
        build_cmd = " ".join([
            "\"%s\"" % cmd_path,
            "\"%s\"" % sln_path,
            "/%s \"Release|Win32\"" % mode,
            "/Project \"%s\"" % proj_name
        ])
        utils_cocos.execute_command(build_cmd)

    def compile_win(self):
        if not utils_cocos.os_is_win32():
            print("this is not win platform, needn't compile")
            return

        # get the VS versions will be used for compiling
        support_vs_versions = self.cfg_info[CocosLibsCompiler.KEY_SUPPORT_VS_VERSIONS]
        compile_vs_versions = support_vs_versions
        if self.vs_version is not None:
            if self.vs_version not in support_vs_versions:
                raise CustomError('Not support VS%d' % self.vs_version)
            else:
                compile_vs_versions = [ self.vs_version ]

        vs_cmd_info = {}
        for vs_version in compile_vs_versions:
            # get the vs command with specified version
            vs_command = utils_cocos.get_vs_cmd_path(vs_version)
            if vs_command is None:
                Logging.warning('Not found VS%d' % vs_version)
            else:
                vs_cmd_info[vs_version] = vs_command

        if len(vs_cmd_info) == 0:
            raise CustomError('Not found available VS.', CustomError.ERROR_TOOLS_NOT_FOUND)

        # get the VS projects info
        win32_proj_info = self.cfg_info[CocosLibsCompiler.KEY_VS_PROJS_INFO]
        for vs_version in vs_cmd_info.keys():
            vs_command = vs_cmd_info[vs_version]
            for key in win32_proj_info.keys():
                output_dir = os.path.join(self.lib_dir, "win32")
                proj_path = os.path.join(self.repo_x, key)

                # get the build folder & win32 output folder
                build_folder_path = os.path.join(os.path.dirname(proj_path), "Release.win32")
                win32_output_dir = os.path.join(self.repo_x, output_dir)
                if not os.path.exists(win32_output_dir):
                    os.makedirs(win32_output_dir)

                # clean solution
                # clean_cmd = " ".join([
                #     "\"%s\"" % vs_command,
                #     "\"%s\"" % proj_path,
                #     "/clean \"Release|Win32\""
                # ])
                # utils_cocos.execute_command(clean_cmd)

                # build project
                if self.use_incredibuild:
                    # use incredibuild, build whole sln
                    build_cmd = " ".join([
                        "BuildConsole",
                        "%s" % proj_path,
                        "/build",
                        "/cfg=\"Release|Win32\""
                    ])
                    utils_cocos.execute_command(build_cmd)
                else:
                    for proj_name in win32_proj_info[key][CocosLibsCompiler.KEY_VS_BUILD_TARGETS]:
                        # build the projects
                        self.build_win32_proj(vs_command, proj_path, proj_name, "build")

                        lib_file_path = os.path.join(build_folder_path, "%s.lib" % proj_name)
                        if not os.path.exists(lib_file_path):
                            # if the lib is not generated, rebuild the project
                            self.build_win32_proj(vs_command, proj_path, proj_name, "rebuild")

                        if not os.path.exists(lib_file_path):
                            raise Exception("Library %s not generated as expected!" % lib_file_path)

                # copy the libs into prebuilt dir
                for file_name in os.listdir(build_folder_path):
                    name, ext = os.path.splitext(file_name)
                    if ext != ".lib" and ext != ".dll":
                        continue

                    file_path = os.path.join(build_folder_path, file_name)
                    shutil.copy(file_path, win32_output_dir)

                # rename the specified libs
                suffix = "_%d" % vs_version
                for proj_name in win32_proj_info[key][CocosLibsCompiler.KEY_VS_RENAME_TARGETS]:
                    src_name = os.path.join(win32_output_dir, "%s.lib" % proj_name)
                    dst_name = os.path.join(win32_output_dir, "%s%s.lib" % (proj_name, suffix))
                    if os.path.exists(src_name):
                        if os.path.exists(dst_name):
                            os.remove(dst_name)
                        os.rename(src_name, dst_name)

        print("Win32 build succeeded.")

    def compile_mac_ios(self):
        if not utils_cocos.os_is_mac():
            print("this is not mac platform, needn't compile")
            return
        print("to compile mac")

        xcode_proj_info = self.cfg_info[CocosLibsCompiler.KEY_XCODE_PROJS_INFO]

        XCODE_CMD_FMT = "xcodebuild -project \"%s\" -configuration Release -target \"%s\" %s CONFIGURATION_BUILD_DIR=%s"
        for key in xcode_proj_info.keys():
            proj_path = os.path.join(self.repo_x, key)
            ios_out_dir = os.path.join(self.lib_dir, "ios")
            mac_out_dir = os.path.join(self.lib_dir, "mac")
            ios_sim_libs_dir = os.path.join(ios_out_dir, "simulator")
            ios_dev_libs_dir = os.path.join(ios_out_dir, "device")

            target = xcode_proj_info[key][CocosLibsCompiler.KEY_XCODE_TARGETS]

            # compile ios simulator
            build_cmd = XCODE_CMD_FMT % (proj_path, "%s iOS" % target, "-sdk iphonesimulator ARCHS=\"i386 x86_64\" VALID_ARCHS=\"i386 x86_64\"", ios_sim_libs_dir)
            retVal = utils_cocos.execute_command(build_cmd)
            if 0 != retVal:
                print("[ERROR] compile ios simulator fail")
                return retVal

            # compile ios device
            build_cmd = XCODE_CMD_FMT % (proj_path, "%s iOS" % target, "-sdk iphoneos", ios_dev_libs_dir)
            retVal = utils_cocos.execute_command(build_cmd)
            if 0 != retVal:
                print("[ERROR] compile ios device fail")
                return retVal

            # compile mac
            build_cmd = XCODE_CMD_FMT % (proj_path, "%s Mac" % target, "", mac_out_dir)
            retVal = utils_cocos.execute_command(build_cmd)
            if 0 != retVal:
                print("[ERROR] compile mac fail")
                return retVal

            # generate fat libs for iOS
            for lib in os.listdir(ios_sim_libs_dir):
                sim_lib = os.path.join(ios_sim_libs_dir, lib)
                dev_lib = os.path.join(ios_dev_libs_dir, lib)
                output_lib = os.path.join(ios_out_dir, lib)
                lipo_cmd = "lipo -create -output \"%s\" \"%s\" \"%s\"" % (output_lib, sim_lib, dev_lib)

                utils_cocos.execute_command(lipo_cmd)

            # remove the simulator & device libs in iOS
            utils_cocos.rmdir(ios_sim_libs_dir)
            utils_cocos.rmdir(ios_dev_libs_dir)

            if not self.disable_strip:
                # strip the libs
                ios_strip_cmd = "xcrun -sdk iphoneos strip -S %s/*.a" % ios_out_dir
                utils_cocos.execute_command(ios_strip_cmd)
                mac_strip_cmd = "xcrun strip -S %s/*.a" % mac_out_dir
                utils_cocos.execute_command(mac_strip_cmd)

    def compile_android(self, language):
        print("compile android")
        # build .so for android
        CONSOLE_PATH = "tools/cocos2d-console/bin"
        ANDROID_A_PATH = "frameworks/runtime-src/proj.android/obj/local"

        android_out_dir = os.path.join(self.lib_dir, "android")
        engine_dir = self.repo_x
        console_dir = os.path.join(engine_dir, CONSOLE_PATH)
        if utils_cocos.os_is_win32():
            cmd_path = os.path.join(console_dir, "cocos.bat")
        else:
            cmd_path = os.path.join(console_dir, "cocos")

        proj_name = "My%sGame" % language
        proj_dir = os.path.join(self.cur_dir, "temp")
        proj_path = os.path.join(proj_dir, proj_name)
        utils_cocos.rmdir(proj_path)

        # create a runtime project
        create_cmd = "%s new -l %s -t runtime -d %s %s" % (cmd_path, language, proj_dir, proj_name)
        utils_cocos.execute_command(create_cmd)

        # build it
        build_cmd = "%s compile -s %s -p android --ndk-mode release -j 4 --app-abi %s" % (cmd_path, proj_path, self.app_abi)
        utils_cocos.execute_command(build_cmd)

        # copy .a to prebuilt dir
        obj_dir = os.path.join(proj_path, ANDROID_A_PATH)
        copy_cfg = {
            "from": obj_dir,
            "to": android_out_dir,
            "include": [
                "*.a$"
            ]
        }
        excopy.copy_files_with_config(copy_cfg, obj_dir, android_out_dir)

        if not self.disable_strip:
            # strip the android libs
            ndk_root = os.environ["NDK_ROOT"]
            if utils_cocos.os_is_win32():
                if utils_cocos.is_32bit_windows():
                    bit_str = ""
                else:
                    bit_str = "-x86_64"
                sys_folder_name = "windows%s" % bit_str
            elif utils_cocos.os_is_mac():
                sys_folder_name = "darwin-x86_64"

            # set strip execute file name
            if utils_cocos.os_is_win32():
                strip_execute_name = "strip.exe"
            else:
                strip_execute_name = "strip"

            # strip arm libs
            strip_cmd_path = os.path.join(ndk_root, "toolchains/arm-linux-androideabi-4.8/prebuilt/%s/arm-linux-androideabi/bin/%s"
                % (sys_folder_name, strip_execute_name))
            if not os.path.exists(strip_cmd_path):
                strip_cmd_path = os.path.join(ndk_root, "toolchains/arm-linux-androideabi-4.8/prebuilt/%s/arm-linux-androideabi/bin/%s"
                    % (sys_folder_name.replace(bit_str, ""), strip_execute_name))
            if os.path.exists(strip_cmd_path):
                armlibs = ["armeabi", "armeabi-v7a"]
                for fold in armlibs:
                    self.trip_libs(strip_cmd_path, os.path.join(android_out_dir, fold))

            # strip x86 libs
            strip_cmd_path = os.path.join(ndk_root, "toolchains/x86-4.8/prebuilt/%s/i686-linux-android/bin/%s" % (sys_folder_name, strip_execute_name))
            if os.path.exists(strip_cmd_path) and os.path.exists(os.path.join(android_out_dir, "x86")):
                self.trip_libs(strip_cmd_path, os.path.join(android_out_dir, 'x86'))

        # remove the project
        utils_cocos.rmdir(proj_path)

    def trip_libs(self, strip_cmd, folder):
        if not os.path.isdir(folder):
            return

        if utils_cocos.os_is_win32():
            for name in os.listdir(folder):
                basename, ext = os.path.splitext(name)
                if ext == ".a":
                    full_name = os.path.join(folder, name)
                    command = "%s -S %s" % (strip_cmd, full_name)
                    utils_cocos.execute_command(command)
        else:
            strip_cmd = "%s -S %s/*.a" % (strip_cmd, folder)
            utils_cocos.execute_command(strip_cmd)

    def clean_libs(self):
        print("to clean libs")
        utils_cocos.rmdir(self.lib_dir)


if __name__ == "__main__":
    parser = ArgumentParser(description="Generate prebuilt engine for Cocos Engine.")
    parser.add_argument('-c', dest='clean', action="store_true", help='clean libs folder')
    parser.add_argument('-all', dest='all', action="store_true", help='compile all platform')
    parser.add_argument('--win', dest='win', action="store_true", help='compile windows platform')
    parser.add_argument('--mac', dest='mac', action="store_true", help='compile mac platform')
    parser.add_argument('--android', dest='android', action="store_true",help='complile android platform')
    parser.add_argument('--dis-strip', "--disable-strip", dest='disable_strip', action="store_true", help='Disable the strip of the generated libs.')
    parser.add_argument('--vs', dest='vs_version', type=int, help='visual studio version, such as 2013.', default=2013)
    parser.add_argument("--app-abi", dest="app_abi",
                        help="Set the APP_ABI of ndk-build.Can be multi value separated with ':'. Sample : --app-aib armeabi:x86:mips. Default value is 'armeabi'.")

    (args, unknown) = parser.parse_known_args()

    if len(unknown) > 0:
        print("unknown arguments: %s" % unknown)

    # Get the engine path
    cur_dir = os.path.realpath(os.path.dirname(__file__))
    args.repo_x = os.path.normpath(os.path.join(cur_dir, os.pardir, os.pardir, os.pardir))

    if not args.win and not args.mac and not args.android:
        args.all = True

    beginSecond = time.time()
    print(">>> Bgein Compile at %s" % time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(beginSecond)))

    try:
        compiler = CocosLibsCompiler(args)
        compiler.compile()
    except Exception as e:
        if isinstance(e, CustomError):
            Logging.error(' '.join(e.args))
            err_no = e.get_error_no()
            sys.exit(err_no)
        else:
            raise
    finally:
        endSecond = time.time()
        print(">>> Bgein Compile at %s" % time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(beginSecond)))
        print(">>> End Compile at %s" % time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(endSecond)))
        interSecond = endSecond - beginSecond
        interSecond = int(interSecond)
        print(">>> Use Second %d" % interSecond)
        houre = interSecond/(60*60)
        interSecond = interSecond%(60*60)
        minute = interSecond/60
        second = interSecond%60
        print(">>> Use Time %d:%d:%d" % (houre, minute, second))
