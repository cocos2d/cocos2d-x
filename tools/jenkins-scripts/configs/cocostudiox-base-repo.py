import os
import sys
ret = os.system('git pull origin master')
if(ret != 0):
  sys.exit(1)
ret = os.system('git submodule update --init --force')
if(ret != 0):
  sys.exit(1)
