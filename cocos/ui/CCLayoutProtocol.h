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

#ifndef __CCLAYOUTPROTOCOL_H__
#define __CCLAYOUTPROTOCOL_H__

#include "cocos2d.h"

NS_CC_BEGIN

namespace ui {
    
    class LayoutExecutant : public Ref
    {
    public:
        LayoutExecutant(){};
        virtual ~LayoutExecutant(){};
        static LayoutExecutant* create();
        virtual void doLayout(const Size& layoutSize, Vector<Node*> container){};
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

    class LayoutProtocol
    {

        
    public:
        
        enum class Type
        {
            ABSOLUTE,
            VERTICAL,
            HORIZONTAL,
            RELATIVE
        };
        
        LayoutProtocol():_curLayoutExecutant(nullptr), _layoutType(Type::ABSOLUTE){};
        virtual ~LayoutProtocol(){CC_SAFE_RELEASE(_curLayoutExecutant);};
        
        /**
         * Sets LayoutType.
         *
         * @see LayoutType
         *
         * @param LayoutType
         */
        virtual void setLayoutType(Type type);
        
        /**
         * Gets LayoutType.
         *
         * @see LayoutType
         *
         * @return LayoutType
         */
        virtual Type getLayoutType() const;
        
    protected:
        LayoutExecutant* createCurrentLayoutExecutant();
        void doLayout(const Size& layoutSize, Vector<Node*> container);
        
    protected:
        LayoutExecutant* _curLayoutExecutant;
        Type _layoutType;
    };
}

NS_CC_END

#endif /* defined(__CCLayoutProtocol__) */
