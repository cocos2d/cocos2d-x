//
//  RunTest.cpp
//  SmartPointer
//
//  Created by Walzer on 6/10/13.
//  Copyright (c) 2013 cocos2d-x. All rights reserved.
//

#include <stdio.h>
#include <memory>
#include <sstream>
#include "RunTest.h"
#include "SharedPointer.h"
#include "CppPointer.h"
#include "Profile.h"

#define LAYERS_PER_SCENE 10
#define NODES_PER_LAYER 50

void TestSharedPointer::onEnter()
{
    // std::cout << "++TestSharedPointer::onEnter()" << std::endl;
    
    // scene
    _scene = shared::Node::create("scene");

    // this scene has 10 layers
    for(int i = 0; i < LAYERS_PER_SCENE; i++)
    {
        // tag for layer
        std::stringstream num;
        num << i;
        std::string tag = "layer-" + num.str();
        
        // create and addChild
        auto layer = shared::Node::create(tag.c_str());
        _scene->addChild(layer);
                
        // each layer has 20 nodes
        for(int j = 0; j < NODES_PER_LAYER; j++)
        {
            // tag for node
            std::stringstream num;
            num << j;
            std::string tag = "node-" + num.str();
            
            // create and addChild
            auto node = shared::Node::create(tag.c_str());
            layer->addChild(node);
        }
        

    }
    
    // std::cout << "--TestSharedPointer::onEnter()" << std::endl;
}

void TestSharedPointer::update()
{
    // std::cout << "++TestSharedPointer::update()" << std::endl;
    _scene->update();
    // std::cout << "--TestSharedPointer::update()" << std::endl;
}

///////////////////////////////////////////////////////////////////
// Test C++ Pointer
TestCppPointer::~TestCppPointer()
{
    _scene->release();
}

void TestCppPointer::onEnter()
{
    // std::cout << "++TestCppPointer::onEnter()" << std::endl;
    
    // scene
    _scene = cpp::Node::create("scene");
    
    // this scene has 10 layers
    for(int i = 0; i < LAYERS_PER_SCENE; i++)
    {
        // tag for layer
        std::stringstream num;
        num << i;
        std::string tag = "layer-" + num.str();
        
        // create and addChild
        auto layer = cpp::Node::create(tag.c_str());
        _scene->addChild(layer);
        
        // each layer has 20 nodes
        for(int j = 0; j < NODES_PER_LAYER; j++)
        {
            // tag for node
            std::stringstream num;
            num << j;
            std::string tag = "node-" + num.str();
            
            // create and addChild
            auto node = cpp::Node::create(tag.c_str());
            layer->addChild(node);
            node->release();
        }
        
        layer->release();
    }
    
    // std::cout << "--TestCppPointer::onEnter()" << std::endl;
}

void TestCppPointer::update()
{
    // std::cout << "++TestCppPointer::update()" << std::endl;
    _scene->update();
    // std::cout << "--TestCppPointer::update()" << std::endl;
}



