/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "UIEditBoxTest.h"
#include "testResource.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

UIEditBoxTests::UIEditBoxTests()
{
    ADD_TEST_CASE(UIEditBoxTest);
    ADD_TEST_CASE(UIEditBoxTestToggleVisibility);
    ADD_TEST_CASE(UIEditBoxTestTextHorizontalAlignment);
    ADD_TEST_CASE(UIEditBoxTestPressedAndDisabled);
}

// UIEditBoxTest

bool UIEditBoxTest::init()
{
    if (UIScene::init())
    {
        auto glview = Director::getInstance()->getOpenGLView();
        auto visibleOrigin = glview->getVisibleOrigin();
        auto visibleSize = glview->getVisibleSize();
        
        auto pBg = Sprite::create("Images/HelloWorld.png");
        pBg->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
        addChild(pBg);
        
        _TTFShowEditReturn = Label::createWithSystemFont("No edit control return!", "Arial", 30);
        _TTFShowEditReturn->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y + visibleSize.height - 50));
        addChild(_TTFShowEditReturn);
        
        
        auto editBoxSize = Size(visibleSize.width - 100, visibleSize.height * 0.1);
        
        // top
        std::string pNormalSprite = "extensions/green_edit.png";
        _editName = ui::EditBox::create(editBoxSize + Size(0,40), ui::Scale9Sprite::create(pNormalSprite));
        _editName->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2-50, visibleOrigin.y+visibleSize.height*3/4));
        _editName->setFontColor(Color3B::RED);
        _editName->setPlaceHolder("Name:");
        _editName->setPlaceholderFontColor(Color3B::WHITE);
        _editName->setMaxLength(8);
        _editName->setFontSize((int)editBoxSize.height/2);
        _editName->setText("v👐👊💝");
        _editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
        _editName->setDelegate(this);
        _editName->setVisible(true);
        addChild(_editName);
       
        Button* button = Button::create("cocosui/animationbuttonnormal.png",
                                        "cocosui/animationbuttonpressed.png");
        auto buttonSize = button->getContentSize();
        button->setTitleText("Single Line");
        button->setPosition(_editName->getPosition() + Vec2(editBoxSize.width/2 + buttonSize.width/2, 0.0f));
        button->addClickEventListener([=](Ref* ref){
            _editName->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
        });
        addChild(button);

        // middle
        _editPassword = ui::EditBox::create(Size(editBoxSize.width,
                                                 editBoxSize.height + 20), "extensions/orange_edit.png");
        _editPassword->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2-50, visibleOrigin.y+visibleSize.height/2));
        _editPassword->setFontColor(Color3B::GREEN);
        _editPassword->setPlaceHolder("Password:");
        _editPassword->setMaxLength(6);
        _editPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
        _editPassword->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
        _editPassword->setFontSize((int)editBoxSize.height/2);
        _editPassword->setDelegate(this);
        _editPassword->setVisible(true);
        addChild(_editPassword);
       
        auto buttonPassword = (ui::Button*)button->clone();
        buttonPassword->setTitleText("Multiline");
        buttonPassword->setPosition(_editPassword->getPosition() + Vec2(editBoxSize.width/2 + buttonSize.width/2, 0.0f));
        buttonPassword->addClickEventListener([=](Ref* ref){
            _editPassword->setInputMode(ui::EditBox::InputMode::ANY);
        });
        addChild(buttonPassword);
        
        // bottom
        // Add an intermediate Node to test scaling and content size relative to world
        _editEmailParent = Node::create();
//        _editEmailParent->setScale(0.5);
        _editEmailParent->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2-50, visibleOrigin.y+visibleSize.height/4));
        addChild(_editEmailParent);
                    
        auto bottomButtonSize = Size(editBoxSize.width, editBoxSize.height + 10);
        _editEmail = ui::EditBox::create(bottomButtonSize, "extensions/yellow_edit.png");
        _editEmail->setPlaceHolder("Email:");
        _editEmail->setInputMode(ui::EditBox::InputMode::EMAIL_ADDRESS);
        _editEmail->setDelegate(this);
        _editEmail->setVisible(true);
        _editEmailParent->addChild(_editEmail);
        //It is required to use setFontSize and setContentSize after adding it to the hierarchy, so that native EditBox get the right size
        _editEmail->setFontSize(30);
        _editEmail->setContentSize(bottomButtonSize);
        
        auto buttonEmail = (ui::Button*)button->clone();
        buttonEmail->setTitleText("Multiline");
        buttonEmail->setPosition(_editEmailParent->getPosition() + Vec2(editBoxSize.width/2 + buttonSize.width/2, 0.0f));
        buttonEmail->addClickEventListener([=](Ref* ref){
            _editEmail->setInputMode(ui::EditBox::InputMode::ANY);
        });
        addChild(buttonEmail);
        
        return true;
    }
    return false;
}

void UIEditBoxTest::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
    log("editBox %p DidBegin !", editBox);
}

void UIEditBoxTest::editBoxEditingDidEndWithAction(cocos2d::ui::EditBox* editBox, cocos2d::ui::EditBoxDelegate::EditBoxEndAction action)
{
    log("editBox %p DidEnd with action %d!", editBox, action);
}

void UIEditBoxTest::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
    log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
    editBox->setText(text.c_str());
}

void UIEditBoxTest::editBoxReturn(ui::EditBox* editBox)
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

// UIEditBoxTestToggleVisibility

bool UIEditBoxTestToggleVisibility::init()
{
    if (UIScene::init())
    {
        auto glview = Director::getInstance()->getOpenGLView();
        auto visibleOrigin = glview->getVisibleOrigin();
        auto visibleSize = glview->getVisibleSize();
        
        auto pBg = Sprite::create("Images/HelloWorld.png");
        pBg->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
        addChild(pBg);
        
        _TTFShowEditReturn = Label::createWithSystemFont("No edit control return!", "Arial", 30);
        _TTFShowEditReturn->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y + visibleSize.height - 50));
        addChild(_TTFShowEditReturn);
        
        
        auto editBoxSize = Size(visibleSize.width - 100, visibleSize.height * 0.1f);
        
        // top
        std::string pNormalSprite = "extensions/green_edit.png";
        _editName = ui::EditBox::create(editBoxSize + Size(0,40), ui::Scale9Sprite::create(pNormalSprite));
        _editName->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2-50, visibleOrigin.y+visibleSize.height*3/4));
        _editName->setFontColor(Color3B::RED);
        _editName->setPlaceHolder("Name:");
        _editName->setPlaceholderFontColor(Color3B::WHITE);
        _editName->setMaxLength(8);
        _editName->setFontSize((int)editBoxSize.height/2);
        _editName->setText("v👐👊💝");
        _editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
        _editName->setDelegate(this);
        _editName->setVisible(true);
        addChild(_editName);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png",
                                        "cocosui/animationbuttonpressed.png");
        auto buttonSize = button->getContentSize();
        button->setTitleText("Toggle Visibility");
        button->setPosition(_editName->getPosition() + Vec2(editBoxSize.width/2 + buttonSize.width/2, 0.0f));
        button->addClickEventListener([=](Ref* ref){
            _editName->setVisible(!_editName->isVisible());
        });
        addChild(button);
        
        // middle
        _editPassword = ui::EditBox::create(editBoxSize, "extensions/orange_edit.png");
        _editPassword->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2-50, visibleOrigin.y+visibleSize.height/2));
        _editPassword->setFontColor(Color3B::GREEN);
        _editPassword->setPlaceHolder("Password:");
        _editPassword->setMaxLength(6);
        _editPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
        _editPassword->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
        _editPassword->setFontSize((float)editBoxSize.height/2);
        _editPassword->setDelegate(this);
        _editPassword->setVisible(true);
        addChild(_editPassword);
        
        auto buttonPassword = (ui::Button*)button->clone();
        buttonPassword->setTitleText("Toggle Visibility");
        buttonPassword->setPosition(_editPassword->getPosition() + Vec2(editBoxSize.width/2 + buttonSize.width/2, 0.0f));
        buttonPassword->addClickEventListener([=](Ref* ref){
            _editPassword->setVisible(!_editPassword->isVisible());
        });
        addChild(buttonPassword);
        
        // bottom
        // Add an intermediate Node to test scaling and content size relative to world
        _editEmailParent = Node::create();
        //        _editEmailParent->setScale(0.5);
        _editEmailParent->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2-50, visibleOrigin.y+visibleSize.height/4));
        addChild(_editEmailParent);
        
        auto bottomButtonSize = Size(editBoxSize.width, editBoxSize.height + 10);
        _editEmail = ui::EditBox::create(bottomButtonSize, "extensions/yellow_edit.png");
        _editEmail->setPlaceHolder("Email:");
        _editEmail->setInputMode(ui::EditBox::InputMode::EMAIL_ADDRESS);
        _editEmail->setDelegate(this);
        _editEmail->setVisible(true);
        _editEmailParent->addChild(_editEmail);
        //It is required to use setFontSize and setContentSize after adding it to the hierarchy, so that native EditBox get the right size
        _editEmail->setFontSize(30);
        _editEmail->setContentSize(bottomButtonSize);
        
        auto buttonEmail = (ui::Button*)button->clone();
        buttonEmail->setTitleText("Toggle Visibility");
        buttonEmail->setPosition(_editEmailParent->getPosition() + Vec2(editBoxSize.width/2 + buttonSize.width/2, 0.0f));
        buttonEmail->addClickEventListener([=](Ref* ref){
            _editEmail->setVisible(!_editEmail->isVisible());
        });
        addChild(buttonEmail);
        
        return true;
    }
    return false;
}

void UIEditBoxTestToggleVisibility::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
    log("editBox %p DidBegin !", editBox);
}

void UIEditBoxTestToggleVisibility::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
    log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void UIEditBoxTestToggleVisibility::editBoxReturn(ui::EditBox* editBox)
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

// UIEditBoxTestTextHorizontalAlignment

bool UIEditBoxTestTextHorizontalAlignment::init() {
    if (!UIScene::init()) {
      return false;
    }
  
    const auto glview = Director::getInstance()->getOpenGLView();
    const auto visibleOrigin = glview->getVisibleOrigin();
    const auto visibleSize = glview->getVisibleSize();
    const auto editBoxSize = Size(visibleSize.width - 100, visibleSize.height * 0.1f);
  
    const auto createEditBox = [this, editBoxSize, visibleOrigin, visibleSize](const std::string& text,
                                      const TextHAlignment alignment,
                                      const int position_y) {
        ui::EditBox* editbox = ui::EditBox::create(editBoxSize + Size(0,40), ui::Scale9Sprite::create("extensions/green_edit.png"));
        editbox->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2-50, (float)position_y));
        editbox->setFontColor(Color3B::RED);
        editbox->setPlaceHolder(text.c_str());
        editbox->setPlaceholderFontColor(Color3B::WHITE);
        editbox->setPlaceholderFontSize((int)editBoxSize.height/2);
        editbox->setFontSize((int)editBoxSize.height/2);
        editbox->setText(text.c_str());
        editbox->setTextHorizontalAlignment(alignment);
        editbox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
        addChild(editbox);
    };
  
    createEditBox("horizontal left text", TextHAlignment::LEFT, (int)(visibleOrigin.y+visibleSize.height*3/4));
    createEditBox("horizontal center text", TextHAlignment::CENTER, (int)(visibleOrigin.y+visibleSize.height/2));
    createEditBox("horizontal right text", TextHAlignment::RIGHT, (int)(visibleOrigin.y+visibleSize.height/4));
  
    return true;
}

// UIEditBoxTestPressedAndDisabled
bool UIEditBoxTestPressedAndDisabled::init() {
    if (!UIScene::init()) {
        return false;
    }

    auto glview = Director::getInstance()->getOpenGLView();
    auto visibleOrigin = glview->getVisibleOrigin();
    auto visibleSize = glview->getVisibleSize();
    const auto editBoxSize = Size(visibleSize.width - 100, visibleSize.height * 0.1f);

    ui::EditBox* editbox = ui::EditBox::create(editBoxSize + Size(0,40), "extensions/yellow_edit.png", "extensions/orange_edit.png");
    editbox->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height*3/4));
    editbox->setFontColor(Color3B::GREEN);
    editbox->setPlaceHolder("Test Pressed Image");
    editbox->setPlaceholderFontColor(Color3B::WHITE);
    editbox->setPlaceholderFontSize((int)editBoxSize.height/2);
    editbox->setFontSize((int)editBoxSize.height/2);
    editbox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    addChild(editbox);

    editbox = ui::EditBox::create(editBoxSize + Size(0,40), "extensions/yellow_edit.png", "extensions/orange_edit.png", "extensions/green_edit.png");
    editbox->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
    editbox->setFontColor(Color3B::GREEN);
    editbox->setPlaceHolder("Test Disabled Image - green");
    editbox->setPlaceholderFontColor(Color3B::WHITE);
    editbox->setPlaceholderFontSize((int)editBoxSize.height/2);
    editbox->setFontSize((int)editBoxSize.height/2);
    editbox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    addChild(editbox);
    editbox->setEnabled(false);

    editbox = ui::EditBox::create(editBoxSize + Size(0,40), "extensions/yellow_edit.png");
    editbox->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/4));
    editbox->setFontColor(Color3B::GREEN);
    editbox->setPlaceHolder("Disabled Gray effect");
    editbox->setPlaceholderFontColor(Color3B::WHITE);
    editbox->setPlaceholderFontSize((int)editBoxSize.height/2);
    editbox->setFontSize((int)editBoxSize.height/2);
    editbox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    addChild(editbox);
    editbox->setEnabled(false);

    return true;
}
