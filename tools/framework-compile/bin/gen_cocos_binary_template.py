#!/usr/bin/python
#-*- coding: UTF-8 -*-

import os
import json
import excopy
import utils_cocos
import gen_prebuilt_mk
import modify_template
import re

from argparse import ArgumentParser

class CocosBinTemplateGenerator(object):

    KEY_COPY_CONFIG = 'template_copy_config'
    KEY_ANDROID_MKS = "android_mks"

    def __init__(self, args):
        print("Generate cocos binary template")

        # get path variables
        self.cur_dir = os.path.realpath(os.path.dirname(__file__))
        self.repo_x = os.path.realpath(args.repo_x)
        self.temp_dir = os.path.join(self.cur_dir, os.pardir, "templates")
        self.lib_dir = os.path.join(self.repo_x, 'prebuilt')
        self.engine_template_dir = os.path.join(self.repo_x, "templates")

        # get the template config info
        self.config_json = self.getConfigJson()

        # get engine version
        self.version = self.get_version_from_source()
        self.is_for_package = True
        try:
            self.is_for_package = args.is_for_package
        except Exception as e:
            print("[Warn] %s" % e)

    def generate(self):
        self.clean_template()
        self.copy_template()
        self.modify_binary_mk()
        self.gen_templates()

        # copy the templates into the templates folder of engine
        excopy.copy_files_in_dir(self.temp_dir, os.path.join(self.repo_x, "templates"))

        # remove the temp dir
        utils_cocos.rmdir(self.temp_dir)

    def clean_template(self):
        utils_cocos.rmdir(self.temp_dir)
        utils_cocos.rmdir(os.path.join(self.engine_template_dir, "cpp-template-binary"))
        utils_cocos.rmdir(os.path.join(self.engine_template_dir, "lua-template-binary"))
        utils_cocos.rmdir(os.path.join(self.engine_template_dir, "js-template-binary"))

    def copy_template(self):
        for item in self.config_json[CocosBinTemplateGenerator.KEY_COPY_CONFIG]:
            excopy.copy_files_with_config(item, self.repo_x, self.temp_dir)

        templates_dir = os.path.join(self.cur_dir, os.path.pardir, "bin-templates")
        excopy.copy_files_in_dir(os.path.join(templates_dir, "cpp-template-default"),
            os.path.join(self.temp_dir, "cpp-template-binary"))
        excopy.copy_files_in_dir(os.path.join(templates_dir, "lua-template-runtime"),
            os.path.join(self.temp_dir, "lua-template-binary"))
        excopy.copy_files_in_dir(os.path.join(templates_dir, "js-template-runtime"),
            os.path.join(self.temp_dir, "js-template-binary"))

    def modify_binary_mk(self):
        android_libs = os.path.join(self.lib_dir, "android")
        android_mks = self.config_json[CocosBinTemplateGenerator.KEY_ANDROID_MKS]
        for mk_file in android_mks:
            mk_file_path = os.path.join(self.repo_x, mk_file)
            dst_file_path = os.path.join(os.path.dirname(mk_file_path), "prebuilt-mk", os.path.basename(mk_file_path))
            tmp_obj = gen_prebuilt_mk.MKGenerator(mk_file_path, android_libs, dst_file_path)
            tmp_obj.do_generate()

        def process_file(sour, dest):
            f = open(sour)
            file_content = f.read()
            f.close()

            file_content = file_content.replace("__LIBS_DIR__", self.lib_dir)

            f = open(os.path.join(dest, os.path.basename(sour)), "w")
            f.write(file_content)
            f.close()

        utils_cocos.copy_files_with_cb(os.path.join(self.cur_dir, os.path.pardir, "x-modified"), self.repo_x, process_file)

    def getConfigJson(self):
        cfg_json_path = os.path.join(self.cur_dir, "template_binary_config.json")
        f = open(cfg_json_path)
        config_json = json.load(f)
        f.close()

        return config_json

    def gen_templates(self):
        dst_dir = self.temp_dir
        x_path = self.repo_x
        lib_dir = self.lib_dir
        # modify the VS project file of templates
        if self.is_for_package:
            version = self.version.replace(" ", "-")
            modifier = modify_template.TemplateModifier(x_path, lib_dir, version, self.is_for_package)
        else:
            modifier = modify_template.TemplateModifier(x_path, lib_dir, "no_use", self.is_for_package)
        cpp_proj_path = os.path.join(dst_dir, "cpp-template-binary/proj.win32/HelloCpp.vcxproj")
        lua_proj_path = os.path.join(dst_dir, "lua-template-binary/frameworks/runtime-src/proj.win32/HelloLua.vcxproj")
        js_proj_path = os.path.join(dst_dir, "js-template-binary/frameworks/runtime-src/proj.win32/HelloJavascript.vcxproj")
        modifier.modify_vs_proj(cpp_proj_path, "cpp")
        modifier.modify_vs_proj(lua_proj_path, "lua")
        modifier.modify_vs_proj(js_proj_path, "js")

        # modify the xcode project file of templates
        cpp_proj_path = os.path.join(dst_dir, "cpp-template-binary/proj.ios_mac/HelloCpp.xcodeproj/project.pbxproj")
        lua_proj_path = os.path.join(dst_dir, "lua-template-binary/frameworks/runtime-src/proj.ios_mac/HelloLua.xcodeproj/project.pbxproj")
        js_proj_path = os.path.join(dst_dir, "js-template-binary/frameworks/runtime-src/proj.ios_mac/HelloJavascript.xcodeproj/project.pbxproj")
        modifier.modify_xcode_proj(cpp_proj_path, "cpp")
        modifier.modify_xcode_proj(lua_proj_path, "lua")
        modifier.modify_xcode_proj(js_proj_path, "js")

        # modify the build-cfg.json for templates
        cpp_build_cfg = os.path.join(dst_dir, "cpp-template-binary/proj.android/build-cfg.json")
        lua_build_cfg = os.path.join(dst_dir, "lua-template-binary/frameworks/runtime-src/proj.android/build-cfg.json")
        js_build_cfg = os.path.join(dst_dir, "js-template-binary/frameworks/runtime-src/proj.android/build-cfg.json")
        self.modify_android_build_cfg(cpp_build_cfg, "cpp")
        self.modify_android_build_cfg(lua_build_cfg, "lua")
        self.modify_android_build_cfg(js_build_cfg, "js")

        self.modify_version_json(os.path.join(dst_dir, "lua-template-binary/.settings/version.json"))
        self.modify_version_json(os.path.join(dst_dir, "js-template-binary/.settings/version.json"))

        self.gen_template_config(dst_dir, self.version)

    def modify_version_json(self, file_path):
        f = open(file_path)
        version_info = json.load(f)
        f.close()

        version_info["engineVersion"] = self.version

        f = open(file_path, "w")
        json.dump(version_info, f, sort_keys=True, indent=4)
        f.close()

    def get_version_from_source(self):
        src_engine_path = self.repo_x
        version_file_path = os.path.join(src_engine_path, "cocos/cocos2d.cpp")
        pattern = r".*return[ \t]+\"(.*)\";"


        # restore the version of engine
        ver = ""
        f = open(version_file_path)
        for line in f.readlines():
            match = re.match(pattern, line)
            if match:
                ver = match.group(1)
                break
        f.close()

        if len(ver) <= 0:
            raise Exception("Can't find version in %s" % version_file_path)

        return ver

    def gen_template_config(self, template_path, engine_ver):
        for name in os.listdir(template_path):
            fullPath = os.path.join(template_path, name)
            if not os.path.isdir(fullPath):
                continue

            if not re.match(".*-template-.*", name):
                continue

            cfg_path = os.path.join(fullPath, ".cocos-project.json")
            cfg_info = {}
            if os.path.exists(cfg_path):
                f = open(cfg_path)
                cfg_info = json.load(f)
                f.close()

            cfg_info["engine_version"] = engine_ver
            cfg_info["engine_type"] = "prebuilt"

            f = open(cfg_path, "w")
            json.dump(cfg_info, f, sort_keys=True, indent=4)
            f.close()

    def modify_android_build_cfg(self, cfg_path, language):
        f = open(cfg_path)
        content = f.read()
        f.close()

        if language == "cpp":
            replace_str = "../cocos2d"
        elif language == "lua":
            replace_str = "../../cocos2d-x"
        else:
            replace_str = "../../cocos2d-x"

        if replace_str is not None:
            content = content.replace(replace_str, self.repo_x)

            f = open(cfg_path, "w")
            f.write(content)
            f.close()


if __name__ == "__main__":
    parser = ArgumentParser(description="Generate binary template.")

    (args, unknown) = parser.parse_known_args()

    if len(unknown) > 0:
        print("unknown arguments: %s" % unknown)

    # Get the engine path
    cur_dir = os.path.realpath(os.path.dirname(__file__))
    args.repo_x = os.path.normpath(os.path.join(cur_dir, os.pardir, os.pardir, os.pardir))

    templateGenerator = CocosBinTemplateGenerator(args)
    templateGenerator.generate()

