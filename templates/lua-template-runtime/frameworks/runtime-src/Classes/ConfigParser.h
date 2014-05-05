#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__

#include <string>
#include <vector>
#include "cocos2d.h"
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
    void readConfig();

    // predefined screen size
    int getScreenSizeCount(void);
    cocos2d::Size getInitViewSize();
    string getInitViewName();
    const SimulatorScreenSize getScreenSize(int index);

private:
    ConfigParser(void);
    static ConfigParser *s_sharedInstance;
    ScreenSizeArray _screenSizeArray;
    cocos2d::Size _initViewSize;
    string _viewName;
};

#endif  // __CONFIG_PARSER_H__

