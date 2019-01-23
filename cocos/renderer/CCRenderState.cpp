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

#include "renderer/CCTexture2D.h"
#include "renderer/CCPass.h"
#include "base/ccUtils.h"
#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"

NS_CC_BEGIN

RenderState::StateBlock* RenderState::StateBlock::_defaultState = nullptr;


RenderState::RenderState()
{
    _state = StateBlock::create();
    CC_SAFE_RETAIN(_state);
}

RenderState::~RenderState()
{
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_state);
}

void RenderState::initialize()
{
    if (StateBlock::_defaultState == nullptr)
    {
        StateBlock::_defaultState = StateBlock::create();
        CC_SAFE_RETAIN(StateBlock::_defaultState);
    }
}

void RenderState::finalize()
{
    CC_SAFE_RELEASE_NULL(StateBlock::_defaultState);
}

bool RenderState::init(RenderState* parent)
{
    CCASSERT(!_parent, "Cannot reinitialize Render State");
    CCASSERT(parent, "parent must be non-null");

    // Weak reference
    _parent = parent;
    return true;
}

std::string RenderState::getName() const
{
    return _name;
}


void RenderState::setTexture(Texture2D* texture)
{
    if (_texture != texture)
    {
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
        CC_SAFE_RETAIN(_texture);
    }
}

Texture2D* RenderState::getTexture() const
{
    return _texture;
}

void RenderState::bind(Pass* pass)
{
    CC_ASSERT(pass);

//    if (_texture)
//    {
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, _texture->getName());
//    }

    // Get the combined modified state bits for our RenderState hierarchy.
    long stateOverrideBits = _state ? _state->_bits : 0;
    RenderState* rs = _parent;
    while (rs)
    {
        if (rs->_state)
        {
            stateOverrideBits |= rs->_state->_bits;
        }
        rs = rs->_parent;
    }

    // Restore renderer state to its default, except for explicitly specified states
    StateBlock::restore(stateOverrideBits);

    // Apply renderer state for the entire hierarchy, top-down.
    rs = nullptr;
    while ((rs = getTopmost(rs)))
    {
        if (rs->_state)
        {
            rs->_state->bindNoRestore();
        }
    }
}

RenderState* RenderState::getTopmost(RenderState* below)
{
    RenderState* rs = this;
    if (rs == below)
    {
        // Nothing below ourself.
        return nullptr;
    }

    while (rs)
    {
        if (rs->_parent == below || rs->_parent == nullptr)
        {
            // Stop traversing up here.
            return rs;
        }
        rs = rs->_parent;
    }

    return nullptr;
}

RenderState::StateBlock* RenderState::getStateBlock() const
{
    return _state;
}

void RenderState::setStateBlock(RenderState::StateBlock* state)
{
    CC_SAFE_RETAIN(state);
    CC_SAFE_RELEASE(_state);
    _state = state;
}

void RenderState::cloneInto(RenderState* renderState) const
{
    CCASSERT(renderState, "must be non null");

    // Clone our state block
    if (_state)
    {
        _state->cloneInto(renderState->getStateBlock());
    }

    renderState->_name = _name;
    renderState->_texture = _texture;
    CC_SAFE_RETAIN(renderState->_texture);
    // weak ref. don't retain
    renderState->_parent = _parent;
}

//
// StateBlock
//
RenderState::StateBlock* RenderState::StateBlock::create()
{
    auto state = new (std::nothrow) RenderState::StateBlock();
    if (state)
    {
        state->autorelease();
    }

    return state;
}

void RenderState::StateBlock::bind()
{
    // When the public bind() is called with no RenderState object passed in,
    // we assume we are being called to bind the state of a single StateBlock,
    // irrespective of whether it belongs to a hierarchy of RenderStates.
    // Therefore, we call restore() here with only this StateBlock's override
    // bits to restore state before applying the new state.
    StateBlock::restore(_bits);

    bindNoRestore();
}

