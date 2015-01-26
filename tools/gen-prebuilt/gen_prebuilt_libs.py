#!/usr/bin/python
# ----------------------------------------------------------------------------
# generate the prebuilt libs of engine
#
# Copyright 2014 (C) zhangbin
#
# License: MIT
# ----------------------------------------------------------------------------
'''
Generate the prebuilt libs of engine
'''

import os
import subprocess
import shutil
import sys
import excopy
import json

from argparse import ArgumentParser

if sys.platform == 'win32':
    import _winreg

TESTS_PROJ_PATH = "tests/lua-tests"
ANDROID_SO_PATH = "project/proj.android/libs"
ANDROID_A_PATH = "project/proj.android/obj/local"
MK_PATH = "project/proj.android/jni/Application.mk"
CONSOLE_PATH = "tools/cocos2d-console/bin"

def os_is_win32():
    return sys.platform == 'win32'

def os_is_mac():
    return sys.platform == 'darwin'

def run_shell(cmd, cwd=None):
    p = subprocess.Popen(cmd, shell=True, cwd=cwd)
    p.wait()

    if p.returncode:
        raise subprocess.CalledProcessError(returncode=p.returncode, cmd=cmd)

    return p.returncode

class Generator(object):

    XCODE_CMD_FMT = "xcodebuild -project \"%s\" -configuration Release -target \"%s\" %s CONFIGURATION_BUILD_DIR=%s"

    CONFIG_FILE = "build_config.json"
    KEY_XCODE_PROJ_INFO = "xcode_proj_info"
    KEY_WIN32_PROJ_INFO = "win32_proj_info"

    KEY_OUTPUT_DIR = "outputdir"
    KEY_TARGETS = "targets"

    def __init__(self, args):
        self.need_clean = args.need_clean
        self.disable_strip = args.disable_strip
        self.use_incredibuild = args.use_incredibuild
        self.tool_dir = os.path.realpath(os.path.dirname(__file__))
        self.no_android = args.no_android

        self.engine_dir = os.path.join(self.tool_dir, os.path.pardir, os.path.pardir)

        self.load_config()

    def load_config(self):
        cfg_json = os.path.join(self.tool_dir, Generator.CONFIG_FILE)
        f = open(cfg_json)
        cfg_info = json.load(f)
        f.close()

        self.xcode_proj_info = cfg_info[Generator.KEY_XCODE_PROJ_INFO]
        self.win32_proj_info = cfg_info[Generator.KEY_WIN32_PROJ_INFO]

    def modify_mk(self, mk_file):
        if os.path.isfile(mk_file):
            file_obj = open(mk_file, "a")
            file_obj.write("\nAPP_ABI :=armeabi armeabi-v7a\n")
            file_obj.close()

    def build_android(self):
        # build .a for android
        console_dir = os.path.join(self.engine_dir, CONSOLE_PATH)
        cmd_path = os.path.join(console_dir, "cocos")
        proj_path = os.path.join(self.engine_dir, TESTS_PROJ_PATH)

        # Add multi ABI in Application.mk
        mk_file = os.path.join(proj_path, MK_PATH)
        f = open(mk_file)
        file_content = f.read()
        f.close()

        self.modify_mk(mk_file)

        # build it
        build_cmd = "%s compile -s %s -p android --ndk-mode release -j 4" % (cmd_path, proj_path)
        run_shell(build_cmd)

        f = open(mk_file, "w")
        f.write(file_content)
        f.close()

        # copy .a to prebuilt dir
        obj_dir = os.path.join(proj_path, ANDROID_A_PATH)
        prebuilt_dir = os.path.join(self.tool_dir, "prebuilt", "android")
        copy_cfg = {
            "from": obj_dir,
            "to": prebuilt_dir,
            "include": [
                "*.a$"
            ]
        }
        excopy.copy_files_with_config(copy_cfg, obj_dir, prebuilt_dir)

        if not self.disable_strip:
            # strip the android libs
            ndk_root = os.environ["NDK_ROOT"]
            if os_is_win32():
                if self.is_32bit_windows():
                    bit_str = ""
                else:
                    bit_str = "-x86_64"

                sys_folder_name = "windows%s" % bit_str
            elif os_is_mac():
                sys_folder_name = "darwin-x86_64"

            strip_cmd_path = os.path.join(ndk_root, "toolchains/arm-linux-androideabi-4.8/prebuilt/%s/arm-linux-androideabi/bin/strip" % sys_folder_name)
            if os.path.exists(strip_cmd_path):
                strip_cmd = "%s -S %s/armeabi*/*.a" % (strip_cmd_path, prebuilt_dir)
                run_shell(strip_cmd)

    def get_required_vs_version(self, proj_file):
        # get the VS version required by the project
        import re
        file_obj = open(proj_file)
        pattern = re.compile(r"^# Visual Studio.+(\d{4})")
        num = None
        for line in file_obj:
            match = pattern.match(line)
            if match is not None:
                num = match.group(1)
                break

        if num is not None:
            if num == "2012":
                ret = "11.0"
            elif num == "2013":
                ret = "12.0"
            else:
                ret = None
        else:
            ret = None

        return ret

    def get_vs_cmd_path(self, require_version):
        # find the VS in register, if system is 64bit, should find vs in both 32bit & 64bit register
        if self.is_32bit_windows():
            reg_flag_list = [ _winreg.KEY_WOW64_32KEY ]
        else:
            reg_flag_list = [ _winreg.KEY_WOW64_64KEY, _winreg.KEY_WOW64_32KEY ]

        needUpgrade = False
        vsPath = None

        try:
            for reg_flag in reg_flag_list:
                print("find vs in reg : %s" % ("32bit" if reg_flag == _winreg.KEY_WOW64_32KEY else "64bit"))
                vs = _winreg.OpenKey(
                    _winreg.HKEY_LOCAL_MACHINE,
                    r"SOFTWARE\Microsoft\VisualStudio",
                    0,
                    _winreg.KEY_READ | reg_flag
                )

                try:
                    i = 0
                    while True:
                        try:
                            # enum the keys in vs reg
                            version = _winreg.EnumKey(vs, i)
                            find_ver = float(version)

                            # find the vs which version >= required version
                            if find_ver >= float(require_version):
                                key = _winreg.OpenKey(vs, r"SxS\VS7")
                                vsPath, type = _winreg.QueryValueEx(key, version)

                                if os.path.exists(vsPath):
                                    if float(version) > float(require_version):
                                        needUpgrade = True
                                    break
                                else:
                                    vsPath = None
                        except:
                            continue
                        finally:
                            i += 1
                except:
                    pass

                # if find one right vs, break
                if vsPath is not None:
                    break
        except WindowsError as e:
            message = "Visual Studio wasn't installed"
            print(e)
            raise Exception(message)

        commandPath = os.path.join(vsPath, "Common7", "IDE", "devenv")
        return (needUpgrade, commandPath)

    def is_32bit_windows(self):
        arch = os.environ['PROCESSOR_ARCHITECTURE'].lower()
        archw = os.environ.has_key("PROCESSOR_ARCHITEW6432")
        return (arch == "x86" and not archw)

    def build_win32_proj(self, cmd_path, sln_path, proj_name, mode):
        build_cmd = " ".join([
            "\"%s\"" % cmd_path,
            "\"%s\"" % sln_path,
            "/%s \"Release|Win32\"" % mode,
            "/Project \"%s\"" % proj_name
        ])
        run_shell(build_cmd)

    def build_win32(self):
        print("Building Win32")

        for key in self.win32_proj_info.keys():
            output_dir = self.win32_proj_info[key][Generator.KEY_OUTPUT_DIR]
            proj_path = os.path.join(self.engine_dir, key)
            require_vs_version = self.get_required_vs_version(proj_path)
            needUpgrade, vs_command = self.get_vs_cmd_path(require_vs_version)

            # get the build folder & win32 output folder
            build_folder_path = os.path.join(os.path.dirname(proj_path), "Release.win32")
            if os.path.exists(build_folder_path):
                shutil.rmtree(build_folder_path)
            os.makedirs(build_folder_path)

            win32_output_dir = os.path.join(self.tool_dir, output_dir)
            if os.path.exists(win32_output_dir):
                shutil.rmtree(win32_output_dir)
            os.makedirs(win32_output_dir)

            # upgrade projects
            if needUpgrade:
                commandUpgrade = ' '.join([
                    "\"%s\"" % vs_command,
                    "\"%s\"" % proj_path,
                    "/Upgrade"
                ])
                run_shell(commandUpgrade)

            if self.use_incredibuild:
                # use incredibuild, build whole sln
                build_cmd = " ".join([
                    "BuildConsole",
                    "%s" % proj_path,
                    "/build",
                    "/cfg=\"Release|Win32\""
                ])
                run_shell(build_cmd)

            if not self.use_incredibuild:
                # build the projects
                for proj_name in self.win32_proj_info[key][Generator.KEY_TARGETS]:
                    self.build_win32_proj(vs_command, proj_path, proj_name, "build")

                    lib_file_path = os.path.join(build_folder_path, "%s.lib" % proj_name)
                    if not os.path.exists(lib_file_path):
                        # if the lib is not generated, rebuild the project
                        self.build_win32_proj(vs_command, proj_path, proj_name, "rebuild")

                    if not os.path.exists(lib_file_path):
                        raise Exception("Library %s not generated as expected!" % lib_file_path)

            # copy the libs into prebuilt dir
            for file_name in os.listdir(build_folder_path):
                file_path = os.path.join(build_folder_path, file_name)
                shutil.copy(file_path, win32_output_dir)

        print("Win32 build succeeded.")

    def build_ios_mac(self):
        for key in self.xcode_proj_info.keys():
            output_dir = self.xcode_proj_info[key][Generator.KEY_OUTPUT_DIR]
            proj_path = os.path.join(self.engine_dir, key)
            ios_out_dir = os.path.join(self.tool_dir, output_dir, "ios")
            mac_out_dir = os.path.join(self.tool_dir, output_dir, "mac")

            ios_sim_libs_dir = os.path.join(ios_out_dir, "simulator")
            ios_dev_libs_dir = os.path.join(ios_out_dir, "device")
            for target in self.xcode_proj_info[key][Generator.KEY_TARGETS]:
                build_cmd = Generator.XCODE_CMD_FMT % (proj_path, "%s iOS" % target, "-sdk iphonesimulator", ios_sim_libs_dir)
                run_shell(build_cmd, self.tool_dir)

                build_cmd = Generator.XCODE_CMD_FMT % (proj_path, "%s iOS" % target, "-sdk iphoneos", ios_dev_libs_dir)
                run_shell(build_cmd, self.tool_dir)

                build_cmd = Generator.XCODE_CMD_FMT % (proj_path, "%s Mac" % target, "", mac_out_dir)
                run_shell(build_cmd, self.tool_dir)

            # generate fat libs for iOS
            for lib in os.listdir(ios_sim_libs_dir):
                sim_lib = os.path.join(ios_sim_libs_dir, lib)
                dev_lib = os.path.join(ios_dev_libs_dir, lib)
                output_lib = os.path.join(ios_out_dir, lib)
                lipo_cmd = "lipo -create -output \"%s\" \"%s\" \"%s\"" % (output_lib, sim_lib, dev_lib)

                run_shell(lipo_cmd)

            # remove the simulator & device libs in iOS
            shutil.rmtree(ios_sim_libs_dir)
            shutil.rmtree(ios_dev_libs_dir)

            if not self.disable_strip:
                # strip the libs
                ios_strip_cmd = "xcrun -sdk iphoneos strip -S %s/*.a" % ios_out_dir
                run_shell(ios_strip_cmd)
                mac_strip_cmd = "xcrun strip -S %s/*.a" % mac_out_dir
                run_shell(mac_strip_cmd)

    def build_all_libs(self):
        if os_is_mac():
            # build for iOS & Mac
            self.build_ios_mac()

        if os_is_win32():
            # build for win32
            self.build_win32()

        if not self.no_android:
            self.build_android()

    def do_generate(self):
        output_dir = os.path.join(self.tool_dir, "prebuilt")
        if self.need_clean and os.path.exists(output_dir):
            shutil.rmtree(output_dir)
        self.build_all_libs()

if __name__ == "__main__":
    parser = ArgumentParser(description="Generate prebuilt engine for Cocos Engine.")
    parser.add_argument('-c', dest='need_clean', action="store_true", help='Remove the \"prebuilt\" directory first.')
    parser.add_argument('-n', "--no-android", dest='no_android', action="store_true", help='Not build android libs.')
    parser.add_argument('-d', "--disable-strip", dest='disable_strip', action="store_true", help='Disable the strip of the generated libs.')
    parser.add_argument('-i', "--incredibuild", dest='use_incredibuild', action="store_true", help='Use incredibuild to build win32 projects. Only available on windows.')
    (args, unknown) = parser.parse_known_args()

    if len(unknown) > 0:
        print("unknown arguments: %s" % unknown)

    gen_obj = Generator(args)
    gen_obj.do_generate()
