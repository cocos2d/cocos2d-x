import jenkinsapi
from jenkinsapi.jenkins import Jenkins
import sys
import time
import os

def main():
    
    J = Jenkins('http://115.28.134.83:8000')
    job = J['cocos-2dx-pull-request-build']
    duration = os.environ['duration']
    #Get the numerical ID of the last build.
    buildnu = job.get_last_buildnumber()
    #Get the last build
    build = job.get_last_build()
    #Get the build running
    running = build.is_running()
    print 'running:',running

    if not running:
        return False
    print "buildnumber:#",buildnu
    nowtime = time.strftime('%M',time.localtime(time.time()))
    #print 'nowtime:',nowtime
    timeb = build.get_timestamp()
    #print 'buildtime:',str(timeb)[14:16]
    buildtime = int(str(timeb)[14:16])
    subtime = 0
    if int(nowtime) >= buildtime:
        subtime = int(nowtime)-buildtime
    else:
        subtime = 60-buildtime+int(nowtime)
    if subtime > duration:
        #print 'subtime',subtime
        build.stop()
    
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
