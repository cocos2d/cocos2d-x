/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2014 GamePlay3D team

 http://www.cocos2d-x.org


 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Ideas taken from:
 - GamePlay3D: http://gameplay3d.org/
 - OGRE3D: http://www.ogre3d.org/
 - Qt3D: http://qt-project.org/

 ****************************************************************************/

#include "renderer/CCRenderState.h"

#include <string>
#include <cassert>

#include "renderer/CCTexture2D.h"
#include "renderer/CCPass.h"
#include "base/ccUtils.h"
#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCMaterial.h"

NS_CC_BEGIN


std::string RenderState::getName() const
{
    return _name;
}


void RenderState::bindPass(Pass* pass, MeshCommand* command)
{
    CC_ASSERT(pass);
    assert(pass->_technique && pass->_technique->_material);
    auto *technique = pass->_technique;
    auto *material = technique->_material;
    auto &pipelineDescriptor = command->getPipelineDescriptor();

    //need reset all state
    //pipelineDescriptor.blendDescriptor.blendEnabled = true;

    // Get the combined modified state bits for our RenderState hierarchy.
    long overrideBits = _state._modifiedBits;
    overrideBits |= technique->getStateBlock()._modifiedBits;
    overrideBits |= material->getStateBlock()._modifiedBits;

    // Restore renderer state to its default, except for explicitly specified states
    RenderState::StateBlock::restoreUnmodifiedStates(overrideBits, &pipelineDescriptor);

    material->getStateBlock().apply(&pipelineDescriptor);
    technique->getStateBlock().apply(&pipelineDescriptor);
    _state.apply(&pipelineDescriptor);

}


RenderState::StateBlock& RenderState::getStateBlock() const
{
    return _state;
}


void RenderState::StateBlock::bind(PipelineDescriptor *pipelineDescriptor)
{
    // When the public bind() is called with no RenderState object passed in,
    // we assume we are being called to bind the state of a single StateBlock,
    // irrespective of whether it belongs to a hierarchy of RenderStates.
    // Therefore, we call restore() here with only this StateBlock's override
    // bits to restore state before applying the new state.
    StateBlock::restoreUnmodifiedStates(_modifiedBits, pipelineDescriptor);

    apply(pipelineDescriptor);
}

void RenderState::StateBlock::apply(PipelineDescriptor *pipelineDescriptor)
{
    //CC_ASSERT(_globalState);

    auto renderer = Director::getInstance()->getRenderer();
    auto &blend = pipelineDescriptor->blendDescriptor;

    // Update any state that differs from _globalState and flip _globalState bits
    if ((_modifiedBits & RS_BLEND))
    {
        blend.blendEnabled = _blendEnabled;
    }

    if ((_modifiedBits & RS_BLEND_FUNC))
    {
        blend.sourceAlphaBlendFactor = blend.sourceRGBBlendFactor = _blendSrc;
        blend.destinationAlphaBlendFactor = blend.destinationRGBBlendFactor = _blendDst;
    }

    if ((_modifiedBits & RS_CULL_FACE))
    {
        if (!_cullFaceEnabled)
             renderer->setCullMode(CullMode::NONE);
    }

    if ((_modifiedBits & RS_CULL_FACE_SIDE))
    {
        renderer->setCullMode(_cullFaceSide);
    }

    if ((_modifiedBits & RS_FRONT_FACE))
    {
        renderer->setWinding(_frontFace);
    }
    if ((_modifiedBits & RS_DEPTH_TEST))
    {
        renderer->setDepthTest(_depthTestEnabled);
    }

    if ((_modifiedBits & RS_DEPTH_WRITE))
    {
        renderer->setDepthWrite(_depthWriteEnabled);
    }

    if ((_modifiedBits & RS_DEPTH_FUNC))
    {
        renderer->setDepthCompareFunction(_depthFunction);
    }
}

