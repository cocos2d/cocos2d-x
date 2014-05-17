/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2010 Sangwoo Im
 
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

#ifndef __CCSCROLLVIEW_H__
#define __CCSCROLLVIEW_H__

#include "2d/CCLayer.h"
#include "base/CCEventListenerTouch.h"
#include "2d/CCActionTween.h"
#include "extensions/ExtensionMacros.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 */

class ScrollView;

class ScrollViewDelegate
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ScrollViewDelegate() {}
    /**
     * @js NA
     * @lua NA
     */
    virtual void scrollViewDidScroll(ScrollView* view) = 0;
    /**
     * @js NA
     * @lua NA
     */
    virtual void scrollViewDidZoom(ScrollView* view) = 0;
};


/**
 * Cocos2d-x的ScrollView支持。
 * 为Cocos2d-x项目提供原生的滚动以及缩放功能。
 */
class ScrollView : public Layer, public ActionTweenDelegate
{
public:
    enum class Direction
    {
        NONE = -1,
        HORIZONTAL = 0,
        VERTICAL,
        BOTH
    };
    /**
     * 返回一个autoreleased的ScrollView对象。
     *
     * @param size view的尺寸
     * @param container 需要被滚动的父对象
     * @return autorelease的ScrollView对象
     */
    static ScrollView* create(Size size, Node* container = NULL);

    /**
     * 返回一个autoreleased的ScrollView对象。
     *
     * @return autorelease的ScrollView对象
     */
    static ScrollView* create();
    /**
     * @js ctor
     */
    ScrollView();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ScrollView();

    bool init();
    /**
     * 初始化
     *
     * @param size view的尺寸
     * @param container 需要被滚动的父对象
     * @return 初始化成功返回true，否则false
     */
    bool initWithViewSize(Size size, Node* container = NULL);

    /**
     * 为被滚动的container设置一个新的偏移值。本方法会忽略最大值最小值的限制，直接用所传参数进行设置。 (与 UIKit中 UIScrollView的处理方式一致)
     *
     * @param offset    新的偏移值
     * @param animated  如果值为真,则滚动到新的偏移位置，否则瞬时改变
     */
    void setContentOffset(Vec2 offset, bool animated = false);
    Vec2 getContentOffset();
    /**
     * 为被滚动的container设置一个新的偏移值。本方法会忽略最大值最小值的限制，直接用所传参数进行设置。 (与 UIKit中 UIScrollView的处理方式一致)
     * 通过本方法可以自定义动画持续时间。
     *
     * @param offset    新的偏移值
     * @param dt        动画持续时间
     */
    void setContentOffsetInDuration(Vec2 offset, float dt); 

    void setZoomScale(float s);
    /**
     * 为被缩放的container设置一个新的缩放比例，如果传入参数要求播放动画，动画持续时间为预定义值。
     *
     * @param s         新的缩放比例
     * @param animated  如果值为真，则有缩放动画变化过程，否则瞬时改变
     */
    void setZoomScale(float s, bool animated);

    float getZoomScale();

    /**
     * 为被缩放的container设置一个新的缩放比例。
     * 通过本方法可以自定义动画持续时间。
     *
     * @param s     新的缩放比例
     * @param dt    动画持续时间
     */
    void setZoomScaleInDuration(float s, float dt);
    /**
     * 返回container的最小偏移值。自己控制滚动动画效果时可能需要用到。
     */
    Vec2 minContainerOffset();
    /**
     * 返回container的最大偏移值。自己控制滚动动画效果时可能需要用到。
     */
    Vec2 maxContainerOffset(); 
    /**
     * 判断给定node的包围盒是否在可见区域
     *
     * @returns 可见返回真，否则返回假
     */
    bool isNodeVisible(Node * node);
    /**
     * 为了和SWLayer的暂停方法兼容，提供本暂停方法。
     */
    void pause(Ref* sender);
    /**
     * 为了和SWLayer的继续方法兼容，提供本继续方法。
     */
    void resume(Ref* sender);

    void setTouchEnabled(bool enabled);
	bool isTouchEnabled() const;
    bool isDragging() const {return _dragging;}
    bool isTouchMoved() const { return _touchMoved; }
    bool isBounceable() const { return _bounceable; }
    void setBounceable(bool bBounceable) { _bounceable = bBounceable; }

    /**
     * 用于裁剪的尺寸。节点的包围盒是直接使用contentSize。
     * 此处与通常意义的scroll view语义不同，
     * 因此额外增加了这个尺寸属性。
     */
    Size getViewSize() const { return _viewSize; }
    void setViewSize(Size size);

