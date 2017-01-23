#include "CCBXLabelTTFLoader.h"
#include "2d/CCLabel.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN
namespace spritebuilder {

static const std::string PROPERTY_BLENDFUNC("blendFunc");
static const std::string PROPERTY_FONTNAME("fontName");
static const std::string PROPERTY_FONTSIZE("fontSize");
static const std::string PROPERTY_HORIZONTALALIGNMENT("horizontalAlignment");
static const std::string PROPERTY_VERTICALALIGNMENT("verticalAlignment");
static const std::string PROPERTY_STRING("string");
static const std::string PROPERTY_DIMENSIONS("dimensions");

static const std::string PROPERTY_FONTCOLOR("fontColor");
static const std::string PROPERTY_OUTLINECOLOR("outlineColor");
static const std::string PROPERTY_OUTLINEWIDTH("outlineWidth");

static const std::string PROPERTY_SHADOWCOLOR("shadowColor");

static const std::string PROPERTY_SHADOWBLURRADIUS("shadowBlurRadius");
static const std::string PROPERTY_SHADOWWIDTH("shadowWidth");

static const std::string PROPERTY_SHADOWOFFSET("shadowOffset");
    
static const std::string PROPERTY_CONTENTSIZE("contentSize");
static const std::string PROPERTY_ADJUSTS_FONT_SIZE_TO_FIT("adjustsFontSizeToFit");
static const std::string PROPERTY_OVERFLOW("overflowType");
static const std::string PROPERTY_WORDWRAP("wordWrap");
    
LabelTTFLoader *LabelTTFLoader::create()
{
    LabelTTFLoader *ret = new LabelTTFLoader();
    ret->autorelease();
    return ret;
}

Node *LabelTTFLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    Label *label = Label::create();
    label->setAnchorPoint(cocos2d::Vec2(0,0));
    return label;
}

void LabelTTFLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    Label *label = dynamic_cast<Label*>(node);
    if(label)
    {
        Size dimensions = getAbsoluteSize(mainScale, additionalScale, _dimensions.size, _dimensions.widthUnits, _dimensions.heightUnits, parentSize);
        float fontSize = getAbsoluteScale(mainScale, additionalScale, _fontSize.scale, _fontSize.type);
        float outlineWidth = getAbsoluteScale(mainScale, additionalScale, _outlineWidth.scale, _outlineWidth.type);
        if (FileUtils::getInstance()->isFileExist(_font))
        {
            TTFConfig ttfConfig(_font, fontSize, GlyphCollection::DYNAMIC);
            ttfConfig.outlineSize = outlineWidth;
            label->setTTFConfig(ttfConfig);
        }
        else
        {
            label->setSystemFontName(_font);
            label->setSystemFontSize(fontSize);
        }
        
        label->setDimensions(dimensions.width, dimensions.height);
        label->setString(_label);
        label->setBlendFunc(_blendFunc);
        float shadowBlurRadius = getAbsoluteScale(mainScale, additionalScale, _shadowBlurRadius.scale, _shadowBlurRadius.type);
        Vec2 shadowOffset = getAbsolutePosition(mainScale, additionalScale, _shadowOffset.pos, _shadowOffset.referenceCorner, _shadowOffset.xUnits, _shadowOffset.yUnits, parentSize);
        if (_outlineColor.a > 0 && outlineWidth > 0)
            label->enableOutline(_outlineColor, outlineWidth);
        if (_shadowColor.a > 0)
            label->enableShadow(_shadowColor, Size(shadowOffset.x, shadowOffset.y), shadowBlurRadius);
        if(_fontColor != Color4B::WHITE)
            label->setTextColor(_fontColor);
        
        Label::Overflow overflow = static_cast<Label::Overflow>(_overflowLabel);
        label->setOverflow((_adjustsFontSizeToFit && overflow == Label::Overflow::NONE) ? Label::Overflow::SHRINK : overflow);
        label->setLineBreakWithoutSpace(!_wordWrapLabel);
        label->setAlignment(_textHAlignment, _textVAlignment);
    }
}

