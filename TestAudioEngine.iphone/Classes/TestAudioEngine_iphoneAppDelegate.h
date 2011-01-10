//
//  TestAudioEngine_iphoneAppDelegate.h
//  TestAudioEngine.iphone
//
//  Created by Walzer on 11-1-8.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class TestAudioEngine_iphoneViewController;

@interface TestAudioEngine_iphoneAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    TestAudioEngine_iphoneViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet TestAudioEngine_iphoneViewController *viewController;

@end

