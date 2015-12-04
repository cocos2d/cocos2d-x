#include "CCBXButtonLoader.h"
#include "2d/CCLabel.h"
#include "ui/UIButton.h"

NS_CC_BEGIN
namespace spritebuilder {

static const std::string PROPERTY_ZOOMONCLICK("zoomOnClick");
static const std::string PROPERTY_LABELANCHORPOINT("labelAnchorPoint");
static const std::string PROPERTY_PREFERREDSIZE("preferredSize");
static const std::string PROPERTY_CONTENTSIZE("contentSize");
static const std::string PROPERTY_MAXSIZE("maxSize");
    
static const std::string PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL("backgroundSpriteFrame|Normal");
static const std::string PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED("backgroundSpriteFrame|Highlighted");
static const std::string PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED("backgroundSpriteFrame|Disabled");
    
static const std::string PROPERTY_BACKGROUNDOPACITY_NORMAL("backgroundOpacity|Normal");
static const std::string PROPERTY_BACKGROUNDOPACITY_HIGHLIGHTED("backgroundOpacity|Highlighted");
static const std::string PROPERTY_BACKGROUNDOPACITY_DISABLED("backgroundOpacity|Disabled");
    
static const std::string PROPERTY_LABELOPACITY_NORMAL("labelOpacity|Normal");
static const std::string PROPERTY_LABELOPACITY_HIGHLIGHTED("labelOpacity|Highlighted");
static const std::string PROPERTY_LABELOPACITY_DISABLED("labelOpacity|Disabled");
    
static const std::string PROPERTY_TITLE("title");
    
static const std::string PROPERTY_TITLECOLOR_NORMAL("labelColor|Normal");
static const std::string PROPERTY_TITLECOLOR_HIGHLIGHTED("labelColor|Highlighted");
static const std::string PROPERTY_TITLECOLOR_DISABLED("labelColor|Disabled");
    
static const std::string PROPERTY_BACKGROUNDCOLOR_NORMAL("backgroundColor|Normal");
static const std::string PROPERTY_BACKGROUNDCOLOR_HIGHLIGHTED("backgroundColor|Highlighted");
static const std::string PROPERTY_BACKGROUNDCOLOR_DISABLED("backgroundColor|Disabled");
    
static const std::string PROPERTY_HORIZONTALPADDING("horizontalPadding");
static const std::string PROPERTY_VERTICALPADDING("verticalPadding");
    
static const std::string PROPERTY_LEFTPADDING("leftPadding");
static const std::string PROPERTY_RIGHTPADDING("rightPadding");
static const std::string PROPERTY_TOPPADDING("topPadding");
static const std::string PROPERTY_BOTTOMPADDING("bottomPadding");
    
static const std::string PROPERTY_HORIZONTALALIGMENT("horizontalAlignment");
static const std::string PROPERTY_VERTICALALIGMENT("verticalAlignment");
    
static const std::string PROPERTY_FONTNAME("fontName");
static const std::string PROPERTY_FONTSIZE("fontSize");
    
static const std::string PROPERTY_ADJUSTS_FONT_SIZE_TO_FIT("adjustsFontSizeToFit");
    
static const std::string PROPERTY_FONTCOLOR("fontColor");
static const std::string PROPERTY_OUTLINECOLOR("outlineColor");
static const std::string PROPERTY_OUTLINEWIDTH("outlineWidth");
    
static const std::string PROPERTY_SHADOWBLURRADIUS("shadowBlurRadius");
static const std::string PROPERTY_SHADOWWIDTH("shadowWidth");
static const std::string PROPERTY_SHADOWCOLOR("shadowColor");
    
static const std::string PROPERTY_SHADOWOFFSET("shadowOffset");
    
static const std::string PROPERTY_MARGIN("margin");
static const std::string PROPERTY_OFFSET("offset");
    
static const std::string PROPERTY_MARGIN_LEFT("marginLeft");
static const std::string PROPERTY_MARGIN_TOP("marginTop");
static const std::string PROPERTY_MARGIN_RIGHT("marginRight");
static const std::string PROPERTY_MARGIN_BOTTOM("marginBottom");
    
static const std::string PROPERTY_OFFSET_LEFT("offsetLeft");
static const std::string PROPERTY_OFFSET_TOP("offsetTop");
static const std::string PROPERTY_OFFSET_RIGHT("offsetRight");
static const std::string PROPERTY_OFFSET_BOTTOM("offsetBottom");
    
static const std::string PROPERTY_IMAGE_SCALE("imageScale");
static const std::string PROPERTY_OVERFLOW("overflowType");
static const std::string PROPERTY_WORDWRAP("wordWrap");
    
ButtonLoader *ButtonLoader::create()
{
    ButtonLoader *ret = new ButtonLoader();
    ret->autorelease();
    return ret;
}

Node *ButtonLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    Rect margin(_margins.x,_margins.y,1.0-_margins.z-_margins.x,1.0-_margins.w-_margins.y);
    ui::Button *button = ui::Button::create();
    button->setAnchorPoint(Vec2(0.0f, 0.0f));
    switch(_normalSpriteFrame.type)
    {
        case SpriteFrameDescription::TextureResType::LOCAL:
            {
                Size size = _normalSpriteFrame.spriteFrame->getOriginalSize();
                Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
                button->loadTextureNormal(_normalSpriteFrame.path, ui::Widget::TextureResType::LOCAL);
                button->setCapInsetsNormalRenderer(realMargins);
            }
            break;
        case SpriteFrameDescription::TextureResType::PLIST:
            {
                Size size = _normalSpriteFrame.spriteFrame->getOriginalSize();
                Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
                button->loadTextureNormal(_normalSpriteFrame.path, ui::Widget::TextureResType::PLIST);
                button->setCapInsetsNormalRenderer(realMargins);
            }
            break;
        default:
            break;
    };
    switch(_selectedSpriteFrame.type)
    {
        case SpriteFrameDescription::TextureResType::LOCAL:
            {
                Size size = _selectedSpriteFrame.spriteFrame->getOriginalSize();
                Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
                button->loadTexturePressed(_selectedSpriteFrame.path, ui::Widget::TextureResType::LOCAL);
                button->setCapInsetsPressedRenderer(realMargins);
            }
            break;
        case SpriteFrameDescription::TextureResType::PLIST:
            {
                Size size = _selectedSpriteFrame.spriteFrame->getOriginalSize();
                Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
                button->loadTexturePressed(_selectedSpriteFrame.path, ui::Widget::TextureResType::PLIST);
                button->setCapInsetsPressedRenderer(realMargins);
            }
            break;
        default:
            break;
    };
    switch(_disabledSpriteFrame.type)
    {
        case SpriteFrameDescription::TextureResType::LOCAL:
            {
                Size size = _disabledSpriteFrame.spriteFrame->getOriginalSize();
                Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
                button->loadTextureDisabled(_disabledSpriteFrame.path, ui::Widget::TextureResType::LOCAL);
                button->setCapInsetsDisabledRenderer(realMargins);
            }
            break;
        case SpriteFrameDescription::TextureResType::PLIST:
            {
                Size size = _disabledSpriteFrame.spriteFrame->getOriginalSize();
                Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
                button->loadTextureDisabled(_disabledSpriteFrame.path, ui::Widget::TextureResType::PLIST);
                button->setCapInsetsDisabledRenderer(realMargins);
            }
            break;
        default:
            break;
    };
    button->setScale9Enabled(true);
    button->setImageScale(getAbsoluteScale(mainScale, additionalScale, _imageScale.scale, _imageScale.type) / CCBXReader::getResolutionScale());
    return button;
}

void ButtonLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    WidgetLoader::setSpecialProperties(node, parentSize, mainScale, additionalScale, owner, rootNode, rootOwner);
    ui::Button *button = dynamic_cast<ui::Button*>(node);
    if(button)
    {
        button->setPressedActionEnabled(true);
        button->setZoomScale(_zoomOnClick - 1.0);
        button->setNormalTitleColor(_normalLabelColor);
        button->setNormalBackgroundColor(_normalBackgroundColor);
        button->setNormalTitleOpacity(_normalLabelOpacity);
        button->setNormalBackgroundOpacity(_normalBackgroundOpacity);
        
        button->setPressedTitleColor(_selectedLabelColor);
        button->setPressedBackgroundColor(_selectedBackgroundColor);
        button->setPressedTitleOpacity(_selectedLabelOpacity);
        button->setPressedBackgroundOpacity(_selectedBackgroundOpacity);
        
        button->setDisabledTitleColor(_disabledLabelColor);
        button->setDisabledBackgroundColor(_disabledBackgroundColor);
        button->setDisabledTitleOpacity(_disabledLabelOpacity);
        button->setDisabledBackgroundOpacity(_disabledBackgroundOpacity);
        
        button->setTitleFontName(_font);
        //button->getTitleRenderer()->setSystemFontName(_font);
        button->setTitleFontSize(getAbsoluteScale(mainScale, additionalScale, _fontSize.scale, _fontSize.type));
        button->setTitleAlignment(_textHAlignment, _textVAlignment);
        button->setPaddingPadding(getAbsoluteScale(mainScale, additionalScale, _leftPadding.scale, _leftPadding.type),
                                  getAbsoluteScale(mainScale, additionalScale, _topPadding.scale, _topPadding.type),
                                  getAbsoluteScale(mainScale, additionalScale, _rightPadding.scale, _rightPadding.type),
                                  getAbsoluteScale(mainScale, additionalScale, _bottomPadding.scale, _bottomPadding.type));
        button->setOffsets(_offset.x, _offset.y, _offset.z, _offset.w);
        button->setTitleText(_label);
        
        Label::Overflow overflow = static_cast<Label::Overflow>(_overflowLabel);
        button->setOverflow((_adjustsFontSizeToFit && overflow == Label::Overflow::NONE) ? static_cast<int>(Label::Overflow::SHRINK) : _overflowLabel);
        button->setLabelWordWrap(_wordWrapLabel);
    }
}

