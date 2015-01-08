//
//  UncaughtExceptionHandler.h
//  player3
//
//  Created by ZhuJunfeng on 15-1-8.
//
//

#ifndef player3_UncaughtExceptionHandler_h
#define player3_UncaughtExceptionHandler_h

//#import <UIKit/UIKit.h>

@interface UncaughtExceptionHandler : NSObject{
    BOOL dismissed;
}
@end

void InstallUncaughtExceptionHandler();

#endif
