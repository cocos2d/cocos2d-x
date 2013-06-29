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
    
    _TTFShowEditReturn = CCLabelTTF::create("No edit control return!", "", 30);
    _TTFShowEditReturn->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y + visibleSize.height - 50));
    addChild(_TTFShowEditReturn);
    
    // Back Menu
    CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", CC_CALLBACK_1(EditBoxTest::toExtensionsMainLayer, this));
    itemBack->setPosition(ccp(visibleOrigin.x+visibleSize.width - 50, visibleOrigin.y+25));
    CCMenu *menuBack = CCMenu::create(itemBack, NULL);
    menuBack->setPosition(CCPointZero);
    addChild(menuBack);
    
    CCSize editBoxSize = CCSizeMake(visibleSize.width - 100, 60);

    // top
    _editName = CCEditBox::create(editBoxSize, CCScale9Sprite::create("extensions/green_edit.png"));
    _editName->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height*3/4));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    _editName->setFontName("Paint Boy");
#else
	_editName->setFontName("fonts/Paint Boy.ttf");
#endif
    _editName->setFontSize(25);
    _editName->setFontColor(ccRED);
    _editName->setPlaceHolder("Name:");
    _editName->setPlaceholderFontColor(ccWHITE);
    _editName->setMaxLength(8);
    _editName->setReturnType(kKeyboardReturnTypeDone);
    _editName->setDelegate(this);
    addChild(_editName);
    
    // middle
    _editPassword = CCEditBox::create(editBoxSize, CCScale9Sprite::create("extensions/orange_edit.png"));
    _editPassword->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	_editPassword->setFont("American Typewriter", 30);
#else
	_editPassword->setFont("fonts/American Typewriter.ttf", 30);
#endif
    _editPassword->setFontColor(ccGREEN);
    _editPassword->setPlaceHolder("Password:");
    _editPassword->setMaxLength(6);
    _editPassword->setInputFlag(kEditBoxInputFlagPassword);
    _editPassword->setInputMode(kEditBoxInputModeSingleLine);
    _editPassword->setDelegate(this);
    addChild(_editPassword);
    
    // bottom
    _editEmail = CCEditBox::create(CCSizeMake(editBoxSize.width, editBoxSize.height), CCScale9Sprite::create("extensions/yellow_edit.png"));
    _editEmail->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/4));
    _editEmail->setAnchorPoint(ccp(0.5, 1.0f));
    _editEmail->setPlaceHolder("Email:");
    _editEmail->setInputMode(kEditBoxInputModeEmailAddr);
    _editEmail->setDelegate(this);
    addChild(_editEmail);
    
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
    
    if (_editName == editBox)
    {
        _TTFShowEditReturn->setString("Name EditBox return !");
    }
    else if (_editPassword == editBox)
    {
        _TTFShowEditReturn->setString("Password EditBox return !"); 
    }
    else if (_editEmail == editBox)
    {
        _TTFShowEditReturn->setString("Email EditBox return !");
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
