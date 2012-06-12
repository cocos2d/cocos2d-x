#ifndef _CCB_CCLAYERGRADIENTLOADER_H_
#define _CCB_CCLAYERGRADIENTLOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCLayerGradientLoader : public CCLayerLoader {
    public:
        STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCLayerGradientLoader, loader);

    protected:
        virtual CCLayerGradient * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char, CCBReader *);
        virtual void onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc, CCBReader *);
};

NS_CC_EXT_END

#endif
