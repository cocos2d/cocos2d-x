
#import "ProjectConfigDialogController.h"

#include "ProjectConfig/SimulatorConfig.h"

@interface OnlyIntegerValueFormatter : NSNumberFormatter
@end

@implementation OnlyIntegerValueFormatter

- (BOOL)isPartialStringValid:(NSString*)partialString newEditingString:(NSString**)newString errorDescription:(NSString**)error
{
    if([partialString length] == 0)
    {
        return YES;
    }

    NSScanner* scanner = [NSScanner scannerWithString:partialString];
    if(!([scanner scanInt:0] && [scanner isAtEnd]))
    {
        NSBeep();
        return NO;
    }

    return YES;
}

@end

#pragma mark -

@implementation ProjectConfigDialogController

@synthesize projectConfig;

@synthesize textFieldProjectDirectory;
@synthesize textFieldScriptFile;
@synthesize textFieldWritablePath;
@synthesize popupScreenSize;
@synthesize textFieldScreenSizeWidth;
@synthesize textFieldScreenSizeHeight;
@synthesize matrixScreenOrientation;
@synthesize buttonScreenOrientationPortait;
@synthesize buttonScreenOrientationLandscape;
@synthesize buttonShowDebugConsole;
@synthesize buttonWriteDebugLogToFile;
@synthesize buttonLoadPrecompiledFramework;
@synthesize buttonOpenProject;

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)dealloc
{
    [super dealloc];
    NSLog(@"[ProjectConfigDialogController dealloc]");
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
    [self.window makeFirstResponder:textFieldProjectDirectory];
    [self initUI];
    [self updateUI];
}

#pragma mark -
#pragma mark functions

- (void) initUI
{
    [textFieldScreenSizeWidth setFormatter:[[[OnlyIntegerValueFormatter alloc] init] autorelease]];
    [textFieldScreenSizeHeight setFormatter:[[[OnlyIntegerValueFormatter alloc] init] autorelease]];

    [popupScreenSize removeAllItems];
    SimulatorConfig *config = SimulatorConfig::sharedDefaults();
    for (int i = 0; i < config->getScreenSizeCount(); ++i)
    {
        [popupScreenSize addItemWithTitle:[NSString stringWithCString:config->getScreenSize(i).title.c_str() encoding:NSUTF8StringEncoding]];
    }
    [popupScreenSize addItemWithTitle:@"Custom..."];
}

- (void) updateUI
{
    [textFieldProjectDirectory setStringValue:[NSString stringWithCString:projectConfig.getProjectDir().c_str() encoding:NSUTF8StringEncoding]];
    [textFieldWritablePath setStringValue:[NSString stringWithCString:projectConfig.getWritablePath().c_str() encoding:NSUTF8StringEncoding]];
    [textFieldScriptFile setStringValue:[NSString stringWithCString:projectConfig.getScriptFile().c_str() encoding:NSUTF8StringEncoding]];

    const CCSize frameSzie = projectConfig.getFrameSize();
    SimulatorConfig *config = SimulatorConfig::sharedDefaults();
    int i = config->checkScreenSize(frameSzie);
    if (i >= 0)
    {
        [popupScreenSize selectItemAtIndex:i];
    }

    [textFieldScreenSizeWidth setStringValue:[NSString stringWithFormat:@"%0.0f", frameSzie.width]];
    [textFieldScreenSizeHeight setStringValue:[NSString stringWithFormat:@"%0.0f", frameSzie.height]];

    if (projectConfig.isLandscapeFrame())
    {
        [buttonScreenOrientationPortait setState:NSOffState];
        [buttonScreenOrientationLandscape setState:NSOnState];
    }
    else
    {
        [buttonScreenOrientationPortait setState:NSOnState];
        [buttonScreenOrientationLandscape setState:NSOffState];
    }

    [buttonShowDebugConsole setState:projectConfig.isShowConsole() ? NSOnState : NSOffState];
    [buttonWriteDebugLogToFile setState:projectConfig.isWriteDebugLogToFile() ? NSOnState : NSOffState];
    [buttonLoadPrecompiledFramework setState:projectConfig.isLoadPrecompiledFramework() ? NSOnState : NSOffState];
    [buttonOpenProject setEnabled:projectConfig.validate()];
}

