#ifndef __PERFORMANCE_TEXTURE_TEST_H__
#define __PERFORMANCE_TEXTURE_TEST_H__

#include "PerformanceTest.h"

class TextureMenuLayer : public PerformBasicLayer
{
public:
    TextureMenuLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        :PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void showCurrentTest();

    virtual void onEnter();
    virtual std::string title() const;
    virtual std::string subtitle() const;
    virtual void performTests() = 0;
};

class TextureTest : public TextureMenuLayer
{
public:
    TextureTest(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        :TextureMenuLayer(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void performTests();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void performTestsPNG(const char* filename);

    static Scene* scene();
};

void runTextureTest();

#endif
