#include "CCBXSclorllBarLoader.h"
#include "ui/UIScrollBar.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_SPACING("spacing");
static const std::string PROPERTY_DIRECTION("direction");
static const std::string PROPERTY_BACKGROUND_OLD("backgroundSpriteFrame|Normal");
static const std::string PROPERTY_BACKGROUND("backgroundSpriteFrame");
//static const std::string PROPERTY_PROGRESS("progressSpriteFrame");
static const std::string PROPERTY_HANDLE_NORMAL("handleSpriteFrame|Normal");
static const std::string PROPERTY_HANDLE_HIGHLIGHTED("handleSpriteFrame|Highlighted");
static const std::string PROPERTY_HANDLE_DISABLED("handleSpriteFrame|Disabled");
static const std::string PROPERTY_HANDLE_MOUSEOVER("handleSpriteFrame|MouseOver");
    
static const std::string PROPERTY_MARGIN("margin");
static const std::string PROPERTY_MARGIN_LEFT("marginLeft");
static const std::string PROPERTY_MARGIN_TOP("marginTop");
static const std::string PROPERTY_MARGIN_RIGHT("marginRight");
static const std::string PROPERTY_MARGIN_BOTTOM("marginBottom");
    
static const std::string PROPERTY_ZOOM_SCALE("zoomScale");
static const std::string PROPERTY_MAX_PERCENT("maxPercent");
static const std::string PROPERTY_SLIDER_VALUE("percent");
    
static const std::string PROPERTY_IMAGE_SCALE("imageScale");
static const std::string PROPERTY_IS_VERTICAL("vertical");
    
static const std::string PROPERTY_HANDLE_MARGIN("handleMargin");
    
ScrollBarLoader *ScrollBarLoader::create()
{
    ScrollBarLoader *ret = new ScrollBarLoader();
    ret->autorelease();
    return ret;
}
Node *ScrollBarLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    ui::ScrollBar *slider = ui::ScrollBar::create();
    slider->setAnchorPoint(Vec2(0.0f, 0.0f));
    return slider;

}
void ScrollBarLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    WidgetLoader::setSpecialProperties(node, parentSize, mainScale, additionalScale, owner, rootNode, rootOwner);
    ui::ScrollBar *slider = static_cast<ui::ScrollBar*>(node);
    slider->setBarType(_isVertical?cocos2d::ui::ScrollBar::BarType::kVertical:cocos2d::ui::ScrollBar::BarType::kHorizontal);
    Rect margin(_margins.x,_margins.y,1.0-_margins.z-_margins.x,1.0-_margins.w-_margins.y);
    Rect handleMargin(_handleMargins.x, _handleMargins.y, 1.0-_handleMargins.z-_handleMargins.x, 1.0-_handleMargins.w-_handleMargins.y);
    
    switch(_background.type)
    {
        case SpriteFrameDescription::TextureResType::LOCAL:
        {
            Size size = _background.spriteFrame->getOriginalSize();
            Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
            slider->loadBarTexture(_background.path, ui::Widget::TextureResType::LOCAL);
            slider->setCapInsetsBarRenderer(realMargins);
            slider->setScale9Enabled(!realMargins.size.equals(size) || realMargins.origin != Vec2::ZERO);
        }
            break;
        case SpriteFrameDescription::TextureResType::PLIST:
        {
            Size size = _background.spriteFrame->getOriginalSize();
            Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
            slider->loadBarTexture(_background.path, ui::Widget::TextureResType::PLIST);
            slider->setCapInsetsBarRenderer(realMargins);
            slider->setScale9Enabled(!realMargins.size.equals(size) || realMargins.origin != Vec2::ZERO);
        }
            break;
        default:
            break;
    };
