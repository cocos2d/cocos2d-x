/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "CCPUParticleSystem3DTranslator.h"

NS_CC_BEGIN

PUParticleSystem3DTranslator::PUParticleSystem3DTranslator()
{
    
}
PUParticleSystem3DTranslator::~PUParticleSystem3DTranslator()
{
    
}

void PUParticleSystem3DTranslator::translate(PUScriptCompiler* compiler, PUAbstractNode *node)
{
    if (typeid(*node) != typeid(PUObjectAbstractNode))
        return;

        PUObjectAbstractNode* obj = reinterpret_cast<PUObjectAbstractNode*>(node);
        if(obj->name.empty())
        {
            return;
        }
        
        //// Create a particle system with the given name
        //_system = PUParticleSystem3D::create();
        //PUParticleSystem3DBuilder::Instance()->PUParticleSystem3DList.push_back(_system);
        //if (!mSystem)
        //{
        //	return;
        //}
        obj->context = _system;
        _system->setName(obj->name);
        for(PUAbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
        {
            if((*i)->type == ANT_PROPERTY)
            {
                PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>((*i));
            //	if (prop->name == token[TOKEN_PS_ITERATION_INTERVAL])
            //	{
            //		// Property: iteration_interval
            //		if (passValidateProperty(compiler, prop, token[TOKEN_PS_ITERATION_INTERVAL], VAL_REAL))
            //		{
            //			Real val = 0.0f;
            //			if(getReal(prop->values.front(), &val))
            //			{
            //				mSystem->setIterationInterval(val);
            //			}
            //		}
            //	}
            //	else if (prop->name == token[TOKEN_PS_NONVIS_UPDATE_TIMEOUT])
            //	{
            //		// Property: nonvisible_update_timeout
            //		if (passValidateProperty(compiler, prop, token[TOKEN_PS_NONVIS_UPDATE_TIMEOUT], VAL_REAL))
            //		{
            //			Real val = 0.0f;
            //			if(getReal(prop->values.front(), &val))
            //			{
            //				mSystem->setNonVisibleUpdateTimeout(val);
            //			}
            //		}
            //	}
            //	else if (prop->name == token[TOKEN_PS_FIXED_TIMEOUT])
            //	{
            //		// Property: fixed_timeout
            //		if (passValidateProperty(compiler, prop, token[TOKEN_PS_FIXED_TIMEOUT], VAL_REAL))
            //		{
            //			Real val = 0.0f;
            //			if(getReal(prop->values.front(), &val))
            //			{
            //				mSystem->setFixedTimeout(val);
            //			}
            //		}
            //	}
            //	else if (prop->name == token[TOKEN_PS_LOD_DISTANCES])
            //	{
            //		// Property: lod_distances
            //		if (passValidatePropertyNoValues(compiler, prop, token[TOKEN_PS_LOD_DISTANCES]))
            //		{
            //			for(PUAbstractNodeList::iterator j = prop->values.begin(); j != prop->values.end(); ++j)
            //			{
            //				Real val = 0.0f;
            //				if(getReal(*j, &val))
            //				{
            //					mSystem->addLodDistance(val);
            //				}
            //				else
            //				{
            //					compiler->addError(PUScriptCompiler::CE_NUMBEREXPECTED, prop->file, prop->line,
   //                                                "PU Compiler: lod_distances expects only numbers as arguments");
            //				}
            //			}
            //		}
            //	}
            //	else if (prop->name == token[TOKEN_PS_MAIN_CAMERA_NAME])
            //	{
            //		// Property: main_camera_name
            //		if (passValidateProperty(compiler, prop, token[TOKEN_PS_MAIN_CAMERA_NAME], VAL_STRING))
            //		{
            //			String val;
            //			if(getString(prop->values.front(), &val))
            //			{
            //				mSystem->setMainCameraName(val);
            //			}
            //		}
            //	}
            //	else if (prop->name == token[TOKEN_PS_SMOOTH_LOD])
            //	{
            //		// Property: smooth_lod
            //		if (passValidateProperty(compiler, prop, token[TOKEN_PS_SMOOTH_LOD], VAL_BOOL))
            //		{
            //			bool val;
            //			if(getBoolean(prop->values.front(), &val))
            //			{
            //				mSystem->setSmoothLod(val);
            //			}
            //		}
            //	}
            //	else if (prop->name == token[TOKEN_PS_FAST_FORWARD])
            //	{
            //		// Property: fast_forward
            //		if (passValidateProperty(compiler, prop, token[TOKEN_PS_SCALE], VAL_VECTOR2))
            //		{
            //			Vector2 val;
            //			if(getVector2(prop->values.begin(), prop->values.end(), &val))
            //			{
            //				mSystem->setFastForward(val.x, val.y);
            //			}
            //		}
            //	}
                if (prop->name == token[TOKEN_PS_SCALE])
                {
                    // Property: scale
                    if (passValidateProperty(compiler, prop, token[TOKEN_PS_SCALE], VAL_VECTOR3))
                    {
                        Vec3 val;
                        if(getVector3(prop->values.begin(), prop->values.end(), &val))
                        {
                            _system->setScaleX(val.x);
                            _system->setScaleY(val.y);
                            _system->setScaleZ(val.z);
                        }
                    }
                }
                else if (prop->name == token[TOKEN_PS_SCALE_VELOCITY])
                {
                    // Property: scale_velocity
                    if (passValidateProperty(compiler, prop, token[TOKEN_PS_ITERATION_INTERVAL], VAL_REAL))
                    {
                        float val = 0.0f;
                        if(getFloat(*prop->values.front(), &val))
                        {
                            _system->setParticleSystemScaleVelocity(val);
                        }
                    }
                }
            //	else if (prop->name == token[TOKEN_PS_SCALE_TIME])
            //	{
            //		// Property: scale_time
            //		if (passValidateProperty(compiler, prop, token[TOKEN_PS_SCALE_TIME], VAL_REAL))
            //		{
            //			Real val = 0.0f;
            //			if(getReal(prop->values.front(), &val))
            //			{
            //				mSystem->setScaleTime(val);
            //			}
            //		}
            //	}
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
            //	else if (prop->name == token[TOKEN_PS_TIGHT_BOUNDING_BOX])
            //	{
            //		// Property: tight_bounding_box
            //		if (passValidateProperty(compiler, prop, token[TOKEN_PS_TIGHT_BOUNDING_BOX], VAL_BOOL))
            //		{
            //			bool val;
            //			if(getBoolean(prop->values.front(), &val))
            //			{
            //				mSystem->setTightBoundingBox(val);
            //			}
            //		}
            //	}
            //	else if (prop->name == token[TOKEN_PS_CATEGORY])
            //	{
            //		// Property: category
            //		if (passValidateProperty(compiler, prop, token[TOKEN_PS_CATEGORY], VAL_STRING))
            //		{
            //			String val;
            //			if(getString(prop->values.front(), &val))
            //			{
            //				mSystem->setCategory(val);
            //			}
            //		}
            //	}
            //	else if (prop->name == token[TOKEN_USE_ALIAS])
            //	{
            //		// Property: use_alias
            //		// The alias can only be a technique
            //		if (passValidateProperty(compiler, prop, token[TOKEN_USE_ALIAS], VAL_STRING))
            //		{
            //			String val;
            //			if(getString(prop->values.front(), &val))
            //			{
            //				IAlias* alias = ParticleSystemManager::getSingletonPtr()->getAlias(val);
            //				if (alias->getAliasType() == IAlias::AT_TECHNIQUE)
            //				{
            //					ParticleTechnique* technique = static_cast<ParticleTechnique*>(alias);
            //					ParticleTechnique* newTechnique = ParticleSystemManager::getSingletonPtr()->cloneTechnique(technique);
            //					mSystem->addTechnique(newTechnique);
            //				}
            //			}
            //		}
            //	}
            //	else
            //	{
            //		errorUnexpectedProperty(compiler, prop);
            //	}
            }
            else if((*i)->type == ANT_OBJECT)
            {
                processNode(compiler, *i);
            }
            else
            {
                errorUnexpectedToken(compiler, *i);
            }
        }
}



NS_CC_END