#ifndef __FILEUTILSTEST_H__
#define __FILEUTILSTEST_H__

#include "../testBasic.h"
#include "../BaseTest.h"

USING_NS_CC;

class FileUtilsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class FileUtilsDemo : public BaseTest
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void backCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void restartCallback(Ref* sender);
};

class TestResolutionDirectories : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestResolutionDirectories);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    std::vector<std::string> _defaultSearchPathArray;
    std::vector<std::string> _defaultResolutionsOrderArray;
};

class TestSearchPath : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestSearchPath);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    std::vector<std::string> _defaultSearchPathArray;
    std::vector<std::string> _defaultResolutionsOrderArray;
};

class TestFilenameLookup : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestFilenameLookup);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
};

class TestIsFileExist : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestIsFileExist);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TextWritePlist : public FileUtilsDemo
{
public:
    CREATE_FUNC(TextWritePlist);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif /* __FILEUTILSTEST_H__ */
