#! /usr/bin/env python
# coding=utf-8
# filename=build_runtime.py

import os
import commands
import _winreg

def checkParams():
    """Custom and check param list.
    """
    from optparse import OptionParser
    # set the parser to parse input params
    # the correspond variable name of "-x, --xxx" is parser.xxx
    parser = OptionParser(
        usage="Usage: %prog -p <win32|android|ios|mac>\n\
        Sample: %prog -p win32"
    )
    parser.add_option(
        "-p",
        "--platform",
        metavar="PLATFORM",
        type="choice",
        choices=["win32","android","ios","mac"],
        help="Set build runtime's platform"
    )

    # parse the params
    (opts, args) = parser.parse_args()
    if not opts.platform:
        parser.error("-p or --platform is not specified")

    return opts.platform


class BuildRuntime:
    
    def __init__(self, platform):
        self.projectPath = None
        if platform == 'win32':
            self.projectPath = "./proj.win32"
        self.projectName = None
        self.runtimePlatform = platform
    
    def buildRuntime(self):
        if self.runtimePlatform == 'win32':
            self.win32Runtime()
        elif self.runtimePlatform == 'android':
            self.androidRuntime()
            
    def androidRuntime(self):
        buildCommand = "python -p 16"
        os.system(buildCommand)
    
    def win32Runtime(self):
        try:
            key = _winreg.OpenKey(
                _winreg.HKEY_LOCAL_MACHINE,
                r"SOFTWARE\Microsoft\VisualStudio",
            )
        except WindowsError:
            print "The computer was not installed visual studio "
            return False
        
        res = self.checkFileByExtention()
        
        if not res:
            print "There is no sln file in the win32 project path"
            return False

        try:
            i = 0
            while 1:
                name = _winreg.EnumKey(key,i)
                try:
                    version = float(name)
                    if version >= 11.0:
                        pathKey = _winreg.OpenKey(key, r"SxS\VS7")
                        pathValue,type = _winreg.QueryValueEx(pathKey, name)
                        
                        msbuildPath = r"C:\Windows\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe"
                        slnPath = "%s\%s.sln" % (self.projectPath, self.projectName)
                        buildCommand = "%s %s /t:rebuild /p:configuration=Debug" % (msbuildPath, slnPath)
                        
                        os.system(buildCommand)
                        print buildCommand
                except:
                    pass
                i += 1
        except WindowsError:
            return False
        
    def checkFileByExtention(self):
        files = os.listdir(self.projectPath)
        for file in files:
            name, extention = os.path.splitext(file)
            print name, extention
            if extention == '.sln':
                self.projectName = name
                return True
        return False
                
        

    
if __name__ == '__main__':
    platform = checkParams();
    buildRuntime = BuildRuntime(platform)
    buildRuntime.buildRuntime()