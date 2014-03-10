#!/usr/bin/python
#coding=utf-8
"""****************************************************************************
Copyright (c) 2014 cocos2d-x.org

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

'''
On Max OS X, when start a shell, it will read these files and execute commands in sequence:

~/.bash_profile
~/.bash_login
~/.profile

And it will read only one of them. So we will add environment variable in the same sequence.
Which means that
* add environment variables into ~/.bash_profile if it exists
* otherwise it will the add environment variables into ~/.bash_login if it exists
* otherwise it will the add environment variables into ~/.profile if it exists

Will create ~/.bash_profile when none of them exist, and add environment variables into it.

'''

import os
import sys
import fileinput
from optparse import OptionParser

COCOS_CONSOLE_ROOT = 'COCOS_CONSOLE_ROOT'
NDK_ROOT = 'NDK_ROOT'
ANDROID_SDK_ROOT = 'ANDROID_SDK_ROOT'


class SetEnvVar(object):
    def __init__(self, ndk=None, android_sdk=None):
        self.current_absolute_path = os.path.dirname(os.path.realpath(__file__))
        self.android_sdk_root = android_sdk
        self.file_used_for_setup = ''

    def _isWindows(self):
        return sys.platform == 'win32'

    def _isLinux(self):
        return sys.platform.startswith('linux')

    def _get_filepath_for_setup(self):

        home = os.path.expanduser('~')
        if os.path.exists(os.path.join(home, '.bash_profile')):
            file_to_write = os.path.join(home, '.bash_profile')
        elif os.path.exists(os.path.join(home, '.bash_login')):
            file_to_write = os.path.join(home, '.bash_login')
        elif os.path.exists(os.path.join(home, '.profile')):
            file_to_write = os.path.join(home, '.profile')
        else:
            file_to_write = os.path.join(home, '.bash_profile')
            file = open(file_to_write, 'w')
            file.close()

        return file_to_write

    def _update_system_variable(self, origin_content, target_content):

        is_updated = False
        file = open(self.file_used_for_setup, 'a')
        for line in fileinput.input(file_to_write, inplace=1):
            if line.startswith(origin_content):
                line = target_content
                if_undated = True
            sys.stdout.write(line)

        file.close()
        return is_updated

    def _find_string_in_file(self, string, file_path):
        with open(file_path) as f:
            for line in f:
                if line.startswith(string):
                    return True
        return False

    # modify registry table to add an environment variable on windows
    def _set_environment_variable_win32(self, key, value):

        import _winreg
        try:
            env = None
            env = _winreg.OpenKeyEx(_winreg.HKEY_CURRENT_USER,
                                'Environment',
                                0,
                                _winreg.KEY_SET_VALUE | _winreg.KEY_READ)
            _winreg.SetValueEx(env, key, 0, _winreg.REG_SZ, value)
            _winreg.CloseKey(env)
        except Exception:
            if env:
                _winreg.CloseKey(env)
            print 'Warning: Could not add "%s" into registry' % key
            return False
        return True

    def _set_environment_variable_unix(self, key, value):

        file = open(self.file_used_for_setup, 'a')
        file.write('export %s=%s\n' % (key, value))
        file.write('export PATH=$%s:$PATH\n' % key)
        if key == ANDROID_SDK_ROOT:
            file.write('export PATH=$%s/sdk/tools:$%s/sdk/platform-tools:$PATH\n' % (key, key))
        file.close()
        return True

    def _set_environment_variable(self, key, value):

        ret = False
        if self._isWindows():
            ret = self._set_environment_variable_win32(key, value)
        else:
            ret = self._set_environment_variable_unix(key, value)
        return ret

    def _find_environment_variable(self, var):
        try:
            os.environ[var]
            return True
        except Exception:
            if not self._isWindows():
                string_to_search = 'export %s' % var
                home = os.path.expanduser('~')

                # search it in ~/.bash_profile
                path = os.path.join(home, '.bash_profile')
                if os.path.exists(path):
                    if self._find_string_in_file(string_to_search, path):
                        self.file_used_for_setup = path
                        return True

                # search it in ~/.bash_login
                path = os.path.join(home, '.bash_login')
                if os.path.exists(path):
                    if self._find_string_in_file(string_to_search, path):
                        self.file_used_for_setup = path
                        return True

                # search it in ~/.profile
                path = os.path.join(home, '.profile')
                if os.path.exists(path):
                    if self._find_string_in_file(string_to_search, path):
                        self.file_used_for_setup = path
                        return True
            else:
                import _winreg
                try:
                    env = None
                    env = _winreg.OpenKeyEx(_winreg.HKEY_CURRENT_USER,
                                'Environment',
                                0,
                                _winreg.KEY_READ)

                    _winreg.QueryValueEx(env, var)
                    _winreg.CloseKey(env)
                    return True
                except Exception:
                    if env:
                        _winreg.CloseKey(env)
                    return False

    def _get_input_value(self, sys_var):

        return raw_input('\tPlease enter its path (or press Enter to skip): ')

#         # python on linux doesn't include Tkinter model, so let user input in terminal
#         if self._isLinux():
#             input_value = raw_input('Couldn\'t find the "%s" envrironment variable. Please enter it: ' % sys_var)        
#         else:

#             # pop up a window to let user select path for ndk root
#             import Tkinter
#             import tkFileDialog

#             self.tmp_input_value = None

#             root = Tkinter.Tk()

#             if sys_var == NDK_ROOT:
#                 root.wm_title('Set NDK_ROOT')
#             else:
#                 root.wm_title('Set ANDROID_SDK_ROOT')

#             def callback():
#                 self.tmp_input_value = tkFileDialog.askdirectory()
#                 root.destroy()

#             if sys_var == NDK_ROOT:
#                 label_content = 'Select path for Android NDK:'
#                 label_help = """
# The Android NDK is needed to develop games for Android. 
# For further information, go to:
# http://developer.android.com/tools/sdk/ndk/index.html.

