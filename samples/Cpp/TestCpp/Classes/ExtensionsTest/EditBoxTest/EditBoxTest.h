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

class EditBoxTest : public cocos2d::Layer, public cocos2d::extension::EditBoxDelegate
{
public:
    EditBoxTest();
    virtual ~EditBoxTest();
    void toExtensionsMainLayer(cocos2d::Object *sender);
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
private:
    cocos2d::LabelTTF* _TTFShowEditReturn;
    cocos2d::extension::EditBox* _editName;
    cocos2d::extension::EditBox* _editPassword;
    cocos2d::extension::EditBox* _editEmail;
};

void runEditBoxTest();

#endif /* defined(__TestCpp__CCEditBoxTest__) */
