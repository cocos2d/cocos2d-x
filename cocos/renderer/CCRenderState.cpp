/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
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

#include "CCRenderState.h"

#include <string>

#include "renderer/CCTexture2D.h"
#include "renderer/CCPass.h"
#include "renderer/ccGLStateCache.h"


NS_CC_BEGIN

RenderState::StateBlock* RenderState::StateBlock::_defaultState = nullptr;


RenderState::RenderState()
: _texture(nullptr)
, _hash(0)
, _hashDirty(true)
, _parent(nullptr)
{
    _state = StateBlock::create();
    CC_SAFE_RETAIN(_state);
}

RenderState::~RenderState()
{
    CC_SAFE_RELEASE(_state);
}

void RenderState::initialize()
{
    if (StateBlock::_defaultState == NULL)
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

    if (_texture)
        GL::bindTexture2D(_texture->getName());

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
    rs = NULL;
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
        return NULL;
    }

    while (rs)
    {
        if (rs->_parent == below || rs->_parent == NULL)
        {
            // Stop traversing up here.
            return rs;
        }
        rs = rs->_parent;
    }

    return NULL;
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

//
// The defaults are based on GamePlay3D defaults, with the following changes
// _depthWriteEnabled is FALSE
// _depthTestEnabled is TRUE
// _blendEnabled is TRUE
RenderState::StateBlock::StateBlock()
: _cullFaceEnabled(false)
, _depthTestEnabled(true), _depthWriteEnabled(false), _depthFunction(RenderState::DEPTH_LESS)
, _blendEnabled(true), _blendSrc(RenderState::BLEND_ONE), _blendDst(RenderState::BLEND_ZERO)
, _cullFaceSide(CULL_FACE_SIDE_BACK), _frontFace(FRONT_FACE_CCW)
, _stencilTestEnabled(false), _stencilWrite(RS_ALL_ONES)
, _stencilFunction(RenderState::STENCIL_ALWAYS), _stencilFunctionRef(0), _stencilFunctionMask(RS_ALL_ONES)
, _stencilOpSfail(RenderState::STENCIL_OP_KEEP), _stencilOpDpfail(RenderState::STENCIL_OP_KEEP), _stencilOpDppass(RenderState::STENCIL_OP_KEEP)
, _bits(0L)
{
}

RenderState::StateBlock::~StateBlock()
{
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

    // Update any state that differs from _defaultState and flip _defaultState bits
    if ((_bits & RS_BLEND) && (_blendEnabled != _defaultState->_blendEnabled))
    {
        if (_blendEnabled)
            glEnable(GL_BLEND);
        else
            glDisable(GL_BLEND);
        _defaultState->_blendEnabled = _blendEnabled;
    }
    if ((_bits & RS_BLEND_FUNC) && (_blendSrc != _defaultState->_blendSrc || _blendDst != _defaultState->_blendDst))
    {
        GL::blendFunc((GLenum)_blendSrc, (GLenum)_blendDst);
        _defaultState->_blendSrc = _blendSrc;
        _defaultState->_blendDst = _blendDst;
    }
    if ((_bits & RS_CULL_FACE) && (_cullFaceEnabled != _defaultState->_cullFaceEnabled))
    {
        if (_cullFaceEnabled)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);
        _defaultState->_cullFaceEnabled = _cullFaceEnabled;
    }
    if ((_bits & RS_CULL_FACE_SIDE) && (_cullFaceSide != _defaultState->_cullFaceSide))
    {
        glCullFace((GLenum)_cullFaceSide);
        _defaultState->_cullFaceSide = _cullFaceSide;
    }
    if ((_bits & RS_FRONT_FACE) && (_frontFace != _defaultState->_frontFace))
    {
        glFrontFace((GLenum)_frontFace);
        _defaultState->_frontFace = _frontFace;
    }
    if ((_bits & RS_DEPTH_TEST) && (_depthTestEnabled != _defaultState->_depthTestEnabled))
    {
        if (_depthTestEnabled)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
        _defaultState->_depthTestEnabled = _depthTestEnabled;
    }
    if ((_bits & RS_DEPTH_WRITE) && (_depthWriteEnabled != _defaultState->_depthWriteEnabled))
    {
        glDepthMask(_depthWriteEnabled ? GL_TRUE : GL_FALSE);
        _defaultState->_depthWriteEnabled = _depthWriteEnabled;
    }
    if ((_bits & RS_DEPTH_FUNC) && (_depthFunction != _defaultState->_depthFunction))
    {
        glDepthFunc((GLenum)_depthFunction);
        _defaultState->_depthFunction = _depthFunction;
    }
