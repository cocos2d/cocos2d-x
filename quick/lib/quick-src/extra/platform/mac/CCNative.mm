
#include <sys/sysctl.h>
#import "platform/mac/CCNativeMac.h"

#include "native/CCNative.h"
#import "platform/mac/openudid/OpenUDIDMac.h"

NS_CC_EXTRA_BEGIN

#pragma mark -
#pragma mark activity indicator

void Native::showActivityIndicator(void)
{
    [[NativeMac sharedInstance] showActivityIndicator];
}

void Native::hideActivityIndicator(void)
{
    [[NativeMac sharedInstance] hideActivityIndicator];
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
    [[NativeMac sharedInstance] createAlertView:title_
                                         andMessage:message_
                               andCancelButtonTitle:cancelButtonTitle_];
}

int Native::addAlertButton(const char* buttonTitle)
{
    NSString *buttonTitle_ = [NSString stringWithUTF8String:buttonTitle ? buttonTitle : "Button"];
    return (int)[[NativeMac sharedInstance] addAlertButton:buttonTitle_];
}

#if CC_LUA_ENGINE_ENABLED > 0
int Native::addAlertButtonLua(const char* buttonTitle)
{
    return addAlertButton(buttonTitle) + 1;
}
#endif

void Native::showAlert(AlertViewDelegate* delegate)
{
    [[NativeMac sharedInstance] showAlertViewWithDelegate:delegate];
}

#if CC_LUA_ENGINE_ENABLED > 0
void Native::showAlertLua(LUA_FUNCTION listener)
{
    [[NativeMac sharedInstance] showAlertViewWithLuaListener:listener];
}
#endif

void Native::cancelAlert(void)
{
    [[NativeMac sharedInstance] cancelAlertView];
}


#pragma mark -
#pragma mark misc

void Native::openURL(const char* url)
{
    if (!url) return;
    NSURL *nsurl = [NSURL URLWithString:[NSString stringWithCString:url encoding:NSUTF8StringEncoding]];
    [[NSWorkspace sharedWorkspace] openURL:nsurl];
}

const string Native::getInputText(const char* title, const char* message, const char* defaultValue)
{
    NSString *title_ = [NSString stringWithUTF8String:title ? title : ""];
    NSString *message_ = [NSString stringWithUTF8String:message ? message : ""];
    NSString *defaultValue_ = [NSString stringWithUTF8String:defaultValue ? defaultValue : ""];
    NSString *input = [[NativeMac sharedInstance] getInputText:title_
                                                           message:message_
                                                      defaultValue:defaultValue_];
    return string([input cStringUsingEncoding:NSUTF8StringEncoding]);
}


#pragma mark -
#pragma mark OpenUDID

const string Native::getOpenUDID(void)
{
    return string([[OpenUDIDMac value] cStringUsingEncoding:NSUTF8StringEncoding]);
}

const string Native::getDeviceName(void)
{
    size_t len = 0;
    sysctlbyname("hw.model", NULL, &len, NULL, 0);
    if (len)
    {
        char* model = static_cast<char*>(malloc(len * sizeof(char)));
        sysctlbyname("hw.model", model, &len, NULL, 0);
        string modelStr(model);
        free(model);
        return modelStr;
    }

    log("Native::getDeviceName() not support on this platform.");
    return string("");
}

void Native::vibrate()
{
    log("Native::vibrate() not support on this platform.");
}

NS_CC_EXTRA_END
