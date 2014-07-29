/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __UIWIDGET_H__
#define __UIWIDGET_H__

#include "ui/CCProtectedNode.h"
#include "ui/UILayoutParameter.h"
#include "ui/GUIDefine.h"
#include "ui/GUIExport.h"
#include "base/CCMap.h"

NS_CC_BEGIN

class EventListenerTouchOneByOne;


namespace ui {
    
typedef enum
{
    TOUCH_EVENT_BEGAN,
    TOUCH_EVENT_MOVED,
    TOUCH_EVENT_ENDED,
    TOUCH_EVENT_CANCELED
}TouchEventType;
    
typedef void (Ref::*SEL_TouchEvent)(Ref*,TouchEventType);
#define toucheventselector(_SELECTOR) (SEL_TouchEvent)(&_SELECTOR)


/**
*   @js NA
*   @lua NA
*/

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef ABSOLUTE
#undef ABSOLUTE
#endif
#endif


class CC_GUI_DLL Widget : public ProtectedNode, public LayoutParameterProtocol
{
public:
    enum class FocusDirection
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    
    enum class PositionType
    {
        ABSOLUTE,
        PERCENT
    };
    
    enum class SizeType
    {
        ABSOLUTE,
        PERCENT
    };
    
    enum class TouchEventType
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELED
    };
    
    enum class TextureResType
    {
        LOCAL = 0,
        PLIST = 1
    };
    
    enum class BrightStyle
    {
        NONE = -1,
        NORMAL,
        HIGHLIGHT
    };

    
    typedef std::function<void(Ref*,Widget::TouchEventType)> ccWidgetTouchCallback;
    /**
     * Default constructor
     */
    Widget(void);
    
    /**
     * Default destructor
     */
    virtual ~Widget();
    /**
     * Allocates and initializes a widget.
     */
    static Widget* create();

    /**
     * Sets whether the widget is enabled
     * 
     * true if the widget is enabled, widget may be touched , false if the widget is disabled, widget cannot be touched.
     *
     * The default value is true, a widget is default to enabled
     *
     * @param enabled
     */
    virtual void setEnabled(bool enabled);

    /**
     * Determines if the widget is enabled
     *
     * @return true if the widget is enabled, false if the widget is disabled.
     */
    bool isEnabled() const;

    /**
     * Sets whether the widget is bright
     *
     * The default value is true, a widget is default to bright
     *
     * @param visible   true if the widget is bright, false if the widget is dark.
     */
    void setBright(bool bright);

    /**
     * Determines if the widget is bright
     *
     * @return true if the widget is bright, false if the widget is dark.
     */
    bool isBright() const;

    /**
     * Sets whether the widget is touch enabled
     *
     * The default value is false, a widget is default to touch disabled
     *
     * @param visible   true if the widget is touch enabled, false if the widget is touch disabled.
     */
    virtual void setTouchEnabled(bool enabled);

    /**
     * To set the bright style of widget.
     *
     * @see BrightStyle
     *
     * @param style   BrightStyle::NORMAL means the widget is in normal state, BrightStyle::HIGHLIGHT means the widget is in highlight state.
     */
    void setBrightStyle(BrightStyle style);

    /**
     * Determines if the widget is touch enabled
     *
     * @return true if the widget is touch enabled, false if the widget is touch disabled.
     */
    bool isTouchEnabled() const;

    /**
     * Determines if the widget is highlighted
     *
     * @return true if the widget is highlighted, false if the widget is not hignlighted .
     */
    bool isHighlighted() const;

    /**
     * Sets whether the widget is hilighted
     *
     * The default value is false, a widget is default to not hilighted
     *
     * @param hilight   true if the widget is hilighted, false if the widget is not hilighted.
     */
    void setHighlighted(bool hilight);

    /**
     * Gets the left boundary position of this widget in parent's coordination system.
     *
     * @return The left boundary position of this widget.
     */
    CC_DEPRECATED_ATTRIBUTE float getLeftInParent(){return this->getLeftBoundary();}
    float getLeftBoundary() const;

    /**
     * Gets the bottom boundary position of this widget in parent's coordination system.
     *
     * @return The bottom boundary position of this widget.
     */
    CC_DEPRECATED_ATTRIBUTE float getBottomInParent(){return this->getBottomBoundary();}
    float getBottomBoundary() const;

    /**
     * Gets the right boundary position of this widget in parent's coordination system.
     *
     * @return The right boundary position of this widget.
     */
    CC_DEPRECATED_ATTRIBUTE float getRightInParent(){return this->getRightBoundary();}
    float getRightBoundary() const;

