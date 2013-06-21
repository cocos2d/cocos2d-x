//
//  CppPointer.h
//  SmartPointer
//
//  Created by Walzer on 6/10/13.
//  Copyright (c) 2013 cocos2d-x. All rights reserved.
//

#ifndef _CppPointer_h_
#define _CppPointer_h_

#include <iostream>
#include <memory>
#include <vector>

namespace cpp {
    
    class Ref
    {
    public:        
        void retain()
        {
            ++_ref;
        }
        
        void release()
        {
            --_ref;
            if (_ref <=0)
            {
                delete this;
            }
        }
        
        int getRef()
        {
            return _ref;
        }
    protected:
        Ref():_ref(1) {};
        virtual ~Ref() {};
        
    private:
        int _ref;
    };
    
    
    class Node: public Ref
    {
    public:
        static Node* create(const char* tag)
        {
            return new Node(tag);
        }
        
        Node(const char* tag)
        {
            _tag = tag;
            // std::cout << "Cpp Node constructor: " << _tag << " " << this << std::endl;
        }
        
        virtual ~Node()
        {
            // std::cout << "Cpp Node destructor: " << _tag << " " << this << std::endl;
            
            for (auto child : _children)
            {
                child->release();
            }
        }
        
        void addChild(Node* child)
        {
            child->retain();
            _children.push_back(child);
        }
        
        void update()
        {
            // std::cout << "Cpp Node update " << _tag << " " << this << std::endl;
            
            for( auto child : _children)
            {
                // a very wild thing is that, when you try to dump a share_ptr from vector<shared_ptr>,
                // its use_count() will be 2, because iterator itself is another shared_ptr 
                // std::cout << "child ref = " << child->getRef() << " ";
                child->update();
            }
        }

        /*
        void release()
        {
            --_ref;
            if (_ref <= 0)
            {
                delete this;
            }
        }
         */
                
    protected:
        std::vector<Node*> _children;
        std::string _tag;
    };
    
}; // end of namespace cc


#endif /* defined(_CppPointer_h_) */

