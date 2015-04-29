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
#include "renderer/CCTexture2D.h"
#include "renderer/CCPass.h"
#include "renderer/ccGLStateCache.h"


NS_CC_BEGIN

// Render state override bits
enum
{
    RS_BLEND = (1 << 0),
    RS_BLEND_FUNC = (1 << 1),
    RS_CULL_FACE = (1 << 2),
    RS_DEPTH_TEST = (1 << 3),
    RS_DEPTH_WRITE = (1 << 4),
    RS_DEPTH_FUNC = (1 << 5),
    RS_CULL_FACE_SIDE = (1 << 6),
    RS_STENCIL_TEST = (1 << 7),
    RS_STENCIL_WRITE = (1 << 8),
    RS_STENCIL_FUNC = (1 << 9),
    RS_STENCIL_OP = (1 << 10),
    RS_FRONT_FACE = (1 << 11),

    RS_ALL_ONES = 0xFFFFFFFF,
};



RenderState* RenderState::create(RenderState* parent)
{
    return new (std::nothrow) RenderState(parent);
}

RenderState::RenderState()
: _parent(nullptr)
, _textures()
, _hash(0)
, _hashDirty(true)
, _state(nullptr)
{
    _state = StateBlock::create();
    CC_SAFE_RETAIN(_state);
}

RenderState::RenderState(RenderState *parent)
{
    _parent = parent;
    CC_SAFE_RETAIN(parent);

    _state = StateBlock::create();
    CC_SAFE_RETAIN(_state);
}

RenderState::~RenderState()
{
    CC_SAFE_RELEASE(_parent);
    CC_SAFE_RELEASE(_state);
}

std::string RenderState::getName() const
{
    return _name;
}


const Vector<Texture2D*>& RenderState::getTextures() const
{
    return _textures;
}

void RenderState::setTexture(Texture2D* texture)
{
    if (_textures.size() > 0)
        _textures.replace(0, texture);
    else
        _textures.pushBack(texture);
}

Texture2D* RenderState::getTexture() const
{
    if (_textures.size() > 0)
        return _textures.at(0);
    return nullptr;
}

void RenderState::bind(Pass* pass)
{
    CC_ASSERT(pass);

    if (_textures.size() > 0)
        GL::bindTexture2D(_textures.at(0)->getName());

    _state->bind();
}

RenderState::StateBlock* RenderState::getStateBlock() const
{
    return _state;
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

RenderState::StateBlock::StateBlock()
: _blendEnabled(true)
, _blendSrc(BLEND_SRC_ALPHA)
, _blendDst(BLEND_ONE_MINUS_SRC_ALPHA)
{
}

RenderState::StateBlock::~StateBlock()
{
}

static bool parseBoolean(const std::string& value)
{
    return (value.compare("true")==0);
}

static int parseInt(const std::string& value)
{
    return std::stoi(value);
}

static unsigned int parseUInt(const std::string& value)
{
    return (unsigned int)std::stoul(value);
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
    else if (name.compare("blendSrc") == 0 || name.compare("srcBlend") == 0 )   // Leaving srcBlend for backward compat.
    {
        setBlendSrc(parseBlend(value));
    }
    else if (name.compare("blendDst") == 0 || name.compare("dstBlend") == 0)    // // Leaving dstBlend for backward compat.
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
    else if (name.compare("stencilTest") == 0)
    {
        setStencilTest(parseBoolean(value));
    }
    else if (name.compare("stencilWrite") == 0)
    {
        setStencilWrite(parseUInt(value));
    }
    else if (name.compare("stencilFunc") == 0)
    {
        setStencilFunction(parseStencilFunc(value), _stencilFunctionRef, _stencilFunctionMask);
    }
    else if (name.compare("stencilFuncRef") == 0)
    {
        setStencilFunction(_stencilFunction, parseInt(value), _stencilFunctionMask);
    }
    else if (name.compare("stencilFuncMask") == 0)
    {
        setStencilFunction(_stencilFunction, _stencilFunctionRef, parseUInt(value));
    }
    else if (name.compare("stencilOpSfail") == 0)
    {
        setStencilOperation(parseStencilOp(value), _stencilOpDpfail, _stencilOpDppass);
    }
    else if (name.compare("stencilOpDpfail") == 0)
    {
        setStencilOperation(_stencilOpSfail, parseStencilOp(value), _stencilOpDppass);
    }
    else if (name.compare("stencilOpDppass") == 0)
    {
        setStencilOperation(_stencilOpSfail, _stencilOpDpfail, parseStencilOp(value));
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

void RenderState::StateBlock::bind()
{
    GL::blendFunc(_blendSrc, _blendDst);
}

void RenderState::StateBlock::setBlend(bool enabled)
{
    _blendEnabled = enabled;
    if (!enabled)
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
    if (blendFunc == BlendFunc::DISABLE)
    {
        setBlendSrc(BLEND_ONE);
        setBlendDst(BLEND_ZERO);
    }
    else if (blendFunc == BlendFunc::ALPHA_PREMULTIPLIED)
    {
        setBlendSrc(BLEND_ONE);
        setBlendDst(BLEND_ONE_MINUS_SRC_ALPHA);
    }
    else if (blendFunc == BlendFunc::ALPHA_NON_PREMULTIPLIED)
    {
        setBlendSrc(BLEND_SRC_ALPHA);
        setBlendDst(BLEND_ONE_MINUS_SRC_ALPHA);
    }
    else if (blendFunc == BlendFunc::ADDITIVE)
    {
        setBlendSrc(BLEND_SRC_ALPHA);
        setBlendDst(BLEND_ONE);
    }
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
    if (!enabled)
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
    if (enabled)
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

void RenderState::StateBlock::setStencilTest(bool enabled)
{
    _stencilTestEnabled = enabled;
    if (!enabled)
    {
        _bits &= ~RS_STENCIL_TEST;
    }
    else
    {
        _bits |= RS_STENCIL_TEST;
    }
}

void RenderState::StateBlock::setStencilWrite(unsigned int mask)
{
    _stencilWrite = mask;
    if (mask == RS_ALL_ONES)
    {
        // Default stencil write
        _bits &= ~RS_STENCIL_WRITE;
    }
    else
    {
        _bits |= RS_STENCIL_WRITE;
    }
}

void RenderState::StateBlock::setStencilFunction(StencilFunction func, int ref, unsigned int mask)
{
    _stencilFunction = func;
    _stencilFunctionRef = ref;
    _stencilFunctionMask = mask;
    if (func == STENCIL_ALWAYS && ref == 0 && mask == RS_ALL_ONES)
    {
        // Default stencil function
        _bits &= ~RS_STENCIL_FUNC;
    }
    else
    {
        _bits |= RS_STENCIL_FUNC;
    }
}

void RenderState::StateBlock::setStencilOperation(StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass)
{
    _stencilOpSfail = sfail;
    _stencilOpDpfail = dpfail;
    _stencilOpDppass = dppass;
    if (sfail == STENCIL_OP_KEEP && dpfail == STENCIL_OP_KEEP && dppass == STENCIL_OP_KEEP)
    {
        // Default stencil operation
        _bits &= ~RS_STENCIL_OP;
    }
    else
    {
        _bits |= RS_STENCIL_OP;
    }
}

NS_CC_END