    /**
     * Gets the top boundary position of this widget in parent's coordination system.
     *
     * @return The top boundary position of this widget.
     */
    CC_DEPRECATED_ATTRIBUTE float getTopInParent(){return this->getTopBoundary();}
    float getTopBoundary() const;

    virtual void visit(cocos2d::Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

    /**
     * Sets the touch event target/selector of the menu item
     */
    CC_DEPRECATED_ATTRIBUTE void addTouchEventListener(Ref* target,SEL_TouchEvent selector);
    void addTouchEventListener(ccWidgetTouchCallback callback);


    /**
     * Changes the position (x,y) of the widget in OpenGL coordinates
     *
     * Usually we use p(x,y) to compose Vec2 object.
     * The original point (0,0) is at the left-bottom corner of screen.
     *
     * @param position  The position (x,y) of the widget in OpenGL coordinates
     */
    virtual void setPosition(const Vec2 &pos) override;

    /**
     * Set the percent(x,y) of the widget in OpenGL coordinates
     *
     * @param percent  The percent (x,y) of the widget in OpenGL coordinates
     */
    void setPositionPercent(const Vec2 &percent);

    /**
     * Gets the percent (x,y) of the widget in OpenGL coordinates
     *
     * @see setPosition(const Vec2&)
     *
     * @return The percent (x,y) of the widget in OpenGL coordinates
     */
    const Vec2& getPositionPercent()const;

    /**
     * Changes the position type of the widget
     *
     * @see PositionType
     *
     * @param type  the position type of widget
     */
    void setPositionType(PositionType type);

    /**
     * Gets the position type of the widget
     *
     * @see PositionType
     *
     * @return type  the position type of widget
     */
    PositionType getPositionType() const;

    /**
     * Sets whether the widget should be flipped horizontally or not.
     *
     * @param bFlippedX true if the widget should be flipped horizaontally, false otherwise.
     */
    virtual void setFlippedX(bool flippedX);

    /**
     * Returns the flag which indicates whether the widget is flipped horizontally or not.
     *
     * It only flips the texture of the widget, and not the texture of the widget's children.
     * Also, flipping the texture doesn't alter the anchorPoint.
     * If you want to flip the anchorPoint too, and/or to flip the children too use:
     * widget->setScaleX(sprite->getScaleX() * -1);
     *
     * @return true if the widget is flipped horizaontally, false otherwise.
     */
    virtual bool isFlippedX()const{return _flippedX;};

    /**
     * Sets whether the widget should be flipped vertically or not.
     *
     * @param bFlippedY true if the widget should be flipped vertically, flase otherwise.
     */
    virtual void setFlippedY(bool flippedY);

    /**
     * Return the flag which indicates whether the widget is flipped vertically or not.
     *
     * It only flips the texture of the widget, and not the texture of the widget's children.
     * Also, flipping the texture doesn't alter the anchorPoint.
     * If you want to flip the anchorPoint too, and/or to flip the children too use:
     * widget->setScaleY(widget->getScaleY() * -1);
     *
     * @return true if the widget is flipped vertically, flase otherwise.
     */
    virtual bool isFlippedY()const{return _flippedY;};

    /** @deprecated Use isFlippedX() instead */
    CC_DEPRECATED_ATTRIBUTE bool isFlipX() { return isFlippedX(); };
    /** @deprecated Use setFlippedX() instead */
    CC_DEPRECATED_ATTRIBUTE void setFlipX(bool flipX) { setFlippedX(flipX); };
    /** @deprecated Use isFlippedY() instead */
    CC_DEPRECATED_ATTRIBUTE bool isFlipY() { return isFlippedY(); };
    /** @deprecated Use setFlippedY() instead */
    CC_DEPRECATED_ATTRIBUTE void setFlipY(bool flipY) { setFlippedY(flipY); };

    /*
     * Checks a point if in parent's area.
     *
     * @param point
     *
     * @return true if the point is in parent's area, flase otherwise.
     */
    CC_DEPRECATED_ATTRIBUTE bool clippingParentAreaContainPoint(const Vec2 &pt){return this->isClippingParentContainsPoint(pt);}
    bool isClippingParentContainsPoint(const Vec2& pt);

    /*
     * Gets the touch began point of widget when widget is selected.
     *
     * @return the touch began point.
     */
    CC_DEPRECATED_ATTRIBUTE const Vec2& getTouchStartPos()const{return this->getTouchBeganPosition();}
    const Vec2& getTouchBeganPosition()const;

    /*
     * Gets the touch move point of widget when widget is selected.
     *
     * @return the touch move point.
     */
    CC_DEPRECATED_ATTRIBUTE const Vec2& getTouchMovePos()const{ return this->getTouchMovePosition();}
    const Vec2& getTouchMovePosition()const;

    /*
     * Gets the touch end point of widget when widget is selected.
     *
     * @return the touch end point.
     */
    CC_DEPRECATED_ATTRIBUTE const Vec2& getTouchEndPos()const{return this->getTouchEndPosition();}
    const Vec2& getTouchEndPosition()const;

    /**
     * Changes the size that is widget's size
     *
     * @param size that is widget's size
     */
    CC_DEPRECATED_ATTRIBUTE virtual void setSize(const Size &size);
    virtual void setContentSize(const Size& contentSize) override;

    /**
     * Changes the percent that is widget's percent size
     *
     * @param percent that is widget's percent size
     */
    virtual void setSizePercent(const Vec2 &percent);

    /**
     * Changes the size type of widget.
     *
     * @see SizeType
     *
     * @param type that is widget's size type
     */
    void setSizeType(SizeType type);

    /**
     * Gets the size type of widget.
     *
     * @see SizeType
     *
     * @param type that is widget's size type
     */
    SizeType getSizeType() const;

    /**
     * Returns size of widget
     *
     * @return size
     */
    CC_DEPRECATED_ATTRIBUTE const Size& getSize() const;
    
    const Size& getCustomSize() const;
    
    virtual const Size& getLayoutSize() {return _contentSize;};

    /**
     * Returns size percent of widget
     *
     * @return size percent
     */
    const Vec2& getSizePercent() const;

    /**
     * Checks a point if is in widget's space
     *
     * @param point
     *
     * @return true if the point is in widget's space, flase otherwise.
     */
    virtual bool hitTest(const Vec2 &pt);

    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent);
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent);

    /**
     * Sets a LayoutParameter to widget.
     *
     * @see LayoutParameter
     *
     * @param LayoutParameter pointer
     *
     * @param type  Relative or Linear
     */
    void setLayoutParameter(LayoutParameter* parameter);

    /**
     * Gets LayoutParameter of widget.
     *
     * @see LayoutParameter
     *
     * @param type  Relative or Linear
     *
     * @return LayoutParameter
     */
    LayoutParameter* getLayoutParameter()const override;
    CC_DEPRECATED_ATTRIBUTE LayoutParameter* getLayoutParameter(LayoutParameter::Type type);


    /**
     *
     * Note: when you set _ignoreSize to true, no matther you call setContentSize or not, 
     * the widget size is always equal to the return value of the member function getVirtualRendererSize.
     *
     * @param ignore, set member variabl _ignoreSize to ignore
     */
    virtual void ignoreContentAdaptWithSize(bool ignore);

    /**
     * Query whether the widget ignores user deinfed content size or not
     *
     * @return bool
     */
    bool isIgnoreContentAdaptWithSize() const;

    /**
     * Gets world position of widget.
     *
     * @return world position of widget.
     */
    Vec2 getWorldPosition()const;

    /**
     * Gets the Virtual Renderer of widget.
     *
     * For example, a button's Virtual Renderer is it's texture renderer.
     *
     * @return Node pointer.
     */
    virtual Node* getVirtualRenderer();


    virtual const Size& getVirtualRendererSize() const;
    

    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;

    Widget* clone();

    virtual void onEnter() override;
    virtual void onExit() override;

    void updateSizeAndPosition();

    void updateSizeAndPosition(const Size& parentSize);
    
    /*temp action*/
    void setActionTag(int tag);
	int getActionTag()const;
    
    /**
     *@return  whether the widget is focused or not
     */
    bool isFocused()const;
    
    /**
     *@param focus  pass true to let the widget get focus or pass false to let the widget lose focus
     *@return void
     */
    void setFocused(bool focus);
    
    /**
     *@return true represent the widget could accept focus, false represent the widget couldn't accept focus
     */
    bool isFocusEnabled()const;
    
    /**
     *@param enable pass true/false to enable/disable the focus ability of a widget
     *@return void
     */
    void setFocusEnabled(bool enable);
    
    /**
     *  When a widget is in a layout, you could call this method to get the next focused widget within a specified direction. 
     *  If the widget is not in a layout, it will return itself
     *@param dir the direction to look for the next focused widget in a layout
     *@param current  the current focused widget
     *@return the next focused widget in a layout
     */
    virtual Widget* findNextFocusedWidget(FocusDirection direction, Widget* current);
    
    /**
     * when a widget calls this method, it will get focus immediately.
     */
    void requestFocus();

    /**
     * no matter what widget object you call this method on , it will return you the exact one focused widget
     * @param isWidget  if your set isWidget to true, it will return the _realFocusedWidget which is always a widget
     *                  otherwise, it will return a widget or a layout
     */
    CC_DEPRECATED_ATTRIBUTE Widget* getCurrentFocusedWidget(bool isWidget){
        CC_UNUSED_PARAM(isWidget);
        return getCurrentFocusedWidget();
    }

    Widget* getCurrentFocusedWidget()const;
    /*
     *  call this method with parameter true to enable the Android Dpad focus navigation feature
     *@param enable  set true to enable dpad focus navigation, otherwise disenable dpad focus navigation
     */
    static void enableDpadNavigation(bool enable);

    /**
     * When a widget lose/get focus, this method will be called. Be Caution when you provide your own version, 
     * you must call widget->setFocused(true/false) to change the focus state of the current focused widget;
     */
    std::function<void(Widget*,Widget*)> onFocusChanged;
    /**
     * use this function to manually specify the next focused widget regards to each direction
     */
    std::function<Widget*(FocusDirection)> onNextFocusedWidget;

