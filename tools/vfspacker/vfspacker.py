#!/usr/bin/env python

import os, sys, string
import plistlib
import json
import copy
import struct
    
def getFileInFolder(destPath):
    result = [string.replace(os.path.join(dp, f), os.path.join(destPath, ''), "") for dp, dn, filenames in os.walk(destPath) for f in filenames if os.path.split(f)[-1][0] != '.']
    return result
    
def getImmediateSubdirectories(destPath):
    return [name for name in os.listdir(destPath)
            if os.path.isdir(os.path.join(destPath, name))]
            
def addNullTerminatedString(array, string):
    array.extend(string.replace('\\', '/'))
    array.append(0)
    
def packFolder(source, dest, prefix):
    print "pack folder:", source
    print "output:", dest
    
    fileList = getFileInFolder(source)
    fileNamesData = bytearray()
    fileHeadersData = bytearray()
    dataOffset = 0;
    for file in fileList:
        len(fileNamesData)
        print "    ", file
        fileSize = os.stat(os.path.join(source, file)).st_size
        fileHeadersData.extend(struct.pack('<IIII', len(fileNamesData), fileSize, dataOffset, 0))
        dataOffset += fileSize
        addNullTerminatedString(fileNamesData, os.path.join(prefix, file).replace('\\', '/'))
        
    mod = len(fileNamesData)%4
    if mod > 0:
        for i in range(0, 4-mod):
            fileNamesData.append(0)
            
    with open(os.path.join(destPath, dest), 'w') as outfile:
        outfile.write(struct.pack('<4sIIII', "cxar", 0, 1, len(fileList), len(fileNamesData)))
        outfile.write(fileHeadersData)
        outfile.write(fileNamesData)
        for file in fileList:
            with open(os.path.join(source, file), 'r') as input:
                outfile.write(input.read())

if __name__ == "__main__":
    destPath = os.path.dirname(os.path.abspath(__file__))
    if len(sys.argv) > 1:
        destPath = os.path.abspath(sys.argv[1])
        
    import argparse
    
    parser = argparse.ArgumentParser(description='Create VFS file from folder')
    parser.add_argument('-p', '--prefix', default='', help='path prefix for all files')
    parser.add_argument('-s', '--single', action='store_true', help='single folder')
    parser.add_argument('source_path', default=None, nargs='?', help='source folder path')
    
    args = parser.parse_args()
    
    destPath = args.source_path
    if destPath == None:
        destPath = os.path.dirname(os.path.abspath(__file__))
    
    args = parser.parse_args()
    
    prefix = args.prefix.replace('\\', '/')
    if not prefix or prefix[-1]!='/':
        prefix += '/'
        
    print "prefix:", prefix
        
    if args.single:
        folder, name = os.path.split(destPath)
        packFolder(destPath, os.path.join(folder, name + ".bin"), prefix)
    else:
        listPackets = getImmediateSubdirectories(destPath)
        for packet in listPackets:
            packFolder(os.path.join(destPath, packet), os.path.join(destPath, packet + ".bin"), args.prefix)


