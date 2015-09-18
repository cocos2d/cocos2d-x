import os
import sys
import traceback
import urllib
import urllib2
import base64
import json
import requests
import subprocess

#set Jenkins build description using submitDescription to mock browser behavior
http_proxy = ''
if('HTTP_PROXY' in os.environ):
    http_proxy = os.environ['HTTP_PROXY']
proxyDict = {'http': http_proxy, 'https': http_proxy}

branch = "v3"
pr_num = 0
workspace = "."
node_name = "ios"

def set_jenkins_job_description(desc, url):
    req_data = urllib.urlencode({'description': desc})
    request = urllib2.Request(url + 'submitDescription', req_data)
    #print(os.environ['BUILD_URL'])
    request.add_header('Content-Type', 'application/x-www-form-urlencoded')
    user_name = os.environ['JENKINS_ADMIN']
    password = os.environ['JENKINS_ADMIN_PW']
    base64string = base64.encodestring(user_name + ":" + password).replace('\n', '')
    request.add_header("Authorization", "Basic " + base64string)
    try:
        urllib2.urlopen(request)
    except:
        traceback.print_exc()

def send_notifies_to_github():
    global branch
    global pr_num
    global workspace
    global node_name
    # get payload from os env
    payload_str = os.environ['payload']
    payload_str = payload_str.decode('utf-8', 'ignore')
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
    pr_desc = '<h3><a href=' + url + '> pr#' + str(pr_num) + ' is ' + action + '</a></h3>'

    #get statuses url
    statuses_url = payload['statuses_url']

    #get pr target branch
    branch = payload['branch']
    workspace = os.environ['WORKSPACE']
    node_name = os.environ['NODE_NAME']

    #set commit status to pending
    # target_url = os.environ['BUILD_URL']
    jenkins_url = os.environ['JENKINS_URL']
    job_name = os.environ['JOB_NAME'].split('/')[0]
    build_number = os.environ['BUILD_NUMBER']
    target_url = jenkins_url + 'job/' + job_name + '/' + build_number + '/'

    set_jenkins_job_description(pr_desc, target_url)

    data = {"state": "pending", "target_url": target_url, "context": "Jenkins CI", "description": "Build started..."}
    access_token = os.environ['GITHUB_ACCESS_TOKEN']
    Headers = {"Authorization": "token " + access_token}

    try:
        requests.post(statuses_url, data=json.dumps(data), headers=Headers, proxies=proxyDict)
    except:
        traceback.print_exc()

def syntronize_remote_pr():
    global workspace
    global branch
    global pr_num
    #reset path to workspace root
    os.system("cd " + workspace)
    #pull latest code
    os.system("git fetch origin " + branch)
    os.system("git --version")
    os.system("git checkout " + branch)
    os.system("git merge origin/" + branch)
    os.system("git branch -D pull" + str(pr_num))
    #clean workspace
    print "Before checkout: git clean -xdf -f"
    os.system("git clean -xdf -f")
    #fetch pull request to local repo
    git_fetch_pr = "git fetch origin pull/" + str(pr_num) + "/head"
    ret = os.system(git_fetch_pr)
    if(ret != 0):
        sys.exit(1)

    #checkout a new branch from v3 or v4-develop
    git_checkout = "git checkout -b " + "pull" + str(pr_num)
    os.system(git_checkout)
    #merge pull reqeust head
    subprocess.call("git merge --no-edit FETCH_HEAD", shell=True)

    # The follow method is not working for Azure server
    # p = os.popen('git merge --no-edit FETCH_HEAD')
    # r = p.read()
    # #check if merge fail
    # if output.find('CONFLICT') > 0:
    #     print output
    #     raise Exception('There are conflicts in your PR!')

    # After checkout a new branch, clean workspace again
    print "After checkout: git clean -xdf -f"
    os.system("git clean -xdf -f")

    #update submodule
    git_update_submodule = "git submodule update --init --force"
    ret = os.system(git_update_submodule)
    if(ret != 0):
        sys.exit(1)


# -------------- main --------------
if __name__ == '__main__':
    sys_ret = 0
    try:
        send_notifies_to_github()
        #syntronize local git repository with remote and merge the PR
        syntronize_remote_pr()
        jenkins_script_path = "tools" + os.sep + "jenkins-scripts" + os.sep + "do-pull-request-builder.py"
        sys_ret = os.system("python " + jenkins_script_path)
    except:
        traceback.print_exc()
        sys_ret = 1
    finally:
        if sys_ret != 0:
            sys.exit(1)
        else:
            sys.exit(0)
