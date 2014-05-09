#ifndef __CCB_CCNODE_RELATIVEPOSITIONING_H__
#define __CCB_CCNODE_RELATIVEPOSITIONING_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCBReader.h"

namespace spritebuilder {

extern cocos2d::Vector2 getAbsolutePosition(const cocos2d::Vector2 &position,
                                            const CCBReader::PositionUnit xUnit,
                                            const CCBReader::PositionUnit yUnit,
                                            const CCBReader::PositionType corner,
                                            const cocos2d::Size &containerSize,
                                            const std::string& propName);

extern void setRelativeScale(cocos2d::Node *node, float scaleX, float scaleY, CCBReader::ScaleType type, const std::string& propName);

}

#endif // __CCB_CCNODE_RELATIVEPOSITIONING_H__
