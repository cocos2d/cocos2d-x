
#include "SimulatorConfig.h"
#include <sstream>

#ifdef _MSC_VER
#define strcasecmp _stricmp
#endif

bool ProjectConfig::isWelcome(void)
{
    return m_isWelcome;
}

void ProjectConfig::resetToWelcome(void)
{
	m_isWelcome = true;
    string path = SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath();
    path.append("player/welcome");
    SimulatorConfig::makeNormalizePath(&path);
    setProjectDir(path);
    setWritablePath(path);
    setScriptFile("$PROJDIR/scripts/main.lua");
    setFrameSize(CCSize(960, 640));
    setFrameScale(1.0f);
    setLoadPrecompiledFramework(true);
    setPackagePath("");
    setShowConsole(true);
    setWindowOffset(CCPointZero);
    setWriteDebugLogToFile(false);
}

const string ProjectConfig::getProjectDir(void)
{
    return m_projectDir;
}

void ProjectConfig::setProjectDir(const string projectDir)
{
    m_projectDir = projectDir;
    normalize();
}

const string ProjectConfig::getScriptFile(void)
{
    return m_scriptFile;
}

const string ProjectConfig::getScriptFileRealPath(void)
{
    return replaceProjectDirToFullPath(m_scriptFile);
}

void ProjectConfig::setScriptFile(const string scriptFile)
{
    m_scriptFile = scriptFile;
    normalize();
}

const string ProjectConfig::getWritablePath(void)
{
    return m_writablePath;
}

const string ProjectConfig::getWritableRealPath(void)
{
    return replaceProjectDirToFullPath(m_writablePath);
}

void ProjectConfig::setWritablePath(const string writablePath)
{
    m_writablePath = writablePath;
    normalize();
}

const string ProjectConfig::getPackagePath(void)
{
    return m_packagePath;
}

const string ProjectConfig::getNormalizedPackagePath(void)
{
    // replace $PROJDIR
    string path = m_packagePath;
    size_t pos = std::string::npos;
    while ((pos = path.find("$PROJDIR")) != std::string::npos)
    {
        path = path.substr(0, pos) + m_projectDir + path.substr(pos + 8);
    }
    size_t len = path.length();
    if (len && path[len - 1] != ';')
    {
        path.append(";");
    }
    path.append(";");
    SimulatorConfig::makeNormalizePath(&path, "/");
    return path;
}

void ProjectConfig::setPackagePath(const string packagePath)
{
    m_packagePath = packagePath;
}

void ProjectConfig::addPackagePath(const string packagePath)
{
    if (packagePath.length())
    {
        if (m_packagePath.length())
        {
            m_packagePath.append(";");
        }
        m_packagePath.append(packagePath);
        normalize();
    }
}

const vector<string> ProjectConfig::getPackagePathArray(void)
{
    vector<string> arr;

    size_t pos = std::string::npos;
    size_t prev = 0;
    while ((pos = m_packagePath.find_first_of(";", pos + 1)) != std::string::npos)
    {
        string path = m_packagePath.substr(prev, pos - prev);
        if (path.length() > 0) arr.push_back(path);
        prev = pos + 1;
    }
    string path = m_packagePath.substr(prev);
    if (path.length() > 0) arr.push_back(path);
    return arr;
}

const CCSize ProjectConfig::getFrameSize(void)
{
    return m_frameSize;
}

void ProjectConfig::setFrameSize(CCSize frameSize)
{
    if (frameSize.width <= 0 || frameSize.width > 2048 || frameSize.height <= 0 || frameSize.height > 2048) return;
    m_frameSize = frameSize;
}

bool ProjectConfig::isLandscapeFrame(void)
{
    return m_frameSize.width > m_frameSize.height;
}

void ProjectConfig::changeFrameOrientation(void)
{
    float w = m_frameSize.width;
    m_frameSize.width = m_frameSize.height;
    m_frameSize.height = w;
}

void ProjectConfig::changeFrameOrientationToPortait(void)
{
    if (isLandscapeFrame()) changeFrameOrientation();
}

void ProjectConfig::changeFrameOrientationToLandscape(void)
{
    if (!isLandscapeFrame()) changeFrameOrientation();
}

const float ProjectConfig::getFrameScale(void)
{
    return m_frameScale;
}

void ProjectConfig::setFrameScale(float frameScale)
{
    CCAssert(frameScale > 0, "Invalid frameScale");
    m_frameScale = frameScale;
}

const bool ProjectConfig::isShowConsole(void)
{
    return m_showConsole;
}

void ProjectConfig::setShowConsole(bool showConsole)
{
    m_showConsole = showConsole;
}

bool ProjectConfig::isLoadPrecompiledFramework(void)
{
    return m_loadPrecompiledFramework;
}

