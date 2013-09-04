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
#include "ExtensionMacros.h"
#include "../Layouts/UILayoutDefine.h"
#include "../Layouts/LayoutParameter.h"
NS_CC_EXT_BEGIN


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

typedef void (CCObject::*SEL_PushEvent)(CCObject*);
typedef void (CCObject::*SEL_MoveEvent)(CCObject*);
typedef void (CCObject::*SEL_ReleaseEvent)(CCObject*);
typedef void (CCObject::*SEL_CancelEvent)(CCObject*);
#define coco_pushselector(_SELECTOR) (cocos2d::extension::SEL_PushEvent)(&_SELECTOR)
#define coco_moveselector(_SELECTOR) (cocos2d::extension::SEL_MoveEvent)(&_SELECTOR)
#define coco_releaseselector(_SELECTOR) (cocos2d::extension::SEL_ReleaseEvent)(&_SELECTOR)
#define coco_cancelselector(_SELECTOR) (cocos2d::extension::SEL_CancelEvent)(&_SELECTOR)

class UILayer;
/*temp action*/
class UIActionNode;

class UIWidget : public CCObject
{
public:    
    /**
     * Default constructor
     */
    UIWidget(void);
    
    /**
     * Default destructor
     */
    virtual ~UIWidget();
    
    /**
     * Allocates and initializes a widget.
     */
    static UIWidget* create();
    
    /**
     * Release texture resoures of widget.
     * Release renderer.
     * If you override releaseResoures, you shall call its parent's one, e.g. UIWidget::releaseResoures().
     */
    virtual void releaseResoures();
    
    /**
     * Sets whether the widget is enabled
     *
     * Highest control of widget.
     * The default value is true, a widget is default to enabled
     *
     * @param enabled   true if the widget is enabled, widget may be touched and visible, false if the widget is disabled, widget cannot be touched and hidden.
     */
    void setEnabled(bool enabled);
    
    /**
     * Determines if the widget is enabled
     *
     * @return true if the widget is enabled, false if the widget is disabled.
     */
    bool isEnabled() const;
    
    /**
     * Sets whether the widget is visible
     *
     * The default value is true, a widget is default to visible
     *
     * @param visible   true if the widget is visible, false if the widget is hidden.
     */
    void setVisible(bool visible);
    
    /**
     * Determines if the widget is visible
     *
     * @return true if the widget is visible, false if the widget is hidden.
     */
    bool isVisible() const;
    
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
     * Determines if the widget is on focus
     *
     * @return true if the widget is on focus, false if the widget is not on focus.
     */
    bool isFocus() const;

    /**
     * Sets whether the widget is on focus
     *
     * The default value is false, a widget is default to not on focus
     *
     * @param fucos   true if the widget is on focus, false if the widget is not on focus.
     */
    void setFocus(bool fucos);
    
    /**
     * Sets the Z order which stands for the drawing order, and reorder this widget in its parent's children array.
     *
     * The Z order of widget is relative to its "brothers": children of the same parent.
     * It's nothing to do with OpenGL's z vertex. This one only affects the draw order of widgets in cocos2d.
     * The larger number it is, the later this widget will be drawn in each message loop.
     * Please refer to setVertexZ(float) for the difference.
     *
     * @param nZOrder   Z order of this widget.
     */
    void setZOrder(int z);
    
    /**
     * Gets the Z order of this widget.
     *
     * @see setZOrder(int)
     *
     * @return The Z order.
     */
    int getZOrder();
    
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
     * Adds a child to the container.
     *
     * @param child A child widget
     */
    virtual bool addChild(UIWidget* child);
    
    /**
     * Removes a child from the container with a cleanup
     *
     * @param child     The child widget which will be removed.
     *
     * @return the result of removing, succeeded or failed.
     */
    virtual bool removeChild(UIWidget* child,bool cleanup);
    
    /**
     * Removes this widget itself from its parent widget.
     * If the widget orphan, then it will destroy itself.
     * @param cleanup   true if all actions and callbacks on this widget should be removed, false otherwise.
     */
    virtual void removeFromParentAndCleanup(bool cleanup);
    
