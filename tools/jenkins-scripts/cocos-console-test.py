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
import threading
import smtplib
from email.mime.text import MIMEText
from os.path import join, getsize

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
	print 'delete older project.'
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

# console result, for record result
console_result = 'the result of cocos-console-test is:\n\r'

# get current android devices count.
def getAndroidDevices():
	cmd = 'adb devices'
	info_devices = os.popen(cmd).read()
	arrDevices = info_devices.split('\n')
	del arrDevices[0]
	count = 0
	for device in arrDevices:
		# e.g: emulator-5554	device, contains 'device', so, min length is len('device')
		if len(device) > len('device') and (device.find('device') >= 0):
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
	strClose = 'close ' + proj + ' on ' + phone
	if IP_PHONE.has_key(phone):
		soc = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
		print proj, phone, IP_PHONE[phone]
		try:
			soc.connect((IP_PHONE[phone], PORT))
			cmd = 'director end\r\n'
			print 'cmd close:', cmd
			soc.send(cmd)
			time.sleep(2) 
			strClose = strClose + ' success.'
		except Exception, e:
			print 'socket is not connect.'
			strClose = strClose + ' failed.' + ' socket is not connect.'
	else:
		strClose = strClose + ' failed.' + ' no ' +phone+ ' type.'
	time.sleep(2)
	return strClose

# appendToResult
def appendToResult(content):
	global console_result
	console_result = console_result + content

info_of_close_app = {}
cur_test_name = ''
class myThread(threading.Thread):
    def __init__(self,threadname):
        threading.Thread.__init__(self,name=threadname)
    def run(self):
        run_name = self.getName()
        print 'run_name:', run_name
        if run_name == 'close':
        	while True:
        		soc = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
        		try:
        			soc.connect(('localhost', PORT))
        			cmd_close = 'director end\r\n'
        			print 'cmd close:', cmd_close
        			soc.send(cmd_close)
        			time.sleep(2)
        			global cur_test_name
        			print 'cur_test_name:', cur_test_name
        			info_of_close_app[cur_test_name] = True
        			break
        		except Exception, e:
					time.sleep(5)

# if any error 
ANY_ERROR_IN_RUN = 0
# excute cocos command
def cocos_project(level):
	global ANY_ERROR_IN_RUN
	print 'will excute cocos_command: ', COCOS_CMD[level], level
	appendToResult('will excute ' + COCOS_CMD[level] + ' command:'+"\n\r\t")
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
			ANY_ERROR_IN_RUN = ANY_ERROR_IN_RUN + info_create
			appendToResult('	'+cmd +': ' + str(not info_create) + ".\n\r\t")
		else:
			for phone in phonePlats:
				print 'platform is: ', phone
				cmd = './'+cocos_console_dir+'cocos '+COCOS_CMD[level]+' -s '+proj+PROJ_SUFFIX+' -p '+phone
				print 'cmd:',cmd
				info_cmd = ''
				if level == ENUM_PARAM.compile:
					if runSupport[curPlat][phone]:
						info_cmd = os.system(cmd)
						print 'info '+COCOS_CMD[level]+':', not info_cmd
						appendToResult('	'+cmd +': ' + str(not info_cmd) + ".\n\r\t")
				else:
					if runSupport[curPlat][phone]:
						print 'in desploy or run:', phone, getAndroidDevices()
						if phone == 'android' and getAndroidDevices() == 0:
							strInfo = 'no android device, please checkout the device is running ok.'
							print strInfo
						else:
							if level == ENUM_PARAM.run:
								global cur_test_name
								cur_test_name = proj+','+phone
								thread_close = myThread('close')
								thread_close.start()
							info_cmd = os.system(cmd)
							time.sleep(5)
							appendToResult('	'+cmd +': ' + str(not info_cmd) + ".\n\r\t")

# build and run according to params of provided.(lv_ignore: e.g:ignore new)
def build_run(lv_ignore):
	print 'will build and run, in function build_run'
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
	print 'in function start_android_simulator.'
	if getAndroidDevices() > 0:
		print 'already connected android device.'
		return
	if cocos_param >= LEVEL_COCOS[ENUM_PARAM.deploy]:
		cmd_start = [ 'emulator -avd '+ANDROID_SIMULATOR_NAME ]
		# print 'cmd_start:', cmd_start
		# info_start = subprocess.Popen(cmd_start, stdin=subprocess.PIPE, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		# print 'start an android simulator:', not info_start

