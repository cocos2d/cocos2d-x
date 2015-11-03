#ifndef __CCBPROXY_H_
#define __CCBPROXY_H_

#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "audio/include/SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

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
