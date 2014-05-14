#ifndef __CCB_CCNODE_RELATIVEPOSITIONING_H__
#define __CCB_CCNODE_RELATIVEPOSITIONING_H__

#include "CCBReader.h"

namespace cocosbuilder {

extern cocos2d::Vec2 getAbsolutePosition(const cocos2d::Vec2 &pt, CCBReader::PositionType type, const cocos2d::Size &containerSize, const std::string&propName);

extern void setRelativeScale(cocos2d::Node *node, float scaleX, float scaleY, CCBReader::ScaleType type, const std::string& propName);

}

#endif // __CCB_CCNODE_RELATIVEPOSITIONING_H__