void ProjectConfig::setLoadPrecompiledFramework(bool load)
{
    m_loadPrecompiledFramework = load;
}

const bool ProjectConfig::isWriteDebugLogToFile(void)
{
    return m_writeDebugLogToFile;
}

void ProjectConfig::setWriteDebugLogToFile(bool writeDebugLogToFile)
{
    m_writeDebugLogToFile = writeDebugLogToFile;
}

const string ProjectConfig::getDebugLogFilePath(void)
{
    string path(getProjectDir());
    path.append("debug.log");
    return path;
}

const CCPoint ProjectConfig::getWindowOffset(void)
{
    return m_windowOffset;
}

void ProjectConfig::setWindowOffset(CCPoint windowOffset)
{
    m_windowOffset = windowOffset;
}

int ProjectConfig::getDebuggerType(void)
{
    return m_debuggerType;
}

void ProjectConfig::setDebuggerType(int debuggerType)
{
    m_debuggerType = debuggerType;
}

bool ProjectConfig::isExitWhenRelaunch(void)
{
    return m_exitWhenRelaunch;
}

void ProjectConfig::setExitWhenRelaunch(bool isExitWhenRelaunch)
{
    m_exitWhenRelaunch = isExitWhenRelaunch;
}

void ProjectConfig::parseCommandLine(vector<string>& args)
{
    vector<string>::iterator it = args.begin();
    while (it != args.end())
    {
        const string& arg = *it;

        if (arg.compare("-quick") == 0)
        {
            ++it;
            if (it == args.end()) break;
            SimulatorConfig::sharedDefaults()->setQuickCocos2dxRootPath((*it).c_str());
        }
        else if (arg.compare("-workdir") == 0)
        {
            ++it;
            if (it == args.end()) break;
            setProjectDir(*it);
            if (m_writablePath.length() == 0) setWritablePath(*it);
        }
        else if (arg.compare("-writable") == 0)
        {
            ++it;
            if (it == args.end()) break;
            setWritablePath(*it);
        }
        else if (arg.compare("-file") == 0)
        {
            ++it;
            if (it == args.end()) break;
            setScriptFile(*it);
        }
        else if (arg.compare("-package.path") == 0)
        {
            ++it;
            if (it == args.end()) break;
            setPackagePath(*it);
        }
        else if (arg.compare("-landscape") == 0)
        {
            setFrameSize(CCSize(DEFAULT_HEIGHT, DEFAULT_WIDTH));
        }
        else if (arg.compare("-portrait") == 0)
        {
            setFrameSize(CCSize(DEFAULT_WIDTH, DEFAULT_HEIGHT));
        }
        else if (arg.compare("-size") == 0)
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
                setFrameSize(CCSize(width, height));
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
            setWriteDebugLogToFile(true);
        }
        else if (arg.compare("-disable-write-debug-log") == 0)
        {
            setWriteDebugLogToFile(false);
        }
        else if (arg.compare("-console") == 0)
        {
            setShowConsole(true);
        }
        else if (arg.compare("-disable-console") == 0)
        {
            setShowConsole(false);
        }
        else if (arg.compare("-load-framework") == 0)
        {
            setLoadPrecompiledFramework(true);
        }
        else if (arg.compare("-disable-load-framework") == 0)
        {
            setLoadPrecompiledFramework(false);
        }
        else if (arg.compare("-offset") == 0)
        {
            ++it;
            if (it == args.end()) break;
            CCPoint pos = CCPointFromString((*it).c_str());
            setWindowOffset(pos);
        }
        else if (arg.compare("-debugger-ldt") == 0)
        {
            setDebuggerType(kCCLuaDebuggerLDT);
        }
        else if (arg.compare("-disable-debugger") == 0)
        {
            setDebuggerType(kCCLuaDebuggerNone);
        }
        else if (arg.compare("-relaunch-off") == 0)
        {
            setExitWhenRelaunch(true);
        }
        else if (arg.compare("-relaunch-on") == 0)
        {
            setExitWhenRelaunch(false);
        }

        ++it;
    }
}

