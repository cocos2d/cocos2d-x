#include "CCNode+CCBRelativePositioning.h"
#include "CCBReader.h"

using namespace cocos2d;

namespace spritebuilder {

    Point getAbsolutePosition(Point pt, CCBReader::PositionType type, CCBReader::PositionUnit xUnit, CCBReader::PositionUnit yUnit, const Size &containerSize, const std::string& propName)
    {
        Point absPt = Point(0,0);
        
        if (xUnit == CCBReader::PositionUnit::NORMALIZED) {
            pt.x = static_cast<int>(containerSize.width * pt.x);
        }
        else if (xUnit == CCBReader::PositionUnit::SCALED) {
            float resolutionScale = CCBReader::getResolutionScale();
            pt.x = pt.x * resolutionScale;
        }
        
        if (yUnit == CCBReader::PositionUnit::NORMALIZED) {
            pt.y = static_cast<int>(containerSize.height * pt.y);
        }
        else if (yUnit == CCBReader::PositionUnit::SCALED) {
            float resolutionScale = CCBReader::getResolutionScale();
            pt.y = pt.y * resolutionScale;
        }
        
        if (type == CCBReader::PositionType::RELATIVE_BOTTOM_LEFT)
        {
            absPt = pt;
        }
        else if (type == CCBReader::PositionType::RELATIVE_TOP_LEFT)
        {
            absPt.x = pt.x;
            absPt.y = containerSize.height - pt.y;
        }
        else if (type == CCBReader::PositionType::RELATIVE_TOP_RIGHT)
        {
            absPt.x = containerSize.width - pt.x;
            absPt.y = containerSize.height - pt.y;
        }
        else if (type == CCBReader::PositionType::RELATIVE_BOTTOM_RIGHT)
        {
            absPt.x = containerSize.width - pt.x;
            absPt.y = pt.y;
        }
        /*
         else if (type == CCBReader::PositionType::PERCENT)
         {
         absPt.x = (int)(containerSize.width * pt.x / 100.0f);
         absPt.y = (int)(containerSize.height * pt.y / 100.0f);
         }
         else if (type == CCBReader::PositionType::MULTIPLY_RESOLUTION)
         {
         float resolutionScale = CCBReader::getResolutionScale();
         
         absPt.x = pt.x * resolutionScale;
         absPt.y = pt.y * resolutionScale;
         }
         */
        
        return absPt;
    }


void setRelativeScale(Node *pNode, float scaleX, float scaleY, CCBReader::ScaleType type, const std::string& propName)
{
    CCASSERT(pNode, "pNode should not be null");
    
    if (type == CCBReader::ScaleType::MULTIPLY_RESOLUTION)
    {
        float resolutionScale = CCBReader::getResolutionScale();
        
        scaleX *= resolutionScale;
        scaleY *= resolutionScale;
    }
    
    pNode->setScaleX(scaleX);
    pNode->setScaleY(scaleY);
}

}
