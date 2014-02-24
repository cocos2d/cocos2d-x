/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#include "platform/CCCommon.h"

#include "CCDirector.h"
#include "CCGLView.h"

#define GLFW_EXPOSE_NATIVE_NSGL
#define GLFW_EXPOSE_NATIVE_COCOA
#include "glfw3native.h"

#include <stdarg.h>
#include <stdio.h>
#include <Cocoa/Cocoa.h>

NS_CC_BEGIN

void LuaLog(const char * format)
{
    puts(format);
}

// ios no MessageBox, use log instead
void MessageBox(const char * msg, const char * title)
{
    NSString * tmpTitle = (title) ? [NSString stringWithUTF8String : title] : nil;
    NSString * tmpMsg = (msg) ? [NSString stringWithUTF8String : msg] : nil;

	NSAlert *alert = [[[NSAlert alloc] init] autorelease];
	[alert addButtonWithTitle:@"OK"];
	[alert setMessageText:tmpMsg];
	[alert setInformativeText:tmpTitle];
	[alert setAlertStyle:NSWarningAlertStyle];

    GLView* glview = Director::getInstance()->getOpenGLView();
    id window = glfwGetCocoaWindow(glview->getWindow());
	[alert beginSheetModalForWindow:window
					  modalDelegate:[window delegate]
					 didEndSelector:nil
						contextInfo:nil];
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_MAC

