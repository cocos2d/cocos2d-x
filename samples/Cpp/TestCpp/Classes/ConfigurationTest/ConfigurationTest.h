#ifndef __CONFIGURATIONTEST_H__
#define __CONFIGURATIONTEST_H__

#include "../testBasic.h"

USING_NS_CC;


// the class inherit from TestScene
// every Scene each test used must inherit from TestScene,
// make sure the test have the menu item for back to main menu
class ConfigurationTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class ConfigurationBase : public CCLayer
{
protected:

public:
    virtual void onEnter();
    virtual void onExit();

    virtual std::string title();
    virtual std::string subtitle();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
};

class ConfigurationLoadConfig : public ConfigurationBase
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ConfigurationQuery : public ConfigurationBase
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ConfigurationInvalid : public ConfigurationBase
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ConfigurationDefault : public ConfigurationBase
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};


#endif // __CONFIGURATIONTEST_H__
