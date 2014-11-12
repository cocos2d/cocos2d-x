
#include "native/CCNative.h"
#import <UIKit/UIKit.h>
#import "platform/ios/CCNativeIOS.h"
#import "platform/ios/openudid/OpenUDIDIOS.h"
#import "AudioToolbox/AudioServices.h"

NS_CC_EXTRA_BEGIN

#pragma mark -
#pragma mark activity indicator

void Native::showActivityIndicator(void)
{
    [[NativeIOS sharedInstance] showActivityIndicator:UIActivityIndicatorViewStyleWhiteLarge];
}

void Native::hideActivityIndicator(void)
{
    [[NativeIOS sharedInstance] hideActivityIndicator];
}

#pragma mark -
#pragma mark alert view

void Native::createAlert(const char* title,
                           const char* message,
                           const char* cancelButtonTitle)
{
    NSString *title_ = [NSString stringWithUTF8String:title ? title : ""];
    NSString *message_ = [NSString stringWithUTF8String:message ? message : ""];
    NSString *cancelButtonTitle_ = cancelButtonTitle ? [NSString stringWithUTF8String:cancelButtonTitle] : nil;
    [[NativeIOS sharedInstance] createAlertView:title_
                                         andMessage:message_
                               andCancelButtonTitle:cancelButtonTitle_];
}

int Native::addAlertButton(const char* buttonTitle)
{
    NSString *buttonTitle_ = [NSString stringWithUTF8String:buttonTitle ? buttonTitle : "Button"];
    return [[NativeIOS sharedInstance] addAlertButton:buttonTitle_];
}

void Native::showAlert(AlertViewDelegate* delegate)
{
    [[NativeIOS sharedInstance] showAlertViewWithDelegate:delegate];
}

void Native::cancelAlert(void)
{
    [[NativeIOS sharedInstance] cancelAlertView];
}

void Native::openURL(const char* url)
{
    if (!url) return;
    NSURL *nsurl = [NSURL URLWithString:[NSString stringWithCString:url encoding:NSUTF8StringEncoding]];
    [[UIApplication sharedApplication] openURL:nsurl];
}

const string Native::getInputText(const char* title, const char* message, const char* defaultValue)
{
    CCLOG("Native::getInputText() - not support this platform.");
    return string("");
}

#pragma mark -
#pragma mark OpenUDID

const string Native::getOpenUDID(void)
{
    return string([[OpenUDIDIOS value] cStringUsingEncoding:NSUTF8StringEncoding]);
}

const string Native::getDeviceName(void)
{
    UIDevice *device = [UIDevice currentDevice];
    return [[device name] cStringUsingEncoding:NSUTF8StringEncoding];
}

void Native::vibrate()
{
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void Native::showAlertObjc(void *delegate)
{
    [[NativeIOS sharedInstance] showAlertViewWithObjcDelegate:(id<UIAlertViewDelegate>)delegate];
}
#endif

#if CC_LUA_ENGINE_ENABLED > 0
int Native::addAlertButtonLua(const char* buttonTitle)
{
    return addAlertButton(buttonTitle) + 1;
}

void Native::showAlertLua(cocos2d::LUA_FUNCTION listener)
{
    [[NativeIOS sharedInstance] showAlertViewWithLuaListener:listener];
}
#endif

NS_CC_EXTRA_END
