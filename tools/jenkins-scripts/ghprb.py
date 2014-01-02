#Github pull reqest builder for Jenkins 

import json
import os
import re
import urllib2
import urllib
import base64
import requests
import sys

#get payload from os env
payload_str = os.environ['payload']
#parse to json obj
payload = json.loads(payload_str)

#get pull number
pr_num = payload['number']
print 'pr_num:' + str(pr_num)

#build for pull request action 'open' and 'synchronize', skip 'close'
action = payload['action']
print 'action: ' + action
if((action != 'opened') and (action != 'synchronize')):
    print 'pull request #' + str(pr_num) + ' is closed, no build triggered'
    exit(0)


pr = payload['pull_request']
url = pr['html_url']
print "url:" + url
pr_desc = '<h3><a href='+ url + '> pr#' + str(pr_num) + '</a></h3>'
#set Jenkins build description using submitDescription to mock browser behavior
#TODO: need to set parent build description 
def set_description(desc):
    req_data = urllib.urlencode({'description': desc})
    req = urllib2.Request(os.environ['BUILD_URL'] + 'submitDescription', req_data)
    #print(os.environ['BUILD_URL'])
    req.add_header('Content-Type', 'application/x-www-form-urlencoded') 
    base64string = base64.encodestring(os.environ['JENKINS_ADMIN']+ ":" + os.environ['JENKINS_ADMIN_PW']).replace('\n', '')
    req.add_header("Authorization", "Basic " + base64string)
    urllib2.urlopen(req)
try:
    set_description(pr_desc)
except:
    e = sys.exc_info()[0]
    print e

#get statuses url
statuses_url = pr['statuses_url']

#get pr target branch
branch = pr['head']['ref']

#set commit status to pending
target_url = os.environ['BUILD_URL']
data = {"state":"pending", "target_url":target_url}
acccess_token = os.environ['GITHUB_ACCESS_TOKEN']
Headers = {"Authorization":"token " + acccess_token} 
try:
    requests.post(statuses_url, data=json.dumps(data), headers=Headers)
    
    #reset path to workspace root
    os.system("cd " + os.environ['WORKSPACE']);

    #fetch pull request to local repo
    git_fetch_pr = "git fetch origin pull/" + str(pr_num) + "/head"
    os.system(git_fetch_pr)

    #checkout
    git_checkout = "git checkout -b " + "pull" + str(pr_num) + " FETCH_HEAD"
    os.system(git_checkout)

    #update submodule
    git_update_submodule = "git submodule update --init --force"
    os.system(git_update_submodule)
except:
    e = sys.exc_info()[0]
    print e


#build
#TODO: support android-mac build currently
#TODO: add android-windows7 build
#TODO: add android-linux build
#TODO: add ios build
#TODO: add mac build
#TODO: add win32 build
if(branch == 'develop'):
  ret = os.system("python build/android-build.py -n -j5 testcpp")
elif(branch == 'master'):
  ret = os.system("samples/Cpp/TestCpp/proj.android/build_native.sh")

#get build result
print "build finished and return " + str(ret)
if ret == 0:
    exit_code = 0
    data['state'] = "success"
    
else:
    exit_code = 1
    data['state'] = "failure"
try:
    #set commit status
    requests.post(statuses_url, data=json.dumps(data), headers=Headers)

    #clean workspace
    os.system("cd " + os.environ['WORKSPACE']);
    os.system("git checkout develop")
    os.system("git branch -D pull" + str(pr_num))
except:
    e = sys.exc_info()[0]
    print e
exit(exit_code)

