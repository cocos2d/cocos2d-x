/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCTEXTURE_ATLAS_H__
#define __CCTEXTURE_ATLAS_H__

#include "ccTypes.h"
#include "CCRef.h"
#include "ccConfig.h"
#include <string>

NS_CC_BEGIN

class Texture2D;
class EventCustom;
class EventListenerCustom;

/**
 * @addtogroup textures
 * @{
 */

/** @brief A class that implements a Texture Atlas.
Supported features:
* The atlas file can be a PVRTC, PNG or any other format supported by Texture2D
* Quads can be updated in runtime
* Quads can be added in runtime
* Quads can be removed in runtime
* Quads can be re-ordered in runtime
* The TextureAtlas capacity can be increased or decreased in runtime
* OpenGL component: V3F, C4B, T2F.
The quads are rendered using an OpenGL ES VBO.
To render the quads using an interleaved vertex array list, you should modify the ccConfig.h file 
*/
class CC_DLL TextureAtlas : public Ref 
{
public:
    /** creates a TextureAtlas with an filename and with an initial capacity for Quads.
     * The TextureAtlas capacity can be increased in runtime.
     */
    static TextureAtlas* create(const std::string& file , ssize_t capacity);

    /** creates a TextureAtlas with a previously initialized Texture2D object, and
     * with an initial capacity for n Quads.
     * The TextureAtlas capacity can be increased in runtime.
     */
    static TextureAtlas* createWithTexture(Texture2D *texture, ssize_t capacity);
    /**
     * @js ctor
     */
    TextureAtlas();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TextureAtlas();

    /** initializes a TextureAtlas with a filename and with a certain capacity for Quads.
    * The TextureAtlas capacity can be increased in runtime.
    *
    * WARNING: Do not reinitialize the TextureAtlas because it will leak memory (issue #706)
    */
    bool initWithFile(const std::string& file, ssize_t capacity);

    /** initializes a TextureAtlas with a previously initialized Texture2D object, and
    * with an initial capacity for Quads. 
    * The TextureAtlas capacity can be increased in runtime.
    *
    * WARNING: Do not reinitialize the TextureAtlas because it will leak memory (issue #706)
    */
    bool initWithTexture(Texture2D *texture, ssize_t capacity);

    /** updates a Quad (texture, vertex and color) at a certain index
    * index must be between 0 and the atlas capacity - 1
    @since v0.8
    */
    void updateQuad(V3F_C4B_T2F_Quad* quad, ssize_t index);

    /** Inserts a Quad (texture, vertex and color) at a certain index
    index must be between 0 and the atlas capacity - 1
    @since v0.8
    */
    void insertQuad(V3F_C4B_T2F_Quad* quad, ssize_t index);

    /** Inserts a c array of quads at a given index
     index must be between 0 and the atlas capacity - 1
     this method doesn't enlarge the array when amount + index > totalQuads
     @since v1.1
    */
    void insertQuads(V3F_C4B_T2F_Quad* quads, ssize_t index, ssize_t amount);

    /** Removes the quad that is located at a certain index and inserts it at a new index
    This operation is faster than removing and inserting in a quad in 2 different steps
    @since v0.7.2
    */
    void insertQuadFromIndex(ssize_t fromIndex, ssize_t newIndex);

    /** removes a quad at a given index number.
    The capacity remains the same, but the total number of quads to be drawn is reduced in 1
    @since v0.7.2
    */
    void removeQuadAtIndex(ssize_t index);

    /** removes a amount of quads starting from index
        @since 1.1
     */
    void removeQuadsAtIndex(ssize_t index, ssize_t amount);
    /** removes all Quads.
    The TextureAtlas capacity remains untouched. No memory is freed.
    The total number of quads to be drawn will be 0
    @since v0.7.2
    */
    void removeAllQuads();

    /** resize the capacity of the TextureAtlas.
    * The new capacity can be lower or higher than the current one
    * It returns true if the resize was successful.
    * If it fails to resize the capacity it will return false with a new capacity of 0.
    */
    bool resizeCapacity(ssize_t capacity);

    /**
     Used internally by ParticleBatchNode
     don't use this unless you know what you're doing
     @since 1.1
    */
    void increaseTotalQuadsWith(ssize_t amount);

    /** Moves an amount of quads from oldIndex at newIndex
     @since v1.1
     */
    void moveQuadsFromIndex(ssize_t oldIndex, ssize_t amount, ssize_t newIndex);

    /**
     Moves quads from index till totalQuads to the newIndex
     Used internally by ParticleBatchNode
     This method doesn't enlarge the array if newIndex + quads to be moved > capacity
     @since 1.1
    */
    void moveQuadsFromIndex(ssize_t index, ssize_t newIndex);

    /**
     Ensures that after a realloc quads are still empty
     Used internally by ParticleBatchNode
     @since 1.1
    */
    void fillWithEmptyQuadsFromIndex(ssize_t index, ssize_t amount);

    /** draws n quads
    * n can't be greater than the capacity of the Atlas
    */
    void drawNumberOfQuads(ssize_t n);

    /** draws n quads from an index (offset).
    n + start can't be greater than the capacity of the atlas

    @since v1.0
    */
    void drawNumberOfQuads(ssize_t numberOfQuads, ssize_t start);

    /** draws all the Atlas's Quads
    */
    void drawQuads();
    /** listen the event that coming to foreground on Android
     */
    void listenBackToForeground(EventCustom* event);

    /** whether or not the array buffer of the VBO needs to be updated*/
    inline bool isDirty(void) { return _dirty; }
    /** specify if the array buffer of the VBO needs to be updated */
    inline void setDirty(bool bDirty) { _dirty = bDirty; }
    /**
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

    /** Gets the quantity of quads that are going to be drawn */
    ssize_t getTotalQuads() const;
    
    /** Gets the quantity of quads that can be stored with the current texture atlas size */
    ssize_t getCapacity() const;
    
    /** Gets the texture of the texture atlas */
    Texture2D* getTexture() const;
    
    /** Sets the texture for the texture atlas */
    void setTexture(Texture2D* texture);
    
    /** Gets the quads that are going to be rendered */
    V3F_C4B_T2F_Quad* getQuads();
    
    /** Sets the quads that are going to be rendered */
    void setQuads(V3F_C4B_T2F_Quad* quads);
    
private:
    void renderCommand();

    void setupIndices();
    void mapBuffers();
    void setupVBOandVAO();
    void setupVBO();

protected:
    GLushort*           _indices;
    GLuint              _VAOname;
    GLuint              _buffersVBO[2]; //0: vertex  1: indices
    bool                _dirty; //indicates whether or not the array buffer of the VBO needs to be updated
    /** quantity of quads that are going to be drawn */
    ssize_t _totalQuads;
    /** quantity of quads that can be stored with the current texture atlas size */
    ssize_t _capacity;
    /** Texture of the texture atlas */
    Texture2D* _texture;
    /** Quads that are going to be rendered */
    V3F_C4B_T2F_Quad* _quads;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _backToForegroundlistener;
#endif
};

// end of textures group
/// @}

NS_CC_END

#endif //__CCTEXTURE_ATLAS_H__


