
#include <sstream>

#include "ProjectConfig/ProjectConfig.h"
#include "ProjectConfig/SimulatorConfig.h"
#include "cocostudio/LocalizationManager.h"

#ifdef _MSC_VER
#define strcasecmp _stricmp
#endif

#if defined(_WINDOWS)
#define DIRECTORY_SEPARATOR "\\"
#define DIRECTORY_SEPARATOR_CHAR '\\'
#else
#define DIRECTORY_SEPARATOR "/"
#define DIRECTORY_SEPARATOR_CHAR '/'
#endif

static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

ProjectConfig::ProjectConfig()
    : _scriptFile("")
    , _writablePath("")
    , _packagePath("")
    , _frameSize(960, 640)
    , _frameScale(1.0f)
    , _showConsole(true)
    , _loadPrecompiledFramework(false)
    , _writeDebugLogToFile(false)
    , _windowOffset(0, 0)
    , _debuggerType(kCCRuntimeDebuggerNone)
    , _isAppMenu(true)
    , _isResizeWindow(false)
    , _isRetinaDisplay(false)
    , _debugLogFile("debug.log")
    , _consolePort(kProjectConfigConsolePort)
    , _fileUploadPort(kProjectConfigUploadPort)
    , _bindAddress("")
{
    normalize();
}

string ProjectConfig::getProjectDir() const
{
    return _projectDir;
}

void ProjectConfig::setProjectDir(const string &projectDir)
{
    _projectDir = projectDir;
    normalize();
}

string ProjectConfig::getScriptFile() const
{
    return _scriptFile;
}

string ProjectConfig::getScriptFileRealPath() const
{
    return replaceProjectDirToFullPath(_scriptFile);
}

void ProjectConfig::setScriptFile(const string &scriptFile)
{
    _scriptFile = scriptFile;
    normalize();
}

string ProjectConfig::getWritablePath() const
{
    return _writablePath;
}

string ProjectConfig::getWritableRealPath() const
{
    return replaceProjectDirToFullPath(_writablePath);
}

void ProjectConfig::setWritablePath(const string &writablePath)
{
    _writablePath = writablePath;
    normalize();
}

string ProjectConfig::getPackagePath() const
{
    return _packagePath;
}

string ProjectConfig::getNormalizedPackagePath() const
{
    // replace $(PROJDIR)
    auto path = _packagePath;
    auto pos = string::npos;
    while ((pos = path.find("$(PROJDIR)")) != string::npos)
    {
        path = path.substr(0, pos) + _projectDir + path.substr(pos + 10);
    }
    auto len = path.length();
    if (len && path[len - 1] != ';')
    {
        path.append(";");
    }
    path.append(";");
    SimulatorConfig::makeNormalizePath(&path, "/");
    return path;
}

void ProjectConfig::setPackagePath(const string &packagePath)
{
    _packagePath = packagePath;
}

void ProjectConfig::addPackagePath(const string &packagePath)
{
    if (packagePath.length())
    {
        if (_packagePath.length())
        {
            _packagePath.append(";");
        }
        _packagePath.append(packagePath);
        normalize();
    }
}

vector<string> ProjectConfig::getPackagePathArray() const
{
    vector<string> arr;

    size_t pos = string::npos;
    size_t prev = 0;
    while ((pos = _packagePath.find_first_of(";", pos + 1)) != string::npos)
    {
        auto path = _packagePath.substr(prev, pos - prev);
        if (path.length() > 0) arr.push_back(path);
        prev = pos + 1;
    }
    auto path = _packagePath.substr(prev);
    if (path.length() > 0) arr.push_back(path);
    return arr;
}

cocos2d::Size ProjectConfig::getFrameSize() const
{
    return _frameSize;
}

void ProjectConfig::setFrameSize(const cocos2d::Size &frameSize)
{
    if (frameSize.width > 0 && frameSize.height > 0)
    {
        _frameSize = frameSize;
    }
}

bool ProjectConfig::isLandscapeFrame() const
{
    return _frameSize.width > _frameSize.height;
}

bool ProjectConfig::isPortraitFrame() const
{
    return _frameSize.width < _frameSize.height;
}

void ProjectConfig::changeFrameOrientation()
{
    float w = _frameSize.width;
    _frameSize.width = _frameSize.height;
    _frameSize.height = w;
}

