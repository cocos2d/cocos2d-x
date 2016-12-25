#include "CCBXScale9SpriteLoader.h"
#include "ui/UIScale9Sprite.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_SPRITEFRAME("spriteFrame");
static const std::string PROPERTY_BLENDFUNC("blendFunc");
    
static const std::string PROPERTY_MARGIN("margin");
static const std::string PROPERTY_MARGIN_LEFT("marginLeft");
static const std::string PROPERTY_MARGIN_TOP("marginTop");
static const std::string PROPERTY_MARGIN_RIGHT("marginRight");
static const std::string PROPERTY_MARGIN_BOTTOM("marginBottom");
    
static const std::string PROPERTY_RENDERING_TYPE("renderingType");

Scale9SpriteLoader *Scale9SpriteLoader::create()
{
    Scale9SpriteLoader *ret = new Scale9SpriteLoader();
    ret->autorelease();
    return ret;
}

Node *Scale9SpriteLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    ui::Scale9Sprite *sprite = _spriteFrame.spriteFrame?ui::Scale9Sprite::createWithSpriteFrame(_spriteFrame.spriteFrame.get()):ui::Scale9Sprite::create();
    sprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    return sprite;
}

void Scale9SpriteLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    ui::Scale9Sprite *sprite = static_cast<ui::Scale9Sprite*>(node);
    Rect margin(_margins.x,_margins.y,1.0-_margins.z-_margins.x,1.0-_margins.w-_margins.y);
    Size size = sprite->getOriginalSize();
    sprite->setCapInsets(Rect(margin.origin.x*size.width,margin.origin.y*size.height,margin.size.width*size.width,margin.size.height*size.height));
    switch (static_cast<ui::Scale9Sprite::RenderingType>(_renderingType)) {
        case ui::Scale9Sprite::RenderingType::SIMPLE:
            sprite->setRenderingType(ui::Scale9Sprite::RenderingType::SIMPLE);
            break;
            
        case ui::Scale9Sprite::RenderingType::TILED:
            sprite->setRenderingType(ui::Scale9Sprite::RenderingType::TILED);
            break;
            
        case ui::Scale9Sprite::RenderingType::SLICE:
            sprite->setRenderingType(_margins == Vec4::ZERO?ui::Scale9Sprite::RenderingType::SIMPLE:ui::Scale9Sprite::RenderingType::SLICE);
            break;
    }
    sprite->setBlendFunc(_blendFunc);
}

Scale9SpriteLoader::Scale9SpriteLoader()
    :_blendFunc(BlendFunc::ALPHA_PREMULTIPLIED)
    ,_renderingType(1)
{
    
}
Scale9SpriteLoader::~Scale9SpriteLoader(){
    
}
    
void Scale9SpriteLoader::onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value) {
    if(propertyName == PROPERTY_BLENDFUNC) {
        _blendFunc = value;
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(propertyName, isExtraProp, value);
    }
}
    
void Scale9SpriteLoader::onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value)
{
    if(propertyName == PROPERTY_SPRITEFRAME) {
        _spriteFrame = value;
    } else {
        NodeLoader::onHandlePropTypeSpriteFrame(propertyName, isExtraProp, value);
    }
}
    
void Scale9SpriteLoader::onHandlePropTypeOffsets(const std::string &propertyName, bool isExtraProp, const Vec4 &value)
{
    if(propertyName == PROPERTY_MARGIN) {
        _margins = value;
    } else {
        NodeLoader::onHandlePropTypeOffsets(propertyName, isExtraProp, value);
    }
}

void Scale9SpriteLoader::onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value)
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
        NodeLoader::onHandlePropTypeFloat(propertyName, isExtraProp, value);
    }
}

void Scale9SpriteLoader::onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_RENDERING_TYPE) {
        _renderingType = value;
    } else {
        NodeLoader::onHandlePropTypeFloat(propertyName, isExtraProp, value);
    }

}
    
}

NS_CC_END
