// #define COCOS2D_DEBUG   1

#include "TextInputTest.h"

//////////////////////////////////////////////////////////////////////////
// local function
//////////////////////////////////////////////////////////////////////////

enum 
{
    kTextFieldTTFDefaultTest = 0,
    kTextFieldTTFActionTest,
    kTextInputTestsCount,
}; 

#define FONT_NAME                       "Thonburi"
#define FONT_SIZE                       36

static int testIdx = -1; 

KeyboardNotificationLayer* createTextInputTest(int nIndex)
{
    switch(nIndex)
    {
    case kTextFieldTTFDefaultTest: return new TextFieldTTFDefaultTest();
    case kTextFieldTTFActionTest: return new TextFieldTTFActionTest();
    default: return 0;
    }
}

CCLayer* restartTextInputTest()
{
    TextInputTest* pContainerLayer = new TextInputTest;
    pContainerLayer->autorelease();

    KeyboardNotificationLayer* pTestLayer = createTextInputTest(testIdx);
    pTestLayer->autorelease();
    pContainerLayer->addKeyboardNotificationLayer(pTestLayer);

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

static CCRect getRect(CCNode * pNode)
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

TextInputTest::TextInputTest()
: _notificationLayer(0)
{
    
}

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

void TextInputTest::addKeyboardNotificationLayer(KeyboardNotificationLayer * pLayer)
{
    _notificationLayer = pLayer;
    addChild(pLayer);
}

std::string TextInputTest::title()
{
    return "text input test";
}

void TextInputTest::onEnter()
{
    BaseTest::onEnter();
}

//////////////////////////////////////////////////////////////////////////
// implement KeyboardNotificationLayer
//////////////////////////////////////////////////////////////////////////

KeyboardNotificationLayer::KeyboardNotificationLayer()
: _trackNode(0)
{
    setTouchEnabled(true);
}

void KeyboardNotificationLayer::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void KeyboardNotificationLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    CCLOG("TextInputTest:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
        info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);

    if (! _trackNode)
    {
        return;
    }

    CCRect rectTracked = getRect(_trackNode);
    CCLOG("TextInputTest:trackingNodeAt(origin:%f,%f, size:%f,%f)",
        rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);

    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! rectTracked.intersectsRect(info.end))
    {
        return;
    }

    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    float adjustVert = info.end.getMaxY() - rectTracked.getMinY();
    CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);

    // move all the children node of KeyboardNotificationLayer
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

// CCLayer function

bool KeyboardNotificationLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("++++++++++++++++++++++++++++++++++++++++++++");
    _beginPos = pTouch->getLocation();    
    return true;
}

void KeyboardNotificationLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (! _trackNode)
    {
        return;
    }
    
    CCPoint endPos = pTouch->getLocation();    

    float delta = 5.0f;
    if (::abs(endPos.x - _beginPos.x) > delta
        || ::abs(endPos.y - _beginPos.y) > delta)
    {
        // not click
        _beginPos.x = _beginPos.y = -1;
        return;
    }

    // decide the trackNode is clicked.
    CCRect rect;
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);

    rect = getRect(_trackNode);
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
        rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

    this->onClickTrackNode(rect.containsPoint(point));
    CCLOG("----------------------------------");
}

//////////////////////////////////////////////////////////////////////////
// implement TextFieldTTFDefaultTest
//////////////////////////////////////////////////////////////////////////

std::string TextFieldTTFDefaultTest::subtitle()
{
    return "TextFieldTTF with default behavior test";
}

void TextFieldTTFDefaultTest::onClickTrackNode(bool bClicked)
{
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)_trackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        CCLOG("TextFieldTTFDefaultTest:CCTextFieldTTF attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // TextFieldTTFTest not be clicked
        CCLOG("TextFieldTTFDefaultTest:CCTextFieldTTF detachWithIME");
        pTextField->detachWithIME();
    }
}

void TextFieldTTFDefaultTest::onEnter()
{
    KeyboardNotificationLayer::onEnter();

    // add CCTextFieldTTF
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCTextFieldTTF * pTextField = CCTextFieldTTF::textFieldWithPlaceHolder("<click here for input>",
        FONT_NAME,
        FONT_SIZE);
    addChild(pTextField);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)    
    // on android, CCTextFieldTTF cannot auto adjust its position when soft-keyboard pop up
    // so we had to set a higher position to make it visable
    pTextField->setPosition(ccp(s.width / 2, s.height/2 + 50));
#else
    pTextField->setPosition(ccp(s.width / 2, s.height / 2));
#endif

    _trackNode = pTextField;
}

//////////////////////////////////////////////////////////////////////////
// implement TextFieldTTFActionTest
//////////////////////////////////////////////////////////////////////////

std::string TextFieldTTFActionTest::subtitle()
{
    return "CCTextFieldTTF with action and char limit test";
}

