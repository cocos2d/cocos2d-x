#include "CCBXSequenceProperty.h"

NS_CC_BEGIN

namespace spritebuilder {

CCBSequenceProperty::CCBSequenceProperty()
: _name("")
, _type(0)
{
    init();
}

bool CCBSequenceProperty::init()
{
    return true;
}

CCBSequenceProperty::~CCBSequenceProperty()
{
}

const char* CCBSequenceProperty::getName()
{
    return _name.c_str();
}

void CCBSequenceProperty::setName(const char *pName)
{
    _name = pName;
}

int CCBSequenceProperty::getType()
{
    return _type;
}

void CCBSequenceProperty::setType(int type)
{
    _type = type;
}

cocos2d::Vector<CCBKeyframe*>& CCBSequenceProperty::getKeyframes()
{
    return _keyframes;
}

}

NS_CC_END