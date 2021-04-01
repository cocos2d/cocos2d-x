/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "platform/CCPlatformConfig.h"
#include "platform/CCDevice.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <string>

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import <UIKit/UIKit.h>

#endif

#include "base/ccTypes.h"
#include "platform/apple/CCDevice-apple.h"

namespace FontUtils {
    NSMutableParagraphStyle* _calculateParagraphStyle(bool enableWrap, int overflow)
    {
        NSMutableParagraphStyle* paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
        paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
        return paragraphStyle;
    }
    
    NSTextAlignment _calculateTextAlignment(cocos2d::Device::TextAlign align)
    {
        unsigned uHoriFlag = (int)align & 0x0f;
        NSTextAlignment nsAlign = (2 == uHoriFlag) ? NSTextAlignmentRight
        : (3 == uHoriFlag) ? NSTextAlignmentCenter
        : NSTextAlignmentLeft;
        
        return nsAlign;
    }
    

    
    CGFloat _calculateTextDrawStartWidth(cocos2d::Device::TextAlign align, CGSize realDimensions, CGSize dimensions)
    {
        CGFloat xPadding = 0;
        unsigned uHoriFlag = (int)align & 0x0f;
        switch (uHoriFlag) {
                //center
            case 3: xPadding = (dimensions.width - realDimensions.width) / 2.0f; break;
                //right
            case 2: xPadding = dimensions.width - realDimensions.width; break;
            default: break;
        }
        return xPadding;
    }

}
