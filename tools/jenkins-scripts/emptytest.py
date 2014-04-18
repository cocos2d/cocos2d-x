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
	payload = json.loads(payload_str)
print 'payload:',payload
pr_num = 1
#get pull number
if payload.has_key('number'):
	pr_num = payload['number']
print 'pr_num:' + str(pr_num)

test_name = ['cpp_empty_test']
if os.environ.has_key('TESTS_NAME'):
	temp_var = os.environ['TESTS_NAME']
	test_name = temp_var.split(', ')
package_name = ['org.cocos2dx.hellocpp']
if os.environ.has_key('PACKAGE_NAME'):
	temp_var = os.environ['PACKAGE_NAME']
	package_name = temp_var.split(', ')
activity_name = ['org.cocos2dx.cpp.AppActivity']
if os.environ.has_key('ACTIVITY_NAME'):
	temp_var = os.environ['ACTIVITY_NAME']
	activity_name = temp_var.split(', ')
gIdx = 0
if os.environ.has_key('TEST_INDEX'):
	gIdx = os.environ('TEST_INDEX')

empty_test_result = True
empty_test_result_info = ''
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
apk_name = 'apks/'+test_name[gIdx]+'/'+test_name[gIdx]+'_'+str(pr_num)+'.apk'
def install_apk():
	print 'will install apk:', apk_name
	if len(arrDevices) == 0:
		empty_test_result = False
		empty_test_result_info = 'no android device.'
		print empty_test_result_info
		return False
	info_of_install = []
	if not os.path.isfile(apk_name):
		print apk_name, 'is not exist!'
		empty_test_result = False
		return False
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
				empty_test_result = False
				empty_test_result_info = 'open :'+info
				return info
	if len(arrDevices):
		print 'activity is opened.'
	else:
		print 'no device.'
	return True

PORT = 5678
def socket_status(device_name):
	soc = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
	status_socket = False
	try:
		print 'telnet ', device_name['ip'], PORT
		soc.connect((device_name['ip'], PORT))
		cmd = 'resolution\r\n'
		# print 'socket cmd :', cmd
		print 'connected successfully.'
		print 'send console command: resolution'
		soc.send(cmd)
		while True:
			data = soc.recv(1024)
			if len(data):
				print data
				if data.find('size:') > -1:
					print 'OK'
					print 'close', test_name[gIdx]
					soc.send('director end')
					print 'OK'
					status_socket = True
					break
			if not data:
				empty_test_result = False
				empty_test_result_info = test_name[gIdx]+' is crashed!'
				print empty_test_result_info
				break
	except Exception, e:
		empty_test_result = False
		empty_test_result_info = test_name[gIdx]+' is crashed!'
		print empty_test_result_info
	time.sleep(2)
	soc.close()
	return status_socket

def uninstall_apk(idx):
	# adb shell pm uninstall -n org.cocos2dx.hellolua
	print 'uninstall ', test_name[idx]
	for device in arrDevices:
		cmd = 'adb -s '+device['name']+' shell pm uninstall -n '+package_name[idx]
		info_uninstall = os.popen(cmd).read()
		if info_uninstall.find('Success') > -1:
			print 'OK'
		else:
			empty_test_result = False
			empty_test_result_info = 'uninstall Failed!'
			print empty_test_result_info
	return True

def wakeup_device(idx):
	file_wakeup = 'wakeup.py'
	if not os.path.isfile(file_wakeup):
		print file_wakeup, 'is not file_wakeup'
		return False
	info_wake = os.popen('monkeyrunner '+file_wakeup).read()
	print 'info_wake:', info_wake

def main():
	print 'in main:'
	getDevices()
	if len(arrDevices):
		wakeup_device(gIdx)
		time.sleep(2)
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
	print 'empty test end', empty_test_result
	if empty_test_result:
		return 0
	else:
		print 'empty_test_result_info:', empty_test_result_info
		return 1

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
