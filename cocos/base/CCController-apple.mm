/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "base/CCController.h"
#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#include "base/ccMacros.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventController.h"
#include "base/CCEventListenerController.h"
#include "base/CCDirector.h"
#include "2d/CCLabel.h"

#import <GameController/GameController.h>

typedef void (^GCControllerConnectionBlock)(GCController* controller);
typedef void (^GCControllerDisconnectionBlock)(GCController* controller);

@interface GCControllerConnectionEventHandler : NSObject
{
}

@property (copy) GCControllerConnectionBlock _connectionBlock;
@property (copy) GCControllerDisconnectionBlock _disconnectionBlock;

+(GCControllerConnectionEventHandler*) getInstance;
+(void) destroyInstance;
@end

@implementation GCControllerConnectionEventHandler


static GCControllerConnectionEventHandler* __instance = nil;

+(GCControllerConnectionEventHandler*) getInstance {
    
    if (__instance == nil)
    {
        __instance = [[GCControllerConnectionEventHandler alloc] init];
    }
    return __instance;
}

+(void) destroyInstance {
    if (__instance)
    {
        [__instance release];
        __instance = nil;
    }
}

-(void) observerConnection: (GCControllerConnectionBlock) connectBlock disconnection: (GCControllerDisconnectionBlock) disconnectBlock {
    self._connectionBlock = connectBlock;
    self._disconnectionBlock = disconnectBlock;

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onControllerConnected:) name:GCControllerDidConnectNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onControllerDisconnected:) name:GCControllerDidDisconnectNotification object:nil];
}

-(void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];

    // Have to reset 'copy' property to nil value to avoid memory leak.
    self._connectionBlock = nil;
    self._disconnectionBlock = nil;

    [super dealloc];
}

-(void) onControllerConnected :(NSNotification *)connectedNotification {
    GCController *controller =(GCController *)[connectedNotification object];
    
    self._connectionBlock(controller);
}

-(void) onControllerDisconnected :(NSNotification *)connectedNotification {
    
    GCController *controller =(GCController *)[connectedNotification object];
    self._disconnectionBlock(controller);
}

@end

NS_CC_BEGIN

class ControllerImpl
{
public:
    ControllerImpl(Controller* controller)
    : _controller(controller)
    , _gcController(nil)
    {
        
    }
    
    Controller* _controller;
    GCController* _gcController;
};

void Controller::startDiscoveryController()
{
    if (NSClassFromString(@"GCController") == nil) {
        return;
    }
    [GCController startWirelessControllerDiscoveryWithCompletionHandler: nil];
    
    [[GCControllerConnectionEventHandler getInstance] observerConnection: ^(GCController* gcController) {
        
        auto controller = new (std::nothrow) Controller();
        controller->_impl->_gcController = gcController;
        controller->_deviceName = [gcController.vendorName UTF8String];
        
        s_allController.push_back(controller);
        
        controller->registerListeners();
        controller->getDeviceName();
        
        controller->onConnected();
        
    } disconnection: ^(GCController* gcController) {
        auto iter = std::find_if(s_allController.begin(), s_allController.end(), [gcController](Controller* c){ return c->_impl->_gcController == gcController; });
        
        if(iter == s_allController.end())
        {
            log("disconnect:Could not find the controller");
            return;
        }
        
        (*iter)->onDisconnected();
        s_allController.erase(iter);
        
    }];
}

void Controller::stopDiscoveryController()
{
    if (NSClassFromString(@"GCController") == nil) {
        return;
    }
    [GCController stopWirelessControllerDiscovery];
}

Controller::Controller()
: _deviceId(0)
, _controllerTag(TAG_UNSET)
, _impl(new ControllerImpl(this))
, _connectEvent(nullptr)
, _keyEvent(nullptr)
, _axisEvent(nullptr)
{
    init();
}

Controller::~Controller()
{
    delete _impl;
    
    delete _connectEvent;
    delete _keyEvent;
    delete _axisEvent;
}

