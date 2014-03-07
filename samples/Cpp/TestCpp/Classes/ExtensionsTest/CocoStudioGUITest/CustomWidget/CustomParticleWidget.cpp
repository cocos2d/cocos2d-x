//
//  CustomParticleWidget.cpp
//  CustomUI
//
//  Created by cai wenzhi on 14-3-7.
//
//

#include "CustomParticleWidget.h"

USING_NS_CC;
using namespace ui;

CustomParticleWidget::CustomParticleWidget()
: _emitter(NULL)
, _emitterPlist("")
{
    
}

CustomParticleWidget::~CustomParticleWidget()
{
    
}

CCObject* CustomParticleWidget::createInstance()
{
    return create();
}

CustomParticleWidget* CustomParticleWidget::create()
{
    CustomParticleWidget* custom = new CustomParticleWidget();
    
    if (custom && custom->init())
    {
        custom->autorelease();
        return custom;
    }
    CC_SAFE_DELETE(custom);
    return NULL;
}

bool CustomParticleWidget::init()
{
    if (Widget::init())
    {
        return true;
    }
    return false;
}

void CustomParticleWidget::initRenderer()
{
    Widget::initRenderer();
    
    _emitter = new CCParticleSystemQuad();
    CCNode::addChild(_emitter , getZOrder() + 1, -1);
}

void CustomParticleWidget::removeAllChildren()
{
    CC_SAFE_RELEASE_NULL(_emitter);
    
    Widget::removeAllChildren();
}

void CustomParticleWidget::setParticlePlist(const char *plist)
{
    _emitter->initWithFile(plist);
    
    _emitterPlist = plist;
}

const char* CustomParticleWidget::getParticlePlist() const
{
    return _emitterPlist;
}

void CustomParticleWidget::setParticlePosition(const CCPoint &pos)
{
    _emitter->setPosition(pos);
    
    _emitterPostion = pos;
}

const CCPoint& CustomParticleWidget::getParticlePosition() const
{
    return _emitterPostion;
}


