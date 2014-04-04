import os
import platform
if(os.path.exists('CocoStudio/CSX/CSX/CSX.pro') == False):
  node_name = os.environ['NODE_NAME']
  source_dir = '../../../cocostudiox-base-repo/node/' + node_name
  if(platform.system() == 'Windows'):
    source_dir = source_dir.replace("/", os.sep)
    os.system("xcopy " + source_dir + ' . /E /Y /H')
  else:
    os.system("cp -r " + source_dir + "/. .")

os.system('git pull origin')
os.system('git submodule update --init --force')

node_name = os.environ['NODE_NAME']
os.chdir('CocoStudio/CSX/CSX')
ret = os.system('qmake -r')
if(ret == 0):
  if(node_name == 'android_mac'):
    ret = os.system('make -j8')
  elif(node_name == 'win32_win7'):
    ret = os.system('mingw32-make -j8')
os.chdir('../../..')

os.system('git clean -xdf')
os.system('git reset --hard')
print ret
if(ret > 0):
  ret = 1
exit(ret)
