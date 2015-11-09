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

/**@~english
 * CCBProxy is a proxy for cocosbuilder.
 * By using CCBProxy we could create a CCBReader object conveniently and set the Lua callback function when some events triggered should be passed onto Lua.
 * @~chinese 
 * CCBProxy是cocosbuilder代理类。
 * 通过使用CCBProxy，我们可以方便地创建一个CCBReader对象，并设置回调函数用于处理一些需要传递给Lua的事件。
 */
class CCBProxy : public Layer{
public:
    /**@~english
     * Default constructor,do nothing.
     *
     * @~chinese 
     * 默认构造函数,不做任何事情。
     * 
     * @lua NA
     * @js NA
     */
    CCBProxy() { }
    
    /**@~english
     * Destructor.
     *
     * @~chinese 
     * 析构函数。
     * 
     * @lua NA
     * @js NA
     */
    virtual ~ CCBProxy(){ }
    
    /**@~english
     * Create a CCBProxy object.
     * 
     * @~chinese 
     * 创建一个CCBProxy对象。
     * 
     * @return @~english a CCBProxy object.
     *
     * @~chinese CCBProxy对象。
     * 
     * @lua NA
     * @js NA
     */
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCBProxy, create);
    
    /**@~english
     * Create a CCBReader object.
     * 
     * @~chinese 
     * 创建一个CCBReader对象。
     * 
     * @return @~english a CCBReader object.
     *
     * @~chinese CCBReader对象。
     * 
     * @lua NA
     * @js NA
     */
    CCBReader* createCCBReader();
    
    /**@~english
     * Read a ccb file.
     *
     * @~chinese 
     * 读取一个ccb文件。
     * 
     * @param pszFileName @~english the string pointer point to the file name.
     * @~chinese ccb文件名称。
     * @param pCCBReader @~english the CCBreader object pointer.
     * @~chinese CCBreader对象指针。
     * @param bSetOwner @~english whether to set the owner or not.
     * @~chinese 是否设置所有者。
     * @return @~english a Node object pointer.
     * @~chinese 一个Node对象指针。
     * @js NA
     */
    Node* readCCBFromFile(const char *pszFileName,CCBReader* pCCBReader,bool bSetOwner = false);
    
    /**@~english
     * Get the real type name of pNode.
     * By using the dynamic_cast function, we could get the real type name of pNode.
     *
     * @~chinese 
     * 获取pNode的真实类型名。
     * 通过调用dynamic_cast函数,我们可以获取pNode的真实类型名。
     * 
     * @param pNode @~english the Node object used to query.
     * @~chinese 用于查询的Node对象指针。
     * @return @~english a string pointer point to the real type name or return "No Support".
     * @~chinese 返回一个真实类型名或者“No Support”。
     * @js NA
     */
    const char* getNodeTypeName(Node* pNode);
    
    /**@~english
     * Set relationship between the Lua callback function reference id handle and the node.
     * According to the different controlEvents values,we would choose different ScriptHandlerMgr::HandlerTyp.
     * When node receive the events information should be passed into Lua, it would find the Lua callback funtion by the handle.Then, push the related data into Lua stack.
     * Finally. call the Lua function.
     * 
     * @~chinese 
     * 设置对应Lua回调函数的handle和node对象的映射关系。
     * 同时根据不同controlEvents值,我们会选择不同的ScriptHandlerMgr::HandlerTyp来构建映射关系。
     * 当node接收到需要传递到Lua的事件时，它会通过handle找到对应的Lua函数，然后将数据信息作为函数参数压入Lua栈中，最后调用Lua函数。
     * 
     * @param node @~english the node object have related with handle.And it would be push into the Lua stack as the function parameter，when the events are triggered.
     * @~chinese 和handl关联的node对象。在事件触发时，它将作为Lua函数的参数压入到Lua栈中。
     * @param handle @~english the Lua callback function reference id.
     * @~chinese Lua函数的reference id。
     * @param controlEvents @~english the combination value of Control::EventType, default 0.
     * @~chinese Control::EventType的组合值,默认为0。
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
