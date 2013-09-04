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

#ifndef __LAYOUTEXECUTANT_H__
#define __LAYOUTEXECUTANT_H__

#include "LayoutParameter.h"

NS_CC_EXT_BEGIN

typedef enum
{
    LAYOUT_DEFAULT,
    LAYOUT_LINEAR_VERTICAL,
    LAYOUT_LINEAR_HORIZONTAL,
    LAYOUT_RELATIVE
}LayoutType;

class Layout;

class LayoutExecutant : public CCObject
{
public:
    /**
     * Default constructor
     */
    LayoutExecutant() : m_pLayout(NULL){m_eLayoutType = LAYOUT_DEFAULT;};
    
    /**
     * Default destructor
     */
    virtual ~LayoutExecutant(){m_pLayout = NULL;};
    
    /**
     * To do layout. Need to be overrided.
     */
    virtual void doLayout()=0;
    
    /**
     * Gets LayoutType.
     *
     * @see LayoutType
     *
     * @return LayoutType
     */
    LayoutType getLayoutType(){return m_eLayoutType;};
    
    /**
     * Binding a Layout to LayoutExecutant.
     *
     * @param Layout
     */
    void setLayout(Layout* layout);
    
    /**
     * Gets the Layout of LayoutExecutant.
     *
     * @return Layout
     */
    Layout* getLayout() const;
protected:
    LayoutType m_eLayoutType;
    Layout* m_pLayout;
};

class LinearVerticalLayoutExecutant : public LayoutExecutant
{
public:
    /**
     * Default constructor
     */
    LinearVerticalLayoutExecutant(){m_eLayoutType = LAYOUT_LINEAR_VERTICAL;};
    
    /**
     * Default destructor
     */
    virtual ~LinearVerticalLayoutExecutant(){};
    
    /**
     * Allocates and initializes.
     * @return A initialized LayoutExecutant which is marked as "autorelease".
     */
    static LinearVerticalLayoutExecutant* create();
    
    //To do layout.
    virtual void doLayout();
};

class LinearHorizontalLayoutExecutant : public LayoutExecutant
{
public:
    /**
     * Default constructor
     */
    LinearHorizontalLayoutExecutant(){m_eLayoutType = LAYOUT_LINEAR_HORIZONTAL;};
    
    /**
     * Default destructor
     */
    virtual ~LinearHorizontalLayoutExecutant(){};
    
    /**
     * Allocates and initializes.
     * @return A initialized LayoutExecutant which is marked as "autorelease".
     */
    static LinearHorizontalLayoutExecutant* create();
    
    //To do layout.
    virtual void doLayout();
};

class RelativeLayoutExecutant : public LayoutExecutant
{
public:
    /**
     * Default constructor
     */
    RelativeLayoutExecutant(){m_eLayoutType = LAYOUT_RELATIVE;};
    
    /**
     * Default destructor
     */
    virtual ~RelativeLayoutExecutant(){};
    
    /**
     * Allocates and initializes.
     * @return A initialized LayoutExecutant which is marked as "autorelease".
     */
    static RelativeLayoutExecutant* create();
    
    //To do layout.
    virtual void doLayout();
};

NS_CC_EXT_END

#endif /* defined(__LayoutExecutant__) */