//    switch(_progress.type)
//    {
//        case SpriteFrameDescription::TextureResType::LOCAL:
//        {
//            Size size = _progress.spriteFrame->getOriginalSize();
//            Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
//            //slider->loadProgressBarTexture(_progress.path, ui::Widget::TextureResType::LOCAL);
//            //slider->setCapInsetProgressBarRenderer(realMargins);
//            slider->setScale9Enabled(!realMargins.size.equals(size) || realMargins.origin != Vec2::ZERO);
//        }
//            break;
//        case SpriteFrameDescription::TextureResType::PLIST:
//        {
//            Size size = _progress.spriteFrame->getOriginalSize();
//            Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
//            //slider->loadProgressBarTexture(_progress.path, ui::Widget::TextureResType::PLIST);
//            //slider->setCapInsetProgressBarRenderer(realMargins);
//            slider->setScale9Enabled(!realMargins.size.equals(size) || realMargins.origin != Vec2::ZERO);
//        }
//            break;
//        default:
//            break;
//    };
    
    Rect realMargins;
    switch(_handleNormal.type)
    {
        case SpriteFrameDescription::TextureResType::LOCAL:
        {
            //slider->loadSlidBallTextureNormal(_handleNormal.path, ui::Widget::TextureResType::LOCAL);
            
            Size size = _handleNormal.spriteFrame->getOriginalSize();
            realMargins = {handleMargin.origin.x*size.width,handleMargin.origin.y*size.height,handleMargin.size.width*size.width,handleMargin.size.height*size.height};
            slider->loadSlidBallTextureNormal(_handleNormal.path, ui::Widget::TextureResType::LOCAL);
            //slider->setCapInsetsForBallRendereds(realMargins);
        }
            break;
        case SpriteFrameDescription::TextureResType::PLIST:
        {
            //slider->loadSlidBallTextureNormal(_handleNormal.path, ui::Widget::TextureResType::PLIST);
            
            Size size = _handleNormal.spriteFrame->getOriginalSize();
            realMargins = {handleMargin.origin.x*size.width,handleMargin.origin.y*size.height,handleMargin.size.width*size.width,handleMargin.size.height*size.height};
            slider->loadSlidBallTextureNormal(_handleNormal.path, ui::Widget::TextureResType::PLIST);
            //slider->setCapInsetsForBallRendereds(realMargins);
        }
            break;
        default:
            break;
    };
    switch(_handleDisabled.type)
    {
        case SpriteFrameDescription::TextureResType::LOCAL:
        {
            slider->loadSlidBallTextureDisabled(_handleDisabled.path, ui::Widget::TextureResType::LOCAL);
        }
            break;
        case SpriteFrameDescription::TextureResType::PLIST:
        {
            slider->loadSlidBallTextureDisabled(_handleDisabled.path, ui::Widget::TextureResType::PLIST);
        }
            break;
        default:
            break;
    };
    switch(_handleHiglihted.type)
    {
        case SpriteFrameDescription::TextureResType::LOCAL:
        {
            slider->loadSlidBallTexturePressed(_handleHiglihted.path, ui::Widget::TextureResType::LOCAL);
        }
            break;
        case SpriteFrameDescription::TextureResType::PLIST:
        {
            slider->loadSlidBallTexturePressed(_handleHiglihted.path, ui::Widget::TextureResType::PLIST);
        }
            break;
        default:
            break;
    };
    switch(_handleMouseOver.type)
    {
        case SpriteFrameDescription::TextureResType::LOCAL:
        {
            slider->loadSlidBallTextureMouseOver(_handleMouseOver.path, ui::Widget::TextureResType::LOCAL);
        }
            break;
        case SpriteFrameDescription::TextureResType::PLIST:
        {
            slider->loadSlidBallTextureMouseOver(_handleMouseOver.path, ui::Widget::TextureResType::PLIST);
        }
            break;
        default:
            break;
    };
    slider->setCapInsetsForBallRendereds(realMargins);
    slider->setPercent(_percent);
    slider->setZoomScale(_zoomScale - 1.0f);
    slider->setImageScale(getAbsoluteScale(mainScale, additionalScale, _imageScale.scale, _imageScale.type) / CCBXReader::getResolutionScale());
    //WidgetLoader::setSpecialProperties(node, parentSize, mainScale, additionalScale);
    //ui::ScrollBar *slider = dynamic_cast<ui::ScrollBar*>(node);
}

