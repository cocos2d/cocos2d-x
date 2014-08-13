#!/usr/bin/env python
#coding=utf-8
#
# ./download-deps.py
#
# Download Cocos2D-X resources from github (https://github.com/cocos2d/cocos2d-x-3rd-party-libs-bin) and extract from ZIP
#
# Helps prevent repo bloat due to large binary files since they can
# be hosted separately.
#

"""****************************************************************************
Copyright (c) 2014 cocos2d-x.org
Copyright (c) 2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************"""

import os.path,zipfile
import shutil
import sys
import traceback
import distutils
import fileinput
import json

from optparse import OptionParser
from time import time
from sys import stdout
from distutils.errors import DistutilsError
from distutils.dir_util import copy_tree, remove_tree

class UnrecognizedFormat:
    def __init__(self, prompt):
        self._prompt = prompt
    def __str__(self):
        return self._prompt

class CocosZipInstaller(object):
    def __init__(self, workpath, config_path, version_path, remote_version_key = None):
        self._workpath = workpath
        self._config_path = config_path
        self._version_path = version_path

        data = self.load_json_file(config_path)

        self._current_version = data["version"]
        self._repo_name = data["repo_name"]
        try:
            self._move_dirs = data["move_dirs"]
        except:
            self._move_dirs = None
        self._filename = self._current_version + '.zip'
        self._url = data["repo_parent"] + self._repo_name + '/archive/' + self._filename
        self._zip_file_size = int(data["zip_file_size"])
        # 'v' letter was swallowed by github, so we need to substring it from the 2nd letter
        self._extracted_folder_name = os.path.join(self._workpath, self._repo_name + '-' + self._current_version[1:])

        try:
            data = self.load_json_file(version_path)
            if remote_version_key == None:
                self._remote_version = data["version"]
            else:
                self._remote_version = data[remote_version_key]
        except:
            print("==> version file doesn't exist")

    def get_input_value(self, prompt):
        ret = raw_input(prompt)
        ret.rstrip(" \t")
        return ret

    def download_file(self):
        print("==> Ready to download '%s' from '%s'" % (self._filename, self._url))
        import urllib2
        try:
            u = urllib2.urlopen(self._url)
        except urllib2.HTTPError as e:
            if e.code == 404:
                print("==> Error: Could not find the file from url: '%s'" % (self._url))
            print("==> Http request failed, error code: " + str(e.code) + ", reason: " + e.read())
            sys.exit(1)

        f = open(self._filename, 'wb')
        meta = u.info()
        content_len = meta.getheaders("Content-Length")
        file_size = 0
        if content_len and len(content_len) > 0:
            file_size = int(content_len[0])
        else:
            # github server may not reponse a header information which contains `Content-Length`,
            # therefore, the size needs to be written hardcode here. While server doesn't return
            # `Content-Length`, use it instead
            print("==> WARNING: Couldn't grab the file size from remote, use 'zip_file_size' section in '%s'" % self._config_path)
            file_size = self._zip_file_size

        print("==> Start to download, please wait ...")

        file_size_dl = 0
        block_sz = 8192
        block_size_per_second = 0
        old_time=time()

        while True:
            buffer = u.read(block_sz)
            if not buffer:
                break

            file_size_dl += len(buffer)
            block_size_per_second += len(buffer)
            f.write(buffer)
            new_time = time()
            if (new_time - old_time) > 1:
                speed = block_size_per_second / (new_time - old_time) / 1000.0
                status = ""
                if file_size != 0:
                    percent = file_size_dl * 100. / file_size
                    status = r"Downloaded: %6dK / Total: %dK, Percent: %3.2f%%, Speed: %6.2f KB/S " % (file_size_dl / 1000, file_size / 1000, percent, speed)
                else:
                    status = r"Downloaded: %6dK, Speed: %6.2f KB/S " % (file_size_dl / 1000, speed)

                status = status + chr(8)*(len(status)+1)
                print(status),
                sys.stdout.flush()
                block_size_per_second = 0
                old_time = new_time

        print("==> Downloading finished!")
        f.close()

    def ensure_directory(self, target):
        if not os.path.exists(target):
            os.mkdir(target)

    def unpack_zipfile(self, extract_dir):
        """Unpack zip `filename` to `extract_dir`

        Raises ``UnrecognizedFormat`` if `filename` is not a zipfile (as determined
        by ``zipfile.is_zipfile()``).
        """

        if not zipfile.is_zipfile(self._filename):
            raise UnrecognizedFormat("%s is not a zip file" % (self._filename))

        print("==> Extracting files, please wait ...")
        z = zipfile.ZipFile(self._filename)
        try:
            for info in z.infolist():
                name = info.filename

                # don't extract absolute paths or ones with .. in them
                if name.startswith('/') or '..' in name:
                    continue

                target = os.path.join(extract_dir, *name.split('/'))
                if not target:
                    continue
                if name.endswith('/'):
                    # directory
                    self.ensure_directory(target)
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
            print("==> Extraction done!")


    def ask_to_delete_downloaded_zip_file(self):
        ret = self.get_input_value("==> Do you want to keep '%s'? So you don't have to download it later. (yes/no): " % self._filename)
        ret = ret.strip()
        if ret != 'yes' and ret != 'y' and ret != 'no' and ret != 'n':
            print("==> Cache the dependency libraries by default")
            return False
        else:
            return True if ret == 'no' or ret =='n' else False

    def download_zip_file(self):
        if not os.path.isfile(self._filename):
            self.download_file()
        try:
            if not zipfile.is_zipfile(self._filename):
                raise UnrecognizedFormat("%s is not a zip file" % (self._filename))
        except UnrecognizedFormat as e:
            print("==> Unrecognized zip format from your local '%s' file!" % (self._filename))
            if os.path.isfile(self._filename):
                os.remove(self._filename)
            print("==> Download it from internet again, please wait...")
            self.download_zip_file()

    def need_to_update(self):
        if not os.path.isfile(self._version_path):
            return True

        with open(self._version_path) as data_file:
            data = json.load(data_file)

        if self._remote_version == self._current_version:
            return False
        return True

    def load_json_file(self, file_path):
        if not os.path.isfile(file_path):
            raise Exception("Could not find (%s)" % (file_path))

        with open(file_path) as data_file:
            data = json.load(data_file)
        return data

    def run(self, workpath, folder_for_extracting, remove_downloaded, force_update, download_only):
        if not force_update and not self.need_to_update():
            print("==> Not need to update!")
            return

        if os.path.exists(self._extracted_folder_name):
            shutil.rmtree(self._extracted_folder_name)

        self.download_zip_file()

        if not download_only:
            self.unpack_zipfile(self._workpath)
            print("==> Copying files...")
            if not os.path.exists(folder_for_extracting):
                os.mkdir(folder_for_extracting)
            distutils.dir_util.copy_tree(self._extracted_folder_name, folder_for_extracting)
            if self._move_dirs is not None:
                for srcDir in self._move_dirs.keys():
                    distDir = os.path.join( os.path.join(workpath, self._move_dirs[srcDir]), srcDir)
                    if os.path.exists(distDir):
                        shutil.rmtree(distDir)
                    shutil.move( os.path.join(folder_for_extracting, srcDir), distDir)
            print("==> Cleaning...")
            if os.path.exists(self._extracted_folder_name):
                shutil.rmtree(self._extracted_folder_name)
            if os.path.isfile(self._filename):
                if remove_downloaded != None:
                    if remove_downloaded == 'yes':
                        os.remove(self._filename)
                elif self.ask_to_delete_downloaded_zip_file():
                    os.remove(self._filename)
        else:
            print("==> Download (%s) finish!" % self._filename)


