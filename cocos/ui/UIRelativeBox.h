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

#ifndef __UIRelativeBox_H__
#define __UIRelativeBox_H__

#include "ui/UILayout.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

namespace ui {
    
/** @class RelativeBox
*@brief @~english RelativeBox is just a convenient wrapper class for relative layout type.
 RelativeBox lays out its children relative to a widget or a position.

 @~chinese RelativeBox仅是关联布局类型的简便封装。
 RelativeBox 把它的子节点布局关联于一个widget或者一个位置。
*/
class CC_GUI_DLL RelativeBox : public Layout{
    
    
public:
    
    /**
     * @~english Default constructor.
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     */
    RelativeBox();
    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~RelativeBox();
    
    /**
     * @~english Create an empty RelativeBox instance.
     * @~chinese 创建一个空的RelativeBox实例。
     * @return @~english A RelativeBox instance. @~chinese 
     */
    static RelativeBox* create();
    
    /**
     * @~english Create a RelativeBox with a fixed size.
     * @~chinese 通过一个固定尺寸创建RelativeBox。
     * @param size @~english Size in `Size`. @~chinese 尺寸大小。
     * @return @~english A RelativeBox instance. @~chinese  RelativeBox实例。
     */
    static RelativeBox* create(const Size& size);
    
CC_CONSTRUCTOR_ACCESS:
    //initializes state of widget.
    virtual bool init() override;
    virtual bool initWithSize(const Size& size);
};
    
}

// end of ui group
/// @}
NS_CC_END

#endif /* defined(__UIRelativeBox__) */
