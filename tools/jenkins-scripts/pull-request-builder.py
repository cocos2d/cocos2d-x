#Github pull reqest builder for Jenkins 

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
from shutil import copy
import MySQLdb

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

def check_current_3rd_libs(branch):
    #get current_libs config
    backup_files = range(2)
    current_files = range(2)
    config_file_paths = ['external/config.json','templates/lua-template-runtime/runtime/config.json']
    if (branch == 'v2'):
        config_file_paths = ['external/config.json']
        backup_files = range(1)
        current_files = range(1)
    for i, config_file_path in enumerate(config_file_paths):
        if not os.path.isfile(config_file_path):
            raise Exception("Could not find 'external/config.json'")

        with open(config_file_path) as data_file:
            data = json.load(data_file)

        current_3rd_libs_version = data["version"]
        filename = current_3rd_libs_version + '.zip'
        node_name = os.environ['NODE_NAME']
        backup_file = '../../../cocos-2dx-external/node/' + node_name + '/' + filename
        backup_files[i] = backup_file
        current_file = filename
        current_files[i] = current_file
        if os.path.isfile(backup_file):
          copy(backup_file, current_file)
    #run download-deps.py
    os.system('python download-deps.py -r no')
    #backup file
    for i, backup_file in enumerate(backup_files):
        current_file = current_files[i]
        copy(current_file, backup_file)

def connect_db():
    db_host = os.environ['db_host']
    db_user = os.environ['db_user']
    db_pw = os.environ['db_pw']
    db_name=os.environ['db_name']
    db = MySQLdb.connect(db_host, db_user, db_pw, db_name)
    return db

def close_db(db):
    db.close()

def save_build_stats(db, pr, filename, size):
    cursor = db.cursor()
    sql = "INSERT INTO %s (number, size, createdTime) VALUES(%d, %d, now())" % (filename, pr, size)
    print sql
    cursor.execute(sql)
    db.commit()

def scan_all_libs(db, pr_num):
    stats = {}
    lib_path = './tests/cpp-tests/proj.android/obj/local/armeabi'
    for root, dirs, files in os.walk(lib_path):
      for _file in files:
        if not _file.endswith(".a"):
          continue
        print _file
        libfile = lib_path + '/' + _file
        _filename = _file.split('.')[0]
        filesize = os.path.getsize(libfile)/1024
        stats[_filename]=filesize
        save_build_stats(db, pr_num, _filename, filesize)
    return stats

http_proxy = ''
if(os.environ.has_key('HTTP_PROXY')):
    http_proxy = os.environ['HTTP_PROXY']
proxyDict = {'http':http_proxy,'https':http_proxy}

