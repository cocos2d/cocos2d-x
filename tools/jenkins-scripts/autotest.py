import os
import sys
import subprocess
import socket
import time

HOST_MAC = 'localhost'
HOST_ADNROID = '10.10.30.64'
HOST_IOS = '10.10.30.61'
PORT = 5678

suc_build_mac = 0
suc_build_android = 0

TYPE_MAC = 0
TYPE_ANDROID = 1
TYPE_IOS = 2

sleep_time = 1.5
def autotest(type):
	soc = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
	if type == TYPE_MAC:
		soc.connect((HOST_MAC, PORT))
	if type == TYPE_ANDROID:
		soc.connect((HOST_ADNROID, PORT))
	if type == TYPE_IOS:
		soc.connect((HOST_IOS, PORT))
	time.sleep(3)
	print 'autotest run:'
	soc.send('autotest run\r\n')

	while True:
		buf = soc.recv(64)
		print buf
	
	print 'test end and close socket.'
	soc.close()

#----------------autotest build and run----------------#
def MAC_BUILD():
	def cleanProj():
		infoClean = os.system('xcodebuild -project ./build/cocos2d_tests.xcodeproj -target Test\ cpp\ Mac clean')
		print 'infoClean: ', infoClean
		if infoClean != 0:
			return False
		time.sleep(sleep_time)
		return True
	def buildProj():
		infoBuild = os.system('xcodebuild -project ./build/cocos2d_tests.xcodeproj -target Test\ cpp\ Mac')
		print 'infoBuild: ', infoBuild
		if infoBuild != 0:
			return False
		time.sleep(sleep_time)
		return True
	def openProj():
		cmd = 'open ./build/build/Debug/Test\ cpp\ Mac.app'
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
			cleanProj()
			buildProj()
		if not openProj():
			return False
		time.sleep(sleep_time)
		return True
	return buildAndRun()
#----------------autotest build and run end----------------#

#----------------autotest-android build and run----------------#
def ANDROID_BUILD():
	def cleanProj():
		infoClean = os.system('rm -rf libs gen obj assets bin')
		print 'infoClean: ', infoClean
		infoClean = os.system('adb uninstall org.cocos2dx.testcpp');
		print 'infoClean: ', infoClean
		if infoClean != 0:
			print 'clean **CLEAN FAILED**'
		time.sleep(sleep_time)
	def updateProperty():
		infoUpdate = os.system('android update project -p  ./cocos/2d/platform/android/java/ -t 12')
		print 'cocos update:', infoUpdate
		infoUpdate = os.system('android update project -p ./tests/proj.android/ -t 12')
		print 'test update:', infoUpdate
	def buildProj():
		infoBuild = os.system('./build/android-build.py testcpp')
		print 'infoBuild testcpp: ', infoBuild
		infoBuild = os.system('ant -buildfile ./tests/proj.android/ debug install')
		print 'infoBuild: ', infoBuild
		if infoBuild != 0:
			print 'build **BUILD FAILED**'
		time.sleep(sleep_time)
		return infoBuild
	def openProj():
		cmd = 'adb shell am start -n org.cocos2dx.testcpp/org.cocos2dx.testcpp.Cocos2dxActivity'
		print 'cmd: ', cmd
		infoOpen = os.system(cmd)
		print 'infoOpen: ', infoOpen
		if infoOpen != 0:
			return False
		time.sleep(sleep_time)
		return True
	def buildAndRun():
		cleanProj()
		updateProperty()
		if buildProj() != 0:
			cleanProj()
			buildProj()
		return openProj()
	return buildAndRun()
#----------------autotest-android build and run end----------------#

def main():
	suc_build_mac = MAC_BUILD()
	suc_build_android = ANDROID_BUILD()
	if suc_build_mac:
		autotest(TYPE_MAC)
	if suc_build_android:
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

