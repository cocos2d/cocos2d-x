#!/bin/bash
# This script should be called by create-android-project.bat
# or should be runned in linux shell. It can not be runned under
# cygwin.
# Don't modify the script until you know what you do.

# set environment paramters

bash `pwd`/create-android-project.sh -linux $@
