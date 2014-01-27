import os

language = ['cpp','lua','javascript']
base_path = 'tools/project-creator/'
create_project = base_path + 'create_project.py'
module_root = base_path + 'moduleTest'

# create project
for item in language:
    ret = os.system('python ' + create_project
                    + ' -n ' + 'module' + item
                    + ' -k ' + 'com.test.module.' + item
                    + ' -l ' + item
                    + ' -p ' + module_root)
    if(ret > 0):
        ret = 1
        exit(ret)

exit(0)
