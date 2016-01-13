
#include "json/document.h"
#include "json/filestream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "ConfigParser.h"
#include "FileServer.h"

// ConfigParser
ConfigParser *ConfigParser::s_sharedConfigParserInstance = NULL;
ConfigParser *ConfigParser::getInstance(void)
{
    if (!s_sharedConfigParserInstance)
    {
        s_sharedConfigParserInstance = new ConfigParser();
        s_sharedConfigParserInstance->readConfig();
    }
    return s_sharedConfigParserInstance;
}

void ConfigParser::purge()
{
	CC_SAFE_DELETE(s_sharedConfigParserInstance);
}

void ConfigParser::readConfig(const string &filepath)
{
    string fullPathFile = filepath;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // add writable path to search path temporarily for reading config file
    vector<std::string> searchPathArray = FileUtils::getInstance()->getSearchPaths();
    searchPathArray.insert(searchPathArray.begin(), FileServer::getShareInstance()->getWritePath());
    FileUtils::getInstance()->setSearchPaths(searchPathArray);
#endif
    
    // read config file
    if (fullPathFile.empty())
    {
        fullPathFile = FileUtils::getInstance()->fullPathForFilename(CONFIG_FILE);
    }
    string fileContent = FileUtils::getInstance()->getStringFromFile(fullPathFile);
  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // revert search path
    searchPathArray.erase(searchPathArray.end() - 1);
    FileUtils::getInstance()->setSearchPaths(searchPathArray);
#endif

    if(fileContent.empty())
        return;
    
    if (_docRootjson.Parse<0>(fileContent.c_str()).HasParseError()) {
        cocos2d::log("read json file %s failed because of %d", fullPathFile.c_str(), _docRootjson.GetParseError());
        return;
    }
    
    if (_docRootjson.HasMember("init_cfg"))
    {
        if(_docRootjson["init_cfg"].IsObject())
        {
            const rapidjson::Value& objectInitView = _docRootjson["init_cfg"];
            if (objectInitView.HasMember("width") && objectInitView.HasMember("height"))
            {
                _initViewSize.width = objectInitView["width"].GetUint();
                _initViewSize.height = objectInitView["height"].GetUint();
                if (_initViewSize.height>_initViewSize.width)
                {
                    float tmpvalue = _initViewSize.height;
                    _initViewSize.height = _initViewSize.width;
                    _initViewSize.width = tmpvalue;
                }
                
            }
            if (objectInitView.HasMember("designWidth") && objectInitView.HasMember("designHeight"))
            {
                _initDesignResolutionSize.width = objectInitView["designWidth"].GetUint();
                _initDesignResolutionSize.height = objectInitView["designHeight"].GetUint();
                if (_initDesignResolutionSize.height>_initDesignResolutionSize.width)
                {
                    float tmpvalue = _initDesignResolutionSize.height;
                    _initDesignResolutionSize.height = _initDesignResolutionSize.width;
                    _initDesignResolutionSize.width = tmpvalue;
                }

            }
            else
            {
                _initDesignResolutionSize = _initViewSize;
            }
            if (objectInitView.HasMember("designResolutionPolicy") && objectInitView["designResolutionPolicy"].IsString())
            {
                std::string policyStr = objectInitView["designResolutionPolicy"].GetString();
                ResolutionPolicy policy;

                if (policyStr.compare("EXACT_FIT") == 0)
                {
                    policy = ResolutionPolicy::EXACT_FIT;
                }
                else if (policyStr.compare("NO_BORDER")  == 0)
                {
                    policy = ResolutionPolicy::NO_BORDER;
                }
                else if (policyStr.compare("SHOW_ALL")  == 0)
                {
                    policy = ResolutionPolicy::SHOW_ALL;
                }
                else if (policyStr.compare("FIXED_HEIGHT")  == 0)
                {
                    policy = ResolutionPolicy::FIXED_HEIGHT;
                }
                else if (policyStr.compare("FIXED_WIDTHT")  == 0)
                {
                    policy = ResolutionPolicy::FIXED_WIDTH;
                }
                else
                {
                    policy = ResolutionPolicy::UNKNOWN;
                }

                _initDesignResolutionPolicy = policy;

            }
            if (objectInitView.HasMember("designContentScaleFactor") && objectInitView["designContentScaleFactor"].IsDouble())
            {
                _initDesignContentScaleFactor = (float)objectInitView["designContentScaleFactor"].GetDouble();

            }
            if (objectInitView.HasMember("name") && objectInitView["name"].IsString())
            {
                _viewName = objectInitView["name"].GetString();
            }
            if (objectInitView.HasMember("isLandscape") && objectInitView["isLandscape"].IsBool())
            {
                _isLandscape = objectInitView["isLandscape"].GetBool();
            }
            if (objectInitView.HasMember("entry") && objectInitView["entry"].IsString())
            {
                setEntryFile(objectInitView["entry"].GetString());
            }
            if (objectInitView.HasMember("consolePort"))
            {
                setConsolePort(objectInitView["consolePort"].GetUint());
            }
            if (objectInitView.HasMember("debugPort"))
            {
                setDebugPort(objectInitView["debugPort"].GetUint());
            }
            if (objectInitView.HasMember("uploadPort"))
            {
                setUploadPort(objectInitView["uploadPort"].GetUint());
            }
            if (objectInitView.HasMember("isWindowTop") && objectInitView["isWindowTop"].IsBool())
            {
                _isWindowTop= objectInitView["isWindowTop"].GetBool();
            }
        }
    }
    if (_docRootjson.HasMember("simulator_screen_size"))
    {
        const rapidjson::Value& ArrayScreenSize = _docRootjson["simulator_screen_size"];
        if (ArrayScreenSize.IsArray())
        {
            _screenSizeArray.clear();
            for (int i = 0; i < ArrayScreenSize.Size(); i++)
            {
                const rapidjson::Value& objectScreenSize = ArrayScreenSize[i];
                if (objectScreenSize.HasMember("title") && objectScreenSize.HasMember("width") && objectScreenSize.HasMember("height"))
                {
                    _screenSizeArray.push_back(SimulatorScreenSize(objectScreenSize["title"].GetString(), objectScreenSize["width"].GetUint(), objectScreenSize["height"].GetUint()));
                }
            }
        }
    }
    if (_docRootjson.HasMember("design_resolution_size"))
    {
        const rapidjson::Value& ArrayScreenSize = _docRootjson["design_resolution_size"];
        if (ArrayScreenSize.IsArray())
        {
            _designResolutionSizeArray.clear();
            for (int i = 0; i < ArrayScreenSize.Size(); i++)
            {
                const rapidjson::Value& objectScreenSize = ArrayScreenSize[i];
                if (objectScreenSize.HasMember("title") && objectScreenSize.HasMember("width") && objectScreenSize.HasMember("height"))
                {
                    _designResolutionSizeArray.push_back(SimulatorScreenSize(objectScreenSize["title"].GetString(), objectScreenSize["width"].GetUint(), objectScreenSize["height"].GetUint()));
                }
            }
        }
    }
    if (_docRootjson.HasMember("design_content_scale_factor"))
    {
        const rapidjson::Value& ContentScaleFactor = _docRootjson["design_content_scale_factor"];
        if (ContentScaleFactor.IsArray())
        {
            _designContentScaleFactorArray.clear();
            for (int i = 0; i < ContentScaleFactor.Size(); i++)
            {
                const rapidjson::Value& objectScaleFactor = ContentScaleFactor[i];
                if (objectScaleFactor.HasMember("title") && objectScaleFactor.HasMember("scale"))
                {
                    float scaleFactor = (float)objectScaleFactor["scale"].GetDouble();
                    _designContentScaleFactorArray.push_back(SimulatorDesignContentScaleFactor(objectScaleFactor["title"].GetString(), scaleFactor));
                }
            }
        }
    }

}

