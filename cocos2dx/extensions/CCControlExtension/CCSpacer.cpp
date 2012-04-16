#include "CCSpacer.h"


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