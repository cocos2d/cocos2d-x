#check latest pull request statuses, it no statuses found after 3 min, rebuild the pr
import os
import requests
import datetime
import re
import json
import sys
import traceback

url = 'https://api.github.com/repos/cocos2d/cocos2d-x/pulls?state=open&sort=created&direction=desc'
job_trigger_url=os.environ['JOB_PULL_REQUEST_BUILD_TRIGGER_URL']
access_token = os.environ['GITHUB_ACCESS_TOKEN']
Headers = {"Authorization":"token " + access_token} 
def main():
    r = requests.get(url,headers=Headers)
    payload = r.json()
    #print payload
    for pr in payload:
        pr_num = pr['number']
        r = requests.get(pr['url']+"/commits",headers=Headers)
            commits = r.json()
        #print commits
            last_commit = commits[len(commits)-1]
            message = last_commit['commit']['message']
        
        #print message
            pattern = re.compile("\[ci(\s+)skip\]", re.I)
            result_commit_title = pattern.search(message)

            title = pr['title']
            result_pr_title = pattern.search(title)
            if result_commit_title is not None or result_pr_title is not None:
                print 'skip build for pull request #' + str(pr_num)
                break
            #return(0)
        s = pr['statuses_url']
        update_time = pr['updated_at']
        #print pr_num
        #print s
        #print update_time
        t = datetime.datetime.strptime(update_time, "%Y-%m-%dT%H:%M:%SZ")
        now = datetime.datetime.utcnow()
        three_minutes = datetime.timedelta(seconds=3*60)
        if (t + three_minutes < now):
            #print pr_num
            statuses = requests.get(s, headers=Headers)
            #print statuses.json()
            if(len(statuses.json()) < 1):
                print pr_num
                payload_forward = {}
                payload_forward['number']=pr_num
                payload_forward['action']=pr['state']
                payload_forward['html_url']=pr['html_url']
                payload_forward['statuses_url']=pr['statuses_url']
                payload_forward['branch']=pr['base']['ref']
                print payload_forward
                post_data = {'payload':""}
                post_data['payload']= json.dumps(payload_forward)

                requests.post(job_trigger_url, data=post_data)

# -------------- main --------------
if __name__ == '__main__':
    sys_ret = 0
    try:
        main()
    except:
    traceback.print_exc()
    sys_ret = 1
    finally:
    sys.exit(sys_ret)

