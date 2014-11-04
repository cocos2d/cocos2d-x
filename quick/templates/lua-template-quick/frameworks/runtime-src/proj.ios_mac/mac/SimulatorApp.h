/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#include <string>
#import "ConsoleWindowController.h"
#include "ProjectConfig/ProjectConfig.h"
#include "AppDelegate.h"

void createSimulator(const char* viewName, float width, float height,bool isLandscape = true,float frameZoomFactor = 1.0f);

@interface AppController : NSObject <NSApplicationDelegate, NSWindowDelegate>
{
    NSWindow *_window;
    NSMenu *_menu;
    ProjectConfig _project;
    
    //log file
    ConsoleWindowController *_consoleController;
    NSFileHandle *_fileHandle;
    
    //console pipe
    NSPipe *_pipe;
    NSFileHandle *_pipeReadHandle;
}

@property (nonatomic, assign) IBOutlet NSMenu* menu;


- (IBAction) onSetTop:(id)sender;
- (IBAction) onFileClose:(id)sender;
- (IBAction) onScreenPortait:(id)sender;
- (IBAction) onScreenLandscape:(id)sender;
- (IBAction) onScreenZoomOut:(id)sender;
- (IBAction) onRelaunch:(id)sender;


@end
