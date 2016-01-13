#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__

#include <string>
#include <vector>
#include "cocos2d.h"
#include "json/document.h"
#include "ProjectConfig/SimulatorConfig.h"
#include "ProjectConfig/ProjectConfig.h"
#include "SimulatorExport.h"

using namespace std;
USING_NS_CC;

#define CONFIG_FILE "config.json"

typedef vector<SimulatorScreenSize> ScreenSizeArray;
typedef vector<SimulatorDesignContentScaleFactor> DesignContentScaleFactorArray;
class CC_LIBSIM_DLL ConfigParser
{
public:
    static ConfigParser *getInstance(void);
    static void purge();

    void readConfig(const string &filepath = "");

    // predefined screen size
    int getScreenSizeCount(void);
    // predefined design resolution size
    int getDesignResolutionSizeCount(void);
    // predefined design content scale factor
    int getDesignContentScaleFactorCount(void);
    cocos2d::Size getInitViewSize();
    cocos2d::Size getInitDesignResolutionSize();
    ResolutionPolicy getInitDesignResolutionPolicy();
    float getInitDesignContentScaleFactor();
    string getInitViewName();
    string getEntryFile();
    rapidjson::Document& getConfigJsonRoot();
    const SimulatorScreenSize getScreenSize(int index);
    const SimulatorScreenSize getDesignResolutionSize(int index);
    const SimulatorDesignContentScaleFactor getDesignContentScaleFactor(int index);
    void setConsolePort(int port);
    void setUploadPort(int port);
    int getConsolePort();
    int getUploadPort();
    int getDebugPort();
    bool isLanscape();
    bool isWindowTop();
    
    void setEntryFile(const std::string &file);
    void setInitViewSize(const cocos2d::Size &size);
    void setInitDesignResolutionSize(const cocos2d::Size &size);
    void setInitDesignResolutionPolicy(ResolutionPolicy policy);
    void setInitDesignContentScaleFactor(float scaleFactor);
    void setBindAddress(const std::string &address);
    const std::string &getBindAddress();


private:
    ConfigParser(void);
    void setDebugPort(int port);
    static ConfigParser *s_sharedConfigParserInstance;
    ScreenSizeArray _screenSizeArray;
    ScreenSizeArray _designResolutionSizeArray;
    DesignContentScaleFactorArray _designContentScaleFactorArray;
    cocos2d::Size _initViewSize;
    cocos2d::Size _initDesignResolutionSize;
    ResolutionPolicy _initDesignResolutionPolicy;
    float _initDesignContentScaleFactor;
    string _viewName;
    string _entryfile;
    bool _isLandscape;
    bool _isWindowTop;
    int _consolePort;
    int _uploadPort;
    int _debugPort;
    string _bindAddress;
    
    rapidjson::Document _docRootjson;
};

#endif  // __CONFIG_PARSER_H__

