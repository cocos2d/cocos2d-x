import json
import re
import os
import requests
import sys
import traceback
import urllib2

http_proxy = ''
if('HTTP_PROXY' in os.environ):
    http_proxy = os.environ['HTTP_PROXY']
proxyDict = {'http': http_proxy, 'https': http_proxy}

def main():
    #get payload from os env
    payload_str = os.environ['payload']
    #parse to json obj
    payload = json.loads(payload_str)

    print payload

    issue = payload['issue']
    #get pull number
    pr_num = issue['number']
    print 'pr_num:' + str(pr_num)
    payload_forword = {"number": pr_num}

    comment = payload['comment']
    #get comment body
    comment_body = comment['body']
    print comment_body
    #will check 'ci' comment
    searchCI = re.search("\[ci.*\]", comment_body)

    #will check console/console create
    searchConsole = re.search('\[console.*\]', comment_body)

    if searchCI is None and searchConsole is None:
        print 'skip build for pull request #' + str(pr_num)
        return(0)

    #build for pull request action 'open' and 'synchronize', skip 'close'
    action = issue['state']
    print 'action: ' + action
    payload_forword['action'] = action

    pr = issue['pull_request']
    url = pr['html_url']
    print "url:" + url
    payload_forword['html_url'] = url

    #get pull request info
    req = os.environ['GITHUB_REMOTE'] + str(pr_num)
    pr_payload = ''
    try:
        pr_payload = urllib2.urlopen(req).read()
    except:
        traceback.print_exc()

    repository = json.loads(pr_payload)
    #get statuses url
    statuses_url = repository['statuses_url']
    payload_forword['statuses_url'] = statuses_url
    print 'statuses_url: ' + statuses_url
    #get comments url
    comments_url = repository['comments_url']
    payload_forword['comments_url'] = comments_url
    print 'comments_url: ' + comments_url

    #get pr target branch
    branch = repository['base']['ref']
    payload_forword['branch'] = branch
    print 'branch: ' + branch

    #set commit status to pending
    target_url = os.environ['JOB_PULL_REQUEST_BUILD_URL']

    if(action == 'closed' or action == 'assigned' or branch == 'v2' or branch == 'v3-doc'):
        print 'pull request #' + str(pr_num) + ' is ' + action + ', no build triggered'
        return(0)

    data = {"state": "pending", "target_url": target_url, "context": "Jenkins CI",
            "description": "Wait available build machine..."}
    access_token = os.environ['GITHUB_ACCESS_TOKEN']
    Headers = {"Authorization": "token " + access_token}

    try:
        if searchCI:
            ciOper = searchCI.group()
            if('rebuild' in ciOper):
                requests.post(statuses_url, data=json.dumps(data),
                              headers=Headers, proxies=proxyDict)
    except:
        traceback.print_exc()

    job_trigger_url = ''
    if searchCI:
        ciOper = searchCI.group()
        if('rebuild' in ciOper):
            job_trigger_url = os.environ['JOB_PULL_REQUEST_BUILD_TRIGGER_URL']
        if('emptytest' in ciOper):
            job_trigger_url = os.environ['JOB_EMPTYTEST_TRIGGER_URL']
        if('release' in ciOper):
            searchTag = re.search('\[ci release (.*)\]', ciOper)
            if searchTag:
                ci_tag = searchTag.group(1)
                payload_forword['tag'] = ci_tag
                job_trigger_url = os.environ['JOB_RELEASE_TRIGGER_URL']
    if searchConsole:
        consoleOper = searchConsole.group()
        job_trigger_url = os.environ['JOB_CONSOLE_TEST_TRIGGER_URL']
        payload_forword['console'] = consoleOper
    print 'job_trigger_url is: ', job_trigger_url

    #send trigger and payload
    if('tag' in payload_forword):
        post_data = {'tag': ""}
        post_data['tag'] = payload_forword['tag']
    else:
        post_data = {'payload': ""}
        post_data['payload'] = json.dumps(payload_forword)
    requests.post(job_trigger_url, data=post_data, proxies=proxyDict)

    return(0)

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
