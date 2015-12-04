#ifndef _CCBX_CCPROGRESSTIMERLOADER_H_
#define _CCBX_CCPROGRESSTIMERLOADER_H_

#include "CCBXNodeLoader.h"

NS_CC_BEGIN

namespace spritebuilder {

class CC_DLL ProgressTimerLoader : public NodeLoader {
public:
    
    static ProgressTimerLoader *create();
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;
    virtual void setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;
    
CC_CONSTRUCTOR_ACCESS:
    ProgressTimerLoader();
    ~ProgressTimerLoader();
    
protected:
    
    virtual void onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value) override;
    virtual void onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value) override;
    virtual void onHandlePropTypeFlip(const std::string &propertyName, bool isExtraProp, const std::pair<bool,bool> &flip) override;
    virtual void onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value) override;
    virtual void onHandlePropTypePoint(const std::string &propertyName, bool isExtraProp, const cocos2d::Point &value) override;
    virtual void onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value) override;
    virtual void onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value) override;
    
private:
    float _percentage;
    SpriteFrameDescription _spriteFrame;
    int _type;
    cocos2d::Point _midpoint;
    cocos2d::Point _barChangeRate;
    BlendFunc _blendFunc;
    bool _reverseDirection;
    std::pair<bool,bool> _flipped;
};
    
}

NS_CC_END

#endif //_CCBX_CCPROGRESSTIMERLOADER_H_
