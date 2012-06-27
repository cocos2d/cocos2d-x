/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "ccTypes.h"
#include "cocoa/CCObject.h"
#include "ccConfig.h"
#include <string>

NS_CC_BEGIN

class CCTexture2D;

/**
 * @addtogroup textures
 * @{
 */

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
    GLushort*           m_pIndices;
#if CC_TEXTURE_ATLAS_USE_VAO
    GLuint              m_uVAOname;
#endif
    GLuint              m_pBuffersVBO[2]; //0: vertex  1: indices
    bool                m_bDirty; //indicates whether or not the array buffer of the VBO needs to be updated


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

    const char* description();

    /** creates a TextureAtlas with an filename and with an initial capacity for Quads.
    * The TextureAtlas capacity can be increased in runtime.
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCTextureAtlas * textureAtlasWithFile(const char* file , unsigned int capacity);

    /** creates a TextureAtlas with an filename and with an initial capacity for Quads.
    * The TextureAtlas capacity can be increased in runtime.
    */
    static CCTextureAtlas* create(const char* file , unsigned int capacity);

    /** initializes a TextureAtlas with a filename and with a certain capacity for Quads.
    * The TextureAtlas capacity can be increased in runtime.
    *
    * WARNING: Do not reinitialize the TextureAtlas because it will leak memory (issue #706)
    */
    bool initWithFile(const char* file, unsigned int capacity);

    /** creates a TextureAtlas with a previously initialized Texture2D object, and
    * with an initial capacity for n Quads. 
    * The TextureAtlas capacity can be increased in runtime.
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCTextureAtlas * textureAtlasWithTexture(CCTexture2D *texture, unsigned int capacity);

   /** creates a TextureAtlas with a previously initialized Texture2D object, and
    * with an initial capacity for n Quads. 
    * The TextureAtlas capacity can be increased in runtime.
    */
    static CCTextureAtlas* create(CCTexture2D *texture, unsigned int capacity);


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

    /** Inserts a c array of quads at a given index
     index must be between 0 and the atlas capacity - 1
     this method doesn't enlarge the array when amount + index > totalQuads
     @since v1.1
    */
    void insertQuads(ccV3F_C4B_T2F_Quad* quads, unsigned int index, unsigned int amount);

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

    /** removes a amount of quads starting from index
        @since 1.1
     */
    void removeQuadsAtIndex(unsigned int index, unsigned int amount);
    /** removes all Quads.
    The TextureAtlas capacity remains untouched. No memory is freed.
    The total number of quads to be drawn will be 0
    @since v0.7.2
    */
    void removeAllQuads();


    /** resize the capacity of the CCTextureAtlas.
    * The new capacity can be lower or higher than the current one
    * It returns YES if the resize was successful.
    * If it fails to resize the capacity it will return NO with a new capacity of 0.
    */
    bool resizeCapacity(unsigned int n);

    /**
     Used internally by CCParticleBatchNode
     don't use this unless you know what you're doing
     @since 1.1
    */
    void increaseTotalQuadsWith(unsigned int amount);

    /** Moves an amount of quads from oldIndex at newIndex
     @since v1.1
     */
    void moveQuadsFromIndex(unsigned int oldIndex, unsigned int amount, unsigned int newIndex);

    /**
     Moves quads from index till totalQuads to the newIndex
     Used internally by CCParticleBatchNode
     This method doesn't enlarge the array if newIndex + quads to be moved > capacity
     @since 1.1
    */
    void moveQuadsFromIndex(unsigned int index, unsigned int newIndex);

    /**
     Ensures that after a realloc quads are still empty
     Used internally by CCParticleBatchNode
     @since 1.1
    */
    void fillWithEmptyQuadsFromIndex(unsigned int index, unsigned int amount);

    /** draws n quads
    * n can't be greater than the capacity of the Atlas
    */
    void drawNumberOfQuads(unsigned int n);

    /** draws n quads from an index (offset).
    n + start can't be greater than the capacity of the atlas

    @since v1.0
    */
    void drawNumberOfQuads(unsigned int n, unsigned int start);

    /** draws all the Atlas's Quads
    */
    void drawQuads();
    /** listen the event that coming to foreground on Android
     */
    void listenBackToForeground(CCObject *obj);
private:
    void setupIndices();
    void mapBuffers();
#if CC_TEXTURE_ATLAS_USE_VAO
    void setupVBOandVAO();
#else
    void setupVBO();
#endif
};

// end of textures group
/// @}

NS_CC_END

#endif //__CCTEXTURE_ATLAS_H__


