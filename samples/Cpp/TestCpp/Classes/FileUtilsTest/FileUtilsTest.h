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
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    void backCallback(Object* sender);
    void nextCallback(Object* sender);
    void restartCallback(Object* sender);
};

class TestResolutionDirectories : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestResolutionDirectories);

    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();
private:
    std::vector<std::string> _defaultSearchPathArray;
    std::vector<std::string> _defaultResolutionsOrderArray;
};

class TestSearchPath : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestSearchPath);

    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();
private:
    std::vector<std::string> _defaultSearchPathArray;
    std::vector<std::string> _defaultResolutionsOrderArray;
};

class TestFilenameLookup : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestFilenameLookup);

    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();
};

class TestIsFileExist : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestIsFileExist);

    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();
};

class TextWritePlist : public FileUtilsDemo
{
public:
    CREATE_FUNC(TextWritePlist);

    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();
};

#endif /* __FILEUTILSTEST_H__ */
