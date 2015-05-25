#!/usr/bin/python
# ----------------------------------------------------------------------------
# extend methods for copy files/dirs
#
# Copyright 2014 (C) zhangbin
#
# License: MIT
# ----------------------------------------------------------------------------

import os
import shutil

def copy_files_in_dir(src, dst):

    for item in os.listdir(src):
        path = os.path.join(src, item)
        if os.path.isfile(path):
            shutil.copy(path, dst)
        if os.path.isdir(path):
            new_dst = os.path.join(dst, item)
            if not os.path.isdir(new_dst):
                os.makedirs(new_dst)
            copy_files_in_dir(path, new_dst)

def copy_files_with_config(config, src_root, dst_root):
    src_dir = config["from"]
    dst_dir = config["to"]

    src_dir = os.path.join(src_root, src_dir)
    dst_dir = os.path.join(dst_root, dst_dir)

    include_rules = None
    if config.has_key("include"):
        include_rules = config["include"]
        include_rules = convert_rules(include_rules)

    exclude_rules = None
    if config.has_key("exclude"):
        exclude_rules = config["exclude"]
        exclude_rules = convert_rules(exclude_rules)

    copy_files_with_rules(src_dir, src_dir, dst_dir, include_rules, exclude_rules)

def copy_files_with_rules(src_rootDir, src, dst, include = None, exclude = None):
    if os.path.isfile(src):
        if not os.path.exists(dst):
            os.makedirs(dst)
        shutil.copy(src, dst)
        return

    if (include is None) and (exclude is None):
        if not os.path.exists(dst):
            os.makedirs(dst)
        copy_files_in_dir(src, dst)
    elif (include is not None):
        # have include
        for name in os.listdir(src):
            abs_path = os.path.join(src, name)
            rel_path = os.path.relpath(abs_path, src_rootDir)
            if os.path.isdir(abs_path):
                sub_dst = os.path.join(dst, name)
                copy_files_with_rules(src_rootDir, abs_path, sub_dst, include = include)
            elif os.path.isfile(abs_path):
                if _in_rules(rel_path, include):
                    if not os.path.exists(dst):
                        os.makedirs(dst)
                    shutil.copy(abs_path, dst)
    elif (exclude is not None):
        # have exclude
        for name in os.listdir(src):
            abs_path = os.path.join(src, name)
            rel_path = os.path.relpath(abs_path, src_rootDir)
            if os.path.isdir(abs_path):
                sub_dst = os.path.join(dst, name)
                copy_files_with_rules(src_rootDir, abs_path, sub_dst, exclude = exclude)
            elif os.path.isfile(abs_path):
                if not _in_rules(rel_path, exclude):
                    if not os.path.exists(dst):
                        os.makedirs(dst)
                    shutil.copy(abs_path, dst)

def _in_rules(rel_path, rules):
    import re
    ret = False
    path_str = rel_path.replace("\\", "/")
    for rule in rules:
        if re.match(rule, path_str):
            ret = True

    return ret

def convert_rules(rules):
    ret_rules = []
    for rule in rules:
        ret = rule.replace('.', '\\.')
        ret = ret.replace('*', '.*')
        ret = "%s" % ret
        ret_rules.append(ret)

    return ret_rules
