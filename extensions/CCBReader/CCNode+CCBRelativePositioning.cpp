#include "CCNode+CCBRelativePositioning.h"
#include "CCBReader.h"

using namespace cocos2d;

NS_CC_EXT_BEGIN

CCPoint getAbsolutePosition(const CCPoint &pt, int nType, const CCSize &containerSize, const char *pPropName)
{
    CCPoint absPt = ccp(0,0);
    if (nType == kCCBPositionTypeRelativeBottomLeft)
    {
        absPt = pt;
    }
    else if (nType == kCCBPositionTypeRelativeTopLeft)
    {
        absPt.x = pt.x;
        absPt.y = containerSize.height - pt.y;
    }
    else if (nType == kCCBPositionTypeRelativeTopRight)
    {
        absPt.x = containerSize.width - pt.x;
        absPt.y = containerSize.height - pt.y;
    }
    else if (nType == kCCBPositionTypeRelativeBottomRight)
    {
        absPt.x = containerSize.width - pt.x;
        absPt.y = pt.y;
    }
    else if (nType == kCCBPositionTypePercent)
    {
        absPt.x = (int)(containerSize.width * pt.x / 100.0f);
        absPt.y = (int)(containerSize.height * pt.y / 100.0f);
    }
    else if (nType == kCCBPositionTypeMultiplyResolution)
    {
        float resolutionScale = CCBReader::getResolutionScale();
        
        absPt.x = pt.x * resolutionScale;
        absPt.y = pt.y * resolutionScale;
    }
    
    return absPt;
}

void setRelativeScale(CCNode *pNode, float fScaleX, float fScaleY, int nType, const char* pPropName)
{
    CCAssert(pNode, "pNode should not be null");
    
    if (nType == kCCBScaleTypeMultiplyResolution)
    {
        float resolutionScale = CCBReader::getResolutionScale();
        
        fScaleX *= resolutionScale;
        fScaleY *= resolutionScale;
    }
    
    pNode->setScaleX(fScaleX);
    pNode->setScaleY(fScaleY);
}

NS_CC_EXT_END