CC_CONSTRUCTOR_ACCESS:

    //initializes state of widget.
    virtual bool init() override;

    /*
     * Sends the touch event to widget's parent
     * @param  event  the touch event type, it could be BEGAN/MOVED/CANCELED/ENDED
     * @param parent
     * @param point
     */
    virtual void interceptTouchEvent(TouchEventType event, Widget* sender, Touch *touch);
    friend class PageView;
    /**
     * This method is called when a focus change event happens
     *@param widgetLostFocus  The widget which lose its focus
     *@param widgetGetFocus  The widget whihc get its focus
     *@return void
     */
    void onFocusChange(Widget* widgetLostFocus, Widget* widgetGetFocus);
    
    /**
     * Dispatch a EventFocus through a EventDispatcher
     *@param widgetLoseFocus  The widget which lose its focus
     *@param widgetGetFocus he widget whihc get its focus
     *@return void
     */
    void  dispatchFocusEvent(Widget* widgetLoseFocus, Widget* widgetGetFocus);
    
protected:
    //call back function called when size changed.
    virtual void onSizeChanged();

    //initializes renderer of widget.
    virtual void initRenderer();

    //call back function called widget's state changed to normal.
    virtual void onPressStateChangedToNormal();
    //call back function called widget's state changed to selected.
    virtual void onPressStateChangedToPressed();
    //call back function called widget's state changed to dark.
    virtual void onPressStateChangedToDisabled();

    void pushDownEvent();
    void moveEvent();

    virtual void releaseUpEvent();
    virtual void cancelUpEvent();

    virtual void updateFlippedX(){};
    virtual void updateFlippedY(){};
    virtual void adaptRenderers(){};
    
    void copyProperties(Widget* model);
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
    virtual void copyClonedWidgetChildren(Widget* model);
    
    Widget* getWidgetParent();
    void updateContentSizeWithTextureSize(const Size& size);
    
    bool isAncestorsEnabled();
    Widget* getAncensterWidget(Node* node);
    bool isAncestorsVisible(Node* node);

    void cleanupWidget();

