#ifndef _CCB_CCSCALE9SPRITELOADER_H_
#define _CCB_CCSCALE9SPRITELOADER_H_

#include "CCNodeLoader.h"
#include "CCScale9SpriteLoader.h"
#include "ui/UIScale9Sprite.h"

namespace spritebuilder {

/* Forward declaration. */
class CCBReader;

class Scale9SpriteLoader : public NodeLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Scale9SpriteLoader() {};
    /**
     * @js NA
     * @lua NA
     */
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(Scale9SpriteLoader, loader);

protected:
    /**
     * @js NA
     * @lua NA
     */
    virtual cocos2d::ui::Scale9Sprite * createNode(cocos2d::Node * pParent, spritebuilder::CCBReader * ccbReader) {
        cocos2d::ui::Scale9Sprite* pNode = cocos2d::ui::Scale9Sprite::create();
        
        pNode->setAnchorPoint(cocos2d::Point(0,0));
        
        return pNode;
    };
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeColor4(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color4F pColor4F, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeByte(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::BlendFunc pBlendFunc, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeSpriteFrame(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Size pSize, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeFloat(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, float pFloat, CCBReader * ccbReader);
    virtual void onDone(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);    
private:
    float _insetLeft;
    float _insetTop;
    float _insetRight;
    float _insetBottom;
    cocos2d::Size _contentSize;
    cocos2d::Size _preferedSize;
    cocos2d::SpriteFrame* _spriteFrame;
};

}

#endif
