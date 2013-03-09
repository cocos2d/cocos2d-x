#include "CCBSequenceProperty.h"

using namespace cocos2d;
using namespace std;

NS_CC_EXT_BEGIN

CCBSequenceProperty::CCBSequenceProperty()
: mName("")
, mType(0)
{
    init();
}

bool CCBSequenceProperty::init()
{
    mKeyframes = new CCArray();
    
    return true;
}

CCBSequenceProperty::~CCBSequenceProperty()
{
    CC_SAFE_RELEASE_NULL(mKeyframes);
}

const char* CCBSequenceProperty::getName()
{
    return mName.c_str();
}

void CCBSequenceProperty::setName(const char *pName)
{
    mName = pName;
}

int CCBSequenceProperty::getType()
{
    return mType;
}

void CCBSequenceProperty::setType(int nType)
{
    mType = nType;
}

CCArray* CCBSequenceProperty::getKeyframes()
{
    return mKeyframes;
}

NS_CC_EXT_END
