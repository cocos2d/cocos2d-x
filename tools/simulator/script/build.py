#!/usr/bin/env python
#coding=utf-8
#
# ./build.py
#
#

"""****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************"""

import os.path, errno
import sys
import traceback
import string
import shutil
import subprocess
import re
from datetime import date

def os_is_win32():
    return sys.platform == 'win32'

def os_is_mac():
    return sys.platform == 'darwin'

def mkdir(dir_path):
    try:
        os.makedirs(dir_path)
    except OSError as exc: # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(dir_path):
            pass
        else: raise

def rmdir(dir_path):
    if os.path.isdir(dir_path):
        shutil.rmtree(dir_path)

def rm(file_path):
    if os.path.isfile(file_path):
        os.remove(file_path)

class Logging:
    # TODO maybe the right way to do this is to use something like colorama?
    RED = '\033[31m'
    GREEN = '\033[32m'
    YELLOW = '\033[33m'
    MAGENTA = '\033[35m'
    RESET = '\033[0m'

    @staticmethod
    def _print(s, color=None):
        if color and sys.stdout.isatty() and sys.platform != 'win32':
            print(color + s + Logging.RESET)
        else:
            print(s)

    @staticmethod
    def debug(s):
        Logging._print(s, Logging.MAGENTA)

    @staticmethod
    def info(s):
        Logging._print(s, Logging.GREEN)

    @staticmethod
    def warning(s):
        Logging._print(s, Logging.YELLOW)

    @staticmethod
    def error(s):
        Logging._print(s, Logging.RED)

#
## class Logging __END__
#
####################################################################################################


