#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# The entrance script of generating documents
#
# Author : Bill Zhang
# License : MIT

import sys, os
import utils
import generate_docs

from argparse import ArgumentParser

if __name__ == "__main__":
    parser = ArgumentParser(description="The tool for generating documents by doxygen.")
    parser.add_argument('-t', dest='doxygen_path', required=True, help='Specify the path of doxygen tool.')

    group_doc = parser.add_argument_group('Document Related')
    group_doc.add_argument('-l', dest='language', action="append", choices=generate_docs.AVAILABLE_LANGUAGES, help='Specify the language of document. Default generate all languages.')

    group_repo = parser.add_argument_group('Repository Related')
    group_repo.add_argument('-b', dest='branch', default='v3-doc', help='Specify the branch of cocos2d-x engine repo.')

    group_upload = parser.add_argument_group('Upload Related')
    group_upload.add_argument('--do-upload', dest='do_upload', action="store_true", help='Upload the generated files.')
    group_upload.add_argument('--ftp-ip', dest='ftp_ip', help='Specify the ip address of ftp.')
    group_upload.add_argument('--ftp-folder', dest='ftp_folder', help='Specify the target folder of ftp.')

    (args, unknown) = parser.parse_known_args()
    argv = sys.argv[1:]

    current_dir = os.path.normpath(os.path.realpath(os.path.dirname(__file__)))
    engine_path = os.path.normpath(os.path.join(current_dir, os.path.pardir, os.path.pardir))

    # Synchronize the code of repo
    sync_tool_path = os.path.join(current_dir, 'sync_x.py')
    sync_cmd = 'python "%s" -e "%s"' % (sync_tool_path, engine_path)
    if args.branch is not None:
        sync_cmd = '%s -b %s' % (sync_cmd, args.branch)
    utils.execute_command(sync_cmd)

    # Generate documents
    gendoc_tool_path = os.path.join(current_dir, 'generate_docs.py')
    gen_cmd = 'python "%s" %s' % (gendoc_tool_path, ' '.join(argv))
    utils.execute_command(gen_cmd)
