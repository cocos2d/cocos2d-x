#ifndef _SB_CCEDITBOXLOADER_H_
#define _SB_CCEDITBOXLOADER_H_

#include "CCNodeLoader.h"
#include "CCExtTextField.h"

namespace spritebuilder {
    
/* Forward declaration. */
class CCBReader;


class EditBoxLoader : public NodeLoader {
public:
    //EditBoxLoader() {}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxLoader() {};
    /**
     * @js NA
     * @lua NA
     */
   
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EditBoxLoader, loader);
    
protected:
    SB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ExtTextField);
    
    /**
     * @js NA
     * @lua NA
     */

    virtual void onHandlePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Size pSize, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeSpriteFrame(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float pFloatScale, CCBReader * ccbReader);
    
    virtual void onHandlePropTypeBlockControl(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, BlockControlData * pBlockControlData, CCBReader * ccbReader);

};


};

#endif
