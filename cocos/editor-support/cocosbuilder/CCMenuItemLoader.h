#ifndef _CCB_CCMENUITEMLOADER_H_
#define _CCB_CCMENUITEMLOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class MenuItemLoader : public NodeLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItemLoader() {};

protected:
    /**
     * @js NA
     * @lua NA
     */
    CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MenuItem);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeBlock(Node * pNode, Node * pParent, const char * pPropertyName, BlockData * pBlockData, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader);
};

NS_CC_EXT_END

#endif
