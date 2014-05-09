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

#ifndef __LAYOUTPARMETER_H__
#define __LAYOUTPARMETER_H__

#include <string>
#include "base/CCRef.h"


NS_CC_BEGIN

namespace ui {

/**
 *   @js NA
 *   @lua NA
 */
class Margin
{
public:
    float left;
    float top;
    float right;
    float bottom;
    
public:
    Margin();
    Margin(float l, float t, float r, float b);
    Margin(const Margin& other);
    Margin& operator= (const Margin& other);
    void setMargin(float l, float t, float r, float b);
    bool equals(const Margin& target) const;
};

const Margin MarginZero = Margin();

typedef enum
{
    LAYOUT_PARAMETER_NONE,
    LAYOUT_PARAMETER_LINEAR,
    LAYOUT_PARAMETER_RELATIVE
}LayoutParameterType;
    
typedef enum
{
    LINEAR_GRAVITY_NONE,
    LINEAR_GRAVITY_LEFT,
    LINEAR_GRAVITY_TOP,
    LINEAR_GRAVITY_RIGHT,
    LINEAR_GRAVITY_BOTTOM,
    LINEAR_GRAVITY_CENTER_VERTICAL,
    LINEAR_GRAVITY_CENTER_HORIZONTAL
}LinearGravity;
    
typedef enum
{
    RELATIVE_ALIGN_NONE,
    RELATIVE_ALIGN_PARENT_TOP_LEFT,
    RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL,
    RELATIVE_ALIGN_PARENT_TOP_RIGHT,
    RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL,
    RELATIVE_CENTER_IN_PARENT,
    RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL,
    RELATIVE_ALIGN_PARENT_LEFT_BOTTOM,
    RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL,
    RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM,
    
    RELATIVE_LOCATION_ABOVE_LEFTALIGN,
    RELATIVE_LOCATION_ABOVE_CENTER,
    RELATIVE_LOCATION_ABOVE_RIGHTALIGN,
    RELATIVE_LOCATION_LEFT_OF_TOPALIGN,
    RELATIVE_LOCATION_LEFT_OF_CENTER,
    RELATIVE_LOCATION_LEFT_OF_BOTTOMALIGN,
    RELATIVE_LOCATION_RIGHT_OF_TOPALIGN,
    RELATIVE_LOCATION_RIGHT_OF_CENTER,
    RELATIVE_LOCATION_RIGHT_OF_BOTTOMALIGN,
    RELATIVE_LOCATION_BELOW_LEFTALIGN,
    RELATIVE_LOCATION_BELOW_CENTER,
    RELATIVE_LOCATION_BELOW_RIGHTALIGN
}RelativeAlign;
/**
*   @js NA
*   @lua NA
*/
class LayoutParameter : public Ref
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
    virtual LayoutParameter* createCloneInstance() override;
    virtual void copyProperties(LayoutParameter* model) override;
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
    
    virtual LayoutParameter* createCloneInstance() override;
    virtual void copyProperties(LayoutParameter* model) override;
protected:
    RelativeAlign _relativeAlign;
    std::string _relativeWidgetName;
    std::string _relativeLayoutName;
    bool _put;
    friend class RelativeLayoutExecutant;
};

}

NS_CC_END

#endif /* defined(__LayoutParameter__) */
