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

class CCInvocation;

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
    CCControlEventTouchDown           = 1 << 0,    // A touch-down event in the control.
    CCControlEventTouchDragInside     = 1 << 1,    // An event where a finger is dragged inside the bounds of the control.
    CCControlEventTouchDragOutside    = 1 << 2,    // An event where a finger is dragged just outside the bounds of the control. 
    CCControlEventTouchDragEnter      = 1 << 3,    // An event where a finger is dragged into the bounds of the control.
    CCControlEventTouchDragExit       = 1 << 4,    // An event where a finger is dragged from within a control to outside its bounds.
    CCControlEventTouchUpInside       = 1 << 5,    // A touch-up event in the control where the finger is inside the bounds of the control. 
    CCControlEventTouchUpOutside      = 1 << 6,    // A touch-up event in the control where the finger is outside the bounds of the control.
    CCControlEventTouchCancel         = 1 << 7,    // A system event canceling the current touches for the control.
    CCControlEventValueChanged        = 1 << 8      // A touch dragging or otherwise manipulating a control, causing it to emit a series of different values.
};
typedef unsigned int CCControlEvent;

/** The possible state for a control.  */
enum 
{
    CCControlStateNormal       = 1 << 0, // The normal, or default state of a control¡ªthat is, enabled but neither selected nor highlighted.
    CCControlStateHighlighted  = 1 << 1, // Highlighted state of a control. A control enters this state when a touch down, drag inside or drag enter is performed. You can retrieve and set this value through the highlighted property.
    CCControlStateDisabled     = 1 << 2, // Disabled state of a control. This state indicates that the control is currently disabled. You can retrieve and set this value through the enabled property.
    CCControlStateSelected     = 1 << 3  // Selected state of a control. This state indicates that the control is currently selected. You can retrieve and set this value through the selected property.
};
typedef unsigned int CCControlState;

/*
 * @class
 * CCControl is inspired by the UIControl API class from the UIKit library of 
 * CocoaTouch. It provides a base class for control CCSprites such as CCButton 
 * or CCSlider that convey user intent to the application.
 *
 * The goal of CCControl is to define an interface and base implementation for 
 * preparing action messages and initially dispatching them to their targets when
 * certain events occur.
 *
 * To use the CCControl you have to subclass it.
 */
class CCControl : public CCLayer, public CCRGBAProtocol
{

    //CCRGBAProtocol
    CC_PROPERTY(GLubyte, m_cOpacity, Opacity); 
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);
    bool m_bIsOpacityModifyRGB;
    bool isOpacityModifyRGB();
    void setOpacityModifyRGB(bool bOpacityModifyRGB);

    /** Changes the priority of the button. The lower the number, the higher the priority. */
    CC_SYNTHESIZE(int, m_nDefaultTouchPriority, DefaultTouchPriority);
    /** The current control state constant. */
    CC_SYNTHESIZE_READONLY(CCControlState, m_eState, State);

    /** True if all of the controls parents are visible */
protected:
    bool m_hasVisibleParents;

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

protected:
    bool m_bEnabled;
    bool m_bSelected;
    bool m_bHighlighted;

    /** 
     * Table of connection between the CCControlEvents and their associated
     * target-actions pairs. For each CCButtonEvents a list of NSInvocation
     * (which contains the target-action pair) is linked.
     */
    CCDictionary* m_pDispatchTable;

public:
    CCControl();
    virtual bool init(void);
    virtual ~CCControl();


    virtual void onEnter();
    virtual void onExit();
    virtual void registerWithTouchDispatcher();

    /**
 * Sends action messages for the given control events.
 *
 * @param controlEvents A bitmask whose set flags specify the control events for
 * which action messages are sent. See "CCControlEvent" for bitmask constants.
 */
    virtual void sendActionsForControlEvents(CCControlEvent controlEvents);

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
    virtual void addTargetWithActionForControlEvents(CCObject* target, SEL_CCControlHandler action, CCControlEvent controlEvents);

    /**
    * Removes a target and action for a particular event (or events) from an 
    * internal dispatch table.
    *
    * @param target The target object—that is, the object to which the action 
    * message is sent. Pass nil to remove all targets paired with action and the
    * specified control events.
    * @param action A selector identifying an action message. Pass NULL to remove
    * all action messages paired with target.
    * @param controlEvents A bitmask specifying the control events associated with
    * target and action. See "CCControlEvent" for bitmask constants.
    */
    virtual void removeTargetWithActionForControlEvents(CCObject* target, SEL_CCControlHandler action, CCControlEvent controlEvents);

    /**
    * Returns a point corresponding to the touh location converted into the 
    * control space coordinates.
    * @param touch A CCTouch object that represents a touch.
    */
    virtual CCPoint getTouchLocation(CCTouch* touch);

    
    /**
    * Returns a boolean value that indicates whether a touch is inside the bounds
    * of the receiver. The given touch must be relative to the world.
    *
    * @param touch A CCTouch object that represents a touch.
    *
    * @return YES whether a touch is inside the receiver¡¯s rect.
    */
    virtual bool isTouchInside(CCTouch * touch);


protected:
    /**
     * Returns an CCInvocation object able to construct messages using a given 
     * target-action pair. (The invocation may optionnaly include the sender and
     * the event as parameters, in that order)
     *
     * @param target The target object.
     * @param action A selector identifying an action message.
     * @param controlEvent A control events for which the action message is sent.
     * See "CCControlEvent" for constants.
     *
     * @return an CCInvocation object able to construct messages using a given 
     * target-action pair.
     */
    CCInvocation* invocationWithTargetAndActionForControlEvent(CCObject* target, SEL_CCControlHandler action, CCControlEvent controlEvent);



    /**
    * Returns the CCInvocation list for the given control event. If the list does
    * not exist, it'll create an empty array before returning it.
    *
    * @param controlEvent A control events for which the action message is sent.
    * See "CCControlEvent" for constants.
    *
    * @return the CCInvocation list for the given control event.
    */
    //<CCInvocation*>
    CCArray* dispatchListforControlEvent(CCControlEvent controlEvent);
    /**
     * Adds a target and action for a particular event to an internal dispatch 
     * table.
     * The action message may optionnaly include the sender and the event as 
     * parameters, in that order.
     * When you call this method, target is not retained.
     *
     * @param target The target object¡ªthat is, the object to which the action 
     * message is sent. It cannot be nil. The target is not retained.
     * @param action A selector identifying an action message. It cannot be NULL.
     * @param controlEvent A control event for which the action message is sent.
     * See "CCControlEvent" for constants.
     */
    void addTargetWithActionForControlEvent(CCObject* target, SEL_CCControlHandler action, CCControlEvent controlEvent);
    
    /**
     * Removes a target and action for a particular event from an internal dispatch
     * table.
     *
     * @param target The target object¡ªthat is, the object to which the action 
     * message is sent. Pass nil to remove all targets paired with action and the
     * specified control events.
     * @param action A selector identifying an action message. Pass NULL to remove
     * all action messages paired with target.
     * @param controlEvent A control event for which the action message is sent.
     * See "CCControlEvent" for constants.
     */
    void removeTargetWithActionForControlEvent(CCObject* target, SEL_CCControlHandler action, CCControlEvent controlEvent);

    static CCControl* create();

};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif