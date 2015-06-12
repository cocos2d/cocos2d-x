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

using namespace cocos2d;

NS_TIMELINE_BEGIN

class Timeline;
class ActionTimeline;

class CC_STUDIO_DLL Frame : public cocos2d::Ref
{
public:
    /** 
    * @~english Set frame index.
    * @~chinese 设置帧索引。
    * @param frameIndex @~english Frame index.
    * @~chinese 帧索引。
    */
    virtual void setFrameIndex(unsigned int frameIndex) { _frameIndex = frameIndex; }
    /**
    * @~english Get frame index.
    * @~chinese 获取帧索引。
    * @return @~english Frame index.
    * @~chinese 帧索引。
    */
    virtual unsigned int getFrameIndex() const { return _frameIndex; }

    /**
    * @~english Set timeline.
    * @~chinese 设置时间线。
    * @param timeline @~english Timeline.
    * @~chinese 时间线。
    */
    virtual void setTimeline(Timeline* timeline) { _timeline = timeline; }
    /**
    * @~english Get timeline.
    * @~chinese 获取时间线。
    * @return @~english Timeline.
    * @~chinese 时间线。
    */
    virtual Timeline* getTimeline() const { return _timeline; }

    /**
    * @~english Set node.
    * @~chinese 设置节点。
    * @param node @~english Node.
    * @~chinese 节点。
    */
    virtual void setNode(cocos2d::Node* node) { _node = node; }
    /**
    * @~english Get node.
    * @~chinese 获取节点。
    * @return @~english Node.
    * @~chinese 节点。
    */
    virtual cocos2d::Node* getNode() const { return _node; }

    /**
    * @~english Set is tween.
    * @~chinese 设置是否补间。
    * @param tween @~english Is tween.
    * @~chinese 是否补间。
    */
    virtual void setTween(bool tween) { _tween = tween; }
    /**
    * @~english Get is tween.
    * @~chinese 获取是否补间。
    * @return @~english Is tween.
    * @~chinese 是否补间。
    */
    virtual bool isTween() const { return _tween; }

    /**
    * @~english Set tween type.
    * @~chinese 设置补间种类。
    * @param tweenType @~english Tween type.
    * @~chinese 补间种类。
    */
    virtual void setTweenType(const tweenfunc::TweenType& tweenType) { _tweenType = tweenType; }
    /**
    * @~english Get tween type.
    * @~chinese 获取补间种类。
    * @return @~english Tween type.
    * @~chinese 补间种类。
    */
    virtual tweenfunc::TweenType getTweenType() const { return _tweenType; }
    
    /**
    * @~english Set tween params, to make easing with params, need `setTweenType(TweenType::CUSTOM_EASING)`.
    * @~chinese 设置补间参数。要使用补间参数，需要调用`setTweenType(TweenType::CUSTOM_EASING)`。
    * @param tweenType @~english Tween params.
    * @~chinese 补间参数。
    */
    virtual void setEasingParams(const std::vector<float>& easingParams);
    /**
    * @~english Set tween params.
    * @~chinese 获取补间参数。
    * @return @~english Tween params.
    * @~chinese 补间参数。
    */
    virtual const std::vector<float>& getEasingParams() const;
    
    virtual bool isEnterWhenPassed() { return _enterWhenPassed; }

    /**
    * @~english Calling when enter this frame.
    * @~chinese 当进入该帧时调用。
    * @param nextFrame @~english Next frame.
    * @~chinese 下一帧。
    * @param currentFrameIndex @~english Current frame Index.
    * @~chinese 当前帧索引。
    */
    virtual void onEnter(Frame* nextFrame, int currentFrameIndex) = 0;

    /**
    * @~english Calculate attribute by tween percent.
    * @~chinese 根据当前补间百分比计算当前属性。
    * @param nextFrame @~english percent.
    * @~chinese 补间百分比。
    */
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
    
    tweenfunc::TweenType _tweenType;
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

    /**
    * @~english Set visible.
    * @~chinese 设置是否可见。
    * @param visible @~english Is visible.
    * @~chinese 是否可见。
    */
    inline void setVisible(bool visible) { _visible = visible;}
    /**
    * @~english Get visible.
    * @~chinese 获取是否可见。
    * @return @~english Is visible.
    * @~chinese 是否可见。
    */
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

