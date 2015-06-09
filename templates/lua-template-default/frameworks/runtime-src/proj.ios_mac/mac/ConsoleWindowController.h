
#import <Cocoa/Cocoa.h>

@interface ConsoleWindowController : NSWindowController
{
    NSTextView *textView;
    IBOutlet NSButton *checkScroll;
    IBOutlet NSButton *topCheckBox;
    NSMutableArray *linesCount;
    NSUInteger traceCount;
}

@property (assign) IBOutlet NSTextView *textView;

- (void) trace:(NSString*)msg;
- (IBAction)onClear:(id)sender;
- (IBAction)onScrollChange:(id)sender;
- (IBAction)onTopChange:(id)sender;

@end



