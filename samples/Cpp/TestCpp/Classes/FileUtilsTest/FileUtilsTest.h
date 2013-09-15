#ifndef __FILEUTILSTEST_H__
#define __FILEUTILSTEST_H__

#include "../testBasic.h"
#include "../BaseTest.h"

USING_NS_CC;
using namespace std;

class FileUtilsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class FileUtilsDemo : public BaseTest
{
public:
    virtual void onEnter();
    virtual string title();
    virtual string subtitle();
    void backCallback(Object* sender);
    void nextCallback(Object* sender);
    void restartCallback(Object* sender);
};

class TestResolutionDirectories : public FileUtilsDemo
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual string title();
    virtual string subtitle();
private:
    vector<string> _defaultSearchPathArray;
    vector<string> _defaultResolutionsOrderArray;
};

class TestSearchPath : public FileUtilsDemo
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual string title();
    virtual string subtitle();
private:
    vector<string> _defaultSearchPathArray;
    vector<string> _defaultResolutionsOrderArray;
};

class TestFilenameLookup : public FileUtilsDemo
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual string title();
    virtual string subtitle();
};

class TestIsFileExist : public FileUtilsDemo
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual string title();
    virtual string subtitle();
};

class TextWritePlist : public FileUtilsDemo
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual string title();
    virtual string subtitle();
};

#endif /* __FILEUTILSTEST_H__ */
