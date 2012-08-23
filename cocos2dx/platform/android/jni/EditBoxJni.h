/****************************************************************************
Copyright (c) 2012 cocos2d-x.org

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
#ifndef __EDITBOX_JNI_H__
#define __EDITBOX_JNI_H__

#include <string>

typedef void (*EditBoxCallback)(const char* pText, void* ctx);

extern "C"
{
void showEditBoxDialogJni(const char* pszTitle,
                            const char* pszContent,
                            int nInputMode,
                            int nInputFlag,
                            int nReturnType,
                            int nMaxLength,
                            EditBoxCallback pfEditBoxCB,
                            void* ctx);

int getFontSizeAccordingHeightJni(int height);
std::string getStringWithEllipsisJni(const char* pszText, float width, float fontSize);

} // end of extern "C"

#endif // __EDITBOX_JNI_H__
