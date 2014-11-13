/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SCRIPT_COMPILER_H__
#define __PU_SCRIPT_COMPILER_H__

#include "OgreScriptCompiler.h"

namespace ParticleUniverse
{
	// If the Ogre renderer is replaced by another renderer, the types below must be re-implemented.
	typedef Ogre::ScriptCompiler ScriptCompiler;
	typedef Ogre::ScriptCompilerManager ScriptCompilerManager;
	typedef Ogre::ObjectAbstractNode ObjectAbstractNode;
	typedef Ogre::AbstractNodePtr AbstractNodePtr;
	typedef Ogre::AbstractNodeList AbstractNodeList;
	typedef Ogre::PropertyAbstractNode PropertyAbstractNode;

	typedef Ogre::AbstractNodeType AbstractNodeType;
	static const AbstractNodeType ANT_PROPERTY = Ogre::ANT_PROPERTY;
	static const AbstractNodeType ANT_OBJECT = Ogre::ANT_OBJECT;
}
#endif