void RenderState::StateBlock::restoreUnmodifiedStates(long overrideBits, PipelineDescriptor *programState)
{
    auto renderer = Director::getInstance()->getRenderer();
    auto &blend = programState->blendDescriptor;

    // Update any state that differs from _globalState and flip _globalState bits
    if (!(overrideBits & RS_BLEND))
    {
        blend.blendEnabled = true;
    }

    if (!(overrideBits & RS_BLEND_FUNC))
    {
        blend.sourceAlphaBlendFactor = blend.sourceRGBBlendFactor = backend::BlendFactor::ONE;
        blend.destinationAlphaBlendFactor = blend.destinationRGBBlendFactor = backend::BlendFactor::ZERO;
    }

    if (!(overrideBits & RS_CULL_FACE))
    {
        renderer->setCullMode(CullMode::NONE);
    }

    if (!(overrideBits & RS_CULL_FACE_SIDE))
    {
        renderer->setCullMode(CullMode::BACK);
    }

    if (!(overrideBits & RS_FRONT_FACE))
    {
        renderer->setWinding(FrontFace::COUNTER_CLOCK_WISE);
    }

    if (!(overrideBits & RS_DEPTH_TEST))
    {
        renderer->setDepthTest(true);
    }

    if (!(overrideBits & RS_DEPTH_WRITE))
    {
        renderer->setDepthWrite(false);
    }


    if (!(overrideBits & RS_DEPTH_FUNC))
    {
        renderer->setDepthCompareFunction(DepthFunction::LESS);
    }
}

static bool parseBoolean(const std::string& value)
{
    return (value.compare("true") == 0);
}

static backend::BlendFactor parseBlend(const std::string& value)
{
    // Convert the string to uppercase for comparison.
    std::string upper(value);
    std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
    if (upper == "ZERO")
        return backend::BlendFactor::ZERO;
    else if (upper == "ONE")
        return backend::BlendFactor::ONE;
    else if (upper == "SRC_COLOR")
        return backend::BlendFactor::SRC_COLOR;
    else if (upper == "ONE_MINUS_SRC_COLOR")
        return backend::BlendFactor::ONE_MINUS_SRC_COLOR;
    else if (upper == "DST_COLOR")
        return backend::BlendFactor::DST_COLOR;
    else if (upper == "ONE_MINUS_DST_COLOR")
        return backend::BlendFactor::ONE_MINUS_DST_COLOR;
    else if (upper == "SRC_ALPHA")
        return backend::BlendFactor::SRC_ALPHA;
    else if (upper == "ONE_MINUS_SRC_ALPHA")
        return backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
    else if (upper == "DST_ALPHA")
        return backend::BlendFactor::DST_ALPHA;
    else if (upper == "ONE_MINUS_DST_ALPHA")
        return backend::BlendFactor::ONE_MINUS_DST_ALPHA;
    else if (upper == "CONSTANT_ALPHA")
        return backend::BlendFactor::CONSTANT_ALPHA;
    else if (upper == "ONE_MINUS_CONSTANT_ALPHA")
        return backend::BlendFactor::ONE_MINUS_CONSTANT_ALPHA;
    else if (upper == "SRC_ALPHA_SATURATE")
        return backend::BlendFactor::SRC_ALPHA_SATURATE;
    else
    {
        CCLOG("Unsupported blend value (%s). (Will default to BLEND_ONE if errors are treated as warnings)", value.c_str());
        return backend::BlendFactor::ONE;
    }
}

static DepthFunction parseDepthFunc(const std::string& value)
{
    // Convert string to uppercase for comparison
    std::string upper(value);
    std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
    if (upper == "NEVER")
        return DepthFunction::NEVER;
    else if (upper == "LESS")
        return DepthFunction::LESS;
    else if (upper == "EQUAL")
        return DepthFunction::EQUAL;
    else if (upper == "LEQUAL")
        return DepthFunction::LESS_EQUAL;
    else if (upper == "GREATER")
        return DepthFunction::GREATER;
    else if (upper == "NOTEQUAL")
        return DepthFunction::NOT_EQUAL;
    else if (upper == "GEQUAL")
        return DepthFunction::GREATER_EQUAL;
    else if (upper == "ALWAYS")
        return DepthFunction::ALWAYS;
    else
    {
        CCLOG("Unsupported depth function value (%s). Will default to DEPTH_LESS if errors are treated as warnings)", value.c_str());
        return DepthFunction::LESS;
    }
}