    /**
    * @~english Set texture name.
    * @~chinese 设置材质名称。
    * @param textureName @~english Texture name.
    * @~chinese 材质名称。
    */
    inline void setTextureName(std::string textureName) { _textureName = textureName;}
    /**
    * @~english Get texture name.
    * @~chinese 获取材质名称。
    * @return @~english Texture name.
    * @~chinese 材质名称。
    */
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

    /**
    * @~english Set rotation.
    * @~chinese 设置旋转。
    * @param rotation @~english Rotation angle.
    * @~chinese 旋转角度。
    */
    inline void  setRotation(float rotation) { _rotation = rotation; }
    /**
    * @~english Get rotation.
    * @~chinese 获取旋转。
    * @return @~english Rotation angle.
    * @~chinese 旋转角度。
    */
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

    /**
    * @~english Set skew x.
    * @~chinese 设置横向拉伸。
    * @param skewx @~english Skew x.
    * @~chinese 横向拉伸。
    */
    inline void  setSkewX(float skewx) { _skewX = skewx; }
    /**
    * @~english Get skew x.
    * @~chinese 获取横向拉伸。
    * @return @~english Skew x.
    * @~chinese 横向拉伸。
    */
    inline float getSkewX() const { return _skewX; }

    /**
    * @~english Set skew y.
    * @~chinese 设置纵向拉伸。
    * @param skewx @~english Skew y.
    * @~chinese 纵向拉伸。
    */
    inline void  setSkewY(float skewy) { _skewY = skewy; }
    /**
    * @~english Get skew y.
    * @~chinese 获取纵向拉伸。
    * @return @~english Skew y.
    * @~chinese 纵向拉伸。
    */
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

    /**
    * @~english Set position.
    * @~chinese 设置坐标。
    * @param position @~english Position.
    * @~chinese 坐标。
    */
    inline void setPosition(const cocos2d::Point& position) { _position = position; }
    /**
    * @~english Get position.
    * @~chinese 获取坐标。
    * @return @~english Position.
    * @~chinese 坐标。
    */
    inline cocos2d::Point getPosition() const { return _position; }

    /**
    * @~english Set position x.
    * @~chinese 设置x坐标。
    * @param x @~english Position x.
    * @~chinese x坐标。
    */
    inline void setX(float x) { _position.x = x; }
    /**
    * @~english Set position y.
    * @~chinese 设置y坐标。
    * @param x @~english Position y.
    * @~chinese y坐标。
    */
    inline void setY(float y) { _position.y = y; }

    /**
    * @~english Get position x.
    * @~chinese 获取x坐标。
    * @return @~english Position x.
    * @~chinese x坐标。
    */
    inline float getX() const { return _position.x; }
    /**
    * @~english Get position y.
    * @~chinese 获取y坐标。
    * @return @~english Position y.
    * @~chinese y坐标。
    */
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

    /**
    * @~english Set scale.
    * @~chinese 设置缩放值。
    * @param scale @~english Scale.
    * @~chinese 缩放值。
    */
    inline void  setScale(float scale) { _scaleX = scale; _scaleY = scale; }

    /**
    * @~english Set scale x.
    * @~chinese 设置x缩放值。
    * @param scaleX @~english Scale x.
    * @~chinese x缩放值。
    */
    inline void  setScaleX(float scaleX) { _scaleX = scaleX; }
    /**
    * @~english Get scale x.
    * @~chinese 获取x缩放值。
    * @return @~english Scale x.
    * @~chinese x缩放值。
    */
    inline float getScaleX() const { return _scaleX; }

    /**
    * @~english Set scale y.
    * @~chinese 设置y缩放值。
    * @param scaleX @~english Scale y.
    * @~chinese y缩放值。
    */
    inline void  setScaleY(float scaleY) { _scaleY = scaleY;}
    /**
    * @~english Get scale y.
    * @~chinese 获取y缩放值。
    * @return @~english Scale y.
    * @~chinese y缩放值。
    */
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

    /**
    * @~english Set anchor point.
    * @~chinese 设置锚点。
    * @param point @~english Anchor point.
    * @~chinese 锚点。
    */
    inline void setAnchorPoint(const cocos2d::Point& point) { _anchorPoint = point; }
    /**
    * @~english Get anchor point.
    * @~chinese 获取锚点。
    * @return @~english Anchor point.
    * @~chinese 锚点。
    */
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

