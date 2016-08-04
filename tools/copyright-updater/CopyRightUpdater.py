#!/usr/bin/env python
# coding=utf-8

import sys
import os
import io


class CopyRightUpdater(object):

    def run(self):

        def callback(path, is_dir):
            # Skip .git folder
            if '.git' in path.split(os.sep):
                return False

            if not is_dir:
                for suffix in self._suffixes:
                    if path.endswith(suffix):
                        self._convert(path)

            return False

        common.deep_iterate_dir(self._src, callback)
        return

    def _convert(self, file_path):
        common.Logging.info("Converting " + file_path)
        infile = open(file_path)
        outfile = io.StringIO()

        while True:
            l = common.utf8_to_unicode(infile.readline())
            if l == u"":
                break

            newline = u''
            for i in xrange(0, len(l)):
                c = l[i]
                if c == u" ":
                    newline += u" "
                    continue
                if c == u"\t":
                    newline += u" " * self._space_num
                    continue
                newline += c

            outfile.write(newline)

        infile.close()
        infile = open(file_path, "w")
        out = outfile.getvalue()
        infile.write(common.unicode_to_utf8(out))
        infile.close()

        return



def main():

    common.Logging.info("==> main entry")

    workspace = os.path.dirname(os.path.realpath(__file__))
    common.Logging.info("workspace: " + workspace)

    from optparse import OptionParser

    parser = OptionParser()

    parser.add_option("-t", "--type",
                      action="store", type="string", dest="type", default=None,
                      help="Tab to spaces or spaces to tab")

    parser.add_option("-n", "--space-num",
                      action="store", type="int", dest="space_num", default=None,
                      help="The space number to be converted")

    parser.add_option("-s", "--src",
                      action="store", type="string", dest="src", default=None,
                      help="The source folder")

    parser.add_option("-x", "--suffix",
                      action="append", type="string", dest="suffixes", default=None,
                      help="The suffix of file to be converted")

    (opts, args) = parser.parse_args()

    # FIXME:
    if not opts.src:
        opts.src = "runtime-java"

    if not opts.suffixes:
        opts.suffixes = ['.java']

    if not opts.space_num:
        opts.space_num = 4

    if not opts.type:
        opts.type = "tab2spaces"

    if not opts.src:
        raise common.ErrorMessage("-s argument wasn't assigned")

    opts = vars(opts)
    opts['workspace'] = workspace

    if opts['type'] == "tab2spaces":
        r = Tab2Spaces(opts)
    elif opts['type'] == "spaces2tab":
        r = Spaces2Tab(opts)
    else:
        raise common.ErrorMessage("-type argument wasn't assigned")

    r.run()

if __name__ == '__main__':
    module_path = os.path.normpath(os.path.join(os.path.split(os.path.realpath(__file__))[0], '..', 'common'))
    sys.path.append(module_path)
    import common

    try:
        main()
    except common.ErrorMessage as e:
        if e.__class__.__name__ == "ErrorMessage":
            common.Logging.error(e.message)
            sys.exit(1)
        else:
            raise
