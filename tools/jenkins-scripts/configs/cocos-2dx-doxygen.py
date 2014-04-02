import os
import platform
print 'Build Config:'
print '    Branch:develop'
print '    Target:Doxygen'
print '    doxygen doxygen.config'
if(os.path.exists('docs/doxygen.config') == False):
  node_name = os.environ['NODE_NAME']
  source_dir = '../cocos-2dx-develop-base-repo/node/' + node_name
  source_dir = source_dir.replace("/", os.sep)
  os.system("xcopy " + source_dir + " . /E /Y /H")
  os.system('git pull origin develop')

os.system('git submodule update --init --force')
os.chdir('docs/')
ret = os.system('doxygen doxygen.config')
os.chdir('../')
os.system('git clean -xdf -f')
print 'build exit'
print ret
if ret == 0:
  exit(0)
else:
  exit(1)
