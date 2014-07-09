
#import <Cocoa/Cocoa.h>

@interface CreateNewProjectDialogController : NSWindowController <NSTextFieldDelegate>
{
    NSTextField *textFieldProjetLocation;
    NSTextField *textFieldPackageName;
    NSTextView *textView;
    NSButton *cancelButton;
    NSButton *createButton;
    bool isCreatingProject;
}

@property (nonatomic, assign) IBOutlet NSTextField *textFieldProjetLocation;
@property (nonatomic, assign) IBOutlet NSTextField *textFieldPackageName;
@property (assign) IBOutlet NSTextView *textView;
@property (assign) IBOutlet NSButton *cancelButton;
@property (assign) IBOutlet NSButton *createButton;

- (IBAction) onSelectProjectLocation:(id)sender;
- (IBAction) onCancel:(id)sender;
- (IBAction) onCreate:(id)sender;
- (IBAction) onPackageNameChanged:(id)sender;

@end
