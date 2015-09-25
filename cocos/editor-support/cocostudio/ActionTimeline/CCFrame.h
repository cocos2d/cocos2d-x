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

#include <string>
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "2d/CCNode.h"
#include "2d/CCSprite.h"
#include "2d/CCTweenFunction.h"
#include "CCTimelineMacro.h"
#include "cocostudio/CocosStudioExport.h"

NS_TIMELINE_BEGIN

class Timeline;
class ActionTimeline;

class CC_STUDIO_DLL Frame : public cocos2d::Ref
{
public:

    virtual void setFrameIndex(unsigned int frameIndex) { _frameIndex = frameIndex; }
    virtual unsigned int getFrameIndex() const { return _frameIndex; }

    virtual void setTimeline(Timeline* timeline) { _timeline = timeline; }
    virtual Timeline* getTimeline() const { return _timeline; }

    virtual void setNode(cocos2d::Node* node) { _node = node; }
    virtual cocos2d::Node* getNode() const { return _node; }

    virtual void setTween(bool tween) { _tween = tween; }
    virtual bool isTween() const { return _tween; }

    virtual void setTweenType(const cocos2d::tweenfunc::TweenType& tweenType) { _tweenType = tweenType; }
    virtual cocos2d::tweenfunc::TweenType getTweenType() const { return _tweenType; }
    
    // !to make easing with params, need setTweenType(TweenType::CUSTOM_EASING)
    virtual void setEasingParams(const std::vector<float>& easingParams);
    virtual const std::vector<float>& getEasingParams() const;
    
    virtual bool isEnterWhenPassed() { return _enterWhenPassed; }

    virtual void onEnter(Frame* nextFrame, int currentFrameIndex) = 0;
    virtual void apply(float percent);

    virtual Frame* clone() = 0;
protected:
    Frame();
    virtual ~Frame();
    
    virtual void onApply(float percent) {};
    //update percent depends _tweenType, and return the Calculated percent
    virtual float tweenPercent(float percent);
    
    virtual void emitEvent();
    virtual void cloneProperty(Frame* frame);
protected:

    unsigned int    _frameIndex;
    bool            _tween;
    bool            _enterWhenPassed;
    
    cocos2d::tweenfunc::TweenType _tweenType;
    std::vector<float>   _easingParam;
    Timeline* _timeline;
    cocos2d::Node*  _node;
};


class CC_STUDIO_DLL VisibleFrame : public Frame
{
public:
    static VisibleFrame* create();

    VisibleFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    inline void setVisible(bool visible) { _visible = visible;}
    inline bool isVisible() const { return _visible; }

protected:
    bool _visible;
};


class CC_STUDIO_DLL TextureFrame : public Frame
{
public:
    static TextureFrame* create();

    TextureFrame();

    virtual void setNode(cocos2d::Node* node) override;

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    inline void setTextureName(std::string textureName) { _textureName = textureName;}
    inline std::string getTextureName() const { return _textureName; }

protected:
    cocos2d::Sprite* _sprite;
    std::string _textureName;
};

class CC_STUDIO_DLL RotationFrame : public Frame
{
public:
    static RotationFrame* create();

    RotationFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    inline void  setRotation(float rotation) { _rotation = rotation; }
    inline float getRotation() const { return _rotation; }

protected:
    virtual void onApply(float percent) override;
    
    float _rotation;
    float _betwennRotation;
};

class CC_STUDIO_DLL SkewFrame : public Frame
{
public:
    static SkewFrame* create();

    SkewFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    inline void  setSkewX(float skewx) { _skewX = skewx; }
    inline float getSkewX() const { return _skewX; }

    inline void  setSkewY(float skewy) { _skewY = skewy; }
    inline float getSkewY() const { return _skewY; }

protected:
    virtual void onApply(float percent) override;
    
    float _skewX;
    float _skewY;
    float _betweenSkewX;
    float _betweenSkewY;
};


class CC_STUDIO_DLL RotationSkewFrame : public SkewFrame
{
public:
    static RotationSkewFrame* create();

    RotationSkewFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;
    
protected:
    virtual void onApply(float percent) override;
};


class CC_STUDIO_DLL PositionFrame : public Frame
{
public:
    static PositionFrame* create();

    PositionFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    inline void setPosition(const cocos2d::Point& position) { _position = position; }
    inline cocos2d::Point getPosition() const { return _position; }

    inline void setX(float x) { _position.x = x; }
    inline void setY(float y) { _position.y = y; }

    inline float getX() const { return _position.x; }
    inline float getY() const { return _position.y; }
    
protected:
    virtual void onApply(float percent) override;
    
    cocos2d::Point _position;
    float _betweenX;
    float _betweenY;
};