    /**
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @param cleanup   true if all running actions on all children widgets should be cleanup, false otherwise.
     */
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
    
    /**
     * Sets the UILayer object that is the manager of a widget tree.
     *
     * @param uiLayer   A UILayer that is the manager of a widget tree.
     */
    void setUILayer(UILayer* uiLayer);

    /**
     * Sets the UILayer object to all of widget's children.
     *
     * @param uiLayer   A UILayer that is the manager of a widget tree.
     */
    void updateChildrenUILayer(UILayer* uiLayer);
    
    /**
     * Unschedules the "update" method.
     */
    void disableUpdate();
    
    /**
     * Reorders a child according to a new z value.
     *
     * @param child     An already added child node. It MUST be already added.
     * @param zOrder    Z order for drawing priority and touched priority. Please refer to setZOrder(int)
     */
    virtual void reorderChild(UIWidget* child);
    
    /**
     * Gets a child from the container with its name
     *
     * @param name   An key to find the child widget.
     *
     * @return a UIWidget object whose name equals to the input parameter
     */
    UIWidget* getChildByName(const char* name);
    
    /**
     * Gets a child from the container with its tag
     *
     * @param tag   An identifier to find the child widget.
     *
     * @return a UIWidget object whose tag equals to the input parameter
     */
    UIWidget* getChildByTag(int tag);
    
    /**
     * Return an array of children
     *
     * Composing a "tree" structure is a very important feature of UIWidget
     *
     * @return An array of children
     */
    virtual CCArray* getChildren();
    
    /**
     * Gets the renderer of widget
     *
     * renderer is a CCNode, it's for drawing
     *
     * @return a CCNode object
     */
    CCNode* getRenderer();
    
    /**
     * Sets the parent widget
     *
     * @param parent    A pointer to the parnet widget
     */
    void setParent(UIWidget* parent);
    
    /**
     * Returns a pointer to the parent widget
     *
     * @see setParent(UIWidget*)
     *
     * @returns A pointer to the parnet widget
     */
    UIWidget* getParent();
    
    /** 
     * Sets the push event target/selector of the menu item
     */
    virtual void addPushDownEvent(CCObject* target,SEL_PushEvent selector);
    
    /**
     * Sets the move event target/selector of the menu item
     */
    virtual void addMoveEvent(CCObject* target,SEL_MoveEvent selector);
    
    /**
     * Sets the release event target/selector of the menu item
     */
    virtual void addReleaseEvent(CCObject* target,SEL_ReleaseEvent selector);
    
    /**
     * Sets the cancel event target/selector of the menu item
     */
    virtual void addCancelEvent(CCObject* target,SEL_CancelEvent selector);
    
    
    //cocos2d property
    
    /**
     * Changes the position (x,y) of the widget in OpenGL coordinates
     *
     * Usually we use ccp(x,y) to compose CCPoint object.
     * The original point (0,0) is at the left-bottom corner of screen.
     *
     * @param position  The position (x,y) of the widget in OpenGL coordinates
     */
    void setPosition(const CCPoint &pos);
    
    /**
     * Gets the position (x,y) of the widget in OpenGL coordinates
     *
     * @see setPosition(const CCPoint&)
     *
     * @return The position (x,y) of the widget in OpenGL coordinates
     */
    const CCPoint& getPosition();
    
    /**
     * Sets the anchor point in percent.
     *
     * anchorPoint is the point around which all transformations and positioning manipulations take place.
     * It's like a pin in the widget where it is "attached" to its parent.
     * The anchorPoint is normalized, like a percentage. (0,0) means the bottom-left corner and (1,1) means the top-right corner.
     * But you can use values higher than (1,1) and lower than (0,0) too.
     * The default anchorPoint is (0.5,0.5), so it starts in the center of the widget.
     *
     * @param anchorPoint   The anchor point of widget.
     */
    virtual void setAnchorPoint(const CCPoint &pt);
    
    /**
     * Returns the anchor point in percent.
     *
     * @see setAnchorPoint(const CCPoint&)
     *
     * @return The anchor point of widget.
     */
    const CCPoint& getAnchorPoint();
    
