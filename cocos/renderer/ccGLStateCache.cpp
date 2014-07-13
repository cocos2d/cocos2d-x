/****************************************************************************
Copyright (c) 2011      Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (C) 2013-2014 Chukong Technologies Inc.

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

#include "renderer/ccGLStateCache.h"

#include "renderer/CCGLProgram.h"
#include "base/CCDirector.h"
#include "base/ccConfig.h"
#include "base/CCConfiguration.h"

NS_CC_BEGIN

#if DIRECTX_ENABLED == 0

static const int MAX_ATTRIBUTES = 16;
static const int MAX_ACTIVE_TEXTURE = 16;

namespace
{
    static GLuint s_currentProjectionMatrix = -1;
    static uint32_t s_attributeFlags = 0;  // 32 attributes max

#if CC_ENABLE_GL_STATE_CACHE

    static GLuint    s_currentShaderProgram = -1;
    static GLuint    s_currentBoundTexture[MAX_ACTIVE_TEXTURE] =  {(GLuint)-1,(GLuint)-1,(GLuint)-1,(GLuint)-1, (GLuint)-1,(GLuint)-1,(GLuint)-1,(GLuint)-1, (GLuint)-1,(GLuint)-1,(GLuint)-1,(GLuint)-1, (GLuint)-1,(GLuint)-1,(GLuint)-1,(GLuint)-1, };
    static GLenum    s_blendingSource = -1;
    static GLenum    s_blendingDest = -1;
    static int       s_GLServerState = 0;
    static GLuint    s_VAO = 0;
    static GLenum    s_activeTexture = -1;

#endif // CC_ENABLE_GL_STATE_CACHE
}

// GL State Cache functions

namespace GL {

void invalidateStateCache( void )
{
    Director::getInstance()->resetMatrixStack();
    s_currentProjectionMatrix = -1;
    s_attributeFlags = 0;

#if CC_ENABLE_GL_STATE_CACHE
    s_currentShaderProgram = -1;
    for( int i=0; i < MAX_ACTIVE_TEXTURE; i++ )
    {
        s_currentBoundTexture[i] = -1;
    }

    s_blendingSource = -1;
    s_blendingDest = -1;
    s_GLServerState = 0;
    s_VAO = 0;
    
#endif // CC_ENABLE_GL_STATE_CACHE
}

void deleteProgram( GLuint program )
{
#if CC_ENABLE_GL_STATE_CACHE
    if(program == s_currentShaderProgram)
    {
        s_currentShaderProgram = -1;
    }
#endif // CC_ENABLE_GL_STATE_CACHE

    glDeleteProgram( program );
}

void useProgram( GLuint program )
{
#if CC_ENABLE_GL_STATE_CACHE
    if( program != s_currentShaderProgram ) {
        s_currentShaderProgram = program;
        glUseProgram(program);
    }
#else
    glUseProgram(program);
#endif // CC_ENABLE_GL_STATE_CACHE
}

static void SetBlending(GLenum sfactor, GLenum dfactor)
{
	if (sfactor == GL_ONE && dfactor == GL_ZERO)
    {
		glDisable(GL_BLEND);
	}
    else
    {
		glEnable(GL_BLEND);
		glBlendFunc(sfactor, dfactor);
	}
}

void blendFunc(GLenum sfactor, GLenum dfactor)
{
#if CC_ENABLE_GL_STATE_CACHE
    if (sfactor != s_blendingSource || dfactor != s_blendingDest)
    {
        s_blendingSource = sfactor;
        s_blendingDest = dfactor;
        SetBlending(sfactor, dfactor);
    }
#else
    SetBlending( sfactor, dfactor );
#endif // CC_ENABLE_GL_STATE_CACHE
}

void blendResetToCache(void)
{
	glBlendEquation(GL_FUNC_ADD);
#if CC_ENABLE_GL_STATE_CACHE
	SetBlending(s_blendingSource, s_blendingDest);
#else
	SetBlending(CC_BLEND_SRC, CC_BLEND_DST);
#endif // CC_ENABLE_GL_STATE_CACHE
}

void bindTexture2D(GLuint textureId)
{
    GL::bindTexture2DN(0, textureId);
}

void bindTexture2DN(GLuint textureUnit, GLuint textureId)
{
#if CC_ENABLE_GL_STATE_CACHE
    CCASSERT(textureUnit < MAX_ACTIVE_TEXTURE, "textureUnit is too big");
    if (s_currentBoundTexture[textureUnit] != textureId)
    {
        s_currentBoundTexture[textureUnit] = textureId;
        activeTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
#else
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureId);
#endif
}


void deleteTexture(GLuint textureId)
{
#if CC_ENABLE_GL_STATE_CACHE
    for (size_t i = 0; i < MAX_ACTIVE_TEXTURE; ++i)
    {
        if (s_currentBoundTexture[i] == textureId)
        {
            s_currentBoundTexture[i] = -1;
        }
    }
#endif // CC_ENABLE_GL_STATE_CACHE
    
	glDeleteTextures(1, &textureId);
}

void deleteTextureN(GLuint textureUnit, GLuint textureId)
{
    deleteTexture(textureId);
}

void activeTexture(GLenum texture)
{
#if CC_ENABLE_GL_STATE_CACHE
    if(s_activeTexture != texture) {
        s_activeTexture = texture;
        glActiveTexture(s_activeTexture);
    }
#else
    glActiveTexture(texture);
#endif
}

void bindVAO(GLuint vaoId)
{
    if (Configuration::getInstance()->supportsShareableVAO())
    {
    
#if CC_ENABLE_GL_STATE_CACHE
        if (s_VAO != vaoId)
        {
            s_VAO = vaoId;
            glBindVertexArray(vaoId);
        }
#else
        glBindVertexArray(vaoId);
#endif // CC_ENABLE_GL_STATE_CACHE
    
    }
}

// GL Vertex Attrib functions

void enableVertexAttribs(uint32_t flags)
{
    bindVAO(0);

    // hardcoded!
    for(int i=0; i < MAX_ATTRIBUTES; i++) {
        unsigned int bit = 1 << i;
        bool enabled = flags & bit;
        bool enabledBefore = s_attributeFlags & bit;
        if(enabled != enabledBefore) {
            if( enabled )
                glEnableVertexAttribArray(i);
            else
                glDisableVertexAttribArray(i);
        }
    }
    s_attributeFlags = flags;
}

// GL Uniforms functions

void setProjectionMatrixDirty( void )
{
    s_currentProjectionMatrix = -1;
}

} // Namespace GL

#else

DXStateCache::DXStateCache()
{
	invalidateStateCache();

	_view = GLView::sharedOpenGLView();
	CCASSERT(_view, "GLView not set.");

	_blendDesc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
	DX::ThrowIfFailed(_view->GetDevice()->CreateBlendState(&_blendDesc, &_blendState));
		
	_rasterizerDesc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
	_rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	DX::ThrowIfFailed(_view->GetDevice()->CreateRasterizerState(&_rasterizerDesc, &_rasterizerState));
}

void DXStateCache::invalidateStateCache()
{
	_vertexBuffer = nullptr;
	_indexBuffer = nullptr;
	_blendState = nullptr;
	_rasterizerState = nullptr;
	_inputLayout = nullptr;
	_vertexShader = nullptr;
	_pixelShader = nullptr;
	_blendDesc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
	_rasterizerDesc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
	_primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	memset(_constantBufferVS, 0, sizeof(_constantBufferVS));
	memset(_constantBufferPS, 0, sizeof(_constantBufferPS));
	memset(_textureViewsVS, 0, sizeof(_textureViewsVS));
	memset(_textureViewsPS, 0, sizeof(_textureViewsPS));
	memset(&_viewportRect, 0, sizeof(_viewportRect));
	memset(&_scissorRect, 0, sizeof(_scissorRect));
}

void DXStateCache::setShaders(ID3D11VertexShader* vs, ID3D11PixelShader* ps)
{
	if (vs != _vertexShader)
	{
		_view->GetContext()->VSSetShader(vs, nullptr, 0);
		_vertexShader = vs;
	}

	if (ps != _pixelShader)
	{
		_view->GetContext()->PSSetShader(ps, nullptr, 0);
		_pixelShader = ps;
	}
}

void DXStateCache::setVertexBuffer(ID3D11Buffer* buffer, UINT stride, UINT offset)
{
	if (buffer != _vertexBuffer)
	{
		_view->GetContext()->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
		_indexBuffer = buffer;
	}
}

void DXStateCache::setIndexBuffer(ID3D11Buffer* buffer)
{
	if (buffer != _indexBuffer)
	{
		_view->GetContext()->IASetIndexBuffer(buffer, DXGI_FORMAT_R16_UINT, 0);
		_indexBuffer = buffer;
	}
}

void DXStateCache::setPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	if (_primitiveTopology != topology)
	{
		_view->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		_primitiveTopology = topology;
	}
}

void DXStateCache::setInputLayout(ID3D11InputLayout* layout)
{
	if (_inputLayout != layout)
	{
		_view->GetContext()->IASetInputLayout(layout);
		_inputLayout = layout;
	}
}

void DXStateCache::setVSConstantBuffer(int index, ID3D11Buffer*const* buffer)
{
	CCASSERT(index < MAX_UNITS, "Invalid index of unit.");
	if (_constantBufferVS[index] != buffer)
	{
		_view->GetContext()->VSSetConstantBuffers(index, 1, buffer);
		_constantBufferVS[index] = buffer;
	}	
}

void DXStateCache::setPSConstantBuffer(int index, ID3D11Buffer*const* buffer)
{
	CCASSERT(index < MAX_UNITS, "Invalid index of unit.");
	if (_constantBufferPS[index] != buffer)
	{
		_view->GetContext()->PSSetConstantBuffers(index, 1, buffer);
		_constantBufferPS[index] = buffer;
	}	
}

void DXStateCache::setVSTexture(int index, ID3D11ShaderResourceView*const* textureView)
{
	CCASSERT(index < MAX_UNITS, "Invalid index of unit.");
	if (_textureViewsVS[index] != textureView)
	{
		_view->GetContext()->VSSetShaderResources(index, 1, textureView);
		_textureViewsVS[index] = textureView;
	}
}

void DXStateCache::setPSTexture(int index, ID3D11ShaderResourceView*const* textureView)
{
	CCASSERT(index < MAX_UNITS, "Invalid index of unit.");
	if (_textureViewsPS[index] != textureView)
	{
		_view->GetContext()->PSSetShaderResources(index, 1, textureView);
		_textureViewsPS[index] = textureView;
	}
}

void DXStateCache::setBlend(GLint GLsrc, GLint GLdst)
{
	D3D11_BLEND src = GetDXBlend(GLsrc);
	D3D11_BLEND dst = GetDXBlend(GLdst);

	bool change = src != _blendDesc.RenderTarget[0].SrcBlend || dst != _blendDesc.RenderTarget[0].DestBlend;
	if (change && _blendState)
	{
		_blendState->Release();
		_blendState = nullptr;
	}

	if (_blendState == nullptr)
	{
		_blendDesc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
		_blendDesc.RenderTarget[0].BlendEnable = true;
		_blendDesc.RenderTarget[0].SrcBlend = src;
		_blendDesc.RenderTarget[0].DestBlend = dst;
		_blendDesc.RenderTarget[0].SrcBlendAlpha = src;
		_blendDesc.RenderTarget[0].DestBlendAlpha = dst;
		DX::ThrowIfFailed(_view->GetDevice()->CreateBlendState(&_blendDesc, &_blendState));
		_view->GetContext()->OMSetBlendState(_blendState, nullptr, 0xffffffff);
	}

	setRasterizer();
}

void DXStateCache::setViewport(float x, float y, float w, float h)
{
	CD3D11_VIEWPORT viewport(x, y, w, h);
	if (viewport != _viewportRect)
	{
		_view->GetContext()->RSSetViewports(1, &viewport);
		_viewportRect = viewport;
	}
}

void DXStateCache::setScissor(float x, float y, float w, float h)
{
	CD3D11_RECT rect(x, y, x + w, y + h);
	if (rect != _scissorRect)
	{
		_view->GetContext()->RSSetScissorRects(1, &rect);
		_scissorRect = rect;
	}
}

void DXStateCache::getScissor(Rect& rect) const
{
	rect.origin.x = _scissorRect.left;
	rect.origin.y = _scissorRect.top;
	rect.size.width = _scissorRect.right - _scissorRect.left;
	rect.size.height = _scissorRect.bottom - _scissorRect.top;
}

void DXStateCache::enableScissor(bool enable)
{
	if (_rasterizerDesc.ScissorEnable != (BOOL)enable)
	{
		_rasterizerDesc.ScissorEnable = enable;
		_rasterizerDirty = true;
	}

	setRasterizer();
}

bool DXStateCache::isScissorEnabled() const
{
	return _rasterizerDesc.ScissorEnable != 0;
}

void DXStateCache::setRasterizer()
{	
	if (_rasterizerDirty)
	{
		if (_rasterizerState)
			_rasterizerState->Release();

		DX::ThrowIfFailed(_view->GetDevice()->CreateRasterizerState(&_rasterizerDesc, &_rasterizerState));
		_rasterizerDirty = false;
	}

	_view->GetContext()->RSSetState(_rasterizerState);
}

D3D11_BLEND DXStateCache::GetDXBlend(GLint glBlend) const
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

NS_CC_END
