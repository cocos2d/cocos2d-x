#!/usr/bin/python
#create new project by cocos-console
#build new project and run

import os
import sys
import json
import time

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

project_types = ['cpp', 'lua']
PROJ_SUFFIX = 'Proj'
phonePlats = ['mac','ios','android']

#need use console's position, perhaps should be set an env-param
cocos_console_dir = 'tools/cocos2d-console/bin/'

#now cocos2d-console suport different run on Platforms, e.g: only run android on win
runSupport = {
	'darwin' : [1, 1, 0],
	'win' : [0, 0, 1],
	'linux' : [0, 0, 1]
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

def create_project():
	print 'will create_project: '
	for proj in project_types:
		print 'proj: ', proj
		cmd = './'+cocos_console_dir+'cocos new -l '+proj+' '+proj+PROJ_SUFFIX
		print proj,'cmd:',cmd
		info_create = os.system(cmd)	#call cmd on win is diff
		print 'create project',proj,' is:', not info_create

def getAppPID(name):
	cmd = 'ps -eo pid,comm | grep '+name
	output = os.popen(cmd)
	result = output.read()
	arrProcess = result.split('\n')
	print 'arrProcess:', arrProcess
	def getProcessId(proInfo):
		if len(proInfo) > 0:
			arrInfo = proInfo.split(' ')
			return int(arrInfo[0])
		return -1
	arrProIdx = []
	for content in arrProcess:
		idx = getProcessId(content)
		if idx > 0:
			arrProIdx.append(idx)
	return arrProIdx
def close_proj(proj, phone):
	print 'close running project'
	if curPlat == 'darwin':
		if phone == 'android':
			cmd = 'adb shell pm uninstall -n org.cocos2dx.hello'+proj
			infoUninstall = os.system(cmd)
			print 'infoUninstall apk:', infoUninstall, cmd
			return infoUninstall == 0
		print 'will close proj:',proj,', on',curPlat
		arrPids = getAppPID(proj+PROJ_SUFFIX)
		print 'arrPids:', arrPids
		for pid in arrPids:
			cmd = 'kill '
			cmd += str(pid)
			print 'cmd:',cmd
			os.system(cmd)

def build_run():
	print 'will build and run'
	for proj in project_types:
		idx = 0
		for phone in phonePlats:
			cmd = './'+cocos_console_dir+'cocos run -p '+phone+' -s '+proj+PROJ_SUFFIX
			print proj,'cmd:',cmd
			if runSupport[curPlat][idx]:
				info_run = os.system(cmd)
				print 'run project', proj, 'is:', not info_run
				if info_run == 0:
					time.sleep(5)
					close_proj(proj, phone)
					time.sleep(2)
			idx += 1

def main():
	clean_project()
	create_project()
	if console_param_arr.count('run'):
	 	build_run()
	# close_proj('cpp', 'android')

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

