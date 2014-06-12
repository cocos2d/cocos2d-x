/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#include "CCController.h"
#include "base/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "CCGamepad.h"
#include "CCControllerDirectionPad.h"
#include "CCControllerButtonInput.h"
#include "CCControllerAxisInput.h"
#include "CCControllerThumbstick.h"

#include "ccMacros.h"
#include "CCEventDispatcher.h"
#include "CCEventController.h"
#include "CCEventListenerController.h"
#include "CCDirector.h"

#import <GameController/GameController.h>

#include "CCNSLog.h"

@interface GCControllerConnectionEventHandler : NSObject

typedef void (^GCControllerConnectionBlock)(GCController* controller);
@property (copy) GCControllerConnectionBlock _connectionBlock;

typedef void (^GCControllerDisconnectionBlock)(GCController* controller);
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

#define sendEventButton(dstID, srcID) \
dstID->setPressed(srcID.isPressed); \
dstID->setValue(srcID.value); \
dstID->setAnalog(srcID.isAnalog); \
EventController evt(EventController::ControllerEventType::BUTTON_STATUS_CHANGED, this, dstID); \
Director::getInstance()->getEventDispatcher()->dispatchEvent(&evt);


#define sendEventAxis(dstID, srcID) \
\
dstID->setValue(srcID.value); \
dstID->setAnalog(srcID.isAnalog); \
\
EventController evt(EventController::ControllerEventType::AXIS_STATUS_CHANGED, this, dstID); \
Director::getInstance()->getEventDispatcher()->dispatchEvent(&evt);

class ControllerImpl
{
public:
    ControllerImpl(Controller* controller)
    : _controller(controller)
    , _gcController(nil)
    {

    }
    
    ~ControllerImpl()
    {

    }
    
    Controller* _controller;
    GCController* _gcController;
};

std::vector<Controller*> Controller::_controllers;

const std::vector<Controller*>& Controller::getControllers()
{
    return _controllers;
}

void Controller::startDiscoveryController()
{
    CCNSLOG("startDiscoveryController...: %s", "hello");
    
    [GCController startWirelessControllerDiscoveryWithCompletionHandler: nil];

    [[GCControllerConnectionEventHandler getInstance] observerConnection: ^(GCController* gcController) {
        auto controller = new Controller();
        controller->_impl->_gcController = gcController;
        
        gcController.controllerPausedHandler = ^(GCController* gcCon){
            
            CCNSLOG("Controller(%p)'s paused handler was invoked.", gcCon);
            auto iter = std::find_if(_controllers.begin(), _controllers.end(), [gcCon](Controller* c){ return c->_impl->_gcController == gcCon; });
            
            CCASSERT(iter != _controllers.end(), "Could not find the controller");
            
            auto button = (*iter)->getGamepad()->getButtonPause();
            button->setPressed(true);
            EventController evt(EventController::ControllerEventType::BUTTON_STATUS_CHANGED, (*iter), button);
            Director::getInstance()->getEventDispatcher()->dispatchEvent(&evt);
            
            // Reset the pause button status to unpressed.
            button->setPressed(false);
        };
        
        CCNSLOG("controller %p was connnected!", gcController);
        _controllers.push_back(controller);
        
        
        EventController evt(EventController::ControllerEventType::CONNECTION, controller, true);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&evt);
        
    } disconnection: ^(GCController* gcController) {
        CCNSLOG("controller %p was disconnected!", gcController);
        
        auto iter = std::find_if(_controllers.begin(), _controllers.end(), [gcController](Controller* c){ return c->_impl->_gcController == gcController; });
        
        CCASSERT(iter != _controllers.end(), "Could not find the controller");
        
        EventController evt(EventController::ControllerEventType::CONNECTION, *iter, false);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&evt);
        
        delete (*iter);
        _controllers.erase(iter);
    }];
}

void Controller::stopDiscoveryController()
{
    [GCController stopWirelessControllerDiscovery];
}

Controller::Controller()
{
    _playerIndex = PLAYER_INDEX_UNSET;
    _gamepad = new Gamepad();
    _gamepad->_controller = this;
    _impl = new ControllerImpl(this);
}

Controller::~Controller()
{
    CC_SAFE_DELETE(_impl);
    CC_SAFE_DELETE(_gamepad);
}

const std::string& Controller::getVendorName()
{
    if (_vendorName.empty())
    {
        _vendorName = [_impl->_gcController.vendorName UTF8String];
    }
    return _vendorName;
}

bool Controller::isConnected() const
{
    return _impl->_gcController.isAttachedToDevice == YES;
}

int Controller::getPlayerIndex() const
{
    return _playerIndex;
}

void Controller::setPlayerIndex(int playerIndex)
{
    _playerIndex = playerIndex;
}

