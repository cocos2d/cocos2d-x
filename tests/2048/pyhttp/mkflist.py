#!/usr/bin/env python

import hashlib
import sys 

def hexstr(s):
    hs = ""
    for i in range(len(s)):
        hs += '%02X' % ord(s[i])
    return hs


def main():
    if len(sys.argv) != 3:
        sys.exit('Usage: %s file version' % sys.argv[0])

    filename = sys.argv[1]
    version = sys.argv[2]
    m = hashlib.md5()
    fp = file(filename,'rb')
    while True:
        blk = fp.read(4096) # 4KB per block
        if not blk: break
        hs = hexstr(blk)
        m.update(hs)
    fp.close()

    ms = m.hexdigest()
    buf = "local list = {\n\tver = \""+version+"\",\n\tstage = {\n"
    buf += "\t\t{name=\"" + filename + "\", code=\""
    buf += ms + "\", act=\"load\"},\n"
    buf += "\t},\n\tremove={\n\t},\n}\nreturn list"

    flist = open('flist', 'w') 
    flist.write(buf)
    flist.close()

if __name__ == '__main__':
    main()
