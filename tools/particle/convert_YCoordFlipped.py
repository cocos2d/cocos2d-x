#!/usr/bin/python
#ConvertYCoordFlipped.py

import plistlib
import os.path
import argparse
import glob
import shutil

#keys in dictionary
metaDataKey = 'metaData'
yCoordFlippedConvertedKey = 'yCoordFlippedConverted'
yCoordFlippedKey = 'yCoordFlipped'

#check if the particle file has been converted
def checkFlippedConvertFlag(plistDict):
    if(not plistDict.has_key(metaDataKey)):
        return False
    else:
        metaDict = plistDict.get(metaDataKey)
        if(not metaDict.has_key(yCoordFlippedConvertedKey)):
            return False
        else:
            return metaDict.get(yCoordFlippedConvertedKey) is 1

#write flag to indicate to file has been converted
def writeFlippedConvertFlag(plistDict):
    metaDict = dict()
    metaDict.update(yCoordFlippedConverted = 1)
    plistDict.update(metaData = metaDict)

#process file
def processConvertFile(filename):
    #print a line to seperate files
    print ('')
    if(not os.path.isfile(filename)):
        print(filename + ' dose not exist!')
        return
    print('Begin process particle file: ' + filename)
    fp = open(filename, 'r')
    pl = plistlib.readPlist(fp) 

    if (not pl.has_key(yCoordFlippedKey)):
        print('Skip plist file: ' + filename + ' for there is no key for yCoordFlipped,')
    else:
        if(not checkFlippedConvertFlag(pl)):
            backupFileName = filename+'.backup'
            print('Write backup file to ' + backupFileName)
            shutil.copyfile(filename,backupFileName)
            print('converting...')
            pl[yCoordFlippedKey] = -pl[yCoordFlippedKey]
            writeFlippedConvertFlag(pl)
            print('converted...')
            print('Write new plist file to ' + filename)
            plistlib.writePlist(pl,filename)
        else:
            print('Skip a converted file ' + filename)

# -------------- entrance --------------
if __name__ == '__main__':
    argparser = argparse.ArgumentParser()
    argparser.add_argument("file", nargs = "+",help = "specify a file or a patten")
    #argparser.add_argument("-r", "--recursive",action = "store_true", help = "recursive folder or not")
    args = argparser.parse_args()

    for file in args.file:
        processConvertFile(file)
