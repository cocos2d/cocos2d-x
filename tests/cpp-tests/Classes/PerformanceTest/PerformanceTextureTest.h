#ifndef __PERFORMANCE_TEXTURE_TEST_H__
#define __PERFORMANCE_TEXTURE_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceTextureTests);

class TexturePerformceTest : public TestCase
{
public:
    CREATE_FUNC(TexturePerformceTest);

    virtual void performTests();
    void performTestsPNG(const char* filename);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};

#endif
