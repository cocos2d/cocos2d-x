#ifndef __CCB_CCNODE_RELATIVEPOSITIONING_H__
#define __CCB_CCNODE_RELATIVEPOSITIONING_H__

#include "cocos2d.h"
#include "CCBReader.h"

namespace cocosbuilder {

extern cocos2d::Point getAbsolutePosition(const cocos2d::Point &pt, CCBReader::PositionType type, const cocos2d::Size &containerSize, const char *propName);

extern void setRelativeScale(cocos2d::Node *node, float scaleX, float scaleY, CCBReader::ScaleType type, const char* propName);

}

#endif // __CCB_CCNODE_RELATIVEPOSITIONING_H__
