import os
import sys
import re

def os_is_win32():
    return sys.platform == 'win32'

def os_is_mac():
    return sys.platform == 'darwin'

class AndroidMK(object):
    FIND_LIB_PATTERN = r"^LOCAL_WHOLE_STATIC_LIBRARIES[ \t]*([:+])=[ \t]*(.*)$"
    FIND_IMPORT_PATTERN = r"^\$\(call[ \t]*import-module,[ \t]*(.*)\)"

    FIND_INCLUDE_STATICLIB_PATTERN = r"^include[ \t]*\$\(BUILD_STATIC_LIBRARY\)"
    FIND_INCLUDE_SHAREDLIB_PATTERN = r"^include[ \t]*\$\(BUILD_SHARED_LIBRARY\)"

    def __init__(self, mk_file_path):
        if os.path.isabs(mk_file_path):
            self.file_path = mk_file_path
        else:
            self.file_path = os.path.abspath(mk_file_path)

        if not os.path.exists(self.file_path):
            print("Can't find file %s" % self.file_path)
            return

        f = open(mk_file_path, "r")
        self.file_lines = f.readlines()
        f.close()

    def save(self, new_path=None):
        if self.file_lines is None:
            return

        if new_path is None:
            savePath = self.file_path
        else:
            if os.path.isabs(new_path):
                savePath = new_path
            else:
                savePath = os.path.abspath(new_path)

        print("Saving the Android.mk to %s" % savePath)
        f = open(savePath, "w")
        file_content = "".join(self.file_lines)
        f.write(file_content)
        f.close()
        print("Saving Finished")

    def remove_lib(self, lib_name, lib_dir):
        if self.file_lines is None:
            return

        lib_pattern = re.compile(AndroidMK.FIND_LIB_PATTERN)
        import_pattern = re.compile(AndroidMK.FIND_IMPORT_PATTERN)
        i = 0
        for line in self.file_lines:
            # find the lib
            line_modified = False
            str1 = line.lstrip()
            str2 = str1.rstrip()

            match = lib_pattern.match(str2)
            if match:
                cur_modules = match.group(2).split()
                for module in cur_modules:
                    if module == lib_name:
                        print("Remove %s from line %d" % (lib_name, i+1))
                        cur_modules.remove(module)
                        line_modified = True

                if line_modified:
                    if len(cur_modules) > 0:
                        self.file_lines[i] = "LOCAL_WHOLE_STATIC_LIBRARIES %s= %s\n" % (match.group(1), " ".join(cur_modules))
                    else:
                        self.file_lines.remove(line)

            # find the import line
            match_import = import_pattern.match(str2)
            if match_import:
                import_str = match_import.group(1)
                import_str = import_str.lstrip()
                import_str = import_str.rstrip()
                if import_str == lib_dir:
                    print("Remove call import-module from line %d" % (i+1))
                    self.file_lines.remove(line)

            i += 1


    def add_lib(self, lib_name, lib_dir):
        if self.file_lines is None:
            return

        need_add_lib = True
        need_add_import = True

        lib_pattern = re.compile(AndroidMK.FIND_LIB_PATTERN)
        import_pattern = re.compile(AndroidMK.FIND_IMPORT_PATTERN)
        static_pattern = re.compile(AndroidMK.FIND_INCLUDE_STATICLIB_PATTERN)
        shared_pattern = re.compile(AndroidMK.FIND_INCLUDE_SHAREDLIB_PATTERN)

        for line in self.file_lines:
            str1 = line.lstrip()
            str2 = str1.rstrip()

            # find lib
            if need_add_lib:
                lib_match = lib_pattern.match(str2)
                if lib_match:
                    cur_modules = lib_match.group(2).split()
                    for module in cur_modules:
                        if module == lib_name:
                            need_add_lib = False
                            break

            # find import
            if need_add_import:
                match_import = import_pattern.match(str2)
                if match_import:
                    import_str = match_import.group(1)
                    import_str = import_str.lstrip()
                    import_str = import_str.rstrip()
                    if import_str == lib_dir:
                        need_add_import = False

            if not need_add_lib and not need_add_import:
                break

        if not need_add_lib and not need_add_import:
            # already contain the lib
            return

        # find the insert place
        colon_idx = -1
        plus_idx = -1
        include_idx = -1
        last_import_idx = -1
        i = 0
        for line in self.file_lines:
            str1 = line.lstrip()
            str2 = str1.rstrip()

            lib_match = lib_pattern.match(str2)
            if lib_match:
                if lib_match.group(1) == ':':
                    colon_idx = i
                else:
                    plus_idx = i

            static_match = static_pattern.match(str2)
            shared_match = shared_pattern.match(str2)
            if static_match or shared_match:
                include_idx = i

            import_match = import_pattern.match(str2)
            if import_match:
                last_import_idx = i

            i+=1

        if include_idx < 0:
            print("The Android.mk is not complete. Can't find \"include $(BUILD_SHARED_LIBRARY)\" or \"include $(BUILD_STATIC_LIBRARY)\"")
            return

        if need_add_lib:
            lib_str = "LOCAL_WHOLE_STATIC_LIBRARIES += %s\n" % lib_name
            if colon_idx >= 0:
                lib_idx = (colon_idx + 1)
            elif plus_idx >= 0:
                lib_idx = (plus_idx + 1)
            else:
                lib_idx = max(0, (include_idx - 1))

            if lib_idx >= len(self.file_lines):
                self.file_lines.append(lib_str)
            else:
                self.file_lines.insert(lib_idx, lib_str)
            print("\"%s\" added" % lib_str.rstrip())

        if need_add_import:
            import_str = "$(call import-module,%s)\n" % lib_dir
            if last_import_idx >= 0:
                if need_add_lib and lib_idx < last_import_idx:
                    import_idx = last_import_idx + 2
                else:
                    import_idx = last_import_idx + 1
            else:
                import_idx = len(self.file_lines)

            if import_idx >= len(self.file_lines):
                self.file_lines.append(import_str)
            else:
                self.file_lines.insert(import_idx, import_str)
            print("\"%s\" added" % import_str.rstrip())
