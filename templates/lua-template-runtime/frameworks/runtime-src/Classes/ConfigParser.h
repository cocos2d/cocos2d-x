#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__

#include <string>
#include <vector>
#include "cocos2d.h"
#include "json/document.h"
using namespace std;
USING_NS_CC;

// ConfigParser
typedef struct _SimulatorScreenSize {
    string title;
    int width;
    int height;

    _SimulatorScreenSize(const string title_, int width_, int height_)
    {
        title  = title_;
        width  = width_;
        height = height_;
    }
} SimulatorScreenSize;

typedef vector<SimulatorScreenSize> ScreenSizeArray;
class ConfigParser
{
public:
    static ConfigParser *getInstance(void);
	static void purge();

    // predefined screen size
    int getScreenSizeCount(void);
    cocos2d::Size getInitViewSize();
    string getInitViewName();
    string getEntryFile();
    rapidjson::Document& getConfigJsonRoot();
    const SimulatorScreenSize getScreenSize(int index);
    int getConsolePort();
    int getUploadPort();
    bool isLanscape();
    bool isWindowTop();
    
private:
    void readConfig();
    ConfigParser(void);
    static ConfigParser *s_sharedConfigParserInstance;
    ScreenSizeArray _screenSizeArray;
    cocos2d::Size _initViewSize;
    string _viewName;
    string _entryfile;
    bool _isLandscape;
    bool _isWindowTop;
    int _consolePort;
    int _uploadPort;
    
    rapidjson::Document _docRootjson;
};

#endif  // __CONFIG_PARSER_H__

