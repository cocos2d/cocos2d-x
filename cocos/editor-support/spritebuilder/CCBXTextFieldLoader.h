#ifndef _CCBX_CCTEXFIELDTLOADER_H_
#define _CCBX_CCTEXFIELDTLOADER_H_

#include "base/CCRef.h"

#include "CCBXWidgetLoader.h"

NS_CC_BEGIN
namespace spritebuilder {

class CC_DLL TextFieldLoader : public WidgetLoader {
public:
    
    static TextFieldLoader *create();
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const override;
    virtual void setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const override;
    
CC_CONSTRUCTOR_ACCESS:
    TextFieldLoader();
    ~TextFieldLoader();

protected:
    virtual void onHandlePropTypeColor3(const std::string &propertyName, bool isExtraProp, const Color3B &value) override;
    virtual void onHandlePropTypeColor4(const std::string &propertyName, bool isExtraProp, const Color4B &value) override;
    virtual void onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value) override;
    virtual void onHandlePropTypeFontTTF(const std::string &propertyName, bool isExtraProp, const std::string &value) override;
    virtual void onHandlePropTypeText(const std::string &propertyName, bool isExtraProp, const std::string &value) override;
    virtual void onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value) override;
    virtual void onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value) override;
    virtual void onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value) override;
    virtual void onHandlePropTypePosition(const std::string &propertyName, bool isExtraProp, const PositionDescription &value) override;
    virtual void onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value) override;
    virtual void onHandlePropTypeInteger(const std::string &propertyName, bool isExtraProp, int value) override;
    
private:
    cocos2d::Color3B _fontColor = cocos2d::Color3B::WHITE;
    cocos2d::Color3B _placeholderFontColor = cocos2d::Color3B::WHITE;
    FloatScaleDescription _fontSize;
    std::string _label;
    std::string _placeholder;
    std::string _font;
    TextHAlignment _textHAlignment;
    TextVAlignment _textVAlignment;
    int _maxLength = 0;
    bool _password = false;
};

}

NS_CC_END

#endif