Gamepad* Controller::getGamepad()
{
    if (_impl->_gcController == nil)
        return nullptr;
    
    if (_impl->_gcController.gamepad != nil || _impl->_gcController.extendedGamepad != nil)
    {
        if (_impl->_gcController.extendedGamepad != nil)
        {
            _impl->_gcController.extendedGamepad.dpad.up.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
                CCNSLOG("dpad up %d, %f", button.pressed, button.value);
                sendEventButton(_gamepad->getDirectionPad()->getUp(), button);
            };
            
            _impl->_gcController.extendedGamepad.dpad.down.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
                CCNSLOG("dpad down %d, %f", button.pressed, button.value);
                sendEventButton(_gamepad->getDirectionPad()->getDown(), button);
            };
            
            _impl->_gcController.extendedGamepad.dpad.left.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
                CCNSLOG("dpad left %d, %f", button.pressed, button.value);
                sendEventButton(_gamepad->getDirectionPad()->getLeft(), button);
            };
            
            _impl->_gcController.extendedGamepad.dpad.right.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
                CCNSLOG("dpad right %d, %f", button.pressed, button.value);
                sendEventButton(_gamepad->getDirectionPad()->getRight(), button);
            };
            
            _impl->_gcController.extendedGamepad.leftThumbstick.xAxis.valueChangedHandler = ^(GCControllerAxisInput *axis, float value){
                sendEventAxis(_gamepad->getLeftThumbstick()->getAxisX(), axis);
            };
            
            _impl->_gcController.extendedGamepad.leftThumbstick.yAxis.valueChangedHandler = ^(GCControllerAxisInput *axis, float value){
                sendEventAxis(_gamepad->getLeftThumbstick()->getAxisY(), axis);
            };
            
            _impl->_gcController.extendedGamepad.rightThumbstick.xAxis.valueChangedHandler = ^(GCControllerAxisInput *axis, float value){
                sendEventAxis(_gamepad->getRightThumbstick()->getAxisX(), axis);
            };
            
            _impl->_gcController.extendedGamepad.rightThumbstick.yAxis.valueChangedHandler = ^(GCControllerAxisInput *axis, float value){
                sendEventAxis(_gamepad->getRightThumbstick()->getAxisY(), axis);
            };
            
            _impl->_gcController.extendedGamepad.valueChangedHandler = ^(GCExtendedGamepad *gamepad, GCControllerElement *element){
                if (element == gamepad.buttonA)
                {
                    sendEventButton(_gamepad->getButtonA(), gamepad.buttonA);
                }
                else if (element == gamepad.buttonB)
                {
                    sendEventButton(_gamepad->getButtonB(), gamepad.buttonB);
                }
                else if (element == gamepad.buttonX)
                {
                    sendEventButton(_gamepad->getButtonX(), gamepad.buttonX);
                }
                else if (element == gamepad.buttonY)
                {
                    sendEventButton(_gamepad->getButtonY(), gamepad.buttonY);
                }
                else if (element == gamepad.leftShoulder)
                {
                    sendEventButton(_gamepad->getLeftShoulder(), gamepad.leftShoulder);
                }
                else if (element == gamepad.rightShoulder)
                {
                    sendEventButton(_gamepad->getRightShoulder(), gamepad.rightShoulder);
                }
                else if (element == gamepad.leftTrigger)
                {
                    sendEventButton(_gamepad->getLeftTrigger(), gamepad.leftTrigger);
                }
                else if (element == gamepad.rightTrigger)
                {
                    sendEventButton(_gamepad->getRightTrigger(), gamepad.rightTrigger);
                }
            };
        }
        else
        {
            _impl->_gcController.gamepad.dpad.up.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
                CCNSLOG("dpad up %d, %f", button.pressed, button.value);
                sendEventButton(_gamepad->getDirectionPad()->getUp(), button);
            };

            _impl->_gcController.gamepad.dpad.down.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
                CCNSLOG("dpad down %d, %f", button.pressed, button.value);
                sendEventButton(_gamepad->getDirectionPad()->getDown(), button);
            };
            
            _impl->_gcController.gamepad.dpad.left.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
                CCNSLOG("dpad left %d, %f", button.pressed, button.value);
                sendEventButton(_gamepad->getDirectionPad()->getLeft(), button);
            };
            
            _impl->_gcController.gamepad.dpad.right.valueChangedHandler = ^(GCControllerButtonInput *button, float value, BOOL pressed){
                CCNSLOG("dpad right %d, %f", button.pressed, button.value);
                sendEventButton(_gamepad->getDirectionPad()->getRight(), button);
            };
            
            _impl->_gcController.gamepad.valueChangedHandler = ^(GCGamepad *gamepad, GCControllerElement *element){
                
                if (element == gamepad.buttonA)
                {
                    sendEventButton(_gamepad->getButtonA(), gamepad.buttonA);
                }
                else if (element == gamepad.buttonB)
                {
                    sendEventButton(_gamepad->getButtonB(), gamepad.buttonB);
                }
                else if (element == gamepad.buttonX)
                {
                    sendEventButton(_gamepad->getButtonX(), gamepad.buttonX);
                }
                else if (element == gamepad.buttonY)
                {
                    sendEventButton(_gamepad->getButtonY(), gamepad.buttonY);
                }
                else if (element == gamepad.leftShoulder)
                {
                    sendEventButton(_gamepad->getLeftShoulder(), gamepad.leftShoulder);
                }
                else if (element == gamepad.rightShoulder)
                {
                    sendEventButton(_gamepad->getRightShoulder(), gamepad.rightShoulder);
                }
            };
        }
    }
    else
    {
        CCASSERT(false, "No gamepad was found!");
    }
    
    return _gamepad;
}

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
