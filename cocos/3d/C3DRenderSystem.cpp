#include "C3DRenderSystem.h"
#include "Base.h"
#include "C3DLayer.h"
#include "C3DScene.h"

#include "Vector4.h"
#include "C3DRenderBlock.h"
#include "C3DViewport.h"
#include "C3DEffect.h"

#include "C3DMaterial.h"

#include "C3DEffectManager.h"
#include "C3DMaterialManager.h"

namespace cocos2d
{
static C3DRenderSystem* __renderSystemInstance = nullptr;

C3DRenderSystem::C3DRenderSystem()
{
	_clearColor = nullptr;
	_clearDepth = 1.0f;
	_clearStencil = 0;

	_effectManager = C3DEffectManager::getInstance();
	_effectManager->retain();

	_materialManager = C3DMaterialManager::getInstance();
	_materialManager->retain();

	initialize();

}

C3DRenderSystem* C3DRenderSystem::create()
{
	if (!__renderSystemInstance)
	{
		__renderSystemInstance = new C3DRenderSystem();
		__renderSystemInstance->autorelease();
	}
	return __renderSystemInstance;
}

C3DRenderSystem* C3DRenderSystem::getInstance()
{
	CCAssert(__renderSystemInstance, "Render system not created");
	return __renderSystemInstance;
}

C3DRenderSystem::~C3DRenderSystem()
{
	finalize();
	__renderSystemInstance = nullptr;
	SAFE_RELEASE(_effectManager);
	SAFE_RELEASE(_materialManager);
}

void C3DRenderSystem::initialize()
{
	C3DStateBlock::initialize();
	// initialize as window size
	cocos2d::CCSize size = cocos2d::CCDirector::sharedDirector()->getWinSize();

	_viewport = new C3DViewport(0, 0, (int)size.width, (int)size.height);

	C3DEffectManager::getInstance()->preload("config/effect.config");
}

void C3DRenderSystem::finalize()
{
	C3DStateBlock::finalize();

	C3DEffectManager::getInstance()->removeAll();
	C3DMaterialManager::getInstance()->removeAll();
	SAFE_DELETE(_viewport);
	SAFE_DELETE(_clearColor);
}

void C3DRenderSystem::setViewport(float x, float y, float width, float height)
{
	_viewport->x = (int)x;
	_viewport->y = (int)y;
	_viewport->width = (int)width;
	_viewport->height = (int)height;
	_viewport->apply();
}

void C3DRenderSystem::setViewport(const C3DViewport* viewport)
{
	if (viewport)
		*_viewport = *viewport;
	_viewport->apply();
}

const C3DViewport* C3DRenderSystem::getViewport() const
{
	return _viewport;
}

RenderChannelManager* C3DRenderSystem::getRenderChannelManager() const
{
	return _renderChannelManager;
}

void C3DRenderSystem::update(long elapsedTime)
{
	C3DEffectManager::getInstance()->update(elapsedTime);
}

void C3DRenderSystem::clear(ClearFlags flags, const Vector4* clearColor, float clearDepth, int clearStencil)
{
	if(clearColor == nullptr)
		return;

	if(_clearColor == nullptr)
	{
		_clearColor = new Vector4();
	}

	GLbitfield bits = 0;
	if (flags & CLEAR_COLOR)
	{
		if (clearColor->x != _clearColor->x ||
				clearColor->y != _clearColor->y ||
				clearColor->z != _clearColor->z ||
				clearColor->w != _clearColor->w )
		{
			glClearColor(clearColor->x, clearColor->y, clearColor->z, clearColor->w);
			_clearColor->set(*clearColor);
		}
		bits |= GL_COLOR_BUFFER_BIT;
	}

	if (flags & CLEAR_DEPTH)
	{
		if (clearDepth != _clearDepth)
		{
			glClearDepth(clearDepth);
			_clearDepth = clearDepth;
		}
		bits |= GL_DEPTH_BUFFER_BIT;

		// We need to explicitly call the static enableDepthWrite() method on StateBlock
		// to ensure depth writing is enabled before clearing the depth buffer (and to
		// update the global StateBlock render state to reflect this).
		C3DStateBlock::enableDepthWrite();
	}

	if (flags & CLEAR_STENCIL)
	{
		if (clearStencil != _clearStencil)
		{
			glClearStencil(clearStencil);
			_clearStencil = clearStencil;
		}
		bits |= GL_STENCIL_BUFFER_BIT;
	}
	glClear(bits);
}
}