# You can safely skip this step now. You can set the NDK_ROOT later.
#                 """

#             if sys_var == ANDROID_SDK_ROOT:
#                 label_content = 'Select path for Android SDK'
#                 label_help = """
# The Android SDK is needed to develop games for Android. 
# For further information, go to:
# https://developer.android.com/tools/sdk/ndk/index.html. 

# You can safely skip this step now. You can set the ANDROID_SDK_ROOT later.
#                 """

#             Tkinter.Label(root, text=label_help).pack()
#             Tkinter.Button(root, text=label_content, command=callback).pack()
#             self._center(root)
#             root.mainloop()

#             input_value = self.tmp_input_value
#             self.tmp_input_value = None
       
#         return input_value

#     # display a window in center and put it on top
#     def _center(self, win):
#         win.update_idletasks()
#         width = win.winfo_width()
#         height = win.winfo_height()
#         x = (win.winfo_screenwidth() / 2) - (width / 2)
#         y = (win.winfo_screenheight() / 2) - (height / 2)
#         win.geometry('{}x{}+{}+{}'.format(width, height, x, y))
#         win.wm_attributes('-topmost', 1)

    def _is_ndk_root_valid(self, ndk_root):
        if not ndk_root:
            return False

        ndk_build_path = os.path.join(ndk_root, 'ndk-build')
        if os.path.isfile(ndk_build_path):
            return True
        else:
            return False

    def _is_android_sdk_root_valid(self, android_sdk_root):
        if not android_sdk_root:
            return False

        android_path = os.path.join(android_sdk_root, 'sdk/tools/android')
        if os.path.isfile(android_path):
            return True
        else:
            return False

    def set_console_root(self):

    	print ""
        print '-> Adding COCOS2D_CONSOLE_ROOT environment variable...',
        if not self._find_environment_variable(COCOS_CONSOLE_ROOT):
            cocos_consle_root = os.path.join(self.current_absolute_path, 'tools/cocos2d-console/bin')
            if self._set_environment_variable(COCOS_CONSOLE_ROOT, cocos_consle_root):
                print 'OK'
                print '  -> Added: %s = %s' % (COCOS_CONSOLE_ROOT, cocos_consle_root)
                return True
        else:
            print 'ALREADY ADDED'
            return False


    def set_environment_variables(self, ndk_root, android_sdk_root):

        print '\nSetting up cocos2d-x...'

        self.file_used_for_setup = self._get_filepath_for_setup()
        
        console_added = self.set_console_root()

        #
        # NDK_ROOT
        #
        print ""
        print '-> Looking for NDK_ROOT envrironment variable...',

        ndk_root_added = False
        ndk_root_found = self._find_environment_variable(NDK_ROOT)

        if not ndk_root and not ndk_root_found:
            print "NOT FOUND"
            ndk_root = self._get_input_value(NDK_ROOT)

        if ndk_root != "" and not self._is_ndk_root_valid(ndk_root) and not ndk_root_found:
            print 'Error: %s is not a valid path of NDK_ROOT. Ignoring it.' % ndk_root

        if ndk_root_found:
            print 'FOUND'
        else:
            if ndk_root and self._is_ndk_root_valid(ndk_root):
                if self._set_environment_variable(NDK_ROOT, ndk_root):
                    ndk_root_added = True
                    print 'ADDED'
                    print '  -- Added: %s = %s' % (NDK_ROOT, ndk_root)


        #
        # ANDROID_SDK_ROOT
        #
        print ""        
        print '-> Looking for ANDROID_SDK_ROOT envrironment variable...',

        android_sdk_root_added = False
        android_sdk_root_found = self._find_environment_variable(ANDROID_SDK_ROOT)

        if not android_sdk_root and not android_sdk_root_found:
            print "NOT FOUND"
            android_sdk_root = self._get_input_value(ANDROID_SDK_ROOT)
        
        if android_sdk_root != "" and not self._is_android_sdk_root_valid(android_sdk_root) and not android_sdk_root_found:
            print 'Error: %s is not a valid path of ANDROID_SDK_ROOT. Ignoring it.' % android_sdk_root

        if android_sdk_root_found:
            print 'FOUND'
        else:
            if android_sdk_root and self._is_android_sdk_root_valid(android_sdk_root):
                if self._set_environment_variable(ANDROID_SDK_ROOT, android_sdk_root):
                    android_sdk_root_added = True
                    print 'ADDED'
                    print '  -> Added: %s = %s' % (ANDROID_SDK_ROOT, android_sdk_root)

        #
        if self._isWindows():
            target = 'registry'
        else:
            target = self.file_used_for_setup

        if console_added or ndk_root_added or android_sdk_root_added:
            print '\nSet up successfull:'

            if console_added:
                print '\tCOCOS_CONSOLE_ROOT was added into %s' % target
            if ndk_root_added:
                print '\tNDK_ROOT was added into %s' % target
            if android_sdk_root_added:
                print '\tANDROID_SDK_ROOT was added into %s' % target
        else:
            print '\nCOCOS_CONSOLE_ROOT was already added. Edit "%s" for manual changes' % target

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('-n', '--ndkroot', dest='ndk_root', help='directory of ndk root')
    parser.add_option('-a', '--androidsdkroot', dest='android_sdk_root', help='directory of android sdk root')
    opts, args = parser.parse_args()

    # set environment variables
    env = SetEnvVar()
    env.set_environment_variables(opts.ndk_root, opts.android_sdk_root)
