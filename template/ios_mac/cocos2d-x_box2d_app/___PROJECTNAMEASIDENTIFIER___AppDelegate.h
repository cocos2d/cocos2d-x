//
//  ___PROJECTNAMEASIDENTIFIER___AppDelegate.h
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//  Copyright ___ORGANIZATIONNAME___ ___YEAR___. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "cocos2d.h"

@class RootViewController;

@interface ___PROJECTNAMEASIDENTIFIER___AppDelegate : NSObject <UIApplicationDelegate> {
        UIWindow                              *window;
        RootViewController             *viewController;
        cocos2d::CCXEGLView     *view;
}

@property (nonatomic, retain) UIWindow *window;

@end
