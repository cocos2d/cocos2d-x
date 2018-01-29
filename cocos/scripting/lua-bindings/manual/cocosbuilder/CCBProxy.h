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

#ifndef __CCBPROXY_H_
#define __CCBPROXY_H_


#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "audio/include/SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "editor-support/cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

/**
 * @addtogroup lua
 * @{
 */

/**
 * CCBProxy is a proxy for cocosbuilder.
 * By using CCBProxy we could create a CCBReader object conveniently and set the Lua callback function when some events triggered should be passed onto Lua.
 */
class CCBProxy : public Layer{
public:
    /**
     * Default constructor,do nothing.
     *
     * @lua NA
     * @js NA
     */
    CCBProxy() { }
    
    /**
     * Destructor.
     *
     * @lua NA
     * @js NA
     */
    virtual ~ CCBProxy(){ }
    
    /**
     * Create a CCBProxy object.
     * 
     * @return a CCBProxy object.
     *
     * @lua NA
     * @js NA
     */
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCBProxy, create);
    
    /**
     * Create a CCBReader object.
     * 
     * @return a CCBReader object.
     *
     * @lua NA
     * @js NA
     */
    CCBReader* createCCBReader();
    
    /**
     * Read a ccb file.
     *
     * @param pszFileName the string pointer point to the file name.
     * @param pCCBReader the CCBreader object pointer.
     * @param bSetOwner whether to set the owner or not.
     * @return a Node object pointer.
     * @js NA
     */
    Node* readCCBFromFile(const char *pszFileName,CCBReader* pCCBReader,bool bSetOwner = false);
    
    /**
     * Get the true type name of pNode.
     * By using the dynamic_cast function, we could get the true type name of pNode.
     *
     * @param pNode the Node object used to query.
     * @return a string pointer point to the true type name otherwise return "No Support".
     * @js NA
     */
    const char* getNodeTypeName(Node* pNode);
    
    /**
     * Set relationship between the Lua callback function reference index handle and the node.
     * According to the different controlEvents values,we would choose different ScriptHandlerMgr::HandlerTyp.
     * When node receive the events information should be passed on to Lua, it would find the Lua callback function by the Lua callback function reference index.
     * 
     * @param node the node object should pass on the events information to Lua,when the events are triggered.
     * @param handle the Lua callback function reference index.
     * @param controlEvents the combination value of Control::EventType, default 0.
     * @js NA
     */
    void setCallback(Node* node,int handle, int controlEvents = 0);
};

// end group
/// @}

/// @cond
class CCBLayerLoader:public LayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCBLayerLoader, loader);
};
/// @endcond

#endif // __CCBPROXY_H_
