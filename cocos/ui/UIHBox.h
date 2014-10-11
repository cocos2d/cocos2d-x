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

namespace ui {

class CC_GUI_DLL HBox : public Layout{
    
    
public:
    
    /**
     * Default constructor
     */
    HBox();
    
    /**
     * Default destructor
     */
    virtual ~HBox();
    
    /**
     * Allocates and initializes a HBox.
     */
    static HBox* create();
    
    static HBox* create(const Size& size);
    
CC_CONSTRUCTOR_ACCESS:
    //initializes state of widget.
    virtual bool init() override;
    virtual bool initWithSize(const Size& size);
};
    
}

NS_CC_END

#endif /* defined(__UIHBox__) */