- (NSString*) browseFolder:(NSString*)title
{
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setTitle:title];
    [openDlg setCanChooseDirectories:YES];
    [openDlg setCanChooseFiles:NO];
    [openDlg setCanHide:YES];
    [openDlg setCanCreateDirectories:NO];
    [openDlg setCanSelectHiddenExtension:NO];
    [openDlg setAllowsMultipleSelection:NO];

    if ([openDlg runModal] == NSFileHandlingPanelOKButton)
    {
        NSURL *url = [openDlg.URLs objectAtIndex:0];
        return [url path];
    }
    return nil;
}

#pragma mark -
#pragma mark outlet

- (IBAction) browseProjectDirectory:(id)sender
{
    NSString *path = [self browseFolder:@"Choose Project Directory"];
    if (path)
    {
        projectConfig.setProjectDir([path cStringUsingEncoding:NSUTF8StringEncoding]);
        [self updateUI];
    }
}

- (IBAction) browseScriptFile:(id)sender
{
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setCanChooseDirectories:NO];
    [openDlg setCanChooseFiles:YES];
    [openDlg setCanHide:YES];
    [openDlg setCanCreateDirectories:NO];
    [openDlg setCanSelectHiddenExtension:NO];
    [openDlg setAllowsMultipleSelection:NO];

    if ([openDlg runModal] == NSFileHandlingPanelOKButton)
    {
        NSURL *url = [openDlg.URLs objectAtIndex:0];
        projectConfig.setScriptFile([[url path] cStringUsingEncoding:NSUTF8StringEncoding]);
        [self updateUI];
    }
}

- (IBAction) browseWritablePath:(id)sender
{
    NSString *path = [self browseFolder:@"Choose Writable Path"];
    if (path)
    {
        projectConfig.setWritablePath([path cStringUsingEncoding:NSUTF8StringEncoding]);
        [self updateUI];
    }
}

- (IBAction) onScreenSizeChanged:(id)sender
{
    int i = (int)[popupScreenSize indexOfSelectedItem];
    SimulatorConfig *config = SimulatorConfig::sharedDefaults();
    if (i >= 0 && i < config->getScreenSizeCount())
    {
        [textFieldScreenSizeWidth setEnabled:NO];
        [textFieldScreenSizeHeight setEnabled:NO];

        float width = config->getScreenSize(i).width;
        float height = config->getScreenSize(i).height;
        projectConfig.setFrameSize(projectConfig.isLandscapeFrame() ? CCSize(height, width) : CCSize(width, height));
        [self updateUI];
    }
    else
    {
        [textFieldScreenSizeWidth setEnabled:YES];
        [textFieldScreenSizeHeight setEnabled:YES];
    }
}

- (IBAction) onScreenSizeTextFieldsChanged:(id)sender
{
    projectConfig.setFrameSize(CCSize([textFieldScreenSizeWidth intValue], [textFieldScreenSizeHeight intValue]));
}

- (IBAction) onScreenOrientationChanged:(id)sender
{
    projectConfig.setFrameSize(CCSize([textFieldScreenSizeWidth intValue], [textFieldScreenSizeHeight intValue]));
    NSButton *button = [matrixScreenOrientation selectedCell];
    if (([button tag] == 1 && projectConfig.isLandscapeFrame()) || ([button tag] == 2 && !projectConfig.isLandscapeFrame()))
    {
        projectConfig.changeFrameOrientation();
        [self updateUI];
    }
}

- (IBAction) onShowDebugConsoleChanged:(id)sender
{
    projectConfig.setShowConsole([buttonShowDebugConsole state] == NSOnState);
}

- (IBAction) onWriteDebugLogToFileChanged:(id)sender
{
    projectConfig.setWriteDebugLogToFile([buttonWriteDebugLogToFile state] == NSOnState);
}

- (IBAction) onLoadPrecompiledFrameworkChanged:(id)sender
{
    projectConfig.setLoadPrecompiledFramework([buttonLoadPrecompiledFramework state] == NSOnState);
}

- (IBAction) onCancel:(id)sender
{
    [self close];
    [NSApp endSheet:self.window returnCode:NSRunAbortedResponse];
}

- (IBAction) onOpenProject:(id)sender
{
    projectConfig.setFrameSize(CCSize([textFieldScreenSizeWidth intValue], [textFieldScreenSizeHeight intValue]));
    [self close];
    [NSApp endSheet:self.window returnCode:NSRunStoppedResponse];
}


@end
