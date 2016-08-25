/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2011 Yannick Loriot.
 * http://yannickloriot.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Converted to c++ / cocos2d-x by Angus C
 */


#ifndef __CCCONTROL_H__
#define __CCCONTROL_H__

#include "CCControlUtils.h"
#include "2d/CCLayer.h"
#include "extensions/ExtensionExport.h"

NS_CC_EXT_BEGIN


class Invocation;

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/** Number of kinds of control event. */
#define kControlEventTotalNumber 9


/*
 * @class
 * Control is inspired by the UIControl API class from the UIKit library of 
 * CocoaTouch. It provides a base class for control Sprites such as Button 
 * or Slider that convey user intent to the application.
 *
 * The goal of Control is to define an interface and base implementation for 
 * preparing action messages and initially dispatching them to their targets when
 * certain events occur.
 *
 * To use the Control you have to subclass it.
 */
class CC_EX_DLL Control : public Layer
{
public:
    /** Kinds of possible events for the control objects. */
    enum class CC_EX_DLL EventType
    {
        TOUCH_DOWN           = 1 << 0,    // A touch-down event in the control.
        DRAG_INSIDE          = 1 << 1,    // An event where a finger is dragged inside the bounds of the control.
        DRAG_OUTSIDE         = 1 << 2,    // An event where a finger is dragged just outside the bounds of the control.
        DRAG_ENTER           = 1 << 3,    // An event where a finger is dragged into the bounds of the control.
        DRAG_EXIT            = 1 << 4,    // An event where a finger is dragged from within a control to outside its bounds.
        TOUCH_UP_INSIDE      = 1 << 5,    // A touch-up event in the control where the finger is inside the bounds of the control.
        TOUCH_UP_OUTSIDE     = 1 << 6,    // A touch-up event in the control where the finger is outside the bounds of the control.
        TOUCH_CANCEL         = 1 << 7,    // A system event canceling the current touches for the control.
        VALUE_CHANGED        = 1 << 8      // A touch dragging or otherwise manipulating a control, causing it to emit a series of different values.
    };
    
    typedef void (Ref::*Handler)(Ref*, EventType);
    
    /** The possible state for a control.  */
    enum class State
    {
        NORMAL         = 1 << 0, // The normal, or default state of a control that is, enabled but neither selected nor highlighted.
        HIGH_LIGHTED   = 1 << 1, // Highlighted state of a control. A control enters this state when a touch down, drag inside or drag enter is performed. You can retrieve and set this value through the highlighted property.
        DISABLED       = 1 << 2, // Disabled state of a control. This state indicates that the control is currently disabled. You can retrieve and set this value through the enabled property.
        SELECTED       = 1 << 3  // Selected state of a control. This state indicates that the control is currently selected. You can retrieve and set this value through the selected property.
    };

    /** Creates a Control object */
    static Control* create();

    /** Tells whether the control is enabled. */
    virtual void setEnabled(bool bEnabled);
    virtual bool isEnabled() const;

    /** A Boolean value that determines the control selected state. */
    virtual void setSelected(bool bSelected);
    virtual bool isSelected() const;

    /** A Boolean value that determines whether the control is highlighted. */
    virtual void setHighlighted(bool bHighlighted);
    virtual bool isHighlighted() const;

    bool hasVisibleParents() const;
    /**
     * Updates the control layout using its current internal state.
     */
    virtual void needsLayout();

    /**
     * Sends action messages for the given control events.
     *
     * @param controlEvents A bitmask whose set flags specify the control events for
     * which action messages are sent. See "CCControlEvent" for bitmask constants.
     */
    virtual void sendActionsForControlEvents(EventType controlEvents);

    /**
     * Adds a target and action for a particular event (or events) to an internal
     * dispatch table.
     * The action message may optionally include the sender and the event as
     * parameters, in that order.
     * When you call this method, target is not retained.
     *
     * @param target The target object that is, the object to which the action
     * message is sent. It cannot be nil. The target is not retained.
     * @param action A selector identifying an action message. It cannot be NULL.
     * @param controlEvents A bitmask specifying the control events for which the
     * action message is sent. See "CCControlEvent" for bitmask constants.
     */
    virtual void addTargetWithActionForControlEvents(Ref* target, Handler action, EventType controlEvents);

