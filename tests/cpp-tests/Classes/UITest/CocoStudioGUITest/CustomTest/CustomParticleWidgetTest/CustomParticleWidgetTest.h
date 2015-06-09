#ifndef __CustomUI__CustomParticleWidgetTest__
#define __CustomUI__CustomParticleWidgetTest__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "BaseTest.h"

class CustomParticleWidgetLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(CustomParticleWidgetLayer);

    virtual bool init() override;
};

class CustomParticleWidgetScene : public TestCase
{
public:
    CREATE_FUNC(CustomParticleWidgetScene);

    virtual bool init() override;
    virtual std::string title() const override { return getTestCaseName(); }
};

#endif /* defined(__CustomUI__CustomParticleWidgetTest__) */
