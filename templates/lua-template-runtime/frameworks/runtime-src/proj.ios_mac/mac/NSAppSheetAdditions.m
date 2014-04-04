
#import "NSAppSheetAdditions.h"

@implementation NSApplication (SheetAdditions)

- (void)beginSheet:(NSWindow *)sheet modalForWindow:(NSWindow *)docWindow didEndBlock:(void (^)(NSInteger returnCode))block
{
    [self beginSheet:sheet
      modalForWindow:docWindow
       modalDelegate:self
      didEndSelector:@selector(my_blockSheetDidEnd:returnCode:contextInfo:)
         contextInfo:Block_copy(block)];
}

- (void)my_blockSheetDidEnd:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo
{
    void (^block)(NSInteger returnCode) = contextInfo;
    block(returnCode);
    Block_release(block);
}

@end
