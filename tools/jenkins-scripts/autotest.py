#!/usr/bin/python
import os
import sys
import subprocess
import socket
import time

HOST_MAC = 'localhost'
HOST_ANDROID = ''
HOST_IOS = '10.10.30.61'
PORT = 5678

suc_build_mac = 0
suc_build_android = 0

TYPE_MAC = 0
TYPE_ANDROID = 1
TYPE_IOS = 2

sleep_time = 1.5

#
def getADBDeviceIP():
	output = os.popen("adb shell netcfg")
	configs = output.read().split('\r\n')
	for l in configs:
		items = l.split()
		if(items[1] == 'UP'):
			if(items[2] != '127.0.0.1'):
				return items[2]

def autotest(type):
	soc = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
	if type == TYPE_MAC:
		soc.connect((HOST_MAC, PORT))
	if type == TYPE_ANDROID:
		HOST_ANDROID = getADBDeviceIP()
		soc.connect((HOST_ANDROID, PORT))
	if type == TYPE_IOS:
		soc.connect((HOST_IOS, PORT))
	time.sleep(1)
	print 'autotest run:'
	soc.send('autotest run\r\n')

	while True:
		data = soc.recv(1024)
		print data
		if data == 'TestEnd':
			lastTestInfo = True
			break
		global lastTestInfo
		if len(data) > len('\n') :
			lastTestInfo = data
		if not data: break
	
	soc.send('director end\r\n')
	print 'test end and close socket.'
	soc.close()

#----------------autotest build and run----------------#
def MAC_BUILD():
	def cleanProj():
		infoClean = os.system('xcodebuild -project ./build/cocos2d_tests.xcodeproj -target cpp-tests\ Mac clean')
		print 'infoClean: ', infoClean
		if infoClean != 0:
			return False
		time.sleep(sleep_time)
		return True
	def buildProj():
		infoBuild = os.system('xcodebuild -project ./build/cocos2d_tests.xcodeproj -target cpp-tests\ Mac')
		print 'infoBuild: ', infoBuild
		if infoBuild != 0:
			return False
		time.sleep(sleep_time)
		return True
	def openProj():
		cmd = 'open ./build/build/Debug/cpp-tests\ Mac.app'
		print 'cmd: ', cmd
		infoOpen = os.system(cmd)
		print 'infoOpen: ', infoOpen
		if infoOpen != 0:
			return False
		time.sleep(sleep_time)
		return True
	def buildAndRun():
		if not cleanProj():
			print '**CLEAN FAILED**'
		if not buildProj():
			print '**BUILD FAILED**'
			return False
		if not openProj():
			return False
		time.sleep(sleep_time)
		return True
	return buildAndRun()
#----------------autotest build and run end----------------#

PATH_ANDROID_SRC = 'tests/cpp-tests/proj.android/'
FILE_ANDROID_DELETE = ['libs','gen','assets','bin','obj']
#----------------autotest-android build and run----------------#
def ANDROID_BUILD():
	def checkDevice():
		cmd = 'adb devices'
		infoDev = os.popen(cmd).readlines()
		firstDev = infoDev[1]
		if len(firstDev) < 5 or firstDev.find('device') < 0:
			print 'no android device.'
			return False
		else:
			print 'device info:', firstDev
		return True
	def cleanProj():
		for strFile in FILE_ANDROID_DELETE:
			infoClean = os.system('rm -rf '+PATH_ANDROID_SRC+strFile)
		infoClean = os.system('adb uninstall org.cocos2dx.cpp_tests');
		print 'infoClean: ', infoClean
		if infoClean != 0:
			print 'clean **CLEAN FAILED**'
		time.sleep(sleep_time)
	def updateProperty():
		infoUpdate = os.system('android update project -p  ./cocos/platform/android/java/ -t 12')
		print 'cocos update:', infoUpdate
		infoUpdate = os.system('android update project -p '+PATH_ANDROID_SRC+' -t 12')
		print 'test update:', infoUpdate
	def buildProj():
		infoBuild = os.system('./build/android-build.py  -p 13 cpp-tests')
		print 'infoBuild cpp_tests: ', infoBuild
		infoBuild = os.system('ant -buildfile '+PATH_ANDROID_SRC+' debug')
		print 'infoBuild: ', infoBuild
		if infoBuild != 0:
			print 'build **BUILD FAILED**'
		time.sleep(sleep_time)
		return infoBuild
	def installProj():
		cmd = 'adb install '+PATH_ANDROID_SRC+'bin/CppTests-debug.apk'
		infoInstall = os.system(cmd)
		print 'infoInstall:', infoInstall
		if infoInstall != 0:
			print 'install **INSTALL FAILED**'
		return infoInstall
	def openProj():
		cmd = 'adb shell am start -n org.cocos2dx.cpp_tests/org.cocos2dx.cpp_tests.Cocos2dxActivity'
		print 'cmd: ', cmd
		infoOpen = os.system(cmd)
		print 'infoOpen: ', infoOpen
		if infoOpen != 0:
			return False
		time.sleep(sleep_time)
		return True
	def buildAndRun():
		if not checkDevice():
			return False
		cleanProj()
		updateProperty()
		buildProj()
		installProj()
		return openProj()
	return buildAndRun()
#----------------autotest-android build and run end----------------#

def main():
	print 'will build mac project.'
	suc_build_mac = MAC_BUILD()
	# print 'will build android project.'
	# suc_build_android = ANDROID_BUILD()
	if suc_build_mac:
		autotest(TYPE_MAC)
	if suc_build_android:
		print 'will run android autotest.'
		autotest(TYPE_ANDROID)


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

