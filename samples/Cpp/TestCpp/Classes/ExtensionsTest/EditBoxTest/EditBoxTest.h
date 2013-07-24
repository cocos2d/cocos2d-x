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
#include "cocos-ext.h"

class EditBoxTest : public cc::Layer, public cc::extension::EditBoxDelegate
{
public:
    EditBoxTest();
    virtual ~EditBoxTest();
    void toExtensionsMainLayer(cc::Object *sender);
    
    virtual void editBoxEditingDidBegin(cc::extension::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cc::extension::EditBox* editBox);
    virtual void editBoxTextChanged(cc::extension::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cc::extension::EditBox* editBox);
private:
    cc::LabelTTF* _TTFShowEditReturn;
    cc::extension::EditBox* _editName;
    cc::extension::EditBox* _editPassword;
    cc::extension::EditBox* _editEmail;
};

void runEditBoxTest();

#endif /* defined(__TestCpp__CCEditBoxTest__) */
