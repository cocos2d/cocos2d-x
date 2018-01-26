#ifndef __CONFIGURATIONTEST_H__
#define __CONFIGURATIONTEST_H__

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ConfigurationTests);

class ConfigurationBase : public TestCase
{
protected:

public:
    virtual std::string title() const override;
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
