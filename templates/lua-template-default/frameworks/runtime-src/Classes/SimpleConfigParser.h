#ifndef __SIMPLE_CONFIG_PARSER_H__
#define __SIMPLE_CONFIG_PARSER_H__

#include <string>
#include <vector>
#include "cocos2d.h"
#include "json/document.h"
using namespace std;
USING_NS_CC;

#define CONFIG_FILE "config.json"

class SimpleConfigParser
{
public:
    static SimpleConfigParser *getInstance(void);
    static void purge();

    void readConfig(const string &filepath = "");
    bool isLanscape();
    rapidjson::Document& getConfigJsonRoot();
private:
    SimpleConfigParser(void);
    static SimpleConfigParser *s_sharedSimpleConfigParserInstance;
    bool _isLandscape;
    
    rapidjson::Document _docRootjson;
};

#endif  // __SIMPLE_CONFIG_PARSER_H__

