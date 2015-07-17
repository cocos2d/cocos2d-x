#Cocos2D-X test project daily build

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

if('language' in os.environ):
    language = os.environ['language']
else:
    language = 'lua'

if('daily_build_type' in os.environ):
    daily_build_type = os.environ['daily_build_type']
else:
    daily_build_type = 'tests'
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
    jenkins_script_path = "tools" + os.sep + "jenkins-scripts" + os.sep + "slave-scripts" + os.sep + daily_build_type + os.sep

    if(branch == 'v3' or branch == 'v4-develop'):
        slave_build_scripts = ""
        if(node_name == 'android') or (node_name == 'android_bak'):
            slave_build_scripts = jenkins_script_path + "android-build.sh "
        elif(node_name == 'win32' or node_name == 'win32_win7' or node_name == 'win32_bak'):
            if daily_build_type == "runtime" or daily_build_type == "templates":
                slave_build_scripts = jenkins_script_path + "win32-" + language + ".bat "
            else:
                slave_build_scripts = jenkins_script_path + "win32-build.bat "
        elif(node_name == 'windows-universal' or node_name == 'windows-universal_bak'):
            if daily_build_type == "runtime" or daily_build_type == "templates":
                slave_build_scripts = jenkins_script_path + "windows-universal-" + language + ".bat "
            else:
                slave_build_scripts = jenkins_script_path + "windows-universal.bat "
        elif(node_name == 'ios_mac' or node_name == 'ios' or node_name == 'ios_bak'):
            slave_build_scripts = jenkins_script_path + "ios-build.sh "
        elif(node_name == 'mac' or node_name == 'mac_bak'):
            slave_build_scripts = jenkins_script_path + "mac-build.sh "
        elif(node_name == 'linux_centos' or node_name == 'linux' or node_name == 'linux_bak'):
            slave_build_scripts = jenkins_script_path + "linux-build.sh "
        elif(node_name == 'wp8'):
            if(branch != 'v4'):
                slave_build_scripts = jenkins_script_path + "wp8-v3.bat "

        if daily_build_type == 'templates':
            ret = os.system("python tools/cocos2d-console/bin/cocos.py new -l " + language)
        elif daily_build_type == 'runtime':
            ret = os.system("python tools/cocos2d-console/bin/cocos.py new -l " + language + " -t runtime")
        else:
            ret = 0
        slave_build_scripts += language
        ret = ret + os.system(slave_build_scripts)

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

    # #clean workspace, we don't won't clean the repository
    # if remote_build == 1:
    #     os.system("cd " + workspace)
    #     os.system("git reset --hard")
    #     os.system("git clean -xdf -f")
    # else:
    #     print "local build, no need to cleanup"

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