void Controller::registerListeners()
{
    if (_impl->_gcController.extendedGamepad != nil)
    {
        _impl->_gcController.extendedGamepad.dpad.up.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
            onButtonEvent(Key::BUTTON_DPAD_UP, pressed, value, button.isAnalog);
        };
        
        _impl->_gcController.extendedGamepad.dpad.down.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
            onButtonEvent(Key::BUTTON_DPAD_DOWN, pressed, value, button.isAnalog);
        };
        
        _impl->_gcController.extendedGamepad.dpad.left.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
            onButtonEvent(Key::BUTTON_DPAD_LEFT, pressed, value, button.isAnalog);
        };
        
        _impl->_gcController.extendedGamepad.dpad.right.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
            onButtonEvent(Key::BUTTON_DPAD_RIGHT, pressed, value, button.isAnalog);
        };
        
        _impl->_gcController.extendedGamepad.leftThumbstick.xAxis.valueChangedHandler = ^(GCControllerAxisInput *axis, float value){
            onAxisEvent(Key::JOYSTICK_LEFT_X, value, axis.isAnalog);
        };
        
        _impl->_gcController.extendedGamepad.leftThumbstick.yAxis.valueChangedHandler = ^(GCControllerAxisInput *axis, float value){
            onAxisEvent(Key::JOYSTICK_LEFT_Y, -value, axis.isAnalog);
        };
        
        _impl->_gcController.extendedGamepad.rightThumbstick.xAxis.valueChangedHandler = ^(GCControllerAxisInput *axis, float value){
            onAxisEvent(Key::JOYSTICK_RIGHT_X, value, axis.isAnalog);
        };
        
        _impl->_gcController.extendedGamepad.rightThumbstick.yAxis.valueChangedHandler = ^(GCControllerAxisInput *axis, float value){
            onAxisEvent(Key::JOYSTICK_RIGHT_Y, -value, axis.isAnalog);
        };
        
        _impl->_gcController.extendedGamepad.valueChangedHandler = ^(GCExtendedGamepad *gamepad, GCControllerElement *element){
            if (element == gamepad.buttonA)
            {
                onButtonEvent(Key::BUTTON_A, gamepad.buttonA.isPressed, gamepad.buttonA.value, gamepad.buttonA.isAnalog);
            }
            else if (element == gamepad.buttonB)
            {
                onButtonEvent(Key::BUTTON_B, gamepad.buttonB.isPressed, gamepad.buttonB.value, gamepad.buttonB.isAnalog);
            }
            else if (element == gamepad.buttonX)
            {
                onButtonEvent(Key::BUTTON_X, gamepad.buttonX.isPressed, gamepad.buttonX.value, gamepad.buttonX.isAnalog);
            }
            else if (element == gamepad.buttonY)
            {
                onButtonEvent(Key::BUTTON_Y, gamepad.buttonY.isPressed, gamepad.buttonY.value, gamepad.buttonY.isAnalog);
            }
            else if (element == gamepad.leftShoulder)
            {
                onButtonEvent(Key::BUTTON_LEFT_SHOULDER, gamepad.leftShoulder.isPressed, gamepad.leftShoulder.value, gamepad.leftShoulder.isAnalog);
            }
            else if (element == gamepad.rightShoulder)
            {
                onButtonEvent(Key::BUTTON_RIGHT_SHOULDER, gamepad.rightShoulder.isPressed, gamepad.rightShoulder.value, gamepad.rightShoulder.isAnalog);
            }
            else if (element == gamepad.leftTrigger)
            {
                onAxisEvent(Key::AXIS_LEFT_TRIGGER, gamepad.leftTrigger.value, gamepad.leftTrigger.isAnalog);
            }
            else if (element == gamepad.rightTrigger)
            {
                onAxisEvent(Key::AXIS_RIGHT_TRIGGER, gamepad.rightTrigger.value, gamepad.rightTrigger.isAnalog);
            }
        };
    }
    else if (_impl->_gcController.gamepad != nil)
    {
        _impl->_gcController.gamepad.dpad.up.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
            onButtonEvent(Key::BUTTON_DPAD_UP, pressed, value, button.isAnalog);
        };
        
        _impl->_gcController.gamepad.dpad.down.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
            onButtonEvent(Key::BUTTON_DPAD_DOWN, pressed, value, button.isAnalog);
        };
        
        _impl->_gcController.gamepad.dpad.left.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
            onButtonEvent(Key::BUTTON_DPAD_LEFT, pressed, value, button.isAnalog);
        };
        
        _impl->_gcController.gamepad.dpad.right.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
            onButtonEvent(Key::BUTTON_DPAD_RIGHT, pressed, value, button.isAnalog);
        };
        
        _impl->_gcController.gamepad.valueChangedHandler = ^(GCGamepad *gamepad, GCControllerElement *element){
            
            if (element == gamepad.buttonA)
            {
                onButtonEvent(Key::BUTTON_A, gamepad.buttonA.isPressed, gamepad.buttonA.value, gamepad.buttonA.isAnalog);
            }
            else if (element == gamepad.buttonB)
            {
                onButtonEvent(Key::BUTTON_B, gamepad.buttonB.isPressed, gamepad.buttonB.value, gamepad.buttonB.isAnalog);
            }
            else if (element == gamepad.buttonX)
            {
                onButtonEvent(Key::BUTTON_X, gamepad.buttonX.isPressed, gamepad.buttonX.value, gamepad.buttonX.isAnalog);
            }
            else if (element == gamepad.buttonY)
            {
                onButtonEvent(Key::BUTTON_Y, gamepad.buttonY.isPressed, gamepad.buttonY.value, gamepad.buttonY.isAnalog);
            }
            else if (element == gamepad.leftShoulder)
            {
                onButtonEvent(Key::BUTTON_LEFT_SHOULDER, gamepad.leftShoulder.isPressed, gamepad.leftShoulder.value, gamepad.leftShoulder.isAnalog);
            }
            else if (element == gamepad.rightShoulder)
            {
                onButtonEvent(Key::BUTTON_RIGHT_SHOULDER, gamepad.rightShoulder.isPressed, gamepad.rightShoulder.value, gamepad.rightShoulder.isAnalog);
            }
        };
    }