void ProjectConfig::changeFrameOrientationToPortait()
{
    if (isLandscapeFrame()) changeFrameOrientation();
}

void ProjectConfig::changeFrameOrientationToLandscape()
{
    if (!isLandscapeFrame()) changeFrameOrientation();
}

float ProjectConfig::getFrameScale() const
{
    return _frameScale;
}

void ProjectConfig::setFrameScale(float frameScale)
{
    if (frameScale > 0)
    {
        _frameScale = frameScale;
    }
}

bool ProjectConfig::isShowConsole() const
{
    return _showConsole;
}

void ProjectConfig::setShowConsole(bool showConsole)
{
    _showConsole = showConsole;
}

bool ProjectConfig::isLoadPrecompiledFramework() const
{
    return _loadPrecompiledFramework;
}

void ProjectConfig::setLoadPrecompiledFramework(bool load)
{
    _loadPrecompiledFramework = load;
}

bool ProjectConfig::isWriteDebugLogToFile() const
{
    return _writeDebugLogToFile;
}

void ProjectConfig::setWriteDebugLogToFile(bool writeDebugLogToFile)
{
    _writeDebugLogToFile = writeDebugLogToFile;
}

void ProjectConfig::setDebugLogFilePath(const std::string &logFile)
{
    _debugLogFile = logFile;
}
string ProjectConfig::getDebugLogFilePath() const
{
    if (isAbsolutePath(_debugLogFile)) return _debugLogFile;

    auto path(getProjectDir());
    path.append(_debugLogFile);
    return path;
}

cocos2d::Vec2 ProjectConfig::getWindowOffset() const
{
    return _windowOffset;
}

void ProjectConfig::setWindowOffset(const cocos2d::Vec2 &windowOffset)
{
    _windowOffset = windowOffset;
}

int ProjectConfig::getDebuggerType() const
{
    return _debuggerType;
}

void ProjectConfig::setDebuggerType(int debuggerType)
{
    _debuggerType = debuggerType;
}

void ProjectConfig::parseCommandLine(const vector<string> &args)
{
    auto it = args.begin();
    while (it != args.end())
    {
        string arg = *it;

        if (arg.compare("-workdir") == 0)
        {
            ++it;
            if (it == args.end()) break;
            setProjectDir(*it);
            if (_writablePath.length() == 0) setWritablePath(*it);
        }
        else if (arg.compare("-writable-path") == 0)
        {
            ++it;
            if (it == args.end()) break;
            setWritablePath(*it);
        }
        else if (arg.compare("-entry") == 0)
        {
            ++it;
            if (it == args.end()) break;
            setScriptFile(*it);
        }
        else if (arg.compare("-landscape") == 0)
        {
            setFrameSize(cocos2d::Size(DEFAULT_HEIGHT, DEFAULT_WIDTH));
        }
        else if (arg.compare("-portrait") == 0)
        {
            setFrameSize(cocos2d::Size(DEFAULT_WIDTH, DEFAULT_HEIGHT));
        }
        else if (arg.compare("-resolution") == 0)
        {
            ++it;
            if (it == args.end()) break;
            const string& sizeStr(*it);
            size_t pos = sizeStr.find('x');
            int width = 0;
            int height = 0;
            if (pos != sizeStr.npos && pos > 0)
            {
                string widthStr, heightStr;
                widthStr.assign(sizeStr, 0, pos);
                heightStr.assign(sizeStr, pos + 1, sizeStr.length() - pos);
                width = atoi(widthStr.c_str());
                height = atoi(heightStr.c_str());
                setFrameSize(cocos2d::Size(width, height));
            }
        }
        else if (arg.compare("-scale") == 0)
        {
            ++it;
            if (it == args.end()) break;
            float scale = atof((*it).c_str());
            setFrameScale(scale);
        }
        else if (arg.compare("-write-debug-log") == 0)
        {
            ++it;
            if (it == args.end()) break;
            setDebugLogFilePath((*it));
            setWriteDebugLogToFile(true);
        }
        else if (arg.compare("-console") == 0)
        {
            ++it;
            if (it == args.end()) break;
            if ((*it).compare("enable") == 0)
            {
                setShowConsole(true);
            }
            else
            {
                setShowConsole(false);
            }
        }
        else if (arg.compare("-position") == 0)
        {
            ++it;
            if (it == args.end()) break;
            const string& posStr(*it);
            size_t pos = posStr.find(',');
            int x = 0;
            int y = 0;
            if (pos != posStr.npos && pos > 0)
            {
                string xStr, yStr;
                xStr.assign(posStr, 0, pos);
                yStr.assign(posStr, pos + 1, posStr.length() - pos);
                x = atoi(xStr.c_str());
                y = atoi(yStr.c_str());
                setWindowOffset(cocos2d::Vec2(x, y));
            }
        }
        else if (arg.compare("-debugger") == 0)
        {
            ++it;
            if (it == args.end()) break;
            if ((*it).compare("codeide") == 0)
            {
                setDebuggerType(kCCRuntimeDebuggerCodeIDE);
            }
            else if ((*it).compare("studio") == 0)
            {
                setDebuggerType(kCCRuntimeDebuggerStudio);
            }
        }
        else if (arg.compare("-app-menu") == 0)
        {
            _isAppMenu = true;
        }
        else if (arg.compare("-resize-window") == 0)
        {
            _isResizeWindow = true;
        }
        else if (arg.compare("-retina-display") == 0)
        {
            _isRetinaDisplay = true;
        }
        else if (arg.compare("-port") == 0)
        {
            CCLOG("TODO:");
        }
        else if (arg.compare("-listen") == 0)
        {
            ++it;
            setBindAddress((*it));
        }
        else if (arg.compare("-search-path") == 0)
        {
            ++it;
            vector<string> pathes = split((*it), ';');
            setSearchPath(pathes);
        }
        else if (arg.compare("-first-search-path") == 0)
        {
            ++it;
            vector<string> pathes = split((*it), ';');
            setFirstSearchPath(pathes);
        }
        else if (arg.compare("-language-data-path") == 0)
        {
            ++it;
            if (it == args.end()) break;
            setLanguageDataPath(*it);
        }
        ++it;
    }
}

