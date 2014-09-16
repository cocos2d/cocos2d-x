import os
import sys
import subprocess

cppcheckDir = '../../tools/cppcheck/'
cppcheck = cppcheckDir + './cppcheck'

cppcheck_cmd = cppcheck + ' '

def add_include_path(path):
	global cppcheck_cmd 
	cppcheck_cmd += '-I ' + path + ' '
	for root, dirs, files in os.walk(path):
		for dir in dirs:
			cppcheck_cmd += '-I ' + os.path.join(root, dir) + ' '

def add_define(name):
	global cppcheck_cmd 
	cppcheck_cmd += '-D' + name + ' '

add_include_path('../../cocos')

cppcheck_cmd += '--force '
cppcheck_cmd += '--enable=all '
cppcheck_cmd += '--suppressions ' + cppcheckDir + 'suppressions.txt '
cppcheck_cmd += '--template \'{file}:{line}: error: {message} ({id})\' '
cppcheck_cmd += '--library=cfg/std.cfg '
cppcheck_cmd += '../../cocos/'
#cppcheck_cmd += '--check-config '

os.system(cppcheck_cmd)
		