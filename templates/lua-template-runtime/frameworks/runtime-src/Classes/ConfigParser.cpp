
#include "json/document.h"
#include "json/filestream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "ConfigParser.h"
#include "FileServer.h"

#define CONFIG_FILE "config.json"
#define CONSOLE_PORT 6010
#define UPLOAD_PORT 6020
#define WIN_WIDTH   960
#define WIN_HEIGHT  640

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

void ConfigParser::readConfig()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // add writable path to search path temporarily for reading config file
    vector<std::string> searchPathArray = FileUtils::getInstance()->getSearchPaths();
    searchPathArray.insert(searchPathArray.begin(), FileServer::getShareInstance()->getWritePath());
    FileUtils::getInstance()->setSearchPaths(searchPathArray);
#endif
    
    // read config file
    string fullPathFile = FileUtils::getInstance()->fullPathForFilename(CONFIG_FILE);
    string fileContent = FileUtils::getInstance()->getStringFromFile(fullPathFile);
  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // revert search path
    searchPathArray.erase(searchPathArray.end() - 1);
    FileUtils::getInstance()->setSearchPaths(searchPathArray);
#endif

    if(fileContent.empty())
        return;
    
    if (_docRootjson.Parse<0>(fileContent.c_str()).HasParseError()) {
        cocos2d::log("read json file %s failed because of %s", fullPathFile.c_str(), _docRootjson.GetParseError());
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
                _entryfile = objectInitView["entry"].GetString();
            }
            if (objectInitView.HasMember("consolePort"))
            {
                _consolePort = objectInitView["consolePort"].GetUint();
                if(_consolePort <= 0)
                    _consolePort = CONSOLE_PORT;
            }
            if (objectInitView.HasMember("uploadPort"))
            {
                _uploadPort = objectInitView["uploadPort"].GetUint();
                if(_uploadPort <= 0)
                    _uploadPort = UPLOAD_PORT;
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
}

ConfigParser::ConfigParser(void) :
_isLandscape(true),
_isWindowTop(false),
_consolePort(CONSOLE_PORT),
_uploadPort(UPLOAD_PORT),
_viewName("HelloLua"),
_entryfile("src/main.lua"),
_initViewSize(WIN_WIDTH, WIN_HEIGHT)
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

bool ConfigParser::isLanscape()
{
    return _isLandscape;
}

bool ConfigParser::isWindowTop()
{
    return _isWindowTop;
}
int ConfigParser::getConsolePort()
{
    return _consolePort;
}
int ConfigParser::getUploadPort()
{
    return _uploadPort;
}
int ConfigParser::getScreenSizeCount(void)
{
    return (int)_screenSizeArray.size();
}

const SimulatorScreenSize ConfigParser::getScreenSize(int index)
{
    return _screenSizeArray.at(index);
}
