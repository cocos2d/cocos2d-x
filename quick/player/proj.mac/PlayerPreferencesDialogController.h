
#import <Cocoa/Cocoa.h>

@interface PlayerPreferencesDialogController : NSWindowController
{
    NSTextField *textFieldQuickCocos2dxRootPath;
    NSButton *buttonSave;
}

@property (nonatomic, assign) IBOutlet NSTextField *textFieldQuickCocos2dxRootPath;
@property (nonatomic, assign) IBOutlet NSButton *buttonSave;

- (IBAction) onSelectQuickCocos2dxRootPath:(id)sender;
- (IBAction) onCancel:(id)sender;
- (IBAction) onSave:(id)sender;

@end