ButtonLoader::ButtonLoader()
    :_zoomOnClick(1.0f)
    ,_normalLabelColor(Color3B::WHITE)
    ,_normalBackgroundColor(Color3B::WHITE)
    ,_normalLabelOpacity(255)
    ,_normalBackgroundOpacity(255)
    ,_selectedLabelColor(Color3B::WHITE)
    ,_selectedBackgroundColor(Color3B::WHITE)
    ,_selectedLabelOpacity(255)
    ,_selectedBackgroundOpacity(255)
    ,_disabledLabelColor(Color3B::WHITE)
    ,_disabledBackgroundColor(Color3B::WHITE)
    ,_disabledLabelOpacity(255)
    ,_disabledBackgroundOpacity(255)
    ,_textHAlignment(TextHAlignment::LEFT)
    ,_textVAlignment(TextVAlignment::TOP)
    ,_leftPadding(FloatScaleDescription{0, 0.0f})
    ,_rightPadding(FloatScaleDescription{0, 0.0f})
    ,_topPadding(FloatScaleDescription{0, 0.0f})
    ,_bottomPadding(FloatScaleDescription{0, 0.0f})
    ,_adjustsFontSizeToFit(false)
    ,_imageScale{0,1.f}
    ,_overflowLabel(static_cast<int>(cocos2d::Label::Overflow::NONE))
    ,_wordWrapLabel(true)
{
    
}

ButtonLoader::~ButtonLoader()
{
    
}

void ButtonLoader::onHandlePropTypeText(const std::string &propertyName, bool isExtraProp, const std::string &value)
{
    if(propertyName == PROPERTY_TITLE) {
        _label = value;
    } else {
        WidgetLoader::onHandlePropTypeText(propertyName, isExtraProp, value);
    }
}
    
void ButtonLoader::onHandlePropTypeFontTTF(const std::string &propertyName, bool isExtraProp, const std::string &value)
{
    if(propertyName == PROPERTY_FONTNAME) {
        _font = value;
    } else {
        WidgetLoader::onHandlePropTypeFontTTF(propertyName, isExtraProp, value);
    }
}
    
