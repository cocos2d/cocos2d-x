/****************************************************************************
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

#include "CCPUParticle3DForceFieldAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUParticle3DForceFieldAffectorTranslator::PUParticle3DForceFieldAffectorTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DForceFieldAffectorTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DAffector* af = static_cast<PUParticle3DAffector*>(prop->parent->context);
    PUParticle3DForceFieldAffector* affector = static_cast<PUParticle3DForceFieldAffector*>(af);

    if (prop->name == token[TOKEN_FORCEFIELD_TYPE])
    {
        // Property: forcefield_type
        if (passValidateProperty(compiler, prop, token[TOKEN_FORCEFIELD_TYPE], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                affector->suppressGeneration(true);
                if (val == token[TOKEN_REALTIME])
                {
                    affector->setForceFieldType(PUForceField::FF_REALTIME_CALC);
                    return true;
                }
                else if (val == token[TOKEN_MATRIX])
                {
                    affector->setForceFieldType(PUForceField::FF_MATRIX_CALC);
                    return true;
                }
                affector->suppressGeneration(false);
            }
        }
    }
    else if (prop->name == token[TOKEN_DELTA])
    {
        // Property: delta
        if (passValidateProperty(compiler, prop, token[TOKEN_DELTA], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->suppressGeneration(true);
                affector->setDelta(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_FORCE])
    {
        // Property: force
        if (passValidateProperty(compiler, prop, token[TOKEN_FORCE], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->suppressGeneration(true);
                affector->setScaleForce(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_OCTAVES])
    {
        // Property: octaves
        if (passValidateProperty(compiler, prop, token[TOKEN_OCTAVES], VAL_UINT))
        {
            unsigned int val = 0;
            if(getUInt(*prop->values.front(), &val))
            {
                affector->suppressGeneration(true);
                affector->setOctaves(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_FREQUENCY])
    {
        // Property: frequency
        if (passValidateProperty(compiler, prop, token[TOKEN_FREQUENCY], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->suppressGeneration(true);
                affector->setFrequency(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_AMPLITUDE])
    {
        // Property: amplitude
        if (passValidateProperty(compiler, prop, token[TOKEN_AMPLITUDE], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->suppressGeneration(true);
                affector->setAmplitude(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_PERSISTENCE])
    {
        // Property: persistence
        if (passValidateProperty(compiler, prop, token[TOKEN_PERSISTENCE], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->suppressGeneration(true);
                affector->setPersistence(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_FORCEFIELDSIZE])
    {
        // Property: forcefield_size
        if (passValidateProperty(compiler, prop, token[TOKEN_FORCEFIELDSIZE], VAL_UINT))
        {
            unsigned int val = 0;
            if(getUInt(*prop->values.front(), &val))
            {
                affector->suppressGeneration(true);
                affector->setForceFieldSize(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_WORLDSIZE])
    {
        // Property: worldsize
        if (passValidateProperty(compiler, prop, token[TOKEN_WORLDSIZE], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                affector->suppressGeneration(true);
                affector->setWorldSize(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_IGNORE_NEGATIVE_X])
    {
        // Property: ignore_negative_x
        if (passValidateProperty(compiler, prop, token[TOKEN_IGNORE_NEGATIVE_X], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                affector->suppressGeneration(true);
                affector->setIgnoreNegativeX(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_IGNORE_NEGATIVE_Y])
    {
        // Property: ignore_negative_y
        if (passValidateProperty(compiler, prop, token[TOKEN_IGNORE_NEGATIVE_Y], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                affector->suppressGeneration(true);
                affector->setIgnoreNegativeY(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_IGNORE_NEGATIVE_Z])
    {
        // Property: ignore_negative_z
        if (passValidateProperty(compiler, prop, token[TOKEN_IGNORE_NEGATIVE_Z], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                affector->suppressGeneration(true);
                affector->setIgnoreNegativeZ(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_MOVEMENT])
    {
        // Property: movement
        if (passValidateProperty(compiler, prop, token[TOKEN_MOVEMENT], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                affector->suppressGeneration(true);
                affector->setMovement(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_MOVEMENT_FREQUENCY])
    {
        // Property: movement_frequency
        if (passValidateProperty(compiler, prop, token[TOKEN_MOVEMENT_FREQUENCY], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->suppressGeneration(true);
                affector->setMovementFrequency(val);
                affector->suppressGeneration(false);
                return true;
            }
        }
    }

    return false;
}

bool PUParticle3DForceFieldAffectorTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END