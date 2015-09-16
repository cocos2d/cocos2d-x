//
//  CCUIEditBoxIOS.h
//  cocos2d_libs
//
//  Created by Mazyad Alabduljaleel on 9/15/15.
//
//

#import <UIKit/UIKit.h>
#import "CCUITextInput.h"
#include "UIEditBoxImpl-ios.h"


@interface UIEditBoxImplIOS_objc : NSObject <UITextFieldDelegate, UITextViewDelegate>

@property (nonatomic, retain) UIView<UITextInput, CCUITextInput> *textInput;
@property (nonatomic, assign) void *editBox;
@property (nonatomic, assign) NSString *text;
@property (nonatomic, assign) CGRect frameRect;
@property (nonatomic, assign) cocos2d::ui::EditBox::InputFlag dataInputMode;
@property (nonatomic, assign) cocos2d::ui::EditBox::KeyboardReturnType keyboardReturnType;
@property (nonatomic, readonly, getter = isEditState) BOOL editState;

- (instancetype)initWithFrame:(CGRect)frameRect editBox:(void *)editBox;
- (void)doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance;

- (NSString *)getDefaultFontName;

- (void)setInputMode:(cocos2d::ui::EditBox::InputMode)inputMode;
- (void)setInputFlag:(cocos2d::ui::EditBox::InputFlag)flag;
- (void)setReturnType:(cocos2d::ui::EditBox::KeyboardReturnType)returnType;

- (void)setPlaceHolder:(NSString *)text;
- (void)setVisible:(BOOL)visible;
- (void)setTextColor:(UIColor*)color;
- (void)setFont:(UIFont *)font;
- (void)setPosition:(CGPoint)pos;
- (void)setContentSize:(CGSize)size;

- (void)openKeyboard;
- (void)closeKeyboard;

@end