//    if ((_bits & RS_STENCIL_TEST) && (_stencilTestEnabled != _defaultState->_stencilTestEnabled))
//    {
//        if (_stencilTestEnabled)
//            glEnable(GL_STENCIL_TEST);
//        else
//            glDisable(GL_STENCIL_TEST);
//        _defaultState->_stencilTestEnabled = _stencilTestEnabled;
//    }
//    if ((_bits & RS_STENCIL_WRITE) && (_stencilWrite != _defaultState->_stencilWrite))
//    {
//        glStencilMask(_stencilWrite);
//        _defaultState->_stencilWrite = _stencilWrite;
//    }
//    if ((_bits & RS_STENCIL_FUNC) && (_stencilFunction != _defaultState->_stencilFunction ||
//                                      _stencilFunctionRef != _defaultState->_stencilFunctionRef ||
//                                      _stencilFunctionMask != _defaultState->_stencilFunctionMask))
//    {
//        glStencilFunc((GLenum)_stencilFunction, _stencilFunctionRef, _stencilFunctionMask);
//        _defaultState->_stencilFunction = _stencilFunction;
//        _defaultState->_stencilFunctionRef = _stencilFunctionRef;
//        _defaultState->_stencilFunctionMask = _stencilFunctionMask;
//    }
//    if ((_bits & RS_STENCIL_OP) && (_stencilOpSfail != _defaultState->_stencilOpSfail ||
//                                    _stencilOpDpfail != _defaultState->_stencilOpDpfail ||
//                                    _stencilOpDppass != _defaultState->_stencilOpDppass))
//    {
//        glStencilOp((GLenum)_stencilOpSfail, (GLenum)_stencilOpDpfail, (GLenum)_stencilOpDppass);
//        _defaultState->_stencilOpSfail = _stencilOpSfail;
//        _defaultState->_stencilOpDpfail = _stencilOpDpfail;
//        _defaultState->_stencilOpDppass = _stencilOpDppass;
//    }

    _defaultState->_bits |= _bits;
}

