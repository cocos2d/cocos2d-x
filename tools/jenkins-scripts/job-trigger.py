#Github pull reqest builder for Jenkins 

import json
import re
import os
import requests
import sys
import traceback
from jenkinsapi.jenkins import Jenkins

http_proxy = ''
if(os.environ.has_key('HTTP_PROXY')):
    http_proxy = os.environ['HTTP_PROXY']
proxyDict = {'http':http_proxy,'https':http_proxy}

def check_queue_build(action, pr_num, statuses_url):
    username = os.environ['JENKINS_ADMIN']
    password = os.environ['JENKINS_ADMIN_PW']
    J = Jenkins('http://115.28.134.83:8000',username,password)
    queues = J.get_queue()
    for key,queue in queues.iteritems():
      q_payload_str = queue.get_parameters()['payload'].decode('utf-8','ignore')
      q_payload = json.loads(q_payload_str)
      q_pr_num = q_payload['number']
      q_statuses_url = q_payload['statuses_url']
      if(q_pr_num == pr_num):
        if(action == 'closed') or (q_statuses_url != statuses_url):
          queues.delete_item(queue)
          target_url = os.environ['JOB_PULL_REQUEST_BUILD_URL']
          data = {"state":"error", "target_url":target_url}
          access_token = os.environ['GITHUB_ACCESS_TOKEN']
          Headers = {"Authorization":"token " + access_token} 
          try:
              requests.post(statuses_url, data=json.dumps(data), headers=Headers, proxies = proxyDict)
          except:
              traceback.print_exc()

def main():
    #get payload from os env
    payload_str = os.environ['payload']
    #parse to json obj
    payload = json.loads(payload_str)

    #get pull number
    pr_num = payload['number']
    print 'pr_num:' + str(pr_num)
    payload_forword = {"number":pr_num}
    
    #build for pull request action 'open' and 'synchronize', skip 'close'
    action = payload['action']
    print 'action: ' + action
    payload_forword['action'] = action
    
    pr = payload['pull_request']
    url = pr['html_url']
    print "url:" + url
    payload_forword['html_url'] = url
    
    #get statuses url
    statuses_url = pr['statuses_url']
    payload_forword['statuses_url'] = statuses_url

    #get pr target branch
    branch = pr['base']['ref']
    payload_forword['branch'] = branch

    #set commit status to pending
    target_url = os.environ['JOB_PULL_REQUEST_BUILD_URL']

    try:    
        check_queue_build(action, pr_num, statuses_url)
    except:
        print 'Can not find build in queue'
    
    if(action == 'closed'):
        print 'pull request #' + str(pr_num) + ' is '+action+', no build triggered'
        return(0)
  
    r = requests.get(pr['url']+"/commits", proxies = proxyDict)
    commits = r.json()
    last_commit = commits[len(commits)-1]
    message = last_commit['commit']['message']

    pattern = re.compile("\[ci(\s+)skip\]", re.I)
    result_commit_title = pattern.search(message)

    title = pr['title']
    result_pr_title = pattern.search(title)
    if result_commit_title is not None or result_pr_title is not None:
        print 'skip build for pull request #' + str(pr_num)
        return(0)
    
    data = {"state":"pending", "target_url":target_url}
    access_token = os.environ['GITHUB_ACCESS_TOKEN']
    Headers = {"Authorization":"token " + access_token} 

    try:
        requests.post(statuses_url, data=json.dumps(data), headers=Headers, proxies = proxyDict)
    except:
        traceback.print_exc()

    job_trigger_url = os.environ['JOB_TRIGGER_URL']
    #send trigger and payload
    post_data = {'payload':""}
    post_data['payload']= json.dumps(payload_forword)
    requests.post(job_trigger_url, data=post_data, proxies = proxyDict)

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