ScrollBarLoader::ScrollBarLoader()
    :_zoomScale(1.0f)
    ,_maxPercent(100)
    ,_percent(0.f)
    ,_imageScale{0,1.f}
    ,_isVertical(false)
{
    
}

ScrollBarLoader::~ScrollBarLoader()
{
    
}
    
void ScrollBarLoader::onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value)
{
    if(propertyName == PROPERTY_BACKGROUND || propertyName == PROPERTY_BACKGROUND_OLD) {
        _background = value;
    } /*else if(propertyName == PROPERTY_PROGRESS) {
        _progress = value;
    }*/ else if(propertyName == PROPERTY_HANDLE_NORMAL) {
        _handleNormal = value;
    } else if(propertyName == PROPERTY_HANDLE_HIGHLIGHTED) {
        _handleHiglihted = value;
    } else if(propertyName == PROPERTY_HANDLE_DISABLED) {
        _handleDisabled = value;
    } else if(propertyName == PROPERTY_HANDLE_MOUSEOVER) {
        _handleMouseOver = value;
    } else {
        WidgetLoader::onHandlePropTypeSpriteFrame(propertyName, isExtraProp, value);
    }
}
    
void ScrollBarLoader::onHandlePropTypeOffsets(const std::string &propertyName, bool isExtraProp, const Vec4 &value)
{
    if(propertyName == PROPERTY_MARGIN) {
        _margins = value;
    }
    else if (PROPERTY_HANDLE_MARGIN == propertyName) {
        _handleMargins = value;
    }
    else {
        NodeLoader::onHandlePropTypeOffsets(propertyName, isExtraProp, value);
    }
}
    
void ScrollBarLoader::onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value)
{
    if(propertyName == PROPERTY_IS_VERTICAL) {
        _isVertical = value;
    } else {
        WidgetLoader::onHandlePropTypeCheck(propertyName, isExtraProp, value);
    }
}
    
void ScrollBarLoader::onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value)
{
    if(propertyName == PROPERTY_MARGIN_LEFT) {
        _margins.x = value;
    } else if(propertyName == PROPERTY_MARGIN_TOP) {
        _margins.y = value;
    } else if(propertyName == PROPERTY_MARGIN_RIGHT) {
        _margins.z = value;
    } else if(propertyName == PROPERTY_MARGIN_BOTTOM) {
        _margins.w = value;
    } else if(propertyName == PROPERTY_ZOOM_SCALE) {
        _zoomScale = value;
    } else if(propertyName == PROPERTY_SLIDER_VALUE) {
        _percent = value;
    } else{
        WidgetLoader::onHandlePropTypeFloat(propertyName, isExtraProp, value);
    }
}
    
void ScrollBarLoader::onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value)
{
    if(propertyName == PROPERTY_IMAGE_SCALE) {
        _imageScale = value;
    } else {
        WidgetLoader::onHandlePropTypeFloatScale(propertyName, isExtraProp, value);
    }
}
    
void ScrollBarLoader::onHandlePropTypeInteger(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_MAX_PERCENT) {
        _maxPercent = value;
    } //else if(propertyName == PROPERTY_SLIDER_VALUE) {
      //  _percent = value;
    //}
    else{
        WidgetLoader::onHandlePropTypeInteger(propertyName, isExtraProp, value);
    }
}
    
void ScrollBarLoader::onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_DIRECTION) {
        //((LayoutBox *)pNode)->setDirection(static_cast<cocos2d::LayoutBoxDirection>(pIntegerLabeled));
    } else {
        WidgetLoader::onHandlePropTypeIntegerLabeled(propertyName, isExtraProp, value);
    }
}

}

NS_CC_END