protected:
    bool _enabled;
    bool _bright;
    bool _touchEnabled;
    bool _highlight;
    bool _reorderWidgetChildDirty;
    bool _affectByClipping;
    bool _ignoreSize;

    BrightStyle _brightStyle;
    SizeType _sizeType;
    PositionType _positionType;

    //used for search widget by action tag in UIHelper class
    int _actionTag;

    Size _customSize;

    Vec2 _sizePercent;
    Vec2 _positionPercent;

    bool _hitted;
    EventListenerTouchOneByOne* _touchListener;
    Vec2 _touchBeganPosition;
    Vec2 _touchMovePosition;
    Vec2 _touchEndPosition;

    bool _flippedX;
    bool _flippedY;

    //use map to enble switch back and forth for user layout parameters
    Map<int,LayoutParameter*> _layoutParameterDictionary;
    LayoutParameter::Type _layoutParameterType;

    bool _focused;
    bool _focusEnabled;
    /**
     * store the only one focued widget
     */
    static Widget *_focusedWidget;  //both layout & widget will be stored in this variable

    Ref*       _touchEventListener;
    #if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #elif _MSC_VER >= 1400 //vs 2005 or higher
    #pragma warning (push)
    #pragma warning (disable: 4996)
    #endif
    SEL_TouchEvent    _touchEventSelector;
    #if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #pragma GCC diagnostic warning "-Wdeprecated-declarations"
    #elif _MSC_VER >= 1400 //vs 2005 or higher
    #pragma warning (pop)
    #endif
    ccWidgetTouchCallback _touchEventCallback;
private:
    class FocusNavigationController;
    static FocusNavigationController* _focusNavigationController;
};
}

NS_CC_END

#endif /* defined(__Widget__) */
