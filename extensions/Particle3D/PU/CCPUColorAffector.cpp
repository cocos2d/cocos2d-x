/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCPUColorAffector.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const PUColorAffector::ColorOperation PUColorAffector::DEFAULT_COLOR_OPERATION = PUColorAffector::CAO_SET;

//-----------------------------------------------------------------------
PUColorAffector::PUColorAffector() : 
    PUAffector(),
    _colorOperation(DEFAULT_COLOR_OPERATION)
{
}

PUColorAffector::~PUColorAffector()
{
}
//-----------------------------------------------------------------------
const PUColorAffector::ColorOperation& PUColorAffector::getColorOperation () const
{
    return _colorOperation;
}
//-----------------------------------------------------------------------
void PUColorAffector::setColorOperation (const PUColorAffector::ColorOperation& colorOperation)
{
    _colorOperation = colorOperation;
}
//-----------------------------------------------------------------------
void PUColorAffector::addColor (float timeFraction, const Vec4& color)
{
    _colorMap[timeFraction] = color;
}
//-----------------------------------------------------------------------
const PUColorAffector::ColorMap& PUColorAffector::getTimeAndColor() const
{
    return _colorMap;
}
//-----------------------------------------------------------------------
void PUColorAffector::clearColorMap ()
{
    _colorMap.clear();
}
//-----------------------------------------------------------------------
PUColorAffector::ColorMapIterator PUColorAffector::findNearestColorMapIterator(float timeFraction)
{
    ColorMapIterator it;
    for (it = _colorMap.begin(); it != _colorMap.end(); ++it)
    {
        if (timeFraction < it->first)
        {
            if (it == _colorMap.begin())
                return it;
            else
                return --it;
        }
    }

    // If not found return the last valid iterator
    return --it;
}

void PUColorAffector::updatePUAffector( PUParticle3D *particle, float /*deltaTime*/ )
{
    // Fast rejection
    if (_colorMap.empty())
        return;

    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        // Linear interpolation of the colour
        Vec4 color = Vec4::ONE;
        float timeFraction = (particle->totalTimeToLive - particle->timeToLive) / particle->totalTimeToLive;
        ColorMapIterator it1 = findNearestColorMapIterator(timeFraction);
        ColorMapIterator it2 = it1;
        ++it2;
        if (it2 != _colorMap.end())
        {
            // Interpolate colour

            color = it1->second + ((it2->second - it1->second) * ((timeFraction - it1->first)/(it2->first - it1->first)));
        }
        else
        {
            color = it1->second;
        }

        // Determine operation
        if (_colorOperation == CAO_SET)
        {
            // No operation, so just set the colour
            particle->color = color;
        }
        else
        {
            // Multiply
            particle->color = Vec4(color.x * particle->originalColor.x, color.y * particle->originalColor.y, color.z * particle->originalColor.z, color.w * particle->originalColor.w);
        }
    }
}

PUColorAffector* PUColorAffector::create()
{
    auto pca = new (std::nothrow) PUColorAffector();
    pca->autorelease();
    return pca;
}

void PUColorAffector::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PUColorAffector* colourAffector = static_cast<PUColorAffector*>(affector);
    colourAffector->_colorMap = _colorMap;
    colourAffector->_colorOperation = _colorOperation;
}

NS_CC_END
