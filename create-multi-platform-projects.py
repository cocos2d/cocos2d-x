#!/usr/bin/env python
# filename = create-multi-platform-projects.py

import os
from tools.project_creator import create_project

if __name__ == '__main__':
    root = os.path.abspath(os.path.dirname(__file__))
    os.chdir(os.path.join(root, 'tools/project_creator/'))
    create_project.createPlatformProjects()
