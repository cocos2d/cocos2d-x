/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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

#ifndef __CCTEXTURE_ATLAS_H__
#define __CCTEXTURE_ATLAS_H__

#include <string>
#include "ccTypes.h"
#include "CCObject.h"
#include "ccConfig.h"

namespace   cocos2d {
class CCTexture2D;

/** @brief A class that implements a Texture Atlas.
Supported features:
* The atlas file can be a PVRTC, PNG or any other fomrat supported by Texture2D
* Quads can be udpated in runtime
* Quads can be added in runtime
* Quads can be removed in runtime
* Quads can be re-ordered in runtime
* The TextureAtlas capacity can be increased or decreased in runtime
* OpenGL component: V3F, C4B, T2F.
The quads are rendered using an OpenGL ES VBO.
To render the quads using an interleaved vertex array list, you should modify the ccConfig.h file 
*/
class CC_DLL CCTextureAtlas : public CCObject 
{
protected:
	GLushort			*m_pIndices;
#if CC_USES_VBO
	GLuint				m_pBuffersVBO[2]; //0: vertex  1: indices
#endif // CC_USES_VBO

	/** quantity of quads that are going to be drawn */
	CC_PROPERTY_READONLY(unsigned int, m_uTotalQuads, TotalQuads)
	/** quantity of quads that can be stored with the current texture atlas size */
	CC_PROPERTY_READONLY(unsigned int, m_uCapacity, Capacity)
	/** Texture of the texture atlas */
	CC_PROPERTY(CCTexture2D *, m_pTexture, Texture)
	/** Quads that are going to be rendered */
	CC_PROPERTY(ccV3F_C4B_T2F_Quad *, m_pQuads, Quads)

public:

	CCTextureAtlas();
	virtual ~CCTextureAtlas();

	char * description();

	/** creates a TextureAtlas with an filename and with an initial capacity for Quads.
	* The TextureAtlas capacity can be increased in runtime.
	*/
	static CCTextureAtlas * textureAtlasWithFile(const char* file , unsigned int capacity);

	/** initializes a TextureAtlas with a filename and with a certain capacity for Quads.
	* The TextureAtlas capacity can be increased in runtime.
	*
	* WARNING: Do not reinitialize the TextureAtlas because it will leak memory (issue #706)
	*/
	bool initWithFile(const char* file, unsigned int capacity);

	/** creates a TextureAtlas with a previously initialized Texture2D object, and
	* with an initial capacity for n Quads. 
	* The TextureAtlas capacity can be increased in runtime.
	*/
	static CCTextureAtlas * textureAtlasWithTexture(CCTexture2D *texture, unsigned int capacity);

	/** initializes a TextureAtlas with a previously initialized Texture2D object, and
	* with an initial capacity for Quads. 
	* The TextureAtlas capacity can be increased in runtime.
	*
	* WARNING: Do not reinitialize the TextureAtlas because it will leak memory (issue #706)
	*/
	bool initWithTexture(CCTexture2D *texture, unsigned int capacity);

	/** updates a Quad (texture, vertex and color) at a certain index
	* index must be between 0 and the atlas capacity - 1
	@since v0.8
	*/
	void updateQuad(ccV3F_C4B_T2F_Quad* quad, unsigned int index);

	/** Inserts a Quad (texture, vertex and color) at a certain index
	index must be between 0 and the atlas capacity - 1
	@since v0.8
	*/
	void insertQuad(ccV3F_C4B_T2F_Quad* quad, unsigned int index);

	/** Removes the quad that is located at a certain index and inserts it at a new index
	This operation is faster than removing and inserting in a quad in 2 different steps
	@since v0.7.2
	*/
	void insertQuadFromIndex(unsigned int fromIndex, unsigned int newIndex);

	/** removes a quad at a given index number.
	The capacity remains the same, but the total number of quads to be drawn is reduced in 1
	@since v0.7.2
	*/
	void removeQuadAtIndex(unsigned int index);

	/** removes all Quads.
	The TextureAtlas capacity remains untouched. No memory is freed.
	The total number of quads to be drawn will be 0
	@since v0.7.2
	*/
	void removeAllQuads();


	/** resize the capacity of the Texture Atlas.
	* The new capacity can be lower or higher than the current one
	* It returns YES if the resize was successful.
	* If it fails to resize the capacity it will return NO with a new capacity of 0.
	*/
	bool resizeCapacity(unsigned int n);


	/** draws n quads
	* n can't be greater than the capacity of the Atlas
	*/
	void drawNumberOfQuads(unsigned int n);

	/** draws all the Atlas's Quads
	*/
	void drawQuads();
private:
	void initIndices();
};
}//namespace   cocos2d 

#endif //__CCTEXTURE_ATLAS_H__


