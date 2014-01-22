#Github pull reqest builder for Jenkins 

import json
import re
import os
import requests
import sys
import traceback

def main():
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

    pr = payload['pull_request']
    
    url = pr['html_url']
    print "url:" + url
    
    #get statuses url
    statuses_url = pr['statuses_url']

    #get pr target branch
    branch = pr['base']['ref']

    #set commit status to pending
    target_url = os.environ['BUILD_URL']
    
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

    job_trigger_url = os.environ['JOB_TRIGGER_URL']
    #send trigger and payload
    post_data = {'payload':""}
    post_data['payload']= payload_str
    requests.post(job_trigger_url, data=post_data)

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
