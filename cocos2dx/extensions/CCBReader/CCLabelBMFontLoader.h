#ifndef _CCB_CCLABELBMFONTLOADER_H_
#define _CCB_CCLABELBMFONTLOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CC_DLL CCLabelBMFontLoader : public CCNodeLoader {
    public:
        STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCLabelBMFontLoader, loader);

    protected:
        virtual CCLabelBMFont * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeFntFile(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char *, CCBReader *);
        virtual void onHandlePropTypeText(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char *, CCBReader *);
};

NS_CC_EXT_END

#endif