LabelTTFLoader::LabelTTFLoader()
    :_blendFunc(BlendFunc::ALPHA_PREMULTIPLIED)
    ,_outlineColor(0,0,0,0)
    ,_shadowColor(0,0,0,127)
	,_outlineWidth(FloatScaleDescription{0, 0.0f})
	,_shadowBlurRadius(FloatScaleDescription{0, 0.0f})
	,_shadowOffset(PositionDescription{PositionReferenceCorner::BOTTOMLEFT, PositionUnit::POINTS, PositionUnit::POINTS, Vec2(0, 0)})
    ,_textHAlignment(TextHAlignment::LEFT)
    ,_textVAlignment(TextVAlignment::TOP)
	,_dimensions(SizeDescription{SizeUnit::POINTS, SizeUnit::POINTS, {0, 0}})
    ,_fontColor(Color4B::WHITE)
    ,_adjustsFontSizeToFit(false)
    ,_overflowLabel(static_cast<int>(cocos2d::Label::Overflow::NONE))
    ,_wordWrapLabel(true)
{
    
}
    
LabelTTFLoader::~LabelTTFLoader()
{
    
}
    
void LabelTTFLoader::onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value)
{
    if(propertyName == PROPERTY_ADJUSTS_FONT_SIZE_TO_FIT){
        _adjustsFontSizeToFit = value;
    } else {
        NodeLoader::onHandlePropTypeCheck(propertyName, isExtraProp, value);
    }
}
    
void LabelTTFLoader::onHandlePropTypeColor4(const std::string &propertyName, bool isExtraProp, const Color4B &value)
{
    if(propertyName == PROPERTY_FONTCOLOR){
        _fontColor = value;
    } else if(propertyName == PROPERTY_OUTLINECOLOR){
        _outlineColor = value;
    } else if(propertyName == PROPERTY_SHADOWCOLOR){
        _shadowColor = value;
    } else {
        NodeLoader::onHandlePropTypeColor4(propertyName, isExtraProp, value);
    }
}

void LabelTTFLoader::onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value)
{
    if(propertyName == PROPERTY_BLENDFUNC) {
        _blendFunc = value;
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(propertyName, isExtraProp, value);
    }
}

void LabelTTFLoader::onHandlePropTypeFontTTF(const std::string &propertyName, bool isExtraProp, const std::string &value)
{
    if(propertyName == PROPERTY_FONTNAME) {
        _font = value;
    } else {
        NodeLoader::onHandlePropTypeFontTTF(propertyName, isExtraProp, value);
    }
}

void LabelTTFLoader::onHandlePropTypeText(const std::string &propertyName, bool isExtraProp, const std::string &value)
{
    if(propertyName == PROPERTY_STRING) {
        _label = value;
    } else {
        NodeLoader::onHandlePropTypeText(propertyName, isExtraProp, value);
    }
}

void LabelTTFLoader::onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value)
{
    if(propertyName == PROPERTY_FONTSIZE) {
        _fontSize = value;
    } else if(propertyName == PROPERTY_OUTLINEWIDTH) {
        _outlineWidth = value;
    } else if(propertyName == PROPERTY_SHADOWBLURRADIUS) {
        _shadowBlurRadius = value;
    } else {
        NodeLoader::onHandlePropTypeFloatScale(propertyName, isExtraProp, value);
    }
}

void LabelTTFLoader::onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_HORIZONTALALIGNMENT) {
        _textHAlignment = static_cast<TextHAlignment>(value);
    } else if(propertyName == PROPERTY_VERTICALALIGNMENT) {
        _textVAlignment = static_cast<TextVAlignment>(value);
    }else if (propertyName == PROPERTY_OVERFLOW) {
        _overflowLabel = value;
    }else if (propertyName == PROPERTY_WORDWRAP) {
        _wordWrapLabel = static_cast<bool>(value);
    } else {
        NodeLoader::onHandlePropTypeIntegerLabeled(propertyName, isExtraProp, value);
    }
}

void LabelTTFLoader::onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value)
{
    if(propertyName == PROPERTY_DIMENSIONS) {
        _dimensions = value;
    } else {
        NodeLoader::onHandlePropTypeSize(propertyName, isExtraProp, value);
    }
}

void LabelTTFLoader::onHandlePropTypePosition(const std::string &propertyName, bool isExtraProp, const PositionDescription &value)
{
    if(propertyName == PROPERTY_SHADOWOFFSET) {
        _shadowOffset = value;
    } else {
        NodeLoader::onHandlePropTypePosition(propertyName, isExtraProp, value);
    }
}

}
    
NS_CC_END