    Node * getContainer();
    void setContainer(Node * pContainer);

    /**
     * 允许滚动的方向，默认是可以双向滚动的ScrollViewDirectionBoth。
     */
    Direction getDirection() const { return _direction; }
    virtual void setDirection(Direction eDirection) { _direction = eDirection; }
    /**
     * @js NA
     * @lua NA
     */
    ScrollViewDelegate* getDelegate() { return _delegate; }
    /**
     * @code
     * 本函数与js或者lua绑定的时候，输入参数会有变化
     * in js: var setDelegate(var jsObject)
     * in lua: local setDelegate()
     * @endcode
     */
    void setDelegate(ScrollViewDelegate* pDelegate) { _delegate = pDelegate; }

	void updateInset();

    /**
     * 判断是否需要对container里的内容进行裁剪
     */
    bool isClippingToBounds() { return _clippingToBounds; }
    void setClippingToBounds(bool bClippingToBounds) { _clippingToBounds = bClippingToBounds; }

    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    virtual void onTouchCancelled(Touch *touch, Event *event);
    
    // Overrides
    virtual void setContentSize(const Size & size) override;
    virtual const Size& getContentSize() const override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;
    
    using Node::addChild;
    virtual void addChild(Node * child, int zOrder, int tag) override;

    /**
     * CCActionTweenDelegate
     */
    void updateTweenAction(float value, const std::string& key);
protected:
    /**
     * 将container重新定位到合适的偏移值，即会受到最大值最小值的限制。
     *
     * @param animated 为真则有动画效果
     */
    void relocateContainer(bool animated);
    /**
     * 实现自动滚动效果。如果需要改变减速时的加速度则修改 SCROLL_DEACCEL_RATE
     * 此值必须小于1.0f。
     *
     * @param dt delta
     */
    void deaccelerateScrolling(float dt);
    /**
     * 本方法确保自动滚动过程中相应的委托方法得到调用
     */
    void performedAnimatedScroll(float dt);
    /**
     * 滚动结束停止相关委托的调用
     */
    void stoppedAnimatedScroll(Node* node);
    /**
     * 对本view进行裁剪，可见范围外的内容将被隐藏。
     */
    void beforeDraw();
    void onBeforeDraw();
    /**
     * 将在beforeDraw中作出的修改还原
     * 以避免影响到其余node
     */
    void afterDraw();
    void onAfterDraw();
    /**
     * 处理缩放
     */
    void handleZoom();

    Rect getViewRect();
    
    /**
     * 当前缩放比例
     */
    float _zoomScale;
    /**
     * 最小缩放比例
     */
    float _minZoomScale;
    /**
     * 最大缩放比例
     */
    float _maxZoomScale;
    /**
     * ScrollView的委托
     */
    ScrollViewDelegate* _delegate;

    Direction _direction;
    /**
     * 当前view正在被拖动时为真
     */
    bool _dragging;

    /**
     * 内容的偏移值，注意左下角为原点
     */
    Vec2 _contentOffset;

    /**
     * Container用于存放具体需要被滚动的内容
     */
    Node* _container;
    /**
     * 用于判断用户的触摸在开始阶段之后是否有移动
     */
    bool _touchMoved;
    /**
     * 用于限制可拖动范围的最大内边框点
     */
    Vec2 _maxInset;
    /**
     * 用于限制可拖动范围的最小内边框点
     */
    Vec2 _minInset;
    /**
     * 用于判断ScrollView是否有反弹效果
     */
    bool _bounceable;

    bool _clippingToBounds;

    /**
     * 滚动距离
     */
    Vec2 _scrollDistance;
    /**
     * 触摸点
     */
    Vec2 _touchPoint;
    /**
     * 两指之间的距离
     */
    float _touchLength;
    /**
     * 用于检测多点触摸的触摸对象数组
     */
    std::vector<Touch*> _touches;
    /**
     * 用于裁剪的尺寸。节点的包围盒是直接使用contentSize。
     * 此处与通常意义的scroll view语义不同，
     * 因此额外增加了这个尺寸属性。
     */
    Size _viewSize;
    /**
     * 最大最小缩放比例
     */
    float _minScale, _maxScale;
    /**
     * 父节点的裁剪矩形，仅用于恢复GL_SCISSOR_BOX
     */
    Rect _parentScissorRect;
    bool _scissorRestored;
    
    /** 触摸的listener */
    EventListenerTouchOneByOne* _touchListener;
    
    CustomCommand _beforeDrawCommand;
    CustomCommand _afterDrawCommand;
};

// end of GUI group
/// @}

NS_CC_EXT_END

#endif /* __CCSCROLLVIEW_H__ */
