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

#include "2d/CCProtectedNode.h"
#include "ui/UILayoutParameter.h"
#include "ui/GUIDefine.h"
#include "ui/GUIExport.h"
#include "ui/UIWidget.h"
#include "base/CCMap.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

class EventListenerTouchOneByOne;
class Camera;

namespace ui {
    class LayoutComponent;

/**
 * Touch event type.
 *@deprecated use `Widget::TouchEventType` instead
 */
typedef enum
{
    TOUCH_EVENT_BEGAN,
    TOUCH_EVENT_MOVED,
    TOUCH_EVENT_ENDED,
    TOUCH_EVENT_CANCELED
}TouchEventType;
    
/**
 * Touch event callback.
 *@deprecated use `Widget::ccWidgetTouchCallback` instead
 */
typedef void (Ref::*SEL_TouchEvent)(Ref*,TouchEventType);
#define toucheventselector(_SELECTOR) (SEL_TouchEvent)(&_SELECTOR)


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef ABSOLUTE
#undef ABSOLUTE
#endif
#endif

/**
 *@brief Base class for all ui widgets.
 * This class inherent from `ProtectedNode` and `LayoutParameterProtocol`.
 * If you want to implements your own ui widget, you should subclass it.
 */
class CC_GUI_DLL Widget : public ProtectedNode, public LayoutParameterProtocol
{
public:
    /**
     * Widget focus direction.
     */
    enum class FocusDirection
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    
    /**
     * Widget position type for layout.
     */
    enum class PositionType
    {
        ABSOLUTE,
        PERCENT
    };
    
    /**
     * Widget size type for layout.
     */
    enum class SizeType
    {
        ABSOLUTE,
        PERCENT
    };
    
    /**
     * Touch event type.
     */
    enum class TouchEventType
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELED
    };
    
    /**
     * Texture resource type.
     * - LOCAL:  It means the texture is loaded from image.
     * - PLIST: It means the texture is loaded from texture atlas.
     */
    enum class TextureResType
    {
        LOCAL = 0,
        PLIST = 1
    };
    
    /**
     * Widget bright style.
     */
    enum class BrightStyle
    {
        NONE = -1,
        NORMAL,
        HIGHLIGHT
    };

    
    /**
     * Widget touch event callback.
     */
    typedef std::function<void(Ref*,Widget::TouchEventType)> ccWidgetTouchCallback;
    /**
     * Widget click event callback.
     */
    typedef std::function<void(Ref*)> ccWidgetClickCallback;
    /**
     * Widget custom event callback.
     * It is mainly used together with Cocos Studio.
     */
    typedef std::function<void(Ref*, int)> ccWidgetEventCallback;
    /**
     * Default constructor
     * @js ctor
     * @lua new
     */
    Widget(void);
    
    /**
     * Default destructor
     * @js NA
     * @lua NA
     */
    virtual ~Widget();
    /**
     * Create and return a empty Widget instance pointer.
     */
    static Widget* create();

    /**
     * Sets whether the widget is enabled
     * 
     * true if the widget is enabled, widget may be touched , false if the widget is disabled, widget cannot be touched.
     *
     * Note: If you want to change the widget's appearance  to disabled state, you should also call  `setBright(false)`.
     *
     * The default value is true, a widget is default to enable touch.
     *
     * @param enabled Set to true to enable touch, false otherwise.
     */
    virtual void setEnabled(bool enabled);

    /**
     * Determines if the widget is enabled or not.
     *
     * @return true if the widget is enabled, false if the widget is disabled.
     */
    bool isEnabled() const;

    /**
     * Sets whether the widget is bright
     *
     * The default value is true, a widget is default to bright
     *
     * @param bright   true if the widget is bright, false if the widget is dark.
     */
    void setBright(bool bright);

    /**
     * Determines if the widget is bright
     *
     * @return true if the widget is bright, false if the widget is dark.
     */
    bool isBright() const;

