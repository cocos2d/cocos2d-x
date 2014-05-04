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
import distutils
from sys import stdout
from distutils.errors import DistutilsError
from distutils.dir_util import copy_tree, remove_tree

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

def default_filter(src,dst):
    """The default progress/filter callback; returns True for all files"""
    return dst

def ensure_directory(target):
    if not os.path.exists(target):
        os.mkdir(target)

def unpack_zipfile(filename, extract_dir, progress_filter=default_filter):
    """Unpack zip `filename` to `extract_dir`

    Raises ``UnrecognizedFormat`` if `filename` is not a zipfile (as determined
    by ``zipfile.is_zipfile()``).  See ``unpack_archive()`` for an explanation
    of the `progress_filter` argument.
    """

    if not zipfile.is_zipfile(filename):
        raise UnrecognizedFormat("%s is not a zip file" % (filename,))

    z = zipfile.ZipFile(filename)
    try:
        for info in z.infolist():
            name = info.filename

            # don't extract absolute paths or ones with .. in them
            if name.startswith('/') or '..' in name:
                continue

            target = os.path.join(extract_dir, *name.split('/'))
            target = progress_filter(name, target)
            if not target:
                continue
            if name.endswith('/'):
                # directory
                ensure_directory(target)
            else:
                # file
                data = z.read(info.filename)
                f = open(target,'wb')
                try:
                    f.write(data)
                finally:
                    f.close()
                    del data
            unix_attributes = info.external_attr >> 16
            if unix_attributes:
                os.chmod(target, unix_attributes)
    finally:
        z.close()

def main():
    download_file(prefix+filename, filename+'.zip')
    workpath = os.path.dirname(os.path.realpath(__file__))

    if os.path.exists(extracted_folder_name):
        shutil.rmtree(extracted_folder_name)

    print("Extracting files, please wait ...")
    unpack_zipfile(filename+'.zip', workpath)
    print("Extraction done!")
    print("Copying files ...")
    distutils.dir_util.copy_tree(extracted_folder_name, workpath)
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
