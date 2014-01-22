#! /usr/bin/env python
# coding=utf-8
# filename=build_runtime.py

import os
import re
import shutil
import platform
import subprocess

if platform.system() == 'Windows':
    import _winreg


def checkParams():
    """Custom and check param list.
    """
    from optparse import OptionParser
    # set the parser to parse input params
    # the correspond variable name of "-x, --xxx" is parser.xxx

    if platform.system() == "Darwin":
        parser = OptionParser(
            usage="Usage: %prog -p <android|ios|mac>\n\
            Sample: %prog -p ios"
        )
        parser.add_option(
            "-p",
            "--platform",
            metavar="PLATFORM",
            type="choice",
            choices=["android", "ios", "mac"],
            help="Set build runtime's platform"
        )
    elif platform.system() == "Windows":
        parser = OptionParser(
            usage="Usage: %prog -p <win32|android>\n\
            Sample: %prog -p win32"
        )
        parser.add_option(
            "-p",
            "--platform",
            metavar="PLATFORM",
            type="choice",
            choices=["win32", "android"],
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
            self.projectPath = os.path.join(scriptPath, "proj.ios_mac")
        elif platform == 'mac':
            self.projectPath = os.path.join(scriptPath, "proj.ios_mac")
        
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
        commands = [
            "xcodebuild",
            "-version"
        ]
        child = subprocess.Popen(commands, stdout=subprocess.PIPE)

        xcodeVersion = None
        for line in child.stdout:
            if 'Xcode' in line:
                xcodeVersion = line

        child.wait()

        if xcodeVersion == None:
            print ("Xcode wasn't installed")
            return False

        res = self.checkFileByExtention(".xcodeproj")
        if not res:
            print ("Can't find the \".xcodeproj\" file")
            return False

        projectPath = os.path.join(self.projectPath, self.projectName)
        pbxprojectPath = os.path.join(projectPath, "project.pbxproj")
        print(pbxprojectPath)

        f = file(pbxprojectPath)
        contents = f.read()

        section = re.search(
            r"Begin PBXProject section.*End PBXProject section",
            contents,
            re.S
        )

        if section == None:
            print ("Can't find Mac target")
            return False

        targets = re.search(r"targets = (.*);", section.group(), re.S)
        if targets == None:
            print ("Can't find Mac target")
            return False

        targetName = None
        names = re.split("\*", targets.group())
        for name in names:
            if "Mac" in name:
                targetName = str.strip(name)

        if targetName == None:
            print ("Can't find Mac target")
            return False

        macFolder = os.path.join(self.projectPath, "..", "..", "runtime", "mac")
        if os.path.isdir(macFolder):
            shutil.rmtree(macFolder)

        commands = [
            "xcodebuild",
            "-project",
            projectPath,
            "-target",
            targetName,
            "CONFIGURATION_BUILD_DIR=%s" % (macFolder)
        ]
        #print commands
        child = subprocess.Popen(commands, stdout=subprocess.PIPE)
        for line in child.stdout:
            print (line)

        child.wait()

        filelist = os.listdir(macFolder)
        for filename in filelist:
            name, extention = os.path.splitext(filename)
            if extention == '.a':
                filename = os.path.join(macFolder, filename)
                os.remove(filename)
            if extention == '.app':
                filename = os.path.join(macFolder, filename)
                if ' ' in name:
                    newname = os.path.join(macFolder, name[:name.find(' ')-1]+extention)
                    os.rename(filename, newname)
    
    def iosRuntime(self):
        commands = [
            "xcodebuild",
            "-version"
        ]
        child = subprocess.Popen(commands, stdout=subprocess.PIPE)

        xcodeVersion = None
        for line in child.stdout:
            if 'Xcode' in line:
                xcodeVersion = line

        child.wait()

        if xcodeVersion == None:
            print ("Xcode wasn't installed")
            return False

        res = self.checkFileByExtention(".xcodeproj")
        if not res:
            print ("Can't find the \".xcodeproj\" file")
            return False

        projectPath = os.path.join(self.projectPath, self.projectName)
        pbxprojectPath = os.path.join(projectPath, "project.pbxproj")
        print(pbxprojectPath)

        f = file(pbxprojectPath)
        contents = f.read()

        section = re.search(r"Begin PBXProject section.*End PBXProject section", contents, re.S)

        if section == None:
            print ("Can't find iOS target")
            return False

        targets = re.search(r"targets = (.*);", section.group(), re.S)
        if targets == None:
            print ("Can't find iOS target")
            return False

        targetName = None
        names = re.split("\*", targets.group())
        for name in names:
            if "iOS" in name:
                targetName = str.strip(name)

        if targetName == None:
            print ("Can't find iOS target")
            return False

        iosFolder = os.path.join(self.projectPath, "..", "..", "runtime", "ios")
        if os.path.isdir(iosFolder):
            shutil.rmtree(iosFolder)

        commands = [
            "xcodebuild",
            "-project",
            projectPath,
            "-target",
            targetName,
            "-sdk",
            "iphonesimulator",
            "CONFIGURATION_BUILD_DIR=%s" % (iosFolder)
        ]
        #print commands
        child = subprocess.Popen(commands, stdout=subprocess.PIPE)
        for line in child.stdout:
            print (line)

        child.wait()

        filelist = os.listdir(iosFolder)

        for filename in filelist:
            name, extention = os.path.splitext(filename)
            if extention == '.a':
                filename = os.path.join(iosFolder, filename)
                os.remove(filename)
            if extention == '.app':
                filename = os.path.join(iosFolder, filename)
                newname = os.path.join(iosFolder, name[:name.find(' ')-1]+extention)
                os.rename(filename, newname)

    def androidRuntime(self):
        buildNative = os.path.join(self.projectPath, "build_native.py")
        commands = [
            "python",
            buildNative,
            "-p",
            "17",
        ]
        child = subprocess.Popen(commands, stdout=subprocess.PIPE)
        for line in child.stdout:
            print line
            
        child.wait()
        
    def win32Runtime(self):
        try:
            vs = _winreg.OpenKey(
                _winreg.HKEY_LOCAL_MACHINE,
                r"SOFTWARE\Microsoft\VisualStudio"
            )

            msbuild = _winreg.OpenKey(
                _winreg.HKEY_LOCAL_MACHINE,
                r"SOFTWARE\Microsoft\MSBuild\ToolsVersions"
            )

        except WindowsError:
            print ("Visual Studio wasn't installed")
            return False

        vsPath = None
        i = 0
        try:
            while True:
                version = _winreg.EnumKey(vs,i)
                try:
                    if float(version) >= 11.0:
                        key = _winreg.OpenKey(vs, r"SxS\VS7")
                        vsPath, type = _winreg.QueryValueEx(key, version)
                except:
                    pass
                i += 1
        except WindowsError:
            pass

        if vsPath == None:
            print("Can't find the Visual Studio's path in the regedit")
            return False

        msbuildPath = None
        i = 0
        try:
            while True:
                version = _winreg.EnumKey(msbuild,i)
                try:
                    if float(version) >= 4.0:
                        key = _winreg.OpenKey(msbuild, version)
                        msbuildPath, type = _winreg.QueryValueEx(
                            key, 
                            "MSBuildToolsPath"
                        )
                except:
                    pass
                i += 1
        except WindowsError:
            pass

        if msbuildPath == None:
            print ("Can't find the MSBuildTools' path in the regedit")
            return False

        res = self.checkFileByExtention(".sln")
        if not res:
            print ("Can't find the \".sln\" file")
            return False

        msbuildPath = os.path.join(msbuildPath, "MSBuild.exe")
        projectPath = os.path.join(self.projectPath, self.projectName)
        commands = [
            msbuildPath,
            projectPath,
            "/maxcpucount:4",
            "/t:build",
            "/p:configuration=Debug"
        ]

        child = subprocess.Popen(commands, stdout=subprocess.PIPE)
        for line in child.stdout:
            print (line)

        child.wait()

        return True
        
    def checkFileByExtention(self, ext, path=None):
        filelist = ""
        if path == None:
            filelist = os.listdir(self.projectPath)
        else:
            filelist = os.listdir(path)

        for file in filelist:
            name, extention = os.path.splitext(file)
            if extention == ext:
                self.projectName = file
                return True
        return False
                
        

    
if __name__ == '__main__':
    platform = checkParams();
    buildRuntime = BuildRuntime(platform)
    buildRuntime.buildRuntime()
