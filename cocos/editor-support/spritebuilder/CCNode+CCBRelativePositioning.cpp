#include "CCNode+CCBRelativePositioning.h"
#include "CCBReader.h"

using namespace cocos2d;

namespace spritebuilder {

Vector2 getAbsolutePosition(const Vector2 &position,
                            const CCBReader::PositionUnit xUnit,
                            const CCBReader::PositionUnit yUnit,
                            const CCBReader::PositionType corner,
                            const Size &containerSize,
                            const std::string& propName)
{
    Vector2 positionInPoints;
    float x = 0;
    float y = 0;
    
    switch( xUnit ) {
        case CCBReader::PositionUnit::PositionUnitPoints:
            x = position.x;
            break;
            
        case CCBReader::PositionUnit::PositionUnitUIPoints:
            x = position.x * CC_CONTENT_SCALE_FACTOR();
            break;
            
        case CCBReader::PositionUnit::PositionUnitNormalized:
            x = position.x * containerSize.width;
            break;
    }
    
    switch( yUnit ) {
        case CCBReader::PositionUnit::PositionUnitPoints:
            y = position.y;
            break;
            
        case CCBReader::PositionUnit::PositionUnitUIPoints:
            y = position.y * CC_CONTENT_SCALE_FACTOR();
            break;
            
        case CCBReader::PositionUnit::PositionUnitNormalized:
            y = position.y * containerSize.height;
            break;
    }
    
    switch( corner ) {
        case CCBReader::PositionType::RELATIVE_BOTTOM_LEFT:
            // Nothing needs to be done
            break;
            
        case CCBReader::PositionType::RELATIVE_TOP_LEFT:
            // Reverse y-axis
            y = containerSize.height - y;
            break;
            
        case CCBReader::PositionType::RELATIVE_TOP_RIGHT:
            // Reverse x-axis and y-axis
            x = containerSize.width - x;
            y = containerSize.height - y;
            break;
            
        case CCBReader::PositionType::RELATIVE_BOTTOM_RIGHT:
            // Reverse x-axis
            x = containerSize.width - x;
            break;
    }
    
    positionInPoints.x = x;
    positionInPoints.y = y;
    
    return positionInPoints;
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