void RenderState::StateBlock::bindNoRestore()
{
    CC_ASSERT(_defaultState);

    auto renderer = Director::getInstance()->getRenderer();

    // Update any state that differs from _defaultState and flip _defaultState bits
    if ((_bits & RS_BLEND) && (_blendEnabled != _defaultState->_blendEnabled))
    {
    //TODO
//        if (_blendEnabled)
//            glEnable(GL_BLEND);
//        else
//            glDisable(GL_BLEND);

        _defaultState->_blendEnabled = _blendEnabled;
    }
    if ((_bits & RS_BLEND_FUNC) && (_blendSrc != _defaultState->_blendSrc || _blendDst != _defaultState->_blendDst))
    {
    //TODO
//        utils::setBlending(utils::toBackendBlendFactor(_blendSrc), utils::toBackendBlendFactor(_blendDst));
        _defaultState->_blendSrc = _blendSrc;
        _defaultState->_blendDst = _blendDst;
    }
    if ((_bits & RS_CULL_FACE) && (_cullFaceEnabled != _defaultState->_cullFaceEnabled))
    {
        if (!_cullFaceEnabled)
             renderer->setCullMode(CullMode::NONE);

        _defaultState->_cullFaceEnabled = _cullFaceEnabled;
    }
    if ((_bits & RS_CULL_FACE_SIDE) && (_cullFaceSide != _defaultState->_cullFaceSide))
    {
        renderer->setCullMode(_cullFaceSide);
        _defaultState->_cullFaceSide = _cullFaceSide;
    }
    if ((_bits & RS_FRONT_FACE) && (_frontFace != _defaultState->_frontFace))
    {
        renderer->setWinding(_frontFace);
        _defaultState->_frontFace = _frontFace;
    }
    if ((_bits & RS_DEPTH_TEST) && (_depthTestEnabled != _defaultState->_depthTestEnabled))
    {
        renderer->setDepthTest(_depthTestEnabled);
        _defaultState->_depthTestEnabled = _depthTestEnabled;
    }
    if ((_bits & RS_DEPTH_WRITE) && (_depthWriteEnabled != _defaultState->_depthWriteEnabled))
    {
        renderer->setDepthWrite(_depthTestEnabled);
        _defaultState->_depthWriteEnabled = _depthWriteEnabled;
    }
    if ((_bits & RS_DEPTH_FUNC) && (_depthFunction != _defaultState->_depthFunction))
    {
    //TODO
//        glDepthFunc((GLenum)_depthFunction);
//        renderer->setDepthCompareFunction(backend::CompareFunction func)
        _defaultState->_depthFunction = _depthFunction;
    }

    _defaultState->_bits |= _bits;
}

void RenderState::StateBlock::restore(long stateOverrideBits)
{
    CC_ASSERT(_defaultState);

    auto renderer = Director::getInstance()->getRenderer();

    // If there is no state to restore (i.e. no non-default state), do nothing.
//    if (_defaultState->_bits == 0)
    if ( (stateOverrideBits | _defaultState->_bits) == stateOverrideBits)
        return;

    // Restore any state that is not overridden and is not default
    if (!(stateOverrideBits & RS_BLEND) && (_defaultState->_bits & RS_BLEND))
    {
    //TODO
//        glEnable(GL_BLEND);
        _defaultState->_bits &= ~RS_BLEND;
        _defaultState->_blendEnabled = true;
    }
    if (!(stateOverrideBits & RS_BLEND_FUNC) && (_defaultState->_bits & RS_BLEND_FUNC))
    {
    //TODO
//        utils::setBlending(backend::BlendFactor::ONE, backend::BlendFactor::ZERO);
        _defaultState->_bits &= ~RS_BLEND_FUNC;
        _defaultState->_blendSrc = RenderState::BLEND_ONE;
        _defaultState->_blendDst = RenderState::BLEND_ZERO;
    }
    if (!(stateOverrideBits & RS_CULL_FACE) && (_defaultState->_bits & RS_CULL_FACE))
    {
        renderer->setCullMode(CullMode::NONE);
        _defaultState->_bits &= ~RS_CULL_FACE;
        _defaultState->_cullFaceEnabled = false;
    }
    if (!(stateOverrideBits & RS_CULL_FACE_SIDE) && (_defaultState->_bits & RS_CULL_FACE_SIDE))
    {
        renderer->setCullMode(CullMode::BACK);
        _defaultState->_bits &= ~RS_CULL_FACE_SIDE;
        _defaultState->_cullFaceSide = CullFaceSide::BACK;
    }
    if (!(stateOverrideBits & RS_FRONT_FACE) && (_defaultState->_bits & RS_FRONT_FACE))
    {
        renderer->setWinding(Winding::COUNTER_CLOCK_WISE);
        _defaultState->_bits &= ~RS_FRONT_FACE;
        _defaultState->_frontFace = Winding::COUNTER_CLOCK_WISE;
    }
    if (!(stateOverrideBits & RS_DEPTH_TEST) && (_defaultState->_bits & RS_DEPTH_TEST))
    {
        renderer->setDepthTest(true);
        _defaultState->_bits &= ~RS_DEPTH_TEST;
        _defaultState->_depthTestEnabled = true;
    }
    if (!(stateOverrideBits & RS_DEPTH_WRITE) && (_defaultState->_bits & RS_DEPTH_WRITE))
    {
        renderer->setDepthWrite(false);
        _defaultState->_bits &= ~RS_DEPTH_WRITE;
        _defaultState->_depthWriteEnabled = false;
    }
    if (!(stateOverrideBits & RS_DEPTH_FUNC) && (_defaultState->_bits & RS_DEPTH_FUNC))
    {
    //TODO
//        glDepthFunc((GLenum)GL_LESS);
        _defaultState->_bits &= ~RS_DEPTH_FUNC;
        _defaultState->_depthFunction = DepthFunction::LESS;
    }
}

