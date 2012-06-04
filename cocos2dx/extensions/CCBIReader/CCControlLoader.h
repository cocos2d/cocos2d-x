#ifndef _CCCONTROL_LOADER_H_
#define _CCCONTROL_LOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCControlLoader : public CCNodeLoader {
    protected:
        virtual CCControl * createCCNode(CCNode *, CCBReader *) = 0;

        virtual void onHandlePropTypeBlockCCControl(CCNode *, CCNode *, std::string, BlockCCControlData *, CCBReader *);
        virtual void onHandlePropTypeCheck(CCNode *, CCNode *, std::string, bool, CCBReader *);
};

NS_CC_EXT_END

#endif
