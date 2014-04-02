import os
import subprocess
import sys
print 'Build Config:'
print '    Host:win7 x86'
print '    Branch:develop'
print '    Target:win32'
print '    "%VS110COMNTOOLS%..\IDE\devenv.com" "build\cocos2d-win32.vc2012.sln" /Build "Debug|Win32"'
if(os.path.exists('build/cocos2d-win32.vc2012.sln') == False):
  node_name = os.environ['NODE_NAME']
  source_dir = '../cocos-2dx-develop-base-repo/node/' + node_name
  source_dir = source_dir.replace("/", os.sep)
  os.system("xcopy " + source_dir + " . /E /Y /H")
  os.system('git pull origin develop')

os.system('git submodule update --init --force')
ret = subprocess.call('"%VS110COMNTOOLS%..\IDE\devenv.com" "build\cocos2d-win32.vc2012.sln" /Build "Debug|Win32"', shell=True)
os.system('git clean -xdf -f')
print 'build exit'
print ret
if ret == 0:
  exit(0)
else:
  exit(1)
