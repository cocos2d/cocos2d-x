#!/usr/bin/python
#-*- coding: UTF-8 -*-

import os
import sys
import time
import shutil
import excopy
from utils_cocos import rmdir
from argparse import ArgumentParser

def os_is_win32():
    return sys.platform == 'win32'

def is_32bit_windows():
    arch = os.environ['PROCESSOR_ARCHITECTURE'].lower()
    archw = os.environ.has_key("PROCESSOR_ARCHITEW6432")
    return (arch == "x86" and not archw)

def os_is_mac():
    return sys.platform == 'darwin'

def convert_to_python_path(path):
    return path.replace("\\","/")

def execute_command(cmdstring, cwd=None, timeout=None, shell=True):
    """ 执行一个SHELL命令
        封装了subprocess的Popen方法, 支持超时判断，支持读取stdout和stderr
        参数:
        cwd: 运行命令时更改路径，如果被设定，子进程会直接先更改当前路径到cwd
        timeout: 超时时间，秒，支持小数，精度0.1秒
        shell: 是否通过shell运行
        Returns: return_code
        Raises:  Exception: 执行超时
    """

    import shlex
    import datetime
    import subprocess
    import time

    if os_is_win32():
        cmdstring = convert_to_python_path(cmdstring)

    print("")
    print("Execute command:")
    print(cmdstring)
    print("")

    if shell:
        cmdstring_list = cmdstring
    else:
        cmdstring_list = shlex.split(cmdstring)
    if timeout:
        end_time = datetime.datetime.now() + datetime.timedelta(seconds=timeout)

    # 没有指定标准输出和错误输出的管道,因此会打印到屏幕上
    sub = None
    try:
        sub = subprocess.Popen(cmdstring_list, cwd=cwd, stdin=subprocess.PIPE, shell=shell, bufsize=4096)
    except Exception, e:
        print "execute command fail:%s" % cmdstring
        raise e

    # subprocess.poll()方法：检查子进程是否结束了，如果结束了，设定并返回码，放在subprocess.returncode变量中
    while sub.poll() is None:
        time.sleep(0.1)
        if timeout:
            if end_time <= datetime.datetime.now():
                raise Exception("Timeout：%s"%cmdstring)

    if 0 != sub.returncode :
        errStr = "[ERROR] execute command fail:%s" % cmdstring
        print errStr
        raise Exception(errStr)

    return sub.returncode


