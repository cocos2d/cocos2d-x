#ifndef __CCB_CCNODE_RELATIVEPOSITIONING_H__
#define __CCB_CCNODE_RELATIVEPOSITIONING_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

extern cocos2d::CCPoint getAbsolutePosition(const cocos2d::CCPoint &pt, int nType, const cocos2d::CCSize &containerSize, const char *pPropName);

extern void setRelativeScale(cocos2d::CCNode *pNode, float fScaleX, float fScaleY, int nType, const char* pPropName);

NS_CC_EXT_END

#endif // __CCB_CCNODE_RELATIVEPOSITIONING_H__