    /**
     * Sets whether the widget is touch enabled.
     *
     * The default value is false, a widget is default to touch disabled.
     *
     * @param enabled   True if the widget is touch enabled, false if the widget is touch disabled.
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
     * @return true if the widget is highlighted, false if the widget is not highlighted.
     */
    bool isHighlighted() const;

    /**
     * Sets whether the widget is highlighted
     *
     * The default value is false, a widget is default to not highlighted
     *
     * @param highlight   true if the widget is highlighted, false if the widget is not highlighted.
     */
    void setHighlighted(bool highlight);

    /**
     * Gets the left boundary position of this widget in parent's coordination system.
     * @deprecated use `getLeftBoundary` instead.
     * @return The left boundary position of this widget.
     */
    CC_DEPRECATED_ATTRIBUTE float getLeftInParent(){return this->getLeftBoundary();}

    /**
     * Gets the left boundary position of this widget in parent's coordination system.
     * @return The left boundary position of this widget.
     */
    float getLeftBoundary() const;

    /**
     * Gets the bottom boundary position of this widget in parent's coordination system.
     * @deprecated use `getBottomBoundary` instead.
     * @return The bottom boundary position of this widget.
     */
    CC_DEPRECATED_ATTRIBUTE float getBottomInParent(){return this->getBottomBoundary();}
    /**
     * Gets the bottom boundary position of this widget in parent's coordination system.
     * @return The bottom boundary position of this widget.
     */
    float getBottomBoundary() const;

    /**
     * Gets the right boundary position of this widget in parent's coordination system.
     * @deprecated use `getRightBoundary` instead.
     * @return The right boundary position of this widget.
     */
    CC_DEPRECATED_ATTRIBUTE float getRightInParent(){return this->getRightBoundary();}
    /**
     * Gets the right boundary position of this widget in parent's coordination system.
     * @return The right boundary position of this widget.
     */
    float getRightBoundary() const;

    /**
     * Gets the top boundary position of this widget in parent's coordination system.
     * @deprecated use `getTopBoundary` instead.
     * @return The top boundary position of this widget.
     */
    CC_DEPRECATED_ATTRIBUTE float getTopInParent(){return this->getTopBoundary();}
    /**
     * Gets the top boundary position of this widget in parent's coordination system.
     * @return The top boundary position of this widget.
     */
    float getTopBoundary() const;

