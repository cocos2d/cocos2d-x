#!/usr/bin/python
# ----------------------------------------------------------------------------
# modify the runtime template for prebuilt engine
#
# Copyright 2014 (C) zhangbin
#
# License: MIT
# ----------------------------------------------------------------------------
'''
modify the runtime template for prebuilt engine
'''

import os
import sys

LUA_TEMPLATE_PATH = "templates/lua-template-runtime"

#
# WIN32_LINK_CPP_LIBS = [
#     "libbox2d", "libcocos2d", "libSpine"
# ]
#
# WIN32_LINK_LUA_LIBS = [ "libluacocos2d", "libsimulator" ]
#
# WIN32_LINK_JS_LIBS = [ "libjscocos2d" ]

XCODE_LINK_CPP_LIBS = [
    "libcocos2d"
]

XCODE_LINK_LUA_LIBS = [ "libluacocos2d", "libsimulator" ]

XCODE_LINK_JS_LIBS = [ "libjscocos2d", "libsimulator" ]

class TemplateModifier(object):
    def __init__(self, engine_path, libs_path, version, is_for_package):
        if os.path.isabs(engine_path):
            self.engine_path = engine_path
        else:
            self.engine_path = os.path.abspath(engine_path)

        if os.path.isabs(libs_path):
            self.libs_path = libs_path
        else:
            self.libs_path = os.path.abspath(libs_path)

        self.version = version
        self.is_for_package = is_for_package

    def modify_xcode_proj(self, proj_file_path, language):
        proj_modifier_path = os.path.join(os.path.dirname(__file__), 'proj_modifier')
        sys.path.append(proj_modifier_path)

        import modify_pbxproj
        pbx_proj = modify_pbxproj.XcodeProject.Load(proj_file_path)

        replace_engine_strs = []
        if language == "cpp":
            targetName = "HelloCpp"
            link_libs = XCODE_LINK_CPP_LIBS
            replace_engine_strs.append("$(SRCROOT)/../cocos2d")
        elif language == "lua":
            targetName = "HelloLua"
            link_libs = XCODE_LINK_CPP_LIBS + XCODE_LINK_LUA_LIBS
            replace_engine_strs.append("$(SRCROOT)/../../cocos2d-x")
        else:
            targetName = "HelloJavascript"
            link_libs = XCODE_LINK_CPP_LIBS + XCODE_LINK_JS_LIBS
            replace_engine_strs.append("$(SRCROOT)/../../cocos2d-x")
            replace_engine_strs.append("../../cocos2d-x")
        ios_target_name = "%s-mobile" % targetName
        mac_target_name = "%s-desktop" % targetName

        # remove the target dependencies
        pbx_proj.remove_proj_reference("cocos2d_libs.xcodeproj")
        if language == "lua":
            pbx_proj.remove_proj_reference("cocos2d_lua_bindings.xcodeproj")
            pbx_proj.remove_proj_reference("libsimulator.xcodeproj")

        if language == "js":
            pbx_proj.remove_proj_reference("cocos2d_js_bindings.xcodeproj")
            pbx_proj.remove_proj_reference("libsimulator.xcodeproj")
            pbx_proj.remove_file_by_path("../../cocos2d-x/cocos/scripting/js-bindings/script")

            common_group = pbx_proj.get_or_create_group("JS Common")
            pbx_proj.add_file_if_doesnt_exist("../../../script", common_group, tree="<group>")
            # pbx_proj.remove_group_by_name("JS Common")

        # add libraries search path
        libs_path = self.libs_path
        if self.is_for_package:
            libs_path = "/Applications/Cocos/frameworks/%s/prebuilt" % self.version
        ios_template_prebuilt_path = os.path.join(libs_path, "ios")
        pbx_proj.add_library_search_paths(ios_template_prebuilt_path, target_name=ios_target_name, recursive=False)
        mac_template_prebuilt_path = os.path.join(libs_path, "mac")
        pbx_proj.add_library_search_paths(mac_template_prebuilt_path, target_name=mac_target_name, recursive=False)

        # add libraries for targets
        ios_lib_group = pbx_proj.get_or_create_group("ios-libs")
        mac_lib_group = pbx_proj.get_or_create_group("mac-libs")
        for lib in link_libs:
            ios_lib_name = "%s iOS.a" % lib
            mac_lib_name = "%s Mac.a" % lib
            ios_lib_path = os.path.join(ios_template_prebuilt_path, ios_lib_name)
            pbx_proj.add_file_if_doesnt_exist(ios_lib_path, ios_lib_group, tree="<group>", target=ios_target_name)

            mac_lib_path = os.path.join(mac_template_prebuilt_path, mac_lib_name)
            pbx_proj.add_file_if_doesnt_exist(mac_lib_path, mac_lib_group, tree="<group>", target=mac_target_name)

        # add studio resources to the xcode project of cpp template
        if language == "cpp":
            pbx_proj.remove_file_by_path("CloseNormal.png")
            pbx_proj.remove_file_by_path("CloseSelected.png")
            pbx_proj.remove_file_by_path("HelloWorld.png")
            pbx_proj.remove_file_by_path("Marker Felt.ttf")
            pbx_proj.remove_file_by_path("fonts")
            pbx_proj.remove_file_by_path("res")

            res_group = pbx_proj.get_or_create_group("Resources")
            pbx_proj.add_file_if_doesnt_exist("../Resources/res", res_group, tree="<group>")

        if pbx_proj.modified:
            print("Save xcode project")
            pbx_proj.save()

        # modify the engine path
        f = open(proj_file_path)
        file_content = f.read()
        f.close()

        install_path = self.engine_path
        if self.is_for_package:
            install_path = "/Applications/Cocos/frameworks/%s" % self.version
        for old_engine_path in replace_engine_strs:
            file_content = file_content.replace(old_engine_path, install_path)

        f = open(proj_file_path, "w")
        f.write(file_content)
        f.close()

    def modify_vs_proj(self, proj_file_path, language):
        proj_modifier_path = os.path.join(os.path.dirname(__file__), "proj_modifier")
        sys.path.append(proj_modifier_path)

        import modify_vcxproj
        vcx_proj = modify_vcxproj.VCXProject(proj_file_path)

        # remove the project references
        vcx_proj.remove_proj_reference()

        install_path = self.engine_path
        if self.is_for_package:
            install_path = "$(COCOS_FRAMEWORKS)\\%s\\" % self.version

        copy_libs_cmd = "if not exist \"$(OutDir)\" mkdir \"$(OutDir)\"\n" \
                        "xcopy /Y /Q \"$(EngineRoot)\\prebuilt\\win32\\*.*\" \"$(OutDir)\"\n"
        vcx_proj.set_event_command('PreLinkEvent', copy_libs_cmd, 'debug')
        vcx_proj.set_event_command('PreLinkEvent', copy_libs_cmd, 'release')

        if language == "js":
            custom_step_event = vcx_proj.get_event_command('CustomBuildStep')
            custom_step_event.replace("$(ProjectDir)..\\..\\cocos2d-x\\cocos\\scripting\\js-bindings\\script",
                                      "$(ProjectDir)..\\..\\..\\script")
            vcx_proj.set_event_command("CustomBuildStep", custom_step_event, create_new=False)

        vcx_proj.remove_predefine_macro("_DEBUG", 'debug')

        #
        # copy_libs_cmd = "if not exist \"$(OutDir)\" mkdir \"$(OutDir)\"\n" \
        #                 "xcopy /Y /Q \"$(EngineRoot)tools\\framework-compile\\libs\\windows\\*.*\" \"$(OutDir)\"\n"
        # if self.is_for_package:
        #     copy_libs_cmd = "if not exist \"$(OutDir)\" mkdir \"$(OutDir)\"\n" \
        #                 "xcopy /Y /Q \"%s\\prebuilt\\win32\\*.*\" \"$(OutDir)\"\n" % install_path
        # if language == "cpp":
        #     copy_libs_cmd = copy_libs_cmd + "xcopy \"$(ProjectDir)..\\Resources\" \"$(OutDir)\" /D /E /I /F /Y\n"
        #
        # vcx_proj.set_event_command("PreLinkEvent", copy_libs_cmd)
        #
        # if language == "lua":
        #     link_cmd = "libcmt.lib;%(IgnoreSpecificDefaultLibraries)"
        #     vcx_proj.set_item("Link", "IgnoreSpecificDefaultLibraries", link_cmd)
        #
        # debug_prebuild = vcx_proj.get_event_command("PreBuildEvent", "debug")
        # debug_prebuild = debug_prebuild.replace("$(ProjectDir)..\\..\\cocos2d-x\\cocos\\scripting\\js-bindings\\script",
        #                                         "$(ProjectDir)..\\..\\..\\script")
        # vcx_proj.set_event_command("PreBuildEvent", debug_prebuild, "debug")
        #
        # release_prebuild = vcx_proj.get_event_command("PreBuildEvent", "release")
        # release_prebuild = release_prebuild.replace("$(ProjectDir)..\\..\\cocos2d-x\\cocos\\scripting\\js-bindings\\script",
        #                                         "$(ProjectDir)..\\..\\..\\script")
        # vcx_proj.set_event_command("PreBuildEvent", release_prebuild, "release")

        vcx_proj.save()

        replace_strs = []
        if self.is_for_package:
            replace_strs.append("$(EngineRoot)")
        if language == "cpp":
            # link_libs = WIN32_LINK_CPP_LIBS
            replace_strs.append("$(ProjectDir)..\\cocos2d")
            replace_strs.append("..\\cocos2d")
        elif language == "lua":
            # link_libs = WIN32_LINK_CPP_LIBS + WIN32_LINK_LUA_LIBS
            replace_strs.append("$(ProjectDir)..\\..\\cocos2d-x")
            replace_strs.append("..\\..\\cocos2d-x")
        else:
            # link_libs = WIN32_LINK_CPP_LIBS + WIN32_LINK_JS_LIBS
            replace_strs.append("$(ProjectDir)..\\..\\cocos2d-x")
            replace_strs.append("..\\..\\cocos2d-x")

        # modify the Runtime.cpp
        vcx_proj_path = os.path.dirname(proj_file_path)
        cpp_path = os.path.join(vcx_proj_path, os.path.pardir, "Classes/runtime/Runtime.cpp")
        if os.path.exists(cpp_path):
            f = open(cpp_path)
            file_content = f.read()
            f.close()

            file_content = file_content.replace("#ifndef _DEBUG", "#ifndef COCOS2D_DEBUG")
            f = open(cpp_path, "w")
            f.write(file_content)
            f.close()

        f = open(proj_file_path)
        file_content = f.read()
        f.close()

        if language == "lua":
            # replace the "lua\lua;" to "lua\luajit;"
            file_content = file_content.replace("lua\\lua;", "lua\\luajit\\include;")

        file_content = file_content.replace("MultiThreadedDebugDLL", "MultiThreadedDLL")
        for str in replace_strs:
            file_content = file_content.replace(str, install_path)
        file_content = file_content.replace('%s\\' % install_path, install_path)

        f = open(proj_file_path, "w")
        f.write(file_content)
        f.close()





