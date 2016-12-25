#include "CCBXScrollViewLoader.h"
#include "ui/UIScrollView.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_DIRECTION("direction");
static const std::string PROPERTY_BOUNCES("bounces");
static const std::string PROPERTY_CONTENTNODE("contentNode");
static const std::string PROPERTY_VERTICALSCROLLENABLED("verticalScrollEnabled");
static const std::string PROPERTY_HORIZONTALSCROLLENABLED("horizontalScrollEnabled");
static const std::string PROPERTY_PAGINGENABLED("pagingEnabled");
static const std::string PROPERTY_CLIPCONTENT("clipContent");
static const std::string PROPERTY_INERTIAL_SCROLL("inertialScroll");
static const std::string PROPERTY_SCROLL_BAR_ENABLED("scrollBarEnabled");
static const std::string PROPERTY_SCROLL_BAR_WIDTH("scrollBarWidth");
static const std::string PROPERTY_SCROLL_BAR_AUTOHIDE_ENABLED("scrollBarAutoHideEnabled");
static const std::string PROPERTY_SCROLL_BAR_HIDE_IF_SIZE_FIT("scrollHideIfSizeFit");
static const std::string PROPERTY_SCROLL_BAR_POSITION_FROM_CORNER("scrollBarPositionFromCorner");
static const std::string PROPERTY_SCROLL_BAR_COLOR("scrollBarColor");
static const std::string PROPERTY_SCROLL_BAR_OPACITY("scrollBarOpacity");
    
ScrollViewLoader *ScrollViewLoader::create()
{
    ScrollViewLoader *ret = new ScrollViewLoader();
    ret->autorelease();
    return ret;
}

Node *ScrollViewLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    ui::ScrollView *scrollView = ui::ScrollView::create();
    scrollView->setAnchorPoint(Vec2(0.0f, 0.0f));
    scrollView->setClippingType(ui::Layout::ClippingType::SCISSOR);
    return scrollView;
}

void ScrollViewLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    WidgetLoader::setSpecialProperties(node, parentSize, mainScale, additionalScale, owner, rootNode, rootOwner);
    ui::ScrollView *scrollView = static_cast<ui::ScrollView*>(node);
    ui::ScrollView::Direction direction = ui::ScrollView::Direction::NONE;
    if(_horizontalScrollEnabled && _verticalScrollEnabled)
        direction = ui::ScrollView::Direction::BOTH;
    else if(_horizontalScrollEnabled)
        direction = ui::ScrollView::Direction::HORIZONTAL;
    else if(_verticalScrollEnabled)
        direction = ui::ScrollView::Direction::VERTICAL;
    scrollView->setBounceEnabled(_bounce);
    scrollView->setClippingEnabled(_clipping);
    scrollView->setDirection(direction);
    if(_file)
    {
        Node *childNode = _file->createNode(scrollView->getContentSize(), mainScale, additionalScale, owner);
        scrollView->setInnerContainerSize(childNode->getContentSize());
        scrollView->getInnerContainer()->addChild(childNode);
        scrollView->setEnabled(true);
    }
    scrollView->setInertiaScrollEnabled(_inertial);
    scrollView->setScrollBarEnabled(_scrollBar);
    
    if(_scrollBar)
    {
        scrollView->setScrollBarWidth(getAbsoluteScale(mainScale, additionalScale, _scrollBarWidth.scale, _scrollBarWidth.type));
        scrollView->setScrollBarAutoHideEnabled(_scrollBarAutoHideEnabled);
        scrollView->setScrollBarPositionFromCorner(getAbsolutePosition(mainScale, additionalScale, _scrollBarPositionFromCorner.pos, _scrollBarPositionFromCorner.referenceCorner, _scrollBarPositionFromCorner.xUnits , _scrollBarPositionFromCorner.yUnits, parentSize));
        scrollView->setScrollBarColor(_scrollBarColor);
        scrollView->setScrollBarOpacity(_scrollBarOpacity);
        scrollView->setScrollBarHideIfSizeFit(_scrollHideIfSizeFit);
    }
}