class CC_STUDIO_DLL ScaleFrame : public Frame
{
public:
    static ScaleFrame* create();

    ScaleFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    inline void  setScale(float scale) { _scaleX = scale; _scaleY = scale; }

    inline void  setScaleX(float scaleX) { _scaleX = scaleX; }
    inline float getScaleX() const { return _scaleX; }

    inline void  setScaleY(float scaleY) { _scaleY = scaleY;}
    inline float getScaleY() const { return _scaleY; }

protected:
    virtual void onApply(float percent) override;
    
    float _scaleX;
    float _scaleY;
    float _betweenScaleX;
    float _betweenScaleY;
};


class CC_STUDIO_DLL AnchorPointFrame : public Frame
{
public:
    static AnchorPointFrame* create();

    AnchorPointFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    inline void setAnchorPoint(const cocos2d::Point& point) { _anchorPoint = point; }
    inline cocos2d::Point getAnchorPoint() const { return _anchorPoint; }

protected:
    cocos2d::Point _anchorPoint;
};



enum InnerActionType
{
    LoopAction,
    NoLoopAction,
    SingleFrame
};

class CC_STUDIO_DLL InnerActionFrame : public Frame
{
public:
    static const std::string AnimationAllName;
    
    static InnerActionFrame* create();
    InnerActionFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    inline void setInnerActionType(InnerActionType type) { _innerActionType = type; }
    inline InnerActionType getInnerActionType() const { return _innerActionType; }
    
    inline void setEnterWithName(bool isEnterWithName) { _enterWithName = isEnterWithName;}
    
	void setStartFrameIndex(int frameIndex);
    inline int  getStartFrameIndex() const { return _startFrameIndex; }

	void setEndFrameIndex(int frameIndex);
    inline int  getEndFrameIndex() const { return _endFrameIndex; }
    
	void setAnimationName(const std::string& animationNamed);
    
    inline void setSingleFrameIndex(int frameIndex) { _singleFrameIndex = frameIndex;}
    inline int  getSingleFrameIndex() const { return _singleFrameIndex;}

protected:
    InnerActionType _innerActionType;
    int _startFrameIndex;
    int _endFrameIndex;
    int _singleFrameIndex;
    std::string _animationName;
    bool _enterWithName;
};


class CC_STUDIO_DLL ColorFrame : public Frame
{
public:
    static ColorFrame* create();
    ColorFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /** @deprecated Use method setAlpha() and getAlpha() of AlphaFrame instead */
    CC_DEPRECATED_ATTRIBUTE inline void    setAlpha(GLubyte alpha) { _alpha = alpha; }
    CC_DEPRECATED_ATTRIBUTE inline GLubyte getAlpha() const { return _alpha; }

    inline void    setColor(const cocos2d::Color3B& color) { _color = color; }
    inline cocos2d::Color3B getColor() const { return _color; }

protected:
    virtual void onApply(float percent) override;
    
    GLubyte _alpha;
    cocos2d::Color3B _color;

    int _betweenRed;
    int _betweenGreen;
    int _betweenBlue;
};

class CC_STUDIO_DLL AlphaFrame : public Frame
{
public:
    static AlphaFrame* create();
    AlphaFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    inline void    setAlpha(GLubyte alpha) { _alpha = alpha; }
    inline GLubyte getAlpha() const { return _alpha; }

protected:
    virtual void onApply(float percent) override;
    
    GLubyte _alpha;
    int _betweenAlpha;
};

class CC_STUDIO_DLL EventFrame : public Frame
{
public:
    static EventFrame* create();
    void init();

    EventFrame();

    virtual void setNode(cocos2d::Node* node) override;
    
    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    inline void setEvent(std::string event) { _event = event;}
    inline std::string getEvent() const { return _event; }

protected:
    std::string _event;
    ActionTimeline* _action;
};

class CC_STUDIO_DLL ZOrderFrame : public Frame
{
public:
    static ZOrderFrame* create();

    ZOrderFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    inline void setZOrder(int zorder) { _zorder = zorder;}
    inline int getZOrder() const { return _zorder; }

protected:
    int _zorder;
};


class CC_STUDIO_DLL BlendFuncFrame : public Frame
{
public:
    static BlendFuncFrame* create();
    
    BlendFuncFrame();
    
    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;
    
    inline cocos2d::BlendFunc getBlendFunc() const { return _blendFunc; }
    inline void setBlendFunc(cocos2d::BlendFunc blendFunc) { _blendFunc = blendFunc; }
    
protected:
    cocos2d::BlendFunc  _blendFunc;
};
NS_TIMELINE_END


#endif /*__CCFRAME_H__*/
