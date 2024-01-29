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

#ifndef _CCB_CCMENULOADER_H_
#define _CCB_CCMENULOADER_H_

#include "editor-support/cocosbuilder/CCLayerLoader.h"
#include "base/CCRef.h"
#include "2d/CCMenu.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class CC_DLL MenuLoader : public LayerLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuLoader() {};
    /**
     * @js NA
     * @lua NA
     */
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MenuLoader, loader);

protected:
    virtual cocos2d::Menu * createNode(cocos2d::Node * pParent, cocosbuilder::CCBReader * ccbReader)
    {
        cocos2d::Menu * pMenu = cocos2d::Menu::create();
        
        pMenu->setContentSize(cocos2d::Size::ZERO);
        
        return pMenu;
    }
};

}

#endif
