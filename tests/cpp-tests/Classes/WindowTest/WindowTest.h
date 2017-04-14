#ifndef __WINDOWTEST_H__
#define __WINDOWTEST_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#include "../BaseTest.h"

DEFINE_TEST_SUITE(WindowTests);

class WindowTest : public TestCase
{
public:
    virtual std::string title() const override;
};

class WindowTestWindowed1 : public WindowTest
{
public:
    CREATE_FUNC(WindowTestWindowed1);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class WindowTestWindowed2 : public WindowTest
{
public:
    CREATE_FUNC(WindowTestWindowed2);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class WindowTestFullscreen1 : public WindowTest
{
public:
    CREATE_FUNC(WindowTestFullscreen1);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class WindowTestFullscreen2 : public WindowTest
{
public:
    CREATE_FUNC(WindowTestFullscreen2);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

#endif /* __WINDOWTEST_H__ */

#endif