    /**
     * Changes both X and Y scale factor of the widget.
     *
     * 1.0 is the default scale factor. It modifies the X and Y scale at the same time.
     *
     * @param scale     The scale factor for both X and Y axis.
     */
    virtual void setScale(float fScale);
    
    /**
     * Gets the scale factor of the widget,  when X and Y have the same scale factor.
     *
     * @warning Assert when m_fScaleX != m_fScaleY.
     * @see setScale(float)
     *
     * @return The scale factor of the widget.
     */
    float getScale();
    
    /**
     * Changes the scale factor on X axis of this widget
     *
     * The deafult value is 1.0 if you haven't changed it before
     *
     * @param fScaleX   The scale factor on X axis.
     */
    virtual void setScaleX(float fScaleX);
    
    /**
     * Returns the scale factor on X axis of this widget
     *
     * @see setScaleX(float)
     *
     * @return The scale factor on X axis.
     */
    float getScaleX();
    
    /**
     * Changes the scale factor on Y axis of this widget
     *
     * The Default value is 1.0 if you haven't changed it before.
     *
     * @param fScaleY   The scale factor on Y axis.
     */
    virtual void setScaleY(float fScaleY);
    
    /**
     * Returns the scale factor on Y axis of this widget
     *
     * @see setScaleY(float)
     *
     * @return The scale factor on Y axis.
     */
    float getScaleY();
    
    /**
     * Sets the rotation (angle) of the widget in degrees.
     *
     * 0 is the default rotation angle.
     * Positive values rotate widget clockwise, and negative values for anti-clockwise.
     *
     * @param fRotation     The roration of the widget in degrees.
     */
    void setRotation(float rotation);
    
    /**
     * Returns the rotation of the widget in degrees.
     *
     * @see setRotation(float)
     *
     * @return The rotation of the widget in degrees.
     */
    float getRotation();
    
    /**
     * Sets the X rotation (angle) of the widget in degrees which performs a horizontal rotational skew.
     *
     * 0 is the default rotation angle.
     * Positive values rotate widget clockwise, and negative values for anti-clockwise.
     *
     * @param fRotationX    The X rotation in degrees which performs a horizontal rotational skew.
     */
    void setRotationX(float rotationX);
    
    /**
     * Gets the X rotation (angle) of the widget in degrees which performs a horizontal rotation skew.
     *
     * @see setRotationX(float)
     *
     * @return The X rotation in degrees.
     */
    float getRotationX();
    
    /**
     * Sets the Y rotation (angle) of the widget in degrees which performs a vertical rotational skew.
     *
     * 0 is the default rotation angle.
     * Positive values rotate widget clockwise, and negative values for anti-clockwise.
     *
     * @param fRotationY    The Y rotation in degrees.
     */
    void setRotationY(float rotationY);
    
    /**
     * Gets the Y rotation (angle) of the widget in degrees which performs a vertical rotational skew.
     *
     * @see setRotationY(float)
     *
     * @return The Y rotation in degrees.
     */
    float getRotationY();
    
    /**
     * Sets whether the widget should be flipped horizontally or not.
     *
     * @param bFlipX true if the widget should be flipped horizaontally, false otherwise.
     */
    virtual void setFlipX(bool flipX){};
    
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
    virtual bool isFlipX(){return false;};
    
    /**
     * Sets whether the widget should be flipped vertically or not.
     *
     * @param bFlipY true if the widget should be flipped vertically, flase otherwise.
     */
    virtual void setFlipY(bool flipY){};
    
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
    virtual bool isFlipY(){return false;};
    
    /**
     * Sets color to widget
     *
     * It default change the color of widget's children.
     *
     * @param color
     */
    virtual void setColor(const ccColor3B &color);
    
    /**
     * Gets color of widget
     *
     * @return color
     */
    virtual const ccColor3B& getColor();
    
    /**
     * Sets opacity to widget
     *
     * It default change the opacity of widget's children.
     *
     * @param color
     */
    virtual void setOpacity(int opacity);
    
