#import "platform/ios/CCInputView-ios.h"
#import "base/CCIMEDispatcher.h"
#import "base/CCDirector.h"

@interface CCInputView ()

@property(nonatomic) NSString* myMarkedText;

@end

@implementation CCInputView

@synthesize myMarkedText;
@synthesize hasText;
@synthesize beginningOfDocument;
@synthesize endOfDocument;
@synthesize markedTextStyle;
@synthesize tokenizer;
@synthesize autocorrectionType;

- (instancetype) initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame] ) {
        self.myMarkedText = nil;
        self.autocorrectionType = UITextAutocorrectionTypeNo;
    }
    
    return self;
}

- (void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self]; // remove keyboard notification
    [self.myMarkedText release];
    [self removeFromSuperview];
    [super dealloc];
}

- (BOOL) canBecomeFirstResponder {
    return YES;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self resignFirstResponder];
    [self removeFromSuperview];
}

#pragma TextInput protocol

- (id<UITextInputDelegate>)inputDelegate {
    return nil;
}

- (void)setInputDelegate:(id<UITextInputDelegate>)inputDelegate {
    
}

- (void)setSelectedTextRange:(UITextRange *)aSelectedTextRange {
    CCLOG("UITextRange:setSelectedTextRange");
}

- (UITextRange *)selectedTextRange {
    return [[[UITextRange alloc] init] autorelease];
}

- (void)deleteBackward {
    if (nil != self.myMarkedText) {
        [self.myMarkedText release];
        self.myMarkedText = nil;
    }
    cocos2d::IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
}

- (void)insertText:(nonnull NSString *)text {
    if (nil != self.myMarkedText) {
        [self.myMarkedText release];
        self.myMarkedText = nil;
    }
    const char * pszText = [text cStringUsingEncoding:NSUTF8StringEncoding];
    cocos2d::IMEDispatcher::sharedDispatcher()->dispatchInsertText(pszText, strlen(pszText));
}

- (NSWritingDirection)baseWritingDirectionForPosition:(nonnull UITextPosition *)position inDirection:(UITextStorageDirection)direction {
    CCLOG("baseWritingDirectionForPosition");
    return NSWritingDirectionLeftToRight;
}

- (CGRect)caretRectForPosition:(nonnull UITextPosition *)position {
    CCLOG("caretRectForPosition");
    return CGRectZero;
}

- (nullable UITextRange *)characterRangeAtPoint:(CGPoint)point {
    CCLOG("characterRangeAtPoint");
    return nil;
}

- (nullable UITextRange *)characterRangeByExtendingPosition:(nonnull UITextPosition *)position inDirection:(UITextLayoutDirection)direction {
    CCLOG("characterRangeByExtendingPosition");
    return nil;
}

- (nullable UITextPosition *)closestPositionToPoint:(CGPoint)point {
    CCLOG("closestPositionToPoint");
    return nil;
}

- (nullable UITextPosition *)closestPositionToPoint:(CGPoint)point withinRange:(nonnull UITextRange *)range {
    CCLOG("closestPositionToPoint");
    return nil;
}

- (NSComparisonResult)comparePosition:(nonnull UITextPosition *)position toPosition:(nonnull UITextPosition *)other {
    CCLOG("comparePosition");
    return (NSComparisonResult)0;
}

- (CGRect)firstRectForRange:(nonnull UITextRange *)range {
    CCLOG("firstRectForRange");
    return CGRectNull;
}

- (NSInteger)offsetFromPosition:(nonnull UITextPosition *)from toPosition:(nonnull UITextPosition *)toPosition {
    CCLOG("offsetFromPosition");
    return 0;
}

- (nullable UITextPosition *)positionFromPosition:(nonnull UITextPosition *)position inDirection:(UITextLayoutDirection)direction offset:(NSInteger)offset {
    CCLOG("positionFromPosition");
    return nil;
}

- (nullable UITextPosition *)positionFromPosition:(nonnull UITextPosition *)position offset:(NSInteger)offset {
    CCLOG("positionFromPosition");
    return nil;
}

- (nullable UITextPosition *)positionWithinRange:(nonnull UITextRange *)range farthestInDirection:(UITextLayoutDirection)direction {
    CCLOG("positionWithinRange");
    return nil;
}

- (void)replaceRange:(nonnull UITextRange *)range withText:(nonnull NSString *)text {
    
}

- (nonnull NSArray<UITextSelectionRect *> *)selectionRectsForRange:(nonnull UITextRange *)range {
    CCLOG("selectionRectsForRange");
    return nil;
}

- (void)setBaseWritingDirection:(NSWritingDirection)writingDirection forRange:(nonnull UITextRange *)range {
    
}

- (void)setMarkedText:(nullable NSString *)markedText selectedRange:(NSRange)selectedRange {
    CCLOG("setMarkedText");
    if (markedText == self.myMarkedText) {
        return;
    }
    if (nil != self.myMarkedText) {
        [self.myMarkedText release];
    }
    self.myMarkedText = markedText;
    [self.myMarkedText retain];
}

- (UITextRange *)markedTextRange
{
    CCLOG("markedTextRange");
    if (nil != self.myMarkedText) {
        return [[[UITextRange alloc] init] autorelease];
    }
    return nil; // Nil if no marked text.
}

- (nullable NSString *)textInRange:(nonnull UITextRange *)range {
    CCLOG("textInRange");
    if (nil != self.myMarkedText) {
        return self.myMarkedText;
    }
    return @"";
}

- (nullable UITextRange *)textRangeFromPosition:(nonnull UITextPosition *)fromPosition toPosition:(nonnull UITextPosition *)toPosition {
    CCLOG("textRangeFromPosition");
    return nil;
}

- (void)unmarkText {
    CCLOG("unmarkText");
    if (nil == self.myMarkedText)
    {
        return;
    }
    const char * pszText = [self.myMarkedText cStringUsingEncoding:NSUTF8StringEncoding];
    cocos2d::IMEDispatcher::sharedDispatcher()->dispatchInsertText(pszText, strlen(pszText));
    [self.myMarkedText release];
    self.myMarkedText = nil;
}

- (void)encodeWithCoder:(nonnull NSCoder *)coder {
}

@end
