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
    KEY_ANDROID_PROJ_INFO = "android_proj_info"

    KEY_OUTPUT_DIR = "outputdir"
    KEY_TARGETS = "targets"
    KEY_ABIS = "ABIs"
    KEY_LANGUAGES = "languages"

    def __init__(self, args):
        self.need_clean = args.need_clean
        self.disable_strip = args.disable_strip
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
        self.android_proj_info = cfg_info[Generator.KEY_ANDROID_PROJ_INFO]

    def modify_mk(self, mk_file):
        if os.path.isfile(mk_file):
            file_obj = open(mk_file, "a")
            abi_str = " ".join(self.android_proj_info[Generator.KEY_ABIS])
            file_obj.write("\nAPP_ABI := %s\n" % abi_str)
            file_obj.close()

    def build_android(self, language):
        # build .a for android
        console_dir = os.path.join(self.engine_dir, CONSOLE_PATH)
        cmd_path = os.path.join(console_dir, "cocos")
        proj_path = os.path.join(self.engine_dir, "tests/%s-tests" % language)

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

            # strip arm libs
            strip_cmd_path = os.path.join(ndk_root, "toolchains/arm-linux-androideabi-4.8/prebuilt/%s/arm-linux-androideabi/bin/strip" % sys_folder_name)
            if os.path.exists(strip_cmd_path):
                strip_cmd = "%s -S %s/armeabi*/*.a" % (strip_cmd_path, prebuilt_dir)
                run_shell(strip_cmd)

            # strip x86 libs
            strip_cmd_path = os.path.join(ndk_root, "toolchains/x86-4.8/prebuilt/%s/i686-linux-android/bin/strip" % sys_folder_name)
            if os.path.exists(strip_cmd_path) and os.path.exists(os.path.join(prebuilt_dir, "x86")):
                strip_cmd = "%s -S %s/x86/*.a" % (strip_cmd_path, prebuilt_dir)
                run_shell(strip_cmd)

    def get_required_vs_version(self, proj_file):
        # get the VS version required by the project
        return "11.0"

    def get_vs_cmd_path(self, vs_reg, proj_path):
        # get required vs version
        required_vs_version = self.get_required_vs_version(proj_path)
        if required_vs_version is None:
            raise Exception("Can't parse the sln file to find required VS version")

        # get the correct available VS path
        needUpgrade = False
        vsPath = None

        i = 0
        try:
            while True:
                version = _winreg.EnumKey(vs_reg, i)
                try:
                    if float(version) >= float(required_vs_version):
                        key = _winreg.OpenKey(vs_reg, r"SxS\VS7")
                        vsPath, type = _winreg.QueryValueEx(key, version)

                        if float(version) > float(required_vs_version):
                            needUpgrade = True

                        key.close()
                        break
                except:
                    pass
                i += 1
        except WindowsError:
            pass

        if vsPath is None:
            message = "Can't find correct Visual Studio's path in the regedit"
            raise Exception(message)

        commandPath = os.path.join(vsPath, "Common7", "IDE", "devenv")
        return (commandPath, needUpgrade)

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

        # find the VS in register
        try:
            if self.is_32bit_windows():
                reg_flag = _winreg.KEY_WOW64_32KEY
            else:
                reg_flag = _winreg.KEY_WOW64_64KEY

            vs_reg = _winreg.OpenKey(
                _winreg.HKEY_LOCAL_MACHINE,
                r"SOFTWARE\Microsoft\VisualStudio",
                0,
                _winreg.KEY_READ | reg_flag
            )

        except WindowsError:
            message = "Visual Studio wasn't installed"
            raise Exception(message)

        for key in self.win32_proj_info.keys():
            output_dir = self.win32_proj_info[key][Generator.KEY_OUTPUT_DIR]
            proj_path = os.path.join(self.engine_dir, key)
            vs_command, needUpgrade = self.get_vs_cmd_path(vs_reg, proj_path)

            # get the build folder & win32 output folder
            build_folder_path = os.path.join(os.path.dirname(proj_path), "Release.win32")
            if os.path.exists(build_folder_path):
                shutil.rmtree(build_folder_path)
            os.makedirs(build_folder_path)

            win32_output_dir = os.path.join(self.tool_dir, output_dir)
            if not os.path.exists(win32_output_dir):
                os.makedirs(win32_output_dir)

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
                name, ext = os.path.splitext(file_name)
                if ext != ".lib" and ext != ".dll":
                    continue

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
                build_cmd = Generator.XCODE_CMD_FMT % (proj_path, "%s iOS" % target, "-sdk iphonesimulator ARCHS=\"i386 x86_64\" VALID_ARCHS=\"i386 x86_64\"", ios_sim_libs_dir)
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
            for lang in self.android_proj_info[Generator.KEY_LANGUAGES]:
                self.build_android(lang)

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
    (args, unknown) = parser.parse_known_args()

    if len(unknown) > 0:
        print("unknown arguments: %s" % unknown)

    gen_obj = Generator(args)
    gen_obj.do_generate()
