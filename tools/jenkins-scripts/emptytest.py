#!/usr/bin/python
# create new project by cocos-console
# compile, deploy project and run
# perpose: for emptytest.
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

test_name = ['cpp_empty_test']
if os.environ.has_key('TESTS_NAME'):
	temp_var = os.environ('TESTS_NAME')
	test_name = temp_var.split(', ')
package_name = ['org.cocos2dx.hellocpp']
if os.environ.has_key('PACKAGE_NAME'):
	temp_var = os.environ('PACKAGE_NAME')
	package_name = temp_var.split(', ')
activity_name = ['org.cocos2dx.cpp.AppActivity']
if os.environ.has_key('ACTIVITY_NAME'):
	temp_var = os.environ('ACTIVITY_NAME')
	activity_name = temp_var.split(', ')
gIdx = 0
if os.environ.has_key('TEST_INDEX'):
	gIdx = os.environ('TEST_INDEX')

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
			obj = {}
			obj['name']  = deviceInfo[0]
			arrDevices.append(obj)
	return count

def getADBDeviceIP(device_name):
	output = os.popen("adb -s "+device_name+" shell netcfg")
	configs = output.read().split('\r\n')
	for l in configs:
		items = l.split()
		if len(items)>1 and items[1] == 'UP':
			if items[2].find('127.0.0.1') < 0 and items[2].find('0.0.0.0') < 0:
				return items[2]
	return False
def mapIP():
	for device in arrDevices:
		ip_d = getADBDeviceIP(device['name'])
		if ip_d:
			ip_d = ip_d.replace('.30.', '.40.')
		device['ip'] = ip_d

info_empty_test = {}
apk_name = test_name[gIdx]+'_'+str(pr_num)+'.apk'
def install_apk():
	print 'will install apk:', apk_name
	if len(arrDevices) == 0:
		print 'no android device.'
		return False
	info_of_install = []
	for device in arrDevices:
		name = device['name']
		cmd = 'adb -s '+name+' install '+apk_name
		print 'install on '+name
		info_install = os.popen(cmd).read()
		print 'infomation of install apk:', info_install
		info_of_install.append(info_install.split('\r\n'))
	info_empty_test['install'] = info_of_install
	return True

def open_apk(type_of_apk):
	print 'will open activity:'
	for device in arrDevices:
		cmd = 'adb -s '+device['name']+' shell am start -n '+package_name[gIdx]+'/'+activity_name[gIdx]
		# print 'start activity:', cmd
		info_start = os.popen(cmd).read()
		info_start = info_start.split('\n')
		# print 'info_start:', info_start
		for info in info_start:
			if info.find('Error:') > -1:
				print 'infomation of open activity:',info
				return info
	print 'activity is opened.'
	return True

PORT = 5678
def socket_status(device_name):
	soc = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
	try:
		print 'will check status of app:', device_name
		soc.connect((device_name['ip'], PORT))
		cmd = 'resolution\r\n'
		# print 'socket cmd :', cmd
		soc.send(cmd)
		while True:
			data = soc.recv(1024)
			if len(data):
				print data
				if data.find('size:') > -1:
					print test_name[gIdx]+' is successful!'
					return True
			if not data:
				print test_name[gIdx]+' is crashed!'
				break
	except Exception, e:
		print test_name[gIdx]+' is crashed!'
		return False

def uninstall_apk(idx):
	# adb shell pm uninstall -n org.cocos2dx.hellolua
	print 'will uninstall apk:', package_name[idx]
	for device in arrDevices:
		cmd = 'adb -s '+device['name']+' shell pm uninstall -n '+package_name[idx]
		info_uninstall = os.popen(cmd).read()
		print 'uninstall apk:', info_uninstall
	return True

def main():
	print 'in main:'
	getDevices()
	if len(arrDevices):
		mapIP()
		print 'arrDevices:',arrDevices
	print 'empty test start:'
	install_info = install_apk()
	open_info = open_apk(test_name[gIdx])
	info_empty_test['open_info'] = open_info
	if open_info:
		time.sleep(5)
		socket_info = socket_status(arrDevices[0])
		info_empty_test['socket_info'] = socket_info
	if install_info:
		time.sleep(5)
		info_uninstall = uninstall_apk(gIdx)
	print 'info_empty_test:', info_empty_test
	print 'empty test end'

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
