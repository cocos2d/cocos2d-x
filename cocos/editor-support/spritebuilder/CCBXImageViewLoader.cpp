#include "CCBXImageViewLoader.h"
#include "ui/UIScale9Sprite.h"
#include "ui/UIImageView.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_SPRITEFRAME("spriteFrame");
static const std::string PROPERTY_BLENDFUNC("blendFunc");
    
static const std::string PROPERTY_MARGIN("margin");
static const std::string PROPERTY_MARGIN_LEFT("marginLeft");
static const std::string PROPERTY_MARGIN_TOP("marginTop");
static const std::string PROPERTY_MARGIN_RIGHT("marginRight");
static const std::string PROPERTY_MARGIN_BOTTOM("marginBottom");
static const std::string PROPERTY_IMAGE_SCALE("imageScale");

ImageViewLoader *ImageViewLoader::create()
{
    ImageViewLoader *ret = new ImageViewLoader();
    ret->autorelease();
    return ret;
}

Node *ImageViewLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    Rect margin(_margins.x,_margins.y,1.0-_margins.z-_margins.x,1.0-_margins.w-_margins.y);
    
    ui::ImageView *imageView = ui::ImageView::create();
    imageView->ignoreContentAdaptWithSize(false);
    imageView->setAnchorPoint(Vec2(0.0f, 0.0f));
    switch(_spriteFrame.type)
    {
        case SpriteFrameDescription::TextureResType::LOCAL:
            {
                Size size = _spriteFrame.spriteFrame->getOriginalSize();
                Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
                imageView->loadTexture(_spriteFrame.path, ui::Widget::TextureResType::LOCAL);
                imageView->setScale9Enabled(_margins != Vec4::ZERO);
                imageView->setCapInsets(realMargins);
                imageView->ignoreContentAdaptWithSize(false);
            }
            break;
        case SpriteFrameDescription::TextureResType::PLIST:
            {
                Size size = _spriteFrame.spriteFrame->getOriginalSize();
                Rect realMargins(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height);
                imageView->loadTexture(_spriteFrame.path, ui::Widget::TextureResType::PLIST);
                imageView->setScale9Enabled(_margins != Vec4::ZERO);
                imageView->setCapInsets(realMargins);
                imageView->ignoreContentAdaptWithSize(false);
            }
            break;
        default:
            break;
    };
    imageView->setImageScale(getAbsoluteScale(mainScale, additionalScale, _imageScale.scale, _imageScale.type) / CCBXReader::getResolutionScale());
    return imageView;
}

void ImageViewLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
}

ImageViewLoader::ImageViewLoader()
    :_imageScale{0,1.f}
{
    
}
ImageViewLoader::~ImageViewLoader(){
    
}
    
void ImageViewLoader::onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value) {
    if(propertyName == PROPERTY_BLENDFUNC) {
        //((LayerColor *)pNode)->setBlendFunc(pBlendFunc);
    } else {
        WidgetLoader::onHandlePropTypeBlendFunc(propertyName, isExtraProp, value);
    }
}
    
void ImageViewLoader::onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value)
{
    if(propertyName == PROPERTY_SPRITEFRAME) {
        _spriteFrame = value;
    } else {
        WidgetLoader::onHandlePropTypeSpriteFrame(propertyName, isExtraProp, value);
    }
}
    
void ImageViewLoader::onHandlePropTypeOffsets(const std::string &propertyName, bool isExtraProp, const Vec4 &value)
{
    if(propertyName == PROPERTY_MARGIN) {
        _margins = value;
    } else {
        NodeLoader::onHandlePropTypeOffsets(propertyName, isExtraProp, value);
    }
}
    
void ImageViewLoader::onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value)
{
    if(propertyName == PROPERTY_MARGIN_LEFT) {
        _margins.x = value;
    } else if(propertyName == PROPERTY_MARGIN_TOP) {
        _margins.y = value;
    } else if(propertyName == PROPERTY_MARGIN_RIGHT) {
        _margins.z = value;
    } else if(propertyName == PROPERTY_MARGIN_BOTTOM) {
        _margins.w = value;
    } else {
        WidgetLoader::onHandlePropTypeFloat(propertyName, isExtraProp, value);
    }
}
    
void ImageViewLoader::onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value)
{
    if(propertyName == PROPERTY_IMAGE_SCALE) {
        _imageScale = value;
    } else {
        WidgetLoader::onHandlePropTypeFloatScale(propertyName, isExtraProp, value);
    }
}

}

NS_CC_END
