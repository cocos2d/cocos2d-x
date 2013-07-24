#ifndef __CCB_CCNODE_RELATIVEPOSITIONING_H__
#define __CCB_CCNODE_RELATIVEPOSITIONING_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

extern Point getAbsolutePosition(const Point &pt, int nType, const Size &containerSize, const char *pPropName);

extern void setRelativeScale(Node *pNode, float fScaleX, float fScaleY, int nType, const char* pPropName);

NS_CC_EXT_END

#endif // __CCB_CCNODE_RELATIVEPOSITIONING_H__
