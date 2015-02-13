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

#include "CCPUParticle3DRendererTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DMaterialManager.h"

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
         PUParticle3DMaterial *material = PUParticle3DMaterialCache::Instance()->getMaterial(system->getMaterialName());
         std::string texFolder = "textures/";
         if (material){
             std::string::size_type pos = obj->file.find_last_of("/");
             //if (pos != std::string::npos)
             //    texFolder = obj->file.substr(0, pos + 1) + texFolder;
             if (pos != std::string::npos){
                 std::string temp = obj->file.substr(0, pos);
                 pos = temp.find_last_of("/");
                 if (pos != std::string::npos){
                     texFolder = temp.substr(0, pos + 1) + texFolder;
                 }
             }
         }
        if (type == "Billboard"){
            if (material)
                _renderer = PUParticle3DQuadRender::create(texFolder + material->textureFile);
            else
                _renderer = PUParticle3DQuadRender::create();
            for(PUAbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
            {
                if((*i)->type == ANT_PROPERTY)
                {
                    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>((*i));
                    if (prop->name == token[TOKEN_BILLBOARD_TYPE])
                    {
                        // Property: billboard_type
                        if (passValidateProperty(compiler, prop, token[TOKEN_BILLBOARD_TYPE], VAL_STRING))
                        {
                            std::string val;
                            if(getString(*prop->values.front(), &val))
                            {
                                if (val == token[TOKEN_POINT])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setType(PUParticle3DQuadRender::POINT);
                                }
                                else if (val == token[TOKEN_BILLBOARD_ORIENTED_SELF])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setType(PUParticle3DQuadRender::ORIENTED_SELF);
                                }
                                else if (val == token[TOKEN_BILLBOARD_ORIENTED_COMMON])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setType(PUParticle3DQuadRender::ORIENTED_COMMON);
                                }
                                else if (val == token[TOKEN_BILLBOARD_ORIENTED_SHAPE])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setType(PUParticle3DQuadRender::ORIENTED_SHAPE);
                                }
                                else if (val == token[TOKEN_BILLBOARD_PERPENDICULAR_COMMON])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setType(PUParticle3DQuadRender::PERPENDICULAR_COMMON);
                                }
                                else if (val == token[TOKEN_BILLBOARD_PERPENDICULAR_SELF])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setType(PUParticle3DQuadRender::PERPENDICULAR_SELF);
                                }
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_BILLBOARD_ORIGIN])
                    {
                        // Property: billboard_origin
                        if (passValidateProperty(compiler, prop, token[TOKEN_BILLBOARD_ORIGIN], VAL_STRING))
                        {
                            std::string val;
                            if(getString(*prop->values.front(), &val))
                            {
                                if (val == token[TOKEN_BILLBOARD_CENTER])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setOrigin(PUParticle3DQuadRender::CENTER);
                                }
                                else if (val == token[TOKEN_BILLBOARD_BOTTOM_CENTER])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setOrigin(PUParticle3DQuadRender::BOTTOM_CENTER);
                                }
                                else if (val == token[TOKEN_BILLBOARD_BOTTON_LEFT])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setOrigin(PUParticle3DQuadRender::BOTTOM_LEFT);
                                }
                                else if (val == token[TOKEN_BILLBOARD_BOTTOM_RIGHT])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setOrigin(PUParticle3DQuadRender::BOTTOM_RIGHT);
                                }
                                else if (val == token[TOKEN_BILLBOARD_CENTER_LEFT])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setOrigin(PUParticle3DQuadRender::CENTER_LEFT);
                                }
                                else if (val == token[TOKEN_BILLBOARD_CENTER_RIGHT])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setOrigin(PUParticle3DQuadRender::CENTER_RIGHT);
                                }
                                else if (val == token[TOKEN_BILLBOARD_TOP_CENTER])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setOrigin(PUParticle3DQuadRender::TOP_CENTER);
                                }
                                else if (val == token[TOKEN_BILLBOARD_TOP_LEFT])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setOrigin(PUParticle3DQuadRender::TOP_LEFT);
                                }
                                else if (val == token[TOKEN_BILLBOARD_TOP_RIGHT])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setOrigin(PUParticle3DQuadRender::TOP_RIGHT);
                                }
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_BILLBOARD_COMMON_DIRECTION])
                    {
                        // Property: common_direction
                        if (passValidateProperty(compiler, prop, token[TOKEN_BILLBOARD_COMMON_DIRECTION], VAL_VECTOR3))
                        {
                            Vec3 val;
                            if(getVector3(prop->values.begin(), prop->values.end(), &val))
                            {
                                static_cast<PUParticle3DQuadRender *>(_renderer)->setCommonDirection(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_BILLBOARD_COMMON_UP_VECTOR])
                    {
                        // Property: common_up_vector
                        if (passValidateProperty(compiler, prop, token[TOKEN_BILLBOARD_COMMON_UP_VECTOR], VAL_VECTOR3))
                        {
                            Vec3 val;
                            if(getVector3(prop->values.begin(), prop->values.end(), &val))
                            {
                                static_cast<PUParticle3DQuadRender *>(_renderer)->setCommonUp(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_RENDERER_TEXCOORDS_ROWS])
                    {
                        // Property: texture_coords_rows
                        if (passValidateProperty(compiler, prop, token[TOKEN_RENDERER_TEXCOORDS_ROWS], VAL_UINT))
                        {
                            unsigned int val = 0;
                            if(getUInt(*prop->values.front(), &val))
                            {
                                static_cast<PUParticle3DQuadRender *>(_renderer)->setTextureCoordsRows(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_RENDERER_TEXCOORDS_COLUMNS])
                    {
                        // Property: texture_coords_columns
                        if (passValidateProperty(compiler, prop, token[TOKEN_RENDERER_TEXCOORDS_COLUMNS], VAL_UINT))
                        {
                            unsigned int val = 0;
                            if(getUInt(*prop->values.front(), &val))
                            {
                                static_cast<PUParticle3DQuadRender *>(_renderer)->setTextureCoordsColumns(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_BILLBOARD_ROTATION_TYPE])
                    {
                        // Property: billboard_rotation_type
                        if (passValidateProperty(compiler, prop, token[TOKEN_BILLBOARD_ROTATION_TYPE], VAL_STRING))
                        {
                            std::string val;
                            if(getString(*prop->values.front(), &val))
                            {
                                if (val == token[TOKEN_VERTEX])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setRotateType(PUParticle3DQuadRender::VERTEX);
                                }
                                else if (val == token[TOKEN_BILLBOARD_TEXCOORD])
                                {
                                    static_cast<PUParticle3DQuadRender *>(_renderer)->setRotateType(PUParticle3DQuadRender::TEXTURE_COORDS);
                                }
                            }
                        }
                    }
                }
            }
        }

        if (type == "Entity"){
            for(PUAbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
            {
                if((*i)->type == ANT_PROPERTY)
                {
                    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>((*i));
                    if (prop->name == token[TOKEN_MESH_NAME])
                    {
                        // Property: mesh_name
                        if (passValidateProperty(compiler, prop, token[TOKEN_MESH_NAME], VAL_STRING))
                        {
                            std::string val;
                            if(getString(*prop->values.front(), &val))
                            {
                                if (material) 
                                    _renderer = PUParticle3DModelRender::create(val, texFolder + material->textureFile);
                                else
                                    _renderer = PUParticle3DModelRender::create(val);
                            }
                        }
                    }
                }
            }
        }

        if (_renderer){
            if (material){
                _renderer->setDepthTest(material->depthTest);
                _renderer->setDepthWrite(material->depthWrite);
            }
            system->setRender(_renderer);
        }
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
    //        //else if (particleRendererFactory->translateChildProperty(compiler, *i))
    //        //{
    //        //    // Parsed the property by another translator; do nothing
    //        //}
    //        else
    //        {
    //            errorUnexpectedProperty(compiler, prop);
    //        }
    //    }
    //    else if((*i)->type == ANT_OBJECT)
    //    {
    //        //ObjectAbstractNode* child = reinterpret_cast<ObjectAbstractNode*>((*i).get());
    //        //if (child->cls == token[TOKEN_RENDERER_TEXCOORDS_SET])
    //        //{
    //        //    // Property: soft_particles_delta
    //        //    RendererSetTranslator rendererSetTranslator;
    //        //    rendererSetTranslator.translate(compiler, *i);
    //        //}
    //        //else if (particleRendererFactory->translateChildObject(compiler, *i))
    //        //{
    //        //    // Parsed the object by another translator; do nothing
    //        //}
    //        //else
    //        //{
    //        //    processNode(compiler, *i);
    //        //}
    //    }
    //    else
    //    {
    //        errorUnexpectedToken(compiler, *i);
    //    }
    //}
}



NS_CC_END
