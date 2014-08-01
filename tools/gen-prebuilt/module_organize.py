import os
import shutil
import json
import excopy

from argparse import ArgumentParser

class ModuleOrganizer(object):

    CFG_FILE = "module_config.json"

    KEY_MODULE_TYPE = "module_type"
    MODULE_TYPE_COMPILED = "compiled"
    MODULE_TYPE_PREBUILT = "prebuilt"

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

    def __init__(self, dst_root):
        self.local_path = os.path.realpath(os.path.dirname(__file__))
        self.modules_info = self._parse_modules()

        self.src_root = os.path.join(self.local_path, os.path.pardir, os.path.pardir)
        self.prebuilt_dir = os.path.join(self.local_path, "prebuilt")

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

    def gen_compiled_module(self, module_name):
        print("generate compiled module : %s" % module_name)
        module_info = self.modules_info[module_name]
        # copy the include files
        if module_info.has_key(ModuleOrganizer.KEY_MODULE_INCLUDE):
            for inclue_cfg in module_info[ModuleOrganizer.KEY_MODULE_INCLUDE]:
                excopy.copy_files_with_config(inclue_cfg, self.src_root, self.dst_root)

        # handle the process for android
        self.handle_for_android(module_info)

        # handle the process for win32
        self.handle_for_win32(module_info)

        # handle the process for ios and mac
        self.handle_for_ios_mac(module_info)

    def gen_prebuilt_module(self, module_name):
        print("generate prebuilt module : %s" % module_name)
        module_info = self.modules_info[module_name]
        copy_cfg = {
            "from" : module_info[ModuleOrganizer.KEY_MODULE_FROM_DIR],
            "to": module_info[ModuleOrganizer.KEY_MODULE_TARGET_DIR]
        }
        excopy.copy_files_with_config(copy_cfg, self.src_root, self.dst_root)

    def gen_modules(self):
        if os.path.exists(self.dst_root):
            shutil.rmtree(self.dst_root)

        for module in self.modules_info.keys():
            module_info = self.modules_info[module]
            if module_info[ModuleOrganizer.KEY_MODULE_TYPE] == ModuleOrganizer.MODULE_TYPE_COMPILED:
                self.gen_compiled_module(module)
            elif module_info[ModuleOrganizer.KEY_MODULE_TYPE] == ModuleOrganizer.MODULE_TYPE_PREBUILT:
                self.gen_prebuilt_module(module)

if __name__ == '__main__':
    parser = ArgumentParser(description="Organize the modules of engine from prebuilt engine.")
    parser.add_argument('-d', "--dst-root", dest='dst_root', help='The path where to place the engine organized by modules.')
    (args, unknown) = parser.parse_known_args()

    if len(unknown) > 0:
        print("unknown arguments: %s" % unknown)

    organizer = ModuleOrganizer(args.dst_root)
    organizer.gen_modules()
