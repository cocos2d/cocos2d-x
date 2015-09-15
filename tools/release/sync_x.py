#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# cocos2d-x repo: https://github.com/cocos2d/cocos2d-x
#
#
import utils
import os
import ConfigParser
import io

from argparse import ArgumentParser

###
DEFAULT_REPO_BRANCH = "v3"
DEFAULT_REPO_REMOTE = "origin"
###

class Synchronizer(object):

    def __init__(self, repo_dir, repo_tag=None, repo_branch=DEFAULT_REPO_BRANCH, remote_name=DEFAULT_REPO_REMOTE):
        self.repo_dir = repo_dir
        self.repo_tag = repo_tag
        self.remote_name = remote_name
        self.repo_branch = repo_branch

    def _repo_cmd_recursive(self, repo_dir, repo_cmd):
        utils.execute_command(repo_cmd, cwd=repo_dir)

        # do action in submodules
        cfg_file = os.path.join(repo_dir, ".gitmodules")
        if os.path.exists(cfg_file):
            file_open = open(cfg_file)
            str_data = file_open.read()
            file_open.close()

            str_can_parsed = str_data.replace("\t", "")
            str_can_parsed = str_can_parsed.replace(" ", "")
            cp = ConfigParser.ConfigParser(allow_no_value=True)
            cp.optionxform = str
            cp.readfp(io.BytesIO(str_can_parsed))

            for s in cp.sections():
                sub_dir = cp.get(s, "path")
                module_dir = os.path.join(repo_dir, sub_dir)
                if os.path.isdir(module_dir):
                    self._repo_cmd_recursive(module_dir, repo_cmd)

    def do_sync(self):
        # reset the repo
        self._repo_cmd_recursive(self.repo_dir, 'git reset --hard')

        # fetch remote
        utils.execute_command('git fetch %s' % self.remote_name, self.repo_dir)

        if self.repo_tag is None:
            # pull the latest code of specified branch
            utils.execute_command("git checkout -B %s --no-track %s/%s" % (self.repo_branch, self.remote_name, self.repo_branch), self.repo_dir)
            self._repo_cmd_recursive(self.repo_dir, 'git reset --hard')
            utils.execute_command("git pull %s %s" % (self.remote_name, self.repo_branch), self.repo_dir)
        else:
            # checkout the specified tag
            utils.execute_command("git fetch %s -t" % self.remote_name, self.repo_dir)
            utils.execute_command("git checkout -B %s tags/%s" % (self.repo_tag, self.repo_tag), self.repo_dir)
            self._repo_cmd_recursive(self.repo_dir, 'git reset --hard')

        utils.execute_command("git submodule update --init", self.repo_dir)

if __name__ == "__main__":
    parser = ArgumentParser(description="Sync code from cocos2d-x.")
    parser.add_argument('-e', dest='repo_path', required=True, help='Set the repo path of cocos2d-x.')
    parser.add_argument('-b', dest='branch', default=DEFAULT_REPO_BRANCH, help='Specify the branch of cocos2d-x engine repo.')
    parser.add_argument('-t', dest='tag', help='Specify the tag of cocos2d-x engine repo.')
    parser.add_argument('--remote', dest='remote_name', default=DEFAULT_REPO_REMOTE,help='Specify the remote name of cocos2d-x engine repo.')
    (args, unknown) = parser.parse_known_args()

    if len(unknown) > 0:
        print("unknown arguments: %s" % unknown)

    gen_obj = Synchronizer(args.repo_path, args.tag, args.branch, args.remote_name)
    gen_obj.do_sync()
