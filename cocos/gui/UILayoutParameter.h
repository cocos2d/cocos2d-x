/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __LAYOUTPARMETER_H__
#define __LAYOUTPARMETER_H__

#include "gui/UILayoutDefine.h"

namespace gui {

typedef enum
{
    LAYOUT_PARAMETER_NONE,
    LAYOUT_PARAMETER_LINEAR,
    LAYOUT_PARAMETER_RELATIVE
}LayoutParameterType;
/**
*   @js NA
*   @lua NA
*/
class UILayoutParameter : public cocos2d::Object
{
public:
    /**
     * Default constructor
     */
    UILayoutParameter() : _margin(UIMargin()){_layoutParameterType = LAYOUT_PARAMETER_NONE;};
    
    /**
     * Default destructor
     */
    virtual ~UILayoutParameter(){};
    
    /**
     * Allocates and initializes.
     * @return A initialized LayoutParameter which is marked as "autorelease".
     */
    static UILayoutParameter* create();
    
    /**
     * Sets Margin parameter for LayoutParameter.
     * 
     * @see UIMargin
     *
     * @param margin
     */
    void setMargin(const UIMargin& margin);
    
    /**
     * Gets Margin parameter of LayoutParameter.
     *
     * @see UIMargin
     *
     * @return const UIMargin&
     */
    const UIMargin& getMargin() const;
    
    /**
     * Gets LayoutParameterType of LayoutParameter.
     *
     * @see LayoutParameterType
     *
     * @return LayoutParameterType
     */
    LayoutParameterType getLayoutType() const;
protected:
    UIMargin _margin;
    LayoutParameterType _layoutParameterType;
};
/**
*   @js NA
*   @lua NA
*/
class UILinearLayoutParameter : public UILayoutParameter
{
public:
    /**
     * Default constructor
     */
    UILinearLayoutParameter() : _linearGravity(LINEAR_GRAVITY_NONE){_layoutParameterType = LAYOUT_PARAMETER_LINEAR;};
    
    /**
     * Default destructor
     */
    virtual ~UILinearLayoutParameter(){};
    
    /**
     * Allocates and initializes.
     * @return A initialized LayoutParameter which is marked as "autorelease".
     */
    static UILinearLayoutParameter* create();
    
    /**
     * Sets UILinearGravity parameter for LayoutParameter.
     *
     * @see UILinearGravity
     *
     * @param UILinearGravity
     */
    void setGravity(UILinearGravity gravity);
    
    /**
     * Gets UILinearGravity parameter for LayoutParameter.
     *
     * @see UILinearGravity
     *
     * @return UILinearGravity
     */
    UILinearGravity getGravity() const;
protected:
    UILinearGravity _linearGravity;
};
/**
*   @js NA
*   @lua NA
*/

class UILayout;

class UIRelativeLayoutParameter : public UILayoutParameter
{
public:
    /**
     * Default constructor
     */
    UIRelativeLayoutParameter() : _relativeAlign(RELATIVE_ALIGN_NONE),_relativeWidgetName(""),_relativeLayoutName(""),_put(false){_layoutParameterType = LAYOUT_PARAMETER_RELATIVE;};
    
    /**
     * Default destructor
     */
    virtual ~UIRelativeLayoutParameter(){};
    
    /**
     * Allocates and initializes.
     * @return A initialized LayoutParameter which is marked as "autorelease".
     */
    static UIRelativeLayoutParameter* create();
    
    /**
     * Sets UIRelativeAlign parameter for LayoutParameter.
     *
     * @see UIRelativeAlign
     *
     * @param UIRelativeAlign
     */
    void setAlign(UIRelativeAlign align);
    
    /**
     * Gets UIRelativeAlign parameter for LayoutParameter.
     *
     * @see UIRelativeAlign
     *
     * @return UIRelativeAlign
     */
    UIRelativeAlign getAlign() const;
    
    /**
     * Sets a key for LayoutParameter. Witch widget named this is relative to.
     *
     * @param name
     */
    void setRelativeToWidgetName(const char* name);
    
    /**
     * Gets the key of LayoutParameter. Witch widget named this is relative to.
     *
     * @return name
     */
    const char* getRelativeToWidgetName() const;
    
    /**
     * Sets a name in Relative Layout for LayoutParameter.
     *
     * @param name
     */
    void setRelativeName(const char* name);
    
    /**
     * Gets a name in Relative Layout of LayoutParameter.
     *
     * @return name
     */
    const char* getRelativeName() const;
protected:
    UIRelativeAlign _relativeAlign;
    std::string _relativeWidgetName;
    std::string _relativeLayoutName;
    bool _put;
    friend class UILayout;
};

}

#endif /* defined(__LayoutParameter__) */
