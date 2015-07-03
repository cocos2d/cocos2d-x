#!/usr/bin/python
#-*- coding: UTF-8 -*-
# ----------------------------------------------------------------------------
# Generate Cocos Simulator
#
# Copyright 2015 (C) zhangbin
#
# License: MIT
# ----------------------------------------------------------------------------

import os
import re
import shutil
import string

import utils_cocos

from datetime import date
from custom_error import Logging, CustomError
from argparse import ArgumentParser

class SimulatorCompiler(object):
    SIMULATOR_PROJ_PATH = 'tools/simulator'
    COCOS_CMD_PATH = 'tools/cocos2d-console/bin/cocos'

    DEFAULT_OUTPUT_FOLDER_NAME = 'simulator'

    SUPPORT_PLATFORMS = {
        "win" : [ 'win32', 'android' ],
        "mac" : [ 'ios', 'mac', 'android' ],
        "other" : [ 'android' ]
    }

    def __init__(self, args):
        self.cur_dir = os.path.realpath(os.path.dirname(__file__))
        self.engine_root = os.path.abspath(os.path.join(self.cur_dir, os.pardir, os.pardir, os.pardir))
        self.simulator_abs_path = os.path.join(self.engine_root, SimulatorCompiler.SIMULATOR_PROJ_PATH)
        self.cocos_bin = os.path.join(self.engine_root, SimulatorCompiler.COCOS_CMD_PATH)

        # get the full path of output dir.
        if args.out_dir is None:
            self.simulator_output_dir = os.path.join(self.engine_root, SimulatorCompiler.DEFAULT_OUTPUT_FOLDER_NAME)
        else:
            out_dir = os.path.expanduser(args.out_dir)
            if os.path.isabs(out_dir):
                self.simulator_output_dir = os.path.normpath(out_dir)
            else:
                self.simulator_output_dir = os.path.normpath(os.path.abspath(out_dir))

        # get arguments
        self.is_clean_before_build = args.do_clean
        if args.compile_mode is None:
            self.mode = 'debug'
        else:
            self.mode = args.compile_mode
        self.platform = args.platform
        self.build_log = ""
        self.vs_version = args.vs_version

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

        if utils_cocos.os_is_mac():
            return osx_keyword
        if utils_cocos.os_is_win32():
            return win_keyword

        return {}

    def convert_path_to_python(self,path):
        """ Convert path which include space to correct style which python can treat correctly.

            eg: on mac: convert '/usr/xxx/apache-ant\ 1.9.3' to '/usr/xxx/apache-ant 1.9.3'
            eg: on windows: convert '"c:\apache-ant 1.9.3"\bin' to 'c:\apache-ant 1.9.3\bin'
        """
        ret = path
        if utils_cocos.os_is_mac():
            ret = path.replace("\ ", " ")

        if utils_cocos.os_is_win32():
            ret = ret.replace("\"", "")

        return ret

    def convert_path_to_win32(self,path):
        return path.replace("/","\\")

    def get_depend_project_file_list(self):
        file_list = []

        if utils_cocos.os_is_mac():
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

        elif utils_cocos.os_is_win32():
            WIN32_PROJECT_TAG = "Project(\""
            project_file_path = os.path.join(self.simulator_abs_path, "frameworks/runtime-src/proj.win32/simulator.sln")
            simulator_win32_project_path = os.path.dirname(project_file_path)

            content_str = self.get_content_from_file(project_file_path)
            lines = content_str.split('\n')
            for l in lines:
                if l.startswith(WIN32_PROJECT_TAG):
                    ret = re.compile('"(.*?)"').findall(l.split(',')[1])
                    if ret:
                        path = self.convert_path_to_win32(os.path.join(simulator_win32_project_path, ret[0]))
                        file_list.append(path)

        return file_list

    def compile_for_osx(self):
        if self.is_clean_before_build:
            project_directory = os.path.join(self.simulator_abs_path, "frameworks/runtime-src/proj.ios_mac/")

            command = "xcodebuild -alltargets -configuration %s clean" % ("Debug" if self.mode == 'debug' else 'Release')
            utils_cocos.execute_command(command, project_directory)

        command = ' '.join([
            "mkdir -p %s" % (os.path.join(self.simulator_abs_path, "src")),
            " && %s compile -p mac -m %s -o \"%s\" --no-res --compile-script 0" % (self.cocos_bin
                , "debug" if self.mode == 'debug' else "release"
                , os.path.join(self.simulator_output_dir,"mac")),
            " && strip %s" % (os.path.join(self.simulator_output_dir,"mac","Simulator.app/Contents/MacOS/Simulator")),
            ])

        ret = utils_cocos.execute_command(command, self.simulator_abs_path)
        self.build_log += "Build osx %s %s\n" % (self.mode, "success" if ret == 0 else "failed")
        return ret

    def compile_for_ios(self):
        if self.is_clean_before_build:
            project_directory = os.path.join(self.simulator_abs_path, "frameworks/runtime-src/proj.ios_mac/")

            command = "xcodebuild -alltargets -configuration %s clean" % ("Debug" if self.mode =='debug' else 'Release')
            utils_cocos.execute_command(command, project_directory)

        command = ' '.join([
            " %s compile -p ios -m %s -o \"%s\" --no-res --compile-script 0" % (self.cocos_bin
                , "debug" if self.mode == 'debug' else "release"
                , os.path.join(self.simulator_output_dir,"ios")),
            " && strip %s" % (os.path.join(self.simulator_output_dir,"ios","Simulator.app/Simulator")),
            " && rm -fr %s" % (os.path.join(self.simulator_output_dir,"ios","Simulator.app.dSYM")),
            ])

        ret = utils_cocos.execute_command(command, self.simulator_abs_path)
        self.build_log += "Build ios %s %s\n" % (self.mode, "success" if ret == 0 else "failed")
        return ret

    def compile_for_win32(self):
        win32_output_dir = os.path.join(self.simulator_output_dir, "win32")
        win32_output_dir = self.convert_path_to_win32(win32_output_dir)
        utils_cocos.mkdir(win32_output_dir)

        lang_file_path = os.path.join(self.simulator_abs_path,"frameworks/runtime-src/Classes/ide-support/lang")
        lang_copy_command = "xcopy /Y %s %s" % (self.convert_path_to_win32(lang_file_path), win32_output_dir)

        # get the vs version should be used
        if self.vs_version is None:
            ver_param = ''
        else:
            ver_param = '--vs %d' % self.vs_version

        if self.mode == 'debug':
            win32_src_dir = os.path.join(self.simulator_abs_path,"runtime/win32/")
            win32_src_dir = self.convert_path_to_win32(win32_src_dir)
            win32_dll_dir = self.convert_path_to_win32(os.path.join(os.path.dirname(self.cur_dir),"dll/"))
            command = ' '.join([
                " %s compile -p win32 -m debug --no-res --compile-script 0 %s" % (self.cocos_bin, ver_param),
                " && xcopy /Y %s*.dll %s" % (win32_src_dir, win32_output_dir),
                " && xcopy /Y %s*.exe %s" % (win32_src_dir, win32_output_dir),
                " && %s" % (lang_copy_command),
                " && if exist %s*.dll xcopy /Y %s*.dll %s" % (win32_dll_dir,win32_dll_dir,win32_output_dir)
            ])
        else:
            command = ' '.join([
                " %s compile -p win32 -m release --no-res --compile-script 0 -o %s %s" % (self.cocos_bin,win32_output_dir,ver_param),
                " && %s" % (lang_copy_command),
                ])

        ret = utils_cocos.execute_command(command, self.simulator_abs_path, use_py_path=False)

        self.build_log += "Build win32 %s %s\n" % (self.mode, "success" if ret == 0 else "failed")
        return ret

    def compile_for_android(self):
        rename_command = ' '.join([
                "mv %s %s" % (os.path.join(self.simulator_output_dir,"android","simulator-debug.apk"),
                              os.path.join(self.simulator_output_dir,"android","Simulator.apk"))
            ])

        command = ' '.join([
            " %s compile -p android --ndk-mode %s -o \"%s\" --no-res --compile-script 0" % (self.cocos_bin
                 , "debug" if self.mode == 'debug' else "release"
                 , os.path.join(self.simulator_output_dir,"android")),
            "&& %s" % (rename_command),
            ])

        ret = utils_cocos.execute_command(command, self.simulator_abs_path)
        self.build_log += "Build android %s %s\n" % (self.mode, "success" if ret == 0 else "failed")
        return ret

    def compile_all(self):
        if utils_cocos.os_is_mac():
            self.compile_for_android()
            self.compile_for_osx()
            self.compile_for_ios()
        elif utils_cocos.os_is_win32():
            self.compile_for_win32()
            self.compile_for_android()

    def do_compile(self):
        if self.platform == 'all':
            self.compile_all()
            return

        if utils_cocos.os_is_mac():
            support_platforms = SimulatorCompiler.SUPPORT_PLATFORMS['mac']
        elif utils_cocos.os_is_win32():
            support_platforms = SimulatorCompiler.SUPPORT_PLATFORMS['win']
        else:
            support_platforms = SimulatorCompiler.SUPPORT_PLATFORMS['other']

        if self.platform not in support_platforms:
            raise CustomError('%s is not support in current system.' % self.platform,
                              CustomError.ERROR_WRONG_ARGS)

        if self.platform == 'win32':
            self.compile_for_win32()
        elif self.platform == 'android':
            self.compile_for_android()
        elif self.platform == 'ios':
            self.compile_for_ios()
        elif self.platform == 'mac':
            self.compile_for_osx()

    def change_cocos2d_debug_macro_to_1(self, file_list):
        keyword = self.get_keywords()
        for file_path in file_list:
            self.replace_keyword_with_file(file_path, keyword)

    def update_bundle_version(self):
        build_date = date.today().strftime("%Y%m%d")

        if utils_cocos.os_is_mac():
            # mac
            info_plist_path = os.path.join(self.simulator_abs_path, "frameworks/runtime-src/proj.ios_mac/mac/Info.plist")
            info_plist_content = self.get_content_from_file(info_plist_path)

            match = re.compile('<key>CFBundleVersion</key>(\s)*<string>(.*?)</string>').findall(info_plist_content)
            if len(match):
                build_date_tag = "<string>%s</string>" % match[0][1]
                keyword_map = { build_date_tag : "<string>%s</string>" % build_date }
                self.replace_keyword_with_file(info_plist_path, keyword_map)

        if utils_cocos.os_is_win32():
            # win32
            game_rc_path = os.path.join(self.simulator_abs_path,"frameworks/runtime-src/proj.win32/game.rc")
            game_rc_content = self.get_content_from_file(game_rc_path)
            match = re.compile('"Version[^\(]*\(.*\)"').findall(game_rc_content)
            if len(match):
                build_info_str = match[0]
                m = re.match(r'"(Version[^\(]*)\(.*\)', build_info_str)
                target_str = '"%s(%s)"' % (m.group(1), build_date)
                keyword_map = { build_info_str : target_str}
                self.replace_keyword_with_file(game_rc_path,keyword_map)

    def backup_files(self, files):
        for f in files:
            full_path = os.path.abspath(f)
            if not os.path.isfile(full_path):
                continue

            backup_file_path = '%s.bak' % full_path
            shutil.copyfile(full_path, backup_file_path)

    def rollback_files(self, files):
        for f in files:
            full_path = os.path.abspath(f)
            backup_file_path = '%s.bak' % full_path
            if not os.path.isfile(backup_file_path):
                continue

            try:
                shutil.copyfile(backup_file_path, full_path)
                os.remove(backup_file_path)
            except:
                print('Roll back file %s failed.' % full_path)
                print('Please rename %s to %s manually.' % (backup_file_path, full_path))
                pass

    def run(self):
        if self.is_clean_before_build:
            utils_cocos.rmdir(self.simulator_output_dir)

        # backup some files
        modify_files = self.get_depend_project_file_list()
        if utils_cocos.os_is_mac():
            modify_files.append(os.path.join(self.simulator_abs_path, 'frameworks/runtime-src/proj.ios_mac/mac/Info.plist'))
        elif utils_cocos.os_is_win32():
            modify_files.append(os.path.join(self.simulator_abs_path, 'frameworks/runtime-src/proj.win32/game.rc'))

        self.backup_files(modify_files)

        try:
            # modify bundle version
            self.update_bundle_version()

            # modify project config files
            self.change_cocos2d_debug_macro_to_1(modify_files)

            # compile simulator
            self.do_compile()
        except Exception as e:
            raise e
        finally:
            # roll back modified files
            self.rollback_files(modify_files)
            Logging.info("")
            Logging.info(self.build_log)
            Logging.info("")

        return 0

if __name__ == '__main__':
    parser = ArgumentParser(description="Generate Cocos Simulator.")
    parser.add_argument('-c', '--clean', dest='do_clean', action='store_true',
                        help='Clean the output directory before generating. Will remove the output directory at first.')
    parser.add_argument('-m', "--mode", dest='compile_mode', type=str, choices=['debug', 'release'],
                        help='Generate simulator for debug or release. Default is debug.')
    parser.add_argument('-o', '--output', dest='out_dir',
                        help='Where to save Cocos Simulator. Default is the simulator folder in the root path of engine.')
    parser.add_argument('-p', '--platform', dest='platform', required=True,
                        choices=['ios', 'mac', 'android', 'win32', 'all'],
                        help='Which platform will be generated for.')
    parser.add_argument('--vs', dest='vs_version', type=int,
                        help='Specify the Visual Studio version will be used. Such as: 2013. Default find available version automatically.')

    (args, unknown) = parser.parse_known_args()
    if len(unknown) > 0:
        print("unknown arguments: %s" % unknown)

    compiler = SimulatorCompiler(args)
    compiler.run()