    /**
     * Removes a target and action for a particular event (or events) from an
     * internal dispatch table.
     *
     * @param target The target object that is, the object to which the action
     * message is sent. Pass nil to remove all targets paired with action and the
     * specified control events.
     * @param action A selector identifying an action message. Pass NULL to remove
     * all action messages paired with target.
     * @param controlEvents A bitmask specifying the control events associated with
     * target and action. See "CCControlEvent" for bitmask constants.
     */
    virtual void removeTargetWithActionForControlEvents(Ref* target, Handler action, EventType controlEvents);

    /**
     * Returns a point corresponding to the touch location converted into the
     * control space coordinates.
     * @param touch A Touch object that represents a touch.
     */
    virtual Vec2 getTouchLocation(Touch* touch);

    virtual bool onTouchBegan(Touch *touch, Event *event) override { return false; };
    virtual void onTouchMoved(Touch *touch, Event *event) override {};
    virtual void onTouchEnded(Touch *touch, Event *event) override {};
    virtual void onTouchCancelled(Touch *touch, Event *event) override {};
    
    /**
     * Returns a boolean value that indicates whether a touch is inside the bounds
     * of the receiver. The given touch must be relative to the world.
     *
     * @param touch A Touch object that represents a touch.
     *
     * @return Whether a touch is inside the receiver's rect.
     */
    virtual bool isTouchInside(Touch * touch);

    // Overrides
    virtual bool isOpacityModifyRGB() const override;
    virtual void setOpacityModifyRGB(bool bOpacityModifyRGB) override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    Control();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Control();

    virtual bool init(void) override;

protected:
    /**
     * Returns an Invocation object able to construct messages using a given 
     * target-action pair. (The invocation may optionally include the sender and
     * the event as parameters, in that order)
     *
     * @param target The target object.
     * @param action A selector identifying an action message.
     * @param controlEvent A control events for which the action message is sent.
     * See "CCControlEvent" for constants.
     *
     * @return an Invocation object able to construct messages using a given 
     * target-action pair.
     */
    Invocation* invocationWithTargetAndActionForControlEvent(Ref* target, Handler action, EventType controlEvent);

    /**
    * Returns the Invocation list for the given control event. If the list does
    * not exist, it'll create an empty array before returning it.
    *
    * @param controlEvent A control events for which the action message is sent.
    * See "CCControlEvent" for constants.
    *
    * @return the Invocation list for the given control event.
    */
    Vector<Invocation*>& dispatchListforControlEvent(EventType controlEvent);

    /**
     * Adds a target and action for a particular event to an internal dispatch 
     * table.
     * The action message may optionally include the sender and the event as 
     * parameters, in that order.
     * When you call this method, target is not retained.
     *
     * @param target The target object that is, the object to which the action
     * message is sent. It cannot be nil. The target is not retained.
     * @param action A selector identifying an action message. It cannot be NULL.
     * @param controlEvent A control event for which the action message is sent.
     * See "CCControlEvent" for constants.
     */
    void addTargetWithActionForControlEvent(Ref* target, Handler action, EventType controlEvent);
    
    /**
     * Removes a target and action for a particular event from an internal dispatch
     * table.
     *
     * @param target The target object that is, the object to which the action
     * message is sent. Pass nil to remove all targets paired with action and the
     * specified control events.
     * @param action A selector identifying an action message. Pass NULL to remove
     * all action messages paired with target.
     * @param controlEvent A control event for which the action message is sent.
     * See "CCControlEvent" for constants.
     */
    void removeTargetWithActionForControlEvent(Ref* target, Handler action, EventType controlEvent);

    bool _enabled;
    bool _selected;
    bool _highlighted;

    /** True if all of the controls parents are visible */
    bool _hasVisibleParents;

    /**
     * Table of connection between the ControlEvents and their associated
     * target-actions pairs. For each ButtonEvents a list of NSInvocation
     * (which contains the target-action pair) is linked.
     */
    std::unordered_map<int, Vector<Invocation*>*> _dispatchTable;

    //CCRGBAProtocol
    bool _isOpacityModifyRGB;

    /** The current control state constant. */
    CC_SYNTHESIZE_READONLY(State, _state, State);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Control);
};

CC_EX_DLL Control::EventType operator|(Control::EventType a, Control::EventType b);

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif
