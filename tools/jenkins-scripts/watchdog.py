import jenkinsapi
from jenkinsapi.jenkins import Jenkins
import sys
import time
import os

def interval_time(time1, time2):
    arr1 = str(time1).split(':')
    arr2 = str(time2).split(':')
    hour = int(arr1[0]) - int(arr2[0])
    minute = int(arr1[1]) - int(arr2[1])
    return hour*60+minute

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
    nowtime = time.strftime('%H:%M',time.localtime(time.time()))
    print 'nowtime:', nowtime
    #get build start time
    timestamp = build._poll()['timestamp']
    timeb = time.ctime(timestamp/1000)
    buildtime = str(timeb)[11:16]
    print 'buildtime:', buildtime
    subtime = interval_time(nowtime, buildtime)
    print 'subtime:', subtime, _threshold
    if subtime > _threshold:
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

