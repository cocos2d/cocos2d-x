#!/usr/bin/env python
#coding=utf-8
#
# ./download-deps.py
#
# Download Cocos2D-X resources from github (https://github.com/minggo/cocos2d-x-resources) and extract from ZIP
#
# Helps prevent repo bloat due to large binary files since they can
# be hosted separately.
#

import urllib2
import os.path,zipfile
import shutil
import sys
import traceback
from sys import stdout

prefix = 'https://codeload.github.com/minggo/cocos2d-x-resources/zip/'
filename = 'cocos2d-x-deps-v3-1'
extracted_folder_name='cocos2d-x-resources-' + filename

def download_file(url, file_name):
    u = urllib2.urlopen(url)
    f = open(file_name, 'wb')
    meta = u.info()
    #file_size = int(meta.getheaders("Content-Length")[0])
    print("Downloading: %s , please wait ... " % (file_name))

   # file_size_dl = 0
    block_sz = 8192
    while True:
        buffer = u.read(block_sz)
        if not buffer:
            break

        #file_size_dl += len(buffer)
        f.write(buffer)
        #status = r"%10d  [%3.2f%%]" % (file_size_dl, file_size_dl * 100. / file_size)
        #status = status + chr(8)*(len(status)+1)
        #print(status),
    f.close()

def unzip(src,dst):
    zf = zipfile.ZipFile(src)
    for file in zf.filelist:
        name = file.filename
        perm = ((file.external_attr >> 16L) & 0777)

        if name.endswith('/'):
            outfile = os.path.join(dst, name)
            if not os.path.exists(outfile):
                os.mkdir(outfile, perm)
        else:
            outfile = os.path.join(dst, name)
            fh = os.open(outfile, os.O_CREAT | os.O_WRONLY, perm)
            os.write(fh, zf.read(name))
            os.close(fh)
    zf.close()

def copy_files(src, dst):
    for item in os.listdir(src):
        path = os.path.join(src, item)
        if os.path.isfile(path):
            shutil.copy(path, dst)
        elif os.path.isdir(path):
            new_dst = os.path.join(dst, item)
            if not os.path.exists(new_dst):
                os.mkdir(new_dst)
            copy_files(path, new_dst)

def main():
    download_file(prefix+filename, filename+'.zip')
    workpath = os.path.dirname(os.path.realpath(__file__))
    print("Extracting files, please wait ...")
    unzip(filename+'.zip', workpath)
    copy_files(extracted_folder_name, workpath)
    print("Cleaning ...")
    if os.path.isfile(filename+'.zip'):
        os.remove(filename+'.zip')
    if os.path.exists(extracted_folder_name):
        shutil.rmtree(extracted_folder_name)
    print("DONE! Cheers!")

# -------------- main --------------
if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        traceback.print_exc()
        sys.exit(1)
