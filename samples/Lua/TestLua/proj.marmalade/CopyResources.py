import os
import shutil

sourcePath  = '../../../../samples/Cpp/TestCpp/Resources/'
destPath  = '../../../../samples/Lua/TestLua/Resources/'

for root, dirs, files in os.walk(sourcePath):
    #figure out where we're going
    dest = destPath + root.replace(sourcePath, '')
    destAbsPath = os.path.abspath(destPath)
    #if we're in a directory that doesn't exist in the destination folder then create a new folder
    if not os.path.isdir(dest):
        os.mkdir(dest)
        print os.path.abspath(dest).replace(destAbsPath, '') + ' created'

    #loop through all files in the directory
    for f in files:
        #compute current (old) & new file locations
        oldLoc = root + "/" + f
        newLoc = dest + "/" + f

        if not os.path.isfile(newLoc):
            try:
                shutil.copy2(oldLoc, newLoc)
                print os.path.abspath(newLoc).replace(destAbsPath,'') + ' copied.'
            except IOError:
                print os.path.abspath(newLoc).replace(destAbsPath,'') + ' already exists'