    /**
    * @~english Set inner action type.
    * @~chinese 设置嵌套动画类型。
    * @param type @~english Inner action type.
    * @~chinese 嵌套动画类型。
    */
    inline void setInnerActionType(InnerActionType type) { _innerActionType = type; }
    /**
    * @~english Get inner action type.
    * @~chinese 获取嵌套动画类型。
    * @return @~english Inner action type.
    * @~chinese 嵌套动画类型。
    */
    inline InnerActionType getInnerActionType() const { return _innerActionType; }
    
    inline void setEnterWithName(bool isEnterWithName) { _enterWithName = isEnterWithName;}
    
    /**
    * @~english Set start frame index.
    * @~chinese 设置起始帧索引。
    * @param type @~english Start frame index.
    * @~chinese 起始帧索引。
    */
	void setStartFrameIndex(int frameIndex);
    /**
    * @~english Get start frame index.
    * @~chinese 获取起始帧索引。
    * @return @~english Start frame index.
    * @~chinese 起始帧索引。
    */
    inline int  getStartFrameIndex() const { return _startFrameIndex; }

    /**
    * @~english Set end frame index.
    * @~chinese 设置结束帧索引。
    * @param type @~english End frame index.
    * @~chinese 结束帧索引。
    */
	void setEndFrameIndex(int frameIndex);
    /**
    * @~english Get end frame index.
    * @~chinese 获取结束帧索引。
    * @return @~english End frame index.
    * @~chinese 结束帧索引。
    */
    inline int  getEndFrameIndex() const { return _endFrameIndex; }
    
    /**
    * @~english Set animation name.
    * @~chinese 设置动画名称。
    * @param animationNamed @~english Animation name.
    * @~chinese 动画名称。
    */
	void setAnimationName(const std::string& animationNamed);
    
    /**
    * @~english Set single frame index.
    * @~chinese 设置单帧索引。
    * @param frameIndex @~english Single frame index.
    * @~chinese 单帧索引。
    */
    inline void setSingleFrameIndex(int frameIndex) { _singleFrameIndex = frameIndex;}
    /**
    * @~english Get single frame index.
    * @~chinese 获取单帧索引。
    * @return @~english Single frame index.
    * @~chinese 单帧索引。
    */
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

    /**
    * @~english Set color.
    * @~chinese 设置颜色。
    * @param color @~english Color.
    * @~chinese 颜色。
    */
    inline void setColor(const cocos2d::Color3B& color) { _color = color; }
    /**
    * @~english Get color.
    * @~chinese 获取颜色。
    * @return @~english Color.
    * @~chinese 颜色。
    */
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

    /**
    * @~english Set alpha.
    * @~chinese 设置透明度。
    * @param alpha @~english Alpha.
    * @~chinese 透明度。
    */
    inline void setAlpha(GLubyte alpha) { _alpha = alpha; }
    /**
    * @~english Get alpha.
    * @~chinese 获取透明度。
    * @return @~english Alpha.
    * @~chinese 透明度。
    */
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

    /**
    * @~english Set frame event.
    * @~chinese 设置帧事件。
    * @param event @~english Frame event.
    * @~chinese 帧事件。
    */
    inline void setEvent(std::string event) { _event = event;}
    /**
    * @~english Get frame event.
    * @~chinese 获取帧事件。
    * @return @~english Frame event.
    * @~chinese 帧事件。
    */
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

    /**
    * @~english Set z order.
    * @~chinese 设置z轴次序。
    * @param zorder @~english Z order.
    * @~chinese z轴次序。
    */
    inline void setZOrder(int zorder) { _zorder = zorder;}
    /**
    * @~english Get z order.
    * @~chinese 获取z轴次序。
    * @return @~english Z order.
    * @~chinese z轴次序。
    */
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
    
    /**
    * @~english Get blend function.
    * @~chinese 获取混合函数。
    * @return @~english Blend function.
    * @~chinese 混合函数。
    */
    inline BlendFunc getBlendFunc() const { return _blendFunc; }
    /**
    * @~english Set blend function.
    * @~chinese 设置混合函数。
    * @param zorder @~english Blend function.
    * @~chinese 混合函数。
    */
    inline void setBlendFunc(BlendFunc blendFunc) { _blendFunc = blendFunc; }
    
protected:
    BlendFunc  _blendFunc;
};
NS_TIMELINE_END


#endif /*__CCFRAME_H__*/
