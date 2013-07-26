#! /usr/bin/evn python
# filename = create-multi-platform-projects.py

import os
from tools.project_creator import create_project

if __name__ == '__main__':
    os.chdir(os.getcwd()+'/tools/project_creator/')
    create_project.createPlatformProjects()
