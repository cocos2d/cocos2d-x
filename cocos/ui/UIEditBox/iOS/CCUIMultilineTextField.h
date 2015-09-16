//
//  CCUIMultilineTextField.h
//  cocos2d_libs
//
//  Created by Mazyad Alabduljaleel on 9/15/15.
//
//

#import <UIKit/UIKit.h>
#import "UITextView+CCUITextInput.h"

#pragma mark - UIMultilineTextField implementation

@interface CCUIMultilineTextField : UITextView

@property (nonatomic, assign) NSString *placeholder;
@property (nonatomic, retain) UILabel *placeHolderLabel;

@end
