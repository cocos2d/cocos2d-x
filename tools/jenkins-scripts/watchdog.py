import jenkinsapi
from jenkinsapi.jenkins import Jenkins
import sys
import time
import os

#check & kill dead buid
def build_time(_job):
    #get jenkins-job-watchdog-threshold
    threshold = os.environ['jenkins-job-watchdog-threshold']
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
    nowtime = time.strftime('%M',time.localtime(time.time()))
    #print 'nowtime:',nowtime
    #get build start time
    timeb = build.get_timestamp()
    #print 'buildtime:',str(timeb)[14:16]
    buildtime = int(str(timeb)[14:16])
    subtime = 0
    if int(nowtime) >= buildtime:
        subtime = int(nowtime)-buildtime
    else:
        subtime = 60-buildtime+int(nowtime)
    if subtime > threshold:
        #print 'subtime',subtime
        #kill dead buid
        build.stop()
    
def main():
    username = os.environ['username']
    password = os.environ['password']
    J = Jenkins('http://115.28.134.83:8000',username,password)
    #get all jenkins jobs
    for key,job in J.iteritems():
        build_time(job)
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

