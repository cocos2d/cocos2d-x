import os
import json
import requests
import jenkinsapi
from jenkinsapi.jenkins import Jenkins
from jenkinsapi.constants import STATUS_SUCCESS

payload_str = os.environ['payload']
payload_str = payload_str.decode('utf-8','ignore')
#parse to json obj
payload = json.loads(payload_str)
#pr = payload['pull_request']
url = payload['html_url']
print "build pr:" + url
#get comments url
comments_url = payload['comments_url']

J = Jenkins(os.environ['JENKINS_URL'])
target_url = os.environ['BUILD_URL']
build_number = int(os.environ['BUILD_NUMBER'])
data = {}
access_token = os.environ['GITHUB_COMMENT_ACCESS_TOKEN']
Headers = {"Authorization":"token " + access_token} 

result = J[os.environ['JOB_NAME']].get_build(build_number).get_status()

if(result == STATUS_SUCCESS):
    data['body'] = "Emptytest run successfully: " + target_url
else:
    data['body'] = "Emptytest failed: " + target_url

requests.post(comments_url, data=json.dumps(data), headers=Headers)