class CocosLibsCompiler(object):

    def __init__(self, args):
        print "Compiler init function"

        # argsments check and set
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

        self.cur_dir = os.path.realpath(os.path.dirname(__file__))
        self.repo_x = os.path.realpath(self.repo_x)
        self.lib_dir = os.path.realpath(os.path.join(self.cur_dir, os.path.pardir, "libs"))

    def compile(self):
        print "compile function"
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
        execute_command(build_cmd)

    def compile_win(self):
        if not os_is_win32():
            print "this is not win platform, needn't compile"
            return

        win32_proj_info = {
            "build/cocos2d-win32.sln" : {
                "outputdir" : self.lib_dir,
                "build_targets" : [
                    "libluacocos2d"
                ],
                "rename_targets" : [
                    # "libcocos2d", "libluacocos2d", "libSpine", "libbox2d"
                ]
            },
            "build/cocos2d-js-win32.sln" : {
                "outputdir" : self.lib_dir,
                "build_targets" : [
                    "libjscocos2d"
                ],
                "rename_targets" : [
                    # "libjscocos2d"
                ]
            },
            "tools/simulator/frameworks/runtime-src/proj.win32/simulator.sln" : {
                "outputdir" : self.lib_dir,
                "build_targets" : [
                    "libsimulator"
                ],
                "rename_targets" : [
                    # "libsimulator"
                ]
            }
        }

        import _winreg
        from utils_cocos import get_vs_cmd_path
        # find the VS in register
        try:
            if is_32bit_windows():
                reg_flag = _winreg.KEY_WOW64_32KEY
            else:
                # reg_flag = _winreg.KEY_WOW64_64KEY
                reg_flag = _winreg.KEY_WOW64_32KEY   # _winreg.KEY_WOW64_64KEY

            vs_reg = _winreg.OpenKey(
                _winreg.HKEY_LOCAL_MACHINE,
                r"SOFTWARE\Microsoft\VisualStudio",
                0,
                _winreg.KEY_READ | reg_flag
            )

        except WindowsError:
            message = "Visual Studio wasn't installed"
            raise Exception(message)

        for key in win32_proj_info.keys():
            output_dir = os.path.join(win32_proj_info[key]["outputdir"], "windows")

            proj_path = os.path.join(self.repo_x, key)

            vs_command, needUpgrade = get_vs_cmd_path(vs_reg, proj_path, self.vs_version)

            # get the build folder & win32 output folder
            build_folder_path = os.path.join(os.path.dirname(proj_path), "Release.win32")

            win32_output_dir = os.path.join(self.repo_x, output_dir)
            if not os.path.exists(win32_output_dir):
                os.makedirs(win32_output_dir)

            # clean solution
            clean_cmd = " ".join([
                "\"%s\"" % vs_command,
                "\"%s\"" % proj_path,
                "/clean \"Release|Win32\""
            ])
            execute_command(clean_cmd)

            if self.use_incredibuild:
                # use incredibuild, build whole sln
                build_cmd = " ".join([
                    "BuildConsole",
                    "%s" % proj_path,
                    "/build",
                    "/cfg=\"Release|Win32\""
                ])
                execute_command(build_cmd)
            else:
                for proj_name in win32_proj_info[key]["build_targets"]:
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

            suffix = ""
            for proj_name in win32_proj_info[key]["rename_targets"]:
                src_name = os.path.join(win32_output_dir, "%s.lib" % proj_name)
                dst_name = os.path.join(win32_output_dir, "%s%s.lib" % (proj_name, suffix))
                if os.path.exists(src_name):
                    if os.path.exists(dst_name):
                        os.remove(dst_name)
                    os.rename(src_name, dst_name)

        print("Win32 build succeeded.")

    def compile_mac_ios(self):
        if not os_is_mac():
            print "this is not mac platform, needn't compile"
            return
        print "to compile mac"

        xcode_proj_info = {
            "build/cocos2d_libs.xcodeproj" : {
                "outputdir" : self.lib_dir,
                "targets"   : "libcocos2d",
            },
            "cocos/scripting/lua-bindings/proj.ios_mac/cocos2d_lua_bindings.xcodeproj" : {
                "outputdir" : self.lib_dir,
                "targets"   : "libluacocos2d",
            },
            "cocos/scripting/js-bindings/proj.ios_mac/cocos2d_js_bindings.xcodeproj" : {
                "outputdir" : self.lib_dir,
                "targets"   : "libjscocos2d",
            },
            "tools/simulator/libsimulator/proj.ios_mac/libsimulator.xcodeproj" : {
                "outputdir" : self.lib_dir,
                "targets"   : "libsimulator",
            }
        }

        XCODE_CMD_FMT = "xcodebuild -project \"%s\" -configuration Release -target \"%s\" %s CONFIGURATION_BUILD_DIR=%s"
        for key in xcode_proj_info.keys():
            output_dir = xcode_proj_info[key]["outputdir"]
            proj_path = os.path.join(self.repo_x, key)
            ios_out_dir = os.path.join(output_dir, "ios")
            mac_out_dir = os.path.join(output_dir, "mac")
            ios_sim_libs_dir = os.path.join(ios_out_dir, "simulator")
            ios_dev_libs_dir = os.path.join(ios_out_dir, "device")

            target = xcode_proj_info[key]["targets"]

            # compile ios simulator
            build_cmd = XCODE_CMD_FMT % (proj_path, "%s iOS" % target, "-sdk iphonesimulator ARCHS=\"i386 x86_64\" VALID_ARCHS=\"i386 x86_64\"", ios_sim_libs_dir)
            retVal = execute_command(build_cmd)
            if 0 != retVal:
                print "[ERROR] compile ios simulator fail"
                return retVal

            # compile ios device
            build_cmd = XCODE_CMD_FMT % (proj_path, "%s iOS" % target, "-sdk iphoneos", ios_dev_libs_dir)
            retVal = execute_command(build_cmd)
            if 0 != retVal:
                print "[ERROR] compile ios device fail"
                return retVal

            # compile mac
            build_cmd = XCODE_CMD_FMT % (proj_path, "%s Mac" % target, "", mac_out_dir)
            retVal = execute_command(build_cmd)
            if 0 != retVal:
                print "[ERROR] compile mac fail"
                return retVal

            # generate fat libs for iOS
            for lib in os.listdir(ios_sim_libs_dir):
                sim_lib = os.path.join(ios_sim_libs_dir, lib)
                dev_lib = os.path.join(ios_dev_libs_dir, lib)
                output_lib = os.path.join(ios_out_dir, lib)
                lipo_cmd = "lipo -create -output \"%s\" \"%s\" \"%s\"" % (output_lib, sim_lib, dev_lib)

                execute_command(lipo_cmd)

            # remove the simulator & device libs in iOS
            rmdir(ios_sim_libs_dir)
            rmdir(ios_dev_libs_dir)

            if not self.disable_strip:
                # strip the libs
                ios_strip_cmd = "xcrun -sdk iphoneos strip -S %s/*.a" % ios_out_dir
                execute_command(ios_strip_cmd)
                mac_strip_cmd = "xcrun strip -S %s/*.a" % mac_out_dir
                execute_command(mac_strip_cmd)

    def compile_android(self, language):
        print "compile android"
        # build .so for android
        CONSOLE_PATH = "tools/cocos2d-console/bin"
        SCRIPT_MK_PATH = "frameworks/runtime-src/proj.android/jni/Application.mk"
        ANDROID_A_PATH = "frameworks/runtime-src/proj.android/obj/local"

        android_out_dir = os.path.join(self.lib_dir, "android")
        engine_dir = self.repo_x
        console_dir = os.path.join(engine_dir, CONSOLE_PATH)
        if os_is_win32():
            cmd_path = os.path.join(console_dir, "cocos.bat")
        else:
            cmd_path = os.path.join(console_dir, "cocos")

        proj_name = "My%sGame" % language
        proj_dir = os.path.join(self.cur_dir, "temp")
        proj_path = os.path.join(proj_dir, proj_name)
        rmdir(proj_path)

        # create a runtime project
        create_cmd = "%s new -l %s -t runtime -d %s %s" % (cmd_path, language, proj_dir, proj_name)
        execute_command(create_cmd)

        # Add multi ABI in Application.mk
        mk_file = os.path.join(proj_path, SCRIPT_MK_PATH)
        self.modify_mk(mk_file)

        # build it
        build_cmd = "%s compile -s %s -p android --ndk-mode release -j 4" % (cmd_path, proj_path)
        execute_command(build_cmd)

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
            if os_is_win32():
                if is_32bit_windows():
                    bit_str = ""
                else:
                    bit_str = "-x86_64"
                sys_folder_name = "windows%s" % bit_str
            elif os_is_mac():
                sys_folder_name = "darwin-x86_64"

            # set strip execute file name
            if os_is_win32():
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
                    self.trip_libs(strip_cmd_path, "%s/%s" % (android_out_dir, fold))

            # strip x86 libs
            strip_cmd_path = os.path.join(ndk_root, "toolchains/x86-4.8/prebuilt/%s/i686-linux-android/bin/%s" % (sys_folder_name, strip_execute_name))
            if os.path.exists(strip_cmd_path) and os.path.exists(os.path.join(android_out_dir, "x86")):
                self.trip_libs(strip_cmd_path, "%s/x86" % android_out_dir)

        # remove the project
        rmdir(proj_path)

    def trip_libs(self, strip_cmd, folder):
        if os_is_win32():
            for name in os.listdir(folder):
                if name[-2:] != ".a":
                    pass
                full_name = os.path.join(folder, name)
                command = "%s -S %s" % (strip_cmd, full_name)
                execute_command(command)
        else:
            strip_cmd = "%s -S %s/*.a" % (strip_cmd, folder)
            execute_command(strip_cmd)


    def modify_mk(self, mk_file):
        if os.path.isfile(mk_file):
            file_obj = open(mk_file, "a")
            file_obj.write("\nAPP_ABI :=armeabi armeabi-v7a x86\n")
            file_obj.close()

    def clean_libs(self):
        print "to clean libs"
        rmdir(self.lib_dir)


