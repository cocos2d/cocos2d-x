#!/usr/bin/python
# process_proj.py
# Copyright (c) 2012 cocos2d-x.org
# Author: WangZhe

import os

def process_proj(context):
    proj_path = context["project_path"] + context["dst_project_name"] + "/proj.win32/"
    
    # remove useless files.
    os.popen("rm -rf " + proj_path)
    print "proj.win32       : TBD, Python script for win32 hasn't been implemented yet. Call Microsoft for help :)"