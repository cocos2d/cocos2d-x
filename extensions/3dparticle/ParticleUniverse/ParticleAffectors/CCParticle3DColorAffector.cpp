/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#include "CCParticle3DColorAffector.h"
#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const Particle3DColorAffector::ColorOperation Particle3DColorAffector::DEFAULT_COLOR_OPERATION = Particle3DColorAffector::CAO_SET;

//-----------------------------------------------------------------------
Particle3DColorAffector::Particle3DColorAffector() : 
    PUParticle3DAffector(),
    _colorOperation(DEFAULT_COLOR_OPERATION)
{
}

Particle3DColorAffector::~Particle3DColorAffector()
{
}
//-----------------------------------------------------------------------
const Particle3DColorAffector::ColorOperation& Particle3DColorAffector::getColorOperation () const
{
    return _colorOperation;
}
//-----------------------------------------------------------------------
void Particle3DColorAffector::setColorOperation (const Particle3DColorAffector::ColorOperation& colorOperation)
{
    _colorOperation = colorOperation;
}
//-----------------------------------------------------------------------
void Particle3DColorAffector::addColor (float timeFraction, const Vec4& color)
{
    _colorMap[timeFraction] = color;
}
//-----------------------------------------------------------------------
const Particle3DColorAffector::ColorMap& Particle3DColorAffector::getTimeAndColor() const
{
    return _colorMap;
}
//-----------------------------------------------------------------------
void Particle3DColorAffector::clearColorMap ()
{
    _colorMap.clear();
}
//-----------------------------------------------------------------------
Particle3DColorAffector::ColorMapIterator Particle3DColorAffector::findNearestColorMapIterator(float timeFraction)
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

void Particle3DColorAffector::updateAffector( PUParticle3D *particle, float deltaTime )
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
        it2++;
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

NS_CC_END