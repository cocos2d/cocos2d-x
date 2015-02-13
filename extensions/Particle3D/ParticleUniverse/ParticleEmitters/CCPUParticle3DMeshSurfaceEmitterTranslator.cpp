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

#include "CCPUParticle3DMeshSurfaceEmitterTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUParticle3DMeshSurfaceEmitterTranslator::PUParticle3DMeshSurfaceEmitterTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DMeshSurfaceEmitterTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DEmitter* em = static_cast<PUParticle3DEmitter*>(prop->parent->context);
    PUParticle3DMeshSurfaceEmitter* emitter = static_cast<PUParticle3DMeshSurfaceEmitter*>(em);

    if (prop->name == token[TOKEN_MESH_NAME])
    {
        // Property: mesh_name
        if (passValidateProperty(compiler, prop, token[TOKEN_MESH_NAME], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                emitter->setMeshName(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_MESH_SURFACE_NAME])
    {
        // Property: mesh_surface_mesh_name (deprecated and replaced by mesh_name)
        if (passValidateProperty(compiler, prop, token[TOKEN_MESH_SURFACE_NAME], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                emitter->setMeshName(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_MESH_SURFACE_DISTRIBUTION])
    {
        // Property: mesh_surface_distribution
        if (passValidateProperty(compiler, prop, token[TOKEN_MESH_SURFACE_DISTRIBUTION], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                if (val == token[TOKEN_MESH_SURFACE_EDGE])
                {
                    emitter->setDistribution(MeshInfo::MSD_EDGE);
                    return true;
                }
                else if (val == token[TOKEN_MESH_SURFACE_HETEROGENEOUS_1])
                {
                    emitter->setDistribution(MeshInfo::MSD_HETEROGENEOUS_1);
                    return true;
                }
                else if (val == token[TOKEN_MESH_SURFACE_HETEROGENEOUS_2])
                {
                    emitter->setDistribution(MeshInfo::MSD_HETEROGENEOUS_2);
                    return true;
                }
                else if (val == token[TOKEN_MESH_SURFACE_HOMOGENEOUS])
                {
                    emitter->setDistribution(MeshInfo::MSD_HOMOGENEOUS);
                    return true;
                }
                else if (val == token[TOKEN_MESH_SURFACE_HOMOGENEOUS])
                {
                    emitter->setDistribution(MeshInfo::MSD_HOMOGENEOUS);
                    return true;
                }
            }
        }
    }
    else if (prop->name == token[TOKEN_MESH_SURFACE_MESH_SCALE])
    {
        // Property: mesh_surface_scale
        if (passValidateProperty(compiler, prop, token[TOKEN_MESH_SURFACE_MESH_SCALE], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                emitter->setScale(val);
                return true;
            }
        }
    }

    return false;
}

bool PUParticle3DMeshSurfaceEmitterTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END