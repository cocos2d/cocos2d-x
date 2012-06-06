#ifndef _CCLABELTTF_LOADER_H_
#define _CCLABELTTF_LOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCLabelTTFLoader : public CCNodeLoader {
    public:
        STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCLabelTTFLoader, loader);

    protected:
        virtual CCLabelTTF * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char *, CCBReader *);
        virtual void onHandlePropTypeText(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char *, CCBReader *);
        virtual void onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float, CCBReader *);
        virtual void onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int, CCBReader *);
        virtual void onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize, CCBReader *);
};

NS_CC_EXT_END

#endif
