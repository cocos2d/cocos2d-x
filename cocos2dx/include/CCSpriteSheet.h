/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009-2010 Ricardo Quesada
Copyright (C) 2009      Matt Oswald

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

#ifndef __SPRITE_CCSPRITE_SHEET_H__
#define __SPRITE_CCSPRITE_SHEET_H__

#include "CCSpriteBatchNode.h"

namespace   cocos2d {
	/* Added only to prevent GCC compile warnings
	Will be removed in v1.1
	*/
	class CC_DLL CCSpriteSheetInternalOnly : public CCSpriteBatchNode
	{
	};

	/** @brief CCSpriteSheet is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
	* (often known as "batch draw").
	*
	* A CCSpriteSheet can reference one and only one texture (one image file, one texture atlas).
	* Only the CCSprites that are contained in that texture can be added to the CCSpriteSheet.
	* All CCSprites added to a CCSpriteSheet are drawn in one OpenGL ES draw call.
	* If the CCSprites are not added to a CCSpriteSheet then an OpenGL ES draw call will be needed for each one, which is less efficient.
	*
	*
	* Limitations:
	*  - The only object that is accepted as child (or grandchild) is CCSprite or any subclass of CCSprite. eg: particles, labels and layer can't be added to a CCSpriteSheet.
	*  - Either all its children are Aliased or Antialiased. It can't be a mix. This is because "alias" is a property of the texture, and all the sprites share the same texture.
	* 
	* @since v0.7.1
	* @deprecated Use CCSpriteBatchNode instead. This class will be removed in v1.1
	*/
	class CC_DLL CCSpriteSheet: public CCSpriteSheetInternalOnly
	{
	};

}//namespace   cocos2d 

#endif // __SPRITE_CCSPRITE_SHEET_H__
