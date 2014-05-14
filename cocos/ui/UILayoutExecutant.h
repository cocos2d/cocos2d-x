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

#ifndef __cocos2d_libs__CCLayoutExecutant__
#define __cocos2d_libs__CCLayoutExecutant__

#include "UILayout.h"

NS_CC_BEGIN

namespace ui {

class LayoutExecutant : public Ref
{
public:
    LayoutExecutant(){};
    virtual ~LayoutExecutant(){};
    
    virtual void doLayout(const Size& layoutSize, Vector<Node*> container) = 0;
};

class LinearVerticalLayoutExecutant : public LayoutExecutant
{
public:
    LinearVerticalLayoutExecutant(){};
    virtual ~LinearVerticalLayoutExecutant(){};
    static LinearVerticalLayoutExecutant* create();
    virtual void doLayout(const Size& layoutSize, Vector<Node*> container);
};

class LinearHorizontalLayoutExecutant : public LayoutExecutant
{
public:
    LinearHorizontalLayoutExecutant(){};
    virtual ~LinearHorizontalLayoutExecutant(){};
    static LinearHorizontalLayoutExecutant* create();
    virtual void doLayout(const Size& layoutSize, Vector<Node*> container);
};

class RelativeLayoutExecutant : public LayoutExecutant
{
public:
    RelativeLayoutExecutant(){};
    virtual ~RelativeLayoutExecutant(){};
    static RelativeLayoutExecutant* create();
    virtual void doLayout(const Size& layoutSize, Vector<Node*> container);
};

    
class LayoutExecutantFactory
{
public:
    static LayoutExecutantFactory* getInstance();
    LayoutExecutant* createExecutant(Layout::Type type);
private:
    LayoutExecutantFactory(){}
    CC_DISALLOW_COPY_AND_ASSIGN(LayoutExecutantFactory);
    
    static LayoutExecutantFactory *_instance;
};

}

NS_CC_END
#endif /* defined(__cocos2d_libs__CCLayoutExecutant__) */
