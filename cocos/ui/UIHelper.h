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

/**
 * @addtogroup ui
 * @{
 */
namespace ui {
    
    class Widget;

/**
 * @~english
 * Helper class for traversing children in widget tree.
 * It also provides some helper functions for layout.
 * @~chinese 
 * 这是一个遍历子节点的辅助类。
 * 它也提供了一些辅助功能布局。
 */
class CC_GUI_DLL Helper
{
public:
    /**
     * @~english
     * Find a widget with a specific tag from root widget.
     * This search will be recursive through all child widgets.
     * @~chinese
     * 查找根节点内包含特定标签的部件。
     * 此搜索将递归所有子节点（部件）。
     *
     * @param root @~english The be searched root widget.
     * @~chinese 被查找的根节点
     *
     * @param tag @~english The widget tag.
     * @~chinese 查找的标签
     *
     * @return @~english Widget instance pointer.
     * @~chinese 找到的部件节点的指针
     */
    static Widget* seekWidgetByTag(Widget* root, int tag);
    
    /**
     * @~english
     * Find a widget with a specific name from root widget.
     * This search will be recursive through all child widgets.
     *
     * @~chinese 
     * 查找根节点内特定name字段的子节点（部件）
     * 此搜索将递归所有子节点（部件）。
     * 
     * @param root @~english The be searched root widget.
     * @~chinese 被搜索的跟节点.
     *
     * @param name @~english The widget name.
     * @~chinese 需要搜索的name
     *
     * @return @~english Widget instance pointer.
     * @~chinese 找到的部件节点的指针
     */
    static Widget* seekWidgetByName(Widget* root, const std::string& name);
    
    /**
     * @~english
     * Find a widget with a specific action tag from root widget
     * This search will be recursive throught all child widgets.
     * @~chinese 
     * 查找指定节点内包含具体action tag的节点
     * 此搜索将递归所有子节点（部件）。
     *
     * @param root @~english The be searched root widget.
     * @~chinese 被搜索的根节点
     *
     * @param tag @~english The widget action's tag.
     * @~chinese 需要索搜的action tag.
     * @return @~english Widget instance pointer.
     * @~chinese 找到的部件节点的指针
     */
    static Widget* seekActionWidgetByActionTag(Widget* root, int tag);
    
    /**
     * @brief @~english Get a UTF8 substring from a std::string with a given start position and length
     *  Sample:  std::string str = "中国中国中国";  substr = getSubStringOfUTF8String(str,0,2) will = "中国"
     *
     * @~chinese 获取一个来自std::string的UTF8字符串的起始位置和长度
     * 示例:  std::string str = "中国中国中国";  substr = getSubStringOfUTF8String(str,0,2) will = "中国"
     * 
     * @param str @~english The source string.
     * @~chinese 源字符串
     *
     * @param start @~english The start position of the substring.
     * @~chinese 需要截取的起始位置
     *
     * @param length @~english The length of the substring in UTF8 count
     * @~chinese 截取的UTF8字符串长度
     *
     * @return @~english a UTF8 substring
     * @~chinese 一个UTF8字符串
     *
     * @js NA
     */
    static std::string getSubStringOfUTF8String(const std::string& str,
                                   std::string::size_type start,
                                   std::string::size_type length);
    
    /**
     * @~english
     * Refresh object and it's children layout state
     *
     * @~chinese 
     * 更新对象节点和子节点的的布局状态
     * 
     * @param rootNode @~english A Node* or Node* descendant instance pointer.
     * @~chinese 一个节点指针，或者节点的内部节点的指针
     * 
     */
    static void doLayout(Node *rootNode);

    /**
     * @~english Change the active property of Layout's
     * @~chinese 改变布局的活动状态
     *
     * @see `LayoutComponent`
     * @param active @~english A boolean value.
     * @~chinese 一个布尔值
     */
    static void changeLayoutSystemActiveState(bool active);
    
    /**
     * @brief @~english  restrict capInsetSize, when the capInsets's width is larger than the textureSize, it will restrict to 0,
     *        the height goes the same way as width.
     * @~chinese 限制capInsetSize，当capInsets的宽度比textureSize较大，它将限制为0，
     * 高度变为相同的方式宽度。
     * @param capInsets @~english A user defined capInsets.
     * @~chinese 一个用户自定义的capInsets.
     *
     * @param textureSize @~english The size of a scale9enabled texture
     * @~chinese 一个开启了九宫格的纹理的尺寸
     *
     * @return @~english a restricted capInset.
     * @~chinese 限制后的capInset.
     */
    static Rect restrictCapInsetRect(const Rect& capInsets, const Size& textureSize);
};
}

// end of ui group
/// @}
NS_CC_END

#endif /* defined(__CocoGUI__UISystem__) */
