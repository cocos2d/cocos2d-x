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

import os
import sys
from optparse import OptionParser

COCOS_CONSOLE_ROOT = 'COCOS_CONSOLE_ROOT'
NDK_ROOT = 'NDK_ROOT1'


class SetEnvVar:

	current_absolute_path = os.path.dirname(os.path.realpath(__file__))

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

	# modify ~/.bash_profile to add an environment variable
	@staticmethod
	def _set_environment_variable_unix(key, value):
		home = os.path.expanduser('~')
		profile_path = os.path.join(home, '.bash_profile')

		file = open(profile_path, 'a')
		file.write('export %s=%s\n' % (key, value))
		file.write('export PATH=$%s:$PATH\n' % key)
		file.close()

		# make it take effect immediately
		cmd = 'source ' + profile_path
		p = os.popen(cmd)
		p.close()


	@staticmethod
	def _set_environment_variable(key, value):

		if SetEnvVar._isWindows():
			_set_environment_variable_win32(key, value)
		else:
			SetEnvVar._set_environment_variable_unix(key, value)

	@staticmethod
	def set_environment_variables():

		SetEnvVar.set_console_root()
		SetEnvVar.set_ndk_root(None)

	@staticmethod
	def set_console_root():
		
		try:
			cocos_console_root = os.environ[COCOS_CONSOLE_ROOT]
		except Exception:
			cocos_console_root = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'tools/cocos2d-console/bin')
			SetEnvVar._set_environment_variable(COCOS_CONSOLE_ROOT, cocos_console_root)
			os.environ[COCOS_CONSOLE_ROOT] = cocos_console_root
		finally:
			print "'COCOS_CONSOLE_ROOT' is %s" % cocos_console_root

	@staticmethod
	def _get_ndk_root():

		ndk_root = None

		# python on linux doesn't include Tkinter model, so let user input in terminal
		if SetEnvVar._isLinux():
			print "not linux"
			while True:

				ndk_root = raw_input('Enter path of ndk, press enter to skip: ')
				if not ndk_root:
					break

				if not os.path.exists(ndk_root):
					print 'input path %s does not exist' % ndk_root
				else:
					break
			
		else:
			# pop up a window to let user select path for ndk root
			import Tkinter, tkFileDialog

			try:
				ndk_root = os.environ[NDK_ROOT]
			except Exception:
				root = Tkinter.Tk()
				SetEnvVar._center(root)

				def callback():
					ndk_root = tkFileDialog.askdirectory()
					root.destroy()


				frame = Tkinter.Frame(root)
				Tkinter.Label(frame, text='select path for ndk root').pack(side=Tkinter.LEFT)
				Tkinter.Button(frame, text='...', command=callback).pack(side=Tkinter.LEFT)
				frame.pack()
				root.mainloop()

		return ndk_root

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

		if value:
			ndk_root = value
		else:
			ndk_root = SetEnvVar._get_ndk_root()

		print "ndk_root is %s" % ndk_root

		if ndk_root:
			os.environ[NDK_ROOT] = ndk_root
			SetEnvVar._set_environment_variable(NDK_ROOT, ndk_root)

usage = ""


if __name__ == '__main__':
	
	parser = OptionParser()
	parser.add_option('-n', '--ndkroot', dest='ndk_root', help='directory of ndk root')
	opts, args = parser.parse_args()

	# ndk_root is passed in
	if opts.ndk_root:
		os.environ[NDK_ROOT] = opts.ndk_root
		SetEnvVar.set_ndk_root()
		exit(0)

	# set environment variables
	SetEnvVar.set_environment_variables()
		