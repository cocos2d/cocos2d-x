#include "CCBXTextFieldLoader.h"
#include "ui/UITextField.h"

NS_CC_BEGIN
namespace spritebuilder {

static const std::string PROPERTY_BLENDFUNC("blendFunc");
static const std::string PROPERTY_FONTCOLOR("fontColor");
static const std::string PROPERTY_FONTNAME("fontName");
static const std::string PROPERTY_FONTSIZE("fontSize");
static const std::string PROPERTY_HORIZONTALALIGNMENT("horizontalAlignment");
static const std::string PROPERTY_VERTICALALIGNMENT("verticalAlignment");
static const std::string PROPERTY_STRING("string");

static const std::string PROPERTY_PLACEHOLDERFONTCOLOR("placeholderFontColor");
static const std::string PROPERTY_PLACEHOLDER("placeholder");

static const std::string PROPERTY_CONTENTSIZE("contentSize");
    
static const std::string PROPERTY_MAXLENGTH("maxLength");
    
    
TextFieldLoader *TextFieldLoader::create()
{
    TextFieldLoader *ret = new TextFieldLoader();
    ret->autorelease();
    return ret;
}

Node *TextFieldLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    ui::TextField *textField = ui::TextField::create(_placeholder, _font, getAbsoluteScale(mainScale, additionalScale, _fontSize.scale, _fontSize.type));
    textField->setAnchorPoint(Vec2(0.0f, 0.0f));
    textField->setString(_label);
    textField->setTextVerticalAlignment(_textVAlignment);
    textField->setTextHorizontalAlignment(_textHAlignment);
    textField->setTextColor(Color4B(_fontColor));
    textField->setPlaceHolderColor(_placeholderFontColor);
    if(_maxLength>0)
    {
        textField->setMaxLengthEnabled(true);
        textField->setMaxLength(_maxLength);
    }
    textField->setPasswordEnabled(_password);
    return textField;
}

void TextFieldLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    WidgetLoader::setSpecialProperties(node, parentSize, mainScale, additionalScale, owner, rootNode, rootOwner);
}

TextFieldLoader::TextFieldLoader()
{
    
}
    
TextFieldLoader::~TextFieldLoader()
{
    
}
    
void TextFieldLoader::onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value)
{
    WidgetLoader::onHandlePropTypeCheck(propertyName, isExtraProp, value);
}
    
void TextFieldLoader::onHandlePropTypeColor3(const std::string &propertyName, bool isExtraProp, const Color3B &value)
{
    if(propertyName == PROPERTY_PLACEHOLDERFONTCOLOR) {
        _placeholderFontColor = value;
    } else if(propertyName == PROPERTY_FONTCOLOR) {
        _fontColor = value;
    } else {
        WidgetLoader::onHandlePropTypeColor3(propertyName, isExtraProp, value);
    }
}
    
void TextFieldLoader::onHandlePropTypeColor4(const std::string &propertyName, bool isExtraProp, const Color4B &value)
{
    WidgetLoader::onHandlePropTypeColor4(propertyName, isExtraProp, value);
}

void TextFieldLoader::onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value)
{
    if(propertyName == PROPERTY_BLENDFUNC) {
        //((LayerColor *)pNode)->setBlendFunc(pBlendFunc);
    }  else {
        WidgetLoader::onHandlePropTypeBlendFunc(propertyName, isExtraProp, value);
    }
}

void TextFieldLoader::onHandlePropTypeFontTTF(const std::string &propertyName, bool isExtraProp, const std::string &value)
{
    if(propertyName == PROPERTY_FONTNAME) {
        _font = value;
    } else {
        WidgetLoader::onHandlePropTypeFontTTF(propertyName, isExtraProp, value);
    }
}

void TextFieldLoader::onHandlePropTypeText(const std::string &propertyName, bool isExtraProp, const std::string &value)
{
    if(propertyName == PROPERTY_STRING) {
        _label = value;
    } else if(propertyName == PROPERTY_PLACEHOLDER) {
        _placeholder = value;
    } else {
        WidgetLoader::onHandlePropTypeText(propertyName, isExtraProp, value);
    }
}

void TextFieldLoader::onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value)
{
    if(propertyName == PROPERTY_FONTSIZE) {
        _fontSize = value;
    } else {
        WidgetLoader::onHandlePropTypeFloatScale(propertyName, isExtraProp, value);
    }
}
    
void TextFieldLoader::onHandlePropTypeInteger(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_MAXLENGTH) {
        _maxLength = value;
    } else {
        WidgetLoader::onHandlePropTypeInteger(propertyName, isExtraProp, value);
    }
}

void TextFieldLoader::onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_HORIZONTALALIGNMENT) {
        _textHAlignment = static_cast<TextHAlignment>(value);
    } else if(propertyName == PROPERTY_VERTICALALIGNMENT) {
        _textVAlignment = static_cast<TextVAlignment>(value);
    } else {
        WidgetLoader::onHandlePropTypeIntegerLabeled(propertyName, isExtraProp, value);
    }
}

void TextFieldLoader::onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value)
{
    WidgetLoader::onHandlePropTypeSize(propertyName, isExtraProp, value);
}

void TextFieldLoader::onHandlePropTypePosition(const std::string &propertyName, bool isExtraProp, const PositionDescription &value)
{
    WidgetLoader::onHandlePropTypePosition(propertyName, isExtraProp, value);
}

}
    
NS_CC_END
