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

typedef enum {
	kCCScrollViewDirectionNone = -1,
    kCCScrollViewDirectionHorizontal = 0,
    kCCScrollViewDirectionVertical,
    kCCScrollViewDirectionBoth
} CCScrollViewDirection;

class CCScrollView;

class CCScrollViewDelegate
{
public:
    virtual ~CCScrollViewDelegate() {}
    virtual void scrollViewDidScroll(CCScrollView* view) = 0;
    virtual void scrollViewDidZoom(CCScrollView* view) = 0;
};


/**
 * ScrollView support for cocos2d for iphone.
 * It provides scroll view functionalities to cocos2d projects natively.
 */
class CCScrollView : public CCLayer
{
public:
    CCScrollView();
    virtual ~CCScrollView();

    bool init();
    virtual void registerWithTouchDispatcher();

    /**
     * Returns an autoreleased scroll view object.
     *
     * @param size view size
     * @param container parent object
     * @return autoreleased scroll view object
     */
    static CCScrollView* create(CCSize size, CCNode* container = NULL);

    /**
     * Returns an autoreleased scroll view object.
     *
     * @param size view size
     * @param container parent object
     * @return autoreleased scroll view object
     */
    static CCScrollView* create();

    /**
     * Returns a scroll view object
     *
     * @param size view size
     * @param container parent object
     * @return scroll view object
     */
    bool initWithViewSize(CCSize size, CCNode* container = NULL);


    /**
     * Sets a new content offset. It ignores max/min offset. It just sets what's given. (just like UIKit's UIScrollView)
     *
     * @param offset new offset
     * @param If YES, the view scrolls to the new offset
     */
    void setContentOffset(CCPoint offset, bool animated = false);
    CCPoint getContentOffset();
    /**
     * Sets a new content offset. It ignores max/min offset. It just sets what's given. (just like UIKit's UIScrollView)
     * You can override the animation duration with this method.
     *
     * @param offset new offset
     * @param animation duration
     */
    void setContentOffsetInDuration(CCPoint offset, float dt); 

    void setZoomScale(float s);
    /**
     * Sets a new scale and does that for a predefined duration.
     *
     * @param s a new scale vale
     * @param animated if YES, scaling is animated
     */
    void setZoomScale(float s, bool animated);

    float getZoomScale();

    /**
     * Sets a new scale for container in a given duration.
     *
     * @param s a new scale value
     * @param animation duration
     */
    void setZoomScaleInDuration(float s, float dt);
    /**
     * Returns the current container's minimum offset. You may want this while you animate scrolling by yourself
     */
    CCPoint minContainerOffset();
    /**
     * Returns the current container's maximum offset. You may want this while you animate scrolling by yourself
     */
    CCPoint maxContainerOffset(); 
    /**
     * Determines if a given node's bounding box is in visible bounds
     *
     * @return YES if it is in visible bounds
     */
    bool isNodeVisible(CCNode * node);
    /**
     * Provided to make scroll view compatible with SWLayer's pause method
     */
    void pause(CCObject* sender);
    /**
     * Provided to make scroll view compatible with SWLayer's resume method
     */
    void resume(CCObject* sender);


    bool isDragging() {return _dragging;}
    bool isTouchMoved() { return _touchMoved; }
    bool isBounceable() { return _bounceable; }
    void setBounceable(bool bBounceable) { _bounceable = bBounceable; }

    /**
     * size to clip. CCNode boundingBox uses contentSize directly.
     * It's semantically different what it actually means to common scroll views.
     * Hence, this scroll view will use a separate size property.
     */
    CCSize getViewSize() { return _viewSize; } 
    void setViewSize(CCSize size);

    CCNode * getContainer();
    void setContainer(CCNode * pContainer);

    /**
     * direction allowed to scroll. CCScrollViewDirectionBoth by default.
     */
    CCScrollViewDirection getDirection() { return _direction; }
    virtual void setDirection(CCScrollViewDirection eDirection) { _direction = eDirection; }

    CCScrollViewDelegate* getDelegate() { return _delegate; }
    void setDelegate(CCScrollViewDelegate* pDelegate) { _delegate = pDelegate; }

    /** override functions */
    // optional
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    virtual void setContentSize(const CCSize & size);
    virtual const CCSize& getContentSize() const;

	void updateInset();
    /**
     * Determines whether it clips its children or not.
     */
    bool isClippingToBounds() { return _clippingToBounds; }
    void setClippingToBounds(bool bClippingToBounds) { _clippingToBounds = bClippingToBounds; }

    virtual void visit();
    virtual void addChild(CCNode * child, int zOrder, int tag);
    virtual void addChild(CCNode * child, int zOrder);
    virtual void addChild(CCNode * child);
    void setTouchEnabled(bool e);
private:
    /**
     * Relocates the container at the proper offset, in bounds of max/min offsets.
     *
     * @param animated If YES, relocation is animated
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
    void stoppedAnimatedScroll(CCNode* node);
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

protected:
    CCRect getViewRect();
    
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
    CCScrollViewDelegate* _delegate;

    CCScrollViewDirection _direction;
    /**
     * If YES, the view is being dragged.
     */
    bool _dragging;

    /**
     * Content offset. Note that left-bottom point is the origin
     */
    CCPoint _contentOffset;

    /**
     * Container holds scroll view contents, Sets the scrollable container object of the scroll view
     */
    CCNode* _container;
    /**
     * Determiens whether user touch is moved after begin phase.
     */
    bool _touchMoved;
    /**
     * max inset point to limit scrolling by touch
     */
    CCPoint _maxInset;
    /**
     * min inset point to limit scrolling by touch
     */
    CCPoint _minInset;
    /**
     * Determines whether the scroll view is allowed to bounce or not.
     */
    bool _bounceable;

    bool _clippingToBounds;

    /**
     * scroll speed
     */
    CCPoint _scrollDistance;
    /**
     * Touch point
     */
    CCPoint _touchPoint;
    /**
     * length between two fingers
     */
    float _touchLength;
    /**
     * UITouch objects to detect multitouch
     */
    CCArray* _touches;
    /**
     * size to clip. CCNode boundingBox uses contentSize directly.
     * It's semantically different what it actually means to common scroll views.
     * Hence, this scroll view will use a separate size property.
     */
    CCSize _viewSize;
    /**
     * max and min scale
     */
    float _minScale, _maxScale;
    /**
     * scissor rect for parent, just for restoring GL_SCISSOR_BOX
     */
    CCRect _parentScissorRect;
    bool _scissorRestored;
};

// end of GUI group
/// @}

NS_CC_EXT_END

#endif /* __CCSCROLLVIEW_H__ */
