#ifndef __TestCpp__CustomImageScene__
#define __TestCpp__CustomImageScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "BaseTest.h"

class CustomImageLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(CustomImageLayer);

    virtual bool init() override;
};

class CustomImageScene : public TestCase
{
public:
    CREATE_FUNC(CustomImageScene);

    virtual bool init() override;
    virtual std::string title() const override { return getTestCaseName(); }
};

#endif /* defined(__TestCpp__CustomUIScene__) */
