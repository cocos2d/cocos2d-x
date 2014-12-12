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

#include "CCPUParticle3DRendererTranslator.h"
#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"
#include "3dparticle/ParticleUniverse/CCPUParticle3DMaterialManager.h"

NS_CC_BEGIN
PUParticle3DRendererTranslator::PUParticle3DRendererTranslator()
{
    
}

PUParticle3DRendererTranslator::~PUParticle3DRendererTranslator()
{
    
}

void PUParticle3DRendererTranslator::translate(PUScriptCompiler* compiler, PUAbstractNode *node)
{
    PUObjectAbstractNode* obj = reinterpret_cast<PUObjectAbstractNode*>(node);
    PUObjectAbstractNode* parent = obj->parent ? reinterpret_cast<PUObjectAbstractNode*>(obj->parent) : 0;
    
    // The name of the obj is the type of the Renderer
    // Remark: This can be solved by using a listener, so that obj->values is filled with type + name. Something for later
    std::string type;
    if(!obj->name.empty())
    {
        type = obj->name;
    }
    
    //// Get the factory
    //ParticleRendererFactory* particleRendererFactory = ParticleSystemManager::getSingletonPtr()->getRendererFactory(type);
    //if (!particleRendererFactory)
    //{
    //    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
    //    return;
    //}
    //
    //// Create the Renderer
    //mRenderer = ParticleSystemManager::getSingletonPtr()->createRenderer(type);
    //if (!mRenderer)
    //{
    //    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
    //    return;
    //}
    
    if (parent && parent->context)
    {
		 PUParticleSystem3D* system = static_cast<PUParticleSystem3D*>(parent->context);

		if (type == "Billboard"){
			PUParticle3DMaterial *material = PUParticle3DMaterialManager::Instance()->getMaterial(system->getMaterialName());
			std::string texFile;
			if (material){
				texFile = material->textureFile;
			}
			_renderer = Particle3DQuadRender::create(texFile);
		}

        system->setRender(_renderer);
    }
    
    // Set it in the context
    obj->context = _renderer;
    
    //// Run through properties
    //for(PUAbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
    //{
    //    // No properties of its own
    //    if((*i)->type == ANT_PROPERTY)
    //    {
    //        PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>((*i));
    //        if (prop->name == token[TOKEN_RENDERER_Q_GROUP])
    //        {
    //            //// Property: render_queue_group
    //            //if (passValidateProperty(compiler, prop, token[TOKEN_RENDERER_Q_GROUP], VAL_UINT))
    //            //{
    //            //    uint val = 0;
    //            //    if(getUInt(prop->values.front(), &val))
    //            //    {
    //            //        mRenderer->setRenderQueueGroup(val);
    //            //    }
    //            //}
    //        }
    //        else if (prop->name == token[TOKEN_RENDERER_SORTING])
    //        {
    //            //// Property: sorting
    //            //if (passValidateProperty(compiler, prop, token[TOKEN_RENDERER_SORTING], VAL_BOOL))
    //            //{
    //            //    bool val = 0;
    //            //    if(getBoolean(prop->values.front(), &val))
    //            //    {
    //            //        mRenderer->setSorted(val);
    //            //    }
    //            //}
    //        }
    //        else if (prop->name == token[TOKEN_RENDERER_TEXCOORDS_ROWS])
    //        {
    //            //// Property: texture_coords_rows
    //            //if (passValidateProperty(compiler, prop, token[TOKEN_RENDERER_TEXCOORDS_ROWS], VAL_UINT))
    //            //{
    //            //    uint val = 0;
    //            //    if(getUInt(prop->values.front(), &val))
    //            //    {
    //            //        mRenderer->setTextureCoordsRows(val);
    //            //    }
    //            //}
    //        }
    //        else if (prop->name == token[TOKEN_RENDERER_TEXCOORDS_COLUMNS])
    //        {
    //            //// Property: texture_coords_columns
    //            //if (passValidateProperty(compiler, prop, token[TOKEN_RENDERER_TEXCOORDS_COLUMNS], VAL_UINT))
    //            //{
    //            //    uint val = 0;
    //            //    if(getUInt(prop->values.front(), &val))
    //            //    {
    //            //        mRenderer->setTextureCoordsColumns(val);
    //            //    }
    //            //}
    //        }
    //        else if (prop->name == token[TOKEN_RENDERER_USE_SOFT_PARTICLES])
    //        {
    //            //// Property: use_soft_particles
    //            //if (passValidateProperty(compiler, prop, token[TOKEN_RENDERER_USE_SOFT_PARTICLES], VAL_BOOL))
    //            //{
    //            //    bool val = 0;
    //            //    if(getBoolean(prop->values.front(), &val))
    //            //    {
    //            //        mRenderer->setUseSoftParticles(val);
    //            //    }
    //            //}
    //        }
    //        else if (prop->name == token[TOKEN_RENDERER_SOFT_PARTICLES_CONTRAST_POWER])
    //        {
    //            //// Property: soft_particles_contrast_power
    //            //if (passValidateProperty(compiler, prop, token[TOKEN_RENDERER_SOFT_PARTICLES_CONTRAST_POWER], VAL_REAL))
    //            //{
    //            //    Real val = 0;
    //            //    if(getReal(prop->values.front(), &val))
    //            //    {
    //            //        mRenderer->setSoftParticlesContrastPower(val);
    //            //    }
    //            //}
    //        }
    //        else if (prop->name == token[TOKEN_RENDERER_SOFT_PARTICLES_SCALE])
    //        {
    //            //// Property: soft_particles_scale
    //            //if (passValidateProperty(compiler, prop, token[TOKEN_RENDERER_SOFT_PARTICLES_SCALE], VAL_REAL))
    //            //{
    //            //    Real val = 0;
    //            //    if(getReal(prop->values.front(), &val))
    //            //    {
    //            //        mRenderer->setSoftParticlesScale(val);
    //            //    }
    //            //}
    //        }
    //        else if (prop->name == token[TOKEN_RENDERER_SOFT_PARTICLES_DELTA])
    //        {
    //            //// Property: soft_particles_delta
    //            //if (passValidateProperty(compiler, prop, token[TOKEN_RENDERER_SOFT_PARTICLES_DELTA], VAL_REAL))
    //            //{
    //            //    Real val = 0;
    //            //    if(getReal(prop->values.front(), &val))
    //            //    {
    //            //        mRenderer->setSoftParticlesDelta(val);
    //            //    }
    //            //}
    //        }
    //        else if (particleRendererFactory->translateChildProperty(compiler, *i))
    //        {
    //            // Parsed the property by another translator; do nothing
    //        }
    //        else
    //        {
    //            errorUnexpectedProperty(compiler, prop);
    //        }
    //    }
    //    else if((*i)->type == ANT_OBJECT)
    //    {
    //        ObjectAbstractNode* child = reinterpret_cast<ObjectAbstractNode*>((*i).get());
    //        if (child->cls == token[TOKEN_RENDERER_TEXCOORDS_SET])
    //        {
    //            // Property: soft_particles_delta
    //            RendererSetTranslator rendererSetTranslator;
    //            rendererSetTranslator.translate(compiler, *i);
    //        }
    //        else if (particleRendererFactory->translateChildObject(compiler, *i))
    //        {
    //            // Parsed the object by another translator; do nothing
    //        }
    //        else
    //        {
    //            processNode(compiler, *i);
    //        }
    //    }
    //    else
    //    {
    //        errorUnexpectedToken(compiler, *i);
    //    }
    //}
}



NS_CC_END
