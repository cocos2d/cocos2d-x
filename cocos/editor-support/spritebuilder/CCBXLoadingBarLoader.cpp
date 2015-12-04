#include "CCBXLoadingBarLoader.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_FLIP("flip");
static const std::string PROPERTY_SPRITEFRAME("spriteFrame");
static const std::string PROPERTY_BLENDFUNC("blendFunc");
static const std::string PROPERTY_DIRECTION("direction");
static const std::string PROPERTY_PERCENTAGE("percentage");
    
static const std::string PROPERTY_MARGIN("margin");
static const std::string PROPERTY_MARGIN_LEFT("marginLeft");
static const std::string PROPERTY_MARGIN_TOP("marginTop");
static const std::string PROPERTY_MARGIN_RIGHT("marginRight");
static const std::string PROPERTY_MARGIN_BOTTOM("marginBottom");
    
static const std::string PROPERTY_IMAGE_SCALE("imageScale");
    
LoadingBarLoader *LoadingBarLoader::create()
{
    LoadingBarLoader *ret = new LoadingBarLoader();
    ret->autorelease();
    return ret;
}

Node *LoadingBarLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    Rect margin(_margins.x,_margins.y,1.0-_margins.z-_margins.x,1.0-_margins.w-_margins.y);
    ui::LoadingBar *loadingBar = ui::LoadingBar::create();
    loadingBar->setAnchorPoint(Vec2(0.0f, 0.0f));
    loadingBar->setScale9Enabled(true);
    switch(_spriteFrame.type)
    {
        case SpriteFrameDescription::TextureResType::LOCAL:
            {
                Size size = _spriteFrame.spriteFrame->getOriginalSize();
                Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
                loadingBar->loadTexture(_spriteFrame.path, ui::Widget::TextureResType::LOCAL);
                loadingBar->setCapInsets(realMargins);
            }
            break;
        case SpriteFrameDescription::TextureResType::PLIST:
            {
                Size size = _spriteFrame.spriteFrame->getOriginalSize();
                Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
                loadingBar->loadTexture(_spriteFrame.path, ui::Widget::TextureResType::PLIST);
                loadingBar->setCapInsets(realMargins);
            }
            break;
        default:
            break;
    };
    loadingBar->setImageScale(getAbsoluteScale(mainScale, additionalScale, _imageScale.scale, _imageScale.type) / CCBXReader::getResolutionScale());
    loadingBar->setPercent(_percentage);
    return loadingBar;
}

void LoadingBarLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    WidgetLoader::setSpecialProperties(node, parentSize, mainScale, additionalScale, owner, rootNode, rootOwner);
    ui::LoadingBar *loadingBar = static_cast<ui::LoadingBar*>(node);
    loadingBar->setDirection(_direction);
}
    
LoadingBarLoader::LoadingBarLoader()
    :_direction(ui::LoadingBar::Direction::LEFT)
    ,_percentage(0)
    ,_imageScale{0,1.f}
{
    
}

LoadingBarLoader::~LoadingBarLoader()
{
    
}
    
void LoadingBarLoader::onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value)
{
        
}
    
void LoadingBarLoader::onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value)
{
    if(propertyName == PROPERTY_SPRITEFRAME) {
        _spriteFrame = value;
    } else {
        WidgetLoader::onHandlePropTypeSpriteFrame(propertyName, isExtraProp, value);
    }
}
    
void LoadingBarLoader::onHandlePropTypeFlip(const std::string &propertyName, bool isExtraProp, const std::pair<bool,bool> &value)
{
    if(propertyName == PROPERTY_FLIP) {
        _flipped = value;
    } else {
        WidgetLoader::onHandlePropTypeFlip(propertyName, isExtraProp, value);
    }
}
    
void LoadingBarLoader::onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value)
{
    if (propertyName == PROPERTY_DIRECTION) {
        _direction =  static_cast<ui::LoadingBar::Direction>(value);
    } else {
        WidgetLoader::onHandlePropTypeIntegerLabeled(propertyName, isExtraProp, value);
    }
}
    
void LoadingBarLoader::onHandlePropTypeOffsets(const std::string &propertyName, bool isExtraProp, const Vec4 &value)
{
    if(propertyName == PROPERTY_MARGIN) {
        _margins = value;
    } else {
        NodeLoader::onHandlePropTypeOffsets(propertyName, isExtraProp, value);
    }
}

void LoadingBarLoader::onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value)
{
    if(propertyName == PROPERTY_MARGIN_LEFT) {
        _margins.x = value;
    } else if(propertyName == PROPERTY_MARGIN_TOP) {
        _margins.y = value;
    } else if(propertyName == PROPERTY_MARGIN_RIGHT) {
        _margins.z = value;
    } else if(propertyName == PROPERTY_MARGIN_BOTTOM) {
        _margins.w = value;
    } else if (propertyName == PROPERTY_PERCENTAGE) {
        _percentage = value;
    } else {
        WidgetLoader::onHandlePropTypeFloat(propertyName, isExtraProp, value);
    }
}
    
void LoadingBarLoader::onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value)
{
    if(propertyName == PROPERTY_IMAGE_SCALE) {
        _imageScale = value;
    } else {
        WidgetLoader::onHandlePropTypeFloatScale(propertyName, isExtraProp, value);
    }
}

}

NS_CC_END
