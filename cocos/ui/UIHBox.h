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

#ifndef __UIHBox_H__
#define __UIHBox_H__

#include "ui/UILayout.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN

/**
 * @addtogroup ui
 * @{
 */
namespace ui {

/**@~english
 * HBox is just a convenient wrapper class for horizontal layout type.
 * HBox lays out its children in a single horizontal row.
 * @~chinese 
 * HBox只是一个水平布局包装类。
 * HBox里面所有的孩子节点都会水平排列成一行
 */
class CC_GUI_DLL HBox : public Layout{
public:
    
    /**@~english
     * Default constructor
     * @~chinese 
     * 默认构造函数
     * @js ctor
     * @lua new
     */
    HBox();
    
    /**@~english
     * Default destructor
     * @~chinese 
     * 默认析构函数
     * @js NA
     * @lua NA
     */
    virtual ~HBox();
    
    /**@~english
     * Create a empty HBox instance.
     * @~chinese 
     * 创建一个空的HBox实例。
     * @return @~english A HBox instance pointer.
     * @~chinese 一个HBox实例
     */
    static HBox* create();
    
    /**@~english
     *Create a HBox with a certain size.
     * @~chinese 
     * 创建一个给定大小的HBox实例
     *@param size @~english The content size of the layout.
     * @~chinese 布局器的大小。
     *@return @~english A HBox instance pointer.
     * @~chinese 一个HBox实例
     */
    static HBox* create(const Size& size);
    
CC_CONSTRUCTOR_ACCESS:
    //initializes state of widget.
    virtual bool init() override;
    virtual bool initWithSize(const Size& size);
};
    
}

// end of ui group
/// @}
NS_CC_END

#endif /* defined(__UIHBox__) */
