
#import "WorkSpaceDialogController.h"

#pragma mark -

@implementation WorkSpaceDialogController

@synthesize textFieldProjectDirectory;
@synthesize textFieldScriptFile;
@synthesize buttonOpenProject;

NSString* projectPath=nil;
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
    NSLog(@"[WorkSpaceDialogController dealloc]");
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
    [self.window makeFirstResponder:textFieldProjectDirectory];
    if (nil != projectPath &&  0 != projectPath.length)
    {
        [textFieldProjectDirectory setStringValue:projectPath];
    }
}

#pragma mark -
#pragma mark functions

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
        [textFieldProjectDirectory setStringValue:path];
    }
}


- (IBAction) onCancel:(id)sender
{
    [self close];
    [NSApp endSheet:self.window returnCode:NSRunAbortedResponse];
}

- (IBAction) onOpenProject:(id)sender
{
    if([[textFieldProjectDirectory stringValue] isEqualToString:@""])
    {
        NSRunAlertPanel(@"Waring",
                        @"Project path empty!",
                        @"OK", NULL, NULL);
        return;
    }
    projectPath =  [textFieldProjectDirectory stringValue];
    [self close];
    [NSApp endSheet:self.window returnCode:NSRunAbortedResponse];
}


@end
