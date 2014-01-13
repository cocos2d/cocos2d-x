#!/usr/bin.python
''' some common path and file operation '''
import os.path
import re
import types
import fileinput
import cStringIO


class PathUtils:
    
    def __init__(self, root):
        self.__root = root

    def __check_file_matchs(self, filePath):
    
        #normalize the path
        realFilePath = os.path.abspath(filePath)

        if not os.path.isfile(realFilePath):
            return False
    
        curDir, fileName = os.path.split(realFilePath)
    
        # check dir is exclude or not
        for dir in self.__exclude:
            dir = os.path.abspath(os.path.join(self.__root, dir))
            if os.path.isdir(dir) and os.path.isdir(curDir[:len(dir)]):
                if self.samefile(dir, curDir[:len(dir)]):
                    return False
    
        if self.__rep.match(fileName):
            # check file is exclude or not
            for file in self.__exclude:
                if os.path.isfile(os.path.join(self.__root, file)):
                    if self.samefile(realFilePath, os.path.join(self.__root, file)):
                        return False
        
            return True
    
        return False


    def __walk_collect_files(self, lst, dirname, names):
        for name in names:
            if self.__check_file_matchs(os.path.join(dirname, name)):
                if type(lst) is types.ListType:
                    lst += [os.path.abspath(os.path.join(dirname, name))]
                 
    def samefile(self, path1, path2):
        return os.stat(path1) == os.stat(path2)

    def set_root(self, root):
        "set the root path"
        self._root = root

    def find_files(self, pathes, suffixes = (), exclude = ()):
        "find files in pathes(a list) with suffixes. It will not collect files your specified in exclude. all of these pathes passed in must be relative to root"
        lst = []
        
        # rep generate with params to search the files
        repStr = cStringIO.StringIO()
        repStr.write(".+")
        for i, suffix in enumerate(suffixes):
            if i == 0:
                repStr.write("\.(?:(?:")
            else:
                repStr.write("|(?:")

            repStr.write(suffix)

            if i == len(suffixes) - 1:
                repStr.write("))$")
            else:
                repStr.write(")")

        self.__rep = re.compile(repStr.getvalue())
        repStr.close()
        self.__exclude = exclude
        
        # find files
        for path in pathes:
            path = os.path.join(self.__root, path)
            if os.path.isdir(path):
                os.path.walk(path, self.__walk_collect_files, lst)
            else:
                lst += [os.path.abspath(path)]

        return lst
