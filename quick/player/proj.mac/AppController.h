//
//  AppDelegate.h
//  quick-x-player
//

#import <Cocoa/Cocoa.h>

#import "ConsoleWindowController.h"

#include "SimulatorConfig.h"
#include "AppDelegate.h"

class AppControllerBridge;

@interface AppController : NSObject <NSApplicationDelegate, NSWindowDelegate>
{
    NSWindow *window;
    
    BOOL waitForRestart;
    BOOL isAlwaysOnTop;
    BOOL isMaximized;
    
    AppDelegate *app;
    GLView      *eglView;
    ProjectConfig projectConfig;
    BOOL hasPopupDialog;
    
    int debugLogFile;
    
    AppControllerBridge *bridge;
    
    //log file
    ConsoleWindowController *consoleController;
    NSFileHandle *fileHandle;
    //console pipe
    NSPipe *pipe;
    NSFileHandle *pipeReadHandle;
}
//@property (assign) IBOutlet NSWindow *window;

- (IBAction) onServicePreferences:(id)sender;

- (IBAction) onFileNewProject:(id)sender;
- (IBAction) onFileNewPlayer:(id)sender;
- (IBAction) onFileOpen:(id)sender;
- (IBAction) onFileOpenRecentClearMenu:(id)sender;
- (IBAction) onFileWelcome:(id)sender;
- (IBAction) onFileClose:(id)sender;

- (IBAction) onPlayerWriteDebugLogToFile:(id)sender;
- (IBAction) onPlayerOpenDebugLog:(id)sender;
- (IBAction) onPlayerRelaunch:(id)sender;
- (IBAction) onPlayerShowProjectSandbox:(id)sender;
- (IBAction) onPlayerShowProjectFiles:(id)sender;

- (IBAction) onScreenPortait:(id)sender;
- (IBAction) onScreenLandscape:(id)sender;
- (IBAction) onScreenZoomOut:(id)sender;

- (IBAction) onWindowAlwaysOnTop:(id)sender;

@end
