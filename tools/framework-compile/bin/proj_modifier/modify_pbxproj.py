#  Copyright 2012 Calvin Rien
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

#  A pbxproj file is an OpenStep format plist
#  {} represents dictionary of key=value pairs delimited by ;
#  () represents list of values delimited by ,
#  file starts with a comment specifying the character type
#  // !$*UTF8*$!

#  when adding a file to a project, create the PBXFileReference
#  add the PBXFileReference's guid to a group
#  create a PBXBuildFile with the PBXFileReference's guid
#  add the PBXBuildFile to the appropriate build phase

#  when adding a header search path add
#  HEADER_SEARCH_PATHS = "path/**";
#  to each XCBuildConfiguration object

#  Xcode4 will read either a OpenStep or XML plist.
#  this script uses `plutil` to validate, read and write
#  the pbxproj file.  Plutil is available in OS X 10.2 and higher
#  Plutil can't write OpenStep plists, so I save as XML

import datetime
import json
import ntpath
import os
import plistlib
import re
import shutil
import subprocess
import uuid
import sys

from UserDict import IterableUserDict
from UserList import UserList

regex = '[a-zA-Z0-9\\._/-]*'

def os_is_win32():
    return sys.platform == 'win32'

def os_is_mac():
    return sys.platform == 'darwin'

class PBXEncoder(json.JSONEncoder):
    def default(self, obj):
        """Tests the input object, obj, to encode as JSON."""

        if isinstance(obj, (PBXList, PBXDict)):
            return obj.data

        return json.JSONEncoder.default(self, obj)


class PBXDict(IterableUserDict):
    def __init__(self, d=None):
        if d:
            d = dict([(PBXType.Convert(k), PBXType.Convert(v)) for k, v in d.items()])

        IterableUserDict.__init__(self, d)

    def __setitem__(self, key, value):
        IterableUserDict.__setitem__(self, PBXType.Convert(key), PBXType.Convert(value))

    def remove(self, key):
        self.data.pop(PBXType.Convert(key), None)


class PBXList(UserList):
    def __init__(self, l=None):
        if isinstance(l, basestring):
            UserList.__init__(self)
            self.add(l)
            return
        elif l:
            l = [PBXType.Convert(v) for v in l]

        UserList.__init__(self, l)

    def add(self, value):
        value = PBXType.Convert(value)

        if value in self.data:
            return False

        self.data.append(value)
        return True

    def remove(self, value):
        value = PBXType.Convert(value)

        if value in self.data:
            self.data.remove(value)
            return True
        return False

    def __setitem__(self, key, value):
        UserList.__setitem__(self, PBXType.Convert(key), PBXType.Convert(value))


class PBXType(PBXDict):
    def __init__(self, d=None):
        PBXDict.__init__(self, d)

        if 'isa' not in self:
            self['isa'] = self.__class__.__name__
        self.id = None

    @staticmethod
    def Convert(o):
        if isinstance(o, list):
            return PBXList(o)
        elif isinstance(o, dict):
            isa = o.get('isa')

            if not isa:
                return PBXDict(o)

            cls = globals().get(isa)

            if cls and issubclass(cls, PBXType):
                return cls(o)

            print('warning: unknown PBX type: %s' % isa)
            return PBXDict(o)
        else:
            return o

    @staticmethod
    def IsGuid(o):
        return re.match('^[A-F0-9]{24}$', str(o))

    @classmethod
    def GenerateId(cls):
        return ''.join(str(uuid.uuid4()).upper().split('-')[1:])

    @classmethod
    def Create(cls, *args, **kwargs):
        return cls(*args, **kwargs)

FILE_TYPE_INFO = {
    'archive.ar' : 'PBXFrameworksBuildPhase',
    'wrapper.application': None,
    'sourcecode.asm': 'PBXSourcesBuildPhase',
    'sourcecode.c.c': 'PBXSourcesBuildPhase',
    'sourcecode.cpp.cpp': 'PBXSourcesBuildPhase',
    'wrapper.framework': 'PBXFrameworksBuildPhase',
    'sourcecode.c.h': None,
    'image.icns': 'PBXResourcesBuildPhase',
    'sourcecode.c.objc': 'PBXSourcesBuildPhase',
    'sourcecode.cpp.objcpp': 'PBXSourcesBuildPhase',
    'wrapper.nib': 'PBXResourcesBuildPhase',
    'text.plist.xml': 'PBXResourcesBuildPhase',
    'text.json': 'PBXResourcesBuildPhase',
    'image.png': 'PBXResourcesBuildPhase',
    'text.rtf': 'PBXResourcesBuildPhase',
    'image.tiff': 'PBXResourcesBuildPhase',
    'text': 'PBXResourcesBuildPhase',
    'wrapper.pb-project': None,
    'file.xib': 'PBXResourcesBuildPhase',
    'text.plist.strings': 'PBXResourcesBuildPhase',
    'wrapper.plug-in': 'PBXResourcesBuildPhase',
    'compiled.mach-o.dylib': 'PBXFrameworksBuildPhase'
}


class PBXFileReference(PBXType):
    def __init__(self, d=None):
        PBXType.__init__(self, d)
        self.build_phase = None

    types = {
        '.a': 'archive.ar',
        '.app': 'wrapper.application',
        '.s': 'sourcecode.asm',
        '.c': 'sourcecode.c.c',
        '.cpp': 'sourcecode.cpp.cpp',
        '.framework': 'wrapper.framework',
        '.h': 'sourcecode.c.h',
        '.hpp': 'sourcecode.c.h',
        '.icns': 'image.icns',
        '.m': 'sourcecode.c.objc',
        '.j': 'sourcecode.c.objc',
        '.mm': 'sourcecode.cpp.objcpp',
        '.nib': 'wrapper.nib',
        '.plist': 'text.plist.xml',
        '.json': 'text.json',
        '.png': 'image.png',
        '.rtf': 'text.rtf',
        '.tiff': 'image.tiff',
        '.txt': 'text',
        '.xcodeproj': 'wrapper.pb-project',
        '.xib': 'file.xib',
        '.strings': 'text.plist.strings',
        '.bundle': 'wrapper.plug-in',
        '.dylib': 'compiled.mach-o.dylib',
        '.lua': 'text',
        '.js': 'text'
    }

    trees = [
        '<absolute>',
        '<group>',
        'BUILT_PRODUCTS_DIR',
        'DEVELOPER_DIR',
        'SDKROOT',
        'SOURCE_ROOT',
        ]

    def guess_file_type(self, ignore_unknown_type=False):
        self.remove('explicitFileType')
        self.remove('lastKnownFileType')

        ext = os.path.splitext(self.get('name', ''))[1]
        if os.path.isdir(self.get('path')) and ext != '.framework' and ext != '.bundle':
            f_type = 'folder'
            build_phase = None
            ext = ''
        else:
            f_type = PBXFileReference.types.get(ext, '?')
            build_phase = FILE_TYPE_INFO.get(f_type, 'PBXResourcesBuildPhase')

        self['lastKnownFileType'] = f_type
        self.build_phase = build_phase

        if f_type == '?' and not ignore_unknown_type:
            print('unknown file extension: %s' % ext)
            print('please add extension and Xcode type to PBXFileReference.types')

        return f_type

    def set_file_type(self, ft):
        self.remove('explicitFileType')
        self.remove('lastKnownFileType')

        self['explicitFileType'] = ft

    @classmethod
    def Create(cls, os_path, tree='SOURCE_ROOT', ignore_unknown_type=False):
        if tree not in cls.trees:
            print('Not a valid sourceTree type: %s' % tree)
            return None

        fr = cls()
        fr.id = cls.GenerateId()
        fr['path'] = os_path
        fr['name'] = os.path.split(os_path)[1]
        fr['sourceTree'] = '<absolute>' if os.path.isabs(os_path) else tree
        fr.guess_file_type(ignore_unknown_type=ignore_unknown_type)

        return fr


