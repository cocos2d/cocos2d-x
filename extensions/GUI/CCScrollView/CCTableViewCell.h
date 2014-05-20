/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2010 Sangwoo Im
 
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

#ifndef __CCTABLEVIEWCELL_H__
#define __CCTABLEVIEWCELL_H__

#include "extensions/ExtensionMacros.h"
#include "2d/CCNode.h"

NS_CC_EXT_BEGIN

/**
 * 用于表示TableView中单元格的抽象类（译者注：此处没有纯虚函数，实际为普通基类，不能算抽象类）
 */
class TableViewCell: public Node
{
public:
    CREATE_FUNC(TableViewCell);
    
    TableViewCell() {}
    /**
     * TableView及其派生类内部使用的索引
     */
    ssize_t getIdx() const;
    void setIdx(ssize_t uIdx);
    /**
     * 对此单元格中一切相关的资源进行清理，并重置 <code>idx</code> 属性
     */
    void reset();

private:
    ssize_t _idx;
};

NS_CC_EXT_END

#endif /* __CCTABLEVIEWCELL_H__ */
