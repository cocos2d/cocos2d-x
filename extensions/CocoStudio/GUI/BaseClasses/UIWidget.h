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

#ifndef __UIWIDGET_H__
#define __UIWIDGET_H__

#include "cocos2d.h"
#include "../Layouts/UILayoutDefine.h"
#include "../Layouts/UILayoutParameter.h"
#include "../System/GUIDefine.h"

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
    UI_TEX_TYPE_LOCAL,
    UI_TEX_TYPE_PLIST
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

typedef void (CCObject::*SEL_TouchEvent)(CCObject*,TouchEventType);
#define toucheventselector(_SELECTOR) (SEL_TouchEvent)(&_SELECTOR)
/**
*   @js NA
*   @lua NA
*/
class CC_EX_DLL Widget : public CCNodeRGBA
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
     * Adds a child to the container with z-order as 0.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child A child node
     */
    virtual void addChild(CCNode * child);
    /**
     * Adds a child to the container with a z-order
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setZOrder(int)
     */
    virtual void addChild(CCNode * child, int zOrder);
    /**
     * Adds a child to the container with z order and tag
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setZOrder(int)
     * @param tag       A interger to identify the node easily. Please refer to setTag(int)
     */
    virtual void addChild(CCNode* child, int zOrder, int tag);
    /**
     * Gets a child from the container with its tag
     *
     * @param tag   An identifier to find the child node.
     *
     * @return a Node object whose tag equals to the input parameter
     */
    virtual CCNode * getChildByTag(int tag);
    
    virtual void sortAllChildren();
    /**
     * Return an array of children
     *
     * Composing a "tree" structure is a very important feature of Node
     * Here's a sample code of traversing children array:
     @code
     Node* node = NULL;
     CCARRAY_FOREACH(parent->getChildren(), node)
     {
     node->setPosition(0,0);
     }
     @endcode
     * This sample code traverses all children nodes, and set their position to (0,0)
     *
     * @return An array of children
     */
    virtual CCArray* getChildren();
    
    /**
     * Get the amount of children.
     *
     * @return The amount of children.
     */
    virtual unsigned int getChildrenCount() const;
    
    /**
     * Removes this node itself from its parent node with a cleanup.
     * If the node orphan, then nothing happens.
     * @see `removeFromParentAndCleanup(bool)`
     */
    virtual void removeFromParent();
    /**
     * Removes this node itself from its parent node.
     * If the node orphan, then nothing happens.
     * @param cleanup   true if all actions and callbacks on this node should be removed, false otherwise.
     * @js removeFromParent
     * @lua removeFromParent
     */
    virtual void removeFromParentAndCleanup(bool cleanup);
    
    virtual void removeChild(CCNode* child);
    
    /**
     * Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
     *
     * @param child     The child node which will be removed.
     * @param cleanup   true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     */
    virtual void removeChild(CCNode* child, bool cleanup);
    
    /**
     * Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter
     *
     * @param tag       An interger number that identifies a child node
     * @param cleanup   true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     */
    virtual void removeChildByTag(int tag, bool cleanup);
    /**
     * Removes all children from the container with a cleanup.
     *
     * @see `removeAllChildrenWithCleanup(bool)`
     */
    virtual void removeAllChildren();
    /**
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @param cleanup   true if all running actions on all children nodes should be cleanup, false oterwise.
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup);
    
    /**
     * Gets a child from the container with its name
     *
     * @param name   An key to find the child widget.
     *
     * @return a Widget object whose name equals to the input parameter
     */
    virtual Widget* getChildByName(const char* name);
    
    virtual void addNode(CCNode* node);
    
    virtual void addNode(CCNode * node, int zOrder);
    
    virtual void addNode(CCNode* node, int zOrder, int tag);
    
    virtual CCNode * getNodeByTag(int tag);
    
    virtual CCArray* getNodes();
    
    virtual void removeNode(CCNode* node);
    
    virtual void removeNodeByTag(int tag);
    
    virtual void removeAllNodes();
    
    virtual void visit();
    
    /**
     * Sets the touch event target/selector of the menu item
     */
    void addTouchEventListener(CCObject* target,SEL_TouchEvent selector);
    
    
    //cocos2d property
    
    /**
     * Changes the position (x,y) of the widget in OpenGL coordinates
     *
     * Usually we use p(x,y) to compose Point object.
     * The original point (0,0) is at the left-bottom corner of screen.
     *
     * @param position  The position (x,y) of the widget in OpenGL coordinates
     */
    void setPosition(const CCPoint &pos);
    
    /**
     * Changes the position (x,y) of the widget in OpenGL coordinates
     *
     * Usually we use p(x,y) to compose Point object.
     * The original point (0,0) is at the left-bottom corner of screen.
     *
     * @param percent  The percent (x,y) of the widget in OpenGL coordinates
     */
    void setPositionPercent(const CCPoint &percent);
        
    /**
     * Gets the percent (x,y) of the widget in OpenGL coordinates
     *
     * @see setPosition(const Point&)
     *
     * @return The percent (x,y) of the widget in OpenGL coordinates
     */
    const CCPoint& getPositionPercent();
    
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
     * @param bFlipX true if the widget should be flipped horizaontally, false otherwise.
     */
    virtual void setFlipX(bool flipX);
    
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
    virtual bool isFlipX(){return _flippedX;};
    
    /**
     * Sets whether the widget should be flipped vertically or not.
     *
     * @param bFlipY true if the widget should be flipped vertically, flase otherwise.
     */
    virtual void setFlipY(bool flipY);
    
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
    virtual bool isFlipY(){return _flippedY;};
    
    virtual void setColor(const ccColor3B& color);
    
    virtual void setOpacity(GLubyte opacity);
    
    const ccColor3B& getColor(){return _color;};

    GLubyte getOpacity(){return _opacity;};
    
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
    bool clippingParentAreaContainPoint(const CCPoint &pt);
    
    /*
     * Sends the touch event to widget's parent
     */
    virtual void checkChildInfo(int handleState,Widget* sender,const CCPoint &touchPoint);
    
    /*
     * Gets the touch began point of widget when widget is selected.
     *
     * @return the touch began point.
     */
    const CCPoint& getTouchStartPos();
    
    /*
     * Gets the touch move point of widget when widget is selected.
     *
     * @return the touch move point.
     */
    const CCPoint& getTouchMovePos();
    
    /*
     * Gets the touch end point of widget when widget is selected.
     *
     * @return the touch end point.
     */
    const CCPoint& getTouchEndPos();
    
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
    virtual void setSize(const CCSize &size);
    
    /**
     * Changes the percent that is widget's percent size
     *
     * @param percent that is widget's percent size
     */
    virtual void setSizePercent(const CCPoint &percent);
    
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
    const CCSize& getSize() const;
    
    virtual const CCSize& getLayoutSize() {return _size;};
    
    /**
     * Returns size percent of widget
     *
     * @return size percent
     */
    const CCPoint& getSizePercent() const;
    
    const CCSize& getCustomSize() const;
    
    /**
     * Checks a point if is in widget's space
     *
     * @param point
     *
     * @return true if the point is in widget's space, flase otherwise.
     */
    virtual bool hitTest(const CCPoint &pt);
    
    virtual bool onTouchBegan(CCTouch *touch, CCEvent *unused_event);
    virtual void onTouchMoved(CCTouch *touch, CCEvent *unused_event);
    virtual void onTouchEnded(CCTouch *touch, CCEvent *unused_event);
    virtual void onTouchCancelled(CCTouch *touch, CCEvent *unused_event);
    
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
    CCPoint getWorldPosition();

    /**
     * Gets the Virtual Renderer of widget.
     *
     * For example, a button's Virtual Renderer is it's texture renderer.
     *
     * @return Node pointer.
     */
    virtual CCNode* getVirtualRenderer();
    
    /**
     * Gets the content size of widget.
     *
     * Content size is widget's texture size.
     */
    virtual const CCSize& getContentSize() const;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const;
    
    Widget* clone();

    virtual void onEnter();
    virtual void onExit();
    
    void updateSizeAndPosition();
    
    void updateSizeAndPosition(const CCSize& parentSize);
    
    /*temp action*/
    void setActionTag(int tag);
	int getActionTag();
    
    /**
     * Returns a user assigned CCDictionary
     *
     * @return A user assigned CCDictionary
     */
    virtual cocos2d::CCDictionary* getScriptObjectDict() const;
    /**
     * Returns a user assigned CCDictionary
     *
     * The scriptObjectDict will be retained once in this method,
     * and the previous scriptObjectDict (if existed) will be relese.
     * The scriptObjectDict will be released in destructure.
     *
     * @param A user assigned CCObject
     */
    virtual void setScriptObjectDict(cocos2d::CCDictionary* scriptObjectDict);