void RenderState::StateBlock::restore(long stateOverrideBits)
{
    CC_ASSERT(_defaultState);

    // If there is no state to restore (i.e. no non-default state), do nothing.
//    if (_defaultState->_bits == 0)
    if ( (stateOverrideBits | _defaultState->_bits) == stateOverrideBits)
    {
        return;
    }

    // Restore any state that is not overridden and is not default
    if (!(stateOverrideBits & RS_BLEND) && (_defaultState->_bits & RS_BLEND))
    {
        glEnable(GL_BLEND);
        _defaultState->_bits &= ~RS_BLEND;
        _defaultState->_blendEnabled = true;
    }
    if (!(stateOverrideBits & RS_BLEND_FUNC) && (_defaultState->_bits & RS_BLEND_FUNC))
    {
        GL::blendFunc(GL_ONE, GL_ZERO);
        _defaultState->_bits &= ~RS_BLEND_FUNC;
        _defaultState->_blendSrc = RenderState::BLEND_ONE;
        _defaultState->_blendDst = RenderState::BLEND_ZERO;
    }
    if (!(stateOverrideBits & RS_CULL_FACE) && (_defaultState->_bits & RS_CULL_FACE))
    {
        glDisable(GL_CULL_FACE);
        _defaultState->_bits &= ~RS_CULL_FACE;
        _defaultState->_cullFaceEnabled = false;
    }
    if (!(stateOverrideBits & RS_CULL_FACE_SIDE) && (_defaultState->_bits & RS_CULL_FACE_SIDE))
    {
        glCullFace((GLenum)GL_BACK);
        _defaultState->_bits &= ~RS_CULL_FACE_SIDE;
        _defaultState->_cullFaceSide = RenderState::CULL_FACE_SIDE_BACK;
    }
    if (!(stateOverrideBits & RS_FRONT_FACE) && (_defaultState->_bits & RS_FRONT_FACE))
    {
        glFrontFace((GLenum)GL_CCW);
        _defaultState->_bits &= ~RS_FRONT_FACE;
        _defaultState->_frontFace = RenderState::FRONT_FACE_CCW;
    }
    if (!(stateOverrideBits & RS_DEPTH_TEST) && (_defaultState->_bits & RS_DEPTH_TEST))
    {
        glEnable(GL_DEPTH_TEST);
        _defaultState->_bits &= ~RS_DEPTH_TEST;
        _defaultState->_depthTestEnabled = true;
    }
    if (!(stateOverrideBits & RS_DEPTH_WRITE) && (_defaultState->_bits & RS_DEPTH_WRITE))
    {
        glDepthMask(GL_FALSE);
        _defaultState->_bits &= ~RS_DEPTH_WRITE;
        _defaultState->_depthWriteEnabled = false;
    }
    if (!(stateOverrideBits & RS_DEPTH_FUNC) && (_defaultState->_bits & RS_DEPTH_FUNC))
    {
        glDepthFunc((GLenum)GL_LESS);
        _defaultState->_bits &= ~RS_DEPTH_FUNC;
        _defaultState->_depthFunction = RenderState::DEPTH_LESS;
    }
//    if (!(stateOverrideBits & RS_STENCIL_TEST) && (_defaultState->_bits & RS_STENCIL_TEST))
//    {
//        glDisable(GL_STENCIL_TEST);
//        _defaultState->_bits &= ~RS_STENCIL_TEST;
//        _defaultState->_stencilTestEnabled = false;
//    }
//    if (!(stateOverrideBits & RS_STENCIL_WRITE) && (_defaultState->_bits & RS_STENCIL_WRITE))
//    {
//        glStencilMask(RS_ALL_ONES);
//        _defaultState->_bits &= ~RS_STENCIL_WRITE;
//        _defaultState->_stencilWrite = RS_ALL_ONES;
//    }
//    if (!(stateOverrideBits & RS_STENCIL_FUNC) && (_defaultState->_bits & RS_STENCIL_FUNC))
//    {
//        glStencilFunc((GLenum)RenderState::STENCIL_ALWAYS, 0, RS_ALL_ONES);
//        _defaultState->_bits &= ~RS_STENCIL_FUNC;
//        _defaultState->_stencilFunction = RenderState::STENCIL_ALWAYS;
//        _defaultState->_stencilFunctionRef = 0;
//        _defaultState->_stencilFunctionMask = RS_ALL_ONES;
//    }
//    if (!(stateOverrideBits & RS_STENCIL_OP) && (_defaultState->_bits & RS_STENCIL_OP))
//    {
//        glStencilOp((GLenum)RenderState::STENCIL_OP_KEEP, (GLenum)RenderState::STENCIL_OP_KEEP, (GLenum)RenderState::STENCIL_OP_KEEP);
//        _defaultState->_bits &= ~RS_STENCIL_OP;
//        _defaultState->_stencilOpSfail = RenderState::STENCIL_OP_KEEP;
//        _defaultState->_stencilOpDpfail = RenderState::STENCIL_OP_KEEP;
//        _defaultState->_stencilOpDppass = RenderState::STENCIL_OP_KEEP;
//    }
}

void RenderState::StateBlock::enableDepthWrite()
{
    CC_ASSERT(_defaultState);

    // Internal method used to restore depth writing before a
    // clear operation. This is necessary if the last code to draw before the
    // next frame leaves depth writing disabled.
    if (!_defaultState->_depthWriteEnabled)
    {
        glDepthMask(GL_TRUE);
        _defaultState->_bits &= ~RS_DEPTH_WRITE;
        _defaultState->_depthWriteEnabled = true;
    }
}

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
    state->_stencilTestEnabled = _stencilTestEnabled;
    state->_stencilWrite = _stencilWrite;
    state->_stencilFunction = _stencilFunction;
    state->_stencilFunctionRef = _stencilFunctionRef;
    state->_stencilFunctionMask = _stencilFunctionMask;
    state->_stencilOpSfail = _stencilOpSfail;
    state->_stencilOpDpfail = _stencilOpDpfail;
    state->_stencilOpDppass = _stencilOpDppass;
    state->_bits = _bits;
}

static bool parseBoolean(const std::string& value)
{
    return (value.compare("true")==0);
}

static int parseInt(const std::string& value)
{
    // Android NDK 10 doesn't support std::stoi a/ std::stoul
#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
    return std::stoi(value);
#else
    return atoi(value.c_str());
#endif
}