ScrollViewLoader::ScrollViewLoader()
    :_clipping(true)
    ,_bounce(false)
    ,_file(nullptr)
    ,_verticalScrollEnabled(true)
    ,_horizontalScrollEnabled(true)
    ,_inertial(true)
    ,_scrollBar(false)
    ,_scrollBarWidth{2,12}
    ,_scrollBarAutoHideEnabled(true)
    ,_scrollHideIfSizeFit(true)
    ,_scrollBarPositionFromCorner{PositionReferenceCorner::BOTTOMLEFT, PositionUnit::UIPOINTS, PositionUnit::UIPOINTS, Vec2(20, 20)}
    ,_scrollBarColor(52, 65, 87)
    ,_scrollBarOpacity(static_cast<GLubyte>(255 * 0.4f))
{
    
}
    
ScrollViewLoader::~ScrollViewLoader()
{
    CC_SAFE_RELEASE(_file);
}
    
void ScrollViewLoader::onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value)
{
    WidgetLoader::onHandlePropTypeSize(propertyName, isExtraProp, value);
}

void ScrollViewLoader::onHandlePropTypeCCBFile(const std::string &propertyName, bool isExtraProp, const std::pair<std::string, NodeLoader*> &value)
{
    if(propertyName == PROPERTY_CONTENTNODE) {
        _filePath = value.first;
        _file = value.second;
    } else {
        WidgetLoader::onHandlePropTypeCCBFile(propertyName, isExtraProp, value);
    }
}
    
void ScrollViewLoader::onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value)
{
    if(propertyName == PROPERTY_SCROLL_BAR_WIDTH) {
        _scrollBarWidth = value;
    } else {
        NodeLoader::onHandlePropTypeFloatScale(propertyName, isExtraProp, value);
    }
}
void ScrollViewLoader::onHandlePropTypeColor3(const std::string &propertyName, bool isExtraProp, const Color3B &value)
{
    if(propertyName == PROPERTY_SCROLL_BAR_COLOR) {
        _scrollBarColor = value;
    } else {
        NodeLoader::onHandlePropTypeColor3(propertyName, isExtraProp, value);
    }
}

void ScrollViewLoader::onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value)
{
    if(propertyName == PROPERTY_SCROLL_BAR_OPACITY) {
        float opacity = value * 255.0f;
        _scrollBarOpacity = (opacity<0.0f)?0:((opacity>255.0f)?255:static_cast<GLubyte>(opacity));
    } else {
        WidgetLoader::onHandlePropTypeFloat(propertyName, isExtraProp, value);
    }
}
    
void ScrollViewLoader::onHandlePropTypePosition(const std::string &propertyName, bool isExtraProp, const PositionDescription &value)
{
    if(propertyName == PROPERTY_SCROLL_BAR_POSITION_FROM_CORNER) {
        _scrollBarPositionFromCorner = value;
    } else {
        WidgetLoader::onHandlePropTypePosition(propertyName, isExtraProp, value);
    }
}
    
void ScrollViewLoader::onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value)
{
    if(propertyName == PROPERTY_CLIPCONTENT) {
        _clipping = value;
    } else if(propertyName == PROPERTY_INERTIAL_SCROLL) {
        _inertial = value;
    } else if(propertyName == PROPERTY_SCROLL_BAR_ENABLED) {
        _scrollBar = value;
    } else if(propertyName == PROPERTY_BOUNCES) {
        _bounce = value;
    } else if(propertyName == PROPERTY_VERTICALSCROLLENABLED) {
        _verticalScrollEnabled = value;
    } else if(propertyName == PROPERTY_HORIZONTALSCROLLENABLED) {
        _horizontalScrollEnabled = value;
    } else if(propertyName == PROPERTY_SCROLL_BAR_AUTOHIDE_ENABLED) {
        _scrollBarAutoHideEnabled = value;
    } else if(propertyName == PROPERTY_SCROLL_BAR_HIDE_IF_SIZE_FIT) {
        _scrollHideIfSizeFit = value;
    } else if(propertyName == PROPERTY_PAGINGENABLED) {
    } else {
        WidgetLoader::onHandlePropTypeCheck(propertyName, isExtraProp, value);
    }
}

}
    
NS_CC_END
