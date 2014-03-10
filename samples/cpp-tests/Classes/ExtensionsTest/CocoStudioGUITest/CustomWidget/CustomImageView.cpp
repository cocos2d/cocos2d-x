

#include "CustomImageView.h"

USING_NS_CC;
using namespace ui;

CustomImageView::CustomImageView()
: _label(NULL)
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
    return NULL;
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
    
    _label = LabelTTF::create();
    CCNodeRGBA::addChild(_label, getZOrder() + 1, -1);
}

void CustomImageView::setText(const std::string &text)
{
    _label->setString(text.c_str());
}

const std::string& CustomImageView::getText() const
{
    return _label->getString();
}
