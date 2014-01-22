import os
import json
import requests
import jenkinsapi
from jenkinsapi.jenkins import Jenkins

payload_str = os.environ['payload']
payload_str = payload_str.decode('utf-8','ignore')
#parse to json obj
payload = json.loads(payload_str)
pr = payload['pull_request']
#get statuses url
statuses_url = pr['statuses_url']
print statuses_url

J = Jenkins(os.environ['JENKINS_URL'])
target_url = os.environ['BUILD_URL']
data = {"state":"pending", "target_url":target_url}
access_token = os.environ['GITHUB_ACCESS_TOKEN']
Headers = {"Authorization":"token " + access_token} 


if(J[os.environ['JOB_NAME']].get_last_build().is_good()):
    data['state'] = "success"
else:
	data['state'] = "failure"

requests.post(statuses_url, data=json.dumps(data), headers=Headers)
