#include "CCBXNodeColorLoader.h"
#include "2d/CCLayer.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_BLENDFUNC("blendFunc");
    
NodeColorLoader *NodeColorLoader::create()
{
    NodeColorLoader *ret = new NodeColorLoader();
    ret->autorelease();
    return ret;
}

Node *NodeColorLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    LayerColor *layer = LayerColor::create();
    layer->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
    layer->ignoreAnchorPointForPosition(false);
    layer->setOpacity(255);
    layer->setColor(Color3B::WHITE);
    return layer;
}

void NodeColorLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    LayerColor *layerColor = static_cast<LayerColor*>(node);
    layerColor->setBlendFunc(_blendFunc);
}

NodeColorLoader::NodeColorLoader()
        :_blendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED)
{
    
}
NodeColorLoader::~NodeColorLoader(){
    
}
    

void NodeColorLoader::onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value) {
    if(propertyName == PROPERTY_BLENDFUNC) {
        _blendFunc = value;
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(propertyName, isExtraProp, value);
    }
}

}

NS_CC_END