protected:
    //call back function called when size changed.
    virtual void onSizeChanged();
    
    //initializes state of widget.
    virtual bool init();
    
    //initializes renderer of widget.
    virtual void initRenderer(){};
    
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
    void updateAnchorPoint();
    virtual void updateTextureColor(){};
    virtual void updateTextureOpacity(){};
    virtual void updateTextureRGBA(){};
    virtual void updateFlippedX(){};
    virtual void updateFlippedY(){};
    void updateColorToRenderer(CCNode* renderer);
    void updateOpacityToRenderer(CCNode* renderer);
    void updateRGBAToRenderer(CCNode* renderer);
    void copyProperties(Widget* model);
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
    virtual void copyClonedWidgetChildren(Widget* model);
    Widget* getWidgetParent();
protected:
    bool _enabled;            ///< Highest control of widget
    bool _bright;             ///< is this widget bright
    bool _touchEnabled;       ///< is this widget touch endabled
    bool _touchPassedEnabled; ///< is the touch event should be passed
    bool _focus;              ///< is the widget on focus
    BrightStyle _brightStyle; ///< bright style
    CCPoint _touchStartPos;    ///< touch began point
    CCPoint _touchMovePos;     ///< touch moved point
    CCPoint _touchEndPos;      ///< touch ended point
    
    CCObject*       _touchEventListener;
    SEL_TouchEvent    _touchEventSelector;
    

    
    std::string _name;
    WidgetType _widgetType;
	int _actionTag;
    CCSize _size;
    CCSize _customSize;
    bool _ignoreSize;
    bool _affectByClipping;
    SizeType _sizeType;
    CCPoint _sizePercent;
    PositionType _positionType;
    CCPoint _positionPercent;
    bool _reorderWidgetChildDirty;
    bool _hitted;
    CCArray* _widgetChildren;
    CCDictionary* _layoutParameterDictionary;
    
    CCArray* _nodes;
    
    ccColor3B _color;
    GLubyte _opacity;
    
    bool _flippedX;
    bool _flippedY;
    
    cocos2d::CCDictionary* _scriptObjectDict;
    
    friend class TouchGroup;
};
}

namespace gui = ui;

NS_CC_END



#endif /* defined(__Widget__) */
