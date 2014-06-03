import os
import json
import requests
import jenkinsapi
from jenkinsapi.jenkins import Jenkins
from jenkinsapi.constants import STATUS_SUCCESS

http_proxy = ''
if(os.environ.has_key('HTTP_PROXY')):
    http_proxy = os.environ['HTTP_PROXY']
payload_str = payload_str.decode('utf-8','ignore')
#parse to json obj
payload = json.loads(payload_str)
#pr = payload['pull_request']
url = payload['html_url']
print "build pr:" + url
#get statuses url
statuses_url = payload['statuses_url']

J = Jenkins(os.environ['JENKINS_URL'])
target_url = os.environ['BUILD_URL']
build_number = int(os.environ['BUILD_NUMBER'])
data = {"state":"pending", "target_url":target_url}
access_token = os.environ['GITHUB_ACCESS_TOKEN']
Headers = {"Authorization":"token " + access_token} 

result = J[os.environ['JOB_NAME']].get_build(build_number).get_status()

if(result == STATUS_SUCCESS):
    data['state'] = "success"
else:
    data['state'] = "failure"

http_proxy = os.environ['HTTP_PROXY']
proxyDict = {'http':http_proxy,'https':http_proxy}
requests.post(statuses_url, data=json.dumps(data), headers=Headers, proxies = proxyDict)
