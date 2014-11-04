
#import "platform/ios/CCNativeIOS.h"

#ifndef utf8cstr
#define utf8cstr(nsstr) (nsstr ? [nsstr cStringUsingEncoding:NSUTF8StringEncoding] : "")
#endif

@implementation NativeIOS

static NativeIOS *s_sharedInstance;

+ (NativeIOS *)sharedInstance
{
    if (!s_sharedInstance)
    {
        s_sharedInstance = [[NativeIOS alloc] init];
    }
    return s_sharedInstance;
}

- (void)dealloc
{
    [self hideActivityIndicator];
    [self removeAlertView];
#if CC_LUA_ENGINE_ENABLED > 0
    [self removeAlertViewLuaListener];
#endif
    [super dealloc];
    s_sharedInstance = nil;
}


#pragma mark -
#pragma mark activity indicator

- (void)showActivityIndicator:(UIActivityIndicatorViewStyle)style
{
    if (activityIndicatorView_)
    {
        CCLOG("[NativeIOS] ERR, showActivityIndicator() activity indicator already visible");
        return;
    }
    
    CCLOG("[NativeIOS] showActivityIndicator()");
    activityIndicatorView_ = [UIActivityIndicatorView  alloc];
    [activityIndicatorView_ initWithActivityIndicatorStyle:style];
    [activityIndicatorView_ autorelease];
    [activityIndicatorView_ retain];
    
    NSInteger count = [UIApplication sharedApplication].windows.count;
    UIWindow* topWindow = [[UIApplication sharedApplication].windows objectAtIndex:count - 1];
    [topWindow addSubview: activityIndicatorView_];
    activityIndicatorView_.center = topWindow.center;
    [activityIndicatorView_ startAnimating];
}

- (void)hideActivityIndicator
{
    if (!activityIndicatorView_)
    {
        CCLOG("[NativeIOS] ERR, hideActivityIndicator() activity indicator not visible");
        return;
    }
    
    CCLOG("[NativeIOS] hideActivityIndicator()");
    [activityIndicatorView_ removeFromSuperview];
    [activityIndicatorView_ release];
    activityIndicatorView_ = nil;
}


#pragma mark -
#pragma mark alert view

- (void)createAlertView:(NSString *)title
             andMessage:(NSString *)message
   andCancelButtonTitle:(NSString *)cancelButtonTitle
{
    if (alertView_)
    {
        CCLOG("[NativeIOS] ERR, createAlertView() alert view already exists");
        return;
    }
    
    CCLOG("[NativeIOS] createAlertView() title: %s, message: %s, cancelButtonTitle: %s",
          utf8cstr(title), utf8cstr(message), utf8cstr(cancelButtonTitle));
    alertView_ = [[UIAlertView alloc] initWithTitle:title
                                            message:message
                                           delegate:self
                                  cancelButtonTitle:cancelButtonTitle
                                  otherButtonTitles:nil];
}

- (NSInteger)addAlertButton:(NSString *)buttonTitle
{
    if (!alertView_)
    {
        CCLOG("[NativeIOS] ERR, addAlertButton() alert view not exists");
        return 0;
    }

    CCLOG("[NativeIOS] addAlertButton() buttonTitle: %s", utf8cstr(buttonTitle));
    return [alertView_ addButtonWithTitle:buttonTitle];
}

- (void)showAlertViewWithDelegate:(AlertViewDelegate *)delegate
{
    if (!alertView_)
    {
        CCLOG("[NativeIOS] ERR, showAlertViewWithDelegate() alert view not exists");
        return;
    }

    CCLOG("[NativeIOS] showAlertViewWithDelegate()");
    alertViewDelegates_ = delegate;
#if CC_LUA_ENGINE_ENABLED > 0
    [self removeAlertViewLuaListener];
#endif
    [alertView_ show];
}

- (void)removeAlertView
{
    if (!alertView_)
    {
        CCLOG("[NativeIOS] ERR, removeAlertView() alert view not exists");
        return;
    }
    
    CCLOG("[NativeIOS] removeAlertView()");
    [alertView_ release];
    alertView_ = nil;
#if CC_LUA_ENGINE_ENABLED > 0
    [self removeAlertViewLuaListener];
#endif
    alertViewDelegates_ = nil;
}

- (void)cancelAlertView
{
    if (!alertView_)
    {
        CCLOG("[NativeIOS] ERR, cancelAlertView() alert view not exists");
        return;
    }
    
    CCLOG("[NativeIOS] cancelAlertView()");
    [alertView_ dismissWithClickedButtonIndex:0 animated:YES];
    [self removeAlertView];
}

#if CC_LUA_ENGINE_ENABLED > 0
- (void)showAlertViewWithLuaListener:(LUA_FUNCTION)listener
{
    if (!alertView_)
    {
        CCLOG("[NativeIOS] ERR, showAlertViewWithLuaListener() alert view not exists");
        return;
    }
    
    CCLOG("[NativeIOS] showAlertViewWithLuaListener()");
    alertViewLuaListener_ = listener;
    alertViewDelegates_ = nil;
    [alertView_ show];
}

- (void)removeAlertViewLuaListener
{
    if (alertViewLuaListener_)
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(alertViewLuaListener_);
    }
}
#endif


#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
- (void)showAlertViewWithObjcDelegate:(id<UIAlertViewDelegate>)delegate
{
    if (!alertView_)
    {
        CCLOG("[NativeIOS] ERR, showAlertViewWithDelegate() alert view not exists");
        return;
    }
    
    CCLOG("[NativeIOS] showAlertViewWithObjcDelegate()");
    [alertView_ setDelegate:delegate];
    [alertView_ show];
}
#endif

#pragma mark -
#pragma mark UIAlertView delegates

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (alertViewDelegates_)
    {
        alertViewDelegates_->alertViewClickedButtonAtIndex(buttonIndex);
    }
#if CC_LUA_ENGINE_ENABLED > 0
    if (alertViewLuaListener_)
    {
        LuaStack *stack = LuaEngine::getInstance()->getLuaStack();
        
        LuaValueDict event;
        event["action"] = LuaValue::stringValue("clicked");
        event["buttonIndex"] = LuaValue::intValue(buttonIndex + 1);
        stack->pushLuaValueDict(event);
        stack->executeFunctionByHandler(alertViewLuaListener_, 1);
    }
#endif
    [self removeAlertView];
}

@end
