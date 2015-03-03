/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "CCPUParticle3DOnPositionObserverTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUParticle3DOnPositionObserverTranslator::PUParticle3DOnPositionObserverTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DOnPositionObserverTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DObserver* ob = static_cast<PUParticle3DObserver*>(prop->parent->context);
    PUParticle3DOnPositionObserver* observer = static_cast<PUParticle3DOnPositionObserver*>(ob);

    if (prop->name == token[TOKEN_ONPOSITION_X])
    {
        // Property: position_x
        if (passValidatePropertyNumberOfValues(compiler, prop, token[TOKEN_ONPOSITION_X], 2))
        {
            std::string compareType;
            float val = 0;
            PUAbstractNodeList::const_iterator i = prop->values.begin();
            if(getString(**i, &compareType))
            {
                if (compareType == token[TOKEN_LESS_THAN])
                {
                    observer->setComparePositionX(CO_LESS_THAN);
                }
                else if (compareType == token[TOKEN_GREATER_THAN])
                {
                    observer->setComparePositionX(CO_GREATER_THAN);
                }
                else if (compareType == token[TOKEN_EQUALS])
                {
                    observer->setComparePositionX(CO_EQUALS);
                }
                ++i;
                if(getFloat(**i, &val))
                {
                    observer->setPositionXThreshold(val);
                    return true;
                }
            }
        }
    }
    else if (prop->name == token[TOKEN_ONPOSITION_Y])
    {
        // Property: position_y
        if (passValidatePropertyNumberOfValues(compiler, prop, token[TOKEN_ONPOSITION_Y], 2))
        {
            std::string compareType;
            float val = 0;
            PUAbstractNodeList::const_iterator i = prop->values.begin();
            if(getString(**i, &compareType))
            {
                if (compareType == token[TOKEN_LESS_THAN])
                {
                    observer->setComparePositionY(CO_LESS_THAN);
                }
                else if (compareType == token[TOKEN_GREATER_THAN])
                {
                    observer->setComparePositionY(CO_GREATER_THAN);
                }
                else if (compareType == token[TOKEN_EQUALS])
                {
                    observer->setComparePositionY(CO_EQUALS);
                }
                ++i;
                if(getFloat(**i, &val))
                {
                    observer->setPositionYThreshold(val);
                    return true;
                }
            }
        }
    }
    else if (prop->name == token[TOKEN_ONPOSITION_Z])
    {
        // Property: position_z
        if (passValidatePropertyNumberOfValues(compiler, prop, token[TOKEN_ONPOSITION_Z], 2))
        {
            std::string compareType;
            float val = 0;
            PUAbstractNodeList::const_iterator i = prop->values.begin();
            if(getString(**i, &compareType))
            {
                if (compareType == token[TOKEN_LESS_THAN])
                {
                    observer->setComparePositionZ(CO_LESS_THAN);
                }
                else if (compareType == token[TOKEN_GREATER_THAN])
                {
                    observer->setComparePositionZ(CO_GREATER_THAN);
                }
                else if (compareType == token[TOKEN_EQUALS])
                {
                    observer->setComparePositionZ(CO_EQUALS);
                }
                ++i;
                if(getFloat(**i, &val))
                {
                    observer->setPositionZThreshold(val);
                    return true;
                }
            }
        }
    }

    return false;
}

bool PUParticle3DOnPositionObserverTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END
