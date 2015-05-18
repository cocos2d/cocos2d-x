import os
import sys
import traceback

# -------------- main --------------
if __name__ == '__main__':
    sys_ret = 0
    try:
        jenkins_script_path = "tools" + os.sep + "jenkins-scripts" + os.sep + "do-pull-request-builder.py"
        sys_ret = os.system("python " + jenkins_script_path)
    except:
        traceback.print_exc()
        sys_ret = 1
    finally:
        if sys_ret != 0:
            sys.exit(1)
        else:
            sys.exit(0)
