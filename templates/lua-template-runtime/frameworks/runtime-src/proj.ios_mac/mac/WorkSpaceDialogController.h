
#import <Cocoa/Cocoa.h>

@interface WorkSpaceDialogController : NSWindowController
{

    NSTextField *textFieldProjectDirectory;
    NSTextField *textFieldScriptFile;
    NSButton *buttonOpenProject;
}

@property (nonatomic, assign) IBOutlet NSTextField *textFieldProjectDirectory;
@property (nonatomic, assign) IBOutlet NSTextField *textFieldScriptFile;

@property (nonatomic, assign) IBOutlet NSButton *buttonOpenProject;

- (IBAction) browseProjectDirectory:(id)sender;

- (IBAction) onCancel:(id)sender;
- (IBAction) onOpenProject:(id)sender;

@end
