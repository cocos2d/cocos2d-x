#ifndef __DATAVISITOR_TEST_H__
#define __DATAVISITOR_TEST_H__

#include "../testBasic.h"

#include <string>

class PrettyPrinterDemo : public CCLayer
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();
    void addSprite();
protected:
    std::string    m_strTitle;
};

class DataVisitorTestScene : public TestScene
{
public:
    virtual void runThisTest();

    CREATE_FUNC(DataVisitorTestScene);
};

#endif // __DATAVISITOR_TEST_H__
