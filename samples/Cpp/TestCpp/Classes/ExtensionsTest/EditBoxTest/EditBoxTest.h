//
//  CCEditBoxTest.h
//  TestCpp
//
//  Created by James on 8/14/12.
//
//

#ifndef __TestCpp__CCEditBoxTest__
#define __TestCpp__CCEditBoxTest__

#include "cocos2d.h"
#include "cocos-ext.h"

class EditBoxTest : public cocos2d::CCLayer, public cocos2d::extension::CCEditBoxDelegate
{
public:
    EditBoxTest();
    virtual ~EditBoxTest();
    void toExtensionsMainLayer(cocos2d::CCObject *sender);
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
private:
    cocos2d::CCLabelTTF* m_pTTFShowEditReturn;
    cocos2d::extension::CCEditBox* m_pEditName;
    cocos2d::extension::CCEditBox* m_pEditPassword;
    cocos2d::extension::CCEditBox* m_pEditEmail;
};

void runEditBoxTest();

#endif /* defined(__TestCpp__CCEditBoxTest__) */
