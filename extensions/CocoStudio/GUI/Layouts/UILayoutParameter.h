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

#include "UILayoutDefine.h"

NS_CC_BEGIN

namespace ui {

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
class LayoutParameter : public CCObject
{
public:
    /**
     * Default constructor
     */
    LayoutParameter() : _margin(Margin()){_layoutParameterType = LAYOUT_PARAMETER_NONE;};
    
    /**
     * Default destructor
     */
    virtual ~LayoutParameter(){};
    
    /**
     * Allocates and initializes.
     * @return A initialized LayoutParameter which is marked as "autorelease".
     */
    static LayoutParameter* create();
    
    /**
     * Sets Margin parameter for LayoutParameter.
     * 
     * @see Margin
     *
     * @param margin
     */
    void setMargin(const Margin& margin);
    
    /**
     * Gets Margin parameter of LayoutParameter.
     *
     * @see Margin
     *
     * @return const Margin&
     */
    const Margin& getMargin() const;
    
    /**
     * Gets LayoutParameterType of LayoutParameter.
     *
     * @see LayoutParameterType
     *
     * @return LayoutParameterType
     */
    LayoutParameterType getLayoutType() const;
    
    LayoutParameter* clone();
    virtual LayoutParameter* createCloneInstance();
    virtual void copyProperties(LayoutParameter* model);
protected:
    Margin _margin;
    LayoutParameterType _layoutParameterType;
};
/**
*   @js NA
*   @lua NA
*/
class LinearLayoutParameter : public LayoutParameter
{
public:
    /**
     * Default constructor
     */
    LinearLayoutParameter() : _linearGravity(LINEAR_GRAVITY_NONE){_layoutParameterType = LAYOUT_PARAMETER_LINEAR;};
    
    /**
     * Default destructor
     */
    virtual ~LinearLayoutParameter(){};
    
    /**
     * Allocates and initializes.
     * @return A initialized LayoutParameter which is marked as "autorelease".
     */
    static LinearLayoutParameter* create();
    
    /**
     * Sets LinearGravity parameter for LayoutParameter.
     *
     * @see LinearGravity
     *
     * @param LinearGravity
     */
    void setGravity(LinearGravity gravity);
    
    /**
     * Gets LinearGravity parameter for LayoutParameter.
     *
     * @see LinearGravity
     *
     * @return LinearGravity
     */
    LinearGravity getGravity() const;
    virtual LayoutParameter* createCloneInstance();
    virtual void copyProperties(LayoutParameter* model);
protected:
    LinearGravity _linearGravity;
};
/**
*   @js NA
*   @lua NA
*/

class RelativeLayoutParameter : public LayoutParameter
{
public:
    /**
     * Default constructor
     */
    RelativeLayoutParameter() : _relativeAlign(RELATIVE_ALIGN_NONE),_relativeWidgetName(""),_relativeLayoutName(""),_put(false){_layoutParameterType = LAYOUT_PARAMETER_RELATIVE;};
    
    /**
     * Default destructor
     */
    virtual ~RelativeLayoutParameter(){};
    
    /**
     * Allocates and initializes.
     * @return A initialized LayoutParameter which is marked as "autorelease".
     */
    static RelativeLayoutParameter* create();
    
    /**
     * Sets RelativeAlign parameter for LayoutParameter.
     *
     * @see RelativeAlign
     *
     * @param RelativeAlign
     */
    void setAlign(RelativeAlign align);
    
    /**
     * Gets RelativeAlign parameter for LayoutParameter.
     *
     * @see RelativeAlign
     *
     * @return RelativeAlign
     */
    RelativeAlign getAlign() const;
    
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
    
    virtual LayoutParameter* createCloneInstance();
    virtual void copyProperties(LayoutParameter* model);
protected:
    RelativeAlign _relativeAlign;
    std::string _relativeWidgetName;
    std::string _relativeLayoutName;
    bool _put;
    friend class Layout;
};

}

NS_CC_END

#endif /* defined(__LayoutParameter__) */
