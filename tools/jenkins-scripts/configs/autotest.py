import os
os.system('git checkout develop')
os.system('git pull origin develop')
print('in building, run autotest.py.')
ret = os.system('python -u tools/jenkins-scripts/autotest.py')
os.system('git reset --hard')
print ret
if(ret > 0):
    ret = 1
exit(ret)
