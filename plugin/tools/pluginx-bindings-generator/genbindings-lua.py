#!/usr/bin/python

# This script is used to generate luabinding glue codes.
# Android ndk version must be ndk-r9b.


import sys
import os, os.path
import shutil
import ConfigParser
import subprocess
import re
from contextlib import contextmanager
import shutil
import yaml
import tempfile


def _check_ndk_root_env():
    ''' Checking the environment NDK_ROOT, which will be used for building
    '''

    try:
        NDK_ROOT = os.environ['NDK_ROOT']
    except Exception:
        print "NDK_ROOT not defined. Please define NDK_ROOT in your environment."
        sys.exit(1)

    return NDK_ROOT

def _check_python_bin_env():
    ''' Checking the environment PYTHON_BIN, which will be used for building
    '''

    try:
        PYTHON_BIN = os.environ['PYTHON_BIN']
    except Exception:
        print "PYTHON_BIN not defined, use current python."
        PYTHON_BIN = sys.executable

    return PYTHON_BIN


class CmdError(Exception):
    pass


@contextmanager
def _pushd(newDir):
    previousDir = os.getcwd()
    os.chdir(newDir)
    yield
    os.chdir(previousDir)

def _run_cmd(command):
    ret = subprocess.call(command, shell=True)
    if ret != 0:
        message = "Error running command"
        raise CmdError(message)

def _edit_yaml(filePath):
    f = open(filePath, 'r')
    data = yaml.load(f)
    f.close()
    data['conversions']['ns_map']['cocos2d::plugin::'] = 'plugin.'
    data['conversions']['to_native']['TIAPDeveloperInfo'] = 'ok &= pluginx::luaval_to_TIAPDeveloperInfo(tolua_S, ${arg_idx}, &${out_value})'
    data['conversions']['to_native']['TAdsDeveloperInfo'] = 'ok &= pluginx::luaval_to_TAdsDeveloperInfo(tolua_S, ${arg_idx}, &${out_value})'
    data['conversions']['to_native']['TAdsInfo'] = 'ok &= pluginx::luaval_to_TAdsInfo(tolua_S, ${arg_idx}, &${out_value})'
    data['conversions']['to_native']['TShareDeveloperInfo'] = 'ok &= pluginx::luaval_to_TShareDeveloperInfo(tolua_S, ${arg_idx}, &${out_value})'
    data['conversions']['to_native']['TSocialDeveloperInfo'] = 'ok &= pluginx::luaval_to_TSocialDeveloperInfo(tolua_S, ${arg_idx}, &${out_value})'
    data['conversions']['to_native']['TUserDeveloperInfo'] = 'ok &= pluginx::luaval_to_TUserDeveloperInfo(tolua_S, ${arg_idx}, &${out_value})'
    f = open(filePath, 'w')
    f.write(yaml.dump(data))
    f.close()

