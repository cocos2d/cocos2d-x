//------------------------------------------------------------------------------
//	PYRCustomShaderManager.cpp
//------------------------------------------------------------------------------
//
//	Copyright (c) 2001-2015 PYR Software Ltd. All rights reserved. This document
//	is for the use of licensed users only and is subject to the terms and
//	conditions of the accompanying and/or applicable license between you and
//	PYR Software Ltd, including without limitation those terms and conditions
//	prohibiting unauthorized translation, reverse engineering, decompilation,
//	disassembly, and other inappropriate use of any software provided. Any
//	unauthorized use, copying, modification, distribution, publication or
//	disclosure of information is a violation of copyright laws. No reproduction
//	in whole or in part of this document may be made without express written
//	consent of PYR Software Ltd.
//
//
//------------------------------------------------------------------------------

#include "renderer/PYRCustomShaderManager.h"

//------------------------------------------------------------------------------

NS_CC_BEGIN

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
CustomShaderFactory::CustomShaderFactory()
{
	CustomShaderManager::getInstance()->registerFactory(this);
}

//------------------------------------------------------------------------------
CustomShaderFactory::~CustomShaderFactory()
{
	// destructor should happend only by request of CustomShaderManager, no need to unregister
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
CustomShaderFactoryBase::CustomShaderFactoryBase()
:CustomShaderFactory()
,_shader(nullptr)
{
}

//------------------------------------------------------------------------------
CustomShaderFactoryBase::~CustomShaderFactoryBase()
{
	clear();
}

//------------------------------------------------------------------------------
void CustomShaderFactoryBase::clear()
{
	if (_shader != nullptr)
	{
		_shader->release();
		_shader = nullptr;
	}
}

//------------------------------------------------------------------------------
void CustomShaderFactoryBase::recreate()
{
	if (_shader == nullptr)
	{
		createShader();
		return;
	}
	_shader->reset();
	if (!initShader(_shader))
		clear();
}

//------------------------------------------------------------------------------
GLProgram* CustomShaderFactoryBase::get()
{
	return _shader;
}

//------------------------------------------------------------------------------
void CustomShaderFactoryBase::createShader()
{
	clear();
	GLProgram* s = new GLProgram();
	if (initShader(s))
		_shader = s;
	else
		s->autorelease();
}

bool CustomShaderFactoryBase::init(cocos2d::GLProgram* shader_, const char* vertex_, const char* fragment_)
{
	if (shader_ == nullptr || vertex_ == nullptr || fragment_ == nullptr)
		return false;

	bool res = shader_->initWithByteArrays(vertex_, fragment_);
	res &= shader_->link();
	shader_->updateUniforms();
	CHECK_GL_ERROR_DEBUG();
	return res;
}



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
CustomShaderManager* CustomShaderManager::_instance(nullptr);

//------------------------------------------------------------------------------
CustomShaderManager::CustomShaderManager()
{
}

//------------------------------------------------------------------------------
CustomShaderManager::~CustomShaderManager()
{
	clear();
}

//------------------------------------------------------------------------------
CustomShaderManager* CustomShaderManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new CustomShaderManager;
	return _instance;
}

//------------------------------------------------------------------------------
void CustomShaderManager::destroyInstance()
{
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
	}
}

//------------------------------------------------------------------------------
void CustomShaderManager::clear()
{
	for (auto it = _factories.begin(); it != _factories.end(); ++it)
		delete *it;
	_factories.clear();
}

//------------------------------------------------------------------------------
void CustomShaderManager::recreate()
{
	for (auto it = _factories.begin(); it != _factories.end(); ++it)
		(*it)->recreate();
}

//------------------------------------------------------------------------------
bool CustomShaderManager::registerFactory(/*new*/ CustomShaderFactory* factory_)
{
	if (factory_ != nullptr)
		_factories.push_back(factory_);
	return true;
}




//------------------------------------------------------------------------------

NS_CC_END
