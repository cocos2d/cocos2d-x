//
//  AppDelegate.h
//  quick-x-player
//

#import <Cocoa/Cocoa.h>
#include "SimulatorConfig.h"
#include "AppDelegate.h"

@interface AppController : NSObject <NSApplicationDelegate, NSWindowDelegate>
{
    AppDelegate *app;
    ProjectConfig projectConfig;
}
@property (assign) IBOutlet NSWindow *window;

@end
