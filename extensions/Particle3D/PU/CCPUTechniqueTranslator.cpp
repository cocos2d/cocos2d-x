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

#include "CCPUTechniqueTranslator.h"
#include "extensions/Particle3D/PU/CCPUMaterialManager.h"

NS_CC_BEGIN

PUTechniqueTranslator::PUTechniqueTranslator()//:mTechnique(0)
{
    
}
PUTechniqueTranslator::~PUTechniqueTranslator()
{
    
}

void PUTechniqueTranslator::translate(PUScriptCompiler* compiler, PUAbstractNode *node)
{
    PUObjectAbstractNode* obj = reinterpret_cast<PUObjectAbstractNode*>(node);
    PUObjectAbstractNode* parent = obj->parent ? reinterpret_cast<PUObjectAbstractNode*>(obj->parent) : 0;
    
    // Create the technique
    _system = PUParticleSystem3D::create();
    //mTechnique = ParticleSystemManager::getSingletonPtr()->createTechnique();
    //if (!mTechnique)
    //{
    //    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
    //    return;
    //}
    
    if (parent && parent->context)
    {
        PUParticleSystem3D* system = static_cast<PUParticleSystem3D*>(parent->context);
        system->addChild(_system);
    }
    //else
    //{
    //    // It is an alias
    //    mTechnique->setAliasName(parent->name); // PU 1.4
    //    ParticleSystemManager::getSingletonPtr()->addAlias(mTechnique);
    //}
    
    _system->setName(obj->name);
    obj->context = _system; // Add this to the context, because it is needed for the underlying emitters, affectors, ...
    
    // Get the name of the technique
    //if(!obj->name.empty())
    //    mTechnique->setName(obj->name);
    
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
                        _system->setEnabled(val);
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
                        _system->setPosition3D(val);
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
                        _system->setKeepLocal(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_TECH_VISUAL_PARTICLE_QUOTA])
            {
                // Property: visual_particle_quota
                if (passValidateProperty(compiler, prop, token[TOKEN_TECH_VISUAL_PARTICLE_QUOTA], VAL_UINT))
                {
                    unsigned int val = 0;
                    if(getUInt(*prop->values.front(), &val))
                    {
                        _system->setParticleQuota(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_TECH_EMITTED_EMITTER_QUOTA])
            {
                // Property: emitted_emitter_quota
                if (passValidateProperty(compiler, prop, token[TOKEN_TECH_EMITTED_EMITTER_QUOTA], VAL_UINT))
                {
                    unsigned int val = 0;
                    if(getUInt(*prop->values.front(), &val))
                    {
                        _system->setEmittedEmitterQuota(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_TECH_EMITTED_AFFECTOR_QUOTA])
            {
                //// Property: emitted_affector_quota
                //if (passValidateProperty(compiler, prop, token[TOKEN_TECH_EMITTED_AFFECTOR_QUOTA], VAL_UINT))
                //{
                //    uint val = 0;
                //    if(getUInt(prop->values.front(), &val))
                //    {
                //        mTechnique->setEmittedAffectorQuota(val);
                //    }
                //}
            }
            else if (prop->name == token[TOKEN_TECH_EMITTED_TECHNIQUE_QUOTA])
            {
                // Property: emitted_technique_quota
                if (passValidateProperty(compiler, prop, token[TOKEN_TECH_EMITTED_TECHNIQUE_QUOTA], VAL_UINT))
                {
                    unsigned int val = 0;
                    if(getUInt(*prop->values.front(), &val))
                    {
                        _system->setEmittedSystemQuota(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_TECH_EMITTED_SYSTEM_QUOTA])
            {
                //// Property: emitted_system_quota
                //if (passValidateProperty(compiler, prop, token[TOKEN_TECH_EMITTED_SYSTEM_QUOTA], VAL_UINT))
                //{
                //    uint val = 0;
                //    if(getUInt(prop->values.front(), &val))
                //    {
                //        mTechnique->setEmittedSystemQuota(val);
                //    }
                //}
            }
            else if (prop->name == token[TOKEN_MATERIAL])
            {
                // Property: material
                if (passValidateProperty(compiler, prop, token[TOKEN_MATERIAL], VAL_STRING))
                {
                    std::string val;
                    if(getString(*prop->values.front(), &val))
                    {
                        _system->setMaterialName(val);
                        PUMaterial *material = PUMaterialCache::Instance()->getMaterial(val);
                        if (material){
                            _system->setBlendFunc(material->blendFunc);
                        }
                    }
                }
            }
            else if (prop->name == token[TOKEN_TECH_LOD_INDEX])
            {
                //// Property: lod_index
                //if (passValidateProperty(compiler, prop, token[TOKEN_TECH_LOD_INDEX], VAL_UINT))
                //{
                //    uint val = 0;
                //    if(getUInt(prop->values.front(), &val))
                //    {
                //        mTechnique->setLodIndex(val);
                //    }
                //}
            }
            else if (prop->name == token[TOKEN_TECH_DEFAULT_PARTICLE_WIDTH])
            {
                // Property: default_particle_width
                if (passValidateProperty(compiler, prop, token[TOKEN_TECH_DEFAULT_PARTICLE_WIDTH], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        _system->setDefaultWidth(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_TECH_DEFAULT_PARTICLE_HEIGHT])
            {
                // Property: default_particle_height
                if (passValidateProperty(compiler, prop, token[TOKEN_TECH_DEFAULT_PARTICLE_HEIGHT], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        _system->setDefaultHeight(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_TECH_DEFAULT_PARTICLE_DEPTH])
            {
                // Property: default_particle_depth
                if (passValidateProperty(compiler, prop, token[TOKEN_TECH_DEFAULT_PARTICLE_DEPTH], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        _system->setDefaultDepth(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_TECH_SPHASHING_CELL_DIMENSION])
            {
                //// Property: spatial_hashing_cell_dimension
                //if (passValidateProperty(compiler, prop, token[TOKEN_TECH_SPHASHING_CELL_DIMENSION], VAL_UINT))
                //{
                //    unsigned int val = 0;
                //    if(getUInt(prop->values.front(), &val))
                //    {
                //        mTechnique->setSpatialHashingCellDimension(val);
                //    }
                //}
            }
            else if (prop->name == token[TOKEN_TECH_SPHASHING_CELL_OVERLAP])
            {
                //// Property: spatial_hashing_cell_overlap
                //if (passValidateProperty(compiler, prop, token[TOKEN_TECH_SPHASHING_CELL_OVERLAP], VAL_UINT))
                //{
                //    unsigned int val = 0;
                //    if(getUInt(prop->values.front(), &val))
                //    {
                //        mTechnique->setSpatialHashingCellOverlap(val);
                //    }
                //}
            }
            else if (prop->name == token[TOKEN_TECH_SPHASHING_SIZE])
            {
                //// Property: spatial_hashtable_size
                //if (passValidateProperty(compiler, prop, token[TOKEN_TECH_SPHASHING_SIZE], VAL_UINT))
                //{
                //    unsigned int val = 0;
                //    if(getUInt(prop->values.front(), &val))
                //    {
                //        mTechnique->setSpatialHashTableSize(val);
                //    }
                //}
            }
            else if (prop->name == token[TOKEN_TECH_SPHASHING_UPDATE_INTERVAL])
            {
                //// Property: spatial_hashing_update_interval
                //if (passValidateProperty(compiler, prop, token[TOKEN_TECH_SPHASHING_UPDATE_INTERVAL], VAL_REAL))
                //{
                //    float val = 0.0f;
                //    if(getReal(prop->values.front(), &val))
                //    {
                //        mTechnique->setSpatialHashingInterval(val);
                //    }
                //}
            }
            else if (prop->name == token[TOKEN_TECH_MAX_VELOCITY])
            {
                // Property: max_velocity
                if (passValidateProperty(compiler, prop, token[TOKEN_TECH_MAX_VELOCITY], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        _system->setMaxVelocity(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_USE_ALIAS])
            {
                //// Property: use_alias
                //if (passValidateProperty(compiler, prop, token[TOKEN_USE_ALIAS], VAL_STRING))
                //{
                //    String val;
                //    if(getString(prop->values.front(), &val))
                //    {
                //        IAlias* alias = ParticleSystemManager::getSingletonPtr()->getAlias(val);
                //        switch (alias->getAliasType())
                //        {
                //            case IAlias::AT_RENDERER:
                //            {
                //                ParticleRenderer* renderer = static_cast<ParticleRenderer*>(alias);
                //                ParticleRenderer* newRenderer = ParticleSystemManager::getSingletonPtr()->cloneRenderer(renderer);
                //                mTechnique->setRenderer(newRenderer);
                //            }
                //                break;
                //                
                //            case IAlias::AT_EMITTER:
                //            {
                //                ParticleEmitter* emitter = static_cast<ParticleEmitter*>(alias);
                //                ParticleEmitter* newEmitter = ParticleSystemManager::getSingletonPtr()->cloneEmitter(emitter);
                //                mTechnique->addEmitter(newEmitter);
                //            }
                //                break;
                //                
                //            case IAlias::AT_AFFECTOR:
                //            {
                //                ParticleAffector* affector = static_cast<ParticleAffector*>(alias);
                //                ParticleAffector* newAffector = ParticleSystemManager::getSingletonPtr()->cloneAffector(affector);
                //                mTechnique->addAffector(newAffector);
                //            }
                //                break;
                //                
                //            case IAlias::AT_OBSERVER:
                //            {
                //                ParticleObserver* observer = static_cast<ParticleObserver*>(alias);
                //                ParticleObserver* newObserver = ParticleSystemManager::getSingletonPtr()->cloneObserver(observer);
                //                mTechnique->addObserver(newObserver);
                //            }
                //                break;
                //                
                //            case IAlias::AT_EXTERN:
                //            {
                //                Extern* externObject = static_cast<Extern*>(alias);
                //                Extern* newExternObject = ParticleSystemManager::getSingletonPtr()->cloneExtern(externObject);
                //                mTechnique->addExtern(newExternObject);
                //            }
                //                break;
                //                
                //            case IAlias::AT_BEHAVIOUR:
                //            {
                //                ParticleBehaviour* behaviour = static_cast<ParticleBehaviour*>(alias);
                //                ParticleBehaviour* newBehaviour = ParticleSystemManager::getSingletonPtr()->cloneBehaviour(behaviour);
                //                mTechnique->_addBehaviourTemplate(newBehaviour);
                //            }
                //                break;
                //        }
                //    }
                //}
            }
            else
            {
                errorUnexpectedProperty(compiler, prop);
            }
        }
        else if((*i)->type == ANT_OBJECT)
        {
            //ObjectAbstractNode* child = reinterpret_cast<ObjectAbstractNode*>((*i).get());
            //if (child->cls == token[TOKEN_CAMERA_DEPENDENCY])
            //{
            //    // Property: camera_dependency
            //    CameraDependency* cameraDependency = PU_NEW_T(CameraDependency, MEMCATEGORY_SCRIPTING)();
            //    child->context = Any(cameraDependency);
            //    CameraDependencyTranslator cameraDependencyTranslator;
            //    cameraDependencyTranslator.translate(compiler, *i);
            //    Real threshold = cameraDependency->getThreshold();
            //    bool increase = cameraDependency->isIncrease();
            //    if (child->name == token[TOKEN_TECH_DEFAULT_PARTICLE_WIDTH])
            //    {
            //        mTechnique->setWidthCameraDependency(threshold * threshold, increase);
            //    }
            //    else if (child->name == token[TOKEN_TECH_DEFAULT_PARTICLE_HEIGHT])
            //    {
            //        mTechnique->setHeightCameraDependency(threshold * threshold, increase);
            //    }
            //    else if (child->name == token[TOKEN_TECH_DEFAULT_PARTICLE_DEPTH])
            //    {
            //        mTechnique->setDepthCameraDependency(threshold * threshold, increase);
            //    }
            //    // Delete the camera dependency
            //    PU_DELETE_T(cameraDependency, CameraDependency, MEMCATEGORY_SCRIPTING);
            //}
            //else
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
