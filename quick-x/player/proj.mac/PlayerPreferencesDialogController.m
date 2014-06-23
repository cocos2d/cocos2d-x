
#import "PlayerPreferencesDialogController.h"

@implementation PlayerPreferencesDialogController

@synthesize textFieldQuickCocos2dxRootPath;
@synthesize buttonSave;

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
    NSString *path = [[NSUserDefaults standardUserDefaults] objectForKey:@"QUICK_COCOS2DX_ROOT"];
    if (path && [path length] > 0)
    {
        [textFieldQuickCocos2dxRootPath setStringValue:path];
        [buttonSave setEnabled:YES];
    }
}

#pragma mark -
#pragma mark IBAction

- (IBAction) onSelectQuickCocos2dxRootPath:(id)sender
{
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setTitle:@"Select quick-cocos2d-x root path"];
    [openDlg setCanChooseDirectories:YES];
    [openDlg setCanChooseFiles:NO];
    [openDlg setCanHide:YES];
    [openDlg setCanCreateDirectories:NO];
    [openDlg setCanSelectHiddenExtension:NO];
    [openDlg setAllowsMultipleSelection:NO];

    if ([openDlg runModal] == NSFileHandlingPanelOKButton)
    {
        NSString *path = [[openDlg.URLs objectAtIndex:0] path];
        [textFieldQuickCocos2dxRootPath setStringValue:path];
        [buttonSave setEnabled:YES];
    }
}

- (IBAction) onCancel:(id)sender
{
    [self close];
    [NSApp endSheet:self.window returnCode:NSRunAbortedResponse];
}

- (IBAction) onSave:(id)sender
{
    [[NSUserDefaults standardUserDefaults] setObject:[textFieldQuickCocos2dxRootPath stringValue] forKey:@"QUICK_COCOS2DX_ROOT"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    [self close];
    [NSApp endSheet:self.window returnCode:NSRunStoppedResponse];
}

@end
