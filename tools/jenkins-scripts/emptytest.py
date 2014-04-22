#!/usr/bin/python
# create new project by cocos-console
# compile, deploy project and run
# perpose: for emptytest.
# now support: mac- mac/ios/android
# will add: window-android,linux-android

import os
import sys
import json
import time
import socket
import platform

payload = {}
#get payload from os env
if os.environ.has_key('payload'):
	payload_str = os.environ['payload']
	#parse to json obj
	payload = json.loads(payload_str)
print 'payload:',payload
pr_num = 6326
#get pull number
if payload.has_key('number'):
	pr_num = payload['number']
print 'pr_num:' + str(pr_num)
run_app_time = 5
if os.environ.has_key('RUN_APP_TIME'):
	global run_app_time
	run_app_time = os.environ['RUN_APP_TIME']
print 'run_app_time:', run_app_time

test_name = ['cpp_empty_test']
if os.environ.has_key('TESTS_NAME'):
	temp_var = os.environ['TESTS_NAME']
	test_name = temp_var.split(', ')
package_name = ['org.cocos2dx.cpp_empty_test']
if os.environ.has_key('PACKAGE_NAME'):
	temp_var = os.environ['PACKAGE_NAME']
	package_name = temp_var.split(', ')
activity_name = ['org.cocos2dx.cpp_empty_test.AppActivity']
if os.environ.has_key('ACTIVITY_NAME'):
	temp_var = os.environ['ACTIVITY_NAME']
	activity_name = temp_var.split(', ')
gIdx = 0
if os.environ.has_key('TEST_INDEX'):
	gIdx = os.environ('TEST_INDEX')

current_platform = platform.system()
print 'current platform is:', current_platform

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
	output.close()
	for l in configs:
		items = l.split()
		if len(items)>1 and items[1] == 'UP':
			if items[2].find('127.0.0.1') < 0 and items[2].find('0.0.0.0') < 0:
				return items[2]
	return False
def mapIP():
	for device in arrDevices:
		ip_d = getADBDeviceIP(device['name'])
		device['ip'] = ip_d

device_info = {}
info_list = '{"product":["model","brand","name","cpu.abi","cpu.abi2","manufacturer","locale.language","locale.region"],"build":["id","version.sdk","version.release"]}'
if os.environ.has_key('DEVICE_INFO_LIST'):
	info_list = os.environ['DEVICE_INFO_LIST']
info_list = eval(info_list)
def getDeviceInfoByName(name):
	cmd = ''
	if len(name) > 0:
		cmd = 'adb -s '+name+' shell cat /system/build.prop'
	else:
		cmd = 'adb shell cat /system/build.prop'
	pip_cat = os.popen(cmd)
	read_info = pip_cat.read()
	read_info_list = read_info.split('\r\n')
	def checkProperty(item_str):
		for argv in info_list:
			for item in info_list[argv]:
				prop = argv+'.'+item
				if item_str.find(prop) > -1:
					arr_item = item_str.split('=')
					device_info[prop] = arr_item[1]
					break
	for item in read_info_list:
		checkProperty(item)

#getDeviceInfoByName('')
#print 'device_info:',device_info
def logDeviceInfomation():
    getDeviceInfoByName('')
    for key in device_info:
        print '\t'+key+':'+device_info[key]

info_empty_test = {}
apk_name = 'apks/'+test_name[gIdx]+'/'+test_name[gIdx]+'_'+str(pr_num)+'.apk'
def install_apk():
	print 'will install apk:', apk_name
	global empty_test_result
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
				global empty_test_result
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
	global empty_test_result
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
			empty_test_result_info = 'uninstall Failed!'
			print empty_test_result_info
	return True

def main():
	print 'in main:'
	getDevices()
	if len(arrDevices):
		mapIP()
		print 'arrDevices:',arrDevices
		uninstall_apk(gIdx)
		time.sleep(1)
	else:
		print 'there is no device for emptytest, please check devices!'
		return 1
	print 'empty test start:'
	print 'device infomation:'
	if len(arrDevices):
		logDeviceInfomation()
	else:
		print '\tno android device.'
	install_info = install_apk()
	open_info = open_apk(test_name[gIdx])
	info_empty_test['open_info'] = open_info
	if open_info:
		time.sleep(5)
		socket_info = socket_status(arrDevices[0])
		info_empty_test['socket_info'] = socket_info
	if install_info:
		time.sleep(run_app_time)
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
