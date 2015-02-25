import os
os.system('git checkout develop')
os.system('git pull origin develop')
os.system('git submodule update')
print('in building, run cocos-console-test.py.')
#ret=0
ret = os.system('python -u tools/jenkins-scripts/cocos-console-test.py')
os.system('git reset --hard')
print ret
if(ret > 0):
    ret = 1
exit(ret)