string ProjectConfig::makeCommandLine(unsigned int mask /* = kProjectConfigAll */) const
{
    stringstream buff;

    vector<string> commands = makeCommandLineVector(mask);
    for (auto &cmd : commands)
    {
        buff << " " << cmd;
    }

    string result = buff.str();
    while (result.at(0) == ' ')
    {
        result = result.assign(result, 1, result.length());
    }

    return result;
}

vector<string> ProjectConfig::makeCommandLineVector(unsigned int mask /* = kProjectConfigAll */) const
{
    vector<string> ret;

    stringstream buff;

    if (mask & kProjectConfigProjectDir)
    {
        auto path = getProjectDir();
        if (path.length())
        {
            ret.push_back("-workdir");
            ret.push_back(dealWithSpaceWithPath(path));
        }
    }

    if (mask & kProjectConfigScriptFile)
    {
        auto path = getScriptFileRealPath();
        if (path.length())
        {
            ret.push_back("-entry");
            ret.push_back(dealWithSpaceWithPath(path));
        }
    }

    if (mask & kProjectConfigWritablePath)
    {
        auto path = getWritableRealPath();
        if (path.length())
        {
            ret.push_back("-writable-path");
            ret.push_back(dealWithSpaceWithPath(path));
        }
    }

    if (mask & kProjectConfigFrameSize)
    {
        buff.str("");
        buff << (int)getFrameSize().width;
        buff << "x";
        buff << (int)getFrameSize().height;

        ret.push_back("-resolution");
        ret.push_back(buff.str());
    }

    if (mask & kProjectConfigFrameScale)
    {
        if (getFrameScale() < 1.0f)
        {
            buff.str("");
            buff.precision(2);
            buff << getFrameScale();

            ret.push_back("-scale");
            ret.push_back(buff.str());
        }
    }

    if (mask & kProjectConfigWriteDebugLogToFile)
    {
        if (isWriteDebugLogToFile())
        {
            ret.push_back("-write-debug-log");
            ret.push_back(getDebugLogFilePath());
        }
    }

    if (mask & kProjectConfigShowConsole)
    {
        if (isShowConsole())
        {
            ret.push_back("-console");
            ret.push_back("enable");
        }
        else
        {
            ret.push_back("-console");
            ret.push_back("disable");
        }
    }

    if (mask & kProjectConfigWindowOffset)
    {
        if (_windowOffset.x != 0 && _windowOffset.y != 0)
        {
            buff.str("");
            buff << (int)_windowOffset.x;
            buff << ",";
            buff << (int)_windowOffset.y;
            buff << "";

            ret.push_back("-position");
            ret.push_back(buff.str());
        }
    }

    if (mask & kProjectConfigDebugger)
    {
        switch (getDebuggerType())
        {
            case kCCRuntimeDebuggerCodeIDE:
                ret.push_back("-debugger");
                ret.push_back("codeide");
                break;
            case kCCRuntimeDebuggerStudio:
                ret.push_back("-debugger");
                ret.push_back("studio");
                break;
        }
    }

    if (mask & kProjectConfigListen)
    {
        if (!_bindAddress.empty())
        {
            ret.push_back("-listen");
            ret.push_back(_bindAddress);
        }
    }

    if (mask & kProjectConfigSearchPath)
    {
        if (_searchPath.size() > 0)
        {
            stringstream pathbuff;
            for (auto &path : _searchPath)
            {
                pathbuff << dealWithSpaceWithPath(path) << ";";
            }
            string pathArgs = pathbuff.str();
            pathArgs[pathArgs.length()-1] = '\0';

            ret.push_back("-search-path");
            ret.push_back(pathArgs);
        }
    }

    if (mask & kProjectConfigFirstSearchPath)
    {
        if (_searchPath.size() > 0)
        {
            stringstream pathbuff;
            for (auto &path : _searchPath)
            {
                pathbuff << dealWithSpaceWithPath(path) << ";";
            }
            string pathArgs = pathbuff.str();
            pathArgs[pathArgs.length() - 1] = '\0';

            ret.push_back("-first-search-path");
            ret.push_back(pathArgs);
        }
    }
    return ret;
}

