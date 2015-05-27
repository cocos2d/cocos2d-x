
#include "json/document.h"
#include "json/filestream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "SimpleConfigParser.h"

// SimpleConfigParser
SimpleConfigParser *SimpleConfigParser::s_sharedSimpleConfigParserInstance = NULL;
SimpleConfigParser *SimpleConfigParser::getInstance(void)
{
    if (!s_sharedSimpleConfigParserInstance)
    {
        s_sharedSimpleConfigParserInstance = new SimpleConfigParser();
        s_sharedSimpleConfigParserInstance->readConfig();
    }
    return s_sharedSimpleConfigParserInstance;
}

void SimpleConfigParser::purge()
{
	CC_SAFE_DELETE(s_sharedSimpleConfigParserInstance);
}

void SimpleConfigParser::readConfig(const string &filepath)
{
    string fullPathFile = filepath;
    
    // read config file
    if (fullPathFile.empty())
    {
        fullPathFile = FileUtils::getInstance()->fullPathForFilename(CONFIG_FILE);
    }
    string fileContent = FileUtils::getInstance()->getStringFromFile(fullPathFile);

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
            if (objectInitView.HasMember("isLandscape") && objectInitView["isLandscape"].IsBool())
            {
                _isLandscape = objectInitView["isLandscape"].GetBool();
            }
        }
    }
}

SimpleConfigParser::SimpleConfigParser(void) :
_isLandscape(true)
{
}

rapidjson::Document& SimpleConfigParser::getConfigJsonRoot()
{
    return _docRootjson;
}

bool SimpleConfigParser::isLanscape()
{
    return _isLandscape;
}