static CullFaceSide parseCullFaceSide(const std::string& value)
{
    // Convert string to uppercase for comparison
    std::string upper(value);
    std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
    if (upper == "BACK")
        return CullFaceSide::BACK;
    else if (upper == "FRONT")
        return CullFaceSide::FRONT;
// XXX: metal doesn't support back&front culling. Is it needed, since it will draw nothing.
//    else if (upper == "FRONT_AND_BACK")
//        return RenderState::CULL_FACE_SIDE_FRONT_AND_BACK;
    else
    {
        CCLOG("Unsupported cull face side value (%s). Will default to BACK if errors are treated as warnings.", value.c_str());
        return CullFaceSide::BACK;
    }
}

static FrontFace parseFrontFace(const std::string& value)
{
    // Convert string to uppercase for comparison
    std::string upper(value);
    std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
    if (upper == "CCW")
        return FrontFace::COUNTER_CLOCK_WISE;
    else if (upper == "CW")
        return FrontFace::CLOCK_WISE;
    else
    {
        CCLOG("Unsupported front face side value (%s). Will default to CCW if errors are treated as warnings.", value.c_str());
        return FrontFace::COUNTER_CLOCK_WISE;
    }
}

void RenderState::StateBlock::setState(const std::string& name, const std::string& value)
{
    if (name.compare("blend") == 0)
    {
        setBlend(parseBoolean(value));
    }
    else if (name.compare("blendSrc") == 0)
    {
        setBlendSrc(parseBlend(value));
    }
    else if (name.compare("blendDst") == 0)
    {
        setBlendDst(parseBlend(value));
    }
    else if (name.compare("cullFace") == 0)
    {
        setCullFace(parseBoolean(value));
    }
    else if (name.compare("cullFaceSide") == 0)
    {
        setCullFaceSide(parseCullFaceSide(value));
    }
    else if (name.compare("frontFace") == 0)
    {
        setFrontFace(parseFrontFace(value));
    }
    else if (name.compare("depthTest") == 0)
    {
        setDepthTest(parseBoolean(value));
    }
    else if (name.compare("depthWrite") == 0)
    {
        setDepthWrite(parseBoolean(value));
    }
    else if (name.compare("depthFunc") == 0)
    {
        setDepthFunction(parseDepthFunc(value));
    }
    else
    {
        CCLOG("Unsupported render state string '%s'.", name.c_str());
    }
}

bool RenderState::StateBlock::isDirty() const
{
    // XXX
    return true;
}

uint32_t RenderState::StateBlock::getHash() const
{
    // XXX
    return 0x12345678;
}

void RenderState::StateBlock::setBlend(bool enabled)
{
    _blendEnabled = enabled;
    _modifiedBits |= RS_BLEND;
}

void RenderState::StateBlock::setBlendFunc(const BlendFunc& blendFunc)
{
    setBlendSrc(blendFunc.src);
    setBlendDst(blendFunc.dst);
}

void RenderState::StateBlock::setBlendSrc(backend::BlendFactor blend)
{
    _blendSrc = blend;
    _modifiedBits |= RS_BLEND_FUNC;
}

void RenderState::StateBlock::setBlendDst(backend::BlendFactor blend)
{
    _blendDst = blend;
    _modifiedBits |= RS_BLEND_FUNC;
}

void RenderState::StateBlock::setCullFace(bool enabled)
{
    _cullFaceEnabled = enabled;
    _modifiedBits |= RS_CULL_FACE;
}

void RenderState::StateBlock::setCullFaceSide(CullFaceSide side)
{
    _cullFaceSide = side;
    _modifiedBits |= RS_CULL_FACE_SIDE;
}

void RenderState::StateBlock::setFrontFace(FrontFace winding)
{
    _frontFace = winding;
    _modifiedBits |= RS_FRONT_FACE;
}

void RenderState::StateBlock::setDepthTest(bool enabled)
{
    _depthTestEnabled = enabled;
    _modifiedBits |= RS_DEPTH_TEST;
}

void RenderState::StateBlock::setDepthWrite(bool enabled)
{
    _depthWriteEnabled = enabled;
    _modifiedBits |= RS_DEPTH_WRITE;
}

void RenderState::StateBlock::setDepthFunction(DepthFunction func)
{
    _depthFunction = func;
    _modifiedBits |= RS_DEPTH_FUNC;
}

NS_CC_END
