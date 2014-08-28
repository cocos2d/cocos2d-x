import os
import shutil
import json
import excopy

from argparse import ArgumentParser

class ModuleOrganizer(object):

    CFG_FILE = "module_config.json"

    KEY_MODULE_IS_COMPILED = "is_compiled"
    KEY_MODULE_FROM_DIR = "from_dir"
    KEY_MODULE_TARGET_DIR = "target_dir"
    KEY_MODULE_INCLUDE = "include"
    KEY_MODULE_ANDROID_LIB_NAME = "android_lib_name"
    KEY_MODULE_ANDROID_LIB_FILE_NAME = "android_lib_file_name"
    KEY_MODULE_EXPORT_INCLUDE = "export_include"
    KEY_MODULE_DEPEND_MODULES = "depend_modules"
    KEY_MODULE_EXPORT_LDLIBS = "export_ldlibs"
    KEY_MODULE_EXPORT_CFLAGS = "export_cflags"
    KEY_MODULE_EXPORT_CPPFLAGS = "export_cppflags"
    KEY_MODULE_WIN32_LIB_FILE_NAME = "win32_lib_file_name"
    KEY_MODULE_IOS_LIB_FILE_NAME = "ios_lib_file_name"
    KEY_MODULE_MAC_LIB_FILE_NAME = "mac_lib_file_name"
    KEY_MODULE_IS_OPTIONAL = "is_optional"
    KEY_MODULE_LUA_BINDINGS = "lua_bindings"
    KEY_MODULE_LUA_LIB_NAME = "lua_lib_name"
    KEY_MODULE_EXCLUDE = "exclude"
    KEY_MODULE_ADDITIONAL_LINK = "additional_link"

    EXPORT_KEYS = [
        KEY_MODULE_IS_COMPILED,
        KEY_MODULE_TARGET_DIR,
        KEY_MODULE_ANDROID_LIB_NAME,
        KEY_MODULE_ANDROID_LIB_FILE_NAME,
        KEY_MODULE_DEPEND_MODULES,
        KEY_MODULE_WIN32_LIB_FILE_NAME,
        KEY_MODULE_IOS_LIB_FILE_NAME,
        KEY_MODULE_MAC_LIB_FILE_NAME,
        KEY_MODULE_IS_OPTIONAL,
        KEY_MODULE_LUA_BINDINGS,
        KEY_MODULE_ADDITIONAL_LINK
    ]

    EXPORT_MODULE_INFO_FILE_NAME = "modules-info.json"

    # Parameter 5--9 means:
    # 5. LOCAL_EXPORT_LDLIBS
    # 6. LOCAL_EXPORT_CFLAGS
    # 7. LOCAL_EXPORT_CPPFLAGS
    # 8. LOCAL_WHOLE_STATIC_LIBRARIES
    # 9. $(call import-module, xxx)
    MK_FORMAT = "LOCAL_PATH := $(call my-dir)\n\n" \
                "include $(CLEAR_VARS)\n\n" \
                "LOCAL_MODULE := %s\n" \
                "LOCAL_MODULE_FILENAME := %s\n\n" \
                "LOCAL_SRC_FILES := %s\n\n" \
                "LOCAL_EXPORT_C_INCLUDES := %s\n\n" \
                "%s" \
                "%s" \
                "%s" \
                "%s" \
                "include $(PREBUILT_STATIC_LIBRARY)\n\n" \
                "%s\n"

    PROPS_FILE_PATH = "cocos/include/2d/cocos2d_headers.props"
    VERSION_SRC_FILE = "cocos/cocos2d.cpp"
    VERSION_DST_FILE = "version"

    def __init__(self, dst_root):
        self.local_path = os.path.realpath(os.path.dirname(__file__))
        self.modules_info = self._parse_modules()

        self.src_root = os.path.join(self.local_path, os.path.pardir, os.path.pardir)
        self.prebuilt_dir = os.path.join(self.local_path, "prebuilt")

        if not os.path.exists(self.prebuilt_dir):
            raise Exception("Prebuilt directory is not existed. PLZ run script 'gen_prebuilt_libs.py' first.")

        if dst_root is None:
            dst = self.local_path
        else:
            if os.path.isabs(dst_root):
                dst = dst_root
            else:
                dst = os.path.abspath(dst_root)
        self.dst_root = os.path.join(dst, "cocos2d-x")

    def _parse_modules(self):
        cfg_path = os.path.join(self.local_path, ModuleOrganizer.CFG_FILE)
        f = open(cfg_path)
        cfg_info = json.load(f)
        f.close()

        return cfg_info

    def gen_android_depend_str(self, depends):
        whole_libs_str = ""
        call_import_str = ""
        i = 0
        for module in depends:
            depend_info = self.modules_info[module]
            if i == 0:
                flag = ":"
            else:
                flag = "+"
            whole_libs_str += ("LOCAL_WHOLE_STATIC_LIBRARIES %s= %s\n" % (flag, depend_info[ModuleOrganizer.KEY_MODULE_ANDROID_LIB_NAME]))
            call_import_str += ("$(call import-module,%s/prebuilt/android)\n" % depend_info[ModuleOrganizer.KEY_MODULE_TARGET_DIR])
            i += 1

        whole_libs_str += "\n"
        return (whole_libs_str, call_import_str)

    def handle_for_android(self, module_info):
        # copy libs file
        android_lib_file_name = module_info[ModuleOrganizer.KEY_MODULE_ANDROID_LIB_FILE_NAME]
        copy_android_lib_cfg = {}
        copy_android_lib_cfg["from"] = "android"
        copy_android_lib_cfg["to"] = "%s/prebuilt/android" % module_info[ModuleOrganizer.KEY_MODULE_TARGET_DIR]
        copy_android_lib_cfg["include"] = [
            "*/%s.a" % android_lib_file_name
        ]
        excopy.copy_files_with_config(copy_android_lib_cfg, self.prebuilt_dir, self.dst_root)

        # generate the prebuilt Android.mk for the module
        android_lib_name = module_info[ModuleOrganizer.KEY_MODULE_ANDROID_LIB_NAME]
        local_src_file = "./$(TARGET_ARCH_ABI)/%s.a" % android_lib_file_name
        export_include_paths = []
        for include_path in module_info[ModuleOrganizer.KEY_MODULE_EXPORT_INCLUDE]:
            temp_path = "${LOCAL_PATH}/%s" % include_path
            export_include_paths.append(temp_path)
        export_include_str = " \\\n".join(export_include_paths)

        export_ldlibs_str = ""
        if module_info.has_key(ModuleOrganizer.KEY_MODULE_EXPORT_LDLIBS):
            export_ldlibs_str = "LOCAL_EXPORT_LDLIBS := "
            for ldlib in module_info[ModuleOrganizer.KEY_MODULE_EXPORT_LDLIBS]:
                export_ldlibs_str += ("-l%s " % ldlib)
            export_ldlibs_str += "\n\n"

        export_cflags_str = ""
        if module_info.has_key(ModuleOrganizer.KEY_MODULE_EXPORT_CFLAGS):
            export_cflags_str = "LOCAL_EXPORT_CFLAGS := "
            export_cflags_str += " ".join(module_info[ModuleOrganizer.KEY_MODULE_EXPORT_CFLAGS])
            export_cflags_str += "\n\n"

        export_cppflags_str = ""
        if module_info.has_key(ModuleOrganizer.KEY_MODULE_EXPORT_CPPFLAGS):
            export_cppflags_str = "LOCAL_EXPORT_CPPFLAGS := "
            export_cppflags_str += " ".join(module_info[ModuleOrganizer.KEY_MODULE_EXPORT_CPPFLAGS])
            export_cppflags_str += "\n\n"

        whole_libs = ""
        call_libs = ""
        if module_info.has_key(ModuleOrganizer.KEY_MODULE_DEPEND_MODULES):
            whole_libs, call_libs = self.gen_android_depend_str(module_info[ModuleOrganizer.KEY_MODULE_DEPEND_MODULES])

        mk_content = ModuleOrganizer.MK_FORMAT % \
                     (android_lib_name,
                      android_lib_file_name,
                      local_src_file,
                      export_include_str,
                      export_ldlibs_str,
                      export_cflags_str,
                      export_cppflags_str,
                      whole_libs,
                      call_libs
                     )

        mk_file_path = os.path.join(self.dst_root, module_info[ModuleOrganizer.KEY_MODULE_TARGET_DIR], "prebuilt/android/Android.mk")
        mk_dir = os.path.dirname(mk_file_path)
        if not os.path.exists(mk_dir):
            os.makedirs(mk_dir)
        mk_obj = open(mk_file_path, "w")
        mk_obj.write(mk_content)
        mk_obj.close()

    def handle_for_win32(self, module_info):
        if module_info.has_key(ModuleOrganizer.KEY_MODULE_WIN32_LIB_FILE_NAME):
            dst_dir = os.path.join(self.dst_root, module_info[ModuleOrganizer.KEY_MODULE_TARGET_DIR], "prebuilt", "win32")
            src_lib_file = os.path.join(self.prebuilt_dir, "win32", "%s.lib" % module_info[ModuleOrganizer.KEY_MODULE_WIN32_LIB_FILE_NAME])
            src_dll_file = os.path.join(self.prebuilt_dir, "win32", "%s.dll" % module_info[ModuleOrganizer.KEY_MODULE_WIN32_LIB_FILE_NAME])
            if not os.path.exists(dst_dir):
                os.makedirs(dst_dir)

            if os.path.exists(src_lib_file):
                shutil.copy(src_lib_file, dst_dir)
            else:
                print("\t%s is not existed" % src_lib_file)

            if os.path.exists(src_dll_file):
                shutil.copy(src_dll_file, dst_dir)

    def handle_for_ios_mac(self, module_info):
        if module_info.has_key(ModuleOrganizer.KEY_MODULE_IOS_LIB_FILE_NAME):
            dst_dir = os.path.join(self.dst_root, module_info[ModuleOrganizer.KEY_MODULE_TARGET_DIR], "prebuilt", "ios")
            src_lib_file = os.path.join(self.prebuilt_dir, "ios", module_info[ModuleOrganizer.KEY_MODULE_IOS_LIB_FILE_NAME])
            if not os.path.exists(dst_dir):
                os.makedirs(dst_dir)

            if os.path.exists(src_lib_file):
                shutil.copy(src_lib_file, dst_dir)
            else:
                print("\t%s is not existed" % src_lib_file)

        if module_info.has_key(ModuleOrganizer.KEY_MODULE_MAC_LIB_FILE_NAME):
            dst_dir = os.path.join(self.dst_root, module_info[ModuleOrganizer.KEY_MODULE_TARGET_DIR], "prebuilt", "mac")
            src_lib_file = os.path.join(self.prebuilt_dir, "mac", module_info[ModuleOrganizer.KEY_MODULE_MAC_LIB_FILE_NAME])
            if not os.path.exists(dst_dir):
                os.makedirs(dst_dir)

            if os.path.exists(src_lib_file):
                shutil.copy(src_lib_file, dst_dir)
            else:
                print("\t%s is not existed" % src_lib_file)

    def handle_for_lua_bindings(self, module_name):
        module_info = self.modules_info[module_name]
        lua_binding_info = module_info[ModuleOrganizer.KEY_MODULE_LUA_BINDINGS]
        lua_lib_name = lua_binding_info[ModuleOrganizer.KEY_MODULE_LUA_LIB_NAME]
        platforms = {
            "android" : "*/%s.a" % lua_lib_name,
            "ios" : "%s iOS.a" % lua_lib_name,
            "mac" : "%s Mac.a" % lua_lib_name,
            "win32" : "%s.lib" % lua_lib_name
        }

        target_dir = os.path.join(self.dst_root, module_info[ModuleOrganizer.KEY_MODULE_TARGET_DIR], "lua-bindings", "prebuilt")
        for p in platforms.keys():
            cpy_info = {
                "from" : p,
                "to" : p,
                "include" : [
                    platforms[p]
                ]
            }
            excopy.copy_files_with_config(cpy_info, self.prebuilt_dir, target_dir)

        # write the Android.mk for lua-bindings lib
        android_lib_name = lua_binding_info[ModuleOrganizer.KEY_MODULE_ANDROID_LIB_NAME]
        mk_file_path = os.path.join(target_dir, "android", "Android.mk")

        depends = [ module_name ]
        if lua_binding_info.has_key(ModuleOrganizer.KEY_MODULE_DEPEND_MODULES):
            depends += lua_binding_info[ModuleOrganizer.KEY_MODULE_DEPEND_MODULES]
        whole_libs, call_libs = self.gen_android_depend_str(depends)
        file_content = ModuleOrganizer.MK_FORMAT % \
                     (android_lib_name,
                      lua_lib_name,
                      "./$(TARGET_ARCH_ABI)/%s.a" % lua_lib_name,
                      "${LOCAL_PATH}/../../include",
                      "", "", "", whole_libs, call_libs )
        f = open(mk_file_path, "w")
        f.write(file_content)
        f.close()

    def gen_compiled_module(self, module_name):
        print("generate compiled module : %s" % module_name)
        module_info = self.modules_info[module_name]
        # copy the include files
        if module_info.has_key(ModuleOrganizer.KEY_MODULE_INCLUDE):
            for include_cfg in module_info[ModuleOrganizer.KEY_MODULE_INCLUDE]:
                excopy.copy_files_with_config(include_cfg, self.src_root, self.dst_root)

        # handle the process for android
        self.handle_for_android(module_info)

        # handle the process for win32
        self.handle_for_win32(module_info)

        # handle the process for ios and mac
        self.handle_for_ios_mac(module_info)

        # handle the lua-bindings
        if module_info.has_key(ModuleOrganizer.KEY_MODULE_LUA_BINDINGS):
            self.handle_for_lua_bindings(module_name)

    def gen_prebuilt_module(self, module_name):
        print("generate prebuilt module : %s" % module_name)
        module_info = self.modules_info[module_name]
        if module_info.has_key(ModuleOrganizer.KEY_MODULE_EXCLUDE):
            exclude = module_info[ModuleOrganizer.KEY_MODULE_EXCLUDE]
        else:
            exclude = []

        if module_info.has_key(ModuleOrganizer.KEY_MODULE_INCLUDE):
            include = module_info[ModuleOrganizer.KEY_MODULE_INCLUDE]
        else:
            include = []

        copy_cfg = {
            "from" : module_info[ModuleOrganizer.KEY_MODULE_FROM_DIR],
            "to": module_info[ModuleOrganizer.KEY_MODULE_TARGET_DIR]
        }

        if len(include) > 0:
            copy_cfg["include"] = include
        elif len(exclude) > 0:
            copy_cfg["exclude"] = exclude

        excopy.copy_files_with_config(copy_cfg, self.src_root, self.dst_root)

    def export_modules_info(self):
        export_file_path = os.path.join(self.dst_root, ModuleOrganizer.EXPORT_MODULE_INFO_FILE_NAME)
        export_info = {}
        for module_name in self.modules_info.keys():
            module_info = self.modules_info[module_name]
            dst_info = {}
            for key in ModuleOrganizer.EXPORT_KEYS:
                if module_info.has_key(key):
                    dst_info[key] = module_info[key]

            export_info[module_name] = dst_info

        outfile = open(export_file_path, "w")
        json.dump(export_info, outfile, sort_keys = True, indent = 4)
        outfile.close()

    def gen_modules(self):
        if os.path.exists(self.dst_root):
            shutil.rmtree(self.dst_root)

        for module in self.modules_info.keys():
            module_info = self.modules_info[module]
            if module_info[ModuleOrganizer.KEY_MODULE_IS_COMPILED]:
                self.gen_compiled_module(module)
            else:
                self.gen_prebuilt_module(module)

        # copy the module config file to dst root
        self.export_modules_info()

        # restore the version of engine
        src_file = os.path.join(self.src_root, ModuleOrganizer.VERSION_SRC_FILE)
        ver = ""
        f = open(src_file)
        import re
        for line in f.readlines():
            match = re.match(r".*return[ \t]*\"(.*)\";", line)
            if match:
                ver = match.group(1)
                break
        f.close()

        if len(ver) <= 0:
            raise Exception("Can't find version in %s" % src_file)
        else:
            dst_file = os.path.join(self.dst_root, ModuleOrganizer.VERSION_DST_FILE)
            f = open(dst_file, "w")
            f.write(ver)
            f.close()

        # modify the cocos2dx.props
        props_file = os.path.join(self.dst_root, ModuleOrganizer.PROPS_FILE_PATH)
        if os.path.exists(props_file):
            f = open(props_file)
            file_content = f.read()
            f.close()

            replace_str = {
                "<EngineRoot>$(MSBuildThisFileDirectory)..\\..\\</EngineRoot>" : "<EngineRoot>$(MSBuildThisFileDirectory)..\\..\\..\\</EngineRoot>",
                "$(EngineRoot)cocos" : "$(EngineRoot)cocos\\include"
            }
            for key in replace_str.keys():
                file_content = file_content.replace(key, replace_str[key])

            f = open(props_file, "w")
            f.write(file_content)
            f.close()

if __name__ == '__main__':
    parser = ArgumentParser(description="Organize the modules of engine from prebuilt engine.")
    parser.add_argument('-d', "--dst-root", dest='dst_root', help='The path where to place the engine organized by modules.')
    (args, unknown) = parser.parse_known_args()

    if len(unknown) > 0:
        print("unknown arguments: %s" % unknown)

    organizer = ModuleOrganizer(args.dst_root)
    organizer.gen_modules()
