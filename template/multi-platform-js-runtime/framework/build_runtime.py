#! /usr/bin/env python
# coding=utf-8
# filename=build_runtime.py

import platform
import os
import commands
import subprocess

if platform.system() == 'Windows':
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
        self.projectName = None
        self.runtimePlatform = platform
        
        scriptPath = os.path.abspath(os.path.dirname(__file__))
        if platform == 'win32':
            self.projectPath = os.path.join(scriptPath, "proj.win32")
        elif platform == 'android':
            self.projectPath = os.path.join(scriptPath, "proj.android")
        elif platform == 'ios':
            self.projectPath = os.path.join(scriptPath, "proj.ios")
        elif platform == 'mac':
            self.projectPath = os.path.join(scriptPath, "proj.mac")
        
    def buildRuntime(self):
        if self.runtimePlatform == 'win32':
            self.win32Runtime()
        elif self.runtimePlatform == 'android':
            self.androidRuntime()
        if self.runtimePlatform == 'ios':
            self.iosRuntime()
        if self.runtimePlatform == 'mac':
            self.macRuntime()
            
    def macRuntime(self):
        pass
    
    def iosRuntime(self):
        pass
    
    def androidRuntime(self):
        buildNative = os.path.join(self.projectPath, "build_native.py")
        buildCommand = "python %s -p 16" % (buildNative)
        #print buildCommand
        os.system(buildCommand)
        
        child = subprocess.Popen(["python", buildNative, "-p", "16"], stdout=subprocess.PIPE)
        for line in child.stdout:
            print line
            
        child.wait()
        
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
                        
                        child = subprocess.Popen([msbuildPath, slnPath, "/maxcpucount:4", "/t:build", "/p:configuration=Debug"], stdout=subprocess.PIPE)
                        #output = child.communicate()
                        for line in child.stdout:
                            print line
                            
                        child.wait()
                except:
                    pass
                i += 1
        except WindowsError:
            return False
        
    def checkFileByExtention(self):
        files = os.listdir(self.projectPath)
        for file in files:
            name, extention = os.path.splitext(file)
            if extention == '.sln':
                self.projectName = name
                return True
        return False
                
        

    
if __name__ == '__main__':
    platform = checkParams();
    buildRuntime = BuildRuntime(platform)
    buildRuntime.buildRuntime()
