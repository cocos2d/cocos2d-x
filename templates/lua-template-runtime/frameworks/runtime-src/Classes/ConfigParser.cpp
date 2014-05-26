
#include "json/document.h"
#include "json/filestream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "ConfigParser.h"

// ConfigParser
ConfigParser *ConfigParser::s_sharedInstance = NULL;
ConfigParser *ConfigParser::getInstance(void)
{
    if (!s_sharedInstance)
    {
        s_sharedInstance = new ConfigParser();
    }
    return s_sharedInstance;
}

bool ConfigParser::isInit()
{
    return _isInit;
}

void ConfigParser::readConfig()
{
    _isInit = true;
    string filecfg = "config.json";
    
    string fileContent;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && !defined(NDEBUG)) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS && defined(COCOS2D_DEBUG))
    string fullPathFile = FileUtils::getInstance()->getWritablePath();
    fullPathFile.append("debugruntime/");
    fullPathFile.append(filecfg.c_str());
    fileContent=FileUtils::getInstance()->getStringFromFile(fullPathFile.c_str());
#endif

    if (fileContent.empty()) {
        filecfg=FileUtils::getInstance()->fullPathForFilename(filecfg.c_str());
        fileContent=FileUtils::getInstance()->getStringFromFile(filecfg.c_str());
    }

    if(!fileContent.empty())
    {
        _docRootjson.Parse<0>(fileContent.c_str());
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
                        float tmpvalue =_initViewSize.height;
                        _initViewSize.height = _initViewSize.width;
                         _initViewSize.width = tmpvalue;
                    }
                    
                }
                if (objectInitView.HasMember("name") && objectInitView["name"].IsString())
                {
                    _viewName = objectInitView["name"].GetString();
                }
                if (objectInitView.HasMember("isLandscape") && objectInitView["isLandscape"].IsBool()) {
                    _isLandscape = objectInitView["isLandscape"].GetBool();
                }
                if (objectInitView.HasMember("entry") && objectInitView["entry"].IsString()) {
                    _entryfile = objectInitView["entry"].GetString();
                }
            }
        }
        if (_docRootjson.HasMember("simulator_screen_size"))
        {
            const rapidjson::Value& ArrayScreenSize = _docRootjson["simulator_screen_size"];
            if (ArrayScreenSize.IsArray())
            {
                for (int i=0; i<ArrayScreenSize.Size(); i++)
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

}

ConfigParser::ConfigParser(void):_isInit(false),_isLandscape(true)
{
    _initViewSize.setSize(960,640);
    _viewName = "HelloLua";
    _entryfile = "src/main.lua";
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

int ConfigParser::getScreenSizeCount(void)
{
    return (int)_screenSizeArray.size();
}

const SimulatorScreenSize ConfigParser::getScreenSize(int index)
{
    return _screenSizeArray.at(index);
}
