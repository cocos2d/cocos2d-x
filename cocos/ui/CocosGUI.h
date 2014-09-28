/****************************************************************************
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

#ifndef __COCOSGUI_H__
#define __COCOSGUI_H__


#include "ui/UIWidget.h"
#include "ui/UILayout.h"
#include "ui/UIButton.h"
#include "ui/UICheckBox.h"
#include "ui/UIImageView.h"
#include "ui/UIText.h"
#include "ui/UITextAtlas.h"
#include "ui/UILoadingBar.h"
#include "ui/UIScrollView.h"
#include "ui/UIListView.h"
#include "ui/UISlider.h"
#include "ui/UITextField.h"
#include "ui/UITextBMFont.h"
#include "ui/UIPageView.h"
#include "ui/UIHelper.h"
#include "ui/UIRichText.h"
#include "ui/UIHBox.h"
#include "ui/UIVBox.h"
#include "ui/UIRelativeBox.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ui/UIVideoPlayer.h"
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "ui/UIWebView.h"
#endif
#include "ui/UIDeprecated.h"
#include "ui/GUIExport.h"
#include "ui/UIScale9Sprite.h"
#include "ui/UIEditBox/UIEditBox.h"
#include "ui/UILayoutComponent.h"

NS_CC_BEGIN
namespace ui {

CC_GUI_DLL const char* CocosGUIVersion();

}
NS_CC_END

#endif /* defined(__CocosGUITest__Cocos__) */
