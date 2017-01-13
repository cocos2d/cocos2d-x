#include "CCBXLayoutBoxLoader.h"
#include "ui/UILayout.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_SPACING("spacing");
static const std::string PROPERTY_DIRECTION("direction");
static const std::string PROPERTY_CLIPCONTENT("clipContent");
static const std::string PROPERTY_DIMENSIONS("dimensions");
    
    
LayoutBoxLoader *LayoutBoxLoader::create()
{
    LayoutBoxLoader *ret = new LayoutBoxLoader();
    ret->autorelease();
    return ret;
}
Node *LayoutBoxLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    ui::Layout *layoutBox = ui::Layout::create();
    layoutBox->setAnchorPoint(Vec2(0.0f, 0.0f));
    return layoutBox;
}

void LayoutBoxLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    WidgetLoader::setSpecialProperties(node, parentSize, mainScale, additionalScale, owner, rootNode, rootOwner);
    Size dimensions = getAbsoluteSize(mainScale, additionalScale, _dimensions.size, _dimensions.widthUnits, _dimensions.heightUnits, parentSize);
    ui::Layout *layout = dynamic_cast<ui::Layout*>(node);
    if(layout)
    {
        if(_direction == Horizontal)
            layout->setLayoutType(ui::Layout::Type::HORIZONTAL_AUTO);
        else
            layout->setLayoutType(ui::Layout::Type::VERTICAL_AUTO);
        layout->setSpacing(getAbsoluteScale(mainScale, additionalScale, _spacing.scale, _spacing.type));
    }
    layout->setContentSize(Size(dimensions.width, dimensions.height));
}

LayoutBoxLoader::LayoutBoxLoader()
    :_spacing(FloatScaleDescription{0, 0})
    ,_clipping(false)
    ,_direction(LayoutBoxDirection::Horizontal)
    ,_dimensions(SizeDescription{SizeUnit::POINTS, SizeUnit::POINTS, {0, 0}})
{
    
}

LayoutBoxLoader::~LayoutBoxLoader()
{
    
}
    
void LayoutBoxLoader::onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value)
{
    if(propertyName == PROPERTY_SPACING) {
        _spacing = value;
    } else {
        WidgetLoader::onHandlePropTypeFloatScale(propertyName, isExtraProp, value);
    }

}
void LayoutBoxLoader::onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_DIRECTION) {
        _direction = static_cast<LayoutBoxDirection>(value);
    } else {
        WidgetLoader::onHandlePropTypeIntegerLabeled(propertyName, isExtraProp, value);
    }
}
    
void LayoutBoxLoader::onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value)
{
    if(propertyName == PROPERTY_CLIPCONTENT) {
        _clipping = value;
    } else {
        WidgetLoader::onHandlePropTypeCheck(propertyName, isExtraProp, value);
    }
}

void LayoutBoxLoader::onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value)
{
    if(propertyName == PROPERTY_DIMENSIONS) {
        _dimensions = value;
    } else {
        WidgetLoader::onHandlePropTypeSize(propertyName, isExtraProp, value);
    }
}

}

NS_CC_END
