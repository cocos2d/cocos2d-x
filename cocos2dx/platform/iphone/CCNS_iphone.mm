/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#import <Availability.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "platform/CCNS.h"

static cocos2d::CGRect static_CCRectFromString(const char* pszContent)
{
    CGRect rect = CGRectFromString([NSString stringWithUTF8String: pszContent]);
    cocos2d::CGRect ret(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    
    return ret;
}

static cocos2d::CGPoint static_CCPointFromString(const char* pszContent)
{
    CGPoint point = CGPointFromString([NSString stringWithUTF8String: pszContent]);
    cocos2d::CGPoint ret(point.x, point.y);
    
    return ret;
}

static cocos2d::CGSize static_CCSizeFromString(const char* pszContent)
{
    CGSize size = CGSizeFromString([NSString stringWithUTF8String: pszContent]);
    cocos2d::CGSize ret(size.width, size.height);
    
    return ret;
}

///@todo implement the functions
namespace cocos2d
{
	CGRect CCRectFromString(const char* pszContent)
	{
        return static_CCRectFromString(pszContent);
	}

	CGPoint CCPointFromString(const char* pszContent)
	{
        return static_CCPointFromString(pszContent);
	}

	CGSize CCSizeFromString(const char* pszContent)
	{
        return static_CCSizeFromString(pszContent);
	}
}