def _check_python_version():
    major_ver = sys.version_info[0]
    if major_ver > 2:
        print ("The python version is %d.%d. But python 2.x is required. (Version 2.7 is well tested)\n"
               "Download it here: https://www.python.org/" % (major_ver, sys.version_info[1]))
        return False

    return True

def main():
    workpath = os.path.dirname(os.path.realpath(__file__))

    if not _check_python_version():
        exit()

    parser = OptionParser()
    parser.add_option('-r', '--remove-download',
                      action="store", type="string", dest='remove_downloaded', default=None,
                      help="Whether to remove downloaded zip file, 'yes' or 'no'")

    parser.add_option("-f", "--force-update",
                      action="store_true", dest="force_update", default=False,
                      help="Whether to force update the third party libraries")

    parser.add_option("-d", "--download-only",
                      action="store_true", dest="download_only", default=False,
                      help="Only download zip file of the third party libraries, will not extract it")

    (opts, args) = parser.parse_args()

    print("=======================================================")
    print("==> Prepare to download external libraries!")
    external_path = os.path.join(workpath, 'external')
    installer = CocosZipInstaller(workpath, os.path.join(workpath, 'external', 'config.json'), os.path.join(workpath, 'external', 'version.json'), "prebuilt_libs_version")
    installer.run(workpath,external_path, opts.remove_downloaded, opts.force_update, opts.download_only)

    print("=======================================================")
    print("==> Prepare to download lua runtime binaries")
    runtime_path = os.path.join(workpath, 'templates', 'lua-template-runtime', 'runtime')
    installer = CocosZipInstaller(workpath, os.path.join(runtime_path, 'config.json'), os.path.join(runtime_path, 'version.json'))
    installer.run(workpath, runtime_path, opts.remove_downloaded, opts.force_update, opts.download_only)

# -------------- main --------------
if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        traceback.print_exc()
        sys.exit(1)