#if defined(CC_TARGET_OS_TVOS)
    else if (_impl->_gcController.microGamepad != nil)
    {
        _impl->_gcController.microGamepad.dpad.up.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
            onButtonEvent(Key::BUTTON_DPAD_UP, pressed, value, button.isAnalog);
        };
        
        _impl->_gcController.microGamepad.dpad.down.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
            onButtonEvent(Key::BUTTON_DPAD_DOWN, pressed, value, button.isAnalog);
        };
        
        _impl->_gcController.microGamepad.dpad.left.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
            onButtonEvent(Key::BUTTON_DPAD_LEFT, pressed, value, button.isAnalog);
        };
        
        _impl->_gcController.microGamepad.dpad.right.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
            onButtonEvent(Key::BUTTON_DPAD_RIGHT, pressed, value, button.isAnalog);
        };
        
        _impl->_gcController.microGamepad.valueChangedHandler = ^(GCMicroGamepad *gamepad, GCControllerElement *element){
            
            if (element == gamepad.buttonA)
            {
                onButtonEvent(Key::BUTTON_A, gamepad.buttonA.isPressed, gamepad.buttonA.value, gamepad.buttonA.isAnalog);
            }
            else if (element == gamepad.buttonX)
            {
                onButtonEvent(Key::BUTTON_X, gamepad.buttonX.isPressed, gamepad.buttonX.value, gamepad.buttonX.isAnalog);
            }
        };
    }
#endif
    
    _impl->_gcController.controllerPausedHandler = ^(GCController* gcCon){
        
        auto iter = std::find_if(s_allController.begin(), s_allController.end(), [gcCon](Controller* c){ return c->_impl->_gcController == gcCon; });
        
        if(iter == s_allController.end())
        {
            log("Could not find the controller");
            return;
        }
        
        onButtonEvent(Key::BUTTON_PAUSE, true, 1.0f, false);
        onButtonEvent(Key::BUTTON_PAUSE, false, 0.0f, false);
    };
}

bool Controller::isConnected() const
{
    return _impl->_gcController.isAttachedToDevice == YES;
}

void Controller::receiveExternalKeyEvent(int externalKeyCode,bool receive)
{
}

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