ConfigParser::ConfigParser(void) :
_isLandscape(true),
_isWindowTop(false),
_consolePort(kProjectConfigConsolePort),
_uploadPort(kProjectConfigUploadPort),
_debugPort(kProjectConfigDebugger),
_viewName("simulator"),
_entryfile(""),
_initViewSize(ProjectConfig::DEFAULT_HEIGHT, ProjectConfig::DEFAULT_WIDTH),
_initDesignResolutionSize(ProjectConfig::DEFAULT_HEIGHT, ProjectConfig::DEFAULT_WIDTH),
_initDesignResolutionPolicy(ProjectConfig::DEFAULT_RESOLUTION_POLICY),
_initDesignContentScaleFactor(ProjectConfig::DEFAULT_CONTENT_SCALE_FACTOR),
_bindAddress("")
{
}

rapidjson::Document& ConfigParser::getConfigJsonRoot()
{
    return _docRootjson;
}

string ConfigParser::getInitViewName()
{
    return _viewName;
}

string ConfigParser::getEntryFile()
{
    return _entryfile;
}

Size ConfigParser::getInitViewSize()
{
    return _initViewSize;
}

Size ConfigParser::getInitDesignResolutionSize()
{
    return _initDesignResolutionSize;
}

ResolutionPolicy ConfigParser::getInitDesignResolutionPolicy()
{
    return _initDesignResolutionPolicy;
}

float ConfigParser::getInitDesignContentScaleFactor()
{
    return _initDesignContentScaleFactor;
}

bool ConfigParser::isLanscape()
{
    return _isLandscape;
}

bool ConfigParser::isWindowTop()
{
    return _isWindowTop;
}
void ConfigParser::setConsolePort(int port)
{
    if (port > 0)
    {
        _consolePort = port;
    }
}
void ConfigParser::setUploadPort(int port)
{
    if (port > 0)
    {
        _uploadPort = port;
    }
}
void ConfigParser::setDebugPort(int port)
{
    if (port > 0)
    {
        _debugPort = port;
    }
}
int ConfigParser::getConsolePort()
{
    return _consolePort;
}
int ConfigParser::getUploadPort()
{
    return _uploadPort;
}
int ConfigParser::getDebugPort()
{
    return _debugPort;
}
int ConfigParser::getScreenSizeCount(void)
{
    return (int)_screenSizeArray.size();
}
int ConfigParser::getDesignResolutionSizeCount(void)
{
    return (int)_designResolutionSizeArray.size();
}

int ConfigParser::getDesignContentScaleFactorCount(void)
{
    return (int)_designContentScaleFactorArray.size();
}

const SimulatorScreenSize ConfigParser::getScreenSize(int index)
{
    return _screenSizeArray.at(index);
}

const SimulatorScreenSize ConfigParser::getDesignResolutionSize(int index)
{
    return _designResolutionSizeArray.at(index);
}

const SimulatorDesignContentScaleFactor ConfigParser::getDesignContentScaleFactor(int index)
{
    return _designContentScaleFactorArray.at(index);
}

void ConfigParser::setEntryFile(const std::string &file)
{
    _entryfile = file;
}

void ConfigParser::setInitViewSize(const cocos2d::Size &size)
{
    _initViewSize = size;
}

void ConfigParser::setInitDesignResolutionSize(const cocos2d::Size &size)
{
    _initDesignResolutionSize = size;
}

void ConfigParser::setInitDesignResolutionPolicy(ResolutionPolicy policy)
{
    _initDesignResolutionPolicy = policy;
}

void ConfigParser::setInitDesignContentScaleFactor(float scaleFactor)
{
    _initDesignContentScaleFactor = scaleFactor;
}

void ConfigParser::setBindAddress(const std::string &address)
{
    _bindAddress = address;
}

const std::string &ConfigParser::getBindAddress()
{
    return _bindAddress;
}