class PBXBuildFile(PBXType):
    def set_weak_link(self, weak=False):
        k_settings = 'settings'
        k_attributes = 'ATTRIBUTES'

        s = self.get(k_settings)

        if not s:
            if weak:
                self[k_settings] = PBXDict({k_attributes: PBXList(['Weak'])})

            return True

        atr = s.get(k_attributes)

        if not atr:
            if weak:
                atr = PBXList()
            else:
                return False

        if weak:
            atr.add('Weak')
        else:
            atr.remove('Weak')

        self[k_settings][k_attributes] = atr

        return True

    def add_compiler_flag(self, flag):
        k_settings = 'settings'
        k_attributes = 'COMPILER_FLAGS'

        if k_settings not in self:
            self[k_settings] = PBXDict()

        if k_attributes not in self[k_settings]:
            self[k_settings][k_attributes] = flag
            return True

        flags = self[k_settings][k_attributes].split(' ')

        if flag in flags:
            return False

        flags.append(flag)

        self[k_settings][k_attributes] = ' '.join(flags)

    @classmethod
    def Create(cls, file_ref, weak=False):
        if isinstance(file_ref, PBXFileReference):
            file_ref = file_ref.id

        bf = cls()
        bf.id = cls.GenerateId()
        bf['fileRef'] = file_ref

        if weak:
            bf.set_weak_link(True)

        return bf


class PBXGroup(PBXType):
    def add_child(self, ref):
        if not isinstance(ref, PBXDict):
            return None

        isa = ref.get('isa')

        if isa != 'PBXFileReference' and isa != 'PBXGroup':
            return None

        if 'children' not in self:
            self['children'] = PBXList()

        self['children'].add(ref.id)

        return ref.id

    def remove_child(self, id):
        if 'children' not in self:
            self['children'] = PBXList()
            return

        if not PBXType.IsGuid(id):
            id = id.id

        self['children'].remove(id)

    def has_child(self, id):
        if 'children' not in self:
            self['children'] = PBXList()
            return False

        if not PBXType.IsGuid(id):
            id = id.id

        return id in self['children']

    def get_name(self):
        path_name = os.path.split(self.get('path', ''))[1]
        return self.get('name', path_name)

    @classmethod
    def Create(cls, name, path=None, tree='SOURCE_ROOT'):
        grp = cls()
        grp.id = cls.GenerateId()
        grp['name'] = name
        grp['children'] = PBXList()

        if path:
            grp['path'] = path
            grp['sourceTree'] = tree
        else:
            grp['sourceTree'] = '<group>'

        return grp


class PBXNativeTarget(PBXType):
    pass


class PBXProject(PBXType):
    pass


class PBXContainerItemProxy(PBXType):
    pass


class PBXReferenceProxy(PBXType):
    pass


class PBXVariantGroup(PBXType):
    pass


class PBXTargetDependency(PBXType):
    pass


class PBXAggregateTarget(PBXType):
    pass
    
    
class PBXHeadersBuildPhase(PBXType):
    pass
    
    
class PBXBuildPhase(PBXType):
    def add_build_file(self, bf):
        if bf.get('isa') != 'PBXBuildFile':
            return False

        if 'files' not in self:
            self['files'] = PBXList()

        self['files'].add(bf.id)

        return True

    def remove_build_file(self, id):
        if 'files' not in self:
            self['files'] = PBXList()
            return

        self['files'].remove(id)

    def has_build_file(self, id):
        if 'files' not in self:
            self['files'] = PBXList()
            return False

        if not PBXType.IsGuid(id):
            id = id.id

        return id in self['files']


class PBXFrameworksBuildPhase(PBXBuildPhase):
    pass


class PBXResourcesBuildPhase(PBXBuildPhase):
    pass


class PBXShellScriptBuildPhase(PBXBuildPhase):
    @classmethod
    def Create(cls, script, shell="/bin/sh", files=[], input_paths=[], output_paths=[], show_in_log = '0'):
        bf = cls()
        bf.id = cls.GenerateId()
        bf['files'] = files
        bf['inputPaths'] = input_paths
        bf['outputPaths'] = output_paths
        bf['runOnlyForDeploymentPostprocessing'] = '0';
        bf['shellPath'] = shell
        bf['shellScript'] = script
        bf['showEnvVarsInLog'] = show_in_log

        return bf


class PBXSourcesBuildPhase(PBXBuildPhase):
    pass


class PBXCopyFilesBuildPhase(PBXBuildPhase):
    pass


