import os

languages = ['cpp', 'lua', 'javascript']
base_path = 'tools/project-creator/'
create_project = base_path + 'create_project.py'
template_root = base_path + 'templateTest'

# create project
for item in languages:
    ret = os.system('python ' + create_project
                    + ' -n ' + 'template' + item
                    + ' -k ' + 'com.test.template.' + item
                    + ' -l ' + item
                    + ' -p ' + template_root)
    if(ret > 0):
        ret = 1
        exit(ret)

exit(0)
