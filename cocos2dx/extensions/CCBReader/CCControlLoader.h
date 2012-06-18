#ifndef _CCB_CCCONTROLLOADER_H_
#define _CCB_CCCONTROLLOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CC_DLL CCControlLoader : public CCNodeLoader {
    public:
        virtual ~CCControlLoader() {};

    protected:
        CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCControl);

        virtual void onHandlePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, BlockCCControlData *, CCBReader *);
        virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool, CCBReader *);
};

NS_CC_EXT_END

#endif
