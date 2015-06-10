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

#ifndef __UIVBox_H__
#define __UIVBox_H__

#include "ui/UILayout.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

namespace ui {
    
/** @class VBox
*@brief @~english VBox is just a convenient wrapper class for vertical layout type.
 VBox lays out its children in a single vertical column.

 @~chinese VBox仅仅是对垂直布局的一个简便的类封装。
 VBox把它的子节点布局在一竖列中。
*/
class CC_GUI_DLL VBox : public Layout{
public:
    
    /**
     * @~english Default constructor
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     */
    VBox();
    
    /**
     * @~english Default destructor
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~VBox();
    
    /**
     * @~english Create a empty VBox instance.
     * @~chinese 创建一个空的VBox实例。
     * @return @~english A VBox instance pointer. @~chinese VBox实例的指针。
     */
    static VBox* create();
    
    /**
     * @~english Create a VBox with a certain size.
     * @~chinese 通过一个指定的区域大小创建VBox。
     * @param size @~english The content size of the layout. @~chinese layout的内容区域大小。
     * @return @~english A VBox instance pointer. @~chinese VBox实例的指针。
     */
    static VBox* create(const Size& size);
    
CC_CONSTRUCTOR_ACCESS:
    //initializes state of widget.
    virtual bool init() override;
    virtual bool initWithSize(const Size& size);
};
    
}

// end of ui group
/// @}
NS_CC_END

#endif /* defined(__UIVBox__) */
