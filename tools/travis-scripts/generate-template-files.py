#!/usr/bin/python
#coding=utf-8
"""****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

import os
import sys
import re
import json

class CocosFileList:
    """
    Function:
        List cocos engine's files and save to "../module/cocos_file_list.json".
        config "config.gitingore" file  can set exclude or include files.
    """

    def __init__(self):
        self.excludeConfig=[]
        self.inludeConfig=[]
        self.rootDir = ""
        self.fileList_com=[]
        self.fileList_lua=[]

        self.luaPath = ["cocos/scripting/lua-bindings", "external/lua", "tools/bindings-generator", "tools/tolua"]

    def readIngoreFile(self, fileName):
        """
            Read configure file which use ".gitingore"'s rules.
        """
        pfile = ""
        try:
            pfile = open(fileName, 'r')
        except IOError:
            return

        for line in pfile:
            line = line.strip()
            if not line or line[0] == "#":
                continue

            #convert .gitingore regular expression to python's regular expression
            line=line.replace('.', '\\.')
            line=line.replace('*', '.*')
            line="%s$" %line
            if line[0] == "!":
                self.inludeConfig.append(line[1:])
            else:
                self.excludeConfig.append(line)
        pfile.close()

    def parseFileList(self, rootDir):
        self.rootDir = os.path.abspath(rootDir)
        self.__parseFileList(rootDir)

    def __parseFileList(self, folderdir):
        """
        """
        for item in os.listdir(folderdir):
            path = os.path.join(folderdir, item)
            relativePath = path[len(self.rootDir)+1:len(path)]
            relativePath = relativePath.replace('\\', '/')
            if os.path.isdir(path):
                if (
                      self.__bInclude("/%s" %relativePath) or
                      self.__bInclude("/%s/" %relativePath) or
                      self.__bInclude(item) or
                      self.__bInclude("%s/" %item)
                    ):
                        foundLuaModule = False
                        for luaPath in self.luaPath:
                            if relativePath.upper().find(luaPath.upper()) == 0:
                                foundLuaModule = True
                                break

                        if foundLuaModule:
                            self.fileList_lua.append("%s/" %relativePath)
                        else:
                            self.fileList_com.append("%s/" %relativePath)
                        self.__parseFileList(path)
                        continue
                if (
                     self.__bExclude("/%s" %relativePath) or
                     self.__bExclude("/%s/" %relativePath) or
                     self.__bExclude(item) or
                     self.__bExclude("%s/" %item)
                    ):
                        continue
                self.__parseFileList(path)
            else:
                if (
                    not self.__bInclude("/%s" %relativePath) and
                    not self.__bInclude(item)
                    ):
                        if (
                            self.__bExclude("/%s" %relativePath) or
                            self.__bExclude(item)
                        ):
                            continue
                # print(relativePath)
                foundLuaModule = False
                for luaPath in self.luaPath:
                    if relativePath.upper().find(luaPath.upper()) == 0:
                        foundLuaModule = True
                        break

                if foundLuaModule:
                    self.fileList_lua.append(relativePath)
                else:
                    self.fileList_com.append(relativePath)

    def __bExclude(self, item):
        bexclude = False
        for index in range(len(self.excludeConfig)):
            if re.match(self.excludeConfig[index], item):
                bexclude = True
                break
        return bexclude

    def __bInclude(self, item):
        binclude = False
        for index in range(len(self.inludeConfig)):
            if re.match(self.inludeConfig[index], item):
                binclude = True
                break
        return binclude

    def writeFileList(self,fileName):
        """
            Save content to file with json format.
        """
        f = open(fileName,"w")
        self.fileList_com.sort()
        self.fileList_lua.sort()
        content ={'common':self.fileList_com,'lua':self.fileList_lua}
        json.dump(content,f,sort_keys=True,indent=4)
        f.close()
        return True

# ------------ main --------------
if __name__ == '__main__':

    cocos_root =os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
    cocos_file_path =os.path.abspath(os.path.join(cocos_root, "templates", "cocos2dx_files.json"))
    cocos_file_ingore =os.path.abspath(os.path.join(os.path.dirname(__file__), "config.gitignore"))
    # print ("begin list files")
    cocosObj = CocosFileList()
    cocosObj.readIngoreFile(cocos_file_ingore)
    cocosObj.parseFileList(cocos_root)
    cocosObj.writeFileList(cocos_file_path)
    # print ("had list files to cocos_file_list.json")

