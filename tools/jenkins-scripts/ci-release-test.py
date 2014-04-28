#CI release for Jenkins 

import json
import os
import re
import urllib2
import urllib
import base64
import requests
import sys
import traceback
import platform
import subprocess
import codecs

#set Jenkins build description using submitDescription to mock browser behavior
#TODO: need to set parent build description 
def set_description(desc, url):
    req_data = urllib.urlencode({'description': desc})
    req = urllib2.Request(url + 'submitDescription', req_data)
    #print(os.environ['BUILD_URL'])
    req.add_header('Content-Type', 'application/x-www-form-urlencoded') 
    base64string = base64.encodestring(os.environ['JENKINS_ADMIN']+ ":" + os.environ['JENKINS_ADMIN_PW']).replace('\n', '')
    req.add_header("Authorization", "Basic " + base64string)
    try:
        urllib2.urlopen(req)
    except:
        traceback.print_exc()

def make_temp_dir():
    #make temp dir
    print "current dir is: " + os.environ['WORKSPACE']
    os.system("cd " + os.environ['WORKSPACE']);
    os.mkdir("android_build_objs")
    #add symbol link
    PROJECTS=["cpp-empty-test", "cpp-tests"]

    print platform.system()
    if(platform.system() == 'Darwin'):
        for item in PROJECTS:
          cmd = "ln -s " + os.environ['WORKSPACE']+"/android_build_objs/ " + os.environ['WORKSPACE']+"/tests/"+item+"/proj.android/obj"  
          os.system(cmd)
    elif(platform.system() == 'Windows'):
        for item in PROJECTS:
          p = item.replace("/", os.sep)
          cmd = "mklink /J "+os.environ['WORKSPACE']+os.sep+"tests"+os.sep +p+os.sep+"proj.android"+os.sep+"obj " + os.environ['WORKSPACE']+os.sep+"android_build_objs"
          print cmd
          os.system(cmd)

def main():
    #get tag
    tag = os.environ['tag']
    print 'tag:' + tag

    pr_desc = '<h3>' + tag + ' is release' + '</h3>'

    #get pr target branch
    branch = 'v3'

    #set parent build description
    jenkins_url = os.environ['JENKINS_URL']
    job_name = os.environ['JOB_NAME'].split('/')[0]
    build_number = os.environ['BUILD_NUMBER']
    target_url = jenkins_url + 'job/' + job_name + '/' + build_number + '/'

    set_description(pr_desc, target_url)

    #pull origin v3
    os.system('git reset --hard')
    os.system("git clean -xdf -f")
    os.system("git checkout v3")
    os.system("git branch -D " + tag)
    os.system("git clean -xdf -f")
    #fetch tag to local repo
    git_fetch_pr = "git fetch origin tag " + tag
    ret = os.system(git_fetch_pr)
    if(ret != 0):
        return(2)

    #checkout
    git_checkout = "git checkout -b " + tag + " FETCH_HEAD"
    os.system(git_checkout)

    # After checkout a new branch, clean workspace again
    print "After checkout: git clean -xdf -f"    
    os.system("git clean -xdf -f")
    
    #update submodule
    git_update_submodule = "git submodule update --init --force"
    ret = os.system(git_update_submodule)
    if(ret != 0):
        return(2)

    #build
    #TODO: add android-linux build
    #TODO: add mac build
    node_name = os.environ['NODE_NAME']
    build_mode = ['debug', 'release']
    tests_dirs = ['tests/cpp-empty-test/proj.android',
                  'tests/cpp-tests/proj.android',
                  'tests/lua-empty-test/project/proj.android',
                  'tests/lua-tests/project/proj.android']
    tests_names = ['cpp-empty-test', 'cpp-tests', 'lua-empty-test', 'lua-tests']
    remote_home = os.environ['REMOTE_HOME']
    for mode in build_mode:
        os.system('git reset --hard')
        os.system("git clean -xdf -f")
        make_temp_dir()
        if(branch == 'v3'):
          # Generate binding glue codes
          ret = os.system("python tools/jenkins-scripts/gen_jsb.py")
          if(ret != 0):
            return(1)
          if(node_name == 'android_mac') or (node_name == 'android_win7'):
            print "Start build android..."
            ret = os.system("python build/android-build.py -b " + mode + " -n -j10 all")
            # create and save apk
            if(ret == 0):
              os.system('android update project -p cocos/2d/platform/android/java/ -t android-13')
              for i, test in enumerate(tests_dirs):
                os.system('android update project -p ' + test + ' -t android-13')
                local_apk = test + '/' + tests_names[i] + '.apk'
                remote_dir = '/data/download/' + tag + '/'
                remote_apk = remote_dir + tests_names[i] + '-' + tag + '-' + mode + '.apk'
                os.system('ant debug -f ' + test + '/build.xml' + ' -Dout.final.file=$PWD/' + local_apk)
                os.system('ssh ' + remote_home + ' "mkdir -p ' + remote_dir + '"')
                os.system('scp ' + local_apk + ' ' + remote_home + ':' + remote_apk)

    #get build result
    print "build finished and return " + str(ret)
    
    exit_code = 1
    if ret == 0:
        exit_code = 0
    else:
        exit_code = 1
    
    #clean workspace
    os.system("cd " + os.environ['WORKSPACE'])
    os.system("git reset --hard")
    os.system("git clean -xdf -f")
    os.system("git checkout v3")

    return(exit_code)

# -------------- main --------------
if __name__ == '__main__':
    sys_ret = 0
    try:    
        sys_ret = main()
    except:
        traceback.print_exc()
        sys_ret = 1
    finally:
        sys.exit(sys_ret)
