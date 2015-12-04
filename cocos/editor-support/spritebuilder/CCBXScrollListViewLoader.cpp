#include "CCBXScrollListViewLoader.h"
#include "CCScrollListView.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_DIRECTION("direction");
static const std::string PROPERTY_BOUNCES("bounces");
static const std::string PROPERTY_TEMPLATE("template");
static const std::string PROPERTY_GRAVITY("gravity");
static const std::string PROPERTY_MAGNETIC("magnetic");
static const std::string PROPERTY_CLIPCONTENT("clipContent");
static const std::string PROPERTY_HORIZONRAL("horizontal");
static const std::string PROPERTY_INERTIAL_SCROLL("inertialScroll");
static const std::string PROPERTY_SCROLL_BAR_ENABLED("scrollBarEnabled");
static const std::string PROPERTY_SCROLL_BAR_WIDTH("scrollBarWidth");
static const std::string PROPERTY_SCROLL_BAR_AUTOHIDE_ENABLED("scrollBarAutoHideEnabled");
static const std::string PROPERTY_SCROLL_BAR_HIDE_IF_SIZE_FIT("scrollHideIfSizeFit");
static const std::string PROPERTY_SCROLL_BAR_POSITION_FROM_CORNER("scrollBarPosition");
static const std::string PROPERTY_SCROLL_BAR_COLOR("scrollBarColor");
static const std::string PROPERTY_SCROLL_BAR_OPACITY("scrollBarOpacity");
    
ScrollListViewLoader *ScrollListViewLoader::create()
{
    ScrollListViewLoader *ret = new ScrollListViewLoader();
    ret->autorelease();
    return ret;
}

Node *ScrollListViewLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    ScrollListView *scrollListView = ScrollListView::create(_file, mainScale, additionalScale);
    scrollListView->setAnchorPoint(Vec2(0.0f, 0.0f));
    scrollListView->setClippingType(ui::Layout::ClippingType::SCISSOR);
    return scrollListView;
}

void ScrollListViewLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner)
{
    WidgetLoader::setSpecialProperties(node, parentSize, mainScale, additionalScale, owner, rootNode, rootOwner);
    ScrollListView *scrollView = static_cast<ScrollListView*>(node);
    scrollView->setBounceEnabled(_bounce);
    scrollView->setClippingEnabled(_clipping);
    scrollView->setDirection(_horizontal?ScrollListView::Direction::HORIZONTAL:ScrollListView::Direction::VERTICAL);
    scrollView->setGravity(static_cast<cocos2d::ui::ListView::Gravity>(_gravity));
    scrollView->setMagneticType(static_cast<cocos2d::ui::ListView::MagneticType>(_magnetic));
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

ScrollListViewLoader::ScrollListViewLoader()
    :_horizontal(false)
    ,_clipping(true)
    ,_bounce(false)
    ,_file(nullptr)
    ,_gravity(0)
    ,_magnetic(0)
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
    
ScrollListViewLoader::~ScrollListViewLoader()
{
    CC_SAFE_RELEASE(_file);
}
    
void ScrollListViewLoader::onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value)
{
    WidgetLoader::onHandlePropTypeSize(propertyName, isExtraProp, value);
}

void ScrollListViewLoader::onHandlePropTypeCCBFile(const std::string &propertyName, bool isExtraProp, NodeLoader *value)
{
    if(propertyName == PROPERTY_TEMPLATE) {
        _file = value;
        CC_SAFE_RETAIN(_file);
    } else {
        WidgetLoader::onHandlePropTypeCCBFile(propertyName, isExtraProp, value);
    }
}
    
void ScrollListViewLoader::onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_GRAVITY) {
        _gravity = value;
    } else if(propertyName == PROPERTY_MAGNETIC) {
        _magnetic = value;
    } else {
        WidgetLoader::onHandlePropTypeIntegerLabeled(propertyName, isExtraProp, value);
    }
}
    
void ScrollListViewLoader::onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value)
{
    if(propertyName == PROPERTY_SCROLL_BAR_WIDTH) {
        _scrollBarWidth = value;
    } else {
        NodeLoader::onHandlePropTypeFloatScale(propertyName, isExtraProp, value);
    }
}
void ScrollListViewLoader::onHandlePropTypeColor3(const std::string &propertyName, bool isExtraProp, const Color3B &value)
{
    if(propertyName == PROPERTY_SCROLL_BAR_COLOR) {
        _scrollBarColor = value;
    } else {
        NodeLoader::onHandlePropTypeColor3(propertyName, isExtraProp, value);
    }
}
    
void ScrollListViewLoader::onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value)
{
    if(propertyName == PROPERTY_SCROLL_BAR_OPACITY) {
        float opacity = value * 255.0f;
        _scrollBarOpacity = (opacity<0.0f)?0:((opacity>255.0f)?255:static_cast<GLubyte>(opacity));
    } else {
        WidgetLoader::onHandlePropTypeFloat(propertyName, isExtraProp, value);
    }
}
    
void ScrollListViewLoader::onHandlePropTypePosition(const std::string &propertyName, bool isExtraProp, const PositionDescription &value)
{
    if(propertyName == PROPERTY_SCROLL_BAR_POSITION_FROM_CORNER) {
        _scrollBarPositionFromCorner = value;
    } else {
        WidgetLoader::onHandlePropTypePosition(propertyName, isExtraProp, value);
    }
}
    
void ScrollListViewLoader::onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value)
{
    if(propertyName == PROPERTY_CLIPCONTENT) {
        _clipping = value;
    } else if(propertyName == PROPERTY_INERTIAL_SCROLL) {
        _inertial = value;
    } else if(propertyName == PROPERTY_SCROLL_BAR_ENABLED) {
        _scrollBar = value;
    } else if(propertyName == PROPERTY_BOUNCES) {
        _bounce = value;
    } else if(propertyName == PROPERTY_HORIZONRAL) {
        _horizontal = value;
    } else if(propertyName == PROPERTY_SCROLL_BAR_AUTOHIDE_ENABLED) {
        _scrollBarAutoHideEnabled = value;
    } else if(propertyName == PROPERTY_SCROLL_BAR_HIDE_IF_SIZE_FIT) {
        _scrollHideIfSizeFit = value;
    } else {
        WidgetLoader::onHandlePropTypeCheck(propertyName, isExtraProp, value);
    }
}

}
    
NS_CC_END
