

#include "CustomImageView.h"
#include "2d/CCNode.h"

USING_NS_CC;
using namespace ui;

CustomImageView::CustomImageView()
: _label(nullptr)
{
    
}

CustomImageView::~CustomImageView()
{
    
}

Ref* CustomImageView::createInstance()
{
    return create();
}

CustomImageView* CustomImageView::create()
{
    CustomImageView* custom = new CustomImageView();
    
    if (custom && custom->init())
    {
        custom->autorelease();
        return custom;
    }
    CC_SAFE_DELETE(custom);
    return nullptr;
}

bool CustomImageView::init()
{
    if (ImageView::init())
    {
        return true;
    }
    return false;
}

void CustomImageView::initRenderer()
{
    ImageView::initRenderer();
    
    _label = Label::create();
    ProtectedNode::addChild(_label, getLocalZOrder() + 1, -1);
}

void CustomImageView::setText(const std::string &text)
{
    _label->setString(text.c_str());
}

const std::string& CustomImageView::getText() const
{
    return _label->getString();
}
