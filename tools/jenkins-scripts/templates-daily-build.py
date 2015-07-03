#Cocos2D-X templates daily build scripts

import os
import sys
import traceback

# for local debugging purpose, you could change the value to 0 and run
# this scripts in your local machine
remote_build = 1

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
    node_name = 'mac'

if('build_mode' in os.environ):
    build_mode = os.environ['build_mode']
else:
    build_mode = "debug"

#valide build_type are 'template' and 'runtime'
if('build_type' in os.environ):
    build_type = os.environ['build_type']
else:
    build_type = 'template'

default_templates_types = ["cpp", "lua", "js"]
runtime_templates_types = ["lua", "js"]
default_templates_names = ["test_cpp", "test_lua", "test_js"]
runtime_template_names = ["test_rt_lua", "test_rt_js"]

def do_clean_up():
    for name in default_templates_names:
        commands = 'rm -rf ' + name
        os.system(commands)
    for name in runtime_template_names:
        commands = 'rm -rf ' + name
        os.system(commands)


def build_templates(mode, templates, is_runtime):
    ret = 0
    if(branch == 'v3' or branch == 'v4-develop'):
        do_clean_up()
        test_project_prefix = " test_"
        if is_runtime:
            test_project_prefix = " test_rt_"

        #build for default templates
        for type in templates:
            #create project
            create_project_commands = "cocos new  -l " + type
            if is_runtime:
                create_project_commands += " -t runtime " + test_project_prefix + type
            else:
                create_project_commands += test_project_prefix + type
            create_ret = os.system(create_project_commands)

            #create project failed
            if create_ret != 0:
                return 1

            ret += create_ret
            #compile
            compile_project_commands = "cocos compile -p " + node_name + " -s " + test_project_prefix + type + " --compile-script 0"
            build_mode_args = "  -m "
            if node_name == "android":
                build_mode_args = " --ndk-mode "
            build_mode_args += mode

            if node_name == "windows-universal":
                #run wp8.1 and windows 8.1
                # lua & js don't have runtime template
                if is_runtime:
                    continue
                wp_ret = os.system("cocos compile -p wp8_1 " + build_mode_args + " -s " + test_project_prefix + type + " --compile-script 0")
                winrt_ret = os.system("cocos compile -p metro " + build_mode_args + " -s " + test_project_prefix + type + " --compile-script 0")
                ret += wp_ret
                ret += winrt_ret
            else:
                if node_name == "android":
                    compile_project_commands += " --app-abi armeabi:armeabi-v7a:x86 "
                if node_name == "linux" and is_runtime:
                    continue
                compile_ret = os.system(compile_project_commands + build_mode_args)
                ret += compile_ret

    return ret


def main():
    #start build jobs on each slave
    default_build_type = default_templates_types
    default_flag = False
    if build_type == "runtime":
        default_build_type = runtime_templates_types
        default_flag = True
    ret = build_templates(build_mode, default_build_type, default_flag)

    print "build finished and return " + str(ret)

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
        sys.exit(sys_ret)
