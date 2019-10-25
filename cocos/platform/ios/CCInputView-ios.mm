#import "platform/ios/CCInputView-ios.h"
#import "base/CCIMEDispatcher.h"
#import "base/CCDirector.h"

@interface CCInputView ()

@property(nonatomic) NSString* myMarkedText;

@end

@implementation CCInputView

@synthesize myMarkedText;
@synthesize isKeyboardShown;

@synthesize hasText;
@synthesize selectedTextRange;
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

- (void)didMoveToWindow
{
#if !defined(CC_TARGET_OS_TVOS)
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardWillShowNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardDidShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardWillHideNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardDidHideNotification object:nil];
#endif
}

- (BOOL) canBecomeFirstResponder {
    return YES;
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
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
    return nil;
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

#pragma UIKeyboard notification

#if !defined(CC_TARGET_OS_TVOS)
namespace {
    UIInterfaceOrientation getFixedOrientation(UIInterfaceOrientation statusBarOrientation)
    {
        if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
        {
            statusBarOrientation = UIInterfaceOrientationPortrait;
        }
        return statusBarOrientation;
    }
}
#endif

- (void)onUIKeyboardNotification:(NSNotification *)notif
{
    NSString * type = notif.name;
    
    NSDictionary* info = [notif userInfo];
    CGRect begin = [self convertRect:
                    [[info objectForKey:UIKeyboardFrameBeginUserInfoKey] CGRectValue]
                            fromView:self];
    CGRect end = [self convertRect:
                  [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue]
                          fromView:self];
    double aniDuration = [[info objectForKey:UIKeyboardAnimationDurationUserInfoKey] doubleValue];
    
    CGSize viewSize = self.frame.size;

    CGFloat tmp;
    switch (getFixedOrientation([[[UIApplication sharedApplication].windows[0] windowScene] interfaceOrientation]))
    {
        case UIInterfaceOrientationPortrait:
            begin.origin.y = viewSize.height - begin.origin.y - begin.size.height;
            end.origin.y = viewSize.height - end.origin.y - end.size.height;
            break;
            
        case UIInterfaceOrientationPortraitUpsideDown:
            begin.origin.x = viewSize.width - (begin.origin.x + begin.size.width);
            end.origin.x = viewSize.width - (end.origin.x + end.size.width);
            break;
            
        case UIInterfaceOrientationLandscapeLeft:
            std::swap(begin.size.width, begin.size.height);
            std::swap(end.size.width, end.size.height);
            std::swap(viewSize.width, viewSize.height);
            
            tmp = begin.origin.x;
            begin.origin.x = begin.origin.y;
            begin.origin.y = viewSize.height - tmp - begin.size.height;
            tmp = end.origin.x;
            end.origin.x = end.origin.y;
            end.origin.y = viewSize.height - tmp - end.size.height;
            break;
            
        case UIInterfaceOrientationLandscapeRight:
            std::swap(begin.size.width, begin.size.height);
            std::swap(end.size.width, end.size.height);
            std::swap(viewSize.width, viewSize.height);
            
            tmp = begin.origin.x;
            begin.origin.x = begin.origin.y;
            begin.origin.y = tmp;
            tmp = end.origin.x;
            end.origin.x = end.origin.y;
            end.origin.y = tmp;
            break;
            
        default:
            break;
    }

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    float scaleX = glview->getScaleX();
    float scaleY = glview->getScaleY();
    
    // Convert to pixel coordinate
    begin = CGRectApplyAffineTransform(begin, CGAffineTransformScale(CGAffineTransformIdentity, self.contentScaleFactor, self.contentScaleFactor));
    end = CGRectApplyAffineTransform(end, CGAffineTransformScale(CGAffineTransformIdentity, self.contentScaleFactor, self.contentScaleFactor));
    
    float offestY = glview->getViewPortRect().origin.y;
    if (offestY < 0.0f)
    {
        begin.origin.y += offestY;
        begin.size.height -= offestY;
        end.size.height -= offestY;
    }
    
    // Convert to design coordinate
    begin = CGRectApplyAffineTransform(begin, CGAffineTransformScale(CGAffineTransformIdentity, 1.0f/scaleX, 1.0f/scaleY));
    end = CGRectApplyAffineTransform(end, CGAffineTransformScale(CGAffineTransformIdentity, 1.0f/scaleX, 1.0f/scaleY));

    
    cocos2d::IMEKeyboardNotificationInfo notiInfo;
    notiInfo.begin = cocos2d::Rect(begin.origin.x,
                                     begin.origin.y,
                                     begin.size.width,
                                     begin.size.height);
    notiInfo.end = cocos2d::Rect(end.origin.x,
                                   end.origin.y,
                                   end.size.width,
                                   end.size.height);
    notiInfo.duration = (float)aniDuration;
    
    cocos2d::IMEDispatcher* dispatcher = cocos2d::IMEDispatcher::sharedDispatcher();
    if (UIKeyboardWillShowNotification == type)
    {
        dispatcher->dispatchKeyboardWillShow(notiInfo);
    }
    else if (UIKeyboardDidShowNotification == type)
    {
        //CGSize screenSize = self.window.screen.bounds.size;
        self.isKeyboardShown = YES;
        dispatcher->dispatchKeyboardDidShow(notiInfo);
    }
    else if (UIKeyboardWillHideNotification == type)
    {
        dispatcher->dispatchKeyboardWillHide(notiInfo);
    }
    else if (UIKeyboardDidHideNotification == type)
    {
        self.isKeyboardShown = NO;
        dispatcher->dispatchKeyboardDidHide(notiInfo);
    }
}

@end
