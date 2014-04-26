//
//  EditBoxTest.cpp
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
    auto glview = Director::getInstance()->getOpenGLView();
    auto visibleOrigin = glview->getVisibleOrigin();
    auto visibleSize = glview->getVisibleSize();
    
    auto pBg = Sprite::create("Images/HelloWorld.png");
    pBg->setPosition(Vector2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
    addChild(pBg);
    
    _TTFShowEditReturn = Label::createWithSystemFont("No edit control return!", "", 30);
    _TTFShowEditReturn->setPosition(Vector2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y + visibleSize.height - 50));
    addChild(_TTFShowEditReturn);
    
    // Back Menu
    auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(EditBoxTest::toExtensionsMainLayer, this));
    itemBack->setPosition(Vector2(visibleOrigin.x+visibleSize.width - 50, visibleOrigin.y+25));
    auto menuBack = Menu::create(itemBack, NULL);
    menuBack->setPosition(Vector2::ZERO);
    addChild(menuBack);
    
    auto editBoxSize = Size(visibleSize.width - 100, 60);

    // top
    _editName = EditBox::create(editBoxSize, Scale9Sprite::create("extensions/green_edit.png"));
    _editName->setPosition(Vector2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height*3/4));
    _editName->setFontName("Paint Boy");
    _editName->setFontSize(25);
    _editName->setFontColor(Color3B::RED);
    _editName->setPlaceHolder("Name:");
    _editName->setPlaceholderFontColor(Color3B::WHITE);
    _editName->setMaxLength(8);
    _editName->setReturnType(EditBox::KeyboardReturnType::DONE);
    _editName->setDelegate(this);
    addChild(_editName);
    
    // middle
    _editPassword = EditBox::create(editBoxSize, Scale9Sprite::create("extensions/orange_edit.png"));
    _editPassword->setPosition(Vector2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	_editPassword->setFont("American Typewriter", 30);
#else
    _editPassword->setFont("American Typewriter", 80);
    _editPassword->setPlaceholderFont("American Typewriter", 80);
#endif
    _editPassword->setFontColor(Color3B::GREEN);
    _editPassword->setPlaceHolder("Password:");
    _editPassword->setMaxLength(6);
    _editPassword->setInputFlag(EditBox::InputFlag::PASSWORD);
    _editPassword->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _editPassword->setDelegate(this);
    addChild(_editPassword);
    
    // bottom
    _editEmail = EditBox::create(Size(editBoxSize.width, editBoxSize.height), Scale9Sprite::create("extensions/yellow_edit.png"));
    _editEmail->setPosition(Vector2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/4));
    _editEmail->setAnchorPoint(Vector2(0.5, 1.0f));
    _editEmail->setPlaceHolder("Email:");
    _editEmail->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
    _editEmail->setDelegate(this);
    addChild(_editEmail);
    
    this->setPosition(Vector2(10, 20));
}

EditBoxTest::~EditBoxTest()
{
    
}

void EditBoxTest::toExtensionsMainLayer(cocos2d::Ref *sender)
{
    auto scene = new ExtensionsTestScene();
    scene->runThisTest();
    scene->release();
}

void EditBoxTest::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
    log("editBox %p DidBegin !", editBox);
}

void EditBoxTest::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
    log("editBox %p DidEnd !", editBox);
}

void EditBoxTest::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
    log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void EditBoxTest::editBoxReturn(EditBox* editBox)
{
    log("editBox %p was returned !",editBox);
    
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
    auto scene = Scene::create();
    EditBoxTest *layer = new EditBoxTest();
    scene->addChild(layer);
    
    Director::getInstance()->replaceScene(scene);
    layer->release();
}
