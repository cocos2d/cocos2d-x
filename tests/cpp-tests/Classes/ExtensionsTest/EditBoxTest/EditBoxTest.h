//
//  EditBoxTest.h
//  TestCpp
//
//  Created by James on 8/14/12.
//
//

#ifndef __TestCpp__CCEditBoxTest__
#define __TestCpp__CCEditBoxTest__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

class EditBoxTest : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{
public:
    EditBoxTest();
    virtual ~EditBoxTest();
    void toExtensionsMainLayer(cocos2d::Ref *sender);
    
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
private:
    cocos2d::Label* _TTFShowEditReturn;
    cocos2d::ui::EditBox* _editName;
    cocos2d::ui::EditBox* _editPassword;
    cocos2d::ui::EditBox* _editEmail;
};

void runEditBoxTest();

#endif /* defined(__TestCpp__CCEditBoxTest__) */