//void RenderState::StateBlock::enableDepthWrite()
//{
//    CC_ASSERT(_defaultState);
//
//    // Internal method used to restore depth writing before a
//    // clear operation. This is necessary if the last code to draw before the
//    // next frame leaves depth writing disabled.
//    if (!_defaultState->_depthWriteEnabled)
//    {
////        glDepthMask(GL_TRUE);
//
//        _defaultState->_bits &= ~RS_DEPTH_WRITE;
//        _defaultState->_depthWriteEnabled = true;
//    }
//}

void RenderState::StateBlock::cloneInto(StateBlock* state) const
{
    CC_ASSERT(state);

    state->_cullFaceEnabled = _cullFaceEnabled;
    state->_depthTestEnabled = _depthTestEnabled;
    state->_depthWriteEnabled = _depthWriteEnabled;
    state->_depthFunction = _depthFunction;
    state->_blendEnabled = _blendEnabled;
    state->_blendSrc = _blendSrc;
    state->_blendDst = _blendDst;
    state->_cullFaceSide = _cullFaceSide;
    state->_frontFace = _frontFace;
    state->_bits = _bits;
}

static bool parseBoolean(const std::string& value)
{
    return (value.compare("true")==0);
}

static RenderState::Blend parseBlend(const std::string& value)
{
    // Convert the string to uppercase for comparison.
    std::string upper(value);
    std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
    if (upper == "ZERO")
        return RenderState::BLEND_ZERO;
    else if (upper == "ONE")
        return RenderState::BLEND_ONE;
    else if (upper == "SRC_COLOR")
        return RenderState::BLEND_SRC_COLOR;
    else if (upper == "ONE_MINUS_SRC_COLOR")
        return RenderState::BLEND_ONE_MINUS_SRC_COLOR;
    else if (upper == "DST_COLOR")
        return RenderState::BLEND_DST_COLOR;
    else if (upper == "ONE_MINUS_DST_COLOR")
        return RenderState::BLEND_ONE_MINUS_DST_COLOR;
    else if (upper == "SRC_ALPHA")
        return RenderState::BLEND_SRC_ALPHA;
    else if (upper == "ONE_MINUS_SRC_ALPHA")
        return RenderState::BLEND_ONE_MINUS_SRC_ALPHA;
    else if (upper == "DST_ALPHA")
        return RenderState::BLEND_DST_ALPHA;
    else if (upper == "ONE_MINUS_DST_ALPHA")
        return RenderState::BLEND_ONE_MINUS_DST_ALPHA;
    else if (upper == "CONSTANT_ALPHA")
        return RenderState::BLEND_CONSTANT_ALPHA;
    else if (upper == "ONE_MINUS_CONSTANT_ALPHA")
        return RenderState::BLEND_ONE_MINUS_CONSTANT_ALPHA;
    else if (upper == "SRC_ALPHA_SATURATE")
        return RenderState::BLEND_SRC_ALPHA_SATURATE;
    else
    {
        CCLOG("Unsupported blend value (%s). (Will default to BLEND_ONE if errors are treated as warnings)", value.c_str());
        return RenderState::BLEND_ONE;
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

static CullMode parseCullFaceSide(const std::string& value)
{
    // Convert string to uppercase for comparison
    std::string upper(value);
    std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
    if (upper == "BACK")
        return CullMode::BACK;
    else if (upper == "FRONT")
        return CullMode::FRONT;
// XXX: metal doesn't support back&front culling. Is it needed, since it will draw nothing.
//    else if (upper == "FRONT_AND_BACK")
//        return RenderState::CULL_FACE_SIDE_FRONT_AND_BACK;
    else
    {
        CCLOG("Unsupported cull face side value (%s). Will default to BACK if errors are treated as warnings.", value.c_str());
        return CullMode::BACK;
    }
}

static Winding parseFrontFace(const std::string& value)
{
    // Convert string to uppercase for comparison
    std::string upper(value);
    std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
    if (upper == "CCW")
        return Winding::COUNTER_CLOCK_WISE;
    else if (upper == "CW")
        return Winding::CLOCK_WISE;
    else
    {
        CCLOG("Unsupported front face side value (%s). Will default to CCW if errors are treated as warnings.", value.c_str());
        return Winding::COUNTER_CLOCK_WISE;
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

void RenderState::StateBlock::invalidate(long stateBits)
{
    CCASSERT(_defaultState, "_default state not created yet. Cannot be invalidated");

    _defaultState->_bits = stateBits;
    _defaultState->restore(0);
}

void RenderState::StateBlock::setBlend(bool enabled)
{
    _blendEnabled = enabled;
    if (enabled)
    {
        _bits &= ~RS_BLEND;
    }
    else
    {
        _bits |= RS_BLEND;
    }
}

void RenderState::StateBlock::setBlendFunc(const BlendFunc& blendFunc)
{
    setBlendSrc((RenderState::Blend)blendFunc.src);
    setBlendDst((RenderState::Blend)blendFunc.dst);
}

void RenderState::StateBlock::setBlendSrc(Blend blend)
{
    _blendSrc = blend;
    if (_blendSrc == BLEND_ONE && _blendDst == BLEND_ZERO)
    {
        // Default blend func
        _bits &= ~RS_BLEND_FUNC;
    }
    else
    {
        _bits |= RS_BLEND_FUNC;
    }
}

void RenderState::StateBlock::setBlendDst(Blend blend)
{
    _blendDst = blend;
    if (_blendSrc == BLEND_ONE && _blendDst == BLEND_ZERO)
    {
        // Default blend func
        _bits &= ~RS_BLEND_FUNC;
    }
    else
    {
        _bits |= RS_BLEND_FUNC;
    }
}

void RenderState::StateBlock::setCullFace(bool enabled)
{
    _cullFaceEnabled = enabled;
    if (!enabled)
    {
        _bits &= ~RS_CULL_FACE;
    }
    else
    {
        _bits |= RS_CULL_FACE;
    }
}

void RenderState::StateBlock::setCullFaceSide(CullFaceSide side)
{
    _cullFaceSide = side;
    if (_cullFaceSide == CullFaceSide::BACK)
    {
        // Default cull side
        _bits &= ~RS_CULL_FACE_SIDE;
    }
    else
    {
        _bits |= RS_CULL_FACE_SIDE;
    }
}

void RenderState::StateBlock::setFrontFace(Winding winding)
{
    _frontFace = winding;
    if (_frontFace == Winding::COUNTER_CLOCK_WISE)
    {
        // Default front face
        _bits &= ~RS_FRONT_FACE;
    }
    else
    {
        _bits |= RS_FRONT_FACE;
    }
}

void RenderState::StateBlock::setDepthTest(bool enabled)
{
    _depthTestEnabled = enabled;
    if (enabled)
    {
        _bits &= ~RS_DEPTH_TEST;
    }
    else
    {
        _bits |= RS_DEPTH_TEST;
    }
}

void RenderState::StateBlock::setDepthWrite(bool enabled)
{
    _depthWriteEnabled = enabled;
    if (!enabled)
    {
        _bits &= ~RS_DEPTH_WRITE;
    }
    else
    {
        _bits |= RS_DEPTH_WRITE;
    }
}

void RenderState::StateBlock::setDepthFunction(DepthFunction func)
{
    _depthFunction = func;
    if (_depthFunction == DepthFunction::LESS)
    {
        // Default depth function
        _bits &= ~RS_DEPTH_FUNC;
    }
    else
    {
        _bits |= RS_DEPTH_FUNC;
    }
}

NS_CC_END
