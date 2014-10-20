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

#ifndef __UIHELPER_H__
#define __UIHELPER_H__

#include <string>
#include "platform/CCPlatformMacros.h"
#include "ui/GUIExport.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

namespace ui {
    
    class Widget;

/**
*   @js NA
*   @lua NA
*/
class CC_GUI_DLL Helper
{
public:
    /**
     * Finds a widget whose tag equals to param tag from root widget.
     *
     * @param root      widget which will be seeked.
     *
     * @tag             tag value.
     *
     * @return finded result.
     */
    static Widget* seekWidgetByTag(Widget* root, int tag);
    
    /**
     * Finds a widget whose name equals to param name from root widget.
     *
     * @param root      widget which will be seeked.
     *
     * @name             name value.
     *
     * @return finded result.
     */
    static Widget* seekWidgetByName(Widget* root, const std::string& name);
    
    /*temp action*/
    static Widget* seekActionWidgetByActionTag(Widget* root, int tag);
    
    /**
     * @brief Get a UTF8 substring from a std::string with a given start position and length
     *  Sample:  std::string str = "中国中国中国";  substr = getSubStringOfUTF8String(str,0,2) will = "中国"
     * @param start The start position of the substring.
     * @param length The length of the substring in UTF8 count
     * @return a UTF8 substring
     */
    static std::string getSubStringOfUTF8String(const std::string& str,
                                   std::string::size_type start,
                                   std::string::size_type length);
    
    static void doLayout(Node *rootNode);

};
}

NS_CC_END

#endif /* defined(__CocoGUI__UISystem__) */
