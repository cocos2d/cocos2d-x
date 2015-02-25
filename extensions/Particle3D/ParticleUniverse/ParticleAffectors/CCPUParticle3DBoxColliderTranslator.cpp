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

#include "CCPUParticle3DBoxColliderTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseColliderTranslator.h"

NS_CC_BEGIN

PUParticle3DBoxColliderTranslator::PUParticle3DBoxColliderTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DBoxColliderTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DAffector* af = static_cast<PUParticle3DAffector*>(prop->parent->context);
    PUParticle3DBoxCollider* affector = static_cast<PUParticle3DBoxCollider*>(af);

    if (prop->name == token[TOKEN_BOX_WIDTH])
    {
        if (passValidateProperty(compiler, prop, token[TOKEN_BOX_WIDTH], VAL_REAL))
        {
            // Property: box_width
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setWidth(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_BOXCOLL_WIDTH])
    {
        // Property: box_collider_width (deprecated and replaced by 'box_width')
        if (passValidateProperty(compiler, prop, token[TOKEN_BOXCOLL_WIDTH], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setWidth(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_BOX_HEIGHT])
    {
        // Property: box_height
        if (passValidateProperty(compiler, prop, token[TOKEN_BOX_HEIGHT], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setHeight(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_BOXCOLL_HEIGHT])
    {
        // Property: box_collider_height (deprecated and replaced by 'box_height')
        if (passValidateProperty(compiler, prop, token[TOKEN_BOXCOLL_HEIGHT], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setHeight(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_BOX_DEPTH])
    {
        // Property: box_depth
        if (passValidateProperty(compiler, prop, token[TOKEN_BOX_DEPTH], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setDepth(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_BOXCOLL_DEPTH])
    {
        // Property: box_collider_depth (deprecated and replaced by 'box_depth')
        if (passValidateProperty(compiler, prop, token[TOKEN_BOXCOLL_DEPTH], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setDepth(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_INNER_COLLISION])
    {
        // Property: inner_collision
        if (passValidateProperty(compiler, prop, token[TOKEN_INNER_COLLISION], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                affector->setInnerCollision(val);
                return true;
            }
        }
    }
    else
    {
        // Parse the BaseCollider
        PUParticle3DBaseColliderTranslator baseColliderTranslator;
        return baseColliderTranslator.translateChildProperty(compiler, node);
    }

    return false;
}

bool PUParticle3DBoxColliderTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END