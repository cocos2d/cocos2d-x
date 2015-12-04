#ifndef _CCBX_CCLOADINGBARLOADER_H_
#define _CCBX_CCLOADINGBARLOADER_H_

#include "CCBXWidgetLoader.h"
#include "ui/UILoadingBar.h"

NS_CC_BEGIN

namespace spritebuilder {

class CC_DLL LoadingBarLoader : public WidgetLoader {
public:
    
    static LoadingBarLoader *create();
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;
    virtual void setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;
    
CC_CONSTRUCTOR_ACCESS:
    LoadingBarLoader();
    ~LoadingBarLoader();
    
protected:
    
    virtual void onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value) override;
    virtual void onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value) override;
    virtual void onHandlePropTypeFlip(const std::string &propertyName, bool isExtraProp, const std::pair<bool,bool> &flip) override;
    virtual void onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value) override;
    virtual void onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value) override;
    virtual void onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value) override;
    virtual void onHandlePropTypeOffsets(const std::string &propertyName, bool isExtraProp, const Vec4 &value) override;
    
private:
    float _percentage;
    SpriteFrameDescription _spriteFrame;
    ui::LoadingBar::Direction _direction;
    std::pair<bool,bool> _flipped;
    Vec4 _margins;
    FloatScaleDescription _imageScale;
};
    
}

NS_CC_END

#endif //_CCBX_CCPROGRESSTIMERLOADER_H_
