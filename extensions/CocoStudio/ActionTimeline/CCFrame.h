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

#ifndef __CCFRAME_H__
#define __CCFRAME_H__

#include "cocos2d.h"
#include "CCTimelineMacro.h"
#include "ExtensionExport.h"

NS_TIMELINE_BEGIN
class Timeline;

class CC_EX_DLL Frame : public cocos2d::CCObject
{
public:
     Frame();
     virtual ~Frame();
    
    virtual void setFrameIndex(unsigned int frameIndex) { _frameIndex = frameIndex; }
    virtual unsigned int getFrameIndex()const { return _frameIndex; }

    virtual void setTimeline(Timeline* timeline) { _timeline = timeline; }
    virtual Timeline* getTimeline() const { return _timeline; }

    virtual void setNode(cocos2d::CCNode* node) { _node = node; }
    virtual cocos2d::CCNode* getNode() const { return _node; }

    virtual void setTween(bool tween) { _tween = tween; }
    virtual bool isTween() const { return _tween; }

    virtual void onEnter(Frame *nextFrame) {}
    virtual void apply(float percent) {}

    virtual Frame* clone() { return NULL; }
    
protected:

    virtual void emitEvent();
    void cloneProperty(Frame* frame);
protected:
    friend class Timeline;

    unsigned int    _frameIndex;
    bool            _tween;

    Timeline* _timeline;
    cocos2d::CCNode*  _node;
};


class CC_EX_DLL VisibleFrame : public Frame
{
public:
    static VisibleFrame* create();

    VisibleFrame();

    virtual void onEnter(Frame *nextFrame) ;
    virtual Frame* clone() ;

    inline void setVisible(bool visible) { _visible = visible;}
    inline bool isVisible() const { return _visible; }

protected:
    bool _visible;
};


class CC_EX_DLL TextureFrame : public Frame
{
public:
    static TextureFrame* create();

    TextureFrame();

    virtual void setNode(cocos2d::CCNode* node);

    virtual void onEnter(Frame *nextFrame) ;
    virtual Frame* clone() ;

    inline void setTextureName(std::string textureName) { _textureName = textureName;}
    inline std::string getTextureName() const { return _textureName; }

protected:
    cocos2d::CCSprite* _sprite;
    std::string _textureName;
};



class CC_EX_DLL RotationFrame : public Frame
{
public:
    static RotationFrame* create();

    RotationFrame();

    virtual void onEnter(Frame *nextFrame) ;
    virtual void apply(float percent) ;
    virtual Frame* clone() ;

    inline void  setRotation(float rotation) { _rotation = rotation; }
    inline float getRotation() const { return _rotation; }

protected:
    float _rotation;
    float _betwennRotation;
};

class CC_EX_DLL SkewFrame : public Frame
{
public:
    static SkewFrame* create();

    SkewFrame();

    virtual void onEnter(Frame *nextFrame) ;
    virtual void apply(float percent) ;
    virtual Frame* clone() ;

    inline void  setSkewX(float skewx) { _skewX = skewx; }
    inline float getSkewX() const { return _skewX; }

    inline void  setSkewY(float skewy) { _skewY = skewy; }
    inline float getSkewY() const { return _skewY; }

protected:
    float _skewX;
    float _skewY;
    float _betweenSkewX;
    float _betweenSkewY;
};


class CC_EX_DLL RotationSkewFrame : public SkewFrame
{
public:
    static RotationSkewFrame* create();

    RotationSkewFrame();

    virtual void onEnter(Frame *nextFrame) ;
    virtual void apply(float percent) ;
    virtual Frame* clone() ;
};


class CC_EX_DLL PositionFrame : public Frame
{
public:
    static PositionFrame* create();

    PositionFrame();

    virtual void onEnter(Frame *nextFrame) ;
    virtual void apply(float percent) ;
    virtual Frame* clone() ;

