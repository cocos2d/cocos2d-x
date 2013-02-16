#include "CCDevice.h"
#import <UIKit/UIKit.h>

NS_CC_BEGIN

float CCDevice::getDPI()
{
    float scale = 1.0f;
    float dpi = 0.0f;
    
    if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)]) {
        scale = [[UIScreen mainScreen] scale];
    }
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        dpi = 132 * scale;
    } else if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
        dpi = 163 * scale;
    } else {
        dpi = 160 * scale;
    }
    return dpi;
}

NS_CC_END
