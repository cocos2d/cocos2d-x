#!/usr/bin/env python

import os
import re
import sys

# list of extensions to replace
replace_extensions = [".cpp", ".h", ".hpp", ".cc", ".mm"]
files_to_skip = None
replace_type = None
skip_contents = ["CCPointMake", "CCSizeMake", "CCRectMake", "CCLOG", \
                 "CCLog", "CCAssert", "CCSkeleton"]

def try_to_replace(fname):
    if replace_type == "add_namespace":
        if fname.lower().endswith(".h"):
            return True
        return False
    else:
        if replace_extensions:
            for replace_extension in replace_extensions:
                if fname.lower().endswith(replace_extension):
                    return True
    return False


def replacement_member_variable(m):
    # print "group 2: ", m.group(2)
    name_prefix = m.group(3)
    first = name_prefix[0]
    second = ""

    if len(name_prefix) > 1:
        second = name_prefix[1]

    if first.isupper() and second.islower():
        first = first.lower()
        name_prefix = first + name_prefix[1:]
        return m.group(1) + "_" + name_prefix
    elif first.isupper() and second.isupper():
        return m.group(1) + "_" + name_prefix
    else:
        print "don't convert: ", m.group(1) + m.group(2) + m.group(3)
    if m.group(2) == "m_":
        return m.group(1) + "_" + name_prefix
    return m.group(1) + m.group(2) + m.group(3)


def remove_prefix_callback(m):
    pos = 0
    for skip_content in skip_contents:
        start = 0
        while True:
            pos = m.string.find(skip_content, start)
            if pos == -1:
                break
            if pos == m.end(1):
                return m.group(1) + "CC" + m.group(2)
            start = pos + 1
    return m.group(1) + m.group(2)


def add_namespace_callback(m):
    """

    Arguments:
    - `m`:
    """
    return m.group(1) + "cocos2d::" + m.group(2)


def replace_callback(m):
    if replace_type == "replace_variable":
        return replacement_member_variable(m)
    elif replace_type == "remove_prefix":
        return remove_prefix_callback(m)
    elif replace_type == "add_namespace":
        return add_namespace_callback(m)
    else:
        raise Exception("type error.")


def file_replace(fname, pat):
    # first, see if the pattern is even in the file.
    with open(fname) as f:
        if not any(re.search(pat, line) for line in f):
            # print "can't find the string..."
            return # pattern does not occur in file so we are done.

    # pattern is in the file, so perform replace operation.
    with open(fname) as f:
        out_fname = fname + ".tmp"
        out = open(out_fname, "w")
        for line in f:
            repl = line
            m = re.search(pat, line)
            if m:
                repl = re.sub(pat, replace_callback, line)

            out.write(repl)
        out.close()
        os.rename(out_fname, fname)


def mass_replace(dir_name, s_before):
    pat = re.compile(s_before)
    for dirpath, dirnames, filenames in os.walk(dir_name):
        for fname in filenames:
            if try_to_replace(fname):
                fullname = os.path.join(dirpath, fname)
                need_skip = False
                if files_to_skip != None:
                    for skip in files_to_skip:
                        if fullname.find(skip) != -1:
                            print "skip file: ", fullname
                            need_skip = True
                            break
                if not need_skip:
                    file_replace(fullname, pat)


prefix_need_replace = [
    "m_pob",
    "m_ob",
    "m_str",
    "m_psz",
    "m_sz",
    "m_pfn",
    "m_pf",
    "m_s",
    "m_p",
    "m_b",
    "m_n",
    "m_h",
    "m_u",
    "m_c",
    "m_e",
    "m_f",
    "m_d",
    "m_t",
    "m_i",
    "m_"
]


def do_member_varible_replace(dir):
    """

    Arguments:
    - `dir`:
    - `dir_skip`:
    """

    for p in prefix_need_replace:
        # mass_replace(".", p)
        pat = "([^\w])(" + p + ')(\w{1,2})'
        mass_replace(dir, pat)
        pat = "(^)(" + p + ')(\w{1,2})'
        mass_replace(dir, pat)


remove_prefix_patterns = [
    "([^/_\"])CC([A-Z][a-z])", \
    "(^)CC([A-Z][a-z])", \
    "([^/_\"])CC(IME[A-Z][a-z])", \
    "(^)CC(IME[A-Z][a-z])", \
    "([^/_\"])CC(TMX)", \
    "(^)CC(TMX)", \
    "([^/_\"])CC(GL\w)", \
    "(^)CC(GL\w)", \
    "([^/_\"])CC(EGL)", \
    "(^)CC(EGL)", \
    "([^/_\"])CC(EGL)", \
    "(^)CC(EGL)", \
    "([^/_\"])CC(RGBA)", \
    "(^)CC(RGBA)", \
    "([^/_\"])CC(SAX)", \
    "(^)CC(SAX)"
]


def do_remove_class_cc_prefix(dir):
    for pat in remove_prefix_patterns:
        mass_replace(dir, pat)


def do_add_namespace(dir):
    """

    Arguments:
    - `dir`:
    """
    pat = "([\s(])(CC[A-Z][a-z])"
    mass_replace(dir, pat)


def main():
    """
    """
    from optparse import OptionParser

    parser = OptionParser("usage: %prog cpp-best-practise-formatter -d DIR_NAME [-s FILES_TO_SKIP]")
    parser.add_option("-t", "--type",
                      action="store", type="string", dest="type", default="all",
                      help='''all: Replaces hungary naming of member variables and removing CC prefix for classes.
                              remove_prefix: Only removes CC prefix for classes.
                              replace_variable: Replaces hungary naming of member variables.
                      ''')

    parser.add_option("-d", "--dir",
                      action="store", type="string", dest="dir_name", default=None,
                      help="The directory which contains sources to format")

    parser.add_option("-s", "--skip",
                      action="append", type="string", dest="skips", default=None,
                      help="Files or directories to skip")


    (options, args) = parser.parse_args(sys.argv)

    if options.dir_name is None:
        raise Exception("Don't set -d at the same time");

    global replace_type
    replace_type = options.type

    global files_to_skip
    files_to_skip = options.skips

    if options.type == "all":
        #replace_type = "add_namespace"
        #do_add_namespace(options.dir_name)
        replace_type = "replace_variable"
        do_member_varible_replace(options.dir_name)
        replace_type = "remove_prefix"
        do_remove_class_cc_prefix(options.dir_name)
    elif options.type == "replace_variable":
        do_member_varible_replace(options.dir_name)
    elif options.type == "remove_prefix":
        do_remove_class_cc_prefix(options.dir_name)
    elif options.type == "add_namespace":
        do_add_namespace(options.dir_name)
    else:
        raise Exception("type error, please use correct -t opinion.")


if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print e
        sys.exit(1)
