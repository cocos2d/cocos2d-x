#ifndef _CCBX_CCTEXTLOADER_H_
#define _CCBX_CCTEXTLOADER_H_

#include "base/CCRef.h"

#include "CCBXWidgetLoader.h"

NS_CC_BEGIN
namespace spritebuilder {

class CC_DLL TextLoader : public WidgetLoader {
public:
    
    static TextLoader *create();
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;
    virtual void setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;
    
CC_CONSTRUCTOR_ACCESS:
    TextLoader();
    ~TextLoader();

protected:
    virtual void onHandlePropTypeColor4(const std::string &propertyName, bool isExtraProp, const Color4B &value) override;
    virtual void onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value) override;
    virtual void onHandlePropTypeFontTTF(const std::string &propertyName, bool isExtraProp, const std::string &value) override;
    virtual void onHandlePropTypeText(const std::string &propertyName, bool isExtraProp, const std::string &value) override;
    virtual void onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value) override;
    virtual void onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value) override;
    virtual void onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value) override;
    virtual void onHandlePropTypePosition(const std::string &propertyName, bool isExtraProp, const PositionDescription &value) override;
    virtual void onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value) override;
    
private:
    cocos2d::Color4B _outlineColor;
    cocos2d::Color4B _shadowColor;
    FloatScaleDescription _outlineWidth;
    FloatScaleDescription _shadowBlurRadius;
    PositionDescription _shadowOffset;
    std::string _label;
    std::string _font;
    FloatScaleDescription _fontSize;
    TextHAlignment _textHAlignment;
    TextVAlignment _textVAlignment;
    BlendFunc _blendFunc;
    Color4B _fontColor;
    SizeDescription _dimensions;
    bool _adjustsFontSizeToFit;
    int _overflowLabel;
    bool _wordWrapLabel;
};

}

NS_CC_END

#endif