    /**
     * @js NA
     */
    virtual void visit(cocos2d::Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

    /**
     * Sets the touch event target/selector to the widget
     */
    CC_DEPRECATED_ATTRIBUTE void addTouchEventListener(Ref* target,SEL_TouchEvent selector);
    /**
     * Set a callback to touch vent listener.
     *@param callback  The callback in `ccWidgetEventCallback.`
     */
    void addTouchEventListener(const ccWidgetTouchCallback& callback);
    
    /**
     * Set a click event handler to the widget.
     * @param callback The callback in `ccWidgetClickCallback`.
     */
    void addClickEventListener(const ccWidgetClickCallback& callback);
    /**
     * Set a event handler to the widget in order to use cocostudio editor and framework
     * @param callback The callback in `ccWidgetEventCallback`.
     * @lua NA
     */
    virtual void addCCSEventListener(const ccWidgetEventCallback& callback);
    /**/

    /**
     * Changes the position (x,y) of the widget in OpenGL coordinates
     *
     * Usually we use p(x,y) to compose a Vec2 object.
     * The original point (0,0) is at the left-bottom corner of screen.
     *
     * @param pos  The position (x,y) of the widget in OpenGL coordinates
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
    const Vec2& getPositionPercent();

    /**
     * Changes the position type of the widget
     *
     * @see `PositionType`
     *
     * @param type  the position type of widget
     */
    void setPositionType(PositionType type);

    /**
     * Gets the position type of the widget
     *
     * @see `PositionType`
     *
     * @return type  the position type of widget
     */
    PositionType getPositionType() const;

    /**
     * Sets whether the widget should be flipped horizontally or not.
     *
     * @param flippedX true if the widget should be flipped horizontally, false otherwise.
     */
    virtual void setFlippedX(bool flippedX);

    /**
     * Returns the flag which indicates whether the widget is flipped horizontally or not.
     *
     * It not only flips the texture of the widget, but also the texture of the widget's children.
     * Also, flipping relies on widget's anchor point.
     * Internally, it just use setScaleX(-1) to flip the widget.
     *
     * @return true if the widget is flipped horizontally, false otherwise.
     */
    virtual bool isFlippedX()const{return _flippedX;};

    /**
     * Sets whether the widget should be flipped vertically or not.
     *
     * @param flippedY true if the widget should be flipped vertically, false otherwise.
     */
    virtual void setFlippedY(bool flippedY);

    /**
     * Return the flag which indicates whether the widget is flipped vertically or not.
     *
     * It not only flips the texture of the widget, but also the texture of the widget's children.
     * Also, flipping relies on widget's anchor point.
     * Internally, it just use setScaleY(-1) to flip the widget.
     *
     * @return true if the widget is flipped vertically, false otherwise.
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

    //override the setScale function of Node
    virtual void setScaleX(float scaleX) override;
    virtual void setScaleY(float scaleY) override;
    virtual void setScale(float scale) override;
    virtual void setScale(float scalex, float scaley) override;
    using Node::setScaleZ;
    virtual float getScaleX() const override;
    virtual float getScaleY() const override;
    virtual float getScale() const override;
    using Node::getScaleZ;
    
    /**
     * Checks a point if in parent's area.
     *
     * @param pt A point in `Vec2`.
     * @deprecated  use `isClippingParentContainsPoint` instead.
     * @return true if the point is in parent's area, false otherwise.
     */
    CC_DEPRECATED_ATTRIBUTE bool clippingParentAreaContainPoint(const Vec2 &pt){return this->isClippingParentContainsPoint(pt);}

    /**
     * Checks a point if in parent's area.
     *
     * @param pt A point in `Vec2`.
     * @return true if the point is in parent's area, false otherwise.
     */
    bool isClippingParentContainsPoint(const Vec2& pt);

    /**
     * Gets the touch began point of widget when widget is selected.
     * @deprecated use `getTouchBeganPosition` instead.
     * @return the touch began point.
     */
    CC_DEPRECATED_ATTRIBUTE const Vec2& getTouchStartPos()const{return this->getTouchBeganPosition();}
    /**
     * Gets the touch began point of widget when widget is selected.
     * @return the touch began point.
     */
    const Vec2& getTouchBeganPosition()const;

    /*
     * Gets the touch move point of widget when widget is selected.
     * @deprecated use `getTouchMovePosition` instead.
     * @return the touch move point.
     */
    CC_DEPRECATED_ATTRIBUTE const Vec2& getTouchMovePos()const{ return this->getTouchMovePosition();}
    /*
     * Gets the touch move point of widget when widget is selected.
     * @return the touch move point.
     */
    const Vec2& getTouchMovePosition()const;

    /*
     * Gets the touch end point of widget when widget is selected.
     * @deprecated use `getTouchEndPosition` instead.
     * @return the touch end point.
     */
    CC_DEPRECATED_ATTRIBUTE const Vec2& getTouchEndPos()const{return this->getTouchEndPosition();}
    /*
     * Gets the touch end point of widget when widget is selected.
     * @return the touch end point.
     */
    const Vec2& getTouchEndPosition()const;

    /**
     * Changes the size that is widget's size
     * @deprecated use `setContentSize` instead.
     * @param size that is widget's size
     */
    CC_DEPRECATED_ATTRIBUTE virtual void setSize(const Size &size);
    /**
     * Changes the size that is widget's size
     * @param contentSize A content size in `Size`.
     */
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
     * @see `SizeType`
     *
     * @param type that is widget's size type
     */
    void setSizeType(SizeType type);

    /**
     * Gets the size type of widget.
     *
     * @see `SizeType`
     */
    SizeType getSizeType() const;

    /**
     * Get the size of widget
     *
     * @return Widget content size.
     */
    CC_DEPRECATED_ATTRIBUTE const Size& getSize() const;
    
    /**
     * Get the user defined widget size.
     *@return User defined size.
     */
    const Size& getCustomSize() const;
    
    /**
     * Get the content size of widget.
     * @warning This API exists mainly for keeping back compatibility.
     * @return 
     */
    virtual const Size& getLayoutSize() {return _contentSize;};

    /**
     * Get size percent of widget.
     *
     * @return Percent size.
     */
    const Vec2& getSizePercent();

    /**
     * Checks a point is in widget's content space.
     * This function is used for determining touch area of widget.
     *
     * @param pt        The point in `Vec2`.
     * @param camera    The camera look at widget, used to convert GL screen point to near/far plane.
     * @param p         Point to a Vec3 for store the intersect point, if don't need them set to nullptr.
     * @return true if the point is in widget's content space, false otherwise.
     */
    virtual bool hitTest(const Vec2 &pt, const Camera* camera, Vec3 *p) const;

    /**
     * A callback which will be called when touch began event is issued.
     *@param touch The touch info.
     *@param unusedEvent The touch event info.
     *@return True if user want to handle touches, false otherwise.
     */
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);

