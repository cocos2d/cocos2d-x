#ifndef __CC_NATIVE_MAC_H_
#define __CC_NATIVE_MAC_H_

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

#include "native/CCAlertViewDelegate.h"

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#endif



USING_NS_CC;
USING_NS_CC_EXTRA;

@interface NativeMac : NSObject
{
    NSAlert *alertView_;
}

+ (NativeMac *)sharedInstance;


#pragma mark -
#pragma mark activity indicator

- (void)showActivityIndicator;
- (void)hideActivityIndicator;


#pragma mark -
#pragma mark alert view

- (void)createAlertView:(NSString *)title
             andMessage:(NSString *)message
   andCancelButtonTitle:(NSString *)cancelButtonTitle;
- (NSInteger)addAlertButton:(NSString *)buttonTitle;
- (void)showAlertViewWithDelegate:(AlertViewDelegate *)delegate;
- (void)removeAlertView;
- (void)cancelAlertView;

#if CC_LUA_ENGINE_ENABLED > 0
- (void)showAlertViewWithLuaListener:(LUA_FUNCTION)listener;
- (void)removeAlertViewLuaListener;
#endif


#pragma mark -
#pragma mark misc

- (NSString*)getInputText:(NSString*)title message:(NSString*)message defaultValue:(NSString*)defaultValue;

@end

#endif
