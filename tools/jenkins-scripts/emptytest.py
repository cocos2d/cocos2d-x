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

payload = {}
#get payload from os env
if os.environ.has_key('payload'):
	payload_str = os.environ['payload']
	#parse to json obj
	global payload
	payload = json.loads(payload_str)
print 'payload:',payload
pr_num = 1
#get pull number
if payload.has_key('issue'):
	issue = payload['issue']
	if issue.has_key('number'):
		pr_num = issue['number']
print 'pr_num:' + str(pr_num)

arrDevices = []
def getDevices():
	cmd = 'adb devices'
	info_devices = os.popen(cmd).read()
	arr_info = info_devices.split('\n')
	del arr_info[0]
	count = 0
	for device in arr_info:
		if len(device) > 0:
			count += 1
			print 'device ', count,device
			deviceInfo = device.split('	')
			global arrDevices
			arrDevices.append(deviceInfo[0])
	return count

apk_name = 'cppProj-debug-unaligned.apk'
info_empty_test = {}
def install_apk():
	print 'in install_apk'
	if len(arrDevices) == 0:
		print 'no android\'s device'
		return False
	info_of_install = []
	for device in arrDevices:
		print 'device:', device
		cmd = 'adb -s '+device+' install '+str(pr_num)+'/'+apk_name
		print 'install on '+device,':', cmd
		info_install = os.popen(cmd).read()
		print 'info_install:', info_install
		info_of_install.append(info_install.split('\r\n'))
	info_empty_test['install'] = info_of_install
	return True

# TYPE_NAME = ['cpp-empty', 'lua-empty', 'cpp-test', 'lua-test']
TYPE_NAME = 'cpp-empty'
package_name = {
	'cpp-empty':'org.cocos2dx.hellocpp'
}
activity_name = {
	'cpp-empty':'org.cocos2dx.cpp.AppActivity'
}

def open_apk(type_of_apk):
	print 'in open_apk111:'
	for device in arrDevices:
		cmd = 'adb -s '+device+' shell am start -n '+package_name[type_of_apk]+'/'+activity_name[type_of_apk]
		print 'start activity:', cmd
		info_start = os.popen(cmd).read()
		info_start = info_start.split('\n')
		print 'info_start:', info_start
		for info in info_start:
			if info.find('Error:') > -1:
				print info
				return info
	return True

IP_PHONE = '10.10.40.64'
if os.environ.has_key('IP_LIST'):
	global IP_PHONE
	IP_PHONE = os.environ('IP_LIST')
	IP_PHONE = IP_PHONE.split(', ')
PORT = 5678
def socket_status():
	soc = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
	try:
		print 'will connect socket:'
		soc.connect((IP_PHONE, PORT))
		cmd = 'director -h\r\n'
		print 'cmd director:', cmd
		soc.send(cmd)
		while True:
			data = soc.recv(1024)
			print data
			if len(data):
				return True
	except Exception, e:
		print 'socket is not connect.'
		return False

def uninstall_apk(apk_name):
	# adb shell pm uninstall -n org.cocos2dx.hellolua
	cmd = 'adb shell pm uninstall -n '+package_name[apk_name]
	info_uninstall = os.system(cmd)
	print 'info_uninstall:',info_uninstall
	return True

def main():
	print 'in main:'
	getDevices()
	print 'arrDevices:',arrDevices
	install_info = install_apk()
	open_info = open_apk(TYPE_NAME)
	print 'open_info:', open_info
	info_empty_test['open_info'] = open_info
	if open_info:
		time.sleep(5)
		socket_info = socket_status()
		info_empty_test['socket_info'] = socket_info
		print 'socket_info:', socket_info
		if not socket_info:
			print 'app run is not correct'
	if install_info:
		time.sleep(5)
		uninstall_apk(TYPE_NAME)
	print 'info_empty_test:', info_empty_test
	print 'end run_step.'

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
