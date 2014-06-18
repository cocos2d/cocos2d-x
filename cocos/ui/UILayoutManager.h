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

#ifndef __cocos2d_libs__CCLayoutManager__
#define __cocos2d_libs__CCLayoutManager__

#include "base/CCRef.h"
#include "base/CCVector.h"

NS_CC_BEGIN

namespace ui {
    
class LayoutProtocol;
class Widget;
class RelativeLayoutParameter;

class LayoutManager : public Ref
{
public:
    virtual ~LayoutManager(){};
    LayoutManager(){};
    
    virtual void doLayout(LayoutProtocol *layout) = 0;
    
    friend class Layout;
};

class LinearVerticalLayoutManager : public LayoutManager
{
private:
    LinearVerticalLayoutManager(){};
    virtual ~LinearVerticalLayoutManager(){};
    static LinearVerticalLayoutManager* create();
    virtual void doLayout(LayoutProtocol *layout) override;
    
    friend class Layout;
};

class LinearHorizontalLayoutManager : public LayoutManager
{
private:
    LinearHorizontalLayoutManager(){};
    virtual ~LinearHorizontalLayoutManager(){};
    static LinearHorizontalLayoutManager* create();
    virtual void doLayout(LayoutProtocol *layout) override;
    
    friend class Layout;
};

class RelativeLayoutManager : public LayoutManager
{
private:
    RelativeLayoutManager()
    :_unlayoutChildCount(0),
    _widget(nullptr),
    _finalPositionX(0.0f),
    _finalPositionY(0.0f),
    _relativeWidgetLP(nullptr)
    {}
    virtual ~RelativeLayoutManager(){};
    static RelativeLayoutManager* create();
    virtual void doLayout(LayoutProtocol *layout) override;
    
    Vector<Widget*> getAllWidgets(LayoutProtocol *layout);
    Widget* getRelativeWidget(Widget* widget);
    bool caculateFinalPositionWithRelativeWidget(LayoutProtocol *layout);
    void caculateFinalPositionWithRelativeAlign();
    
    ssize_t _unlayoutChildCount;
    Vector<Widget*> _widgetChildren;
    Widget* _widget;
    float _finalPositionX;
    float _finalPositionY;
    
    RelativeLayoutParameter* _relativeWidgetLP;
    
    friend class Layout;
};

}

NS_CC_END
#endif /* defined(__cocos2d_libs__CCLayoutManager__) */
