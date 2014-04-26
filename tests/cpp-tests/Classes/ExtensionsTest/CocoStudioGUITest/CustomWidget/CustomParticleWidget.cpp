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
: _emitter(nullptr)
, _emitterPlist("")
{
    
}

CustomParticleWidget::~CustomParticleWidget()
{
    
}

Ref* CustomParticleWidget::createInstance()
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
}

void CustomParticleWidget::removeAllChildren()
{
    Widget::removeAllChildren();
}

void CustomParticleWidget::setParticlePlist(const char *plist)
{
    if (!_emitter)
    {
        _emitter = ParticleSystemQuad::create(plist);
        
    }
    else
    {
        _emitter->removeFromParent();
        _emitter = ParticleSystemQuad::create(plist);
    }
    Node::addChild(_emitter , getLocalZOrder() + 1, -1);
    
    _emitterPlist = plist;
}

const char* CustomParticleWidget::getParticlePlist() const
{
    return _emitterPlist;
}

void CustomParticleWidget::setParticlePosition(const Vector2 &pos)
{
    _emitter->setPosition(pos);
    
    _emitterPostion = pos;
}

const Vector2& CustomParticleWidget::getParticlePosition() const
{
    return _emitterPostion;
}

void CustomParticleWidget::playParticle()
{
    if (_emitter)
    {
        _emitter->resetSystem();
    }
    
}

void CustomParticleWidget::stopParticle()
{
    if (_emitter)
    {
        _emitter->stopSystem();
    }
    
}