    inline void setPosition(const cocos2d::CCPoint& position) { _position = position; }
    inline cocos2d::CCPoint getPosition() const { return _position; }

    inline void setX(float x) { _position.x = x; }
    inline void setY(float y) { _position.y = y; }

    inline float getX() const { return _position.x; }
    inline float getY() const { return _position.y; }
protected:
    cocos2d::CCPoint _position;
    float _betweenX;
    float _betweenY;
};


class CC_EX_DLL ScaleFrame : public Frame
{
public:
    static ScaleFrame* create();

    ScaleFrame();

    virtual void onEnter(Frame *nextFrame) ;
    virtual void apply(float percent) ;
    virtual Frame* clone() ;

    inline void  setScale(float scale) { _scaleX = scale; _scaleY = scale; }

    inline void  setScaleX(float scaleX) { _scaleX = scaleX; }
    inline float getScaleX() const { return _scaleX; }

    inline void  setScaleY(float scaleY) { _scaleY = scaleY;}
    inline float getScaleY() const { return _scaleY; }

protected:
    float _scaleX;
    float _scaleY;
    float _betweenScaleX;
    float _betweenScaleY;
};


class CC_EX_DLL AnchorPointFrame : public Frame
{
public:
    static AnchorPointFrame* create();

    AnchorPointFrame();

    virtual void onEnter(Frame *nextFrame) ;
    virtual Frame* clone() ;

    inline void setAnchorPoint(const cocos2d::CCPoint& point) { _anchorPoint = point; }
    inline cocos2d::CCPoint getAnchorPoint() const { return _anchorPoint; }

protected:
    cocos2d::CCPoint _anchorPoint;
};



enum InnerActionType
{
    LoopAction,
    NoLoopAction,
    SingleFrame
};

class CC_EX_DLL InnerActionFrame : public Frame
{
public:
    static InnerActionFrame* create();
    InnerActionFrame();

    virtual void onEnter(Frame *nextFrame) ;
    virtual Frame* clone() ;

    inline void setInnerActionType(InnerActionType type) { _innerActionType = type; }
    inline InnerActionType getInnerActionType() const { return _innerActionType; }

    inline void setStartFrameIndex(int frameIndex) { _startFrameIndex = frameIndex; }
    inline int  getStartFrameIndex() const { return _startFrameIndex; }

protected:
    InnerActionType _innerActionType;
    int _startFrameIndex;
};


class CC_EX_DLL ColorFrame : public Frame
{
public:
    static ColorFrame* create();
    ColorFrame();

    virtual void onEnter(Frame *nextFrame) ;
    virtual void apply(float percent) ;
    virtual Frame* clone() ;

    inline void    setAlpha(GLubyte alpha) { _alpha = alpha; }
    inline GLubyte getAlpha() const { return _alpha; }

    inline void    setColor(const cocos2d::ccColor3B& color) { _color = color; }
    inline cocos2d::ccColor3B getColor() const { return _color; }

protected:
    GLubyte _alpha;
    cocos2d::ccColor3B _color;

    int _betweenAlpha;
    int _betweenRed;
    int _betweenGreen;
    int _betweenBlue;
};

class CC_EX_DLL EventFrame : public Frame
{
public:
    static EventFrame* create();

    EventFrame();

    virtual void onEnter(Frame *nextFrame) ;
    virtual Frame* clone() ;

    inline void setEvent(std::string event) { _event = event;}
    inline std::string getEvent() const { return _event; }

protected:
    std::string _event;
};

class CC_EX_DLL ZOrderFrame : public Frame
{
public:
    static ZOrderFrame* create();

    ZOrderFrame();

    virtual void onEnter(Frame *nextFrame) ;
    virtual Frame* clone() ;

    inline void setZOrder(int zorder) { _zorder = zorder;}
    inline int getZOrder() const { return _zorder; }

protected:
    int _zorder;
};

NS_TIMELINE_END


#endif /*__CCFRAME_H__*/
