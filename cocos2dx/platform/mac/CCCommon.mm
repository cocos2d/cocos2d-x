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
#include <Cocoa/Cocoa.h>

#include "platform/CCCommon.h"

#include <stdarg.h>
#include <stdio.h>
#import "EAGLView.h"


NS_CC_BEGIN;

void CCLog(const char * pszFormat, ...)
{
    printf("Cocos2d: ");
    char szBuf[kMaxLogLen];
    
    va_list ap;
    va_start(ap, pszFormat);
    vsprintf(szBuf, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
}

// ios no MessageBox, use CCLog instead
void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
    NSString * title = (pszTitle) ? [NSString stringWithUTF8String : pszTitle] : nil;
    NSString * msg = (pszMsg) ? [NSString stringWithUTF8String : pszMsg] : nil;

	NSAlert *alert = [[[NSAlert alloc] init] autorelease];
	[alert addButtonWithTitle:@"OK"];
	[alert setMessageText:msg];
	[alert setInformativeText:title];
	[alert setAlertStyle:NSWarningAlertStyle];
	
	NSWindow *window = [[EAGLView sharedEGLView] window];
	[alert beginSheetModalForWindow:window
					  modalDelegate:[window delegate]
					 didEndSelector:nil 
						contextInfo:nil];
}

NS_CC_END;
