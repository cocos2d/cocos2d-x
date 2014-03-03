import os
import sys
import subprocess
import socket
import time

HOST = 'localhost'
PORT = 5678

def autotest():
	soc = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
	soc.connect((HOST, PORT))
	time.sleep(3)
	print 'autotest run:'
	soc.send('autotest run\r\n')

	while True:
		buf = soc.recv(64)
		print buf
	
	print 'test end and close socket.'
	soc.close()

#----------------autotest build and run----------------#
sleep_time = 1.5
def cleanProj():
	infoClean = os.system('xcodebuild -project ./build/cocos2d_tests.xcodeproj -target Test\ cpp\ Mac clean')
	print 'infoClean: ', infoClean
	if infoClean != 0:
		print 'clean **CLEAN FAILED**'
	time.sleep(sleep_time)
def buildProj():
	infoBuild = os.system('xcodebuild -project ./build/cocos2d_tests.xcodeproj -target Test\ cpp\ Mac')
	print 'infoBuild: ', infoBuild
	if infoBuild != 0:
		print 'build **BUILD FAILED**'
	time.sleep(sleep_time)
	return infoBuild
def openProj():
	cmd = 'open ./build/build/Debug/Test\ cpp\ Mac.app'
	print 'cmd: ', cmd
	infoOpen = os.system(cmd)
	print 'infoOpen: ', infoOpen
	if infoOpen != 0:
		print 'open **OPEN FAILED**'
	time.sleep(sleep_time)
def buildAndRun():
	# cleanProj()
	if buildProj() != 0:
		cleanProj()
		buildProj()
	openProj()
	time.sleep(sleep_time)
#----------------autotest build and run end----------------#

def main():
	try:
		buildAndRun()
	except Exception, e:
		print 'BUILD FAILED!'
	else:
		autotest()


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

