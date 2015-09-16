//
//  UITextField+CCUITextInput.m
//  cocos2d_libs
//
//  Created by Mazyad Alabduljaleel on 9/15/15.
//
//

#import "UITextField+CCUITextInput.h"

@implementation UITextField (CCUITextInput)

- (NSString *)ccui_text
{
    return self.text;
}

- (void)ccui_setText:(NSString *)ccui_text
{
    self.text = ccui_text;
}

- (NSString *)ccui_placeholder
{
    return self.placeholder;
}

- (void)ccui_setPlaceholder:(NSString *)ccui_placeholder
{
    self.placeholder = ccui_placeholder;
}

- (UIColor *)ccui_textColor
{
    return self.textColor;
}

- (void)ccui_setTextColor:(UIColor *)ccui_textColor
{
    self.textColor = ccui_textColor;
}

- (UIFont *)ccui_font
{
    return self.font;
}

- (void)ccui_setFont:(UIFont *)ccui_font
{
    self.font = ccui_font;
}

- (BOOL)ccui_secureTextEntry
{
    return self.secureTextEntry;
}

- (void)ccui_setSecureTextEntry:(BOOL)ccui_secureTextEntry
{
    self.secureTextEntry = ccui_secureTextEntry;
}

- (void)ccui_setDelegate:(id<UITextFieldDelegate,UITextViewDelegate>)delegate
{
    self.delegate = delegate;
}

@end


void LoadUITextFieldCCUITextInputCategory() {
    // noop
}
