//
//  CCUISingleLineTextField.m
//  cocos2d_libs
//
//  Created by Mazyad Alabduljaleel on 9/15/15.
//
//

#import "CCUISingleLineTextField.h"
#import "CCUITextInput.h"

#include "base/CCDirector.h"


@implementation CCUISingleLineTextField

- (CGRect)textRectForBounds:(CGRect)bounds
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    
    float padding = CC_EDIT_BOX_PADDING * glview->getScaleX() / glview->getContentScaleFactor();
    return CGRectInset(bounds, padding, padding);
}

- (CGRect)editingRectForBounds:(CGRect)bounds
{
    return [self textRectForBounds:bounds];
}

@end
