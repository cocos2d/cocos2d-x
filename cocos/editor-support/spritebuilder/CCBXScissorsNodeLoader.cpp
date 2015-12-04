#include "CCBXScissorsNodeLoader.h"
#include "ui/UILayout.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_SPACING("spacing");
static const std::string PROPERTY_DIRECTION("direction");
    
    
ScissorsNodeLoader *ScissorsNodeLoader::create()
{
    ScissorsNodeLoader *ret = new ScissorsNodeLoader();
    ret->autorelease();
    return ret;
}
Node *ScissorsNodeLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    ui::Layout *layout = ui::Layout::create();
    layout->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
    return layout;
}
void ScissorsNodeLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    WidgetLoader::setSpecialProperties(node, parentSize, mainScale, additionalScale, owner, rootNode, rootOwner);
    ui::Layout *layout = dynamic_cast<ui::Layout*>(node);
    layout->setClippingType(ui::Layout::ClippingType::SCISSOR);
    layout->setClippingEnabled(true);
}

ScissorsNodeLoader::ScissorsNodeLoader()
{
    
}

ScissorsNodeLoader::~ScissorsNodeLoader()
{
    
}

}

NS_CC_END