    /**
     * A callback which will be called when touch moved event is issued.
     *@param touch The touch info.
     *@param unusedEvent The touch event info.
     */
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent);

    /**
     * A callback which will be called when touch ended event is issued.
     *@param touch The touch info.
     *@param unusedEvent The touch event info.
     */
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);

    /**
     * A callback which will be called when touch cancelled event is issued.
     *@param touch The touch info.
     *@param unusedEvent The touch event info.
     */
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent);

    /**
     * Sets a LayoutParameter to widget.
     *
     * @see LayoutParameter
     * @param parameter LayoutParameter pointer
     */
    void setLayoutParameter(LayoutParameter* parameter);

    /**
     * Gets LayoutParameter of widget.
     *
     * @see LayoutParameter
     * @return LayoutParameter
     */
    LayoutParameter* getLayoutParameter()const override;
    /**
     * Gets LayoutParameter of widget.
     *
     * @see LayoutParameter
     * @deprecated use `getLayoutParameter()` instead.
     * @param type  Relative or Linear
     * @return LayoutParameter
     */
    CC_DEPRECATED_ATTRIBUTE LayoutParameter* getLayoutParameter(LayoutParameter::Type type);


    /**
     * Toggle whether ignore user defined content size for widget.
     * Set true will ignore user defined content size which means 
     * the widget size is always equal to the return value of `getVirtualRendererSize`.
     *
     * @param ignore set member variable _ignoreSize to ignore
     */
    virtual void ignoreContentAdaptWithSize(bool ignore);

    /**
     * Query whether the widget ignores user defined content size or not
     *
     * @return True means ignore user defined content size, false otherwise.
     */
    bool isIgnoreContentAdaptWithSize() const;

    /**
     * Gets position of widget in world space.
     *
     * @return Position of widget in world space.
     */
    Vec2 getWorldPosition()const;

    /**
     * Gets the inner Renderer node of widget.
     *
     * For example, a button's Virtual Renderer is it's texture renderer.
     *
     * @return Node pointer.
     */
    virtual Node* getVirtualRenderer();


    /**
     *  Get the virtual renderer's size
     *@return Widget virtual renderer size.
     */
    virtual Size getVirtualRendererSize() const;
    

    /**
     * Returns the string representation of widget class name
     * @return get the class description.
     */
    virtual std::string getDescription() const override;

    /**
     * Create a new widget copy of the original one.
     * @return A cloned widget copy of original.
     */
    Widget* clone();
    /**
     * @lua NA
     */
    virtual void onEnter() override;
    
    /**
     * @lua NA
     */
    virtual void onExit() override;

    /**
     * Update all children's contents size and position recursively.
     * @see `updateSizeAndPosition(const Size&)`
     */
    void updateSizeAndPosition();

    /**
     * Update all children's contents size and position recursively.
     */
    void updateSizeAndPosition(const Size& parentSize);
    
    /**
     * Set the tag of action.
     *@param tag  A integer tag value.
     */
    void setActionTag(int tag);

    /**
     * Get the action tag.
     *@return Action tag.
     */
    int getActionTag()const;
    
    /**
     * @brief Allow widget touch events to propagate to its parents. Set false will disable propagation
     * @param isPropagate  True to allow propagation, false otherwise.
     * @since v3.3
     */
    void setPropagateTouchEvents(bool isPropagate);
    
    /**
     * Return whether the widget is propagate touch events to its parents or not
     * @return whether touch event propagation is allowed or not.
     * @since v3.3
     */
     
    bool isPropagateTouchEvents()const;
    
    /**
     * Toggle widget swallow touch option.
     * @brief Specify widget to swallow touches or not
     * @param swallow True to swallow touch, false otherwise.
     * @since v3.3
     */
    void setSwallowTouches(bool swallow);
    
    /**
     * Return whether the widget is swallowing touch or not
     * @return Whether touch is swallowed.
     * @since v3.3
     */
    bool isSwallowTouches()const;
    
    /**
     * Query whether widget is focused or not.
     *@return  whether the widget is focused or not
     */
    bool isFocused()const;
    
    /**
     * Toggle widget focus status.
     *@param focus  pass true to let the widget get focus or pass false to let the widget lose focus
     *@return void
     */
    void setFocused(bool focus);
    
    /**
     * Query widget's focus enable state.
     *@return true represent the widget could accept focus, false represent the widget couldn't accept focus
     */
    bool isFocusEnabled()const;
    
    /**
     * Allow widget to accept focus.
     *@param enable pass true/false to enable/disable the focus ability of a widget
     *@return void
     */
    void setFocusEnabled(bool enable);
    
    /**
     *  When a widget is in a layout, you could call this method to get the next focused widget within a specified direction. 
     *  If the widget is not in a layout, it will return itself
     *@param direction the direction to look for the next focused widget in a layout
     *@param current  the current focused widget
     *@return the next focused widget in a layout
     */
    virtual Widget* findNextFocusedWidget(FocusDirection direction, Widget* current);
    
    /**
     * when a widget calls this method, it will get focus immediately.
     */
    void requestFocus();

    /**
     * Return a current focused widget in your UI scene.
     * No matter what widget object you call this method on , it will return you the exact one focused widget.
     * @param isWidget  if your set isWidget to true, it will return the _realFocusedWidget which is always a widget
     *                  otherwise, it will return a widget or a layout.
     * @deprecated use `getCurrentFocusedWidget` instead.
     */
    CC_DEPRECATED_ATTRIBUTE Widget* getCurrentFocusedWidget(bool isWidget){
        CC_UNUSED_PARAM(isWidget);
        return getCurrentFocusedWidget();
    }

    /**
     * Return a current focused widget in your UI scene.
     * No matter what widget object you call this method on , it will return you the exact one focused widget.
     */
    static Widget* getCurrentFocusedWidget();

    /*
     *  Call this method with parameter true to enable the Android Dpad focus navigation feature
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
    
    /**
     *Toggle use unify size.
     *@param enable True to use unify size, false otherwise.
     *@return void
     */
    void setUnifySizeEnabled(bool enable);

    /**
     * Query whether unify size enable state. 
     *@return true represent the widget use Unify Size, false represent the widget couldn't use Unify Size
     */
    bool isUnifySizeEnabled()const;

    /**
     * Set callback name.
     *@param callbackName A string representation of callback name.
     */
    void setCallbackName(const std::string& callbackName) { _callbackName = callbackName; }


    /**
     * Query callback name.
     *@return The callback name.
     */
    const std::string& getCallbackName() const{ return _callbackName; }
    
    /**
     * Set callback type.
     * @param callbackType A string representation of callback type.
     */
    void setCallbackType(const std::string& callbackType) { _callbackType = callbackType; }

    /**
     * Query callback type.
     *@return Callback type string.
     */
    const std::string& getCallbackType() const{ return _callbackType; }

    /**
     * Toggle layout component enable.
     *@param enable Layout Component of a widget
     *@return void
     */
    void setLayoutComponentEnabled(bool enable);

    /**
     * Query whether layout component is enabled or not. 
     *@return true represent the widget use Layout Component, false represent the widget couldn't use Layout Component.
     */
    bool isLayoutComponentEnabled()const;

