
#import <Cocoa/Cocoa.h>

@interface CreateNewProjectDialogController : NSWindowController
{
    NSTextField *textFieldProjetLocation;
    NSTextField *textFieldPackageName;
    NSTextView *textView;
}

@property (nonatomic, assign) IBOutlet NSTextField *textFieldProjetLocation;
@property (nonatomic, assign) IBOutlet NSTextField *textFieldPackageName;
@property (assign) IBOutlet NSTextView *textView;

- (IBAction) onSelectProjectLocation:(id)sender;
- (IBAction) onCancel:(id)sender;
- (IBAction) onCreate:(id)sender;
- (IBAction) onPackageNameChanged:(id)sender;

@end
