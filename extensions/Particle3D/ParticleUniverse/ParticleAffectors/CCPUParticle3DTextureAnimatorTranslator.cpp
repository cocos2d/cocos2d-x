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

#include "CCPUParticle3DTextureAnimatorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUParticle3DTextureAnimatorTranslator::PUParticle3DTextureAnimatorTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DTextureAnimatorTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DAffector* af = static_cast<PUParticle3DAffector*>(prop->parent->context);
    PUParticle3DTextureAnimator* affector = static_cast<PUParticle3DTextureAnimator*>(af);

    if (prop->name == token[TOKEN_TIME_STEP])
    {
        // Property: time_step
        if (passValidateProperty(compiler, prop, token[TOKEN_TIME_STEP], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setAnimationTimeStep(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_TEXANIM_TIME_STEP])
    {
        // Property: time_step_animation (deprecated and replaced by 'time_step')
        if (passValidateProperty(compiler, prop, token[TOKEN_TEXANIM_TIME_STEP], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setAnimationTimeStep(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_START_TEXANIM_TEXCOORDS_RANGE])
    {
        // Property: start_texture_coords_range
        if (passValidateProperty(compiler, prop, token[TOKEN_START_TEXANIM_TEXCOORDS_RANGE], VAL_UINT))
        {
            unsigned int val = 0;
            if(getUInt(*prop->values.front(), &val))
            {
                affector->setTextureCoordsStart(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_TEXANIM_TEXCOORDS_START])
    {
        // Property: texture_coords_start (deprecated and replaced by start_texture_coords_range)
        if (passValidateProperty(compiler, prop, token[TOKEN_TEXANIM_TEXCOORDS_START], VAL_UINT))
        {
            unsigned int val = 0;
            if(getUInt(*prop->values.front(), &val))
            {
                affector->setTextureCoordsStart(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_END_TEXANIM_TEXCOORDS_RANGE])
    {
        // Property: texture_coords_end
        if (passValidateProperty(compiler, prop, token[TOKEN_END_TEXANIM_TEXCOORDS_RANGE], VAL_UINT))
        {
            unsigned int val = 0;
            if(getUInt(*prop->values.front(), &val))
            {
                affector->setTextureCoordsEnd(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_TEXANIM_TEXCOORDS_END])
    {
        // Property: texture_coords_end (deprecated and replaced by end_texture_coords_range)
        if (passValidateProperty(compiler, prop, token[TOKEN_TEXANIM_TEXCOORDS_END], VAL_UINT))
        {
            unsigned int val = 0;
            if(getUInt(*prop->values.front(), &val))
            {
                affector->setTextureCoordsEnd(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_TEXANIM_ANIMATION_TYPE])
    {
        // Property: texture_animation_type
        if (passValidateProperty(compiler, prop, token[TOKEN_TEXANIM_ANIMATION_TYPE], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                if (val == token[TOKEN_TEXANIM_LOOP])
                {
                    affector->setTextureAnimationType(PUParticle3DTextureAnimator::TAT_LOOP);
                    return true;
                }
                else if (val == token[TOKEN_TEXANIM_UP_DOWN])
                {
                    affector->setTextureAnimationType(PUParticle3DTextureAnimator::TAT_UP_DOWN);
                    return true;
                }
                else if (val == token[TOKEN_TEXANIM_RANDOM])
                {
                    affector->setTextureAnimationType(PUParticle3DTextureAnimator::TAT_RANDOM);
                    return true;
                }
            }
        }
    }
    else if (prop->name == token[TOKEN_TEXANIM_START_RANDOM])
    {
        // Property: texture_start_random
        if (passValidateProperty(compiler, prop, token[TOKEN_TEXANIM_START_RANDOM], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                affector->setStartRandom(val);
                return true;
            }
        }
    }

    return false;
}

bool PUParticle3DTextureAnimatorTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END