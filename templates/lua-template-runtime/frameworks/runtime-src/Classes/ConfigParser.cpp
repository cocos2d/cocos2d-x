
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

void ConfigParser::readConfig()
{
    _initViewSize.setSize(960,640);
    _viewName="HelloLua";
    string filecfg = "res/config.json";
    string fullPathFile = FileUtils::getInstance()->fullPathForFilename(filecfg);
    FILE * pFile = fopen (fullPathFile.c_str() , "r");
    if(pFile)
    {
        rapidjson::FileStream inputStream(pFile);
        rapidjson::Document runtimecfgjson; 
        runtimecfgjson.ParseStream<0>(inputStream);
        fclose(pFile);
        if (runtimecfgjson.HasMember("init_view") && runtimecfgjson["init_view"].IsObject())
        {
            const rapidjson::Value& objectInitView = runtimecfgjson["init_view"];
            if (objectInitView.HasMember("width") && objectInitView.HasMember("height"))
            {
                _initViewSize.width = objectInitView["width"].GetUint();
                _initViewSize.height = objectInitView["height"].GetUint();
            }
            if (objectInitView.HasMember("name"))
            {
                _viewName = objectInitView["name"].GetString();
            }
            
        }
        if (runtimecfgjson.HasMember("simulator_screen_size"))
        {
            const rapidjson::Value& ArrayScreenSize = runtimecfgjson["simulator_screen_size"];
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

ConfigParser::ConfigParser(void)
{

}
string ConfigParser::getInitViewName()
{
    return _viewName;
}

Size ConfigParser::getInitViewSize()
{
    return _initViewSize;
}

int ConfigParser::getScreenSizeCount(void)
{
    return (int)_screenSizeArray.size();
}

const SimulatorScreenSize ConfigParser::getScreenSize(int index)
{
    return _screenSizeArray.at(index);
}