class XCBuildConfiguration(PBXType):
    def add_search_paths(self, paths, base, key, recursive=True, escape=True):
        modified = False

        if not isinstance(paths, list):
            paths = [paths]

        if base not in self:
            self[base] = PBXDict()

        if key not in self[base]:
            self[base][key] = PBXList()
            self[base][key].add("$(inherited)")
        elif isinstance(self[base][key], basestring):
            self[base][key] = PBXList(self[base][key])

        for path in paths:
            if recursive and not path.endswith('/**'):
                path = os.path.join(path, '**')

            if os.path.isabs(path):
                add_path = path
            else:
                add_path = "$(SRCROOT)/%s" % path

            if self[base][key].add(add_path):
                modified = True

        return modified

    def add_user_header_search_paths(self, paths, recursive=True, add_inherite=True):
        modified = False

        if not isinstance(paths, list):
            paths = [paths]

        base = "buildSettings"
        key = "USER_HEADER_SEARCH_PATHS"
        if base not in self:
            self[base] = PBXDict()

        if add_inherite and key not in self[base]:
            self[base][key] = "$(inherited)"

        path_list = self[base][key].split(" ")

        for path in paths:
            if recursive and not path.endswith('/**'):
                path = os.path.join(path, '**')

            if os.path.isabs(path):
                add_path = path
            else:
                add_path = "$(SRCROOT)/%s" % path

            if add_path not in path_list:
                path_list.append(add_path)
                modified = True

        if modified:
            self[base][key] = " ".join(path_list)

        return modified

    def remove_user_header_search_paths(self, paths):
        modified = False

        base = "buildSettings"
        key = "USER_HEADER_SEARCH_PATHS"
        if base not in self or key not in self[base]:
            return modified

        if paths == "ALL":
            self[base][key] = ""
            modified = True
            return modified

        if not isinstance(paths, list):
            paths = [paths]

        path_list = self[base][key].split(" ")
        for path in paths:
            if os.path.isabs(path):
                add_path = path
            else:
                add_path = "$(SRCROOT)/%s" % path

            if add_path in path_list:
                path_list.remove(add_path)
                modified = True

        if modified:
            self[base][key] = " ".join(path_list)

        return modified

    def remove_library_search_paths(self, paths):
        modified = False

        if not isinstance(paths, list):
            paths = [paths]

        base = "buildSettings"
        key = "LIBRARY_SEARCH_PATHS"
        if base not in self or key not in self[base]:
            return modified

        path_list = self[base][key]
        for path in paths:
            if os.path.isabs(path):
                add_path = path
            else:
                add_path = "$(SRCROOT)/%s" % path

            if add_path in path_list:
                path_list.remove(add_path)
                modified = True

        return modified

    def add_header_search_paths(self, paths, recursive=True):
        return self.add_search_paths(paths, 'buildSettings', 'HEADER_SEARCH_PATHS', recursive=recursive)

    def add_library_search_paths(self, paths, recursive=True):
        return self.add_search_paths(paths, 'buildSettings', 'LIBRARY_SEARCH_PATHS', recursive=recursive)

    def add_framework_search_paths(self, paths, recursive=True):
        return self.add_search_paths(paths, 'buildSettings', 'FRAMEWORK_SEARCH_PATHS', recursive=recursive)

    def add_other_cflags(self, flags):
        modified = False

        base = 'buildSettings'
        key = 'OTHER_CFLAGS'

        if isinstance(flags, basestring):
            flags = PBXList(flags)

        if base not in self:
            self[base] = PBXDict()

        for flag in flags:
            if key not in self[base]:
                self[base][key] = PBXList()
            elif isinstance(self[base][key], basestring):
                self[base][key] = PBXList(self[base][key])

            if self[base][key].add(flag):
                self[base][key] = [e for e in self[base][key] if e]
                modified = True

        return modified

    def add_other_ldflags(self, flags):
        modified = False

        base = 'buildSettings'
        key = 'OTHER_LDFLAGS'

        if isinstance(flags, basestring):
            flags = PBXList(flags)

        if base not in self:
            self[base] = PBXDict()

        for flag in flags:
            if key not in self[base]:
                self[base][key] = PBXList()
            elif isinstance(self[base][key], basestring):
                self[base][key] = PBXList(self[base][key])

            if self[base][key].add(flag):
                self[base][key] = [e for e in self[base][key] if e]
                modified = True

        return modified

    def remove_other_ldflags(self, flags):
        modified = False

        base = 'buildSettings'
        key = 'OTHER_LDFLAGS'

        if isinstance(flags, basestring):
            flags = PBXList(flags)

        if base in self:  # there are flags, so we can "remove" something
            for flag in flags:
                if key not in self[base]:
                    return False
                elif isinstance(self[base][key], basestring):
                    self[base][key] = PBXList(self[base][key])

                if self[base][key].remove(flag):
                    self[base][key] = [e for e in self[base][key] if e]
                    modified = True

        return modified


class XCConfigurationList(PBXType):
    pass


