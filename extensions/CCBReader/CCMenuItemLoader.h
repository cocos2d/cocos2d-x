#ifndef _CCB_CCMENUITEMLOADER_H_
#define _CCB_CCMENUITEMLOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class MenuItemLoader : public NodeLoader {
    public:
        virtual ~MenuItemLoader() {};

    protected:
        CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MenuItem);

        virtual void onHandlePropTypeBlock(Node * pNode, Node * pParent, const char * pPropertyName, BlockData * pBlockData, CCBReader * ccbReader);
        virtual void onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader);
};

NS_CC_EXT_END

#endif
