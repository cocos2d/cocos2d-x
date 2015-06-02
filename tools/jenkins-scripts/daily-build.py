#Github pull reqest builder for Jenkins

import os
import sys
import traceback

if('branch' in os.environ):
    branch = os.environ['branch']
else:
    branch = 'v4-develop'

if('WORKSPACE' in os.environ):
    workspace = os.environ['WORKSPACE']
else:
    workspace = "."

if('NODE_NAME' in os.environ):
    node_name = os.environ['NODE_NAME']
else:
    node_name = 'ios'
# for local debugging purpose, you could change the value to 0 and run
# this scripts in your local machine
remote_build = 1

def download_3rd_library():
    #run download-deps.py
    print("prepare to downloading ...")
    os.system('python download-deps.py -r no')


def sync_remote_repo():
    #reset path to workspace root
    os.system("cd " + workspace)

    #pull latest code
    os.system("git fetch origin " + branch)
    os.system("git checkout " + branch)
    os.system("git merge origin/" + branch)
    #clean workspace
    print "Before checkout: git clean -xdf -f"
    os.system("git clean -xdf -f")

    #update submodule
    git_update_submodule = "git submodule update --init --force"
    ret = os.system(git_update_submodule)
    if(ret != 0):
        sys.exit(ret)


def gen_scripting_bindings():
    # Generate binding glue codes
    if(branch == 'v3' or branch == 'v4-develop'):
        ret = os.system("python tools/jenkins-scripts/slave-scripts/gen_jsb.py")
    if(ret != 0):
        sys.exit(ret)


def do_build_slaves():
    jenkins_script_path = "tools" + os.sep + "jenkins-scripts" + os.sep + "slave-scripts" + os.sep
    js_tests_build_scripts = ""

    if(branch == 'v3' or branch == 'v4-develop'):
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


def main():
    if remote_build == 1:
        #syntronize local git repository with remote and merge the PR
        sync_remote_repo()
        #copy check_current_3rd_libs
        download_3rd_library()
        #generate jsb and luabindings
        gen_scripting_bindings()

    #start build jobs on each slave
    ret = do_build_slaves()

    exit_code = 1
    if ret == 0:
        exit_code = 0
    else:
        exit_code = 1

    #clean workspace
    if remote_build == 1:
        os.system("cd " + workspace)
        os.system("git reset --hard")
        os.system("git clean -xdf -f")
    else:
        print "local build, no need to cleanup"

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
        sys.exit(sys_ret)
