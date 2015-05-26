import os
import sys
import traceback
import json

branch = "v3"
node_name = "ios"

payload_str = os.environ['payload']
payload_str = payload_str.decode('utf-8', 'ignore')
#parse to json obj
payload = json.loads(payload_str)
pr_num = payload['number']

#get pr target branch
branch = payload['branch']
workspace = os.environ['WORKSPACE']
node_name = os.environ['NODE_NAME']

def download_3rd_libs(branch):
    #run download-deps.py
    print("prepare to downloading ...")
    os.system('python download-deps.py -r no')


def gen_scripting_bindings():
    global branch
    # Generate binding glue codes
    if(branch != 'v1' and branch != 'v2'):
        ret = os.system("python tools/jenkins-scripts/slave-scripts/gen_jsb.py")
    if(ret != 0):
        sys.exit(1)


def do_build_slaves():
    global branch
    global node_name

    jenkins_script_path = "tools" + os.sep + "jenkins-scripts" + os.sep + "slave-scripts" + os.sep
    js_tests_build_scripts = ""

    if(branch != 'v1' and branch != 'v2'):
        slave_build_scripts = ""
        if(node_name == 'android') or (node_name == 'android_bak'):
            slave_build_scripts = jenkins_script_path + "android-build.sh"
        elif(node_name == 'win32' or node_name == 'win32_win7' or node_name == 'win32_bak'):
            slave_build_scripts = jenkins_script_path + "win32-build.bat"
            js_tests_build_scripts = jenkins_script_path + "win32-js-build.bat"
        elif(node_name == 'windows-universal' or node_name == 'windows-universal_bak'):
            slave_build_scripts = jenkins_script_path + "windows-universal.bat"
            js_tests_build_scripts = jenkins_script_path + "windows-js-universal.bat"
        elif(node_name == 'ios_mac' or node_name == 'ios' or node_name == 'ios_bak'):
            slave_build_scripts = jenkins_script_path + "ios-build.sh"
            js_tests_build_scripts = jenkins_script_path + "ios-js-build.sh"
        elif(node_name == 'mac' or node_name == 'mac_bak'):
            slave_build_scripts = jenkins_script_path + "mac-build.sh"
            js_tests_build_scripts = jenkins_script_path + "mac-js-build.sh"
        elif(node_name == 'linux_centos' or node_name == 'linux' or node_name == 'linux_bak'):
            slave_build_scripts = jenkins_script_path + "linux-build.sh"
        elif(node_name == 'wp8'):
            if(branch != 'v4'):
                slave_build_scripts = jenkins_script_path + "wp8-v3.bat"

        ret = os.system(slave_build_scripts)
        js_test_ret = os.system(js_tests_build_scripts)
        ret = ret + js_test_ret

    #get build result
    print "build finished and return " + str(ret)
    return ret

def cleanup_workspace():
    global workspace
    global branch
    global pr_num
    #clean workspace
    os.system("cd " + workspace)
    os.system("git reset --hard")
    os.system("git clean -xdf -f")
    os.system("git checkout " + branch)
    os.system("git branch -D pull" + str(pr_num))

def main():
    download_3rd_libs(branch)
    #generate jsb and luabindings
    gen_scripting_bindings()
    #start build jobs on each slave
    ret = do_build_slaves()

    cleanup_workspace()

    exit_code = 1
    if ret == 0:
        exit_code = 0
    else:
        exit_code = 1

    return(exit_code)


# -------------- main --------------
if __name__ == '__main__':
    sys_ret = 0
    try:
        sys_ret = main()
    except:
        traceback.print_exc()
        sys_ret = 1
    finally:
        print "return value is " + str(sys_ret)
        if sys_ret != 0:
            sys.exit(1)
        else:
            sys.exit(0)
