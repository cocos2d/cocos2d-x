/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
 ****************************************************************************/


#ifndef __PROJECT_CONFIG_H_
#define __PROJECT_CONFIG_H_

#include <string>
#include <vector>

using namespace std;

#include "cocos2d.h"
#include "SimulatorExport.h"

#define kCCRuntimeDebuggerNone      0
#define kCCRuntimeDebuggerLDT       1
#define kCCRuntimeDebuggerCodeIDE   2
#define kCCRuntimeDebuggerStudio    3

#define kProjectConfigProjectDir                1       // -workdir "PATH"
#define kProjectConfigScriptFile                2       // -script "FILENAME"
#define kProjectConfigPackagePath               4       // -package.path "PATH;PATH"
#define kProjectConfigWritablePath              8       // -writable "PATH"
#define kProjectConfigFrameSize                 16      // -size 960x640
#define kProjectConfigFrameScale                32      // -scale 1.0
#define kProjectConfigShowConsole               64      // -console, -disable-console
#define kProjectConfigLoadPrecompiledFramework  128     // -load-framework, -disable-load-framework
#define kProjectConfigWriteDebugLogToFile       256     // -write-debug-log, -disable-write-debug-log
#define kProjectConfigWindowOffset              512     // -offset {0,0}
#define kProjectConfigDebugger                  1024    // -debugger-ldt, -debugger-codeide, -disable-debugger
#define kProjectConfigListen                    2048    //
#define kProjectConfigSearchPath                4096    //
#define kProjectConfigFirstSearchPath            8192    // -first-search-path

#define kProjectConfigOpenRecent (kProjectConfigProjectDir | kProjectConfigScriptFile | kProjectConfigPackagePath | kProjectConfigWritablePath | kProjectConfigFrameSize | kProjectConfigFrameScale | kProjectConfigShowConsole | kProjectConfigLoadPrecompiledFramework | kProjectConfigWriteDebugLogToFile)

#define kProjectConfigAll (kProjectConfigProjectDir | kProjectConfigScriptFile | kProjectConfigPackagePath | kProjectConfigWritablePath | kProjectConfigFrameSize | kProjectConfigFrameScale | kProjectConfigShowConsole | kProjectConfigLoadPrecompiledFramework | kProjectConfigWriteDebugLogToFile | kProjectConfigWindowOffset | kProjectConfigDebugger | kProjectConfigListen | kProjectConfigSearchPath | kProjectConfigFirstSearchPath)


#define kProjectConfigConsolePort   6010
#define kProjectConfigUploadPort    6020
#define kProjectConfigDebugPort     5086

class CC_LIBSIM_DLL ProjectConfig
{
public:
    ProjectConfig();

    static const int DEFAULT_WIDTH = 640;
    static const int DEFAULT_HEIGHT = 960;

    string getProjectDir() const;
    void setProjectDir(const string &projectDir);

    string getScriptFile() const;
    string getScriptFileRealPath() const;
    void setScriptFile(const string &scriptFile);

    string getWritablePath() const;
    string getWritableRealPath() const;
    void setWritablePath(const string &writablePath);

    string getPackagePath() const;
    string getNormalizedPackagePath() const;
    void setPackagePath(const string &packagePath);
    void addPackagePath(const string &packagePath);
    vector<string> getPackagePathArray() const;

    cocos2d::Size getFrameSize() const;
    void setFrameSize(const cocos2d::Size &frameSize);
    bool isLandscapeFrame() const;
    bool isPortraitFrame() const;
    void changeFrameOrientation();
    void changeFrameOrientationToPortait();
    void changeFrameOrientationToLandscape();

    float getFrameScale() const;
    void setFrameScale(float frameScale);

    bool isShowConsole() const;
    void setShowConsole(bool showConsole);

    bool isLoadPrecompiledFramework() const;
    void setLoadPrecompiledFramework(bool load);

    bool isWriteDebugLogToFile() const;
    void setWriteDebugLogToFile(bool writeDebugLogToFile);
    void setDebugLogFilePath(const std::string &logFile);
    string getDebugLogFilePath() const;

    cocos2d::Vec2 getWindowOffset() const;
    void setWindowOffset(const cocos2d::Vec2 &windowOffset);

    int getDebuggerType() const;
    void setDebuggerType(int debuggerType);

    void parseCommandLine(const vector<string> &args);
    string makeCommandLine(unsigned int mask = kProjectConfigAll) const;
    vector<string> makeCommandLineVector(unsigned int mask = kProjectConfigAll) const;

    void setConsolePort(int port);
    int getConsolePort();
    void setFileUploadPort(int port);
    int getFileUploadPort();
    // @address: 127.0.0.1
    void setBindAddress(const std::string &address);
    const std::string &getBindAddress() const;
    void setSearchPath(const vector<string> &args);
    const vector<string> &getSearchPath() const;
    void setFirstSearchPath(const vector<string> &args);
    const vector<string> &getFirstSearchPath() const;
    void setLanguageDataPath(const std::string &filePath);

    bool isAppMenu() const;
    bool isResizeWindow() const;
    bool isRetinaDisplay() const;

    bool validate() const;
    void dump();

private:
    string _projectDir;
    string _scriptFile;
    string _packagePath;
    string _writablePath;
    cocos2d::Size _frameSize;
    float _frameScale;
    bool _showConsole;
    bool _loadPrecompiledFramework;
    bool _writeDebugLogToFile;
    bool _restartProcess;
    cocos2d::Vec2 _windowOffset;
    int _debuggerType;
    bool _isAppMenu;
    bool _isResizeWindow;
    bool _isRetinaDisplay;
    string _debugLogFile;
    int _consolePort;
    int _fileUploadPort;
    string _bindAddress;
    vector<string> _searchPath;
    vector<string> _firstSearchPath;
    string _languageDataPath;

    void normalize();
    string replaceProjectDirToMacro(const string &path) const;
    string replaceProjectDirToFullPath(const string &path) const;
    bool isAbsolutePath(const string &path) const;
    
    /**
     * windows : Y:\Documents\CocosProjects\Cocos Project\ -> "Y:\Documents\CocosProjects\Cocos Project\\"
     * other   : return @path
     */
    string dealWithSpaceWithPath(const string &path) const;
};

#endif // __PROJECT_CONFIG_H_
