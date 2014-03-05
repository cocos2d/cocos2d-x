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
* add environment variable into ~/.bash_profile when exists
* add environment variable into ~/.bash_login when exits and ~/.bash_profile not exits
* add environment variable into ~/.profile when exits and ~/.bash_profile & ~/.bash_login not exist

Will create ~/.bash_profile when none of them exist, and add environment variable into it.

'''

import os
import sys
import fileinput
from optparse import OptionParser

COCOS_CONSOLE_ROOT = 'COCOS_CONSOLE_ROOT'
NDK_ROOT = 'NDK_ROOT'


class SetEnvVar:

	current_absolute_path = os.path.dirname(os.path.realpath(__file__))
	ndk_root = None
	# whether the value of "ndk_root" is passed or not
	ndk_root_passed = False 
	file_to_write_environment = None

	@staticmethod
	def _isWindows():
		return sys.platform == 'win32'

	@staticmethod
	def _isLinux():
		return sys.platform.startswith('linux')

	# modify register table to add an environment variable on windows
	# TODO: test in on windows
	@staticmethod
	def _set_environment_variable_win32(key, value):

		import _winreg

		env = _winreg.OpenKeyEx(_winreg._winreg.HKEY_LOCAL_MACHINE,\
			                    r'SYSTEM\ControlSet001\Control\Session Manager\Environment',\
			                    0,
			                    _winreg.KEY_SET_VALUE|_winreg.KEY_READ)
		_winreg.SetValueEx(env, key, 0, _winreg.REG_SZ, value)

	@staticmethod
	def _set_environment_variable_unix(key, value):

		home = os.path.expanduser('~')
		if os.path.exists(os.path.join(home, '.bash_profile')):
			file_to_write = os.path.join(home, '.bash_profile')
		elif os.path.exists(os.path.join(home, '.bash_login')):
			file_to_write = os.path.join(home, '.bash_login')
		elif os.path.exists(os.path.join(home, '.profile')):
			file_to_write = os.path.join(home, '.profile')
		else:
			file_to_write = os.path.join(home, '.bash_profile')

		SetEnvVar.file_to_write_environment = file_to_write

		file = open(file_to_write, 'a')
		if SetEnvVar.ndk_root_passed and SetEnvVar._find_string_in_file('export '.join(key), file_to_write):
			# if ndk_root is passed and "ndk_root" is set yet, replace existing string in the file
			for line in fileinput.input(file_to_write, inplace=1):
				if line.startswith('export '.join(key)):
					line = 'export %s=%s' % (key, value)
				sys.stdout.write(line)
		else:
			file.write('export %s=%s\n' % (key, value))
			file.write('export PATH=$%s:$PATH\n' % key)
			file.close()


	@staticmethod
	def _set_environment_variable(key, value):

		if SetEnvVar._isWindows():
			_set_environment_variable_win32(key, value)
		else:
			SetEnvVar._set_environment_variable_unix(key, value)

	@staticmethod
	def _find_string_in_file(string, file_path):
		with open(file_path) as f:
			for line in f:
				if line.startswith(string):
					return True
		return False


	@staticmethod
	def _find_environment_variable(var):
		
		try:
			result = os.environ[var]
			if result:
				return True
			else:
				return False
		except Exception:
			string_to_search = 'export %s' % var 
			home = os.path.expanduser('~')

			# find it in ~/.bash_profile
			if os.path.exists(os.path.join(home, '.bash_profile')):
				if SetEnvVar._find_string_in_file(string_to_search, os.path.join(home, '.bash_profile')):
					return True

			# find it in ~/.bash_login
			if os.path.exists(os.path.join(home, '.bash_login')):
				if SetEnvVar._find_string_in_file(string_to_search, os.path.join(home, '.bash_login')):
					return True

			# find it in ~/.profile if exit
			if os.path.exists(os.path.join(home, '.profile')):
				if SetEnvVar._find_string_in_file(string_to_search, os.path.join(home, '.profile')):
					return True

		return False


	@staticmethod
	def _get_ndk_root():

		if not SetEnvVar._find_environment_variable(NDK_ROOT):

			# python on linux doesn't include Tkinter model, so let user input in terminal
			if SetEnvVar._isLinux():
				SetEnvVar.ndk_root = raw_input('can not find envrironment variable "NDK_ROOT", please enter it: ')		
			else:

				# pop up a window to let user select path for ndk root
				import Tkinter, tkFileDialog

				root = Tkinter.Tk()
				SetEnvVar._center(root)

				def callback():
					SetEnvVar.ndk_root = tkFileDialog.askdirectory()
					root.destroy()

				frame = Tkinter.Frame(root)
				Tkinter.Label(frame, text='select path for ndk root').pack(side=Tkinter.LEFT)
				Tkinter.Button(frame, text='...', command=callback).pack(side=Tkinter.LEFT)
				frame.pack()
				root.mainloop()

			return True

		return False

	# display a window in center and put it on top
	@staticmethod
	def _center(win):
		win.update_idletasks()
		width = win.winfo_width()
		height = win.winfo_height()
		x = (win.winfo_screenwidth() / 2) - (width / 2)
		y = (win.winfo_screenheight() / 2) - (height / 2)
		win.geometry('{}x{}+{}+{}'.format(width, height, x, y))
		win.wm_attributes('-topmost', 1)


	@staticmethod
	def set_ndk_root(value):

		ndk_root_updated = False

		if value:
			SetEnvVar.ndk_root = value
			ndk_root_updated = True
		else:
			ndk_root_updated = SetEnvVar._get_ndk_root()

		if SetEnvVar.ndk_root:
			os.environ[NDK_ROOT] = SetEnvVar.ndk_root
			SetEnvVar._set_environment_variable(NDK_ROOT, SetEnvVar.ndk_root)
			ndk_root_updated = True
		else:
			ndk_root_updated = False

		return ndk_root_updated

	@staticmethod
	def set_console_root():

		if not SetEnvVar._find_environment_variable(COCOS_CONSOLE_ROOT):
			cocos_consle_root = os.path.join(SetEnvVar.current_absolute_path, 'tools/cocos2d-console/bin')
			SetEnvVar._set_environment_variable(COCOS_CONSOLE_ROOT, cocos_consle_root)
			return True

		return False

	@staticmethod
	def set_environment_variables(ndk_root):

		console_updated = SetEnvVar.set_console_root()
		ndk_root_updated = SetEnvVar.set_ndk_root(ndk_root)

		if SetEnvVar._isWindows():
			if console_updated or ndk_root_updated:
				result_string = 'Set up successful.' 
				if console_updated:
					result_string += 'COCOS_CONSOLE_ROOT was added into register table.\n'
				if ndk_root_updated:
					result_string += 'NDK_ROOT was added into register table.'

				print result_string
		else:
			if console_updated or ndk_root_updated:
				result_string = 'Set up successful.' 
				if console_updated:
					result_string += 'COCOS_CONSOLE_ROOT was added into %s.\n' % SetEnvVar.file_to_write_environment
				if ndk_root_updated:
					result_string += 'NDK_ROOT was added into %s.' % SetEnvVar.file_to_write_environment

				print result_string


if __name__ == '__main__':
	
	parser = OptionParser()
	parser.add_option('-n', '--ndkroot', dest='ndk_root', help='directory of ndk root')
	opts, args = parser.parse_args()

	# ndk_root is passed in
	if opts.ndk_root:
		os.environ[NDK_ROOT] = opts.ndk_root
		SetEnvVar.ndk_root_passed = True
		SetEnvVar.set_environment_variables(opts.ndk_root)
		exit(0)

	# set environment variables
	SetEnvVar.set_environment_variables(None)
		