    /**
     * Gets opacity of widget
     *
     * @return opacity
     */
    virtual int getOpacity();
    virtual bool isCascadeOpacityEnabled();
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    virtual bool isCascadeColorEnabled();
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);
    void setBlendFunc(ccBlendFunc blendFunc);
    
    //cocos action
    virtual void setActionManager(CCActionManager* actionManager);
    virtual CCActionManager* getActionManager();
    CCAction* runAction(CCAction* action);
    void stopAllActions(void);
    void stopAction(CCAction* action);
    void stopActionByTag(int tag);
    CCAction* getActionByTag(int tag);
    
    /**
     * A call back function when widget lost of focus.
     */
    void didNotSelectSelf();
    
    /*
     * Update method will be called automatically every frame if "setUpdateEnabled" is called, and the widget is "live"
     */
    virtual void update(float dt){};
    
    /*
     * Checks a point if in parent's area.
     *
     * @param point
     *
     * @return true if the point is in parent's area, flase otherwise.
     */
    bool parentAreaContainPoint(const CCPoint &pt);
    
    /*
     * Sends the touch event to widget's parent
     */
    virtual void checkChildInfo(int handleState,UIWidget* sender,const CCPoint &touchPoint);
    
    /*
     * Informs UILayer that the structure of widget tree has changed.
     */
    void structureChangedEvent();
    
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
     * Changes the tag that is used to identify the widget easily.
     *
     * @param A interger that indentifies the widget.
     */
    void setTag(int tag);
    
    /**
     * Returns a tag that is used to identify the widget easily.
     *
     * You can set tags to widget then identify them easily.
     *
     * @return A interger that identifies the widget.
     */
    int getTag() const;
    
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
     * Returns size of widget
     *
     * @return A WidgetType
     */
    const CCSize& getSize() const;
    
    /**
     * Checks a point if is in widget's space
     *
     * @param point
     *
     * @return true if the point is in widget's space, flase otherwise.
     */
    virtual bool hitTest(const CCPoint &pt);
    
    /**
     * A call back function called when widget is selected, and on touch began.
     *
     * @param touch point
     *
     * @return true if the event should be pass to parent, flase otherwise.
     */
    virtual bool onTouchBegan(const CCPoint &touchPoint);
    
    /**
     * A call back function called when widget is selected, and on touch moved.
     *
     * @param touch point
     */
    virtual void onTouchMoved(const CCPoint &touchPoint);
    
    /**
     * A call back function called when widget is selected, and on touch ended.
     *
     * @param touch point
     */
    virtual void onTouchEnded(const CCPoint &touchPoint);
    
    /**
     * A call back function called when widget is selected, and on touch canceled.
     *
     * @param touch point
     */
    virtual void onTouchCancelled(const CCPoint &touchPoint);
    
    /**
     * A call back function called when widget is selected, and on touch long clicked.
     *
     * @param touch point
     */
    virtual void onTouchLongClicked(const CCPoint &touchPoint);
    
    /**
     * Sets a LayoutParameter to widget. 
     *
     * @see LayoutParameter
     *
     * @param LayoutParameter pointer
     */
    void setLayoutParameter(LayoutParameter* parameter);
    
    /**
     * Gets LayoutParameter of widget.
     *
     * @see LayoutParameter
     */
    LayoutParameter* getLayoutParameter();
    
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
     * Converts a Point to world space coordinates. The result is in Points.
     */
    CCPoint convertToWorldSpace(const CCPoint& pt);
    
    /**
     * Gets the Virtual Renderer of widget.
     *
     * For example, a button's Virtual Renderer is it's texture renderer.
     *
     * @return CCNode pointer.
     */
    virtual CCNode* getVirtualRenderer();
    
    /**
     * Schedules the "update" method.
     */
    void setUpdateEnabled(bool enable);
    
    /**
     * is the "update" method scheduled.
     */
    bool isUpdateEnabled();
    
    /**
     * Gets the content size of widget.
     *
     * Content size is widget's texture size.
     */
    virtual const CCSize& getContentSize() const;
    
    /*******to be removed*******/
    CC_DEPRECATED_ATTRIBUTE virtual void setTouchEnable(bool enabled, bool containChildren = false);
    CC_DEPRECATED_ATTRIBUTE void disable(bool containChildren = false);
    CC_DEPRECATED_ATTRIBUTE void active(bool containChildren = false);
    CC_DEPRECATED_ATTRIBUTE bool isActive();
    CC_DEPRECATED_ATTRIBUTE void setBright(bool bright, bool containChild);
    CC_DEPRECATED_ATTRIBUTE CCRect getRect();
    CC_DEPRECATED_ATTRIBUTE CCNode* getValidNode(){return getVirtualRenderer();};
    CC_DEPRECATED_ATTRIBUTE void setWidgetZOrder(int z){setZOrder(z);};
    CC_DEPRECATED_ATTRIBUTE int getWidgetZOrder(){return getZOrder();};
    CC_DEPRECATED_ATTRIBUTE float getRelativeLeftPos(){return getLeftInParent();};
    CC_DEPRECATED_ATTRIBUTE float getRelativeBottomPos(){return getBottomInParent();};
    CC_DEPRECATED_ATTRIBUTE float getRelativeRightPos(){return getRightInParent();};
    CC_DEPRECATED_ATTRIBUTE float getRelativeTopPos(){return getTopInParent();};
    CC_DEPRECATED_ATTRIBUTE CCNode* getContainerNode(){return getRenderer();};
    CC_DEPRECATED_ATTRIBUTE void setWidgetParent(UIWidget* parent){setParent(parent);};
    CC_DEPRECATED_ATTRIBUTE UIWidget* getWidgetParent(){return getParent();};
    CC_DEPRECATED_ATTRIBUTE void setWidgetTag(int tag){setTag(tag);};
    CC_DEPRECATED_ATTRIBUTE int getWidgetTag(){return getTag();};
    /***************************/
    
    /*temp action*/
    void setActionTag(int tag);
	int getActionTag();
    void setBindingAction(UIActionNode* actionNode);
