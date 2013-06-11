//
//  SharedPointer.h
//  SmartPointer
//
//  Created by Walzer on 6/10/13.
//  Copyright (c) 2013 cocos2d-x. All rights reserved.
//

#ifndef _SharedPointer_h_
#define _SharedPointer_h_

#include <iostream>
#include <memory>
#include <vector>

namespace shared {
    
    class Node
    {
    public:
        static std::shared_ptr<Node> create(const char* tag)
        {
            // There're 3 ways to write here
            // (1) std::shared_ptr<Node> RetVal(new Node(tag));
            // (2) std::shared_ptr<Node> RetVal = std::make_shared<Node>(tag)
            // (3) auto RetVal = std::make_shared<Node>(tag)
            auto RetVal = std::make_shared<Node>(tag);
            return RetVal;
        }
        
        Node(const char* tag)
        {
            _tag = tag;
            // std::cout << "Shared Node constructor: " << _tag << " " << this << std::endl;
        }
        
        ~Node()
        {
            // std::cout << "Shared Node destructor: " << _tag << " " << this << std::endl;
        }
        
        void addChild(std::shared_ptr<Node> child)
        {
            _children.push_back(child);
        }
        
        void update()
        {
            // std::cout << "Shared Node update " << _tag << " " << this << std::endl;
            
            for( auto child : _children)
            {
                // a very wild thing is that, when you try to dump a share_ptr from vector<shared_ptr>,
                // its use_count() will be 2, because iterator itself is another shared_ptr 
                // std::cout << "child ref = " << child.use_count() << " ";
                child->update();
            }
        }
                
    protected:
        std::vector<std::shared_ptr<Node>> _children;
        std::string _tag;
    };
    
}; // end of namespace cc


#endif /* defined(_SharedPointer_h_) */

