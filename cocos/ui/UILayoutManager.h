/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

namespace ui {
    
class LayoutProtocol;
class Widget;
class RelativeLayoutParameter;

/**
 *@brief Base class for managing layout.
 * All the concrete layout manager should inherit from this class.
 */
class CC_GUI_DLL LayoutManager : public Ref
{
public:
    virtual ~LayoutManager(){};
    LayoutManager(){};
    
    /**
     * The interface does the actual layouting work.
     */
    virtual void doLayout(LayoutProtocol *layout) = 0;
    
    friend class Layout;
};

/**
 *@brief Linear vertical layouting class.
 * Note: This class is used only by @see `Layout` class.
 * @lua NA
 * @js NA
 */
class CC_GUI_DLL LinearVerticalLayoutManager : public LayoutManager
{
private:
    LinearVerticalLayoutManager(){};
    virtual ~LinearVerticalLayoutManager(){};
    static LinearVerticalLayoutManager* create();
    virtual void doLayout(LayoutProtocol *layout) override;
    
    friend class Layout;
};

/**
 *@brief Linear horizontal layouting class.
 *Note: This class is used only by @see `Layout` class.
 * @lua NA
 * @js NA
 */
class CC_GUI_DLL LinearHorizontalLayoutManager : public LayoutManager
{
private:
    LinearHorizontalLayoutManager(){};
    virtual ~LinearHorizontalLayoutManager(){};
    static LinearHorizontalLayoutManager* create();
    virtual void doLayout(LayoutProtocol *layout) override;
    
    friend class Layout;
};

/**
 *@brief Relative layouting class.
 *Note: This class is used only by `Layout` class.
 * @lua NA
 * @js NA
 */
class CC_GUI_DLL RelativeLayoutManager : public LayoutManager
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
    bool calculateFinalPositionWithRelativeWidget(LayoutProtocol *layout);
    void calculateFinalPositionWithRelativeAlign();

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
// end of ui group
/// @}
#endif /* defined(__cocos2d_libs__CCLayoutManager__) */
