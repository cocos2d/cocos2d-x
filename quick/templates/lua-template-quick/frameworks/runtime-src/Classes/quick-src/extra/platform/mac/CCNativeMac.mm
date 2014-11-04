
#import "platform/mac/CCNativeMac.h"

#ifndef utf8cstr
#define utf8cstr(nsstr) (nsstr ? [nsstr cStringUsingEncoding:NSUTF8StringEncoding] : "")
#endif

@implementation NativeMac

static NativeMac *s_sharedInstance;

+ (NativeMac *)sharedInstance
{
    if (!s_sharedInstance)
    {
        s_sharedInstance = [[NativeMac alloc] init];
    }
    return s_sharedInstance;
}


#pragma mark -
#pragma mark activity indicator

- (void)showActivityIndicator
{
    log("Native::showActivityIndicator() not support on this platform.");
}

- (void)hideActivityIndicator
{
    log("Native::hideActivityIndicator() not support on this platform.");
}


#pragma mark -
#pragma mark alert view

- (void)createAlertView:(NSString *)title
             andMessage:(NSString *)message
   andCancelButtonTitle:(NSString *)cancelButtonTitle
{
    if (alertView_)
    {
        CCLOG("Native::createAlertView() - alert view already exists");
        return;
    }
    
    CCLOG("Native::createAlertView() - title: %s, message: %s, cancelButtonTitle: %s",
          utf8cstr(title), utf8cstr(message), utf8cstr(cancelButtonTitle));
    alertView_ = [NSAlert alertWithMessageText:title
                                 defaultButton:cancelButtonTitle
                               alternateButton:nil
                                   otherButton:nil
                     informativeTextWithFormat:@"%@", message];
    [alertView_ retain];
}

- (NSInteger)addAlertButton:(NSString *)buttonTitle
{
    if (!alertView_)
    {
        CCLOG("Native::addAlertButton() - alert view not exists");
        return 0;
    }

    CCLOG("Native::addAlertButton() - buttonTitle: %s", utf8cstr(buttonTitle));
    [alertView_ addButtonWithTitle:buttonTitle];
    return [alertView_.buttons count] - 1;
}

- (void)showAlertViewWithDelegate:(AlertViewDelegate *)delegate
{
    if (!alertView_)
    {
        CCLOG("Native::showAlertViewWithDelegate() - alert view not exists");
        return;
    }

    CCLOG("Native::showAlertViewWithDelegate()");
    int buttonIndex = (int)[alertView_ runModal];
    buttonIndex = [self processButtonId:buttonIndex];
    if (delegate)
    {
        delegate->alertViewClickedButtonAtIndex(buttonIndex);
    }
    [self removeAlertView];
}

- (void)removeAlertView
{
    if (!alertView_)
    {
        CCLOG("Native::removeAlertView() - alert view not exists");
        return;
    }
    
    CCLOG("Native::removeAlertView()");
    [alertView_ release];
    alertView_ = nil;
#if CC_LUA_ENGINE_ENABLED > 0
    [self removeAlertViewLuaListener];
#endif
}

- (void)cancelAlertView
{
    if (!alertView_)
    {
        CCLOG("Native::cancelAlertView() - alert view not exists");
        return;
    }
    
    CCLOG("Native::cancelAlertView()");
    [self removeAlertView];
}

#if CC_LUA_ENGINE_ENABLED > 0
- (void)showAlertViewWithLuaListener:(LUA_FUNCTION)listener
{
    if (!alertView_)
    {
        CCLOG("Native::showAlertViewWithLuaListener() - alert view not exists");
        return;
    }
    
    CCLOG("Native::showAlertViewWithLuaListener()");
    int buttonIndex = (int)[alertView_ runModal];
    buttonIndex = [self processButtonId:buttonIndex];
    
    LuaValueDict event;
    event["action"] = LuaValue::stringValue("clicked");
    event["buttonIndex"] = LuaValue::intValue(buttonIndex);
    
    LuaStack *stack = LuaEngine::getInstance()->getLuaStack();
    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(listener, 1);
    
    [self removeAlertView];
}

- (void)removeAlertViewLuaListener
{
}
#endif


#pragma mark -
#pragma mark misc

- (NSString*)getInputText:(NSString*)title message:(NSString*)message defaultValue:(NSString*)defaultValue
{
    NSAlert *alert = [NSAlert alertWithMessageText:title
                                     defaultButton:@"OK"
                                   alternateButton:@"Cancel"
                                       otherButton:nil
                         informativeTextWithFormat:@"%@", message];
    
    NSRect frame = NSMakeRect(0, 0, 320, 22);
    NSTextField *textField = [[NSTextField alloc] initWithFrame:frame];
    [textField setStringValue:defaultValue];
    [alert setAccessoryView:textField];
    NSInteger buttonIndex = [alert runModal];
    if (buttonIndex == 0)
    {
        return @"";
    }
    else
    {
        return [textField stringValue];
    }
}

- (int) processButtonId:(int) buttonIndex
{
    if (buttonIndex != NSAlertDefaultReturn)
    {
        buttonIndex = buttonIndex - NSAlertFirstButtonReturn + 1;
    }
    return buttonIndex;
}

@end