#
class SimulatorCompiler(object):
    """docstring for SimulatorCompiler"""
    def __init__(self):
        super(SimulatorCompiler, self).__init__()

        Logging.debug( "Welcome to Simulator Compiler" )

        self.simulator_output_dir_for_cocos  = "/Users/dualface/Public/cocos-simulator-bin" if os_is_mac() else "Z:/cocos-simulator-bin"
        self.simulator_output_dir_for_framework = "/tmp/simulator/framework" if os_is_mac() else "Z:/framework"
        self.output_dir = ""
        self.script_path = os.path.realpath(__file__)
        self.simulator_abs_path = os.path.dirname(os.path.dirname(self.script_path))
        self.cocos2d_root = os.path.join(self.simulator_abs_path,"../..")
        self.backup_file_list = {}
        if os_is_mac():
            self.cocos_bin = os.path.join(self.cocos2d_root, "tools/cocos2d-console/bin/cocos")
        elif os_is_win32():
            self.cocos_bin = os.path.join(self.cocos2d_root, "tools/cocos2d-console/bin/cocos.bat")
        else:
            self.cocos_bin = "cocos"

        self.is_clean_before_build = True

        # mkdir(os.path.join(self.simulator_abs_path,"src"))

    def update_source_repo(self):
        command = ' '.join([
            "cd %s && " % self.cocos2d_root,
            "git reset --hard && "
            "git pull && ",
            "python download-deps.py -r 'no'"
            ])

        Logging.debug(command)
        self.run_cmd(command)

    def hard_reset_source_repo(self):
        command = ' '.join([
            "cd %s && " % (self.cocos2d_root),
            "git reset --hard"
            ])

        Logging.debug(command)
        self.run_cmd(command)

    def update_source_info(self):
        info_plist_src = os.path.join(os.path.dirname(self.script_path),"info.plist")
        info_plist_dst = os.path.join(self.simulator_abs_path,"frameworks/runtime-src/proj.ios_mac/mac/Info.plist")
        shutil.copyfile(info_plist_src,info_plist_dst)

        game_rc_src = os.path.join(os.path.dirname(self.script_path),"game.rc")
        game_rc_dst = os.path.join(self.simulator_abs_path,"frameworks/runtime-src/proj.win32/game.rc")
        shutil.copyfile(game_rc_src,game_rc_dst)

        file_list = [info_plist_dst, game_rc_dst]
        keyword_map = {"__COCOS_VERSION__":self.get_cocos_version(),"__BUILD_DATE__":date.today().strftime("%Y%m%d")}
        for f in file_list:
            self.replace_keyword_with_file(f,keyword_map)

    def get_cocos_version(self):
        match_str = "cocos2d-x (.)*"
        content = self.get_content_from_file(os.path.join(self.cocos2d_root,"cocos/cocos2d.cpp"))
        ret = re.search(match_str, content)

        version = "3.5beta0"
        if ret:
            version = ret.group(0).replace("cocos2d-x ", "").replace("\";","")
        return version

    def revert_backup_files(self):
        Logging.debug( "" )
        Logging.debug( "----------------------------------------" )
        Logging.debug( "Revert file" )
        Logging.debug( "----------------------------------------" )
        Logging.debug( "" )

        file_list = self.backup_file_list

        for key in file_list:
            src = file_list[key]
            dst = key
            print src, '->\n', dst
            shutil.copyfile(src, dst)

    def backup_file(self,file_path):
        if os.path.isfile(file_path):
            backup_file_path = file_path + ".bak"
            backup_file_path = os.path.realpath(backup_file_path)
            file_path = os.path.realpath(file_path)
            print file_path, '->\n', backup_file_path
            shutil.copyfile(file_path, backup_file_path)
            self.backup_file_list[file_path] = backup_file_path


    def openFolder(self,path):
        path = self.convert_path_to_python(path)

        if sys.platform == 'darwin':
            Logging.debug(path)
            subprocess.call(' '.join(['open', '--', path]), shell=True)
        elif sys.platform == 'win32':
            subprocess.call(' '.join(['explorer',  self.convert_path_to_win32(path)]), shell=True)
        else:
            print("Not support %s", sys.platform)

    def replace_keyword_with_content(self,content,old,new):
        found_string = string.find(content,old) >= 0
        return found_string, string.replace(content,old,new)

    def get_content_from_file(self,file_path):
        if not os.path.isfile(file_path):
            raise Exception("Could not find (%s)" % (file_path))

        with open(file_path) as f:
            return f.read()

    def write_content_to_file(self,content, file_path):
        if not os.path.isfile(file_path):
            raise Exception("Could not find (%s)" % (file_path))

        with open(file_path, 'w') as f:
            f.write(content)

    def replace_keyword_with_file(self,file_path,keyword_map):
        content = self.get_content_from_file(file_path)

        found = False
        for k in keyword_map:
            old, new = k, keyword_map[k]
            has_found, content = self.replace_keyword_with_content(content, old, new)
            if has_found :
                found = has_found

        if found == True:
            self.backup_file(file_path)
            self.write_content_to_file(content,file_path)

    def get_keywords(self):
        osx_keyword = {
            "CC_TARGET_OS_IPHONE,":"CC_TARGET_OS_IPHONE,\n\"COCOS2D_DEBUG=1\",",
            "CC_TARGET_OS_MAC,":"CC_TARGET_OS_MAC,\n\"COCOS2D_DEBUG=1\",",
            "COCOS2D_DEBUG=0":"COCOS2D_DEBUG=1",
        }

        win_keyword = {
            "_WINDOWS":"_WINDOWS;COCOS2D_DEBUG=1",
        }

        if os_is_mac():
            return osx_keyword
        if os_is_win32():
            return win_keyword

        return {}

    def convert_path_to_python(self,path):
        """ Convert path which include space to correct style which python can treat correctly.

            eg: on mac: convert '/usr/xxx/apache-ant\ 1.9.3' to '/usr/xxx/apache-ant 1.9.3'
            eg: on windows: convert '"c:\apache-ant 1.9.3"\bin' to 'c:\apache-ant 1.9.3\bin'
        """
        ret = path
        if os_is_mac():
            ret = path.replace("\ ", " ")

        if os_is_win32():
            ret = ret.replace("\"", "")

        # print("!!!!! Convert %s to %s\n" % (path, ret))
        return ret

    def convert_path_to_win32(self,path):
        return path.replace("/","\\")

    def run_cmd(self,command):
        Logging.debug("Run command %s" % (command))

        ret = subprocess.call(command, shell=True)
        if ret != 0:
            message = "Error running command, return code: %s" % str(ret)

        return ret


    def get_depend_project_file_list(self,workpath):
        file_list = []

        if os_is_mac():
            IOS_MAC_PROJECT_SUFFIX = "project.pbxproj"
            IOS_MAC_PROJECT_REFERENCES_TAG = 'ProjectRef ='
            IOS_MAC_PROJECT_NAME_RE = r'\w+.xcodeproj'
            IOS_MAC_PROJECT_PATH_RE = r'name = %s; path = (.)*.xcodeproj'

            project_file_path = os.path.join(self.simulator_abs_path,
                                            "frameworks/runtime-src/proj.ios_mac/simulator.xcodeproj",
                                            IOS_MAC_PROJECT_SUFFIX)
            contents_str = self.get_content_from_file(project_file_path)
            lines = re.split(r'\n', contents_str)

            simulator_mac_project_path = os.path.dirname(os.path.dirname(project_file_path))
            project_references = []
            for l in lines:
                if IOS_MAC_PROJECT_REFERENCES_TAG in l:
                    ret = re.search(IOS_MAC_PROJECT_NAME_RE, l)
                    if ret: project_references.append(ret.group(0))

            for references in project_references:
                re_str = IOS_MAC_PROJECT_PATH_RE % references
                ret = re.search(re_str, contents_str)
                if ret:
                    match_str = ret.group(0)
                    match_str = match_str.replace("name = %s; path = " % references, "")
                    match_str = match_str.replace('"', "")
                    file_list.append(os.path.join(simulator_mac_project_path, match_str, IOS_MAC_PROJECT_SUFFIX))

        elif os_is_win32():
            project_file_path = os.path.join(self.simulator_abs_path, "frameworks/runtime-src/proj.win32/simulator.sln")
            simulator_win32_project_path = os.path.dirname(project_file_path)
            depends_project_list = ["simulator.vcxproj"
                ,"../../../../../cocos/2d/libcocos2d.vcxproj"
                ,"../../../../../cocos/scripting/lua-bindings/proj.win32/libluacocos2d.vcxproj"
                ,"../../../libsimulator/proj.win32/libsimulator.vcxproj"
                ,"../../../../../cocos/scripting/js-bindings/proj.win32/libjscocos2d.vcxproj"]

            for proj in depends_project_list:
                file_list.append(self.convert_path_to_win32(os.path.join(simulator_win32_project_path, proj)))

        return file_list

    # @configuration: ["debug","release"]
    def compile_for_osx(self,configuration="debug"):
        if self.is_clean_before_build:
            project_directory = os.path.join(self.simulator_abs_path,
                                    "frameworks/runtime-src/proj.ios_mac/")

            command = ' '.join([
                "cd %s" % (project_directory),
                "&&",
                "xcodebuild -alltargets -configuration %s clean" % ("Debug" if configuration=='debug' else 'Release')
                ])
            self.run_cmd(command)

        command = ' '.join([
            "cd \"%s\"" % (self.simulator_abs_path),
            " && mkdir -p %s" % (os.path.join(self.simulator_abs_path,"src")),
            " && %s compile -p mac -m %s -o \"%s\" --no-res" % (self.cocos_bin
                , "debug" if configuration=='debug' else "release"
                , os.path.join(self.output_dir,"mac")),
            " && strip %s" % (os.path.join(self.output_dir,"mac","Simulator.app/Contents/MacOS/Simulator")),
            ])

        return self.run_cmd(command)

    def compile_for_ios(self,configuration):
        if self.is_clean_before_build:
            project_directory = os.path.join(self.simulator_abs_path,
                                    "frameworks/runtime-src/proj.ios_mac/")

            command = ' '.join([
                "cd %s" % (project_directory),
                "&&",
                "xcodebuild -alltargets -configuration %s clean" % ("Debug" if configuration=='debug' else 'Release')
                ])
            self.run_cmd(command)

        command = ' '.join([
            "cd \"%s\"" % (self.simulator_abs_path),
            " && %s compile -p ios -m %s -o \"%s\" --no-res" % (self.cocos_bin
                , "debug" if configuration=='debug' else "release"
                , os.path.join(self.output_dir,"ios")),
            " && strip %s" % (os.path.join(self.output_dir,"ios","Simulator.app/Simulator")),
            " && rm -fr %s" % (os.path.join(self.output_dir,"ios","Simulator.app.dSYM")),
            ])

        return self.run_cmd(command)

    def compile_for_ios_ipa(self,configuration):
        project_directory = os.path.join(self.simulator_abs_path,
                                "frameworks/runtime-src/proj.ios_mac/")

        if self.is_clean_before_build:
            command = ' '.join([
                "cd %s" % (project_directory),
                "&&",
                "xcodebuild -alltargets -configuration %s clean" % ("Debug" if configuration=='debug' else 'Release')
                ])
            self.run_cmd(command)

        sign = "iPhone Distribution: Xiamen YAJI Software Co.,LTD"
        scheme = "Simulator iOS"
        ipa_name = "Simulator"
        jobs = 4
        output_dir = os.path.join(self.output_dir,"ios")

        mkdir(output_dir)
        ipa_file_path = os.path.join(output_dir, ipa_name + ".ipa")
        rm(ipa_file_path)
        command = ' '.join([
            "cd \"%s\"" % (project_directory),
            " && xcodebuild archive -scheme \"%s\" -archivePath \"%s.xcarchive\" -configuration %s -jobs %d" % (scheme,scheme,"Debug" if configuration=='debug' else "Release",jobs),
            " && xcodebuild -exportArchive -archivePath \"%s.xcarchive\" -exportPath \"%s\" -exportFormat ipa -exportSigningIdentity \"%s\"" % (scheme,os.path.join(output_dir,ipa_name),sign),
            ])

        return self.run_cmd(command)

    def compile_for_win32(self,configuration):
        win32_output_dir = os.path.join(self.output_dir,"win32")
        win32_output_dir = self.convert_path_to_win32(win32_output_dir)
        mkdir(win32_output_dir)

        lang_copy_command = ' '.join([
            "xcopy /Y %s %s" % (self.convert_path_to_win32(os.path.join(self.simulator_abs_path,"frameworks/runtime-src/Classes/ide-support/lang")),
                                win32_output_dir)
            ])
        if configuration=='debug':
            win32_src_dir = os.path.join(self.simulator_abs_path,"runtime/win32/")
            win32_src_dir = self.convert_path_to_win32(win32_src_dir)
            command = ' '.join([
                "cd \"%s\"" % (self.simulator_abs_path),
                " && %s compile -p win32 -m debug --no-res" % (self.cocos_bin),
                " && xcopy /Y %s*.dll %s" % (win32_src_dir, win32_output_dir),
                " && xcopy /Y %s*.exe %s" % (win32_src_dir, win32_output_dir),
                " && %s" % (lang_copy_command),
                " && xcopy /Y %s*.dll %s" % (self.convert_path_to_win32(os.path.join(os.path.dirname(self.script_path),"dll/")),win32_output_dir)
            ])
        else:
            command = ' '.join([
                "cd \"%s\"" % (self.simulator_abs_path),
                "&&",
                "%s compile -p win32 -m release --no-res -o %s" % (self.cocos_bin,win32_output_dir),
                "&&",
                "%s" % (lang_copy_command)
                ])

        return self.run_cmd(command)

    def compile_for_android(self,configuration):
        rename_command = ' '.join([
                "mv %s %s" % (os.path.join(self.output_dir,"android","simulator-debug.apk"),
                              os.path.join(self.output_dir,"android","Simulator.apk"))
            ])

        command = ' '.join([
            "cd",
            "\"%s\"" % (self.simulator_abs_path),
            "&&",
            "%s compile -p android -m %s -o \"%s\" --no-res" % (self.cocos_bin
                ,"debug" if configuration=='debug' else "release"
                , os.path.join(self.output_dir,"android")),
            "&&",
            "%s" % (rename_command),
            ])

        return self.run_cmd(command)

    def compile_all(self,configuration):
        if os_is_mac():
            self.compile_for_osx(configuration)
            self.compile_for_ios(configuration)
            self.compile_for_ios_ipa(configuration)
            self.compile_for_android("debug")
        elif os_is_win32():
            self.compile_for_win32(configuration)

    def compile_for_cocos(self):
        dir_path = self.simulator_output_dir_for_cocos
        self.change_output_directory(dir_path)

        self.compile_all("release")
        self.openFolder(dir_path)

    def compile_for_framework(self):
        dir_path = self.simulator_output_dir_for_framework
        self.change_output_directory(dir_path)

        self.compile_all("debug")
        self.openFolder(dir_path)

    def change_cocos2d_debug_macro_to_1(self):
        file_list = self.get_depend_project_file_list(self.simulator_abs_path)
        keyword = self.get_keywords()

        for l in file_list:
            self.replace_keyword_with_file(l, keyword)

    def change_output_directory(self, path):
        mkdir(path)
        self.output_dir = path

    def run(self):
        self.change_cocos2d_debug_macro_to_1()
        self.compile_for_cocos()
        self.compile_for_framework()
        self.revert_backup_files()

        return 0
#
## class SimulatorCompiler __END__
#
###################################################################################################


# -------------- main --------------
if __name__ == '__main__':
    try:
        if os_is_mac() or os_is_win32():
            Compiler = SimulatorCompiler()
            Compiler.update_source_repo()
            Compiler.update_source_info()
            Compiler.run()
            Compiler.hard_reset_source_repo()
        else:
            print("build.py only run on win32 or mac.")
        sys.exit(0)
    except Exception as e:
        traceback.print_exc()
        sys.exit(1)

