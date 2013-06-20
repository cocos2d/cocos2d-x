#ifndef _CCB_CCSCROLLVIEWLOADER_H_
#define _CCB_CCSCROLLVIEWLOADER_H_

#include "CCNodeLoader.h"
#include "../GUI/CCScrollView/CCScrollView.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class ScrollViewLoader : public NodeLoader {
    public:
        virtual ~ScrollViewLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ScrollViewLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ScrollView);
		virtual void onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * pCCBReader);
        virtual void onHandlePropTypeCCBFile(Node * pNode, Node * pParent, const char * pPropertyName, Node * pCCBFileNode, CCBReader * pCCBReader);
        virtual void onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloat(Node * pNode, Node * pParent, const char * pPropertyName, float pFloat, CCBReader * pCCBReader);
        virtual void onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
