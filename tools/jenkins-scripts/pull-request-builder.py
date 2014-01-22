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

    pr = payload['pull_request']
    
    url = pr['html_url']
    print "url:" + url
    pr_desc = '<h3><a href='+ url + '> pr#' + str(pr_num) + ' is '+ action +'</a></h3>'
    


    #get statuses url
    statuses_url = pr['statuses_url']

    #get pr target branch
    branch = pr['base']['ref']

    #set commit status to pending
    target_url = os.environ['BUILD_URL']

    set_description(pr_desc, target_url)
    
    if(action == 'closed'):
        print 'pull request #' + str(pr_num) + ' is '+action+', no build triggered'
        return(0)
  
    r = requests.get(pr['url']+"/commits")
    commits = r.json()
    last_commit = commits[len(commits)-1]
    message = last_commit['commit']['message']

    pattern = re.compile("\[ci(\s+)skip\]", re.I)
    result = pattern.search(message)
    if result is not None:
        print 'skip build for pull request #' + str(pr_num)
        return(0)
    
    data = {"state":"pending", "target_url":target_url}
    access_token = os.environ['GITHUB_ACCESS_TOKEN']
    Headers = {"Authorization":"token " + access_token} 

    try:
        requests.post(statuses_url, data=json.dumps(data), headers=Headers)
    except:
        traceback.print_exc()

    #reset path to workspace root
    os.system("cd " + os.environ['WORKSPACE']);
    os.system("git checkout develop")
    os.system("git branch -D pull" + str(pr_num))
    #clean workspace
    print "git clean -xdf"
    os.system("git clean -xdf")
    
   
    #fetch pull request to local repo
    git_fetch_pr = "git fetch origin pull/" + str(pr_num) + "/head"
    os.system(git_fetch_pr)
 
    #checkout
    git_checkout = "git checkout -b " + "pull" + str(pr_num) + " FETCH_HEAD"
    os.system(git_checkout)
 
    #update submodule
    git_update_submodule = "git submodule update --init --force"
    os.system(git_update_submodule)

    # Generate binding glue codes
    if(platform.system() == 'Darwin'):
      os.system("tools/jenkins-scripts/gen_jsb.sh")

    #make temp dir
    print "current dir is" + os.environ['WORKSPACE']
    os.system("cd " + os.environ['WORKSPACE']);
    os.mkdir("android_build_objs")
    #add symbol link
    PROJECTS=["Cpp/HelloCpp","Cpp/TestCpp","Cpp/SimpleGame","Cpp/AssetsManagerTest",
            "Javascript/TestJavascript","Javascript/CocosDragonJS","Javascript/CrystalCraze",
            "Javascript/MoonWarriors","Javascript/WatermelonWithMe","Lua/HelloLua","Lua/TestLua"]
    print platform.system()
    if(platform.system() == 'Darwin'):
        for item in PROJECTS:
          cmd = "ln -s " + os.environ['WORKSPACE']+"/android_build_objs/ " + os.environ['WORKSPACE']+"/samples/"+item+"/proj.android/obj"  
          os.system(cmd)
    elif(platform.system() == 'Windows'):
        for item in PROJECTS:
          p = item.replace("/", os.sep)
          cmd = "mklink /J "+os.environ['WORKSPACE']+os.sep+"samples"+os.sep +p+os.sep+"proj.android"+os.sep+"obj " + os.environ['WORKSPACE']+os.sep+"android_build_objs"
          print cmd
          os.system(cmd)
 
    #build
    #TODO: support android-mac build currently
    #TODO: add android-windows7 build
    #TODO: add android-linux build
    #TODO: add ios build
    #TODO: add mac build
    #TODO: add win32 build
    if(branch == 'develop'):
      ret = os.system("python build/android-build.py -n -j10 all")
    elif(branch == 'master'):
      ret = os.system("samples/Cpp/TestCpp/proj.android/build_native.sh")

    #get build result
    print "build finished and return " + str(ret)
    exit_code = 1
    if ret == 0:
        exit_code = 0
        data['state'] = "success"
        
    else:
        exit_code = 1
        data['state'] = "failure"

    #set commit status
    try:
        requests.post(statuses_url, data=json.dumps(data), headers=Headers)
    except:
        traceback.print_exc()

    #clean workspace
    os.system("cd " + os.environ['WORKSPACE']);
    os.system("git checkout develop")
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
