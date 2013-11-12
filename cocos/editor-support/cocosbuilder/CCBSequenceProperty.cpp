#include "CCBSequenceProperty.h"

using namespace cocos2d;
using namespace std;

namespace cocosbuilder {

CCBSequenceProperty::CCBSequenceProperty()
: _name("")
, _type(0)
{
    init();
}

bool CCBSequenceProperty::init()
{
    _keyframes = new Array();
    _keyframes->init();

    return true;
}

CCBSequenceProperty::~CCBSequenceProperty()
{
    CC_SAFE_RELEASE_NULL(_keyframes);
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

Array* CCBSequenceProperty::getKeyframes()
{
    return _keyframes;
}

}
