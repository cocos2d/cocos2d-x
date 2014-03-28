#ifndef __CCB_CCNODE_RELATIVEPOSITIONING_H__
#define __CCB_CCNODE_RELATIVEPOSITIONING_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

extern CC_EX_DLL CCPoint getAbsolutePosition(const CCPoint &pt, int nType, const CCSize &containerSize, const char *pPropName);

extern CC_EX_DLL void setRelativeScale(CCNode *pNode, float fScaleX, float fScaleY, int nType, const char* pPropName);

NS_CC_EXT_END

#endif // __CCB_CCNODE_RELATIVEPOSITIONING_H__
