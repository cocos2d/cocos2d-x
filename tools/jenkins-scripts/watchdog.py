import jenkinsapi
from jenkinsapi.jenkins import Jenkins
from jenkinsapi.node import Node
import sys
import time
import os
from email.mime.text import MIMEText
import smtplib
import requests

def send_mail(sub,title,content):
    to_list = os.environ['EMAIL_LIST'].split(' ')
    mail_user = os.environ['EMAIL_USER']
    mail_pass = os.environ['EMAIL_PWD']
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

def sendEmail(msg):
    send_mail("Jenkins node " + msg + " is offline", 'for offline.', msg + ' is offline')

def rebuild_jobs(build):
    rebuild_jobs = os.environ['REBUILD_JOBS'].split(' ')
    trigger_urls = os.environ['JOB_TRIGGER_URLS'].split(' ')
    for i, rebuild_job in enumerate(rebuild_jobs):
        if rebuild_job in build.__str__():
            payload = build._poll()['actions'][0]['parameters'][0]['value']
            job_trigger_url = trigger_urls[i]
            post_data = {'payload': payload}
            requests.post(job_trigger_url, data=post_data)
            print 'build_job:', rebuild_job, 'rebuild : TRUE'

#check & kill dead buid
def build_time(_job,_threshold):
    #get jenkins-job-watchdog-threshold
    #Get last build running
    build = _job.get_last_build()
    running = build.is_running()
    print 'build_job:',_job,'running:',running
    if not running:
        return False
    
    #Get numerical ID of the last build.
    buildnu = _job.get_last_buildnumber()
    print "buildnumber:#",buildnu
    #get nowtime
    nowtime = int(time.time())
    print 'nowtime:', time.ctime(nowtime)
    #get build start time
    timestamp = build._poll()['timestamp']
    buildtime = int(timestamp)/1000
    print 'buildtime:', time.ctime(buildtime)
    subtime = (nowtime - buildtime)/60
    print 'subtime:', subtime, _threshold
    if subtime > _threshold:
        rebuild_jobs(build)
        #print 'subtime',subtime
        #kill dead buid
        build.stop()
    
def main():
    username = os.environ['JENKINS_ADMIN']
    password = os.environ['JENKINS_ADMIN_PW']
    J = Jenkins('http://115.28.134.83:8000',username,password)
    #get all jenkins jobs
    for key,job in J.iteritems():
        threshold = 0
        if(os.environ.has_key(key+'-threshold')):
            threshold = int(os.environ[key+'-threshold'])
        else:
            threshold = int(os.environ['jenkins-job-watchdog-threshold'])
        build_time(job,threshold)

    #check node status
    node_names = os.environ['NODE_LIST'].split(' ')
    for node_name in node_names:
        node = J.get_node(node_name)
        if node.is_online():
            print node_name, ' : is online'
        else:
            sendEmail(node_name)
            print node_name, ' : is offline'
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

