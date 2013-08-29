import os
import shutil
from optparse import OptionParser

def cccopy(sourcePath, destPath):
    for root, dirs, files in os.walk(sourcePath):
        #figure out where we're going
        dest = destPath + root.replace(sourcePath, '')
        destAbsPath = os.path.abspath(destPath)
        #if we're in a directory that doesn't exist in the destination folder then create a new folder
        if not os.path.isdir(dest):
            os.mkdir(dest)
            print os.path.abspath(dest).replace(destAbsPath, '')[1:] + ' directory created.'

        #loop through all files in the directory
        for f in files:
            #compute current (old) & new file locations
            oldLoc = root + "/" + f
            newLoc = dest + "/" + f

            if not os.path.isfile(newLoc):
                try:
                    shutil.copy2(oldLoc, newLoc)
                    print os.path.abspath(newLoc).replace(destAbsPath,'')[1:] + ' copied.'
                except IOError:
                    print os.path.abspath(newLoc).replace(destAbsPath,'')[1:] + ' already exists.'

                
                
# main
def main():
    # parse options
    parser = OptionParser(usage="%prog [options]") 
    parser.add_option("-s", "--sourcePath", action="store", help="Source path", dest="sourcePath")
    parser.add_option("-d", "--destPath", action="store", help="Destination path", dest="destPath")    
    
    (options, args) = parser.parse_args()
    	
    if options.sourcePath and options.destPath:
         cccopy(options.sourcePath, options.destPath)
    else:
        parser.error("")

## entry
if __name__ == "__main__":
    main()