

#include "CustomImageView.h"

CustomImageView::CustomImageView()
: _label(NULL)
{
    
}

CustomImageView::~CustomImageView()
{
    
}

CCObject* CustomImageView::createInstance()
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
    
    _label = CCLabelTTF::create();
    CCNode::addChild(_label, getZOrder() + 1, -1);
}

void CustomImageView::setText(const char* text)
{
    _label->setString(text);
}

const char* CustomImageView::getText() const
{
    return _label->getString();
}
