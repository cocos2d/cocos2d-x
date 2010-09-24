/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCNode.h"
#include "CCProtocols.h"
#include "CCTextureAtlas.h"
#include "ccMacros.h"

namespace cocos2d {

	class CCSprite;
	class CCTexture2D;

	/** CCSpriteBatchNode is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
	* (often known as "batch draw").
	*
	* A CCSpriteBatchNode can reference one and only one texture (one image file, one texture atlas).
	* Only the CCSprites that are contained in that texture can be added to the CCSpriteBatchNode.
	* All CCSprites added to a CCSpriteBatchNode are drawn in one OpenGL ES draw call.
	* If the CCSprites are not added to a CCSpriteBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient.
	*
	*
	* Limitations:
	*  - The only object that is accepted as child (or grandchild, grand-grandchild, etc...) is CCSprite or any subclass of CCSprite. eg: particles, labels and layer can't be added to a CCSpriteBatchNode.
	*  - Either all its children are Aliased or Antialiased. It can't be a mix. This is because "alias" is a property of the texture, and all the sprites share the same texture.
	* 
	* @since v0.7.1
	*/
	class CCX_DLL CCSpriteBatchNode : public CCNode, public CCTextureProtocol
	{
	protected:
		/** returns the TextureAtlas that is used */
		CCTextureAtlas	*m_pTextureAtlas;
		/** conforms to CCTextureProtocol protocol */
		ccBlendFunc		m_tBlendFunc;
		/** descendants (children, gran children, etc) */
		/// chneyan @todo CCArray	*descendants_; what is CCArray

	public:
		CCSpriteBatchNode();
		virtual ~CCSpriteBatchNode();
		/** creates a CCSpriteBatchNode with a texture2d and a default capacity of 29 children.
		The capacity will be increased in 33% in runtime if it run out of space.
		*/
		CCSpriteBatchNode * batchNodeWithTexture(CCTexture2D *texture);
		CCSpriteBatchNode * spriteSheetWithTexture(CCTexture2D *texture);// DEPRECATED_ATTRIBUTE;

		/** creates a CCSpriteBatchNode with a texture2d and capacity of children.
		The capacity will be increased in 33% in runtime if it run out of space.
		*/
		CCSpriteBatchNode * batchNodeWithTexture(CCTexture2D *texture, unsigned int capacity);
		CCSpriteBatchNode * spriteSheetWithTexture(CCTexture2D *texture, unsigned int capacity); //DEPRECATED_ATTRIBUTE;

		/** creates a CCSpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) with a default capacity of 29 children.
		The capacity will be increased in 33% in runtime if it run out of space.
		The file will be loaded using the TextureMgr.
		*/
		CCSpriteBatchNode * batchNodeWithFile(const char * fileImage);
		CCSpriteBatchNode * spriteSheetWithFile(const char * fileImage);// DEPRECATED_ATTRIBUTE;

		/** creates a CCSpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and capacity of children.
		The capacity will be increased in 33% in runtime if it run out of space.
		The file will be loaded using the TextureMgr.
		*/
		CCSpriteBatchNode * batchNodeWithFile(const char *fileImage, unsigned int capacity);
		CCSpriteBatchNode * spriteSheetWithFile(const char *fileImage, unsigned int capacity);//DEPRECATED_ATTRIBUTE;

		/** initializes a CCSpriteBatchNode with a texture2d and capacity of children.
		The capacity will be increased in 33% in runtime if it run out of space.
		*/
		bool initWithTexture(CCTexture2D *texture, unsigned int capacity);
		/** initializes a CCSpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and a capacity of children.
		The capacity will be increased in 33% in runtime if it run out of space.
		The file will be loaded using the TextureMgr.
		*/
		bool initWithFile(const char *fileImage, unsigned int capacity);

		void increaseAtlasCapacity();

		/** creates an sprite with a rect in the CCSpriteBatchNode.
		It's the same as:
		- create an standard CCSsprite
		- set the usingSpriteSheet = YES
		- set the textureAtlas to the same texture Atlas as the CCSpriteBatchNode
		@deprecated Use [CCSprite spriteWithBatchNode:rect:] instead;
		*/
		CCSprite* createSpriteWithRect(CGRect rect);// DEPRECATED_ATTRIBUTE;

		/** initializes a previously created sprite with a rect. This sprite will have the same texture as the CCSpriteBatchNode.
		It's the same as:
		- initialize an standard CCSsprite
		- set the usingBatchNode = YES
		- set the textureAtlas to the same texture Atlas as the CCSpriteBatchNode
		@since v0.99.0
		@deprecated Use [CCSprite initWithBatchNode:rect:] instead;
		*/ 
		void initSprite(CCSprite* sprite, CGRect rect);// DEPRECATED_ATTRIBUTE;

		/** removes a child given a certain index. It will also cleanup the running actions depending on the cleanup parameter.
		@warning Removing a child from a CCSpriteBatchNode is very slow
		*/
		void removeChildAtIndex(int index, bool cleanup);

		/** removes a child given a reference. It will also cleanup the running actions depending on the cleanup parameter.
		@warning Removing a child from a CCSpriteBatchNode is very slow
		*/
		void removeChild(CCSprite *sprite, bool cleanup);

		void insertChild(CCSprite *child, int inAtlasAtIndex);
		void removeSpriteFromAtlas(CCSprite *sprite);

		unsigned int rebuildIndexInOrder(CCSprite *parent, unsigned int atlasIndex);
		unsigned int atlasIndexForChild(CCSprite *sprite, int z);
		//super methods;
		virtual CCTexture2D *getTexture();
		virtual void setTexture(CCTexture2D *texture);
		virtual ccBlendFunc getBlendFunc();
		virtual void setBlendFunc(ccBlendFunc blendFunc);
	};
} // namespace cocos2d