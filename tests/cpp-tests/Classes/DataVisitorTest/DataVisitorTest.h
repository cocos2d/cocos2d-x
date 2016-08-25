#ifndef __DATAVISITOR_TEST_H__
#define __DATAVISITOR_TEST_H__

#include "../BaseTest.h"

#include <string>

DEFINE_TEST_SUITE(DataVisitorTests);

class PrettyPrinterDemo : public TestCase
{
public:
    CREATE_FUNC(PrettyPrinterDemo);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void addSprite();
protected:
    std::string    _title;
};


#endif // __DATAVISITOR_TEST_H__
