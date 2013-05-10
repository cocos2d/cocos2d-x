#include "CocoaSerializationTest.h"
#include "../testResource.h"
#include "cocos2d.h"
#include "CocoaSingleTestRunner.h"

void CocoaSerializationTestScene::runThisTest()
{
    CCString *text = CCString::createWithFormat("Running 0 / %d.",
                                                (int)m_resources.size());
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    m_progress = CCLabelTTF::create(text->getCString(), "Arial", 22);
    m_progress->setPosition(ccp(0.5 * winSize.width, 0.66 * winSize.height));
    addChild(m_progress);

    schedule(schedule_selector(CocoaSerializationTestScene::runNextResource), 0.25);
    CCDirector::sharedDirector()->replaceScene(this);
}

CocoaSerializationTestScene::CocoaSerializationTestScene()
    : m_nextResource(0)
    , m_failures(0)
    , m_progress(0)
{
    m_resources.push_back("animations/animations-2.plist");
    m_resources.push_back("animations/animations.plist");
    m_resources.push_back("animations/grossini_family.plist");
}

void CocoaSerializationTestScene::runNextResource(float)
{
    if (m_nextResource >= m_resources.size()) {
        CCLabelTTF *status = 0;
        if (m_failures == 0) {
            status = CCLabelTTF::create("All passed!", "Arial", 22);
        } else {
            CCString *text = CCString::createWithFormat("Failures: %d / %d.",
                                                        m_failures,
                                                        (int)m_resources.size());
            status = CCLabelTTF::create(text->getCString(), "Arial", 22);
        }
        const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        status->setPosition(ccp(0.5 * winSize.width, 0.33 * winSize.height));
        addChild(status);
    } else {
        const std::string resource = m_resources[m_nextResource];
        ++m_nextResource;
        CCString *text = CCString::createWithFormat("Running %d / %d.",
                                                    (int)m_nextResource,
                                                    (int)m_resources.size());
        m_progress->setString(text->getCString());
        if (!runCocoaSerializationTestCase(resource))
            ++m_failures;
    }
}
