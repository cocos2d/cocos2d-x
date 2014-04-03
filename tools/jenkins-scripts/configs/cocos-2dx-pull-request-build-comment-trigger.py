import os
#os.system('git checkout develop')
#os.system('git pull origin develop')
ret = os.system('python -u tools/jenkins-scripts/job-comment-trigger.py')
if ret == 0: 
  exit(0)
else:
  exit(1)