void ButtonLoader::onHandlePropTypeOffsets(const std::string &propertyName, bool isExtraProp, const Vec4 &value)
{
    if(propertyName == PROPERTY_MARGIN) {
        _margins = value;
    } else if(propertyName == PROPERTY_OFFSET) {
        _offset = value;
    } else {
        WidgetLoader::onHandlePropTypeOffsets(propertyName, isExtraProp, value);
    }
}

void ButtonLoader::onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value)
{
    if(propertyName == PROPERTY_MARGIN_LEFT) {
        _margins.x = value;
    } else if(propertyName == PROPERTY_MARGIN_TOP) {
        _margins.y = value;
    } else if(propertyName == PROPERTY_MARGIN_RIGHT) {
        _margins.z = value;
    } else if(propertyName == PROPERTY_MARGIN_BOTTOM) {
        _margins.w = value;
    } else if(propertyName == PROPERTY_OFFSET_LEFT) {
        _offset.x = value;
    } else if(propertyName == PROPERTY_OFFSET_TOP) {
        _offset.y = value;
    } else if(propertyName == PROPERTY_OFFSET_RIGHT) {
        _offset.z = value;
    } else if(propertyName == PROPERTY_OFFSET_BOTTOM) {
        _offset.w = value;
    } else if(propertyName == PROPERTY_BACKGROUNDOPACITY_NORMAL) {
        float opacity = value * 255.0f;
        _normalBackgroundOpacity = (opacity<0.0f)?0:((opacity>255.0f)?255:static_cast<GLubyte>(opacity));
    } else if(propertyName == PROPERTY_BACKGROUNDOPACITY_HIGHLIGHTED) {
        float opacity = value * 255.0f;
        _selectedBackgroundOpacity = (opacity<0.0f)?0:((opacity>255.0f)?255:static_cast<GLubyte>(opacity));
    } else if(propertyName == PROPERTY_BACKGROUNDOPACITY_DISABLED) {
        float opacity = value * 255.0f;
        _disabledBackgroundOpacity = (opacity<0.0f)?0:((opacity>255.0f)?255:static_cast<GLubyte>(opacity));
    } else if(propertyName == PROPERTY_LABELOPACITY_NORMAL) {
        float opacity = value * 255.0f;
        _normalLabelOpacity = (opacity<0.0f)?0:((opacity>255.0f)?255:static_cast<GLubyte>(opacity));
    } else if(propertyName == PROPERTY_LABELOPACITY_HIGHLIGHTED) {
        float opacity = value * 255.0f;
        _selectedLabelOpacity = (opacity<0.0f)?0:((opacity>255.0f)?255:static_cast<GLubyte>(opacity));
    } else if(propertyName == PROPERTY_LABELOPACITY_DISABLED) {
        float opacity = value * 255.0f;
        _disabledLabelOpacity = (opacity<0.0f)?0:((opacity>255.0f)?255:static_cast<GLubyte>(opacity));
    } else if(propertyName == PROPERTY_ZOOMONCLICK) {
        _zoomOnClick = value;
    } else {
        WidgetLoader::onHandlePropTypeFloat(propertyName, isExtraProp, value);
    }
}

void ButtonLoader::onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value)
{
    if(propertyName == PROPERTY_FONTSIZE) {
        _fontSize = value;
    } else if(propertyName == PROPERTY_HORIZONTALPADDING) {
        _leftPadding = value;
        _rightPadding = value;
    } else if(propertyName == PROPERTY_VERTICALPADDING) {
        _topPadding = value;
        _bottomPadding = value;
    } else  if(propertyName == PROPERTY_LEFTPADDING) {
        _leftPadding = value;
    } else if(propertyName == PROPERTY_TOPPADDING) {
        _topPadding = value;
    } else  if(propertyName == PROPERTY_RIGHTPADDING) {
        _rightPadding = value;
    } else if(propertyName == PROPERTY_BOTTOMPADDING) {
        _bottomPadding = value;
    } else if(propertyName == PROPERTY_OUTLINEWIDTH) {
        //_outlineWidth = pFloatScale;
    } else if(propertyName == PROPERTY_SHADOWBLURRADIUS) {
        //_shadowBlurRadius = pFloatScale;
    } else if(propertyName == PROPERTY_IMAGE_SCALE) {
        _imageScale = value;
    } else {
        WidgetLoader::onHandlePropTypeFloatScale(propertyName, isExtraProp, value);
    }
}

