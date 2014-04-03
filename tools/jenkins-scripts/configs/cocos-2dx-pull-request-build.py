import os
import platform
if(os.path.exists('tools/jenkins-scripts/pull-request-builder.py') == False):
  node_name = os.environ['NODE_NAME']
  source_dir = '../../../cocos-2dx-develop-base-repo/node/' + node_name
  if(platform.system() == 'Windows'):
    source_dir = source_dir.replace("/", os.sep)
    os.system("xcopy " + source_dir + ' . /E /Y /H')
  else:
    os.system("cp -r " + source_dir + "/. .")

os.system('git reset --hard')
os.system('git checkout develop')
os.system('git reset --hard')
os.system('git pull origin develop')
ret = os.system('python -u tools/jenkins-scripts/pull-request-builder.py')
os.system('git reset --hard')
print ret
if(ret > 0):
  ret = 1
exit(ret)
