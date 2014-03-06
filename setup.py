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
* otherwise it will the add environment variable sinto ~/.profile if it exists

Will create ~/.bash_profile when none of them exist, and add environment variable into it.

'''

import os
import sys
import fileinput
from optparse import OptionParser

COCOS_CONSOLE_ROOT = 'COCOS_CONSOLE_ROOT'
NDK_ROOT = 'NDK_ROOT'


class SetEnvVar(object):
    def __init__(self, ndk=None):
        self.current_absolute_path = os.path.dirname(os.path.realpath(__file__))
        self.ndk_root = ndk
        # whether the value of "ndk_root" is passed or not
        self.ndk_root_passed = False
        self.file_to_write_environment = None
        self.file_used_for_setup = ''
        self.variable_found_in_env = False

    def _isWindows(self):
        return sys.platform == 'win32'

    def _isLinux(self):
        return sys.platform.startswith('linux')

    # modify register table to add an environment variable on windows
    # TODO: test in on windows
    def _set_environment_variable_win32(self, key, value):

        import _winreg
        env = _winreg.OpenKeyEx(_winreg._winreg.HKEY_LOCAL_MACHINE,
                                r'SYSTEM\ControlSet001\Control\Session Manager\Environment',
                                0,
                                _winreg.KEY_SET_VALUE | _winreg.KEY_READ)
        _winreg.SetValueEx(env, key, 0, _winreg.REG_SZ, value)

    def _set_environment_variable_unix(self, key, value):

        home = os.path.expanduser('~')
        if os.path.exists(os.path.join(home, '.bash_profile')):
            file_to_write = os.path.join(home, '.bash_profile')
        elif os.path.exists(os.path.join(home, '.bash_login')):
            file_to_write = os.path.join(home, '.bash_login')
        elif os.path.exists(os.path.join(home, '.profile')):
            file_to_write = os.path.join(home, '.profile')
        else:
            file_to_write = os.path.join(home, '.bash_profile')

        self.file_to_write_environment = file_to_write

        file = open(file_to_write, 'a')
        if self.ndk_root_passed and self._find_string_in_file('export '.join(key), file_to_write):
            # if ndk_root is passed and "ndk_root" is set yet, replace existing string in the file
            for line in fileinput.input(file_to_write, inplace=1):
                if line.startswith('export '.join(key)):
                    line = 'export %s=%s' % (key, value)
                sys.stdout.write(line)
        else:
            file.write('export %s=%s\n' % (key, value))
            file.write('export PATH=$%s:$PATH\n' % key)
            file.close()

    def _set_environment_variable(self, key, value):

        if self._isWindows():
            self._set_environment_variable_win32(key, value)
        else:
            self._set_environment_variable_unix(key, value)

    def _find_string_in_file(self, string, file_path):
        with open(file_path) as f:
            for line in f:
                if line.startswith(string):
                    return True
        return False

    def _find_environment_variable(self, var):
        try:
            result = os.environ[var]
            self.variable_found_in_env = true
            if result:
                return True
            else:
                return False
        except Exception:
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
        return False

    def _get_ndk_root(self):
        if not self._find_environment_variable(NDK_ROOT):

            # python on linux doesn't include Tkinter model, so let user input in terminal
            if self._isLinux():
                self.ndk_root = raw_input('Couldn\'t find the "NDK_ROOT" envrironment variable. Please enter it: ')        
            else:

                # pop up a window to let user select path for ndk root
                import Tkinter
                import tkFileDialog

                root = Tkinter.Tk()
                self._center(root)

                def callback():
                    self.ndk_root = tkFileDialog.askdirectory()
                    root.destroy()

                frame = Tkinter.Frame(root)
                Tkinter.Label(frame, text='Select path for NDK_ROOT:').pack(side=Tkinter.LEFT)
                Tkinter.Button(frame, text='...', command=callback).pack(side=Tkinter.LEFT)
                frame.pack()
                root.mainloop()

            return True

        return False

    # display a window in center and put it on top
    def _center(self, win):
        win.update_idletasks()
        width = win.winfo_width()
        height = win.winfo_height()
        x = (win.winfo_screenwidth() / 2) - (width / 2)
        y = (win.winfo_screenheight() / 2) - (height / 2)
        win.geometry('{}x{}+{}+{}'.format(width, height, x, y))
        win.wm_attributes('-topmost', 1)

    def set_ndk_root(self, value):
        print '-> Adding NDK_ROOT environment variable...',

        self.ndk_root_updated = False

        if value:
            self.ndk_root = value
            ndk_root_updated = True
        else:
            ndk_root_updated = self._get_ndk_root()

        if self.ndk_root:
            os.environ[NDK_ROOT] = self.ndk_root
            self._set_environment_variable(NDK_ROOT, self.ndk_root)
            ndk_root_updated = True
        else:
            ndk_root_updated = False

        if ndk_root_updated:
            print 'OK'
        return ndk_root_updated

    def set_console_root(self):

        print '-> Adding COCOS2D_CONSOLE_ROOT environment variable...',
        if not self._find_environment_variable(COCOS_CONSOLE_ROOT):
            cocos_consle_root = os.path.join(self.current_absolute_path, 'tools/cocos2d-console/bin')
            self._set_environment_variable(COCOS_CONSOLE_ROOT, cocos_consle_root)
            print 'OK'
            return True

        print 'ALREADY ADDED'
        return False

    def set_environment_variables(self, ndk_root):

        print '\nSetting up cocos2d-x...'

        console_updated = self.set_console_root()
        ndk_root_updated = self.set_ndk_root(ndk_root)

        if self._isWindows():
            if console_updated or ndk_root_updated:
                result_string = '\nSet up successful.\n'
                if console_updated:
                    result_string += '\tCOCOS_CONSOLE_ROOT was added into the registry.\n'
                if ndk_root_updated:
                    result_string += '\tNDK_ROOT was added into the registry.\n'

                print result_string
            else:
                print 'cocos2d-x was already setted up. Edit the registry manually in order to change the current settings'
        else:
            if console_updated or ndk_root_updated:
                result_string = '\nSet up successful:\n'
                if console_updated:
                    result_string += '\tCOCOS_CONSOLE_ROOT was added into %s.\n' % self.file_to_write_environment
                if ndk_root_updated:
                    result_string += '\tNDK_ROOT was added into %s.\n' % self.file_to_write_environment

                print result_string
            else:
                if self.variable_found_in_env:
                    print '\nFound cocos2d-x environment variables. No action needed'
                else:
                    print '\ncocos2d-x was already set up. Edit the script %s manually' % self.file_used_for_setup


if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('-n', '--ndkroot', dest='ndk_root', help='directory of ndk root')
    opts, args = parser.parse_args()

    # ndk_root is passed in
    if opts.ndk_root:
        os.environ[NDK_ROOT] = opts.ndk_root
        env = SetEnvVar(True)
        env.set_environment_variables(opts.ndk_root)
        exit(0)

    # set environment variables
    env = SetEnvVar(False)
    env.set_environment_variables(None)
