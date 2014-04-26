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
#include "ui/UILayoutDefine.h"
#include "ui/UILayoutParameter.h"
#include "ui/GUIDefine.h"

NS_CC_BEGIN

namespace ui {

typedef enum
{
    BRIGHT_NONE = -1,
    BRIGHT_NORMAL,
    BRIGHT_HIGHLIGHT
}BrightStyle;

typedef enum
{
    WidgetTypeWidget, //control
    WidgetTypeContainer //container
}WidgetType;

typedef enum
{
    UI_TEX_TYPE_LOCAL = 0,
    UI_TEX_TYPE_PLIST = 1
}TextureResType;

typedef enum
{
    TOUCH_EVENT_BEGAN,
    TOUCH_EVENT_MOVED,
    TOUCH_EVENT_ENDED,
    TOUCH_EVENT_CANCELED
}TouchEventType;

typedef enum
{
    SIZE_ABSOLUTE,
    SIZE_PERCENT
}SizeType;

typedef enum
{
    POSITION_ABSOLUTE,
    POSITION_PERCENT
}PositionType;

typedef void (Ref::*SEL_TouchEvent)(Ref*,TouchEventType);
#define toucheventselector(_SELECTOR) (SEL_TouchEvent)(&_SELECTOR)
/**
*   @js NA
*   @lua NA
*/
class Widget : public ProtectedNode
{
public:
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
     * Highest control of widget.
     * The default value is true, a widget is default to enabled
     *
     * @param enabled   true if the widget is enabled, widget may be touched and visible, false if the widget is disabled, widget cannot be touched and hidden.
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
     * @param style   BRIGHT_NORMAL the widget is normal state, BRIGHT_HIGHLIGHT the widget is height light state.
     */
    void setBrightStyle(BrightStyle style);

    /**
     * Determines if the widget is touch enabled
     *
     * @return true if the widget is touch enabled, false if the widget is touch disabled.
     */
    bool isTouchEnabled() const;

    /**
     * Determines if the widget is on focused
     *
     * @return true if the widget is on focused, false if the widget is not on focused.
     */
    bool isFocused() const;

    /**
     * Sets whether the widget is on focused
     *
     * The default value is false, a widget is default to not on focused
     *
     * @param fucosed   true if the widget is on focused, false if the widget is not on focused.
     */
    void setFocused(bool fucosed);

    /**
     * Gets the left boundary position of this widget.
     *
     * @return The left boundary position of this widget.
     */
    float getLeftInParent();

    /**
     * Gets the bottom boundary position of this widget.
     *
     * @return The bottom boundary position of this widget.
     */
    float getBottomInParent();

    /**
     * Gets the right boundary position of this widget.
     *
     * @return The right boundary position of this widget.
     */
    float getRightInParent();

    /**
     * Gets the top boundary position of this widget.
     *
     * @return The top boundary position of this widget.
     */
    float getTopInParent();

    /**
     * Gets a child from the container with its name
     *
     * @param name   An key to find the child widget.
     *
     * @return a Widget object whose name equals to the input parameter
     */
    virtual Widget* getChildByName(const char* name);

    virtual void visit(cocos2d::Renderer *renderer, const Matrix &parentTransform, bool parentTransformUpdated) override;

    /**
     * Sets the touch event target/selector of the menu item
     */
    void addTouchEventListener(Ref* target,SEL_TouchEvent selector);


    //cocos2d property

    /**
     * Changes the position (x,y) of the widget in OpenGL coordinates
     *
     * Usually we use p(x,y) to compose Vector2 object.
     * The original point (0,0) is at the left-bottom corner of screen.
     *
     * @param position  The position (x,y) of the widget in OpenGL coordinates
     */
    virtual void setPosition(const Vector2 &pos) override;

    /**
     * Changes the position (x,y) of the widget in OpenGL coordinates
     *
     * Usually we use p(x,y) to compose Vector2 object.
     * The original point (0,0) is at the left-bottom corner of screen.
     *
     * @param percent  The percent (x,y) of the widget in OpenGL coordinates
     */
    void setPositionPercent(const Vector2 &percent);

    /**
     * Gets the percent (x,y) of the widget in OpenGL coordinates
     *
     * @see setPosition(const Vector2&)
     *
     * @return The percent (x,y) of the widget in OpenGL coordinates
     */
    const Vector2& getPositionPercent();

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
    virtual bool isFlippedX(){return _flippedX;};

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
    virtual bool isFlippedY(){return _flippedY;};
    
    virtual void setColor(const Color3B& color) override;
    
    virtual void setOpacity(GLubyte opacity) override;
    
    const Color3B& getColor() const override {return _color;};
    
    GLubyte getOpacity() const override {return _opacity;};

    /** @deprecated Use isFlippedX() instead */
    CC_DEPRECATED_ATTRIBUTE bool isFlipX() { return isFlippedX(); };
    /** @deprecated Use setFlippedX() instead */
    CC_DEPRECATED_ATTRIBUTE void setFlipX(bool flipX) { setFlippedX(flipX); };
    /** @deprecated Use isFlippedY() instead */
    CC_DEPRECATED_ATTRIBUTE bool isFlipY() { return isFlippedY(); };
    /** @deprecated Use setFlippedY() instead */
    CC_DEPRECATED_ATTRIBUTE void setFlipY(bool flipY) { setFlippedY(flipY); };

