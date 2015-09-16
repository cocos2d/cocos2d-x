//
//  CCUITextInput.h
//  cocos2d_libs
//
//  Created by Mazyad Alabduljaleel on 9/15/15.
//
//

#ifndef cocos2d_libs_CCUITextInput_h
#define cocos2d_libs_CCUITextInput_h

static const int CC_EDIT_BOX_PADDING = 5;

/**
    This protocol provides a common interface for consolidating text input method calls
 */
@protocol CCUITextInput <NSObject>

@property (nonatomic, retain, setter=ccui_setText:) NSString *ccui_text;
@property (nonatomic, retain, setter=ccui_setPlaceholder:) NSString *ccui_placeholder;
@property (nonatomic, retain, setter=ccui_setTextColor:) UIColor *ccui_textColor;
@property (nonatomic, retain, setter=ccui_setFont:) UIFont *ccui_font;
@property (nonatomic, assign, setter=ccui_setSecureTextEntry:) BOOL ccui_secureTextEntry;

/* can only set. and not get, since the getter will only return one delegate implementation */
- (void)ccui_setDelegate:(id<UITextFieldDelegate, UITextViewDelegate>)delegate;

@end

#endif
