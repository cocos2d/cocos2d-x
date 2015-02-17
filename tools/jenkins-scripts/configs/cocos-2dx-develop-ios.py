import os
print 'Build Config:'
print '    Host:MAC'
print '    Branch:develop'
print '    Target:iOS'
if(os.path.exists('tools/jenkins-scripts/ios-build.sh') == False):
    node_name = os.environ['NODE_NAME']
    source_dir = '../cocos-2dx-develop-base-repo/node/' + node_name + "/."
    os.system("cp -r " + source_dir + " .")
    os.system('git pull origin develop')

os.system('git submodule update --init --force')
ret = os.system('tools/jenkins-scripts/ios-build.sh')
os.system('git clean -xdf -f')
print 'build exit'
print ret
if ret == 0:
    exit(0)
else:
    exit(1)