const string ProjectConfig::makeCommandLine(unsigned int mask /* = kProjectConfigAll */)
{
    stringstream buff;

    if (mask & kProjectConfigQuickRootPath)
    {
        const string path = SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath();
        if (path.length())
        {
            buff << " -quick ";
            buff << path;
        }
    }

    if (mask & kProjectConfigProjectDir)
    {
		const string path = getProjectDir();
		if (path.length())
		{
			buff << " -workdir ";
			buff << path;
		}
    }

    if (mask & kProjectConfigScriptFile)
    {
		const string path = getScriptFileRealPath();
		if (path.length())
		{
			buff << " -file ";
			buff << path;
		}
    }

    if (mask & kProjectConfigWritablePath)
    {
		const string path = getWritableRealPath();
		if (path.length())
		{
			buff << " -writable ";
			buff << path;
		}
    }

    if (mask & kProjectConfigPackagePath)
    {
        const string packagePath = getPackagePath();
        if (packagePath.length())
        {
            buff << " -package.path ";
            buff << packagePath;
        }
    }

    if (mask & kProjectConfigFrameSize)
    {
        buff << " -size ";
        buff << (int)getFrameSize().width;
        buff << "x";
        buff << (int)getFrameSize().height;
    }

    if (mask & kProjectConfigFrameScale)
    {
        if (getFrameScale() < 1.0f)
        {
            buff << " -scale ";
            buff.precision(2);
            buff << getFrameScale();
        }
    }

    if (mask & kProjectConfigWriteDebugLogToFile)
    {
        if (isWriteDebugLogToFile())
        {
            buff << " -write-debug-log";
        }
        else
        {
            buff << " -disable-write-debug-log";
        }
    }

    if (mask & kProjectConfigShowConsole)
    {
        if (isShowConsole())
        {
            buff << " -console";
        }
        else
        {
            buff << " -disable-console";
        }
    }

    if (mask & kProjectConfigLoadPrecompiledFramework)
    {
        if (isLoadPrecompiledFramework())
        {
            buff << " -load-framework";
        }
        else
        {
            buff << " -disable-load-framework";
        }
    }

    if (mask & kProjectConfigWindowOffset)
    {
        if (m_windowOffset.x != 0 && m_windowOffset.y != 0)
        {
            buff << " -offset {";
            buff << (int)m_windowOffset.x;
            buff << ",";
            buff << (int)m_windowOffset.y;
            buff << "}";
        }
    }

    if (mask & kProjectConfigDebugger)
    {
        switch (getDebuggerType())
        {
            case kCCLuaDebuggerLDT:
                buff << " -debugger-ldt";
                break;
            case kCCLuaDebuggerNone:
            default:
                buff << " -disable-debugger";
        }
    }

    return buff.str();
}

bool ProjectConfig::validate(void)
{
    CCFileUtils *utils = CCFileUtils::sharedFileUtils();
    if (!utils->isDirectoryExist(m_projectDir)) return false;
    if (!utils->isDirectoryExist(getWritableRealPath())) return false;
    if (!utils->isFileExist(getScriptFileRealPath())) return false;
    return true;
}

void ProjectConfig::dump(void)
{
    CCLog("Project Config:");
    CCLog("    quick root path: %s", SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().c_str());
    CCLog("    project dir: %s", m_projectDir.c_str());
    CCLog("    writable path: %s", m_writablePath.length() ? m_writablePath.c_str() : "-");
    CCLog("    script file: %s", m_scriptFile.c_str());
    CCLog("    package.path: %s", m_packagePath.length() ? m_packagePath.c_str() : "-");
    CCLog("    frame size: %0.0f x %0.0f", m_frameSize.width, m_frameSize.height);
    CCLog("    frame scale: %0.2f", m_frameScale);
    CCLog("    show console: %s", m_showConsole ? "YES" : "NO");
    CCLog("    write debug log: %s", m_writeDebugLogToFile ? "YES" : "NO");
    CCLog("    debugger: %s", m_debuggerType == kCCLuaDebuggerLDT ? "Eclipse LDT" : "NONE");
    CCLog("\n\n");
}

void ProjectConfig::normalize(void)
{
    SimulatorConfig::makeNormalizePath(&m_projectDir);
    SimulatorConfig::makeNormalizePath(&m_scriptFile);
    SimulatorConfig::makeNormalizePath(&m_writablePath);
    SimulatorConfig::makeNormalizePath(&m_packagePath);

    // projectDir
    size_t len = m_projectDir.length();
    if (len > 0 && m_projectDir[len - 1] != DIRECTORY_SEPARATOR_CHAR)
    {
        m_projectDir.append(DIRECTORY_SEPARATOR);
        len++;
    }

    // writablePath
    if (len > 0 && m_writablePath.length() == 0)
    {
        m_writablePath = m_projectDir;
    }
    len = m_writablePath.length();
    if (len > 0 && m_writablePath[len - 1] != DIRECTORY_SEPARATOR_CHAR)
    {
        m_writablePath.append(DIRECTORY_SEPARATOR);
    }
    m_writablePath = replaceProjectDirToMacro(m_writablePath);

    // scriptFile
    m_scriptFile = replaceProjectDirToMacro(m_scriptFile);

    // package.path
    vector<string> arr = getPackagePathArray();
    m_packagePath = string("");
    for (vector<string>::iterator it = arr.begin(); it != arr.end(); ++it)
    {
        string path = replaceProjectDirToMacro(*it);
        m_packagePath.append(path);
        m_packagePath.append(";");
    }
    if (m_packagePath.length() > 0 && m_packagePath[m_packagePath.length() - 1] == ';')
    {
        m_packagePath = m_packagePath.substr(0, m_packagePath.length() - 1);
    }
}