def main():
    #get payload from os env
    payload_str = os.environ['payload']
    payload_str = payload_str.decode('utf-8','ignore')
    #parse to json obj
    payload = json.loads(payload_str)

    #get pull number
    pr_num = payload['number']
    print 'pr_num:' + str(pr_num)

    #build for pull request action 'open' and 'synchronize', skip 'close'
    action = payload['action']
    print 'action: ' + action

    #pr = payload['pull_request']
    
    url = payload['html_url']
    print "url:" + url
    pr_desc = '<h3><a href='+ url + '> pr#' + str(pr_num) + ' is '+ action +'</a></h3>'
    


    #get statuses url
    statuses_url = payload['statuses_url']

    #get pr target branch
    branch = payload['branch']

    #set commit status to pending
    #target_url = os.environ['BUILD_URL']
    jenkins_url = os.environ['JENKINS_URL']
    job_name = os.environ['JOB_NAME'].split('/')[0]
    build_number = os.environ['BUILD_NUMBER']
    target_url = jenkins_url + 'job/' + job_name + '/' + build_number + '/'

    set_description(pr_desc, target_url)
 
    
    data = {"state":"pending", "target_url":target_url, "context":"Jenkins CI", "description":"Build started..."}
    access_token = os.environ['GITHUB_ACCESS_TOKEN']
    Headers = {"Authorization":"token " + access_token} 

    try:
        requests.post(statuses_url, data=json.dumps(data), headers=Headers, proxies = proxyDict)
    except:
        traceback.print_exc()

    #reset path to workspace root
    os.system("cd " + os.environ['WORKSPACE']);
    #pull latest code
    os.system("git pull origin v3")
    os.system("git checkout v3")
    os.system("git branch -D pull" + str(pr_num))
    #clean workspace
    print "Before checkout: git clean -xdf -f"    
    os.system("git clean -xdf -f")
    #fetch pull request to local repo
    git_fetch_pr = "git fetch origin pull/" + str(pr_num) + "/head"
    ret = os.system(git_fetch_pr)
    if(ret != 0):
        return(2)
 
    #checkout a new branch from v3
    git_checkout = "git checkout -b " + "pull" + str(pr_num)
    os.system(git_checkout)
    #merge pull reqeust head
    p = os.popen('git merge --no-edit FETCH_HEAD')
    r = p.read()
    #check if merge fail
    if r.find('CONFLICT') > 0:
        print r
        return(3)
 
    # After checkout a new branch, clean workspace again
    print "After checkout: git clean -xdf -f"    
    os.system("git clean -xdf -f")

    #update submodule
    git_update_submodule = "git submodule update --init --force"
    ret = os.system(git_update_submodule)
    if(ret != 0):
        return(2)

    #copy check_current_3rd_libs
    # check_current_3rd_libs(branch)

    # Generate binding glue codes
    if(branch == 'v3'):
      ret = os.system("python tools/jenkins-scripts/gen_jsb.py")
    elif(branch == 'v2'):
      os.chdir('tools/tojs')
      if(platform.system() == 'Windows'):
        os.environ['NDK_ROOT'] = os.environ['NDK_ROOT_R8E']
        ret = os.system("genbindings-win32.bat")
        os.environ['NDK_ROOT'] = os.environ['NDK_ROOT_R9B']
      else:
        ret = os.system("./genbindings.sh")
      os.chdir('../..')
    if(ret != 0):
        return(1)

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
 
    #build
    #TODO: add android-linux build
    #TODO: add mac build
    node_name = os.environ['NODE_NAME']
    if(branch == 'v3'):
      if(node_name == 'android_mac') or (node_name == 'android_win7'):
        #modify tests/cpp-empty-test/Classes/AppDelegate.cpp to support Console
        modify_file = 'tests/cpp-empty-test/Classes/AppDelegate.cpp'
        data = codecs.open(modify_file, encoding='UTF-8').read()
        data = re.sub("director->setDisplayStats\(true\);", "director->setDisplayStats(true); director->getConsole()->listenOnTCP(5678);", data)
        codecs.open(modify_file, 'wb', encoding='UTF-8').write(data)
        #modify tests/cpp-empty-test/proj.android/AndroidManifest.xml to support Console
        modify_file = 'tests/cpp-empty-test/proj.android/AndroidManifest.xml'
        data = codecs.open(modify_file, encoding='UTF-8').read()
        data = re.sub('<uses-feature android:glEsVersion="0x00020000" />', '<uses-feature android:glEsVersion="0x00020000" /> <uses-permission android:name="android.permission.INTERNET"/>', data)
        codecs.open(modify_file, 'wb', encoding='UTF-8').write(data)
        print "Start build android..."
        ret = os.system("python build/android-build.py -p 10 all")
        # create and save apk
        if(ret == 0):
          sample_dir = 'tests/cpp-tests/proj.android/'
          local_apk = sample_dir + 'bin/CppTests-debug.apk'
          backup_apk = os.environ['BACKUP_PATH'] + 'CppTests_' + str(pr_num) + '.apk'
          os.system('cp ' + local_apk + ' ' + backup_apk)
          db = connect_db()
          scan_all_libs(db, pr_num)
          ret = os.system("python build/android-build.py -p 10 -b release cpp-empty-test")
          if(ret == 0):
            _path = 'tests/cpp-empty-test/proj.android/libs/armeabi/libcpp_empty_test.so'
            filesize = os.path.getsize(_path)
            pr_desc = pr_desc + '<h3>size of libcpp_empty_test.so is:' + str(filesize/1024) + 'kb</h3>'
            set_description(pr_desc, target_url)
            save_build_stats(db, pr_num, 'libcpp_empty_test', filesize/1024)
          ret = os.system("python build/android-build.py -p 10 -b release lua-empty-test")
          if(ret == 0):
            _path = 'tests/lua-empty-test/project/proj.android/libs/armeabi/liblua_empty_test.so'
            filesize = os.path.getsize(_path)
            pr_desc = pr_desc + '<h3>size of liblua_empty_test.so is:' + str(filesize/1024) + 'kb</h3>'
            set_description(pr_desc, target_url)
            save_build_stats(db, pr_num, 'liblua_empty_test', filesize/1024)
          close_db(db)
      elif(node_name == 'win32_win7'):
        ret = subprocess.call('"%VS110COMNTOOLS%..\IDE\devenv.com" "build\cocos2d-win32.vc2012.sln" /Build "Debug|Win32"', shell=True)
      elif(node_name == 'ios_mac'):
        ret = os.system("tools/jenkins-scripts/ios-build.sh")
      elif(node_name == 'linux_centos'):
        os.chdir("build/")
        ret = os.system("cmake ../")
        ret = os.system("make -j10")
        os.chdir("../")
    elif(branch == 'v2'):
      SAMPLES_DIRS = ['Cpp/HelloCpp', 'Cpp/SimpleGame', 'Cpp/TestCpp', 'Javascript/TestJavascript', 'Lua/HelloLua', 'Lua/TestLua']
      SAMPLES_NAMES = ['HelloCpp', 'SimpleGame', 'TestCpp', 'TestJavascript', 'HelloLua', 'TestLua']
      if(node_name == 'android_mac'):
        for item in SAMPLES_DIRS:
          proj_dir = "samples/" + item + "/proj.android"
          os.system('ln -s ../../../../android_build_objs obj')
          os.system(proj_dir + "/build_native.sh")
          if (ret != 0):
            break
      elif(node_name == 'win32_win7'):
        ret = subprocess.call('"%VS110COMNTOOLS%..\IDE\devenv.com" "cocos2d-win32.vc2012.sln" /Build "Debug|Win32"', shell=True)
      elif(node_name == 'ios_mac'):
        for i, item in enumerate(SAMPLES_DIRS):
          cmd = "xcodebuild -project samples/" + item + "/proj.ios/" + SAMPLES_NAMES[i] + ".xcodeproj -scheme " + SAMPLES_NAMES[i] + ' -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)"'
          cmd_clean = cmd + ' clean'
          cmd_build = cmd + ' build'
          ret = os.system(cmd_clean)
          if(ret != 0):
            break
          ret = os.system(cmd_build)
          if(ret != 0):
            break
      elif(node_name == 'linux_centos'):
        data = codecs.open('cocos2dx/proj.linux/cocos2dx.mk', encoding='UTF-8').read()
        data = re.sub('-lglfw','-L$(GLFW_279_LIB) -lglfw', data)
        codecs.open('cocos2dx/proj.linux/cocos2dx.mk', 'wb', encoding='UTF-8').write(data)
        ret = os.system('make -j10')
      else:
        ret = 0

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
    os.system("git branch -D pull" + str(pr_num))

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
