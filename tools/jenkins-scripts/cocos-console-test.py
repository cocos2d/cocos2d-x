#!/usr/bin/python
# create new project by cocos-console
# compile, deploy project and run
# perpose: for autotest cocos2d-console command.
# now support: mac- mac/ios/android
# will add: window-android,linux-android

import os
import subprocess
import sys
import json
import time
import socket

# default console_param.
console_param = '[console run]'
# get param from commit.
if os.environ.has_key('payload'):
	payload_str = os.environ['payload']
	payload = json.loads(payload_str)
	if payload.has_key('console'):
		console_param = payload['console']
console_param = console_param[1:len(console_param)-1]
print 'console_param:',console_param

console_param_arr = console_param.split(' ')

# enum command type
class ENUM_PARAM:
	new = 0
	compile = 1
	deploy = 2
	run = 3

# partition different level
LEVEL_COCOS = {
	ENUM_PARAM.new : 1,
	ENUM_PARAM.compile : 2,
	ENUM_PARAM.deploy : 4,
	ENUM_PARAM.run : 8
}

# level's cocos command
COCOS_CMD = {
	ENUM_PARAM.new:'new',
	ENUM_PARAM.compile:'compile',
	ENUM_PARAM.deploy:'deploy',
	ENUM_PARAM.run:'run'
}

# set cocos_param for run different command
cocos_param = 0
for level in LEVEL_COCOS:
	if console_param_arr.count(COCOS_CMD[level]):
		cocos_param = cocos_param + LEVEL_COCOS[level]
if cocos_param < LEVEL_COCOS[ENUM_PARAM.new]:
	cocos_param = LEVEL_COCOS[ENUM_PARAM.new]
print 'cocos_param:', cocos_param

# project types
project_types = ['cpp', 'lua']
# project suffix
PROJ_SUFFIX = 'Proj'
# different phone platform
phonePlats = ['mac','ios','android']

# need use console's position, perhaps should be set an env-param
cocos_console_dir = 'tools/cocos2d-console/bin/'

# now cocos2d-console suport different run on Platforms, e.g: only run android on win
runSupport = {
	'darwin' : {'mac':1,'ios':1,'android':1},
	'win' : {'mac':0,'ios':0,'android':1},
	'linux' : {'mac':0,'ios':0,'android':1}
}

# get current running system
curPlat = sys.platform
if curPlat.find('linux') >= 0:
	curPlat = 'linux'
elif curPlat.find('darwin') >= 0:
	curPlat = 'darwin'
else:
	curPlat = 'win'
print 'current platform is:', curPlat

# delete project.(will use different system command to delete.just mac now.)
def clean_project():
	for proj in project_types:
		cmd = 'rm -rf '+proj+PROJ_SUFFIX
		os.system(cmd)

# file path.(for add console listen command.)
FILE_PATH = '/Classes/AppDelegate.cpp'
FILE_DIR = {
	'cpp':'',
	'lua':'/frameworks/runtime-src'
}
PARSE_WORD = 'director->setDisplayStats(true);'
CONSOLE_COMMAND = 'director->getConsole()->listenOnTCP(5678);'

# add console listenOnTCP to AppDelegate.cpp.
def addConsoleListenOnTCP(name):
	filePath = name+PROJ_SUFFIX+FILE_DIR[name]+FILE_PATH
	print 'filePath:',filePath
	strCont = ''
	if os.path.isfile(filePath):
		file_object = open(filePath, 'r')
		strLine = file_object.readline() 
		while strLine:
		 	strCont = strCont + strLine
		 	if strLine.find(PARSE_WORD) > -1:
		 		print 'add console listenOnTCP command.'
		 		strCont = strCont+'\n\t' + CONSOLE_COMMAND + '\n'
		 	strLine = file_object.readline() 
		
		file_object.close()
		file_object = open(filePath, 'w')
		file_object.write(strCont)
		file_object.close()
		time.sleep(2)
	else:
		print 'file is not exist.'

# get current android devices count.
def getAndroidDevices():
	cmd = 'adb devices'
	info_devices = os.popen(cmd).read()
	arrDevices = info_devices.split('\n')
	del arrDevices[0]
	count = 0
	for device in arrDevices:
		if len(device) > 0:
			count += 1
	return count

# close running app or exe by using console command.
IP_PHONE = {
	'mac':'localhost',
	'ios':'localhost'
}
PORT = 5678

def close_proj(proj, phone):
	print 'close running project'
	# connect socket
	if IP_PHONE.has_key(phone):
		soc = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
		print proj, phone, IP_PHONE[phone]
		try:
			soc.connect((IP_PHONE[phone], PORT))
			cmd = 'director end\r\n'
			print 'cmd close:', cmd
			soc.send(cmd)
		except Exception, e:
			print 'socket is not connect.'
	time.sleep(2)

# excute cocos command
def cocos_project(level):
	print 'will excute cocos_command: ', COCOS_CMD[level]
	for proj in project_types:
		print 'proj: ', proj
		if level == ENUM_PARAM.new:
			cmd = './'+cocos_console_dir+'cocos new -l '+proj+' '+proj+PROJ_SUFFIX
			print proj,'cmd:',cmd
			info_create = os.system(cmd)	#call cmd on win is diff
			if info_create == 0:
				time.sleep(12)
				addConsoleListenOnTCP(proj)
			print 'create project',proj,' is:', not info_create
		else:
			for phone in phonePlats:
				print 'platform is: ', phone
				cmd = './'+cocos_console_dir+'cocos '+COCOS_CMD[level]+' -s '+proj+PROJ_SUFFIX+' -p '+phone
				print 'cmd:',cmd
				if level == ENUM_PARAM.compile:
					if runSupport[curPlat][phone]:
						info_cmd = os.system(cmd)
						print 'info '+COCOS_CMD[level]+':', not info_cmd
				else :
					if runSupport[curPlat][phone]:
						if phone == 'android' and getAndroidDevices() == 0:
							print 'no android device, please checkout the device is running ok.'
							continue
						info_cmd = os.system(cmd)
						print 'info '+COCOS_CMD[level]+':', not info_cmd
						if level == ENUM_PARAM.run:
							time.sleep(20)
							close_proj(proj, phone)

# build and run according to params of provided.(lv_ignore: e.g:ignore new)
def build_run(lv_ignore):
	print 'will build and run'
	for level in LEVEL_COCOS:
		print 'level:', level, cocos_param, LEVEL_COCOS[level]
		if cocos_param >= LEVEL_COCOS[level] and level > lv_ignore:
			if level == ENUM_PARAM.new:
				clean_project()
			cocos_project(level)

# android simulator name.
ANDROID_SIMULATOR_NAME = 'console-test'
# start android simulator if no android devices connected.
def start_android_simulator():
	if getAndroidDevices() > 0:
		print 'already connected android device.'
		return
	if cocos_param >= LEVEL_COCOS[ENUM_PARAM.deploy]:
		cmd_start = [ 'emulator -avd '+ANDROID_SIMULATOR_NAME ]
		print 'cmd_start:', cmd_start
		info_start = subprocess.Popen(cmd_start, stdin=subprocess.PIPE, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		print 'start an android simulator:', not info_start

def main():
	print 'in main:'
	start_android_simulator()
	print 'will build_run:'
	build_run(-1)

# -------------- main --------------
if __name__ == '__main__':
    sys_ret = 0
    try:
    	sys_ret = main()
    except:
		traceback.print_exc()
		sys_ret = 1
    finally:
		sys.exit(sys_ret)
