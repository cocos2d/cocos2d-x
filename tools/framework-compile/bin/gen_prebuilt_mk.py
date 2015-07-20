#!/usr/bin/python
# ----------------------------------------------------------------------------
# generate the prebuilt Android.mk from source code Android.mk
#
# Copyright 2014 (C) zhangbin
#
# License: MIT
# ----------------------------------------------------------------------------
'''
generate the prebuilt Android.mk from source code Android.mk
'''

import os
import shutil
import re

from argparse import ArgumentParser

class MKGenerator(object):

    SRC_FILE_CFG_PATTERN = r"^LOCAL_SRC_FILES[ \t]+[\:\+]=[ \t]+.+"
    INCLUDE_CFG_PATTERN  = r"^include[ \t]+\$\(BUILD_STATIC_LIBRARY\)"

    LIB_MODULE_PATTERN = r"^LOCAL_MODULE[ \t]+\:=[ \t]+(.+)"
    LIB_MODULE_FILENAME_PATTERN   = r"^LOCAL_MODULE_FILENAME[ \t]+\:=[ \t]+(.+)"

    EXPORT_INCLUDE_PATTERN = r"^LOCAL_EXPORT_C_INCLUDES[ \t]+[\:\+]=[ \t]+(.+)"
    INCLUDE_MODULE_PATTERN = r"^\$\(call[ \t]*import-module,[ \t]*(.*)\)"


    KEY_IS_MODULE = 'is_module'
    KEY_MODULE_LINES = 'lines'

    def __init__(self, src_mk_path, lib_file_path, dst_mk_path=None):
        if os.path.isabs(src_mk_path):
            self.src_mk_path = src_mk_path
        else:
            self.src_mk_path = os.path.abspath(src_mk_path)

        if os.path.isabs(lib_file_path):
            self.lib_file_path = lib_file_path
        else:
            self.lib_file_path = os.path.abspath(lib_file_path)

        if dst_mk_path is None:
            self.dst_mk_path = os.path.join(os.path.dirname(src_mk_path), "Android-prebuilt.mk")
        else:
            if os.path.isabs(dst_mk_path):
                self.dst_mk_path = dst_mk_path
            else:
                self.dst_mk_path = os.path.abspath(dst_mk_path)

        dst_mk_dir = os.path.dirname(self.dst_mk_path)
        if not os.path.exists(dst_mk_dir):
            os.makedirs(dst_mk_dir)

        from utils_cocos import win2unix
        win2unix(self.src_mk_path)

    def get_lib_file_name(self, lines):
        module_file_name = None
        module_name = None
        for line in lines:
            trim_line = line.lstrip(" ")
            trim_line = trim_line.rstrip(" ")
            match1 = re.match(MKGenerator.LIB_MODULE_FILENAME_PATTERN, trim_line)
            if match1 is not None:
                module_file_name = match1.group(1)

            match2 = re.match(MKGenerator.LIB_MODULE_PATTERN, trim_line)
            if match2 is not None:
                module_name = match2.group(1)

        ret = None
        if module_file_name is not None:
            ret = "%s.a" % module_file_name
        elif module_name is not None:
            ret = "lib%s.a" % module_name

        return ret

    def modidy_src_file(self, lines, new_src_file):
        new_lines = []

        src_file_begin_flag = False
        added = False
        found_src_file_cfg = False
        for line in lines:
            trim_line = line.lstrip(" ")
            if re.match(MKGenerator.SRC_FILE_CFG_PATTERN, trim_line):
                found_src_file_cfg = True
                if not added:
                    new_lines.append("LOCAL_SRC_FILES := %s\n" % new_src_file)
                    added = True
                if line.endswith("\\\n"):
                    src_file_begin_flag = True
            elif src_file_begin_flag:
                if not line.endswith("\\\n"):
                    src_file_begin_flag = False
            else:
                new_lines.append(line)

        if not found_src_file_cfg:
            ret_lines = []
            for line in new_lines:
                ret_lines.append(line)
                if re.match(MKGenerator.LIB_MODULE_FILENAME_PATTERN, line):
                    ret_lines.append("LOCAL_SRC_FILES := %s\n" % new_src_file)
        else:
            ret_lines = new_lines

        return ret_lines

    def remove_config(self, lines, cfg_key):
        new_lines = []
        cfg_begin = False
        line_pattern = r"^%s[ ]+[\+\:]=[ ]+.+" % cfg_key
        for line in lines:
            trim_line = line.lstrip(" ")
            if re.match(line_pattern, trim_line):
                if line.endswith("\\\n"):
                    cfg_begin = True
            elif cfg_begin:
                if not line.endswith("\\\n"):
                    cfg_begin = False
            else:
                new_lines.append(line)

        return new_lines

    def modify_export_c_include(self, lines):
        if self.src_mk_path == self.dst_mk_path:
            return lines

        new_lines = []
        insert_idx = -1
        cur_idx = 0
        include_paths = []
        cfg_begin = False
        for line in lines:
            trim_line = line.lstrip(" ")
            match = re.match(MKGenerator.EXPORT_INCLUDE_PATTERN, trim_line)
            if match is not None:
                if insert_idx == -1:
                    insert_idx = cur_idx

                path_str = match.group(1)
                if line.endswith("\\\n"):
                    cfg_begin = True
                    path_str = path_str.replace("\\", "")
                include_paths += path_str.split()
            elif cfg_begin:
                path_str = trim_line
                if line.endswith("\\\n"):
                    path_str = path_str.replace("\\\n", "")
                else:
                    cfg_begin = False

                include_paths += path_str.split()
            else:
                new_lines.append(line)
            cur_idx += 1

        src_dir = os.path.dirname(self.src_mk_path)
        dst_dir = os.path.dirname(self.dst_mk_path)
        rel_path = os.path.relpath(src_dir, dst_dir)
        new_include_paths = []
        for include_path in include_paths:
            if include_path.startswith("$(LOCAL_PATH)"):
                new_path = include_path.replace("$(LOCAL_PATH)", "$(LOCAL_PATH)/%s" % rel_path)
            else:
                new_path = "$(LOCAL_PATH)/%s/%s" % (rel_path, include_path)
            new_include_paths.append(new_path)

        if len(new_include_paths) > 0:
            new_path_str = "LOCAL_EXPORT_C_INCLUDES := "
            new_path_str += " \\\n".join(new_include_paths)
            new_path_str += "\n"
            if insert_idx >= 0:
                new_lines.insert(insert_idx, new_path_str)
            else:
                new_lines.append(new_path_str)

        return new_lines

    def modify_include_cfg(self, lines):
        new_lines = []

        for line in lines:
            trim_line = line.lstrip(" ")
            if re.match(MKGenerator.INCLUDE_CFG_PATTERN, trim_line):
                new_lines.append("include $(PREBUILT_STATIC_LIBRARY)\n")
            else:
                new_lines.append(line)

        return new_lines

    def modify_import_module(self, lines):
        if self.src_mk_path == self.dst_mk_path:
            return lines

        new_lines = []

        ignore_strs = [
            "prebuilt"
        ]
        for line in lines:
            trim_line = line.lstrip(" ")
            match = re.match(MKGenerator.INCLUDE_MODULE_PATTERN, trim_line)
            if match is not None:
                module = match.group(1)
                need_modify = True
                for str in ignore_strs:
                    if module.find(str) >= 0:
                        need_modify = False
                        break

                if need_modify:
                    new_lines.append("$(call import-module, %s/prebuilt-mk)\n" % module)
                else:
                    new_lines.append(line)
            else:
                new_lines.append(line)

        return new_lines

    def use_whole_lib(self, lines):
        new_lines = []
        for line in lines:
            new_line = line.replace("LOCAL_STATIC_LIBRARIES", "LOCAL_WHOLE_STATIC_LIBRARIES")
            new_lines.append(new_line)

        ret_lines = []
        is_first_time = True
        pattern = r'LOCAL_WHOLE_STATIC_LIBRARIES[ \t]*:=.*'
        for line in new_lines:
            ret_line = line
            if re.match(pattern, line):
                if is_first_time:
                    is_first_time = False
                else:
                    ret_line = line.replace(":=", "+=")

            ret_lines.append(ret_line)

        return ret_lines

    def split_modules(self, origin_lines):
        ret = []
        cur_module = {}
        cur_module[MKGenerator.KEY_MODULE_LINES] = []
        cur_module[MKGenerator.KEY_IS_MODULE] = False

        pattern_begin = r'include[ \t]+\$\(CLEAR_VARS\)'
        pattern_end = r'include[ \t]+\$\(BUILD_STATIC_LIBRARY\)'
        for line in origin_lines:
            if re.match(pattern_begin, line):
                if len(cur_module[MKGenerator.KEY_MODULE_LINES]) > 0:
                    ret.append(cur_module)

                cur_module = {}
                cur_module[MKGenerator.KEY_MODULE_LINES] = []
                cur_module[MKGenerator.KEY_IS_MODULE] = True

            cur_module[MKGenerator.KEY_MODULE_LINES].append(line)

            if re.match(pattern_end, line):
                if len(cur_module[MKGenerator.KEY_MODULE_LINES]) > 0:
                    ret.append(cur_module)
                cur_module = {}
                cur_module[MKGenerator.KEY_MODULE_LINES] = []
                cur_module[MKGenerator.KEY_IS_MODULE] = False

        if len(cur_module[MKGenerator.KEY_MODULE_LINES]) > 0:
            ret.append(cur_module)

        return ret

    def handle_module(self, module_lines, relative_path):
        # modify the LOCAL_SRC_FILES
        lib_file_name = self.get_lib_file_name(module_lines)
        if lib_file_name is None:
            raise Exception("The mk file %s not specify module name." % self.src_mk_path)
        relative_path = "%s/$(TARGET_ARCH_ABI)/%s" % (relative_path, lib_file_name)
        dst_lines = self.modidy_src_file(module_lines, relative_path)

        # remove the LOCAL_C_INCLUDES & LOCAL_LDLIBS
        dst_lines = self.remove_config(dst_lines, "LOCAL_C_INCLUDES")
        dst_lines = self.remove_config(dst_lines, "LOCAL_LDLIBS")

        # modify the LOCAL_EXPORT_C_INCLUDES
        dst_lines = self.modify_export_c_include(dst_lines)

        # modify the line $(include BUILD_STATIC_LIBRARY)
        dst_lines = self.modify_include_cfg(dst_lines)

        # use whole libs
        dst_lines = self.use_whole_lib(dst_lines)

        return dst_lines

    def do_generate(self):
        src_mk_obj = open(self.src_mk_path)

        # open the dst file
        tmp_file = "%s-tmp" % self.src_mk_path
        use_tmp_file = False
        if self.dst_mk_path == self.src_mk_path:
            use_tmp_file = True
            dst_mk_obj = open(tmp_file, "w")
        else:
            dst_mk_obj = open(self.dst_mk_path, "w")

        relative_path = os.path.relpath(self.lib_file_path, os.path.dirname(self.dst_mk_path))

        # read the src file
        src_lines = src_mk_obj.readlines()

        modules = self.split_modules(src_lines)
        dst_lines = []
        for module in modules:
            if module[MKGenerator.KEY_IS_MODULE]:
                ret_lines = self.handle_module(module[MKGenerator.KEY_MODULE_LINES], relative_path)
            else:
                ret_lines = module[MKGenerator.KEY_MODULE_LINES]

            for l in ret_lines:
                dst_lines.append(l)

        # modify the import-module
        dst_lines = self.modify_import_module(dst_lines)

        dst_mk_obj.writelines(dst_lines)

        #close files
        dst_mk_obj.close()
        src_mk_obj.close()

        # rename the file if temp file used
        if use_tmp_file:
            os.remove(self.src_mk_path)
            os.rename(tmp_file, self.dst_mk_path)

if __name__ == "__main__":
    parser = ArgumentParser(description="Generate prebuilt engine for Cocos Engine.")
    parser.add_argument('-s', '--src-mk', dest='src_mk', help='The source Android.mk path.')
    parser.add_argument('-d', "--dst-mk", dest='dst_mk', help='The output path of Android.mk. Default is beside the source mk with name \"Android-prebuilt.mk\".')
    parser.add_argument('-l', "--lib-path", dest='lib_path', help='The lib file path.')
    (args, unknown) = parser.parse_known_args()

    gen_obj = MKGenerator(args.src_mk, args.lib_path, args.dst_mk)
    gen_obj.do_generate()