void TextFieldTTFActionTest::onClickTrackNode(bool bClicked)
{
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)_trackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        CCLOG("TextFieldTTFActionTest:CCTextFieldTTF attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // TextFieldTTFTest not be clicked
        CCLOG("TextFieldTTFActionTest:CCTextFieldTTF detachWithIME");
        pTextField->detachWithIME();
    }
}

void TextFieldTTFActionTest::onEnter()
{
    KeyboardNotificationLayer::onEnter();

    _charLimit = 12;

    _textFieldAction = CCRepeatForever::create(
        CCSequence::create(
            CCFadeOut::create(0.25),
            CCFadeIn::create(0.25),
            0
        ));
    _textFieldAction->retain();
    _action = false;

    // add CCTextFieldTTF
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    _textField = CCTextFieldTTF::textFieldWithPlaceHolder("<click here for input>",
        FONT_NAME,
        FONT_SIZE);
    addChild(_textField);

    _textField->setDelegate(this);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)    
    // on android, CCTextFieldTTF cannot auto adjust its position when soft-keyboard pop up
    // so we had to set a higher position
    _textField->setPosition(ccp(s.width / 2, s.height/2 + 50));
#else
    _textField->setPosition(ccp(s.width / 2, s.height / 2));
#endif

    _trackNode = _textField;
}

void TextFieldTTFActionTest::onExit()
{
    KeyboardNotificationLayer::onExit();
    _textFieldAction->release();
}

// CCTextFieldDelegate protocol
bool TextFieldTTFActionTest::onTextFieldAttachWithIME(CCTextFieldTTF * pSender)
{
    if (! _action)
    {
        _textField->runAction(_textFieldAction);
        _action = true;
    }
    return false;
}

bool TextFieldTTFActionTest::onTextFieldDetachWithIME(CCTextFieldTTF * pSender)
{
    if (_action)
    {
        _textField->stopAction(_textFieldAction);
        _textField->setOpacity(255);
        _action = false;
    }
    return false;
}

bool TextFieldTTFActionTest::onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen)
{
    // if insert enter, treat as default to detach with ime
    if ('\n' == *text)
    {
        return false;
    }
    
    // if the textfield's char count more than _charLimit, doesn't insert text anymore.
    if (pSender->getCharCount() >= _charLimit)
    {
        return true;
    }

    // create a insert text sprite and do some action
    CCLabelTTF * label = CCLabelTTF::create(text, FONT_NAME, FONT_SIZE);
    this->addChild(label);
    ccColor3B color = { 226, 121, 7};
    label->setColor(color);

    // move the sprite from top to position
    CCPoint endPos = pSender->getPosition();
    if (pSender->getCharCount())
    {
        endPos.x += pSender->getContentSize().width / 2;
    }
    CCSize  inputTextSize = label->getContentSize();
    CCPoint beginPos(endPos.x, CCDirector::sharedDirector()->getWinSize().height - inputTextSize.height * 2); 

    float duration = 0.5;
    label->setPosition(beginPos);
    label->setScale(8);

    CCAction * seq = CCSequence::create(
        CCSpawn::create(
            CCMoveTo::create(duration, endPos),
            CCScaleTo::create(duration, 1),
            CCFadeOut::create(duration),
        0),
        CCCallFuncN::create(this, callfuncN_selector(TextFieldTTFActionTest::callbackRemoveNodeWhenDidAction)),
        0);
    label->runAction(seq);
    return false;
}

bool TextFieldTTFActionTest::onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen)
{
    // create a delete text sprite and do some action
    CCLabelTTF * label = CCLabelTTF::create(delText, FONT_NAME, FONT_SIZE);
    this->addChild(label);

    // move the sprite to fly out
    CCPoint beginPos = pSender->getPosition();
    CCSize textfieldSize = pSender->getContentSize();
    CCSize labelSize = label->getContentSize();
    beginPos.x += (textfieldSize.width - labelSize.width) / 2.0f;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint endPos(- winSize.width / 4.0f, winSize.height * (0.5 + (float)rand() / (2.0f * RAND_MAX)));

    float duration = 1;
    float rotateDuration = 0.2f;
    int repeatTime = 5; 
    label->setPosition(beginPos);

    CCAction * seq = CCSequence::create(
        CCSpawn::create(
            CCMoveTo::create(duration, endPos),
            CCRepeat::create(
                CCRotateBy::create(rotateDuration, (rand()%2) ? 360 : -360),
                repeatTime),
            CCFadeOut::create(duration),
        0),
        CCCallFuncN::create(this, callfuncN_selector(TextFieldTTFActionTest::callbackRemoveNodeWhenDidAction)),
        0);
    label->runAction(seq);
    return false;
}

bool TextFieldTTFActionTest::onDraw(CCTextFieldTTF * pSender)
{
    return false;
}

void TextFieldTTFActionTest::callbackRemoveNodeWhenDidAction(CCNode * pNode)
{
    this->removeChild(pNode, true);
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
