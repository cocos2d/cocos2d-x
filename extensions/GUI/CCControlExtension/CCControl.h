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

#include "CCInvocation.h"
#include "CCControlUtils.h"
#include "cocos2d.h"

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

/** Kinds of possible events for the control objects. */
enum 
{
    ControlEventTouchDown           = 1 << 0,    // A touch-down event in the control.
    ControlEventTouchDragInside     = 1 << 1,    // An event where a finger is dragged inside the bounds of the control.
    ControlEventTouchDragOutside    = 1 << 2,    // An event where a finger is dragged just outside the bounds of the control. 
    ControlEventTouchDragEnter      = 1 << 3,    // An event where a finger is dragged into the bounds of the control.
    ControlEventTouchDragExit       = 1 << 4,    // An event where a finger is dragged from within a control to outside its bounds.
    ControlEventTouchUpInside       = 1 << 5,    // A touch-up event in the control where the finger is inside the bounds of the control. 
    ControlEventTouchUpOutside      = 1 << 6,    // A touch-up event in the control where the finger is outside the bounds of the control.
    ControlEventTouchCancel         = 1 << 7,    // A system event canceling the current touches for the control.
    ControlEventValueChanged        = 1 << 8      // A touch dragging or otherwise manipulating a control, causing it to emit a series of different values.
};
typedef unsigned int ControlEvent;

/** The possible state for a control.  */
enum 
{
    ControlStateNormal       = 1 << 0, // The normal, or default state of a control��that is, enabled but neither selected nor highlighted.
    ControlStateHighlighted  = 1 << 1, // Highlighted state of a control. A control enters this state when a touch down, drag inside or drag enter is performed. You can retrieve and set this value through the highlighted property.
    ControlStateDisabled     = 1 << 2, // Disabled state of a control. This state indicates that the control is currently disabled. You can retrieve and set this value through the enabled property.
    ControlStateSelected     = 1 << 3  // Selected state of a control. This state indicates that the control is currently selected. You can retrieve and set this value through the selected property.
};
typedef unsigned int ControlState;

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
class Control : public LayerRGBA
{

    //CCRGBAProtocol
    bool _isOpacityModifyRGB;
    
    /** The current control state constant. */
    CC_SYNTHESIZE_READONLY(ControlState, _state, State);

    /** True if all of the controls parents are visible */
protected:
    bool _hasVisibleParents;

public:
    /** Tells whether the control is enabled. */
    virtual void setEnabled(bool bEnabled);
    virtual bool isEnabled();
    /** A Boolean value that determines the control selected state. */
    virtual void setSelected(bool bSelected);
    virtual bool isSelected();
    /** A Boolean value that determines whether the control is highlighted. */
    virtual void setHighlighted(bool bHighlighted);
    virtual bool isHighlighted();
    bool hasVisibleParents();
    /**
     * Updates the control layout using its current internal state.
     */
    virtual void needsLayout();
    
    virtual bool isOpacityModifyRGB();
    virtual void setOpacityModifyRGB(bool bOpacityModifyRGB);

protected:
    bool _enabled;
    bool _selected;
    bool _highlighted;

    /** 
     * Table of connection between the ControlEvents and their associated
     * target-actions pairs. For each ButtonEvents a list of NSInvocation
     * (which contains the target-action pair) is linked.
     */
    Dictionary* _dispatchTable;

public:
    Control();
    virtual bool init(void);
    virtual ~Control();


    virtual void onEnter();
    virtual void onExit();
    virtual void registerWithTouchDispatcher();

    /**
 * Sends action messages for the given control events.
 *
 * @param controlEvents A bitmask whose set flags specify the control events for
 * which action messages are sent. See "CCControlEvent" for bitmask constants.
 */
    virtual void sendActionsForControlEvents(ControlEvent controlEvents);

    /**
    * Adds a target and action for a particular event (or events) to an internal
    * dispatch table.
    * The action message may optionnaly include the sender and the event as 
    * parameters, in that order.
    * When you call this method, target is not retained.
    *
    * @param target The target object that is, the object to which the action 
    * message is sent. It cannot be nil. The target is not retained.
    * @param action A selector identifying an action message. It cannot be NULL.
    * @param controlEvents A bitmask specifying the control events for which the 
    * action message is sent. See "CCControlEvent" for bitmask constants.
    */
    virtual void addTargetWithActionForControlEvents(Object* target, SEL_CCControlHandler action, ControlEvent controlEvents);

    /**
    * Removes a target and action for a particular event (or events) from an 
    * internal dispatch table.
    *
    * @param target The target object�that is, the object to which the action 
    * message is sent. Pass nil to remove all targets paired with action and the
    * specified control events.
    * @param action A selector identifying an action message. Pass NULL to remove
    * all action messages paired with target.
    * @param controlEvents A bitmask specifying the control events associated with
    * target and action. See "CCControlEvent" for bitmask constants.
    */
    virtual void removeTargetWithActionForControlEvents(Object* target, SEL_CCControlHandler action, ControlEvent controlEvents);

    /**
    * Returns a point corresponding to the touh location converted into the 
    * control space coordinates.
    * @param touch A Touch object that represents a touch.
    */
    virtual Point getTouchLocation(Touch* touch);

    
    /**
    * Returns a boolean value that indicates whether a touch is inside the bounds
    * of the receiver. The given touch must be relative to the world.
    *
    * @param touch A Touch object that represents a touch.
    *
    * @return YES whether a touch is inside the receiver��s rect.
    */
    virtual bool isTouchInside(Touch * touch);


protected:
    /**
     * Returns an Invocation object able to construct messages using a given 
     * target-action pair. (The invocation may optionnaly include the sender and
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
    Invocation* invocationWithTargetAndActionForControlEvent(Object* target, SEL_CCControlHandler action, ControlEvent controlEvent);



    /**
    * Returns the Invocation list for the given control event. If the list does
    * not exist, it'll create an empty array before returning it.
    *
    * @param controlEvent A control events for which the action message is sent.
    * See "CCControlEvent" for constants.
    *
    * @return the Invocation list for the given control event.
    */
    //<Invocation*>
    Array* dispatchListforControlEvent(ControlEvent controlEvent);
    /**
     * Adds a target and action for a particular event to an internal dispatch 
     * table.
     * The action message may optionnaly include the sender and the event as 
     * parameters, in that order.
     * When you call this method, target is not retained.
     *
     * @param target The target object��that is, the object to which the action 
     * message is sent. It cannot be nil. The target is not retained.
     * @param action A selector identifying an action message. It cannot be NULL.
     * @param controlEvent A control event for which the action message is sent.
     * See "CCControlEvent" for constants.
     */
    void addTargetWithActionForControlEvent(Object* target, SEL_CCControlHandler action, ControlEvent controlEvent);
    
    /**
     * Removes a target and action for a particular event from an internal dispatch
     * table.
     *
     * @param target The target object��that is, the object to which the action 
     * message is sent. Pass nil to remove all targets paired with action and the
     * specified control events.
     * @param action A selector identifying an action message. Pass NULL to remove
     * all action messages paired with target.
     * @param controlEvent A control event for which the action message is sent.
     * See "CCControlEvent" for constants.
     */
    void removeTargetWithActionForControlEvent(Object* target, SEL_CCControlHandler action, ControlEvent controlEvent);

    static Control* create();
public:
    void addHandleOfControlEvent(int nFunID,ControlEvent controlEvent);
    void removeHandleOfControlEvent(ControlEvent controlEvent);
private:
    int  getHandleOfControlEvent(ControlEvent controlEvent);
private:
    std::map<int,int> _mapHandleOfControlEvent;
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif