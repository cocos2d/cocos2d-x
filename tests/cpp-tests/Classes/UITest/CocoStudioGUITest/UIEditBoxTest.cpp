/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

// UIEditBoxTest
UIEditBoxTest::UIEditBoxTest()
{
    
}

UIEditBoxTest::~UIEditBoxTest()
{
}

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
        
        
        auto editBoxSize = Size(visibleSize.width - 100, 60);
        
        // top
        std::string pNormalSprite = "extensions/green_edit.png";
        _editName = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create(pNormalSprite));
        _editName->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height*3/4));
        _editName->setFontName("Paint Boy");
        _editName->setFontSize(25);
        _editName->setFontColor(Color3B::RED);
        _editName->setPlaceHolder("Name:");
        _editName->setPlaceholderFontColor(Color3B::WHITE);
        _editName->setMaxLength(8);
        _editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
        _editName->setDelegate(this);
        addChild(_editName);
        
        // middle
        _editPassword = ui::EditBox::create(editBoxSize, "extensions/orange_edit.png");
        _editPassword->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
        _editPassword->setFontColor(Color3B::GREEN);
        _editPassword->setPlaceHolder("Password:");
        _editPassword->setMaxLength(6);
        _editPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
        _editPassword->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
        _editPassword->setDelegate(this);
        addChild(_editPassword);
        
        // bottom
        _editEmail = ui::EditBox::create(Size(editBoxSize.width, editBoxSize.height), "extensions/yellow_edit.png");
        _editEmail->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/4));
        _editEmail->setAnchorPoint(Vec2(0.5, 1.0f));
        _editEmail->setPlaceHolder("Email:");
        _editEmail->setInputMode(ui::EditBox::InputMode::EMAIL_ADDRESS);
        _editEmail->setDelegate(this);
        addChild(_editEmail);
        
        this->setPosition(Vec2(10, 20));
        
      
        
        return true;
    }
    return false;
}

void UIEditBoxTest::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
    log("editBox %p DidBegin !", editBox);
}

void UIEditBoxTest::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
    log("editBox %p DidEnd !", editBox);
}

void UIEditBoxTest::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
    log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
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
