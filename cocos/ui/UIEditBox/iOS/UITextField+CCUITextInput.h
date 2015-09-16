//
//  UITextField+CCUITextInput.h
//  cocos2d_libs
//
//  Created by Mazyad Alabduljaleel on 9/15/15.
//
//

#import <UIKit/UIKit.h>
#import "CCUITextInput.h"


@interface UITextField (CCUITextInput) <CCUITextInput>
@end


/** Trick to load category objects without using -ObjC flag
 *  http://stackoverflow.com/questions/2567498/objective-c-categories-in-static-library
 */
extern void LoadUITextFieldCCUITextInputCategory();
