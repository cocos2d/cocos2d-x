import os
import json
import requests
import jenkinsapi
from jenkinsapi.jenkins import Jenkins
from jenkinsapi.constants import STATUS_SUCCESS
from email.mime.text import MIMEText
import smtplib
def send_mail(sub,title,content):
    #to_list = os.environ['EMAIL_LIST'].split(' ')
    mail_user = os.environ['EMAIL_USER']
    mail_pass = os.environ['EMAIL_PWD']
    to_list = os.environ['EMAIL_LIST'].split(' ')
    mail_postfix = 'gmail.com'
    me = mail_user + "<" + mail_user + "@" + mail_postfix + ">"
    msg = MIMEText(content, _subtype='plain', _charset='gb2312')
    msg['Subject'] = sub
    msg['From'] = me
    msg['To'] = " ".join(to_list)
    print 'to users:', msg['To']
    msg['Content'] = 'test'
    try:
        s = smtplib.SMTP('smtp.gmail.com', 587)
        s.ehlo()
        s.starttls()
        s.login(mail_user,mail_pass)
        s.sendmail(me, to_list, str(msg))
        print 'info:', me, to_list, str(msg)
        s.close()
        return True
    except Exception, e:
        print str(e)
        return False

def sendEmail(pr, html_url, target_url):
	sub = "Pull request #" + str(pr) + " build is failed!"
	title = "build failed!"
	content = 'to view build result, check:\r\n'+target_url + '\r\nYou can view the failed pr at:\r\n'+html_url
	send_mail(sub, title, content)

payload_str = os.environ['payload']
payload_str = payload_str.decode('utf-8','ignore')
#parse to json obj
payload = json.loads(payload_str)
#pr = payload['pull_request']
url = payload['html_url']
print "build pr:" + url
pr_num = payload['number']
#get statuses url
statuses_url = payload['statuses_url']

J = Jenkins(os.environ['JENKINS_URL'])
target_url = os.environ['BUILD_URL']
build_number = int(os.environ['BUILD_NUMBER'])
data = {"state":"pending", "target_url":target_url, "context":"Jenkins CI", "description":"Build finished!"}
access_token = os.environ['GITHUB_ACCESS_TOKEN']
Headers = {"Authorization":"token " + access_token} 

result = J[os.environ['JOB_NAME']].get_build(build_number).get_status()

if(result == STATUS_SUCCESS):
    data['state'] = "success"
    data['description'] = "Build successfully!"
else:
    data['state'] = "failure"
    data['description'] = "Build failed!"
    sendEmail(pr_num, url, target_url)
http_proxy = ''
if(os.environ.has_key('HTTP_PROXY')):
    http_proxy = os.environ['HTTP_PROXY']
proxyDict = {'http':http_proxy,'https':http_proxy}
requests.post(statuses_url, data=json.dumps(data), headers=Headers, proxies = proxyDict)
