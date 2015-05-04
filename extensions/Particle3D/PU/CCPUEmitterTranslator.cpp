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

#include "CCPUEmitterTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"
#include "extensions/Particle3D/PU/CCPUEmitterManager.h"

NS_CC_BEGIN

PUEmitterTranslator::PUEmitterTranslator()
:_emitter(nullptr)
{
}
//-------------------------------------------------------------------------
void PUEmitterTranslator::translate(PUScriptCompiler* compiler, PUAbstractNode *node)
{
    PUObjectAbstractNode* obj = reinterpret_cast<PUObjectAbstractNode*>(node);
    PUObjectAbstractNode* parent = obj->parent ? reinterpret_cast<PUObjectAbstractNode*>(obj->parent) : 0;

    // The name of the obj is the type of the emitter
    // Remark: This can be solved by using a listener, so that obj->values is filled with type + name. Something for later
    std::string type;
    if(!obj->name.empty())
    {
        type = obj->name;
    }
    

    //// Get the factory
    //ParticleEmitterFactory* particleEmitterFactory = ParticleSystemManager::getSingletonPtr()->getEmitterFactory(type);
    //if (!particleEmitterFactory)
    //{
    //	compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
    //	return;
    //}
    PUScriptTranslator *particleEmitterTranlator = PUEmitterManager::Instance()->getTranslator(type);
    if (!particleEmitterTranlator) return;

    //// Create the emitter
    //mEmitter = ParticleSystemManager::getSingletonPtr()->createEmitter(type);
    //if (!mEmitter)
    //{
    //	compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
    //	return;
    //}
    _emitter = PUEmitterManager::Instance()->createEmitter(type);
    if (!_emitter) return;
	_emitter->setEmitterType(type);

    if (parent && parent->context)
    {
        PUParticleSystem3D* system = static_cast<PUParticleSystem3D*>(parent->context);
        system->addEmitter(_emitter);
    }

    // The first value is the (optional) name
    std::string name;
    if(!obj->values.empty())
    {
        getString(*obj->values.front(), &name);
        _emitter->setName(name);
    }

    // Set it in the context
    obj->context = _emitter;

    // Run through properties
    for(PUAbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
    {
        if((*i)->type == ANT_PROPERTY)
        {
            PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>((*i));
            if (prop->name == token[TOKEN_ENABLED])
            {
                // Property: enabled
                if (passValidateProperty(compiler, prop, token[TOKEN_ENABLED], VAL_BOOL))
                {
                    bool val;
                    if(getBoolean(*prop->values.front(), &val))
                    {
                        _emitter->setEnabled(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_POSITION])
            {
                // Property: positon
                if (passValidateProperty(compiler, prop, token[TOKEN_POSITION], VAL_VECTOR3))
                {
                    Vec3 val;
                    if(getVector3(prop->values.begin(), prop->values.end(), &val))
                    {
                        //mEmitter->position = val;
                        //mEmitter->originalPosition = val;
                        _emitter->setLocalPosition(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_DIRECTION])
            {
                // Property: direction
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_DIRECTION], VAL_VECTOR3))
                {
                    Vec3 val;
                    if(getVector3(prop->values.begin(), prop->values.end(), &val))
                    {
                        _emitter->setParticleDirection(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_ORIENTATION])
            {
                // Property: orientation
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_ORIENTATION], VAL_QUATERNION))
                {
                    Quaternion val;
                    if(getQuaternion(prop->values.begin(), prop->values.end(), &val))
                    {
                        _emitter->setParticleOrientation(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_START_ORIENTATION_RANGE])
            {
                // Property: start_orientation_range
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_START_ORIENTATION_RANGE], VAL_QUATERNION))
                {
                    Quaternion val;
                    if(getQuaternion(prop->values.begin(), prop->values.end(), &val))
                    {
                        _emitter->setParticleOrientationRangeStart(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_ORIENTATION_RANGE_START])
            {
                // Property: range_start_orientation (deprecated and replaced by start_orientation_range)
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_ORIENTATION_RANGE_START], VAL_QUATERNION))
                {
                    Quaternion val;
                    if(getQuaternion(prop->values.begin(), prop->values.end(), &val))
                    {
                        _emitter->setParticleOrientationRangeStart(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_END_ORIENTATION_RANGE])
            {
                // Property: end_orientation_range
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_END_ORIENTATION_RANGE], VAL_QUATERNION))
                {
                    Quaternion val;
                    if(getQuaternion(prop->values.begin(), prop->values.end(), &val))
                    {
                        _emitter->setParticleOrientationRangeEnd(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_ORIENTATION_RANGE_END])
            {
                // Property: range_end_orientation (deprecated and replaced by end_orientation_range)
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_ORIENTATION_RANGE_END], VAL_QUATERNION))
                {
                    Quaternion val;
                    if(getQuaternion(prop->values.begin(), prop->values.end(), &val))
                    {
                        _emitter->setParticleOrientationRangeEnd(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_EMISSION_RATE])
            {
                // Property: emission_rate
                // If it is a property, it is a fixed value
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_EMISSION_RATE], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                        dynamicAttributeFixed->setValue(val);
                        _emitter->setDynEmissionRate(dynamicAttributeFixed);
                    }
                }
            }
            else if (prop->name == token[TOKEN_TIME_TO_LIVE])
            {
                // Property: time_to_live
                // If it is a property, it is a fixed value
                if (passValidateProperty(compiler, prop, token[TOKEN_TIME_TO_LIVE], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                        dynamicAttributeFixed->setValue(val);
                        _emitter->setDynTotalTimeToLive(dynamicAttributeFixed);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_MASS])
            {
                // Property: mass
                // If it is a property, it is a fixed value
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_MASS], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                        dynamicAttributeFixed->setValue(val);
                        _emitter->setDynParticleMass(dynamicAttributeFixed);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_START_TEXCOORDS_RANGE])
            {
                // Property: start_texture_coords_range
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_START_TEXCOORDS_RANGE], VAL_UINT))
                {
                    unsigned int val = 0;
                    if(getUInt(*prop->values.front(), &val))
                    {
                        _emitter->setParticleTextureCoordsRangeStart(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_START_TEXCOORDS])
            {
                // Property: start_texture_coords (deprecated and replaced by start_texture_coords_range)
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_START_TEXCOORDS], VAL_UINT))
                {
                    unsigned int val = 0;
                    if(getUInt(*prop->values.front(), &val))
                    {
                        _emitter->setParticleTextureCoordsRangeStart(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_END_TEXCOORDS_RANGE])
            {
                // Property: end_texture_coords_range
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_END_TEXCOORDS_RANGE], VAL_UINT))
                {
                    unsigned int val = 0;
                    if(getUInt(*prop->values.front(), &val))
                    {
                        _emitter->setParticleTextureCoordsRangeEnd(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_END_TEXCOORDS])
            {
                // Property: end_texture_coords (deprecated and replaced by end_texture_coords_range)
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_END_TEXCOORDS], VAL_UINT))
                {
                    unsigned int val = 0;
                    if(getUInt(*prop->values.front(), &val))
                    {
                        _emitter->setParticleTextureCoordsRangeEnd(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_TEXCOORDS])
            {
                // Property: texture_coords
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_TEXCOORDS], VAL_UINT))
                {
                    unsigned int val = 0;
                    if(getUInt(*prop->values.front(), &val))
                    {
                        _emitter->setParticleTextureCoords(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_START_COLOUR_RANGE])
            {
                // Property: start_colour_range
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_START_COLOUR_RANGE], VAL_COLOURVALUE))
                {
                    Vec4 val;
                    if(getVector4(prop->values.begin(), prop->values.end(), &val))
                    {
                        _emitter->setParticleColorRangeStart(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_END_COLOUR_RANGE])
            {
                // Property: end_colour_range
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_END_COLOUR_RANGE], VAL_COLOURVALUE))
                {
                    Vec4 val;
                    if(getVector4(prop->values.begin(), prop->values.end(), &val))
                    {
                        _emitter->setParticleColorRangeEnd(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_COLOUR])
            {
                // Property: colour
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_COLOUR], VAL_COLOURVALUE))
                {
                    Vec4 val;
                    if(getVector4(prop->values.begin(), prop->values.end(), &val))
                    {
                        _emitter->setParticleColor(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_VELOCITY])
            {
                // Property: velocity
                // If it is a property, it is a fixed value
                if (passValidateProperty(compiler, prop, token[TOKEN_VELOCITY], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                        dynamicAttributeFixed->setValue(val);
                        _emitter->setDynVelocity(dynamicAttributeFixed);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_DURATION])
            {
                // Property: duration
                // If it is a property, it is a fixed value
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_DURATION], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                        dynamicAttributeFixed->setValue(val);
                        _emitter->setDynDuration(dynamicAttributeFixed);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_REPEAT_DELAY])
            {
                // Property: repeat_delay
                // If it is a property, it is a fixed value
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_REPEAT_DELAY], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                        dynamicAttributeFixed->setValue(val);
                        _emitter->setDynRepeatDelay(dynamicAttributeFixed);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_EMITS])
            {
                // Property: emits
                if (passValidatePropertyNumberOfValues(compiler, prop, token[TOKEN_EMITTER_EMITS], 2))
                {
                    std::string particleType;
                    PUAbstractNodeList::const_iterator it = prop->values.begin();
                    if (getString(**it, &particleType))
                    {
                        if (particleType == token[TOKEN_VISUAL_PARTICLE])
                        {
                            _emitter->setEmitsType(PUParticle3D::PT_VISUAL);
                        }
                        else if (particleType == token[TOKEN_EMITTER_PARTICLE])
                        {
                            _emitter->setEmitsType(PUParticle3D::PT_EMITTER);
                        }
                        else if (particleType == token[TOKEN_AFFECTOR_PARTICLE])
                        {
                            _emitter->setEmitsType(PUParticle3D::PT_AFFECTOR);
                        }
                        else if (particleType == token[TOKEN_TECHNIQUE_PARTICLE])
                        {
                            _emitter->setEmitsType(PUParticle3D::PT_TECHNIQUE);
                        }
                        else if (particleType == token[TOKEN_SYSTEM_PARTICLE])
                        {
                            _emitter->setEmitsType(PUParticle3D::PT_SYSTEM);
                        }
                        ++it;
                        if (getString(**it, &name))
                        {
                            _emitter->setEmitsName(name);
                        }
                    }
                }
            }
            else if (prop->name == token[TOKEN_ANGLE])
            {
                // Property: angle
                // If it is a property, it is a fixed value
                if (passValidateProperty(compiler, prop, token[TOKEN_ANGLE], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                        dynamicAttributeFixed->setValue(val);
                        _emitter->setDynAngle(dynamicAttributeFixed);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_ALL_PARTICLE_DIM])
            {
                // Property: all_particle_dimensions
                // If it is a property, it is a fixed value
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_ALL_PARTICLE_DIM], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                        dynamicAttributeFixed->setValue(val);
                        _emitter->setDynParticleAllDimensions(dynamicAttributeFixed);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_PARTICLE_WIDTH])
            {
                // Property: particle_width
                // If it is a property, it is a fixed value
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_PARTICLE_WIDTH], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                        dynamicAttributeFixed->setValue(val);
                        _emitter->setDynParticleWidth(dynamicAttributeFixed);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_PARTICLE_HEIGHT])
            {
                // Property: particle_height
                // If it is a property, it is a fixed value
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_PARTICLE_HEIGHT], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                        dynamicAttributeFixed->setValue(val);
                        _emitter->setDynParticleHeight(dynamicAttributeFixed);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_PARTICLE_DEPTH])
            {
                // Property: particle_depth
                // If it is a property, it is a fixed value
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_PARTICLE_DEPTH], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                        dynamicAttributeFixed->setValue(val);
                        _emitter->setDynParticleDepth(dynamicAttributeFixed);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_AUTO_DIRECTION])
            {
                // Property: auto_direction
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_AUTO_DIRECTION], VAL_BOOL))
                {
                    bool val;
                    if(getBoolean(*prop->values.front(), &val))
                    {
                        _emitter->setAutoDirection(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_KEEP_LOCAL])
            {
                // Property: keep_local
                if (passValidateProperty(compiler, prop, token[TOKEN_KEEP_LOCAL], VAL_BOOL))
                {
                    bool val;
                    if(getBoolean(*prop->values.front(), &val))
                    {
                        _emitter->setKeepLocal(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_EMITTER_FORCE_EMISSION])
            {
                // Property: force_emission
                if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_FORCE_EMISSION], VAL_BOOL))
                {
                    bool val;
                    if(getBoolean(*prop->values.front(), &val))
                    {
                        _emitter->setForceEmission(val);
                    }
                }
            }
            else if (particleEmitterTranlator->translateChildProperty(compiler, *i))
            {
                // Parsed the property by another translator; do nothing
            }
            else
            {
                errorUnexpectedProperty(compiler, prop);
            }
        }
        else if((*i)->type == ANT_OBJECT)
        {
            PUObjectAbstractNode* child = reinterpret_cast<PUObjectAbstractNode*>((*i));
            PUDynamicAttributeTranslator dynamicAttributeTranslator;
            if (child->cls == token[TOKEN_EMITTER_EMISSION_RATE])
            {
                // Property: emission_rate
                dynamicAttributeTranslator.translate(compiler, *i);
                PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
                _emitter->setDynEmissionRate(dynamicAttribute);
            }
            else if (child->cls == token[TOKEN_TIME_TO_LIVE])
            {
                // Property: time_to_live
                dynamicAttributeTranslator.translate(compiler, *i);
                PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
                _emitter->setDynTotalTimeToLive(dynamicAttribute);
            }
            else if (child->cls == token[TOKEN_EMITTER_MASS])
            {
                // Property: mass
                dynamicAttributeTranslator.translate(compiler, *i);
                PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
                _emitter->setDynParticleMass(dynamicAttribute);
            }
            else if (child->cls == token[TOKEN_VELOCITY])
            {
                // Property: velocity
                dynamicAttributeTranslator.translate(compiler, *i);
                PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
                _emitter->setDynVelocity(dynamicAttribute);
            }
            else if (child->cls == token[TOKEN_EMITTER_DURATION])
            {
                // Property: duration
                dynamicAttributeTranslator.translate(compiler, *i);
                PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
                _emitter->setDynDuration(dynamicAttribute);
            }
            else if (child->cls == token[TOKEN_EMITTER_REPEAT_DELAY])
            {
                // Property: repeat_delay
                dynamicAttributeTranslator.translate(compiler, *i);
                PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
                _emitter->setDynRepeatDelay(dynamicAttribute);
            }
            else if (child->cls == token[TOKEN_ANGLE])
            {
                // Property: angle
                dynamicAttributeTranslator.translate(compiler, *i);
                PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
                _emitter->setDynAngle(dynamicAttribute);
            }
            else if (child->cls == token[TOKEN_EMITTER_ALL_PARTICLE_DIM])
            {
                // Property: all_particle_dimensions
                dynamicAttributeTranslator.translate(compiler, *i);
                PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
                _emitter->setDynParticleAllDimensions(dynamicAttribute);
            }
            else if (child->cls == token[TOKEN_EMITTER_PARTICLE_WIDTH])
            {
                // Property: particle_width
                dynamicAttributeTranslator.translate(compiler, *i);
                PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
                _emitter->setDynParticleWidth(dynamicAttribute);
            }
            else if (child->cls == token[TOKEN_EMITTER_PARTICLE_HEIGHT])
            {
                // Property: particle_height
                dynamicAttributeTranslator.translate(compiler, *i);
                PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
                _emitter->setDynParticleHeight(dynamicAttribute);
            }
            else if (child->cls == token[TOKEN_EMITTER_PARTICLE_DEPTH])
            {
                // Property: particle_depth
                dynamicAttributeTranslator.translate(compiler, *i);
                PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
                _emitter->setDynParticleDepth(dynamicAttribute);
            }
            else if (child->cls == token[TOKEN_CAMERA_DEPENDENCY])
            {
                //// Property: it can only be a camera_dependency for emission rate
                //CameraDependency* cameraDependency = PU_NEW_T(CameraDependency, MEMCATEGORY_SCRIPTING)();
                //child->context = Any(cameraDependency);
                //CameraDependencyTranslator cameraDependencyTranslator;
                //cameraDependencyTranslator.translate(compiler, *i);
                //Real threshold = cameraDependency->getThreshold();
                //mEmitter->setEmissionRateCameraDependency(threshold * threshold, cameraDependency->isIncrease());

                //// Delete the camera dependency
                //PU_DELETE_T(cameraDependency, CameraDependency, MEMCATEGORY_SCRIPTING);
            }
            else if (particleEmitterTranlator->translateChildObject(compiler, *i))
            {
                // Parsed the object by another translator; do nothing
            }
            else
            {
                processNode(compiler, *i);
            }
        }
        else
        {
            errorUnexpectedToken(compiler, *i);
        }
    }
}

NS_CC_END