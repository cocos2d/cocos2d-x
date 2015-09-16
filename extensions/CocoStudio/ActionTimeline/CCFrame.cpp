/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCFrame.h"
#include "CCTimeLine.h"
#include "CCActionTimeline.h"

using namespace cocos2d;

NS_TIMELINE_BEGIN

// Frame
Frame::Frame()
    : _frameIndex(0)
    , _tween(true)
    , _timeline(NULL)
    , _node(NULL)
{
}

Frame::~Frame()
{
}

void Frame::emitEvent()
{
    if (_timeline)
    {
        _timeline->getActionTimeline()->emitFrameEvent(this);
    }
}

void Frame::cloneProperty(Frame* frame)
{
    _frameIndex = frame->getFrameIndex();
    _tween = frame->isTween();
}


// VisibleFrame
VisibleFrame* VisibleFrame::create()
{
    VisibleFrame* frame = new VisibleFrame();
    if (frame)
    {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return NULL;
}

VisibleFrame::VisibleFrame()
    : _visible(true)
{
}

void VisibleFrame::onEnter(Frame *nextFrame)
{
    _node->setVisible(_visible);
}


Frame* VisibleFrame::clone()
{
    VisibleFrame* frame = VisibleFrame::create();
    frame->setVisible(_visible);

    frame->cloneProperty(this);

    return frame;
}


// TextureFrame
TextureFrame* TextureFrame::create()
{
    TextureFrame* frame = new TextureFrame();
    if (frame)
    {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return NULL;
}

TextureFrame::TextureFrame()
    : _textureName("")
{
}

void TextureFrame::setNode(cocos2d::CCNode* node)
{
    Frame::setNode(node);

    _sprite = dynamic_cast<CCSprite*>(node);
}

void TextureFrame::onEnter(Frame *nextFrame)
{
    if(_sprite)
    {
        CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_textureName.c_str());

        if(spriteFrame != NULL)
            _sprite->initWithSpriteFrame(spriteFrame);
        else
            _sprite->initWithFile(_textureName.c_str());
    }
}


Frame* TextureFrame::clone()
{
    TextureFrame* frame = TextureFrame::create();
    frame->setTextureName(_textureName);

    frame->cloneProperty(this);

    return frame;
}


// RotationFrame
RotationFrame* RotationFrame::create()
{
    RotationFrame* frame = new RotationFrame();
    if (frame)
    {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return NULL;
}

RotationFrame::RotationFrame()
    : _rotation(0)
{
}

void RotationFrame::onEnter(Frame *nextFrame)
{
    _node->setRotation(_rotation);

    if(_tween)
    {
        _betwennRotation = static_cast<RotationFrame*>(nextFrame)->_rotation - _rotation;
    }
}

void RotationFrame::apply(float percent)
{
    if (_tween && _betwennRotation != 0)
    {
        float rotation = _rotation + percent * _betwennRotation;
        _node->setRotation(rotation);
    }
}

Frame* RotationFrame::clone()
{
    RotationFrame* frame = RotationFrame::create();
    frame->setRotation(_rotation);

    frame->cloneProperty(this);

    return frame;
}



// SkewFrame
SkewFrame* SkewFrame::create()
{
    SkewFrame* frame = new SkewFrame();
    if (frame)
    {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return NULL;
}

SkewFrame::SkewFrame()
    : _skewX(0)
    , _skewY(0)
{
}

void SkewFrame::onEnter(Frame *nextFrame)
{
    _node->setSkewX(_skewX);
    _node->setSkewY(_skewY);
    
    if(_tween)
    {
        _betweenSkewX = static_cast<SkewFrame*>(nextFrame)->_skewX - _skewX;
        _betweenSkewY = static_cast<SkewFrame*>(nextFrame)->_skewY - _skewY;
    }

}

void SkewFrame::apply(float percent)
{
    if (_tween && (_betweenSkewX != 0 || _betweenSkewY != 0))
    {
        float skewx = _skewX + percent * _betweenSkewX;
        float skewy = _skewY + percent * _betweenSkewY;

        _node->setSkewX(skewx);
        _node->setSkewY(skewy);
    }
}

Frame* SkewFrame::clone()
{
    SkewFrame* frame = SkewFrame::create();
    frame->setSkewX(_skewX);
    frame->setSkewY(_skewY);

    frame->cloneProperty(this);

    return frame;
}




// RotationSkewFrame
RotationSkewFrame* RotationSkewFrame::create()
{
    RotationSkewFrame* frame = new RotationSkewFrame();
    if (frame)
    {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return NULL;
}

RotationSkewFrame::RotationSkewFrame()
{
}

void RotationSkewFrame::onEnter(Frame *nextFrame)
{
    _node->setRotationX(_skewX);
    _node->setRotationY(_skewY);
    
    if (_tween)
    {
        _betweenSkewX = static_cast<RotationSkewFrame*>(nextFrame)->_skewX - _skewX;
        _betweenSkewY = static_cast<RotationSkewFrame*>(nextFrame)->_skewY - _skewY;
    }
}

void RotationSkewFrame::apply(float percent)
{
    if (_tween && (_betweenSkewX != 0 || _betweenSkewY != 0))
    {
        float skewx = _skewX + percent * _betweenSkewX;
        float skewy = _skewY + percent * _betweenSkewY;

        _node->setRotationX(skewx);
        _node->setRotationY(skewy);
    }
}

Frame* RotationSkewFrame::clone()
{
    RotationSkewFrame* frame = RotationSkewFrame::create();
    frame->setSkewX(_skewX);
    frame->setSkewY(_skewY);

    frame->cloneProperty(this);

    return frame;
}


// PositionFrame
PositionFrame* PositionFrame::create()
{
    PositionFrame* frame = new PositionFrame();
    if (frame)
    {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return NULL;
}

PositionFrame::PositionFrame()
    : _position(0,0)
{
}

void PositionFrame::onEnter(Frame *nextFrame)
{
    _node->setPosition(_position);

    if(_tween)
    {
        _betweenX = static_cast<PositionFrame*>(nextFrame)->_position.x - _position.x;
        _betweenY = static_cast<PositionFrame*>(nextFrame)->_position.y - _position.y;
    }
}

void PositionFrame::apply(float percent)
{
    if (_tween && (_betweenX != 0 || _betweenY != 0))
    {
        CCPoint p;
        p.x = _position.x + _betweenX * percent;
        p.y = _position.y + _betweenY * percent;

        _node->setPosition(p);
    }
}

Frame* PositionFrame::clone()
{
    PositionFrame* frame = PositionFrame::create();
    frame->setPosition(_position);

    frame->cloneProperty(this);

    return frame;
}


// ScaleFrame
ScaleFrame* ScaleFrame::create()
{
    ScaleFrame* frame = new ScaleFrame();
    if (frame)
    {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return NULL;
}

ScaleFrame::ScaleFrame()
    : _scaleX(1)
    , _scaleY(1)
{
}

void ScaleFrame::onEnter(Frame *nextFrame)
{
    _node->setScaleX(_scaleX);
    _node->setScaleY(_scaleY);
    
    if(_tween)
    {
        _betweenScaleX = static_cast<ScaleFrame*>(nextFrame)->_scaleX - _scaleX;
        _betweenScaleY = static_cast<ScaleFrame*>(nextFrame)->_scaleY - _scaleY;
    }
}

void ScaleFrame::apply(float percent)
{
    if (_tween && (_betweenScaleX != 0 || _betweenScaleY != 0))
    {
        float scaleX = _scaleX + _betweenScaleX * percent;
        float scaleY = _scaleY + _betweenScaleY * percent;

        _node->setScaleX(scaleX);
        _node->setScaleY(scaleY);
    }
}

Frame* ScaleFrame::clone()
{
    ScaleFrame* frame = ScaleFrame::create();
    frame->setScaleX(_scaleX);
    frame->setScaleY(_scaleY);  

    frame->cloneProperty(this);

    return frame;
}


// AnchorPointFrame
AnchorPointFrame* AnchorPointFrame::create()
{
    AnchorPointFrame* frame = new AnchorPointFrame();
    if (frame)
    {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return NULL;
}

AnchorPointFrame::AnchorPointFrame()
    : _anchorPoint(0.5f,0.5f)
{
}

void AnchorPointFrame::onEnter(Frame *nextFrame)
{
    _node->setAnchorPoint(_anchorPoint);
}


Frame* AnchorPointFrame::clone()
{
    AnchorPointFrame* frame = AnchorPointFrame::create();
    frame->setAnchorPoint(_anchorPoint);

    frame->cloneProperty(this);

    return frame;
}



// InnerActionFrame
InnerActionFrame* InnerActionFrame::create()
{
    InnerActionFrame* frame = new InnerActionFrame();
    if (frame)
    {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return NULL;
}

InnerActionFrame::InnerActionFrame()
    : _innerActionType(LoopAction)
    , _startFrameIndex(0)
{
}

void InnerActionFrame::onEnter(Frame *nextFrame)
{
}


Frame* InnerActionFrame::clone()
{
    InnerActionFrame* frame = InnerActionFrame::create();
    frame->setInnerActionType(_innerActionType);
    frame->setStartFrameIndex(_startFrameIndex);

    frame->cloneProperty(this);

    return frame;
}


// ColorFrame
ColorFrame* ColorFrame::create()
{
    ColorFrame* frame = new ColorFrame();
    if (frame)
    {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return NULL;
}

ColorFrame::ColorFrame()
    : _alpha(255)
    , _color(ccc3(255, 255, 255))
{
}

void ColorFrame::onEnter(Frame *nextFrame)
{
    CCRGBAProtocol *rgbaProtocaol = dynamic_cast<CCRGBAProtocol *>(_node);

    if(!rgbaProtocaol)
        return;

    rgbaProtocaol->setOpacity(_alpha);
    rgbaProtocaol->setColor(_color);
    
    if(_tween)
    {
        _betweenAlpha = static_cast<ColorFrame*>(nextFrame)->_alpha - _alpha;

        const cocos2d::ccColor3B& color = static_cast<ColorFrame*>(nextFrame)->_color;
        _betweenRed   = color.r - _color.r;
        _betweenGreen = color.g - _color.g;
        _betweenBlue  = color.b - _color.b;
    }

    rgbaProtocaol->setCascadeColorEnabled(true);
    rgbaProtocaol->setCascadeOpacityEnabled(true);

}

void ColorFrame::apply(float percent)
{
    if (_tween && (_betweenAlpha != 0 || _betweenRed != 0 || _betweenGreen != 0 || _betweenBlue != 0))
    {
        CCRGBAProtocol *rgbaProtocaol = dynamic_cast<CCRGBAProtocol *>(_node);

        if(!rgbaProtocaol)
            return;

        GLubyte alpha = _alpha + _betweenAlpha * percent;

        cocos2d::ccColor3B color;
        color.r = _color.r+ _betweenRed   * percent;
        color.g = _color.g+ _betweenGreen * percent;
        color.b = _color.b+ _betweenBlue  * percent;

        rgbaProtocaol->setOpacity(alpha);
        rgbaProtocaol->setColor(color);
    }
}

Frame* ColorFrame::clone()
{
    ColorFrame* frame = ColorFrame::create();
    frame->setAlpha(_alpha);
    frame->setColor(_color);

    frame->cloneProperty(this);

    return frame;
}



// EventFrame
EventFrame* EventFrame::create()
{
    EventFrame* frame = new EventFrame();
    if (frame)
    {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return NULL;
}

EventFrame::EventFrame()
    : _event("")
{
}

void EventFrame::onEnter(Frame *nextFrame)
{
    emitEvent();
}


Frame* EventFrame::clone()
{
    EventFrame* frame = EventFrame::create();
    frame->setEvent(_event);

    frame->cloneProperty(this);

    return frame;
}


// ZOrderFrame
ZOrderFrame* ZOrderFrame::create()
{
    ZOrderFrame* frame = new ZOrderFrame();
    if (frame)
    {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return NULL;
}

ZOrderFrame::ZOrderFrame()
    : _zorder(0)
{
}

void ZOrderFrame::onEnter(Frame *nextFrame)
{
    if(_node)
        _node->setZOrder(_zorder);
}


Frame* ZOrderFrame::clone()
{
    ZOrderFrame* frame = ZOrderFrame::create();
    frame->setZOrder(_zorder);

    frame->cloneProperty(this);

    return frame;
}

NS_TIMELINE_END
