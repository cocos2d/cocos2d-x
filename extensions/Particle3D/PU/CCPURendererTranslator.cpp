/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "CCPURendererTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUMaterialManager.h"

NS_CC_BEGIN
PURendererTranslator::PURendererTranslator()
{
    
}

PURendererTranslator::~PURendererTranslator()
{
    
}

void PURendererTranslator::translate(PUScriptCompiler* compiler, PUAbstractNode *node)
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
         PUMaterial *material = PUMaterialCache::Instance()->getMaterial(system->getMaterialName());
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
        else if (type == "Entity"){
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
                                std::string::size_type pos = val.find_last_of(".");
                                val = val.substr(0, pos + 1) + std::string("c3b");
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
        else if (type == "Box"){
            if (material) 
                _renderer = PUParticle3DBoxRender::create(texFolder + material->textureFile);
            else
                _renderer = PUParticle3DBoxRender::create();
        }
        else if (type == "Sphere"){
            if (material) 
                _renderer = PUSphereRender::create(texFolder + material->textureFile);
            else
                _renderer = PUSphereRender::create();
        }
        else if (type == "Beam"){
            if (material) 
                _renderer = PUBeamRender::create(texFolder + material->textureFile);
            else
                _renderer = PUBeamRender::create();

            for(PUAbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
            {
                if((*i)->type == ANT_PROPERTY)
                {
                    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>((*i));

                    if (prop->name == token[TOKEN_UPDATE_INTERVAL])
                    {
                        // Property: update_interval
                        if (passValidateProperty(compiler, prop, token[TOKEN_UPDATE_INTERVAL], VAL_REAL))
                        {
                            float val = 0.0f;
                            if(getFloat(*prop->values.front(), &val))
                            {
                                static_cast<PUBeamRender *>(_renderer)->setUpdateInterval(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_BEAMRENDERER_UPDATE_INTERVAL])
                    {
                        // Property: beam_update_interval (deprecated and replaced by 'update_interval')
                        if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_UPDATE_INTERVAL], VAL_REAL))
                        {
                            float val = 0.0f;
                            if(getFloat(*prop->values.front(), &val))
                            {
                                static_cast<PUBeamRender *>(_renderer)->setUpdateInterval(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_BEAMRENDERER_DEVIATION])
                    {
                        // Property: beam_deviation
                        if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_DEVIATION], VAL_REAL))
                        {
                            float val = 0.0f;
                            if(getFloat(*prop->values.front(), &val))
                            {
                                static_cast<PUBeamRender *>(_renderer)->setDeviation(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_NUMBER_OF_SEGMENTS])
                    {
                        // Property: number_of_segments
                        if (passValidateProperty(compiler, prop, token[TOKEN_NUMBER_OF_SEGMENTS], VAL_UINT))
                        {
                            unsigned int val = 0;
                            if(getUInt(*prop->values.front(), &val))
                            {
                                static_cast<PUBeamRender *>(_renderer)->setNumberOfSegments(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_BEAMRENDERER_NUMBER_OF_SEGMENTS])
                    {
                        // Property: beam_number_segments (deprecated and replaced by 'number_of_segments')
                        if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_NUMBER_OF_SEGMENTS], VAL_UINT))
                        {
                            unsigned int val = 0;
                            if(getUInt(*prop->values.front(), &val))
                            {
                                static_cast<PUBeamRender *>(_renderer)->setNumberOfSegments(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_BEAMRENDERER_JUMP])
                    {
                        // Property: beam_jump_segments
                        if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_JUMP], VAL_BOOL))
                        {
                            bool val;
                            if(getBoolean(*prop->values.front(), &val))
                            {
                                static_cast<PUBeamRender *>(_renderer)->setJump(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_BEAMRENDERER_TEXCOORD_DIRECTION])
                    {
                        // Property: beam_texcoord_direction
                        if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_TEXCOORD_DIRECTION], VAL_STRING))
                        {
                            std::string val;
                            if(getString(*prop->values.front(), &val))
                            {
                                if (val == token[TOKEN_BEAMRENDERER_TCD_U])
                                {
                                    static_cast<PUBeamRender *>(_renderer)->setTexCoordDirection(PUBillboardChain::TCD_U);
                                }
                                else if (val == token[TOKEN_BEAMRENDERER_TCD_V])
                                {
                                    static_cast<PUBeamRender *>(_renderer)->setTexCoordDirection(PUBillboardChain::TCD_V);
                                }
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_USE_VERTEX_COLOURS])
                    {
                        // Property: use_vertex_colours
                        if (passValidateProperty(compiler, prop, token[TOKEN_USE_VERTEX_COLOURS], VAL_BOOL))
                        {
                            bool val;
                            if(getBoolean(*prop->values.front(), &val))
                            {
                                static_cast<PUBeamRender *>(_renderer)->setUseVertexColours(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_BEAMRENDERER_VERTEX_COLOURS])
                    {
                        // Property: beam_vertex_colours (deprecated and replaced by 'use_vertex_colours')
                        if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_VERTEX_COLOURS], VAL_BOOL))
                        {
                            bool val;
                            if(getBoolean(*prop->values.front(), &val))
                            {
                                static_cast<PUBeamRender *>(_renderer)->setUseVertexColours(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_MAX_ELEMENTS])
                    {
                        // Property: max_elements
                        if (passValidateProperty(compiler, prop, token[TOKEN_MAX_ELEMENTS], VAL_UINT))
                        {
                            unsigned int val = 0;
                            if(getUInt(*prop->values.front(), &val))
                            {
                                static_cast<PUBeamRender *>(_renderer)->setMaxChainElements(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_BEAMRENDERER_MAX_ELEMENTS])
                    {
                        // Property: beam_max_elements (deprecated and replaced by 'max_elements')
                        if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_MAX_ELEMENTS], VAL_UINT))
                        {
                            unsigned int val = 0;
                            if(getUInt(*prop->values.front(), &val))
                            {
                                static_cast<PUBeamRender *>(_renderer)->setMaxChainElements(val);
                            }
                        }
                    }
                }
            }
        }
        else if (type == "RibbonTrail"){
            if (material) 
                _renderer = PURibbonTrailRender::create(texFolder + material->textureFile);
            else
                _renderer = PURibbonTrailRender::create();

            for(PUAbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
            {
                if((*i)->type == ANT_PROPERTY)
                {
                    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>((*i));

                    if (prop->name == token[TOKEN_USE_VERTEX_COLOURS])
                    {
                        // Property: use_vertex_colours
                        if (passValidateProperty(compiler, prop, token[TOKEN_USE_VERTEX_COLOURS], VAL_BOOL))
                        {
                            bool val;
                            if(getBoolean(*prop->values.front(), &val))
                            {
                                static_cast<PURibbonTrailRender *>(_renderer)->setUseVertexColors(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_RIBBONTRAIL_VERTEX_COLOURS])
                    {
                        // Property: ribbontrail_vertex_colours (deprecated and replaced by 'use_vertex_colours')
                        if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_VERTEX_COLOURS], VAL_BOOL))
                        {
                            bool val;
                            if(getBoolean(*prop->values.front(), &val))
                            {
                                static_cast<PURibbonTrailRender *>(_renderer)->setUseVertexColors(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_MAX_ELEMENTS])
                    {
                        // Property: max_elements
                        if (passValidateProperty(compiler, prop, token[TOKEN_MAX_ELEMENTS], VAL_UINT))
                        {
                            unsigned int val = 0;
                            if(getUInt(*prop->values.front(), &val))
                            {
                                static_cast<PURibbonTrailRender *>(_renderer)->setMaxChainElements(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_RIBBONTRAIL_MAX_ELEMENTS])
                    {
                        // Property: ribbontrail_max_elements (deprecated and replaced by 'max_elements')
                        if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_MAX_ELEMENTS], VAL_UINT))
                        {
                            unsigned int val = 0;
                            if(getUInt(*prop->values.front(), &val))
                            {
                                static_cast<PURibbonTrailRender *>(_renderer)->setMaxChainElements(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_RIBBONTRAIL_LENGTH])
                    {
                        // Property: ribbontrail_length
                        if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_MAX_ELEMENTS], VAL_REAL))
                        {
                            float val = 0;
                            if(getFloat(*prop->values.front(), &val))
                            {
                                static_cast<PURibbonTrailRender *>(_renderer)->setTrailLength(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_RIBBONTRAIL_WIDTH])
                    {
                        // Property: ribbontrail_width
                        if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_WIDTH], VAL_REAL))
                        {
                            float val = 0;
                            if(getFloat(*prop->values.front(), &val))
                            {
                                static_cast<PURibbonTrailRender *>(_renderer)->setTrailWidth(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_RANDOM_INITIAL_COLOUR])
                    {
                        // Property: random_initial_colour
                        if (passValidateProperty(compiler, prop, token[TOKEN_RANDOM_INITIAL_COLOUR], VAL_BOOL))
                        {
                            bool val;
                            if(getBoolean(*prop->values.front(), &val))
                            {
                                static_cast<PURibbonTrailRender *>(_renderer)->setRandomInitialColor(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_RIBBONTRAIL_RANDOM_INITIAL_COLOUR])
                    {
                        // Property: ribbontrail_random_initial_colour (deprecated and replaced by 'random_initial_colour'))
                        if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_RANDOM_INITIAL_COLOUR], VAL_BOOL))
                        {
                            bool val;
                            if(getBoolean(*prop->values.front(), &val))
                            {
                                static_cast<PURibbonTrailRender *>(_renderer)->setRandomInitialColor(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_INITIAL_COLOUR])
                    {
                        // Property: initial_colour
                        if (passValidateProperty(compiler, prop, token[TOKEN_INITIAL_COLOUR], VAL_COLOURVALUE))
                        {
                            Vec4 val;
                            if(getVector4(prop->values.begin(), prop->values.end(), &val))
                            {
                                static_cast<PURibbonTrailRender *>(_renderer)->setInitialColor(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_RIBBONTRAIL_INITIAL_COLOUR])
                    {
                        // Property: ribbontrail_initial_colour (deprecated and replaced by 'initial_colour')
                        if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_INITIAL_COLOUR], VAL_COLOURVALUE))
                        {
                            Vec4 val;
                            if(getVector4(prop->values.begin(), prop->values.end(), &val))
                            {
                                static_cast<PURibbonTrailRender *>(_renderer)->setInitialColor(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_COLOUR_CHANGE])
                    {
                        // Property: colour_change
                        if (passValidateProperty(compiler, prop, token[TOKEN_COLOUR_CHANGE], VAL_COLOURVALUE))
                        {
                            Vec4 val;
                            if(getVector4(prop->values.begin(), prop->values.end(), &val))
                            {
                                static_cast<PURibbonTrailRender *>(_renderer)->setColorChange(val);
                            }
                        }
                    }
                    else if (prop->name == token[TOKEN_RIBBONTRAIL_COLOUR_CHANGE])
                    {
                        // Property: ribbontrail_colour_change (deprecated and replaced by 'colour_change')
                        if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_COLOUR_CHANGE], VAL_COLOURVALUE))
                        {
                            Vec4 val;
                            if(getVector4(prop->values.begin(), prop->values.end(), &val))
                            {
                                static_cast<PURibbonTrailRender *>(_renderer)->setColorChange(val);
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
                _renderer->setBlendFunc(material->blendFunc);
                static_cast<PURender *>(_renderer)->setRenderType(type);
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