if __name__ == "__main__":
    parser = ArgumentParser(description="Generate prebuilt engine for Cocos Engine.")
    parser.add_argument('-c', dest='clean', action="store_true", help='clean libs folder')
    parser.add_argument('-all', dest='all', action="store_true", help='compile all platform')
    parser.add_argument('--win', dest='win', action="store_true", help='compile windows platform')
    parser.add_argument('--mac', dest='mac', action="store_true", help='compile mac platform')
    parser.add_argument('--android', dest='android', action="store_true",help='complile android platform')
    parser.add_argument('--dis-strip', "--disable-strip", dest='disable_strip', action="store_true", help='Disable the strip of the generated libs.')
    parser.add_argument('--repo-x',  dest='repo_x', help='Set the repo path of cocos2d-x.')
    parser.add_argument('--vs', dest='vs_version', help='visual studio version, such as 2013.', default=2013)

    (args, unknown) = parser.parse_known_args()

    if len(unknown) > 0:
        print("unknown arguments: %s" % unknown)

    if args.repo_x is None:
        print("ERROR! must set repo of cocos2d-x")
        exit(1)
    if not args.win and not args.mac and not args.android:
        args.all = True

    beginSecond = time.time()
    print ">>> Bgein Compile at %s" % time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(beginSecond))

    compiler = CocosLibsCompiler(args)
    compiler.compile()

    endSecond = time.time()
    print ">>> Bgein Compile at %s" % time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(beginSecond))
    print ">>> End Compile at %s" % time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(endSecond))
    interSecond = endSecond - beginSecond
    interSecond = int(interSecond)
    print ">>> Use Second %d" % interSecond
    houre = interSecond/(60*60)
    interSecond = interSecond%(60*60)
    minute = interSecond/60
    second = interSecond%60
    print ">>> Use Time %d:%d:%d" % (houre, minute, second)

