/****************************************************************************
 Copyright (c) 2015 cocos2d-x.org
 
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

#ifndef __TestCpp__UIRadioButtonTest__
#define __TestCpp__UIRadioButtonTest__

#include "../UIScene.h"

DEFINE_TEST_SUITE(UIRadioButtonTests);

class UIRadioButtonTest : public UIScene
{
public:
    CREATE_FUNC(UIRadioButtonTest);
    
    UIRadioButtonTest();
    ~UIRadioButtonTest();
    
    virtual bool init() override;
    
    void addRadioButton(Ref* sender);
    void deleteRadioButton(Ref* sender);

private:
    cocos2d::ui::RadioButtonGroup* _radioButtonGroup;
    cocos2d::ui::Text* _allowNoSelectionText;
    
};


class UIRadioButtonTwoGroupsTest : public UIScene
{
public:
    CREATE_FUNC(UIRadioButtonTwoGroupsTest);

    UIRadioButtonTwoGroupsTest();
    ~UIRadioButtonTwoGroupsTest();

    virtual bool init() override;
    void onChangedRadioButtonGroup1(cocos2d::ui::RadioButton* radioButton, int index, cocos2d::ui::RadioButtonGroup::EventType type);
    void onChangedRadioButtonGroup2(cocos2d::ui::RadioButton* radioButton, int index, cocos2d::ui::RadioButtonGroup::EventType type);
    void onChangedRadioButtonSelect(cocos2d::ui::RadioButton* radioButton,cocos2d::ui::RadioButton::EventType type);
    void clearRadioButtonGroup(Ref* sender);

    
protected:
    void addLog(const std::string& log);
    
    cocos2d::ui::RadioButtonGroup* _radioButtonGroups[2];
    cocos2d::ui::Text* _groupEventLabel;
    cocos2d::ui::Text* _buttonEventLabel;
    cocos2d::ui::Text* _logConsole;
    int _numberOfLogLines;
};

class UIRadioButtonTabTest : public UIScene
{
public:
    CREATE_FUNC(UIRadioButtonTabTest);
    virtual bool init() override;
};

#endif /* defined(__TestCpp__UIRadioButtonTest__) */