static unsigned int parseUInt(const std::string& value)
{
    // Android NDK 10 doesn't support std::stoi a/ std::stoul
#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
    return (unsigned int)std::stoul(value);
#else
    return (unsigned int)atoi(value.c_str());
#endif

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

static RenderState::DepthFunction parseDepthFunc(const std::string& value)
{
    // Convert string to uppercase for comparison
    std::string upper(value);
    std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
    if (upper == "NEVER")
        return RenderState::DEPTH_NEVER;
    else if (upper == "LESS")
        return RenderState::DEPTH_LESS;
    else if (upper == "EQUAL")
        return RenderState::DEPTH_EQUAL;
    else if (upper == "LEQUAL")
        return RenderState::DEPTH_LEQUAL;
    else if (upper == "GREATER")
        return RenderState::DEPTH_GREATER;
    else if (upper == "NOTEQUAL")
        return RenderState::DEPTH_NOTEQUAL;
    else if (upper == "GEQUAL")
        return RenderState::DEPTH_GEQUAL;
    else if (upper == "ALWAYS")
        return RenderState::DEPTH_ALWAYS;
    else
    {
        CCLOG("Unsupported depth function value (%s). Will default to DEPTH_LESS if errors are treated as warnings)", value.c_str());
        return RenderState::DEPTH_LESS;
    }
}

static RenderState::CullFaceSide parseCullFaceSide(const std::string& value)
{
    // Convert string to uppercase for comparison
    std::string upper(value);
    std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
    if (upper == "BACK")
        return RenderState::CULL_FACE_SIDE_BACK;
    else if (upper == "FRONT")
        return RenderState::CULL_FACE_SIDE_FRONT;
    else if (upper == "FRONT_AND_BACK")
        return RenderState::CULL_FACE_SIDE_FRONT_AND_BACK;
    else
    {
        CCLOG("Unsupported cull face side value (%s). Will default to BACK if errors are treated as warnings.", value.c_str());
        return RenderState::CULL_FACE_SIDE_BACK;
    }
}

static RenderState::FrontFace parseFrontFace(const std::string& value)
{
    // Convert string to uppercase for comparison
    std::string upper(value);
    std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
    if (upper == "CCW")
        return RenderState::FRONT_FACE_CCW;
    else if (upper == "CW")
        return RenderState::FRONT_FACE_CW;
    else
    {
        CCLOG("Unsupported front face side value (%s). Will default to CCW if errors are treated as warnings.", value.c_str());
        return RenderState::FRONT_FACE_CCW;
    }
}

static RenderState::StencilFunction parseStencilFunc(const std::string& value)
{
    // Convert string to uppercase for comparison
    std::string upper(value);
    std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
    if (upper == "NEVER")
        return RenderState::STENCIL_NEVER;
    else if (upper == "LESS")
        return RenderState::STENCIL_LESS;
    else if (upper == "EQUAL")
        return RenderState::STENCIL_EQUAL;
    else if (upper == "LEQUAL")
        return RenderState::STENCIL_LEQUAL;
    else if (upper == "GREATER")
        return RenderState::STENCIL_GREATER;
    else if (upper == "NOTEQUAL")
        return RenderState::STENCIL_NOTEQUAL;
    else if (upper == "GEQUAL")
        return RenderState::STENCIL_GEQUAL;
    else if (upper == "ALWAYS")
        return RenderState::STENCIL_ALWAYS;
    else
    {
        CCLOG("Unsupported stencil function value (%s). Will default to STENCIL_ALWAYS if errors are treated as warnings)", value.c_str());
        return RenderState::STENCIL_ALWAYS;
    }
}

static RenderState::StencilOperation parseStencilOp(const std::string& value)
{
    // Convert string to uppercase for comparison
    std::string upper(value);
    std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
    if (upper == "KEEP")
        return RenderState::STENCIL_OP_KEEP;
    else if (upper == "ZERO")
        return RenderState::STENCIL_OP_ZERO;
    else if (upper == "REPLACE")
        return RenderState::STENCIL_OP_REPLACE;
    else if (upper == "INCR")
        return RenderState::STENCIL_OP_INCR;
    else if (upper == "DECR")
        return RenderState::STENCIL_OP_DECR;
    else if (upper == "INVERT")
        return RenderState::STENCIL_OP_INVERT;
    else if (upper == "INCR_WRAP")
        return RenderState::STENCIL_OP_INCR_WRAP;
    else if (upper == "DECR_WRAP")
        return RenderState::STENCIL_OP_DECR_WRAP;
    else
    {
        CCLOG("Unsupported stencil operation value (%s). Will default to STENCIL_OP_KEEP if errors are treated as warnings)", value.c_str());
        return RenderState::STENCIL_OP_KEEP;
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
//    else if (name.compare("stencilTest") == 0)
//    {
//        setStencilTest(parseBoolean(value));
//    }
//    else if (name.compare("stencilWrite") == 0)
//    {
//        setStencilWrite(parseUInt(value));
//    }
//    else if (name.compare("stencilFunc") == 0)
//    {
//        setStencilFunction(parseStencilFunc(value), _stencilFunctionRef, _stencilFunctionMask);
//    }
//    else if (name.compare("stencilFuncRef") == 0)
//    {
//        setStencilFunction(_stencilFunction, parseInt(value), _stencilFunctionMask);
//    }
//    else if (name.compare("stencilFuncMask") == 0)
//    {
//        setStencilFunction(_stencilFunction, _stencilFunctionRef, parseUInt(value));
//    }
//    else if (name.compare("stencilOpSfail") == 0)
//    {
//        setStencilOperation(parseStencilOp(value), _stencilOpDpfail, _stencilOpDppass);
//    }
//    else if (name.compare("stencilOpDpfail") == 0)
//    {
//        setStencilOperation(_stencilOpSfail, parseStencilOp(value), _stencilOpDppass);
//    }
//    else if (name.compare("stencilOpDppass") == 0)
//    {
//        setStencilOperation(_stencilOpSfail, _stencilOpDpfail, parseStencilOp(value));
//    }
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
    if (_cullFaceSide == CULL_FACE_SIDE_BACK)
    {
        // Default cull side
        _bits &= ~RS_CULL_FACE_SIDE;
    }
    else
    {
        _bits |= RS_CULL_FACE_SIDE;
    }
}

void RenderState::StateBlock::setFrontFace(FrontFace winding)
{
    _frontFace = winding;
    if (_frontFace == FRONT_FACE_CCW)
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
    if (_depthFunction == DEPTH_LESS)
    {
        // Default depth function
        _bits &= ~RS_DEPTH_FUNC;
    }
    else
    {
        _bits |= RS_DEPTH_FUNC;
    }
}

//void RenderState::StateBlock::setStencilTest(bool enabled)
//{
//    _stencilTestEnabled = enabled;
//    if (!enabled)
//    {
//        _bits &= ~RS_STENCIL_TEST;
//    }
//    else
//    {
//        _bits |= RS_STENCIL_TEST;
//    }
//}
//
//void RenderState::StateBlock::setStencilWrite(unsigned int mask)
//{
//    _stencilWrite = mask;
//    if (mask == RS_ALL_ONES)
//    {
//        // Default stencil write
//        _bits &= ~RS_STENCIL_WRITE;
//    }
//    else
//    {
//        _bits |= RS_STENCIL_WRITE;
//    }
//}
//
//void RenderState::StateBlock::setStencilFunction(StencilFunction func, int ref, unsigned int mask)
//{
//    _stencilFunction = func;
//    _stencilFunctionRef = ref;
//    _stencilFunctionMask = mask;
//    if (func == STENCIL_ALWAYS && ref == 0 && mask == RS_ALL_ONES)
//    {
//        // Default stencil function
//        _bits &= ~RS_STENCIL_FUNC;
//    }
//    else
//    {
//        _bits |= RS_STENCIL_FUNC;
//    }
//}
//
//void RenderState::StateBlock::setStencilOperation(StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass)
//{
//    _stencilOpSfail = sfail;
//    _stencilOpDpfail = dpfail;
//    _stencilOpDppass = dppass;
//    if (sfail == STENCIL_OP_KEEP && dpfail == STENCIL_OP_KEEP && dppass == STENCIL_OP_KEEP)
//    {
//        // Default stencil operation
//        _bits &= ~RS_STENCIL_OP;
//    }
//    else
//    {
//        _bits |= RS_STENCIL_OP;
//    }
//}

NS_CC_END