void ProjectConfig::setConsolePort(int port)
{
    _consolePort = port;
}

int ProjectConfig::getConsolePort()
{
    return _consolePort;
}

void ProjectConfig::setFileUploadPort(int port)
{
    _fileUploadPort = port;
}

int ProjectConfig::getFileUploadPort()
{
    return _fileUploadPort;
}

void ProjectConfig::setBindAddress(const std::string &address)
{
    _bindAddress = address;
}

const std::string &ProjectConfig::getBindAddress() const
{
    return _bindAddress;
}

void ProjectConfig::setSearchPath(const vector<string> &args)
{
    _searchPath = args;
}

const vector<string> &ProjectConfig::getSearchPath() const
{
    return _searchPath;
}

void ProjectConfig::setFirstSearchPath(const vector<string> &args)
{
    _firstSearchPath = args;
}

const vector<string> &ProjectConfig::getFirstSearchPath() const
{
    return _firstSearchPath;
}

void ProjectConfig::setLanguageDataPath(const std::string &filePath)
{
    bool isBinary = true;
    string jsonExtension = ".json";
    int exLength = jsonExtension.length();
    if (filePath.length() >= exLength &&
        (0 == filePath.compare(filePath.length() - exLength, exLength, jsonExtension)))
    {
        isBinary = false;
    }

    cocostudio::ILocalizationManager* lm;
    if (isBinary)
        lm = cocostudio::BinLocalizationManager::getInstance();
    else
        lm = cocostudio::JsonLocalizationManager::getInstance();
    lm->initLanguageData(filePath);
    cocostudio::LocalizationHelper::setCurrentManager(lm, isBinary);
}

bool ProjectConfig::isAppMenu() const
{
    return _isAppMenu;
}

bool ProjectConfig::isResizeWindow() const
{
    return _isResizeWindow;
}

bool ProjectConfig::isRetinaDisplay() const
{
    return _isRetinaDisplay;
}

bool ProjectConfig::validate() const
{
    auto utils = cocos2d::FileUtils::getInstance();
    if (!utils->isDirectoryExist(_projectDir)) return false;
    if (!utils->isDirectoryExist(getWritableRealPath())) return false;
    if (!utils->isFileExist(getScriptFileRealPath())) return false;
    return true;
}