CC_CONSTRUCTOR_ACCESS:

    //initializes state of widget.
    virtual bool init() override;

    /*
     * @brief Sends the touch event to widget's parent, if a widget wants to handle touch event under another widget, 
     *        it must override this function.
     * @param  event  the touch event type, it could be BEGAN/MOVED/CANCELED/ENDED
     * @param parent
     * @param point
     */
    virtual void interceptTouchEvent(TouchEventType event, Widget* sender, Touch *touch);
    
    /**
     *@brief Propagate touch events to its parents
     */
    void propagateTouchEvent(TouchEventType event, Widget* sender, Touch *touch);
    
    friend class PageView;
    /**
     * This method is called when a focus change event happens
     *@param widgetLostFocus  The widget which lose its focus
     *@param widgetGetFocus  The widget which get its focus
     *@return void
     */
    void onFocusChange(Widget* widgetLostFocus, Widget* widgetGetFocus);
    
    /**
     * Dispatch a EventFocus through a EventDispatcher
     *@param widgetLoseFocus  The widget which lose its focus
     *@param widgetGetFocus he widget which get its focus
     *@return void
     */
    void  dispatchFocusEvent(Widget* widgetLoseFocus, Widget* widgetGetFocus);
    
protected:
    /**
     * Get a normal state GLProgramState
     *@since v3.4
     */
    
    GLProgramState* getNormalGLProgramState()const;
    
    /**
     * Get a disabled state GLProgramState
     *@since v3.4
     */
    GLProgramState* getGrayGLProgramState()const;
     
    
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

    
    virtual void adaptRenderers(){};
    void updateChildrenDisplayedRGBA();
    
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
    LayoutComponent* getOrCreateLayoutComponent();

