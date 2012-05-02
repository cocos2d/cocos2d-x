#include "CCSpacer.h"

NS_CC_EXT_BEGIN

CCSpacer* CCSpacer::verticalSpacer(float space)
{
    CCSpacer *pRet = new CCSpacer();
    pRet->init();
    pRet->setContentSize(CCSizeMake(0, space));
    pRet->autorelease();
    return pRet;
}

CCSpacer* CCSpacer::horizontalSpacer(float space)
{
    CCSpacer *pRet = new CCSpacer();
    pRet->init();
    pRet->setContentSize(CCSizeMake(space, 0));
    pRet->autorelease();
    return pRet;
}

NS_CC_EXT_END
