import os
import platform
print 'Build Config:'
print '    Branch:develop'
print '    Target:Android'
print '    build script:python build/android-build.py all'
if(os.path.exists('build/android-build.py') == False):
    node_name = os.environ['NODE_NAME']
    source_dir = '../cocos-2dx-develop-base-repo/node/' + node_name + "/."
    os.system("cp -r" + source_dir + " .")
    os.system('git pull origin develop')

os.system('git submodule update --init --force')
ret = os.system('python build/android-build.py -n -j8 all')
os.system('git clean -xdf -f')
print 'build exit'
print ret
if ret == 0:
    exit(0)
else:
    exit(1)