protected:
    //call back function called when size changed.
    virtual void onSizeChanged();
    
    //initializes state of widget.
    virtual bool init();
    
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
    void longClickEvent();
    void updateAnchorPoint();
protected:
    bool m_bEnabled;            ///< Highest control of widget
    bool m_bVisible;            ///< is this widget visible
    bool m_bBright;             ///< is this widget bright
    bool m_bTouchEnabled;       ///< is this widget touch endabled
    bool m_bTouchPassedEnabled; ///< is the touch event should be passed
    bool m_bFocus;              ///< is the widget on focus
    int m_nWidgetZOrder;        ///< z-order value that affects the draw order and touch order
    CCPoint m_anchorPoint;      ///< anchor point normalized
    UIWidget* m_pWidgetParent;  ///< parent of widget
    BrightStyle m_eBrightStyle; ///< bright style
    bool m_bUpdateEnabled;      ///< is "update" method scheduled
    CCNode* m_pRenderer;        ///< base renderer
    CCPoint m_touchStartPos;    ///< touch began point
    CCPoint m_touchMovePos;     ///< touch moved point
    CCPoint m_touchEndPos;      ///< touch ended point
    CCObject*       m_pPushListener;
    SEL_PushEvent    m_pfnPushSelector;
    CCObject*       m_pMoveListener;
    SEL_MoveEvent    m_pfnMoveSelector;
    CCObject*       m_pReleaseListener;
    SEL_ReleaseEvent    m_pfnReleaseSelector;
    CCObject*       m_pCancelListener;
    SEL_ReleaseEvent    m_pfnCancelSelector;
    bool m_bOpacityDirty;
    int m_nWidgetTag;
    std::string m_strName;
    WidgetType m_WidgetType;
    UILayer* m_pUILayer;
	int m_nActionTag;
    CCSize m_size;
    CCSize m_customSize;
    LayoutParameter* m_pLayoutParameter;
    bool m_bIgnoreSize;
    CCArray* m_children;
    bool m_bAffectByClipping;
    /*temp action*/
    UIActionNode* m_pBindingAction;
};

class GUIRenderer : public CCNodeRGBA
{
public:
    GUIRenderer();
    virtual ~GUIRenderer();
    virtual void visit(void);
    static GUIRenderer* create();
    void setEnabled(bool enabled);
    bool getEnabled() const;
protected:
    bool m_bEnabled;
};

NS_CC_EXT_END

#endif /* defined(__UIWidget__) */
