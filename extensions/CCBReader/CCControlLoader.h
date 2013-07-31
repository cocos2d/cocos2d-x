#ifndef _CCB_CCCONTROLLOADER_H_
#define _CCB_CCCONTROLLOADER_H_

#include "CCNodeLoader.h"
#include "../GUI/CCControlExtension/CCControl.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class ControlLoader : public NodeLoader {
    public:
        virtual ~ControlLoader() {};

    protected:
        CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Control);

        virtual void onHandlePropTypeBlockControl(Node * pNode, Node * pParent, const char * pPropertyName, BlockControlData * pBlockControlData, CCBReader * ccbReader);
        virtual void onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader);
};

NS_CC_EXT_END

#endif
