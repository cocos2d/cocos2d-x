#ifndef _CCCONTROL_LOADER_H_
#define _CCCONTROL_LOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCControlLoader : public CCNodeLoader {
    protected:
        virtual CCControl * createCCNode(CCNode *, CCBReader *) = 0;

        virtual void onHandlePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, const char * pPropertyName, BlockCCControlData *, CCBReader *);
        virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool, CCBReader *);
};

NS_CC_EXT_END

#endif