# send email
EMAIL_KEYS={
	0:'EMAIL_HOST',
	1:'EMAIL_USER',
	2:'EMAIL_PWD',
	3:'EMAIL_POSTFIX',
	4:'EMAIL_LIST',
	5:'NEED_SEND_EMAIL'
}

OBJ_EMAIL_INFO = {}
print 'will get env info.'
for key in EMAIL_KEYS:
	if os.environ.has_key(EMAIL_KEYS[key]):
		OBJ_EMAIL_INFO[EMAIL_KEYS[key]] = os.environ[EMAIL_KEYS[key]]
		if key == 4:
			# string to list by ' ', for separate users.
			OBJ_EMAIL_INFO[EMAIL_KEYS[4]] = OBJ_EMAIL_INFO[EMAIL_KEYS[4]].split(' ')

print 'will send email.', OBJ_EMAIL_INFO
def send_mail(to_list,sub,title,content):
	mail_user = OBJ_EMAIL_INFO[ EMAIL_KEYS[1] ]
	mail_postfix = OBJ_EMAIL_INFO[ EMAIL_KEYS[3] ]
	mail_host = OBJ_EMAIL_INFO[ EMAIL_KEYS[0] ]
	mail_pass = OBJ_EMAIL_INFO[ EMAIL_KEYS[2] ]
	me = mail_user+"<"+mail_user+"@"+mail_postfix+">"
	msg = MIMEText(content,_subtype='plain',_charset='gb2312')
	msg['Subject'] = sub
	msg['From'] = me
	msg['To'] = " ".join(to_list)
	print 'to users:', msg['To']
	msg['Content'] = 'test'
	try:
		s = smtplib.SMTP()
		s.connect(mail_host)
		s.login(mail_user,mail_pass)
		s.sendmail(me, to_list, str(msg))
		print 'info:', me, to_list, str(msg)
		s.close()
		appendToResult( 'send email true:' + str(msg) )
		return True
	except Exception, e:
		appendToResult( 'send email false:' + str(e) )
        print str(e)
        return False

def sendEmail(msg):
	send_mail(OBJ_EMAIL_INFO[EMAIL_KEYS[4]], "cocos-console-test result", 'for error.', msg)

# get package size 
def getdirsize(dir):  
	size = 0L  
	for root, dirs, files in os.walk(dir):  
		size += sum([getsize(join(root, name)) for name in files])  
	return size
APP_FILE_DIR = {
	'cpp':'bin/debug/',
	'lua':'runtime/'
}
APP_FILE_SUFFIX = {
	'mac':'.app',
	'ios':'.app',
	'android':'-debug-unaligned.apk'
}
if os.environ.has_key('APP_FILE_SUFFIX'):
	str_app_suffix = os.environ['APP_FILE_SUFFIX']
	APP_FILE_SUFFIX = eval(str_app_suffix)

def getPackageSize():
	for proj in project_types:
		for phone in phonePlats:
			# if runSupport[curPlat][phone]:
			package_path = './'+proj+PROJ_SUFFIX+'/'+APP_FILE_DIR[proj]+phone+'/'+proj+PROJ_SUFFIX+APP_FILE_SUFFIX[phone]
			print 'package_path', package_path
			package_size = 0
			if os.path.isfile(package_path):
				package_size = os.path.getsize(package_path);
			else:
				package_size = getdirsize(package_path);
			strSize = 'size of '+proj+PROJ_SUFFIX+' '+phone+' is:'+str(package_size/(1024))+'KB'+'\n\t'
			print 'strSize:', strSize
			appendToResult(strSize)

def main():
	print 'in main:'
	# start_android_simulator()
	print 'will build_run:'
	build_run(-1)
	print 'ANY_ERROR_IN_RUN:', ANY_ERROR_IN_RUN
	print 'end build run. and get package size.'
	getPackageSize()
	print 'will send email:'
	print 'console_result:', console_result
	if OBJ_EMAIL_INFO[ EMAIL_KEYS[5] ] or ANY_ERROR_IN_RUN:
		sendEmail(console_result)

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
