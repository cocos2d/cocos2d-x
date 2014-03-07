#ifndef __DATAVISITOR_TEST_H__
#define __DATAVISITOR_TEST_H__

#include "../testBasic.h"

#include <string>

class PrettyPrinterDemo : public Layer
{
public:
    virtual std::string title() const;
    virtual std::string subtitle() const;
    virtual void onEnter() override;
    void addSprite();
protected:
    std::string    _title;
};

class DataVisitorTestScene : public TestScene
{
public:
    virtual void runThisTest();

    CREATE_FUNC(DataVisitorTestScene);
};

#endif // __DATAVISITOR_TEST_H__
