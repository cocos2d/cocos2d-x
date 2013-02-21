#!/usr/bin/python
# handle_project_files.py for BlackBerry
# Copyright (c) 2012 cocos2d-x.org
# Author: Zhe WANG

# BlackBerry

import os
import shutil

def handle_project_files(context):    
    # determine proj_path
    proj_path = context["dst_project_path"] + "/proj.marmalade/"
                        
    # rename files and folders
    os.rename(proj_path + context["src_project_name"] + ".mkb",
              proj_path + context["dst_project_name"] + ".mkb" )


    # done!
    print "proj.blackberry  : Done!"
