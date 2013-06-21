//
//  CCEditBoxTest.cpp
//  TestCpp
//
//  Created by James on 8/14/12.
//
//

#include "EditBoxTest.h"
#include "../ExtensionsTest.h"

USING_NS_CC;
USING_NS_CC_EXT;


EditBoxTest::EditBoxTest()
{
    CCPoint visibleOrigin = CCEGLView::sharedOpenGLView()->getVisibleOrigin();
    CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
    
    CCSprite* pBg = CCSprite::create("Images/HelloWorld.png");
    pBg->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
    addChild(pBg);
    
    m_pTTFShowEditReturn = CCLabelTTF::create("No edit control return!", "", 30);
    m_pTTFShowEditReturn->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y + visibleSize.height - 50));
    addChild(m_pTTFShowEditReturn);
    
    // Back Menu
    CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(EditBoxTest::toExtensionsMainLayer));
    itemBack->setPosition(ccp(visibleOrigin.x+visibleSize.width - 50, visibleOrigin.y+25));
    CCMenu *menuBack = CCMenu::create(itemBack, NULL);
    menuBack->setPosition(CCPointZero);
    addChild(menuBack);
    
    CCSize editBoxSize = CCSizeMake(visibleSize.width - 100, 60);

    // top
    m_pEditName = CCEditBox::create(editBoxSize, CCScale9Sprite::create("extensions/green_edit.png"));
    m_pEditName->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height*3/4));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pEditName->setFontName("Paint Boy");
#else
	m_pEditName->setFontName("fonts/Paint Boy.ttf");
#endif
    m_pEditName->setFontSize(25);
    m_pEditName->setFontColor(ccRED);
    m_pEditName->setPlaceHolder("Name:");
    m_pEditName->setPlaceholderFontColor(ccWHITE);
    m_pEditName->setMaxLength(8);
    m_pEditName->setReturnType(kKeyboardReturnTypeDone);
    m_pEditName->setDelegate(this);
    addChild(m_pEditName);
    
    // middle
    m_pEditPassword = CCEditBox::create(editBoxSize, CCScale9Sprite::create("extensions/orange_edit.png"));
    m_pEditPassword->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	m_pEditPassword->setFont("American Typewriter", 30);
#else
	m_pEditPassword->setFont("fonts/American Typewriter.ttf", 30);
#endif
    m_pEditPassword->setFontColor(ccGREEN);
    m_pEditPassword->setPlaceHolder("Password:");
    m_pEditPassword->setMaxLength(6);
    m_pEditPassword->setInputFlag(kEditBoxInputFlagPassword);
    m_pEditPassword->setInputMode(kEditBoxInputModeSingleLine);
    m_pEditPassword->setDelegate(this);
    addChild(m_pEditPassword);
    
    // bottom
    m_pEditEmail = CCEditBox::create(CCSizeMake(editBoxSize.width, editBoxSize.height), CCScale9Sprite::create("extensions/yellow_edit.png"));
    m_pEditEmail->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/4));
    m_pEditEmail->setAnchorPoint(ccp(0.5, 1.0f));
    m_pEditEmail->setPlaceHolder("Email:");
    m_pEditEmail->setInputMode(kEditBoxInputModeEmailAddr);
    m_pEditEmail->setDelegate(this);
    addChild(m_pEditEmail);
    
    this->setPosition(ccp(10, 20));
}

EditBoxTest::~EditBoxTest()
{
    
}

void EditBoxTest::toExtensionsMainLayer(cocos2d::CCObject *sender)
{
    ExtensionsTestScene *pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}

void EditBoxTest::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p DidBegin !", editBox);
}

void EditBoxTest::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p DidEnd !", editBox);
}

void EditBoxTest::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void EditBoxTest::editBoxReturn(CCEditBox* editBox)
{
    CCLog("editBox %p was returned !",editBox);
    
    if (m_pEditName == editBox)
    {
        m_pTTFShowEditReturn->setString("Name EditBox return !");
    }
    else if (m_pEditPassword == editBox)
    {
        m_pTTFShowEditReturn->setString("Password EditBox return !"); 
    }
    else if (m_pEditEmail == editBox)
    {
        m_pTTFShowEditReturn->setString("Email EditBox return !");
    }
}

void runEditBoxTest()
{
    CCScene *pScene = CCScene::create();
    EditBoxTest *pLayer = new EditBoxTest();
    pScene->addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(pScene);
    pLayer->release();
}
