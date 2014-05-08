//
//  CCLayoutProtocol.h
//  cocos2d_libs
//
//  Created by cai wenzhi on 14-5-7.
//
//

#ifndef __cocos2d_libs__CCLayoutProtocol__
#define __cocos2d_libs__CCLayoutProtocol__

#include "cocos2d.h"

NS_CC_BEGIN

namespace layout {
    typedef enum
    {
        LAYOUT_ABSOLUTE,
        LAYOUT_LINEAR_VERTICAL,
        LAYOUT_LINEAR_HORIZONTAL,
        LAYOUT_RELATIVE
    }LayoutType;
    
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
        LayoutProtocol():_curLayoutExecutant(nullptr), _layoutType(LAYOUT_ABSOLUTE){};
        virtual ~LayoutProtocol(){CC_SAFE_RELEASE(_curLayoutExecutant);};
        
        /**
         * Sets LayoutType.
         *
         * @see LayoutType
         *
         * @param LayoutType
         */
        virtual void setLayoutType(LayoutType type);
        
        /**
         * Gets LayoutType.
         *
         * @see LayoutType
         *
         * @return LayoutType
         */
        virtual LayoutType getLayoutType() const;
        
    protected:
        LayoutExecutant* createCurrentLayoutExecutant();
        void doLayout(const Size& layoutSize, Vector<Node*> container);
        
    protected:
        LayoutExecutant* _curLayoutExecutant;
        LayoutType _layoutType;
    };
}

NS_CC_END

#endif /* defined(__cocos2d_libs__CCLayoutProtocol__) */
