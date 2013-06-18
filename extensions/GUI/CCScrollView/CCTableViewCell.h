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

#include "base_nodes/CCNode.h"
#include "CCSorting.h"

NS_CC_EXT_BEGIN

/**
 * Abstract class for SWTableView cell node
 */
class CCTableViewCell: public CCNode, public CCSortableObject
{
public:
    CCTableViewCell() {}
    /**
     * The index used internally by SWTableView and its subclasses
     */
    unsigned int getIdx();
    void setIdx(unsigned int uIdx);
    /**
     * Cleans up any resources linked to this cell and resets <code>idx</code> property.
     */
    void reset();

    void setObjectID(unsigned int uIdx);
    unsigned int getObjectID();
private:
    unsigned int _idx;
};

NS_CC_EXT_END

#endif /* __CCTABLEVIEWCELL_H__ */
