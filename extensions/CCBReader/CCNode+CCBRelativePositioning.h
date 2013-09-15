#ifndef __CCB_CCNODE_RELATIVEPOSITIONING_H__
#define __CCB_CCNODE_RELATIVEPOSITIONING_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCBReader.h"

NS_CC_EXT_BEGIN

extern Point getAbsolutePosition(const Point &pt, CCBReader::PositionType type, const Size &containerSize, const char *propName);

extern void setRelativeScale(Node *node, float scaleX, float scaleY, CCBReader::ScaleType type, const char* propName);

NS_CC_EXT_END

#endif // __CCB_CCNODE_RELATIVEPOSITIONING_H__
