#!/usr/bin/python
#create new project by cocos-console
#build new project and run

import os
import sys
import json
import time
import socket

# get payload argvs
console_param = '[console run]'
# payload = ''
if os.environ.has_key('payload'):
	payload_str = os.environ['payload']
	payload = json.loads(payload_str)
	if payload.has_key('console'):
		console_param = payload['console']
console_param = console_param[1:len(console_param)-1]
print 'console_param:',console_param

console_param_arr = console_param.split(' ')

class ENUM_PARAM:
	new = 0
	compile = 1
	deploy = 2
	run = 3

LEVEL_COCOS = {
	ENUM_PARAM.new : 1,
	ENUM_PARAM.compile : 2,
	ENUM_PARAM.deploy : 4,
	ENUM_PARAM.run : 8
}

COCOS_CMD = {
	ENUM_PARAM.new:'new',
	ENUM_PARAM.compile:'compile',
	ENUM_PARAM.deploy:'deploy',
	ENUM_PARAM.run:'run'
}

cocos_param = 0
for level in LEVEL_COCOS:
	if console_param_arr.count(COCOS_CMD[level]):
		cocos_param = cocos_param + LEVEL_COCOS[level]
if cocos_param < LEVEL_COCOS[ENUM_PARAM.new]:
	cocos_param = LEVEL_COCOS[ENUM_PARAM.new]
print 'cocos_param:', cocos_param
project_types = ['cpp', 'lua']
PROJ_SUFFIX = 'Proj'
phonePlats = ['mac','ios','android']

#need use console's position, perhaps should be set an env-param
cocos_console_dir = 'tools/cocos2d-console/bin/'

#now cocos2d-console suport different run on Platforms, e.g: only run android on win
runSupport = {
	'darwin' : {'mac':1,'ios':1,'android':0},
	'win' : {'mac':0,'ios':0,'android':0},
	'linux' : {'mac':0,'ios':0,'android':0}
}

curPlat = sys.platform
if curPlat.find('linux') >= 0:
	curPlat = 'linux'
elif curPlat.find('darwin') >= 0:
	curPlat = 'darwin'
else:
	curPlat = 'win'
print 'current platform is:', curPlat

def clean_project():
	for proj in project_types:
		cmd = 'rm -rf '+proj+PROJ_SUFFIX
		os.system(cmd)

FILE_PATH = '/Classes/AppDelegate.cpp'
FILE_DIR = {
	'cpp':'',
	'lua':'/frameworks/runtime-src'
}
PARSE_WORD = 'director->setDisplayStats(true);'
CONSOLE_COMMAND = 'director->getConsole()->listenOnTCP(5678);'

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

def cocos_project(level):
	print 'will cocos_project: ', level
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
						info_cmd = os.system(cmd)
						print 'info '+COCOS_CMD[level]+':', not info_cmd
						if level == ENUM_PARAM.run:
							time.sleep(10)
							close_proj(proj, phone)

def build_run(lv_ignore):
	print 'will build and run'
	for level in LEVEL_COCOS:
		print 'level:', level, cocos_param, LEVEL_COCOS[level]
		if cocos_param >= LEVEL_COCOS[level] and level > lv_ignore:
			if level == ENUM_PARAM.new:
				clean_project()
			cocos_project(level)

def main():
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