void ProjectConfig::dump()
{
    CCLOG("Project Config:");
    CCLOG("    project dir: %s", _projectDir.c_str());
    CCLOG("    writable path: %s", _writablePath.length() ? _writablePath.c_str() : "-");
    CCLOG("    script file: %s", _scriptFile.c_str());
    CCLOG("    frame size: %0.0f x %0.0f", _frameSize.width, _frameSize.height);
    CCLOG("    frame scale: %0.2f", _frameScale);
    CCLOG("    show console: %s", _showConsole ? "YES" : "NO");
    CCLOG("    write debug log: %s (%s)", _writeDebugLogToFile ? getDebugLogFilePath().c_str() : "NO",
                                          _writeDebugLogToFile ? getDebugLogFilePath().c_str() : "");
    CCLOG("    listen: %s", _bindAddress.c_str());

    if (_debuggerType == kCCRuntimeDebuggerLDT)
    {
        CCLOG("    debugger: Eclipse LDT");
    }
    else if (_debuggerType == kCCRuntimeDebuggerCodeIDE)
    {
        CCLOG("    debugger: Cocos Code IDE");
    }
    else if (_debuggerType == kCCRuntimeDebuggerStudio)
    {
        CCLOG("    debugger: Cocos Studio");
    }
    else
    {
        CCLOG("    debugger: none");
    }

    CCLOG("    add searching path:");
    for (auto &path : _searchPath)
    {
        CCLOG("        %s", path.c_str());
    }

    CCLOG("\n\n");
}

void ProjectConfig::normalize()
{
    SimulatorConfig::makeNormalizePath(&_projectDir);
    SimulatorConfig::makeNormalizePath(&_scriptFile);
    SimulatorConfig::makeNormalizePath(&_writablePath);
    SimulatorConfig::makeNormalizePath(&_packagePath);

    // projectDir
    size_t len = _projectDir.length();
    if (len > 0 && _projectDir[len - 1] != DIRECTORY_SEPARATOR_CHAR)
    {
        _projectDir.append(DIRECTORY_SEPARATOR);
        len++;
    }

    // writablePath
    if (len > 0 && _writablePath.length() == 0)
    {
        _writablePath = _projectDir;
    }
    len = _writablePath.length();
    if (len > 0 && _writablePath[len - 1] != DIRECTORY_SEPARATOR_CHAR)
    {
        _writablePath.append(DIRECTORY_SEPARATOR);
    }
    _writablePath = replaceProjectDirToMacro(_writablePath);

    // scriptFile
    _scriptFile = replaceProjectDirToMacro(_scriptFile);

    // package.path
    vector<string> arr = getPackagePathArray();
    _packagePath = string("");
    for (auto it = arr.begin(); it != arr.end(); ++it)
    {
        string path = replaceProjectDirToMacro(*it);
        _packagePath.append(path);
        _packagePath.append(";");
    }
    if (_packagePath.length() > 0 && _packagePath[_packagePath.length() - 1] == ';')
    {
        _packagePath = _packagePath.substr(0, _packagePath.length() - 1);
    }
}

string ProjectConfig::replaceProjectDirToMacro(const string &path) const
{
    if (!isAbsolutePath(path))
    {
        if (path.compare(0, 10, "$(PROJDIR)") == 0) return path;
        string result("$(PROJDIR)");
        result.append(DIRECTORY_SEPARATOR);
        result.append(path);
        return result;
    }

    string result = path;
    size_t len = _projectDir.length();
    if (len > 0 && result.compare(0, len, _projectDir) == 0)
    {
        result = "$(PROJDIR)";
        result.append(DIRECTORY_SEPARATOR);
        result.append(path.substr(len));
    }
    return result;
}

string ProjectConfig::replaceProjectDirToFullPath(const string &path) const
{
    if (isAbsolutePath(path)) return path;

    if (path.length() == 0) return _projectDir;

    string result = path;
    if (path.compare(0, 10, "$(PROJDIR)") == 0)
    {
        result = _projectDir;
        string suffix = path.substr(10);
        if (suffix[0] == DIRECTORY_SEPARATOR_CHAR)
        {
            suffix = suffix.substr(1);
        }
        result.append(suffix);
    }
    return result;
}

bool ProjectConfig::isAbsolutePath(const string &path) const
{
#if defined(_WINDOWS)
    return path.length() > 2 && path[1] == ':';
#else
    return path.length() > 0 && path[0] == '/';
#endif
}

string ProjectConfig::dealWithSpaceWithPath(const string &path) const
{
#if defined(_WINDOWS)
    string ret("\"");
    ret += path;
    if (path[path.length() - 1] == '\\')
    {
        ret += "\\";
    }
    ret += "\"";
    return ret;
#else
    return path;
#endif
}
