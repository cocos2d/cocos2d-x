#ifndef _CCB_CCSCROLLVIEWLOADER_H_
#define _CCB_CCSCROLLVIEWLOADER_H_

#include "CCNodeLoader.h"
#include "../GUI/CCScrollView/CCScrollView.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCScrollViewLoader : public CCNodeLoader {
    public:
        virtual ~CCScrollViewLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCScrollViewLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCScrollView);
		virtual void onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, CCBReader * pCCBReader);
        virtual void onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCNode * pCCBFileNode, CCBReader * pCCBReader);
        virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloat, CCBReader * pCCBReader);
        virtual void onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
