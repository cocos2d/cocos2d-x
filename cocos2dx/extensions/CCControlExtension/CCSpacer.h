#ifndef __CCSPACER_H__
#define __CCSPACER_H__

#include "CCLayer.h"

NS_CC_BEGIN

class CC_DLL CCSpacer: public CCLayer
{
public:
    static CCSpacer* verticalSpacer(float space);
    static CCSpacer* horizontalSpacer(float space);
};

NS_CC_END

#endif