void ButtonLoader::onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value)
{
    if(propertyName == PROPERTY_PREFERREDSIZE) {
        //WidgetLoader::onHandlePropTypeSize(PROPERTY_CONTENTSIZE, isExtraProp, value);
    } else if(propertyName == PROPERTY_MAXSIZE) {
        //((ButtonControl *)pNode)->setMaxSize(pSize);
    } else {
        WidgetLoader::onHandlePropTypeSize(propertyName, isExtraProp, value);
    }
}

void ButtonLoader::onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value)
{
    if(propertyName == PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL) {
        _normalSpriteFrame = value;
    } else if(propertyName == PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED) {
        _selectedSpriteFrame = value;
    } else if(propertyName == PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED) {
        _disabledSpriteFrame = value;
    } else {
        WidgetLoader::onHandlePropTypeSpriteFrame(propertyName, isExtraProp, value);
    }
}

void ButtonLoader::onHandlePropTypeColor3(const std::string &propertyName, bool isExtraProp, const Color3B &value)
{
    if(propertyName == PROPERTY_TITLECOLOR_NORMAL) {
        _normalLabelColor = value;
    } else if(propertyName == PROPERTY_TITLECOLOR_HIGHLIGHTED) {
        _selectedLabelColor = value;
    } else if(propertyName == PROPERTY_TITLECOLOR_DISABLED) {
        _disabledLabelColor = value;
    } else if(propertyName == PROPERTY_BACKGROUNDCOLOR_NORMAL) {
        _normalBackgroundColor = value;
    } else if(propertyName == PROPERTY_BACKGROUNDCOLOR_HIGHLIGHTED) {
        _selectedBackgroundColor = value;
    } else if(propertyName == PROPERTY_BACKGROUNDCOLOR_DISABLED) {
       _disabledBackgroundColor = value;
    } else {
        WidgetLoader::onHandlePropTypeColor3(propertyName, isExtraProp, value);
    }
}

void ButtonLoader::onHandlePropTypeColor4(const std::string &propertyName, bool isExtraProp, const Color4B &value)
{
    if(propertyName == PROPERTY_FONTCOLOR){
        //((ButtonControl *)pNode)->getLabel()->setTextColor(pColor4B);
    } else if(propertyName == PROPERTY_OUTLINECOLOR){
        //_outlineColor = pColor4B;
    } else if(propertyName == PROPERTY_SHADOWCOLOR){
        //_shadowColor = pColor4B;
    } else {
        WidgetLoader::onHandlePropTypeColor4(propertyName, isExtraProp, value);
    }
}

void ButtonLoader::onHandlePropTypePosition(const std::string &propertyName, bool isExtraProp, const PositionDescription &value)
{
    if(propertyName == PROPERTY_SHADOWOFFSET) {
        //_shadowOffset = pPosition;
    } else {
        WidgetLoader::onHandlePropTypePosition(propertyName, isExtraProp, value);
    }
}

void ButtonLoader::onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_HORIZONTALALIGMENT){
        _textHAlignment = static_cast<TextHAlignment>(value);
    } else if(propertyName == PROPERTY_VERTICALALIGMENT) {
        _textVAlignment = static_cast<TextVAlignment>(value);
    }else if (propertyName == PROPERTY_OVERFLOW) {
        _overflowLabel = value;
    }else if (propertyName == PROPERTY_WORDWRAP) {
        _wordWrapLabel = static_cast<bool>(value);
    } else {
        WidgetLoader::onHandlePropTypeIntegerLabeled(propertyName, isExtraProp, value);
    }
}
    
void ButtonLoader::onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value)
{
    if(propertyName == PROPERTY_ADJUSTS_FONT_SIZE_TO_FIT){
        _adjustsFontSizeToFit = value;
    } else {
        WidgetLoader::onHandlePropTypeCheck(propertyName, isExtraProp, value);
    }
}

}

NS_CC_END