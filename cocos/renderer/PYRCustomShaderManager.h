//------------------------------------------------------------------------------
//	PYRCustomShaderManager.h
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

#if !defined( __PYRCustomShaderManager_h_included__ )
#define __PYRCustomShaderManager_h_included__

//------------------------------------------------------------------------------

#include "renderer/CCGLProgram.h"
#include <list>

//------------------------------------------------------------------------------

NS_CC_BEGIN

//------------------------------------------------------------------------------
// base factory interface
class CC_DLL CustomShaderFactory 
{
public:
	// constructor
	CustomShaderFactory();

	// destructor
	virtual ~CustomShaderFactory();

	// recreate shader
	virtual void recreate() = 0;

	// return shader
	virtual GLProgram* get() = 0;
};


//------------------------------------------------------------------------------
// class to manage custom shader factories
class CC_DLL CustomShaderManager
{
public:
	static CustomShaderManager* getInstance();
	
	static void destroyInstance();

	void clear();
	void recreate();
	bool registerFactory(/*new*/ CustomShaderFactory* factory_);

public:
	CustomShaderManager();
	~CustomShaderManager();

protected:
	std::list<CustomShaderFactory*>	_factories;

	static CustomShaderManager*		_instance;
};



//------------------------------------------------------------------------------
// create/manage one custom shader, base implementation. Retain shader.
class CC_DLL CustomShaderFactoryBase : protected CustomShaderFactory
{
protected:
	// recreate shader
	virtual void recreate() override;

	// return shader
	virtual GLProgram* get() override;

	// init shader data
	virtual bool initShader(GLProgram* shader_) = 0;

protected:
	// constructor
	CustomShaderFactoryBase();

	// destructor
	virtual ~CustomShaderFactoryBase();

	// create shader
	void createShader();

	// clear shader reference
	void clear();

	// standard init function
	bool init(GLProgram* shader_, const char* vertex_, const char* fragment_);

protected:
	GLProgram* _shader;  // retained
};


//------------------------------------------------------------------------------

NS_CC_END

//------------------------------------------------------------------------------
#endif // !defined( __PYRCustomShaderManager_h_included__ )
