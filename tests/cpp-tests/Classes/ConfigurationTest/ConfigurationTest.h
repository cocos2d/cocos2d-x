#ifndef __CONFIGURATIONTEST_H__
#define __CONFIGURATIONTEST_H__

#include "../testBasic.h"
#include "../BaseTest.h"

USING_NS_CC;


// the class inherit from TestScene
// every Scene each test used must inherit from TestScene,
// make sure the test have the menu item for back to main menu
class ConfigurationTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class ConfigurationBase : public BaseTest
{
protected:

public:
    virtual void onEnter() override;
    virtual void onExit() override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
};

class ConfigurationLoadConfig : public ConfigurationBase
{
public:
    CREATE_FUNC(ConfigurationLoadConfig);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ConfigurationQuery : public ConfigurationBase
{
public:
    CREATE_FUNC(ConfigurationQuery);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ConfigurationInvalid : public ConfigurationBase
{
public:
    CREATE_FUNC(ConfigurationInvalid);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ConfigurationDefault : public ConfigurationBase
{
public:
    CREATE_FUNC(ConfigurationDefault);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ConfigurationSet : public ConfigurationBase
{
public:
    CREATE_FUNC(ConfigurationSet);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};


#endif // __CONFIGURATIONTEST_H__