class XcodeProject(PBXDict):
    plutil_path = 'plutil'
    special_folders = ['.bundle', '.framework', '.xcodeproj']

    def __init__(self, d=None, path=None):
        if not path:
            path = os.path.join(os.getcwd(), 'project.pbxproj')

        self.pbxproj_path = os.path.abspath(path)
        self.source_root = os.path.abspath(os.path.join(os.path.split(path)[0], '..'))

        IterableUserDict.__init__(self, d)

        self.data = PBXDict(self.data)
        self.objects = self.get('objects')
        self.modified = False

        root_id = self.get('rootObject')

        if root_id:
            self.root_object = self.objects[root_id]
            root_group_id = self.root_object.get('mainGroup')
            self.root_group = self.objects[root_group_id]
        else:
            print("error: project has no root object")
            self.root_object = None
            self.root_group = None

        for k, v in self.objects.iteritems():
            v.id = k

    def add_other_cflags(self, flags):
        build_configs = [b for b in self.objects.values() if b.get('isa') == 'XCBuildConfiguration']

        for b in build_configs:
            if b.add_other_cflags(flags):
                self.modified = True

    def add_other_ldflags(self, flags):
        build_configs = [b for b in self.objects.values() if b.get('isa') == 'XCBuildConfiguration']

        for b in build_configs:
            if b.add_other_ldflags(flags):
                self.modified = True

    def remove_other_ldflags(self, flags):
        build_configs = [b for b in self.objects.values() if b.get('isa') == 'XCBuildConfiguration']

        for b in build_configs:
            if b.remove_other_ldflags(flags):
                self.modified = True

    def add_user_header_search_paths(self, paths, target_name=None, recursive=True):
        if target_name is None:
            build_configs = [b for b in self.objects.values() if b.get('isa') == 'XCBuildConfiguration']

            for b in build_configs:
                if b.add_user_header_search_paths(paths, recursive):
                    self.modified = True
        else:
            target_obj = self.get_native_target(target_name)
            if target_obj is None:
                print("Can't find target %s" % target_name)
            else:
                if target_obj.get("isa") == "PBXProject":
                    add_inherite = False
                else:
                    add_inherite = True

                build_cfg_list_id = target_obj.get("buildConfigurationList")
                build_cfg_list = self.objects.get(build_cfg_list_id)
                build_cfgs = build_cfg_list.get("buildConfigurations")
                for cfg_id in build_cfgs:
                    cfg = self.objects.get(cfg_id)
                    if cfg.add_user_header_search_paths(paths, recursive, add_inherite):
                        self.modified = True

    def remove_user_header_search_paths(self, paths, target_name=None):
        if target_name is None:
            build_configs = [b for b in self.objects.values() if b.get('isa') == 'XCBuildConfiguration']

            for b in build_configs:
                if b.remove_user_header_search_paths(paths):
                    self.modified = True
        else:
            target_obj = self.get_native_target(target_name)
            if target_obj is None:
                print("Can't find target %s" % target_name)
            else:
                build_cfg_list_id = target_obj.get("buildConfigurationList")
                build_cfg_list = self.objects.get(build_cfg_list_id)
                build_cfgs = build_cfg_list.get("buildConfigurations")
                for cfg_id in build_cfgs:
                    cfg = self.objects.get(cfg_id)
                    if cfg.remove_user_header_search_paths(paths):
                        self.modified = True

    def remove_library_search_paths(self, paths, target_name=None):
        if target_name is None:
            build_configs = [b for b in self.objects.values() if b.get('isa') == 'XCBuildConfiguration']

            for b in build_configs:
                if b.remove_library_search_paths(paths):
                    self.modified = True
        else:
            target_obj = self.get_native_target(target_name)
            if target_obj is None:
                print("Can't find target %s" % target_name)
            else:
                build_cfg_list_id = target_obj.get("buildConfigurationList")
                build_cfg_list = self.objects.get(build_cfg_list_id)
                build_cfgs = build_cfg_list.get("buildConfigurations")
                for cfg_id in build_cfgs:
                    cfg = self.objects.get(cfg_id)
                    if cfg.remove_library_search_paths(paths):
                        self.modified = True

    def add_header_search_paths(self, paths, target_name=None, recursive=True):
        if target_name is None:
            build_configs = [b for b in self.objects.values() if b.get('isa') == 'XCBuildConfiguration']

            for b in build_configs:
                if b.add_header_search_paths(paths, recursive):
                    self.modified = True
        else:
            target_obj = self.get_native_target(target_name)
            if target_obj is None:
                print("Can't find target %s" % target_name)
            else:
                build_cfg_list_id = target_obj.get("buildConfigurationList")
                build_cfg_list = self.objects.get(build_cfg_list_id)
                build_cfgs = build_cfg_list.get("buildConfigurations")
                for cfg_id in build_cfgs:
                    cfg = self.objects.get(cfg_id)
                    if cfg.add_header_search_paths(paths, recursive):
                        self.modified = True

    def add_framework_search_paths(self, paths, recursive=True):
        build_configs = [b for b in self.objects.values() if b.get('isa') == 'XCBuildConfiguration']

        for b in build_configs:
            if b.add_framework_search_paths(paths, recursive):
                self.modified = True

    def add_library_search_paths(self, paths, target_name=None, recursive=True):

        if target_name is None:
            build_configs = [b for b in self.objects.values() if b.get('isa') == 'XCBuildConfiguration']

            for b in build_configs:
                if b.add_library_search_paths(paths, recursive):
                    self.modified = True
        else:
            target_obj = self.get_native_target(target_name)
            if target_obj is None:
                print("Can't find target %s" % target_name)
            else:
                build_cfg_list_id = target_obj.get("buildConfigurationList")
                build_cfg_list = self.objects.get(build_cfg_list_id)
                build_cfgs = build_cfg_list.get("buildConfigurations")
                for cfg_id in build_cfgs:
                    cfg = self.objects.get(cfg_id)
                    if cfg.add_library_search_paths(paths, recursive):
                        self.modified = True

    def get_obj(self, id):
        return self.objects.get(id)

    def get_ids(self):
        return self.objects.keys()

    def get_files_by_os_path(self, os_path, tree='SOURCE_ROOT'):
        files = [f for f in self.objects.values() if f.get('isa') == 'PBXFileReference'
                                                     and f.get('path') == os_path
                                                     and f.get('sourceTree') == tree]

        return files

    def get_files_by_name(self, name, parent=None):
        if parent:
            files = [f for f in self.objects.values() if f.get('isa') == 'PBXFileReference'
                                                         and f.get('name') == name
                                                         and parent.has_child(f)]
        else:
            files = [f for f in self.objects.values() if f.get('isa') == 'PBXFileReference'
                                                         and f.get('name') == name]

        return files

    def get_build_files(self, id):
        files = [f for f in self.objects.values() if f.get('isa') == 'PBXBuildFile'
                                                     and f.get('fileRef') == id]

        return files

    def get_groups_by_name(self, name, parent=None):
        if parent:
            groups = [g for g in self.objects.values() if g.get('isa') == 'PBXGroup'
                                                          and g.get_name() == name
                                                          and parent.has_child(g)]
        else:
            groups = [g for g in self.objects.values() if g.get('isa') == 'PBXGroup'
                                                          and g.get_name() == name]

        return groups

    def get_group_id(self, group_name):
        objs = self.data.get('objects')
        ret_id = None
        for key in objs:
            obj = objs.get(key)
            if obj.get("isa") == "PBXGroup" and obj.get("name") == group_name:
                ret_id = key
                break

        return ret_id

    def get_or_create_group(self, name, path=None, parent=None):
        if not name:
            return None

        if not parent:
            parent = self.root_group
        elif not isinstance(parent, PBXGroup):
            # assume it's an id
            parent = self.objects.get(parent, self.root_group)

        groups = self.get_groups_by_name(name)

        for grp in groups:
            if parent.has_child(grp.id):
                return grp

        grp = PBXGroup.Create(name, path)
        parent.add_child(grp)

        self.objects[grp.id] = grp

        self.modified = True

        return grp

    def get_groups_by_os_path(self, path):
        path = os.path.abspath(path)

        groups = [g for g in self.objects.values() if g.get('isa') == 'PBXGroup'
                                                      and os.path.abspath(g.get('path', '/dev/null')) == path]

        return groups

    def get_build_phases(self, phase_name):
        phases = [p for p in self.objects.values() if p.get('isa') == phase_name]

        return phases

    def get_native_target(self, target_name):
        target = None
        for obj in self.objects.values():
            if target_name == "PROJECT":
                if obj.get('isa') == "PBXProject":
                    target = obj
                    break
            else:
                if obj.get('isa') == "PBXNativeTarget" and obj.get("name") == target_name:
                    target = obj
                    break

        return target

    def get_relative_path(self, os_path):
        return os.path.relpath(os_path, self.source_root)

    def verify_files(self, file_list, parent=None):
        # returns list of files not in the current project.
        if not file_list:
            return []

        if parent:
            exists_list = [f.get('name') for f in self.objects.values() if f.get('isa') == 'PBXFileReference' and f.get('name') in file_list and parent.has_child(f)]
        else:
            exists_list = [f.get('name') for f in self.objects.values() if f.get('isa') == 'PBXFileReference' and f.get('name') in file_list]

        return set(file_list).difference(exists_list)

    def add_run_script(self, target, script=None):
        result = []
        targets = [t for t in self.get_build_phases('PBXNativeTarget') + self.get_build_phases('PBXAggregateTarget') if t.get('name') == target]
        if len(targets) != 0 :
            script_phase = PBXShellScriptBuildPhase.Create(script)
            for t in targets:
                skip = False
                for buildPhase in t['buildPhases']:
                    if self.objects[buildPhase].get('isa') == 'PBXShellScriptBuildPhase' and self.objects[buildPhase].get('shellScript') == script:
                        skip = True
                        
                if not skip:
                    t['buildPhases'].add(script_phase.id)
                    self.objects[script_phase.id] = script_phase
                    result.append(script_phase)
            
        return result
    
    def add_run_script_all_targets(self, script=None):
        result = []
        targets = self.get_build_phases('PBXNativeTarget') + self.get_build_phases('PBXAggregateTarget')
        if len(targets) != 0 :
            script_phase = PBXShellScriptBuildPhase.Create(script)
            for t in targets:
                skip = False
                for buildPhase in t['buildPhases']:
                    if self.objects[buildPhase].get('isa') == 'PBXShellScriptBuildPhase' and self.objects[buildPhase].get('shellScript') == script:
                        skip = True
                        
                if not skip:
                    t['buildPhases'].add(script_phase.id)
                    self.objects[script_phase.id] = script_phase
                    result.append(script_phase)
            
        return result
    
    def add_folder(self, os_path, parent=None, excludes=None, recursive=True, create_build_files=True):
        if not os.path.isdir(os_path):
            return []

        if not excludes:
            excludes = []

        results = []

        if not parent:
            parent = self.root_group
        elif not isinstance(parent, PBXGroup):
            # assume it's an id
            parent = self.objects.get(parent, self.root_group)

        path_dict = {os.path.split(os_path)[0]: parent}
        special_list = []

        for (grp_path, subdirs, files) in os.walk(os_path):
            parent_folder, folder_name = os.path.split(grp_path)
            parent = path_dict.get(parent_folder, parent)

            if [sp for sp in special_list if parent_folder.startswith(sp)]:
                continue

            if folder_name.startswith('.'):
                special_list.append(grp_path)
                continue

            if os.path.splitext(grp_path)[1] in XcodeProject.special_folders:
                # if this file has a special extension (bundle or framework mainly) treat it as a file
                special_list.append(grp_path)
                new_files = self.verify_files([folder_name], parent=parent)

                # Ignore this file if it is in excludes
                if new_files and not [m for m in excludes if re.match(m, grp_path)]:
                    results.extend(self.add_file(grp_path, parent, create_build_files=create_build_files))

                continue

            # create group
            grp = self.get_or_create_group(folder_name, path=self.get_relative_path(grp_path), parent=parent)
            path_dict[grp_path] = grp

            results.append(grp)

            file_dict = {}

            for f in files:
                if f[0] == '.' or [m for m in excludes if re.match(m, f)]:
                    continue

                kwds = {
                    'create_build_files': create_build_files,
                    'parent': grp,
                    'name': f
                }

                f_path = os.path.join(grp_path, f)
                file_dict[f_path] = kwds

            new_files = self.verify_files([n.get('name') for n in file_dict.values()], parent=grp)
            add_files = [(k, v) for k, v in file_dict.items() if v.get('name') in new_files]

            for path, kwds in add_files:
                kwds.pop('name', None)
                self.add_file(path, **kwds)

            if not recursive:
                break

        for r in results:
            self.objects[r.id] = r

        return results

    def path_leaf(self, path):
        head, tail = ntpath.split(path)
        return tail or ntpath.basename(head)

    def add_file_if_doesnt_exist(self, f_path, parent=None, tree='SOURCE_ROOT', create_build_files=True, weak=False, ignore_unknown_type=False, target=None):
        # for obj in self.objects.values():
        #     if 'path' in obj:
        #         if self.path_leaf(f_path) == self.path_leaf(obj.get('path')):
        #             return []

        return self.add_file(f_path, parent, tree, create_build_files, weak, ignore_unknown_type=ignore_unknown_type, target=target)

    def add_file(self, f_path, parent=None, tree='SOURCE_ROOT', create_build_files=True, weak=False, ignore_unknown_type=False, target=None):
        results = []
        abs_path = ''

        if os.path.isabs(f_path):
            abs_path = f_path

            if not os.path.exists(f_path):
                print("Warning: %s not existed!" % f_path)
            elif tree == 'SOURCE_ROOT':
                f_path = os.path.relpath(f_path, self.source_root)
            else:
                tree = '<absolute>'

        if not parent:
            parent = self.root_group
        elif not isinstance(parent, PBXGroup):
            # assume it's an id
            parent = self.objects.get(parent, self.root_group)

        file_ref = None
        for key in self.objects:
            obj = self.objects.get(key)
            if 'path' in obj:
                if self.path_leaf(f_path) == self.path_leaf(obj.get('path')):
                    file_ref = obj
                    break

        if file_ref is None:
            file_ref = PBXFileReference.Create(f_path, tree, ignore_unknown_type=ignore_unknown_type)
            parent.add_child(file_ref)

        results.append(file_ref)

        # create a build file for the file ref
        if file_ref.build_phase and create_build_files:

            if target is None:
                phases = self.get_build_phases(file_ref.build_phase)

                for phase in phases:
                    build_file = PBXBuildFile.Create(file_ref, weak=weak)

                    phase.add_build_file(build_file)
                    results.append(build_file)
            else:
                target_obj = self.get_native_target(target)
                if target_obj is None:
                    print("Can't find target %s" % target)
                else:
                    phases = target_obj.get("buildPhases")
                    for phaseid in phases:
                        phase_info = self.objects.get(phaseid)
                        if phase_info.get("isa") == file_ref.build_phase:
                            build_file = PBXBuildFile.Create(file_ref, weak=weak)

                            phase_info.add_build_file(build_file)
                            results.append(build_file)

            if abs_path and tree == 'SOURCE_ROOT' \
                        and os.path.isfile(abs_path) \
                        and file_ref.build_phase == 'PBXFrameworksBuildPhase':
                library_path = os.path.join('$(SRCROOT)', os.path.split(f_path)[0])
                self.add_library_search_paths([library_path], recursive=False)

            if abs_path and tree == 'SOURCE_ROOT' \
                        and not os.path.isfile(abs_path) \
                        and file_ref.build_phase == 'PBXFrameworksBuildPhase':
                framework_path = os.path.join('$(SRCROOT)', os.path.split(f_path)[0])
                self.add_framework_search_paths([framework_path, '$(inherited)'], recursive=False)

        for r in results:
            self.objects[r.id] = r

        if results:
            self.modified = True

        return results

    def check_and_repair_framework(self, base):
        name = os.path.basename(base)

        if ".framework" in name:
            basename = name[:-len(".framework")]

            finalHeaders = os.path.join(base, "Headers")
            finalCurrent = os.path.join(base, "Versions/Current")
            finalLib = os.path.join(base, basename)
            srcHeaders = "Versions/A/Headers"
            srcCurrent = "A"
            srcLib = "Versions/A/" + basename

            if not os.path.exists(finalHeaders):
                os.symlink(srcHeaders, finalHeaders)
            if not os.path.exists(finalCurrent):
                os.symlink(srcCurrent, finalCurrent)
            if not os.path.exists(finalLib):
                os.symlink(srcLib, finalLib)

    def remove_group_by_name(self, grp_name):
        objs = self.data.get('objects')
        find_grp = None
        for key in objs:
            obj = objs.get(key)
            if obj.get("isa") == "PBXGroup" and obj.get("name") == grp_name:
                find_grp = key
                break

        if find_grp is not None:
            self.remove_group(find_grp)

    def remove_group_by_path(self, grp_path):
        objs = self.data.get('objects')
        find_grp = None
        for key in objs:
            obj = objs.get(key)
            if obj.get("isa") == "PBXGroup" and obj.get("path") == grp_path:
                find_grp = key
                break

        if find_grp is not None:
            self.remove_group(find_grp)

    def remove_group(self, grp):
        objs = self.data.get('objects')
        group_info = objs.get(grp)
        if group_info is None:
            print("Can't find the PBXGroup %s in the project configuration." % grp)
            return

        objs.remove(grp)
        children = group_info.get("children")

        self.modified = True
        for child in children:
            child_info = objs.get(child)
            if child_info.get("isa") == "PBXGroup":
                self.remove_group(child)
            else:
                self.remove_file_by_id(child)

    def remove_build_file(self, build_file_id):
        objs = self.data.get('objects')
        build_file_info = objs.get(build_file_id)
        if build_file_info is None or build_file_info.get('isa') != "PBXBuildFile":
            return

        objs.remove(build_file_id)
        self.modified = True

        fileRefID = build_file_info.get("fileRef")
        need_remove_fileRef = True
        for key in objs:
            obj_info = objs.get(key)
            if obj_info.get("isa") == "PBXBuildFile" and obj_info.get("fileRef") == fileRefID:
                need_remove_fileRef = False
                break

        if need_remove_fileRef:
            objs.remove(fileRefID)

    def remove_file_by_id(self, file_id):
        objs = self.data.get('objects')
        file_info = objs.get(file_id)
        if file_info is None:
            print("Can't find the file ID \"%s\" in the project configuration." % file_id)
            return

        if file_info["isa"] == "PBXReferenceProxy":
            buildPhase = FILE_TYPE_INFO.get(file_info['fileType'], "PBXResourcesBuildPhase")
        elif file_info["isa"]  == "PBXFileReference":
            buildPhase = FILE_TYPE_INFO.get(file_info['lastKnownFileType'], "PBXResourcesBuildPhase")
        elif file_info["isa"] == "PBXVariantGroup":
            buildPhase = None
            children = file_info["children"]
            for child in children:
                self.remove_file_by_id(child)

        objs.remove(file_id)

        self.modified = True

        # remove build file
        need_remove_build_files = []
        for key in objs:
            obj = objs.get(key)
            if obj.get("isa") == "PBXBuildFile" and obj.get("fileRef") == file_id:
                need_remove_build_files.append(key)

        for item in need_remove_build_files:
            objs.remove(item)

            if buildPhase is None:
                continue

            # remove the build file from build phase
            for key in objs:
                obj = objs.get(key)
                if obj.get("isa") == buildPhase:
                    phase_files = obj.get("files")
                    if item in phase_files:
                        phase_files.remove(item)

    def remove_target(self, target_name, ignore_case=False):
        objs = self.data.get('objects')
        remove_phases = []
        remove_cfg_list = ""
        key_of_target = ""
        product_ref = ""

        find_target_name = target_name
        if ignore_case:
            find_target_name = target_name.lower()

        for key in objs:
            obj = objs.get(key)
            if obj.get("isa") == "PBXAggregateTarget":
                name = obj.get("name")
                if ignore_case:
                    name = name.lower()

                if name == find_target_name:
                    objs.remove(key)
                    remove_cfg_list = obj.get("buildConfigurationList")
                    key_of_target = key
                    self.modified = True
                    break

            if obj.get("isa") == "PBXNativeTarget":
                name = obj.get("name")
                if ignore_case:
                    name = name.lower()

                if name == find_target_name:
                    objs.remove(key)
                    remove_phases = obj.get("buildPhases")
                    remove_cfg_list = obj.get("buildConfigurationList")
                    product_ref = obj.get("productReference")
                    key_of_target = key
                    self.modified = True
                    break

        if len(key_of_target) == 0:
            return

        # remove product reference
        if len(product_ref) > 0:
            objs.remove(product_ref)
            for key in objs:
                obj = objs.get(key)
                if obj.get("isa") == "PBXGroup":
                    children = obj.get("children")
                    if product_ref in children:
                        children.remove(product_ref)

        # remove build config
        if len(remove_cfg_list) > 0:
            cfg_list_info = objs.get(remove_cfg_list)
            objs.remove(remove_cfg_list)
            cfgs = cfg_list_info.get("buildConfigurations")
            for cfg in cfgs:
                objs.remove(cfg)

        # remove build phase
        for phase in remove_phases:
            phase_obj = objs.get(phase)
            objs.remove(phase)
            build_files = phase_obj.get("files")
            for build_file in build_files:
                self.remove_build_file(build_file)

        # remove from dependencies
        for key in objs:
            obj = objs.get(key)
            if obj.get("isa") == "PBXNativeTarget":
                depends = obj.get("dependencies")
                if key_of_target in depends:
                    depends.remove(key_of_target)

    def remove_proj_reference(self, proj_name):
        objs = self.data.get('objects')
        fileRefID = ""
        for key in objs:
            obj = objs.get(key)
            if obj.get("isa") == "PBXFileReference":
                if obj.get("path") == proj_name or obj.get("name") == proj_name:
                    fileRefID = key
                    objs.remove(key)
                    break

        if len(fileRefID) <= 0:
            print("Can't find the project reference in the project configuration.")
            return

        # remove related configs
        need_remove_container = []
        need_remove_product_group = []
        for key in objs:
            obj = objs.get(key)
            isa_value = obj.get("isa")
            if isa_value == "PBXContainerItemProxy" and obj.get("containerPortal") == fileRefID:
                need_remove_container.append(key)

            if isa_value == "PBXGroup":
                children = obj.get("children")
                if fileRefID in children:
                    children.remove(fileRefID)

            if isa_value == "PBXProject":
                proj_refers = obj.get("projectReferences")
                for refer in proj_refers:
                    if refer.get("ProjectRef") == fileRefID:
                        proj_refers.remove(refer)
                        if len(proj_refers) == 0:
                            obj.remove("projectReferences")
                        need_remove_product_group.append(refer.get("ProductGroup"))

        # remove containers
        need_remove_dependencies = []
        for item in need_remove_container:
            objs.remove(item)

            for key in objs:
                obj = objs.get(key)
                if obj.get("isa") == "PBXTargetDependency" and obj.get("targetProxy") == item:
                    need_remove_dependencies.append(key)

        # remove dependencies
        for item in need_remove_dependencies:
            objs.remove(item)

            for key in objs:
                obj = objs.get(key)
                if obj.get("isa") == "PBXNativeTarget":
                    depends = obj.get("dependencies")
                    if item in depends:
                        depends.remove(item)

        # remove group
        for group in need_remove_product_group:
            self.remove_group(group)

        self.modified = True

    def remove_file_by_path(self, file_path):
        objs = self.data.get('objects')
        fileRefID = ""
        buildPhase = "PBXResourcesBuildPhase"
        for key in objs:
            obj = objs.get(key)
            if obj.get('isa') == "PBXFileReference" and obj.get("path") == file_path:
                fileRefID = key
                buildPhase = FILE_TYPE_INFO.get(obj['lastKnownFileType'], "PBXResourcesBuildPhase")
                objs.remove(key)
                break

        if len(fileRefID) <= 0:
            print("Can't find the file in the project configuration.")
            return

        self.modified = True

        buildFileIDs = []
        for key in objs:
            obj = objs.get(key)
            if obj.get('isa') == "PBXBuildFile" and obj.get("fileRef") == fileRefID:
                if key not in buildFileIDs:
                    buildFileIDs.append(key)

        if len(buildFileIDs) > 0:
            for id in buildFileIDs:
                objs.remove(id)

        for key in objs:
            obj = objs.get(key)
            if obj.get('isa') == buildPhase:
                files = obj.get("files")
                need_remove_files = []
                for fileID in files:
                    if fileID in buildFileIDs and fileID not in need_remove_files:
                        need_remove_files.append(fileID)

                if len(need_remove_files) > 0:
                    for fID in need_remove_files:
                        files.remove(fID)

            if obj.get('isa') == "PBXGroup":
                children = obj.get("children")
                for child in children:
                    if child == fileRefID:
                        children.remove(child)
                        break

    def remove_file(self, id, recursive=True):
        if not PBXType.IsGuid(id):
            id = id.id

        if id in self.objects:
            self.objects.remove(id)

            if recursive:
                groups = [g for g in self.objects.values() if g.get('isa') == 'PBXGroup']

                for group in groups:
                    if id in group['children']:
                        group.remove_child(id)

            self.modified = True

    def move_file(self, id, dest_grp=None):
        pass

    def apply_patch(self, patch_path, xcode_path):
        if not os.path.isfile(patch_path) or not os.path.isdir(xcode_path):
            print('ERROR: couldn\'t apply "%s" to "%s"' % (patch_path, xcode_path))
            return

        print('applying "%s" to "%s"' % (patch_path, xcode_path))

        return subprocess.call(['patch', '-p1', '--forward', '--directory=%s' % xcode_path, '--input=%s' % patch_path])

    def apply_mods(self, mod_dict, default_path=None):
        if not default_path:
            default_path = os.getcwd()

        keys = mod_dict.keys()

        for k in keys:
            v = mod_dict.pop(k)
            mod_dict[k.lower()] = v

        parent = mod_dict.pop('group', None)

        if parent:
            parent = self.get_or_create_group(parent)

        excludes = mod_dict.pop('excludes', [])

        if excludes:
            excludes = [re.compile(e) for e in excludes]

        compiler_flags = mod_dict.pop('compiler_flags', {})

        for k, v in mod_dict.items():
            if k == 'patches':
                for p in v:
                    if not os.path.isabs(p):
                        p = os.path.join(default_path, p)

                    self.apply_patch(p, self.source_root)
            elif k == 'folders':
                # get and compile excludes list
                # do each folder individually
                for folder in v:
                    kwds = {}

                    # if path contains ':' remove it and set recursive to False
                    if ':' in folder:
                        args = folder.split(':')
                        kwds['recursive'] = False
                        folder = args.pop(0)

                    if os.path.isabs(folder) and os.path.isdir(folder):
                        pass
                    else:
                        folder = os.path.join(default_path, folder)
                        if not os.path.isdir(folder):
                            continue

                    if parent:
                        kwds['parent'] = parent

                    if excludes:
                        kwds['excludes'] = excludes

                    self.add_folder(folder, **kwds)
            elif k == 'headerpaths' or k == 'librarypaths':
                paths = []

                for p in v:
                    if p.endswith('/**'):
                        p = os.path.split(p)[0]

                    if not os.path.isabs(p):
                        p = os.path.join(default_path, p)

                    if not os.path.exists(p):
                        continue

                    p = self.get_relative_path(p)
                    paths.append(os.path.join('$(SRCROOT)', p, "**"))

                if k == 'headerpaths':
                    self.add_header_search_paths(paths)
                else:
                    self.add_library_search_paths(paths)
            elif k == 'other_cflags':
                self.add_other_cflags(v)
            elif k == 'other_ldflags':
                self.add_other_ldflags(v)
            elif k == 'libs' or k == 'frameworks' or k == 'files':
                paths = {}

                for p in v:
                    kwds = {}

                    if ':' in p:
                        args = p.split(':')
                        p = args.pop(0)

                        if 'weak' in args:
                            kwds['weak'] = True

                    file_path = os.path.join(default_path, p)
                    search_path, file_name = os.path.split(file_path)

                    if [m for m in excludes if re.match(m, file_name)]:
                        continue

                    try:
                        expr = re.compile(file_name)
                    except re.error:
                        expr = None

                    if expr and os.path.isdir(search_path):
                        file_list = os.listdir(search_path)

                        for f in file_list:
                            if [m for m in excludes if re.match(m, f)]:
                                continue

                            if re.search(expr, f):
                                kwds['name'] = f
                                paths[os.path.join(search_path, f)] = kwds
                                p = None

                    if k == 'libs':
                        kwds['parent'] = self.get_or_create_group('Libraries', parent=parent)
                    elif k == 'frameworks':
                        kwds['parent'] = self.get_or_create_group('Frameworks', parent=parent)

                    if p:
                        kwds['name'] = file_name

                        if k == 'libs':
                            p = os.path.join('usr', 'lib', p)
                            kwds['tree'] = 'SDKROOT'
                        elif k == 'frameworks':
                            p = os.path.join('System', 'Library', 'Frameworks', p)
                            kwds['tree'] = 'SDKROOT'
                        elif k == 'files' and not os.path.exists(file_path):
                            # don't add non-existent files to the project.
                            continue

                        paths[p] = kwds

                new_files = self.verify_files([n.get('name') for n in paths.values()])
                add_files = [(k, v) for k, v in paths.items() if v.get('name') in new_files]

                for path, kwds in add_files:
                    kwds.pop('name', None)

                    if 'parent' not in kwds and parent:
                        kwds['parent'] = parent

                    self.add_file(path, **kwds)

        if compiler_flags:
            for k, v in compiler_flags.items():
                filerefs = []

                for f in v:
                    filerefs.extend([fr.id for fr in self.objects.values() if fr.get('isa') == 'PBXFileReference'
                                                                              and fr.get('name') == f])

                buildfiles = [bf for bf in self.objects.values() if bf.get('isa') == 'PBXBuildFile'
                                                                    and bf.get('fileRef') in filerefs]

                for bf in buildfiles:
                    if bf.add_compiler_flag(k):
                        self.modified = True

    def backup(self, file_name=None, backup_name=None):
        if not file_name:
            file_name = self.pbxproj_path

        if not backup_name:
            backup_name = "%s.%s.backup" % (file_name, datetime.datetime.now().strftime('%d%m%y-%H%M%S'))

        shutil.copy2(file_name, backup_name)

    def save(self, file_name=None, old_format=False):
        if old_format :
            self.saveFormatXML(file_name)
        else:
            self.saveFormat3_2(file_name)
    
    def saveFormat3_2(self, file_name=None):
        """Alias for backward compatibility"""
        self.save_new_format(file_name)
        
    def save_format_xml(self, file_name=None):
        """Saves in old (xml) format"""
        if not file_name:
            file_name = self.pbxproj_path

        # This code is adapted from plistlib.writePlist
        with open(file_name, "w") as f:
            writer = PBXWriter(f)
            writer.writeln("<plist version=\"1.0\">")
            writer.writeValue(self.data)
            writer.writeln("</plist>")

    def get_comment(self, key, whole_data):
        obj_data = whole_data.get(key)
        obj_isa = obj_data.get('isa')

        ret = ""
        if obj_isa == "PBXBuildFile":
            fileRef = obj_data.get("fileRef")
            fileRef_info = whole_data.get(fileRef)
            if fileRef_info.has_key("name"):
                fileName = fileRef_info.get("name")
            elif fileRef_info.has_key("path"):
                fileName = fileRef_info.get("path")

            if fileRef_info.has_key("fileType"):
                fileType = FILE_TYPE_INFO.get(fileRef_info["fileType"], "PBXResourcesBuildPhase")
            else:
                fileType = FILE_TYPE_INFO.get(fileRef_info.get("lastKnownFileType"), "PBXResourcesBuildPhase")

            if fileType == "PBXFrameworksBuildPhase":
                ret = "%s in %s" % (fileName, "Frameworks")
            elif fileType == "PBXSourcesBuildPhase":
                ret = "%s in %s" % (fileName, "Sources")
            elif fileType == "PBXResourcesBuildPhase":
                ret = "%s in %s" % (fileName, "Resources")
            else:
                ret = "%s" % fileName
        elif obj_isa == "PBXTargetDependency":
            ret = "PBXTargetDependency"
        elif obj_isa == "PBXContainerItemProxy":
            ret = "PBXContainerItemProxy"
        elif 'name' in obj_data:
            ret = obj_data.get('name')
        elif 'path' in obj_data:
            ret = obj_data.get('path')
        else:
            if obj_isa == 'PBXProject':
                ret = "Project object"
            elif obj_isa[0:3] == 'PBX':
                ret = obj_isa[3:-10]
            else:
                ret = 'Build configuration list for PBXNativeTarget "TARGET_NAME"'

        return ret


    def save_new_format(self, file_name=None):
        """Save in Xcode 3.2 compatible (new) format"""
        if not file_name:
            file_name = self.pbxproj_path

        # process to get the section's info and names
        objs = self.data.get('objects')
        sections = dict()
        uuids = dict()

        for key in objs:
            obj_isa = objs.get(key).get('isa')
            if obj_isa in sections:
                l = sections.get(obj_isa)
            else:
                l = list()

            l.append(tuple([key, objs.get(key)]))
            sections[obj_isa] = l

            uuids[key] = self.get_comment(key, objs)

        ro = self.data.get('rootObject')
        uuids[ro] = 'Project object'

        for key in objs:
            obj_isa = objs.get(key).get('isa')
            if obj_isa == "PBXNativeTarget":
                obj_data = objs.get(key)
                uuids[obj_data.get("buildConfigurationList")] = "Build configuration list for PBXNativeTarget \"%s\"" % obj_data.get("name")
            if obj_isa == "PBXProject":
                obj_data = objs.get(key)
                proj_name = os.path.basename(os.path.dirname(self.pbxproj_path))
                proj_name = os.path.splitext(proj_name)[0]
                uuids[obj_data.get("buildConfigurationList")] = "Build configuration list for PBXProject \"%s\"" % proj_name

        self.uuids = uuids
        self.sections = sections

        out = open(file_name, 'w')
        out.write('// !$*UTF8*$!\n')
        self._printNewXCodeFormat(out, self.data, '', enters=True)
        out.close()

    @classmethod
    def addslashes(cls, s):
        d = {'"': '\\"', "'": "\\'", "\0": "\\\0", "\\": "\\\\", "\n":"\\n"}
        return ''.join(d.get(c, c) for c in s)

    def _printNewXCodeFormat(self, out, root, deep, enters=True):
        if isinstance(root, IterableUserDict):
            out.write('{')

            if enters:
                out.write('\n')

            isa = root.pop('isa', '')

            if isa != '':  # keep the isa in the first spot
                if enters:
                    out.write('\t' + deep)

                out.write('isa = ')
                self._printNewXCodeFormat(out, isa, '\t' + deep, enters=enters)
                out.write(';')

                if enters:
                    out.write('\n')
                else:
                    out.write(' ')

            for key in sorted(root.iterkeys()):  # keep the same order as Apple.
                if enters:
                    out.write('\t' + deep)

                if re.match(regex, key).group(0) == key:
                    out.write(key.encode("utf-8") + ' = ')
                else:
                    out.write('"' + key.encode("utf-8") + '" = ')

                if key == 'objects':
                    out.write('{')  # open the objects section

                    if enters:
                        out.write('\n')
                        #root.remove('objects')  # remove it to avoid problems

                    sections = [
                        ('PBXBuildFile', False),
                        ('PBXContainerItemProxy', True),
                        ('PBXCopyFilesBuildPhase', True),
                        ('PBXFileReference', False),
                        ('PBXFrameworksBuildPhase', True),
                        ('PBXGroup', True),
                        ('PBXAggregateTarget', True),
                        ('PBXNativeTarget', True),
                        ('PBXProject', True),
                        ('PBXReferenceProxy', True),
                        ('PBXResourcesBuildPhase', True),
                        ('PBXShellScriptBuildPhase', True),
                        ('PBXSourcesBuildPhase', True),
                        ('PBXTargetDependency', True),
                        ('PBXVariantGroup', True),
                        ('XCBuildConfiguration', True),
                        ('XCConfigurationList', True)]

                    for section in sections:  # iterate over the sections
                        if self.sections.get(section[0]) is None:
                            continue

                        out.write('\n/* Begin %s section */' % section[0].encode("utf-8"))
                        self.sections.get(section[0]).sort(cmp=lambda x, y: cmp(x[0], y[0]))

                        for pair in self.sections.get(section[0]):
                            key = pair[0]
                            value = pair[1]
                            out.write('\n')

                            if enters:
                                out.write('\t\t' + deep)

                            out.write(key.encode("utf-8"))

                            if key in self.uuids and len(self.uuids[key]) > 0:
                                out.write(" /* " + self.uuids[key].encode("utf-8") + " */")

                            out.write(" = ")
                            self._printNewXCodeFormat(out, value, '\t\t' + deep, enters=section[1])
                            out.write(';')

                        out.write('\n/* End %s section */\n' % section[0].encode("utf-8"))

                    out.write(deep + '\t}')  # close of the objects section
                else:
                    self._printNewXCodeFormat(out, root[key], '\t' + deep, enters=enters)

                out.write(';')

                if enters:
                    out.write('\n')
                else:
                    out.write(' ')

            root['isa'] = isa  # restore the isa for further calls

            if enters:
                out.write(deep)

            out.write('}')

        elif isinstance(root, UserList):
            out.write('(')

            if enters:
                out.write('\n')

            for value in root:
                if enters:
                    out.write('\t' + deep)

                self._printNewXCodeFormat(out, value, '\t' + deep, enters=enters)
                out.write(',')

                if enters:
                    out.write('\n')

            if enters:
                out.write(deep)

            out.write(')')

        else:
            if len(root) > 0 and re.match(regex, root).group(0) == root:
                if root.encode("utf-8").find("-") >= 0:
                    out.write('"' + root.encode("utf-8") + '"')
                else:
                    out.write(root.encode("utf-8"))
            else:
                out.write('"' + XcodeProject.addslashes(root.encode("utf-8")) + '"')

            if root in self.uuids and len(self.uuids[root]) > 0:
                out.write(" /* " + self.uuids[root].encode("utf-8") + " */")

    @classmethod
    def Load(cls, path):
        if os_is_mac():
            cls.plutil_path = 'plutil'
        elif os_is_win32():
            cls.plutil_path = os.path.join(os.path.dirname(__file__), "plutil-win32", "plutil.exe")
        else:
            print("Can't find 'plutil' to parse the project file.")
            exit(1)

        # load project by converting to xml and then convert that using plistlib
        p = subprocess.Popen([XcodeProject.plutil_path, '-convert', 'xml1', '-o', '-', path], stdout=subprocess.PIPE)
        stdout, stderr = p.communicate()

        # If the plist was malformed, returncode will be non-zero
        if p.returncode != 0:
            print(stdout)
            return None

        tree = plistlib.readPlistFromString(stdout)
        return XcodeProject(tree, path)
    
    @classmethod    
    def LoadFromXML(cls, path):
        tree = plistlib.readPlist(path)
        return XcodeProject(tree, path)


