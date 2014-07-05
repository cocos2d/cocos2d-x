/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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


#include "renderer/CCQuadCommand.h"

#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "xxhash.h"

NS_CC_BEGIN


QuadCommand::QuadCommand()
:_materialID(0)
,_texture(nullptr)
,_glProgramState(nullptr)
,_blendType(BlendFunc::DISABLE)
,_quads(nullptr)
,_quadsCount(0)
{
    _type = RenderCommand::Type::QUAD_COMMAND;
}

void QuadCommand::init(float globalOrder, Texture2D* texture, GLProgramState* glProgramState, BlendFunc blendType, V3F_C4B_T2F_Quad* quad, ssize_t quadCount, const Mat4 &mv)
{
    CCASSERT(glProgramState, "Invalid GLProgramState");
    CCASSERT(glProgramState->getVertexAttribsFlags() == 0, "No custom attributes are supported in QuadCommand");

    _globalOrder = globalOrder;

    _quadsCount = quadCount;
    _quads = quad;

    _mv = mv;

	if (_texture != texture || _blendType.src != blendType.src || _blendType.dst != blendType.dst || _glProgramState != glProgramState) {

        _texture = texture;
        _blendType = blendType;
        _glProgramState = glProgramState;

        generateMaterialID();
    }
}

QuadCommand::~QuadCommand()
{
}

void QuadCommand::generateMaterialID()
{

    if(_glProgramState->getUniformCount() > 0)
    {
        _materialID = QuadCommand::MATERIAL_ID_DO_NOT_BATCH;
    }
    else
    {
        int glProgram = (int)_glProgramState->getGLProgram()->getProgram();
        int intArray[4] = { glProgram, (int)_texture->getName(), (int)_blendType.src, (int)_blendType.dst};

        _materialID = XXH32((const void*)intArray, sizeof(intArray), 0);
    }
}

#if (DIRECTX_ENABLED == 1)
D3D11_BLEND GetDXBlend(GLint glBlend)
{
	if (glBlend == GL_ZERO)
		return D3D11_BLEND_ZERO;
	else if (glBlend == GL_SRC_COLOR)
		return D3D11_BLEND_SRC_COLOR;
	else if (glBlend == GL_ONE_MINUS_SRC_COLOR)
		return D3D11_BLEND_INV_SRC_COLOR;
	else if (glBlend == GL_SRC_ALPHA)
		return D3D11_BLEND_SRC_ALPHA;
	else if (glBlend == GL_ONE_MINUS_SRC_ALPHA)
		return D3D11_BLEND_INV_SRC_ALPHA;
	else if (glBlend == GL_DST_ALPHA)
		return D3D11_BLEND_DEST_ALPHA;
	else if (glBlend == GL_ONE_MINUS_DST_ALPHA)
		return D3D11_BLEND_INV_DEST_ALPHA;
	else if (glBlend == GL_DST_COLOR)
		return D3D11_BLEND_DEST_COLOR;
	else if (glBlend == GL_ONE_MINUS_DST_COLOR)
		return D3D11_BLEND_INV_DEST_COLOR;
	else if (glBlend == GL_SRC_ALPHA_SATURATE)
		return D3D11_BLEND_SRC_ALPHA_SAT;
	return D3D11_BLEND_ONE;
}
#endif

void QuadCommand::useMaterial() const
{
    //Set texture
#if (DIRECTX_ENABLED == 1)
	auto view = GLView::sharedOpenGLView();

	view->GetContext()->PSSetShaderResources(0, 1, _texture->getView());

	D3D11_BLEND src = GetDXBlend(_blendType.src);
	D3D11_BLEND dst = GetDXBlend(_blendType.dst);

	ID3D11BlendState* state = nullptr;
	if(state == nullptr)
	{
		CD3D11_BLEND_DESC d = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
		d.AlphaToCoverageEnable = false;
		d.IndependentBlendEnable = false;
		d.RenderTarget[0].BlendEnable = true; 
		d.RenderTarget[0].SrcBlend = src;
		d.RenderTarget[0].DestBlend = dst;
		//d.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		d.RenderTarget[0].SrcBlendAlpha = src;
		d.RenderTarget[0].DestBlendAlpha = dst;
		//d.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		//d.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		DX::ThrowIfFailed(view->GetDevice()->CreateBlendState(&d, &state));
	}

	view->GetContext()->OMSetBlendState(state, nullptr, 0xffffffff);
#else
    GL::bindTexture2D(_textureID);

    //set blend mode
    GL::blendFunc(_blendType.src, _blendType.dst);
#endif

    _glProgramState->apply(_mv);
}

NS_CC_END