    /**
     * A call back function when widget lost of focus.
     */
    void didNotSelectSelf();

    /*
     * Checks a point if in parent's area.
     *
     * @param point
     *
     * @return true if the point is in parent's area, flase otherwise.
     */
    bool clippingParentAreaContainPoint(const Vector2 &pt);

    /*
     * Sends the touch event to widget's parent
     */
    virtual void checkChildInfo(int handleState,Widget* sender,const Vector2 &touchPoint);

    /*
     * Gets the touch began point of widget when widget is selected.
     *
     * @return the touch began point.
     */
    const Vector2& getTouchStartPos();

    /*
     * Gets the touch move point of widget when widget is selected.
     *
     * @return the touch move point.
     */
    const Vector2& getTouchMovePos();

    /*
     * Gets the touch end point of widget when widget is selected.
     *
     * @return the touch end point.
     */
    const Vector2& getTouchEndPos();

    /**
     * Changes the name that is used to identify the widget easily.
     *
     * @param A const char* that indentifies the widget.
     */
    void setName(const char* name);

    /**
     * Returns a name that is used to identify the widget easily.
     *
     * You can set tags to widget then identify them easily.
     *
     * @return A const char* that identifies the widget.
     */
    const char* getName() const;

    /**
     * Returns a type that is widget's type
     *
     * @see WidgetType
     *
     * @return A WidgetType
     */
    WidgetType getWidgetType() const;

    /**
     * Changes the size that is widget's size
     *
     * @param size that is widget's size
     */
    virtual void setSize(const Size &size);

    /**
     * Changes the percent that is widget's percent size
     *
     * @param percent that is widget's percent size
     */
    virtual void setSizePercent(const Vector2 &percent);

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
    const Size& getSize() const;
    
    const Size& getCustomSize() const;
    
    virtual const Size& getLayoutSize() {return _size;};

    /**
     * Returns size percent of widget
     *
     * @return size percent
     */
    const Vector2& getSizePercent() const;

    /**
     * Checks a point if is in widget's space
     *
     * @param point
     *
     * @return true if the point is in widget's space, flase otherwise.
     */
    virtual bool hitTest(const Vector2 &pt);

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
    LayoutParameter* getLayoutParameter(LayoutParameterType type);

    /**
     * Ignore the widget size
     *
     * @param ignore, true that widget will ignore it's size, use texture size, false otherwise. Default value is true.
     */
    virtual void ignoreContentAdaptWithSize(bool ignore);

    /**
     * Gets the widget if is ignore it's size.
     *
     * @param ignore, true that widget will ignore it's size, use texture size, false otherwise. Default value is true.
     */
    bool isIgnoreContentAdaptWithSize() const;

    /**
     * Gets world position of widget.
     *
     * @return world position of widget.
     */
    Vector2 getWorldPosition();

    /**
     * Gets the Virtual Renderer of widget.
     *
     * For example, a button's Virtual Renderer is it's texture renderer.
     *
     * @return Node pointer.
     */
    virtual Node* getVirtualRenderer();

//    /**
//     * Gets the content size of widget.
//     *
//     * Content size is widget's texture size.
//     */
//    virtual const Size& getContentSize() const;
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
	int getActionTag();
    
CC_CONSTRUCTOR_ACCESS:
    //initializes state of widget.
    virtual bool init() override;
    
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
    void releaseUpEvent();
    void cancelUpEvent();
    virtual void updateTextureColor(){};
    virtual void updateTextureOpacity(){};
    virtual void updateTextureRGBA(){};
    virtual void updateFlippedX(){};
    virtual void updateFlippedY(){};
    void updateColorToRenderer(Node* renderer);
    void updateOpacityToRenderer(Node* renderer);
    void updateRGBAToRenderer(Node* renderer);
    void copyProperties(Widget* model);
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
    virtual void copyClonedWidgetChildren(Widget* model);
    Widget* getWidgetParent();
    void updateContentSizeWithTextureSize(const Size& size);
    virtual void adaptRenderers(){};
protected:
    bool _enabled;            ///< Highest control of widget
    bool _bright;             ///< is this widget bright
    bool _touchEnabled;       ///< is this widget touch endabled
    bool _touchPassedEnabled; ///< is the touch event should be passed
    bool _focus;              ///< is the widget on focus
    BrightStyle _brightStyle; ///< bright style
    Vector2 _touchStartPos;    ///< touch began point
    Vector2 _touchMovePos;     ///< touch moved point
    Vector2 _touchEndPos;      ///< touch ended point
    Ref*       _touchEventListener;
    SEL_TouchEvent    _touchEventSelector;
    std::string _name;
    WidgetType _widgetType;
	int _actionTag;
    Size _size;
    Size _customSize;
    bool _ignoreSize;
    bool _affectByClipping;
    SizeType _sizeType;
    Vector2 _sizePercent;
    PositionType _positionType;
    Vector2 _positionPercent;
    bool _reorderWidgetChildDirty;
    bool _hitted;
    EventListenerTouchOneByOne* _touchListener;
    Color3B _color;
    GLubyte _opacity;
    bool _flippedX;
    bool _flippedY;
    Map<int, LayoutParameter*> _layoutParameterDictionary;

};
}

NS_CC_END

#endif /* defined(__Widget__) */