# The code below was adapted from plistlib.py.

class PBXWriter(plistlib.PlistWriter):
    def writeValue(self, value):
        if isinstance(value, (PBXList, PBXDict)):
            plistlib.PlistWriter.writeValue(self, value.data)
        else:
            plistlib.PlistWriter.writeValue(self, value)

    def simpleElement(self, element, value=None):
        """
        We have to override this method to deal with Unicode text correctly.
        Non-ascii characters have to get encoded as character references.
        """
        if value is not None:
            value = _escapeAndEncode(value)
            self.writeln("<%s>%s</%s>" % (element, value, element))
        else:
            self.writeln("<%s/>" % element)


# Regex to find any control chars, except for \t \n and \r
_controlCharPat = re.compile(
    r"[\x00\x01\x02\x03\x04\x05\x06\x07\x08\x0b\x0c\x0e\x0f"
    r"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f]")


def _escapeAndEncode(text):
    m = _controlCharPat.search(text)
    if m is not None:
        raise ValueError("strings can't contains control characters; "
                         "use plistlib.Data instead")
    text = text.replace("\r\n", "\n")       # convert DOS line endings
    text = text.replace("\r", "\n")         # convert Mac line endings
    text = text.replace("&", "&amp;")       # escape '&'
    text = text.replace("<", "&lt;")        # escape '<'
    text = text.replace(">", "&gt;")        # escape '>'
    return text.encode("ascii", "xmlcharrefreplace")  # encode as ascii with xml character references
