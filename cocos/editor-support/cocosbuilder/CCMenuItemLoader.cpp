/****************************************************************************
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

#include "editor-support/cocosbuilder/CCMenuItemLoader.h"

using namespace cocos2d;

#define PROPERTY_BLOCK "block"
#define PROPERTY_ISENABLED "isEnabled"

namespace cocosbuilder {

void MenuItemLoader::onHandlePropTypeBlock(Node * pNode, Node * pParent, const char * pPropertyName, BlockData * pBlockData, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLOCK) == 0) {
        if (nullptr != pBlockData) // Add this condition to allow MenuItemImage without target/selector predefined 
        {
            ((MenuItem *)pNode)->setCallback( std::bind( pBlockData->mSELMenuHandler, pBlockData->_target, std::placeholders::_1) );
//            ((MenuItem *)pNode)->setTarget(pBlockData->_target, pBlockData->mSELMenuHandler);
        }
    } else {
        NodeLoader::onHandlePropTypeBlock(pNode, pParent, pPropertyName, pBlockData, ccbReader);
    }
}

void MenuItemLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_ISENABLED) == 0) {
        ((MenuItem *)pNode)->setEnabled(pCheck);
    } else {
        NodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, ccbReader);
    }
}

}
