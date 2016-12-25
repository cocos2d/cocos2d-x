#include "CCBXSpriteLoader.h"
#include "2d/CCSprite.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_SPRITEFRAME("spriteFrame");
static const std::string PROPERTY_BLENDFUNC("blendFunc");
static const std::string PROPERTY_FLIP("flip");

SpriteLoader *SpriteLoader::create()
{
    SpriteLoader *ret = new SpriteLoader();
    ret->autorelease();
    return ret;
}

Node *SpriteLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    Sprite *sprite = Sprite::create();
    sprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    return sprite;
}

void SpriteLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    Sprite *sprite = static_cast<Sprite*>(node);
    if(_spriteFrame.spriteFrame)
        sprite->setSpriteFrame(_spriteFrame.spriteFrame);
    sprite->setBlendFunc(_blendFunc);
    sprite->setFlippedX(_flipped.first);
    sprite->setFlippedY(_flipped.second);
}

SpriteLoader::SpriteLoader():_flipped(false, false), _blendFunc(BlendFunc::ALPHA_PREMULTIPLIED)
{
    
}
SpriteLoader::~SpriteLoader(){
    
}
    
void SpriteLoader::onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value) {
    if(propertyName == PROPERTY_BLENDFUNC) {
        _blendFunc = value;
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(propertyName, isExtraProp, value);
    }
}
    
void SpriteLoader::onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value)
{
    if(propertyName == PROPERTY_SPRITEFRAME) {
        _spriteFrame = value;
    } else {
        NodeLoader::onHandlePropTypeSpriteFrame(propertyName, isExtraProp, value);
    }
}
    
void SpriteLoader::onHandlePropTypeFlip(const std::string &propertyName, bool isExtraProp, const std::pair<bool,bool> &value)
{
    if(propertyName == PROPERTY_FLIP) {
        _flipped = value;
    } else {
        NodeLoader::onHandlePropTypeFlip(propertyName, isExtraProp, value);
    }
}

}

NS_CC_END