def main():

    cur_platform= '??'
    llvm_path = '??'
    ndk_root = _check_ndk_root_env()
    # del the " in the path
    ndk_root = re.sub(r"\"", "", ndk_root)
    python_bin = _check_python_bin_env()

    platform = sys.platform
    if platform == 'win32':
        cur_platform = 'windows'
    elif platform == 'darwin':
        cur_platform = platform
    elif 'linux' in platform:
        cur_platform = 'linux'
    else:
        print 'Your platform is not supported!'
        sys.exit(1)

    if platform == 'win32':
        x86_llvm_path = os.path.abspath(os.path.join(ndk_root, 'toolchains/llvm-3.3/prebuilt', '%s' % cur_platform))
        if not os.path.exists(x86_llvm_path):
            x86_llvm_path = os.path.abspath(os.path.join(ndk_root, 'toolchains/llvm-3.4/prebuilt', '%s' % cur_platform))
    else:
        x86_llvm_path = os.path.abspath(os.path.join(ndk_root, 'toolchains/llvm-3.3/prebuilt', '%s-%s' % (cur_platform, 'x86')))
        if not os.path.exists(x86_llvm_path):
            x86_llvm_path = os.path.abspath(os.path.join(ndk_root, 'toolchains/llvm-3.4/prebuilt', '%s-%s' % (cur_platform, 'x86')))
    x64_llvm_path = os.path.abspath(os.path.join(ndk_root, 'toolchains/llvm-3.3/prebuilt', '%s-%s' % (cur_platform, 'x86_64')))
    if not os.path.exists(x64_llvm_path):
        x64_llvm_path = os.path.abspath(os.path.join(ndk_root, 'toolchains/llvm-3.4/prebuilt', '%s-%s' % (cur_platform, 'x86_64')))

    if os.path.isdir(x86_llvm_path):
        llvm_path = x86_llvm_path
    elif os.path.isdir(x64_llvm_path):
        llvm_path = x64_llvm_path
    else:
        print 'llvm toolchain not found!'
        print 'path: %s or path: %s are not valid! ' % (x86_llvm_path, x64_llvm_path)
        sys.exit(1)

    project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..'))
    cocos_root = os.path.abspath(os.path.join(project_root, ''))
    cxx_generator_root = os.path.abspath(os.path.join(project_root, 'tools/bindings-generator'))
    pluginx_root = os.path.abspath(os.path.join(project_root, 'plugin'))

    # save config to file
    config = ConfigParser.ConfigParser()
    config.set('DEFAULT', 'androidndkdir', ndk_root)
    config.set('DEFAULT', 'clangllvmdir', llvm_path)
    config.set('DEFAULT', 'cocosdir', cocos_root)
    config.set('DEFAULT', 'cxxgeneratordir', cxx_generator_root)
    config.set('DEFAULT', 'extra_flags', '')
    config.set('DEFAULT', 'pluginxdir', pluginx_root)

    # To fix parse error on windows, we must difine __WCHAR_MAX__ and undefine __MINGW32__ .
    if platform == 'win32':
        config.set('DEFAULT', 'extra_flags', '-D__WCHAR_MAX__=0x7fffffff -U__MINGW32__')

    conf_ini_file = os.path.abspath(os.path.join(os.path.dirname(__file__), 'userconf.ini'))

    print 'generating userconf.ini...'
    with open(conf_ini_file, 'w') as configfile:
      config.write(configfile)


    # set proper environment variables
    if 'linux' in platform or platform == 'darwin':
        os.putenv('LD_LIBRARY_PATH', '%s/libclang' % cxx_generator_root)
    if platform == 'win32':
        path_env = os.environ['PATH']
        os.putenv('PATH', r'%s;%s\libclang;%s\tools\win32;' % (path_env, cxx_generator_root, cxx_generator_root))

    # edit conversions config for pluginx
    conversions_yaml = '%s/targets/lua/conversions.yaml' % cxx_generator_root
    conversions_backup = '%s.backup' % conversions_yaml
    shutil.copy(conversions_yaml, conversions_backup)
    _edit_yaml(conversions_yaml)

    try:

        tolua_root = '%s/plugin/tools/pluginx-bindings-generator/tolua' % project_root
        output_dir = '%s/plugin/luabindings/auto' % project_root

        cmd_args = {'cocos2dx_pluginx.ini' : ('cocos2dx_pluginx', 'lua_cocos2dx_pluginx_auto')}
        target = 'lua'
        generator_py = '%s/generator.py' % cxx_generator_root
        for key in cmd_args.keys():
            args = cmd_args[key]
            cfg = '%s/%s' % (tolua_root, key)
            print 'Generating bindings for %s...' % (key[:-4])
            command = '%s %s %s -s %s -t %s -o %s -n %s' % (python_bin, generator_py, cfg, args[0], target, output_dir, args[1])
            _run_cmd(command)

        if platform == 'win32':
            with _pushd(output_dir):
                _run_cmd('dos2unix *')

        # replace header file
        tmpfd,tmpname = tempfile.mkstemp(dir='.')
        input_file_name = '%s/%s.cpp' % (output_dir, args[1])
        try:
            output_file = os.fdopen(tmpfd, 'w')
            input_file = open(input_file_name)
            for line in input_file:
                output_file.write(line.replace('#include "LuaBasicConversions.h"', '#include "LuaBasicConversions.h"\n#include "lua_pluginx_basic_conversions.h"')) 
        finally:
            output_file.close()
            input_file.close()
        shutil.move(tmpname, input_file_name)

        print '---------------------------------'
        print 'Generating lua bindings succeeds.'
        print '---------------------------------'

    except Exception as e:
        if e.__class__.__name__ == 'CmdError':
            print '---------------------------------'
            print 'Generating lua bindings fails.'
            print '---------------------------------'
            sys.exit(1)
        else:
            raise
    finally:
        shutil.move(conversions_backup, conversions_yaml)


# -------------- main --------------
if __name__ == '__main__':
    main()
