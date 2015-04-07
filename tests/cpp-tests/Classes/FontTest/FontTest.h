#ifndef _FONT_TEST_H_
#define _FONT_TEST_H_

#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(FontTests);

class FontTest : public TestCase
{
public:
    static FontTest* create(const std::string& fontFile)
    {
        auto ret = new (std::nothrow) FontTest;
        if (ret && ret->init())
        {
            ret->showFont(fontFile);
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }

        return ret;
    }

    void showFont(const std::string& fontFile);

    virtual std::string title() const override;
};

#endif // _FONT_TEST_H_
