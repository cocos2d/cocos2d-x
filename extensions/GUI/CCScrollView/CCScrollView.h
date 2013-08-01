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

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 */

class ScrollView;

class ScrollViewDelegate
{
public:
    virtual ~ScrollViewDelegate() {}
    virtual void scrollViewDidScroll(ScrollView* view) = 0;
    virtual void scrollViewDidZoom(ScrollView* view) = 0;
};


/**
 * ScrollView support for cocos2d for iphone.
 * It provides scroll view functionalities to cocos2d projects natively.
 */
class ScrollView : public Layer
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
     * Returns an autoreleased scroll view object.
     *
     * @param size view size
     * @param container parent object
     * @return autoreleased scroll view object
     */
    static ScrollView* create(Size size, Node* container = NULL);

    /**
     * Returns an autoreleased scroll view object.
     *
     * @return autoreleased scroll view object
     */
    static ScrollView* create();

    ScrollView();
    virtual ~ScrollView();

    bool init();
    /**
     * Returns a scroll view object
     *
     * @param size view size
     * @param container parent object
     * @return scroll view object
     */
    bool initWithViewSize(Size size, Node* container = NULL);

    virtual void registerWithTouchDispatcher();

    /**
     * Sets a new content offset. It ignores max/min offset. It just sets what's given. (just like UIKit's UIScrollView)
     *
     * @param offset    The new offset.
     * @param animated  If true, the view will scroll to the new offset.
     */
    void setContentOffset(Point offset, bool animated = false);
    Point getContentOffset();
    /**
     * Sets a new content offset. It ignores max/min offset. It just sets what's given. (just like UIKit's UIScrollView)
     * You can override the animation duration with this method.
     *
     * @param offset    The new offset.
     * @param dt        The animation duration.
     */
    void setContentOffsetInDuration(Point offset, float dt); 

    void setZoomScale(float s);
    /**
     * Sets a new scale and does that for a predefined duration.
     *
     * @param s         The new scale vale
     * @param animated  If true, scaling is animated
     */
    void setZoomScale(float s, bool animated);

    float getZoomScale();

    /**
     * Sets a new scale for container in a given duration.
     *
     * @param s     The new scale value
     * @param dt    The animation duration
     */
    void setZoomScaleInDuration(float s, float dt);
    /**
     * Returns the current container's minimum offset. You may want this while you animate scrolling by yourself
     */
    Point minContainerOffset();
    /**
     * Returns the current container's maximum offset. You may want this while you animate scrolling by yourself
     */
    Point maxContainerOffset(); 
    /**
     * Determines if a given node's bounding box is in visible bounds
     *
     * @returns true if it is in visible bounds
     */
    bool isNodeVisible(Node * node);
    /**
     * Provided to make scroll view compatible with SWLayer's pause method
     */
    void pause(Object* sender);
    /**
     * Provided to make scroll view compatible with SWLayer's resume method
     */
    void resume(Object* sender);


    bool isDragging() const {return _dragging;}
    bool isTouchMoved() const { return _touchMoved; }
    bool isBounceable() const { return _bounceable; }
    void setBounceable(bool bBounceable) { _bounceable = bBounceable; }

    /**
     * size to clip. Node boundingBox uses contentSize directly.
     * It's semantically different what it actually means to common scroll views.
     * Hence, this scroll view will use a separate size property.
     */
    Size getViewSize() const { return _viewSize; }
    void setViewSize(Size size);

    Node * getContainer();
    void setContainer(Node * pContainer);

    /**
     * direction allowed to scroll. ScrollViewDirectionBoth by default.
     */
    Direction getDirection() const { return _direction; }
    virtual void setDirection(Direction eDirection) { _direction = eDirection; }

    ScrollViewDelegate* getDelegate() { return _delegate; }
    void setDelegate(ScrollViewDelegate* pDelegate) { _delegate = pDelegate; }

	void updateInset();

    /**
     * Determines whether it clips its children or not.
     */
    bool isClippingToBounds() { return _clippingToBounds; }
    void setClippingToBounds(bool bClippingToBounds) { _clippingToBounds = bClippingToBounds; }

    // Overrides
    virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent) override;
    virtual void ccTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void ccTouchEnded(Touch *pTouch, Event *pEvent) override;
    virtual void ccTouchCancelled(Touch *pTouch, Event *pEvent) override;
    virtual void setContentSize(const Size & size) override;
    virtual const Size& getContentSize() const override;
    virtual void visit() override;
    virtual void addChild(Node * child, int zOrder, int tag) override;
    virtual void addChild(Node * child, int zOrder) override;
    virtual void addChild(Node * child) override;
    void setTouchEnabled(bool e) override;

protected:
    /**
     * Relocates the container at the proper offset, in bounds of max/min offsets.
     *
     * @param animated If true, relocation is animated
     */
    void relocateContainer(bool animated);
    /**
     * implements auto-scrolling behavior. change SCROLL_DEACCEL_RATE as needed to choose
     * deacceleration speed. it must be less than 1.0f.
     *
     * @param dt delta
     */
    void deaccelerateScrolling(float dt);
    /**
     * This method makes sure auto scrolling causes delegate to invoke its method
     */
    void performedAnimatedScroll(float dt);
    /**
     * Expire animated scroll delegate calls
     */
    void stoppedAnimatedScroll(Node* node);
    /**
     * clip this view so that outside of the visible bounds can be hidden.
     */
    void beforeDraw();
    /**
     * retract what's done in beforeDraw so that there's no side effect to
     * other nodes.
     */
    void afterDraw();
    /**
     * Zoom handling
     */
    void handleZoom();

    Rect getViewRect();
    
    /**
     * current zoom scale
     */
    float _zoomScale;
    /**
     * min zoom scale
     */
    float _minZoomScale;
    /**
     * max zoom scale
     */
    float _maxZoomScale;
    /**
     * scroll view delegate
     */
    ScrollViewDelegate* _delegate;

    Direction _direction;
    /**
     * If YES, the view is being dragged.
     */
    bool _dragging;

    /**
     * Content offset. Note that left-bottom point is the origin
     */
    Point _contentOffset;

    /**
     * Container holds scroll view contents, Sets the scrollable container object of the scroll view
     */
    Node* _container;
    /**
     * Determiens whether user touch is moved after begin phase.
     */
    bool _touchMoved;
    /**
     * max inset point to limit scrolling by touch
     */
    Point _maxInset;
    /**
     * min inset point to limit scrolling by touch
     */
    Point _minInset;
    /**
     * Determines whether the scroll view is allowed to bounce or not.
     */
    bool _bounceable;

    bool _clippingToBounds;

    /**
     * scroll speed
     */
    Point _scrollDistance;
    /**
     * Touch point
     */
    Point _touchPoint;
    /**
     * length between two fingers
     */
    float _touchLength;
    /**
     * UITouch objects to detect multitouch
     */
    Array* _touches;
    /**
     * size to clip. Node boundingBox uses contentSize directly.
     * It's semantically different what it actually means to common scroll views.
     * Hence, this scroll view will use a separate size property.
     */
    Size _viewSize;
    /**
     * max and min scale
     */
    float _minScale, _maxScale;
    /**
     * scissor rect for parent, just for restoring GL_SCISSOR_BOX
     */
    Rect _parentScissorRect;
    bool _scissorRestored;
};

// end of GUI group
/// @}

NS_CC_EXT_END

#endif /* __CCSCROLLVIEW_H__ */