const string ProjectConfig::replaceProjectDirToMacro(const string& path)
{
    if (!isAbsolutePath(path))
    {
        if (path.compare(0, 8, "$PROJDIR") == 0) return path;
        string result("$PROJDIR");
        result.append(DIRECTORY_SEPARATOR);
        result.append(path);
        return result;
    }

    string result = path;
    size_t len = m_projectDir.length();
    if (len > 0 && result.compare(0, len, m_projectDir) == 0)
    {
        result = "$PROJDIR";
        result.append(DIRECTORY_SEPARATOR);
        result.append(path.substr(len));
    }
    return result;
}

const string ProjectConfig::replaceProjectDirToFullPath(const string& path)
{
    if (isAbsolutePath(path)) return path;

	if (path.length() == 0) return m_projectDir;

    string result = path;
    if (path.compare(0, 8, "$PROJDIR") == 0)
    {
        result = m_projectDir;
        string suffix = path.substr(8);
        if (suffix[0] == DIRECTORY_SEPARATOR_CHAR)
        {
            suffix = suffix.substr(1);
        }
        result.append(suffix);
    }
    return result;
}

bool ProjectConfig::isAbsolutePath(const string& path)
{
#ifdef CC_TARGET_QT
    return cocos2d::CCFileUtils::sharedFileUtils()->isAbsolutePath(path);
#endif
    if (DIRECTORY_SEPARATOR_CHAR == '/')
    {
        return path.length() > 0 && path[0] == '/';
    }
    return path.length() > 2 && path[1] == ':';
}


// SimulatorConfig

SimulatorConfig *SimulatorConfig::s_sharedInstance = NULL;

SimulatorConfig *SimulatorConfig::sharedDefaults(void)
{
    if (!s_sharedInstance)
    {
        s_sharedInstance = new SimulatorConfig();
    }
    return s_sharedInstance;
}

SimulatorConfig::SimulatorConfig(void)
{
    m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 3Gs (320x480)", 320, 480));
    m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 4 (640x960)", 640, 960));
    m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 5 (640x1136)", 640, 1136));
    m_screenSizeArray.push_back(SimulatorScreenSize("iPad (768x1024)", 768, 1024));
    m_screenSizeArray.push_back(SimulatorScreenSize("iPad Retina (1536x2048)", 1536, 2048));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (480x800)", 480, 800));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (480x854)", 480, 854));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (540x960)", 540, 960));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (600x1024)", 600, 1024));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (720x1280)", 720, 1280));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (800x1280)", 800, 1280));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (1080x1920)", 1080, 1920));
}

int SimulatorConfig::getScreenSizeCount(void)
{
    return (int)m_screenSizeArray.size();
}

const SimulatorScreenSize SimulatorConfig::getScreenSize(int index)
{
    return m_screenSizeArray.at(index);
}

int SimulatorConfig::checkScreenSize(const CCSize& size)
{
    int width = size.width;
    int height = size.height;

    if (width > height)
    {
        int w = width;
        width = height;
        height = w;
    }

    int count = (int)m_screenSizeArray.size();
    for (int i = 0; i < count; ++i)
    {
        const SimulatorScreenSize &size = m_screenSizeArray[i];
        if (size.width == width && size.height == height)
        {
            return i;
        }
    }

    return -1;
}


void SimulatorConfig::setQuickCocos2dxRootPath(const char *path)
{
    if (path)
    {
        m_quickCocos2dxRootPath = path;
        makeNormalizePath(&m_quickCocos2dxRootPath);
        if (m_quickCocos2dxRootPath[m_quickCocos2dxRootPath.length() - 1] != DIRECTORY_SEPARATOR_CHAR)
        {
            m_quickCocos2dxRootPath.append(DIRECTORY_SEPARATOR);
        }
    }
}

const string SimulatorConfig::getQuickCocos2dxRootPath(void)
{
    return m_quickCocos2dxRootPath;
}

// load framework
const string SimulatorConfig::getPrecompiledFrameworkPath(void)
{
    string path = m_quickCocos2dxRootPath;
    path.append("lib");
    path.append(DIRECTORY_SEPARATOR);
    path.append("framework_precompiled");
    path.append(DIRECTORY_SEPARATOR);
    path.append("framework_precompiled.zip");
    return path;
}


// helper

void SimulatorConfig::makeNormalizePath(string *path, const char *directorySeparator/* = NULL*/)
{
    if (!directorySeparator) directorySeparator = DIRECTORY_SEPARATOR;
    size_t pos = std::string::npos;
    while ((pos = path->find_first_of("/\\", pos + 1)) != std::string::npos)
    {
        path->replace(pos, 1, directorySeparator);
    }
}
