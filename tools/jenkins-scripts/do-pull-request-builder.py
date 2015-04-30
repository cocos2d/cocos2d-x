#Github pull reqest builder for Jenkins

import json
import os
import urllib2
import urllib
import base64
import requests
import sys
import traceback
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
# for local debugging purpose, you could change the value to 0 and run
# this scripts in your local machine
remote_build = 1


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


def check_current_3rd_libs(branch):
    #run download-deps.py
    print("prepare to downloading ...")
    os.system('python download-deps.py -r no')


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


def gen_scripting_bindings():
    global branch
    # Generate binding glue codes
    if(branch != 'v1' and branch != 'v2'):
        ret = os.system("python tools/jenkins-scripts/slave-scripts/gen_jsb.py")
    if(ret != 0):
        sys.exit(1)


def do_build_slaves():
    global branch
    global node_name

    jenkins_script_path = "tools" + os.sep + "jenkins-scripts" + os.sep + "slave-scripts" + os.sep

    if(branch != 'v1' and branch != 'v2'):
        slave_build_scripts = ""
        if(node_name == 'android') or (node_name == 'android_bak'):
            # patch_cpp_empty_test()
            slave_build_scripts = jenkins_script_path + "android-build.sh"
        elif(node_name == 'win32' or node_name == 'win32_win7' or node_name == 'win32_bak'):
            if branch != 'v4':
                slave_build_scripts = jenkins_script_path + "win32-vs2012-build.bat"
            else:
                slave_build_scripts = jenkins_script_path + "win32-vs2013-build.bat"
        elif(node_name == 'windows-universal' or node_name == 'windows-universal_bak'):
            if branch != 'v4':
                slave_build_scripts = jenkins_script_path + "windows-universal-v3.bat"
            else:
                slave_build_scripts = jenkins_script_path + "windows-universal.bat"
        elif(node_name == 'ios_mac' or node_name == 'ios' or node_name == 'ios_bak'):
            slave_build_scripts = jenkins_script_path + "ios-build.sh"
        elif(node_name == 'mac' or node_name == 'mac_bak'):
            slave_build_scripts = jenkins_script_path + "mac-build.sh"
        elif(node_name == 'linux_centos' or node_name == 'linux' or node_name == 'linux_bak'):
            slave_build_scripts = jenkins_script_path + "linux-build.sh"
        elif(node_name == 'wp8'):
            if(branch != 'v4'):
                slave_build_scripts = jenkins_script_path + "wp8-v3.bat"

        ret = os.system(slave_build_scripts)

    #get build result
    print "build finished and return " + str(ret)
    return ret


def main():
    global pr_num
    global workspace
    global branch
    global node_name
    global remote_build

    if remote_build == 1:
        send_notifies_to_github()
        #syntronize local git repository with remote and merge the PR
        syntronize_remote_pr()
        #copy check_current_3rd_libs
        check_current_3rd_libs(branch)

    #generate jsb and luabindings
    gen_scripting_bindings()
    #start build jobs on each slave
    ret = do_build_slaves()

    exit_code = 1
    if ret == 0:
        exit_code = 0
    else:
        exit_code = 1

    #clean workspace
    if remote_build == 1:
        os.system("cd " + workspace)
        os.system("git reset --hard")
        os.system("git clean -xdf -f")
        os.system("git checkout " + branch)
        os.system("git branch -D pull" + str(pr_num))
    else:
        print "local build, no need to cleanup"

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
        print "return value is " + str(sys_ret)
        if sys_ret != 0:
            sys.exit(1)
        else:
            sys.exit(0)
