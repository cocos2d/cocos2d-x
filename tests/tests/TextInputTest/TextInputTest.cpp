#include "TextInputTest.h"

//////////////////////////////////////////////////////////////////////////
// local function
//////////////////////////////////////////////////////////////////////////

enum 
{
    kTextFieldTTFTest,
    kTextInputTestsCount,
}; 

static int testIdx = -1; 

CCLayer* createTextInputTest(int nIndex)
{
    switch(nIndex)
    {
    case kTextFieldTTFTest: return new TextFieldTTFTest();
    }

    return NULL;
}

CCLayer* restartTextInputTest()
{
    CCLayer* pContainerLayer = new TextInputTest;
    pContainerLayer->autorelease();

    CCLayer* pTestLayer = createTextInputTest(testIdx);
    pTestLayer->autorelease();

    pContainerLayer->addChild(pTestLayer);

    return pContainerLayer;
}

CCLayer* nextTextInputTest()
{
    testIdx++;
    testIdx = testIdx % kTextInputTestsCount;

    return restartTextInputTest();
}

CCLayer* backTextInputTest()
{
    testIdx--;
    int total = kTextInputTestsCount;
    if( testIdx < 0 )
        testIdx += total;	

    return restartTextInputTest();
}

CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}

//////////////////////////////////////////////////////////////////////////
// implement TextInputTest
//////////////////////////////////////////////////////////////////////////

void TextInputTest::restartCallback(CCObject* pSender)
{
    CCScene* s = new TextInputTestScene();
    s->addChild(restartTextInputTest()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void TextInputTest::nextCallback(CCObject* pSender)
{
    CCScene* s = new TextInputTestScene();
    s->addChild( nextTextInputTest() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void TextInputTest::backCallback(CCObject* pSender)
{
    CCScene* s = new TextInputTestScene();
    s->addChild( backTextInputTest() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void TextInputTest::onEnter()
{
    CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 32);
    addChild(label);
    label->setPosition(ccp(s.width/2, s.height-50));

    std::string subTitle = subtitle();
    if(! subTitle.empty())
    {
        CCLabelTTF* l = CCLabelTTF::labelWithString(subTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(ccp(s.width/2, s.height-80));
    }

    CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage("Images/b1.png", "Images/b2.png", this, menu_selector(TextInputTest::backCallback));
    CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage("Images/r1.png","Images/r2.png", this, menu_selector(TextInputTest::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage("Images/f1.png", "Images/f2.png", this, menu_selector(TextInputTest::nextCallback) );

    CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);
    menu->setPosition(CCPointZero);
    item1->setPosition(ccp( s.width/2 - 100,30));
    item2->setPosition(ccp( s.width/2, 30));
    item3->setPosition(ccp( s.width/2 + 100,30));

    addChild(menu, 1);
}

std::string TextInputTest::title()
{
    return "text input test";
}

std::string TextInputTest::subtitle()
{
    return "";
}

//////////////////////////////////////////////////////////////////////////
// implement KeyboardNotificationLayer
//////////////////////////////////////////////////////////////////////////

KeyboardNotificationLayer::KeyboardNotificationLayer()
: m_pTrackNode(0)
{
    setIsTouchEnabled(true);
}

void KeyboardNotificationLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, false);
}

void KeyboardNotificationLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    if (! m_pTrackNode)
    {
        return;
    }

    CCRect rectTracked = getRect(m_pTrackNode);
    if (! CCRect::CCRectIntersectsRect(rectTracked, info.end))
    {
        return;
    }

    float adjustVert = CCRect::CCRectGetMaxY(info.end) - CCRect::CCRectGetMinY(rectTracked);

    CCArray * children = getChildren();
    CCNode * node = 0;
    int count = children->count();
    CCPoint pos;
    for (int i = 0; i < count; ++i)
    {
        node = (CCNode*)children->objectAtIndex(i);
        pos = node->getPosition();
        pos.y += adjustVert;
        node->setPosition(pos);
    }
}

//////////////////////////////////////////////////////////////////////////
// implement TextFieldTTFTest
//////////////////////////////////////////////////////////////////////////

TextFieldTTFTest::TextFieldTTFTest()
: m_nSelected(-1)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    m_pTextField[0] = CCTextFieldTTF::textFieldWithPlaceHolder("<click here>", 
                                                               CCSizeMake(240, 28),
                                                               CCTextAlignmentCenter,
                                                               "Thonburi",
                                                               24);
    addChild(m_pTextField[0]);
    m_pTextField[0]->setPosition(ccp(s.width/2, s.height/2 + 16));

    m_pTextField[1] = CCTextFieldTTF::textFieldWithPlaceHolder("<click here>",
                                                               "Thonburi",
                                                               24);
    addChild(m_pTextField[1]);
    m_pTextField[1]->setPosition(ccp(s.width/2, s.height/2 - 16));
}

std::string TextFieldTTFTest::subtitle()
{
    return "CCTextFieldTTF test";
}

bool TextFieldTTFTest::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_beginPos = pTouch->locationInView(pTouch->view());	
    m_beginPos = CCDirector::sharedDirector()->convertToGL(m_beginPos);
    return true;
}

void TextFieldTTFTest::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint endPos = pTouch->locationInView(pTouch->view());	
    endPos = CCDirector::sharedDirector()->convertToGL(endPos);

    float delta = 5.0f;
    if (::abs(endPos.x - m_beginPos.x) > delta
        || ::abs(endPos.y - m_beginPos.y) > delta)
    {
        // not click
        m_beginPos.x = m_beginPos.y = -1;
        return;
    }

    int index = 0;
    for (; index < sizeof(m_pTextField) / sizeof(CCTextFieldTTF *); ++index)
    {
        if (CCRect::CCRectContainsPoint(getRect(m_pTextField[index]), convertTouchToNodeSpaceAR(pTouch)))
        {
            break;
        }
    }

    if (index < sizeof(m_pTextField) / sizeof(CCTextFieldTTF *))
    {
        m_nSelected = index;
        m_pTrackNode = m_pTextField[index];
        m_pTextField[index]->attachWithIME();
    }
    else if (m_nSelected >= 0)
    {
        m_pTextField[m_nSelected]->detachWithIME();
        m_nSelected = -1;
        m_pTrackNode = 0;
    }
}

//////////////////////////////////////////////////////////////////////////
// implement TextInputTestScene
//////////////////////////////////////////////////////////////////////////

void TextInputTestScene::runThisTest()
{
    CCLayer* pLayer = nextTextInputTest();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