protected:
    bool _usingLayoutComponent;
    bool _unifySize;
    bool _enabled;
    bool _bright;
    bool _touchEnabled;
    bool _highlight;
    bool _affectByClipping;
    bool _ignoreSize;
    bool _propagateTouchEvents;

    BrightStyle _brightStyle;
    SizeType _sizeType;
    PositionType _positionType;

    //used for search widget by action tag in UIHelper class
    int _actionTag;

    Size _customSize;

    Vec2 _sizePercent;
    Vec2 _positionPercent;

    bool _hitted;
    // weak reference of the camera which made the widget passed the hit test when response touch begin event
    // it's useful in the next touch move/end events
    const Camera *_hittedByCamera;
    EventListenerTouchOneByOne* _touchListener;
    Vec2 _touchBeganPosition;
    Vec2 _touchMovePosition;
    Vec2 _touchEndPosition;

    bool _flippedX;
    bool _flippedY;

    //use map to enable switch back and forth for user layout parameters
    Map<int,LayoutParameter*> _layoutParameterDictionary;
    LayoutParameter::Type _layoutParameterType;

    bool _focused;
    bool _focusEnabled;
    /**
     * store the only one focused widget
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
    ccWidgetClickCallback _clickEventListener;
    ccWidgetEventCallback _ccEventCallback;
    
    std::string _callbackType;
    std::string _callbackName;
private:
    class FocusNavigationController;
    static FocusNavigationController* _focusNavigationController;
};
}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__Widget__) */
