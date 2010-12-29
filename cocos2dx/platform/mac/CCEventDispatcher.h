/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2010 Ricardo Quesada
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
 */

// Only compile this code on Mac. These files should not be included on your iOS project.
// But in case they are included, it won't be compiled.
#import <Availability.h>
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#elif defined(__MAC_OS_X_VERSION_MAX_ALLOWED)

#import <Cocoa/Cocoa.h>

#import "MacGLView.h"
#import "../../Support/uthash.h"	// hack: uthash needs to be imported before utlist to prevent warning
#import "../../Support/utlist.h"
#import "../../ccConfig.h"

#pragma mark -
#pragma mark CCMouseEventDelegate

/** CCMouseEventDelegate protocol.
 Implement it in your node to receive any of mouse events
 */
@protocol CCMouseEventDelegate <NSObject>
@optional

//
// left
//
/** called when the "mouseDown" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccMouseDown:(NSEvent*)event;

/** called when the "mouseDragged" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccMouseDragged:(NSEvent*)event;

/** called when the "mouseMoved" event is received.
 Return YES to avoid propagating the event to other delegates.
 By default, "mouseMoved" is disabled. To enable it, send the "setAcceptsMouseMovedEvents:YES" message to the main window.
 */
-(BOOL) ccMouseMoved:(NSEvent*)event;

/** called when the "mouseUp" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccMouseUp:(NSEvent*)event;


//
// right
//

/** called when the "rightMouseDown" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccRightMouseDown:(NSEvent*)event;

/** called when the "rightMouseDragged" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccRightMouseDragged:(NSEvent*)event;

/** called when the "rightMouseUp" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccRightMouseUp:(NSEvent*)event;

//
// other
//

/** called when the "otherMouseDown" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccOtherMouseDown:(NSEvent*)event;

/** called when the "otherMouseDragged" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccOtherMouseDragged:(NSEvent*)event;

/** called when the "otherMouseUp" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccOtherMouseUp:(NSEvent*)event;

//
// scroll wheel
//

/** called when the "scrollWheel" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (BOOL)ccScrollWheel:(NSEvent *)theEvent;


//
// enter / exit
//

/** called when the "mouseEntered" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (void)ccMouseEntered:(NSEvent *)theEvent;

/** called when the "mouseExited" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
- (void)ccMouseExited:(NSEvent *)theEvent;

@end

#pragma mark -
#pragma mark CCKeyboardEventDelegate

/** CCKeyboardEventDelegate protocol.
 Implement it in your node to receive any of keyboard events
 */
@protocol CCKeyboardEventDelegate <NSObject>
@optional
/** called when the "keyUp" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccKeyUp:(NSEvent*)event;

/** called when the "keyDown" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccKeyDown:(NSEvent*)event;
/** called when the "flagsChanged" event is received.
 Return YES to avoid propagating the event to other delegates.
 */
-(BOOL) ccFlagsChanged:(NSEvent*)event;
@end


#pragma mark -
#pragma mark CCEventDispatcher

struct _listEntry;

/** CCEventDispatcher
 
 This is object is responsible for dispatching the events:
	- Mouse events
	- Keyboard events
	- Touch events
 
 Only available on Mac
 */
@interface CCEventDispatcher : NSObject <MacEventDelegate> {

	BOOL					dispatchEvents_;
	
	struct	_listEntry		*keyboardDelegates_;
	struct	_listEntry		*mouseDelegates_;
}

@property (nonatomic, readwrite) BOOL dispatchEvents;


/** CCEventDispatcher singleton */
+(CCEventDispatcher*) sharedDispatcher;

#pragma mark CCEventDispatcher - Mouse

/** Adds a mouse delegate to the dispatcher's list.
 Delegates with a lower priority value will be called before higher priority values.
 All the events will be propgated to all the delegates, unless the one delegate returns YES.

 IMPORTANT: The delegate will be retained.
 */
-(void) addMouseDelegate:(id<CCMouseEventDelegate>) delegate priority:(NSInteger)priority;

/** removes a mouse delegate */
-(void) removeMouseDelegate:(id) delegate;

/** Removes all mouse delegates, releasing all the delegates */
-(void) removeAllMouseDelegates;

#pragma mark CCEventDispatcher - Keyboard

/** Adds a Keyboard delegate to the dispatcher's list.
 Delegates with a lower priority value will be called before higher priority values.
 All the events will be propgated to all the delegates, unless the one delegate returns YES.
 
 IMPORTANT: The delegate will be retained.
 */
-(void) addKeyboardDelegate:(id<CCKeyboardEventDelegate>) delegate priority:(NSInteger)priority;

/** removes a mouse delegate */
-(void) removeKeyboardDelegate:(id) delegate;

/** Removes all mouse delegates, releasing all the delegates */
-(void) removeAllKeyboardDelegates;

#pragma mark CCEventDispatcher - Touches

// XXX

#pragma mark CCEventDispatcher - Dispatch Events

#if CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
-(void) dispatchQueuedEvents;
#endif

@end


#endif // __MAC_OS_X_VERSION_MAX_ALLOWED
