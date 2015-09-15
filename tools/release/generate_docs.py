#!/usr/bin/env python
# -*- coding: utf-8 -*-
#

import os, time
import utils
import shutil

from argparse import ArgumentParser

AVAILABLE_LANGUAGES = ['en', 'zh']

DOCUMENT_CONFIG = {
    'en' : 'docs/doxygen_white_book_en.config',
    'zh' : 'docs/doxygen_white_book_zh.config'
}

OUTPUT_DIR = 'docs'
GENERATE_FOLDER_NAME = 'html'

class Generator:
    def __init__(self, args):
        current_dir = os.path.normpath(os.path.realpath(os.path.dirname(__file__)))
        self.engine_root = os.path.normpath(os.path.join(current_dir, os.path.pardir, os.path.pardir))
        self.doxygen = self.get_real_path(args.doxygen_path)

        if args.language is None:
            self.languanges = AVAILABLE_LANGUAGES
        else:
            self.languanges = args.language

        self.do_upload = args.do_upload
        self.ftp_ip = args.ftp_ip
        self.ftp_folder = args.ftp_folder

    def get_real_path(self, p):
        ret = os.path.expanduser(p)
        if not os.path.isabs(ret):
            ret = os.path.abspath(ret)

        ret = os.path.normpath(ret)
        return ret

    def uploadFile(self, file, dest, ip = None, fileName = None):
        from uploadfile import Upload
        upload = Upload()
        upload.upload(file, dest, ip, fileName)

    def do_generate(self):
        if not os.path.isfile(self.doxygen):
            print('%s is not a valid file.' % self.doxygen)
            return

        if self.do_upload:
            if self.ftp_ip is None:
                print('To upload file, please specify the ftp ip by "--ftp-ip".')
                return

            if self.ftp_folder is None:
                print('To upload file, please specify the ftp folder by "--ftp-folder".')
                return

        out_dir = os.path.join(self.engine_root, OUTPUT_DIR)
        engine_version = utils.get_src_engine_version(self.engine_root)
        engine_version = engine_version[10:]
        timeStr = time.strftime("%Y%m%d%H%M%S", time.localtime(time.time()))
        for l in self.languanges:
            out_html_path = os.path.join(out_dir, GENERATE_FOLDER_NAME)
            folder_with_langugae = "%s-%s" % (GENERATE_FOLDER_NAME, l)
            if os.path.exists(out_html_path):
                shutil.rmtree(out_html_path)

            # generate documents
            config_file = os.path.join(self.engine_root, DOCUMENT_CONFIG[l])
            gen_cmd = '%s %s' % (self.doxygen, config_file)
            utils.execute_command(gen_cmd, cwd=out_dir)

            new_path = os.path.join(out_dir, folder_with_langugae)
            if os.path.exists(new_path):
                shutil.rmtree(new_path)
            shutil.copytree(out_html_path, os.path.join(new_path, folder_with_langugae))

            # zip the documents
            zip_file_path = os.path.join(out_dir, '%s.zip' % folder_with_langugae)
            if os.path.exists(zip_file_path):
                os.remove(zip_file_path)
            utils.zip_dir(new_path, zip_file_path)

            # do upload
            if self.do_upload:
                new_name = '%s-v%s-%s.zip' % (folder_with_langugae, engine_version, timeStr)
                self.uploadFile(zip_file_path, self.ftp_folder, self.ftp_ip, new_name)

if __name__ == "__main__":
    parser = ArgumentParser(description="The tool for generating documents by doxygen.")
    parser.add_argument('-t', dest='doxygen_path', required=True, help='Specify the path of doxygen tool.')

    group_doc = parser.add_argument_group('Document Related')
    group_doc.add_argument('-l', dest='language', action="append", choices=AVAILABLE_LANGUAGES, help='Specify the language of document. Default generate all languages.')

    group_upload = parser.add_argument_group('Upload Related')
    group_upload.add_argument('--do-upload', dest='do_upload', action="store_true", help='Upload the generated files.')
    group_upload.add_argument('--ftp-ip', dest='ftp_ip', help='Specify the ip address of ftp.')
    group_upload.add_argument('--ftp-folder', dest='ftp_folder', help='Specify the target folder of ftp.')

    (args, unknown) = parser.parse_known_args()

    generator = Generator(args)
    generator.do_generate()
