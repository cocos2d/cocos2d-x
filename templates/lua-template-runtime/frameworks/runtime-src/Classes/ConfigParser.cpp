
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
    string filecfg = "res/config.json";
    string fullPathFile = FileUtils::getInstance()->fullPathForFilename(filecfg);
    FILE * pFile = fopen (fullPathFile.c_str() , "r");
    if(pFile)
    {
        rapidjson::FileStream inputStream(pFile);
        _docRootjson.ParseStream<0>(inputStream);
        fclose(pFile);
        if (_docRootjson.HasMember("init_cfg") && _docRootjson["init_cfg"].IsObject())
        {
            const rapidjson::Value& objectInitView = _docRootjson["init_cfg"];
            if (objectInitView.HasMember("width") && objectInitView.HasMember("height"))
            {
                _initViewSize.width = objectInitView["width"].GetUint();
                _initViewSize.height = objectInitView["height"].GetUint();
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
