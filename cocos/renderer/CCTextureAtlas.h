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

#include <string>

#include "base/ccTypes.h"
#include "base/CCRef.h"
#include "base/ccConfig.h"

NS_CC_BEGIN

class Texture2D;
class EventCustom;
class EventListenerCustom;

/**
 * @addtogroup _2d
 * @{
 */

/** @brief @~english A class that implements a Texture Atlas.
 * Supported features:
 * - The atlas file can be a PVRTC, PNG or any other format supported by Texture2D
 * - Quads can be updated in runtime
 * - Quads can be added in runtime
 * - Quads can be removed in runtime
 * - Quads can be re-ordered in runtime
 *
 * The TextureAtlas capacity can be increased or decreased in runtime
 * OpenGL component: V3F, C4B, T2F.
 * The quads are rendered using an OpenGL ES VBO.
 * To render the quads using an interleaved vertex array list, you should modify the ccConfig.h file 
 * @~chinese 一个实现纹理地图集的类。
 * 支持的功能:
 * - atlas 文件可以是 PVRTC，PNG 或者 Texture2D 支持的任何其他图片格式。
 * - 可以在运行时更新矩形数据
 * - 可以在运行时添加矩形数据
 * - 可以在运行时删除矩形数据
 * - 可以在运行时重新排序矩形数据
 *
 * TextureAtlas 的数量可以在运行时增加或减少。
 * OpenGL 组件: V3F，C4B，T2F。
 * 矩形数据会使用 OpenGL ES VBO 来渲染。
 * 如果要使用交叉顶点数组列表来渲染矩形数据，需要修改 ccConfig.h 文件。
 * 
 * @warning @~english If you want to use TextureAtlas, you'd better setup GL status before it's rendered.
 * Otherwise, the effect of TextureAtlas will be affected by the GL status of other nodes.
 * @~chinese 如果你想使用 TextureAtlas，你最好在渲染之前设置 GL 状态。
 * 否则，TextureAtlas 的效果将受到其他节点 GL 状态的影响。
 */
class CC_DLL TextureAtlas : public Ref 
{
public:
    /** @~english Creates a TextureAtlas with an filename and with an initial capacity for Quads.
     * The TextureAtlas capacity can be increased in runtime.
     * @~chinese 使用指定的文件和初始的矩形个数上限创建一个 TextureAtlas。
     * 矩形个数上限可以在运行时增加。
     * @param file @~english The absolute/related path of file.
     * @~chinese 文件的绝对路径或相对路径。
     * @param capacity @~english Capacity for Quads.
     * @~chinese 矩形个数的上限。
     * @return @~english A TextureAtlas object.
     * @~chinese 一个 TextureAtlas 对象。
     */
    static TextureAtlas* create(const std::string& file , ssize_t capacity);

    /** @~english Creates a TextureAtlas with a previously initialized Texture2D object, and
     * with an initial capacity for n Quads.
     * The TextureAtlas capacity can be increased in runtime.
     * @~chinese 使用指定的纹理对象和矩形个数上限创建一个 TextureAtlas。
     * 矩形个数上限可以在运行时增加。
     * @param texture @~english A texture2D object pointer.
     * @~chinese 指定的纹理对象。
     * @param capacity @~english Capacity for Quads.
     * @~chinese 矩形个数的上限。
     * @return @~english A TextureAtlas object.
     * @~chinese 一个 TextureAtlas 对象。
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

    /** @~english Initializes a TextureAtlas with a filename and with a certain capacity for Quads.
     * The TextureAtlas capacity can be increased in runtime.
     * @~chinese 使用指定的文件和初始的矩形个数上限初始化 TextureAtlas。
     * 矩形个数上限可以在运行时增加。
     * @attention @~english Do not reinitialize the TextureAtlas because it will leak memory (issue #706).
     * @~chinese 不要重复初始化 TextureAtlas，会导致泄漏内存 (issue #706)。
     * @param file @~english The absolute/related path of file.
     * @~chinese 文件的绝对路径或相对路径。
     * @param capacity @~english Capacity for Quads.
     * @~chinese 矩形个数的上限。
     * @return @~english If the initialization is successful, return true; else return false.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     */
    bool initWithFile(const std::string& file, ssize_t capacity);

    /** @~english Initializes a TextureAtlas with a previously initialized Texture2D object, and
     * with an initial capacity for Quads. 
     * The TextureAtlas capacity can be increased in runtime.
     * @~chinese 使用指定的纹理对象和矩形个数上限初始化 TextureAtlas。
     * 矩形个数上限可以在运行时增加。
     * @attention @~english Do not reinitialize the TextureAtlas because it will leak memory (issue #706).
     * @~chinese 不要重复初始化 TextureAtlas，会导致泄漏内存 (issue #706)。
     * @param texture @~english A texture2D object pointer.
     * @~chinese 指定的纹理对象。
     * @param capacity @~english Capacity for Quads.
     * @~chinese 矩形个数的上限。
     * @return @~english If the initialization is successful, return true; else return false.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     */
    bool initWithTexture(Texture2D *texture, ssize_t capacity);

    /** @~english Updates a Quad (texture, vertex and color) at a certain index.
     * @~chinese 根据指定的索引值更新该矩形的数据(纹理坐标、顶点坐标和颜色)。
     * @param quad @~english Quad that are going to be rendered.
     * @~chinese 需要更新的矩形数据。
     * @param index @~english Index must be between 0 and the atlas capacity - 1.
     * @~chinese 需要查找的索引值，必须在 0 到 capacity - 1 之间。
     * @since v0.8
     */
    void updateQuad(V3F_C4B_T2F_Quad* quad, ssize_t index);

    /** @~english Inserts a Quad (texture, vertex and color) at a certain index.
     * @~chinese 在指定的索引值位置插入一个矩形数据(纹理坐标、顶点坐标和颜色)。
     * @param quad @~english Quad that are going to be rendered.
     * @~chinese 需要插入的矩形数据。
     * @param index @~english Index must be between 0 and the atlas capacity - 1.
     * @~chinese 需要插入的索引值，必须在 0 到 capacity - 1 之间。
     * @since v0.8
     */
    void insertQuad(V3F_C4B_T2F_Quad* quad, ssize_t index);

    /** @~english Inserts a c array of quads at a given index.
     * @~chinese 在指定的索引值位置插入一个矩形数据的数组。
     * @param quads @~english Quad that are going to be rendered.
     * @~chinese 需要插入的矩形数据数组的起始指针。
     * @param index @~english Index must be between 0 and the atlas capacity - 1.
     * @~chinese 需要插入的索引值，必须在 0 到 capacity - 1 之间。
     * @param amount @~english The quads array amount.
     * @~chinese 矩形数据数组中元素的个数。
     * @attention @~english This method doesn't enlarge the array when amount + index > totalQuads.
     * @~chinese 当 amount + index 大于矩形数据的上限时，此方法不会增加矩形数据的上限。
     * @since v1.1
     */
    void insertQuads(V3F_C4B_T2F_Quad* quads, ssize_t index, ssize_t amount);

    /** @~english Removes the quad that is located at a certain index and inserts it at a new index.
     * This operation is faster than removing and inserting in a quad in 2 different steps.
     * @~chinese 将指定索引值位置的矩形数据插入到另外的索引值位置。
     * 这个方法比先从指定位置删除再插入到指定位置的效率更高。
     * @param fromIndex @~english The index where the quad is from.
     * @~chinese 需要移动的矩形数据的当前索引值。
     * @param newIndex @~english The index where the quad will be inserted.
     * @~chinese 矩形数据需要插入到的新索引值。
     * @since v0.7.2
     */
    void insertQuadFromIndex(ssize_t fromIndex, ssize_t newIndex);

    /** @~english Removes a quad at a given index number.
     * The capacity remains the same, but the total number of quads to be drawn is reduced in 1.
     * @~chinese 删除指定索引值位置的矩形数据。
     * 矩形数据的上限不变，但是矩形数据的总数 -1。
     * @param index @~english The index of the quad will be removed.
     * @~chinese 需要删除的矩形数据索引值。
     * @since v0.7.2
     */
    void removeQuadAtIndex(ssize_t index);

    /** @~english Removes a amount of quads starting from index.
     * @~chinese 从指定的索引值位置删除多个矩形数据。
     * @param index @~english The start index of the quads will be removed.
     * @~chinese 需要删除的矩形数据的起始索引值。
     * @param amount @~english The amount of the quads will be removed.
     * @~chinese 需要删除的矩形数据个数。
     * @since 1.1
     */
    void removeQuadsAtIndex(ssize_t index, ssize_t amount);
    /** @~english Removes all Quads.
     * The TextureAtlas capacity remains untouched. No memory is freed.
     * The total number of quads to be drawn will be 0.
     * @~chinese 删除所有的矩形数据。
     * 矩形数据的个数上限不变，没有释放任何内存。
     * 矩形数据的总数变为 0。
     * @since v0.7.2
     */
    void removeAllQuads();

    /** @~english Resize the capacity of the TextureAtlas.
     * The new capacity can be lower or higher than the current one.
     * It returns true if the resize was successful.
     * If it fails to resize the capacity it will return false with a new capacity of 0.
     * @~chinese 调整 TextureAtlas 中矩形数据的容量。
     * 新的容量可以比当前容量高，也可以比当前容量低。
     * 如果调整成功，将返回 true。
     * 如果调整失败，将返回 false，并且容量被设置为 0。
     * @param capacity @~english Capacity for Quads.
     * @~chinese 需要调整的容量值。
     * @return @~english It returns true if the resize was successful; else return false.
     * @~chinese 如果调整成功，返回 true；否则返回 false。
     */
    bool resizeCapacity(ssize_t capacity);

    /**@~english
     * Used internally by ParticleBatchNode.
     * don't use this unless you know what you're doing.
     * @~chinese 
     * 提供给 ParticleBatchNode 内部使用的方法。
     * 不要调用这个方法，除非你知道你在做什么。
     * @since 1.1
     */
    void increaseTotalQuadsWith(ssize_t amount);

    /** @~english Moves an amount of quads from oldIndex at newIndex.
     * @~chinese 将指定的多个矩形数据从当前索引值位置移动到新的索引值位置。
     * @param oldIndex @~english The current index of the quads will be moved from.
     * @~chinese 需要移动的矩形数据的当前索引值位置。
     * @param amount @~english The amount of the quads will be moved.
     * @~chinese 需要移动的矩形数据个数。
     * @param newIndex @~english The new index of the quads will be moved to.
     * @~chinese 矩形数据需要移动到的新的索引值位置。
     * @since v1.1
     */
    void moveQuadsFromIndex(ssize_t oldIndex, ssize_t amount, ssize_t newIndex);

    /**@~english
     * Moves quads from index till totalQuads to the newIndex.
     * Used internally by ParticleBatchNode.
     * This method doesn't enlarge the array if newIndex + quads to be moved > capacity.
     * @~chinese 
     * 把从指定索引值之后的所有矩形数据移动到新的索引值位置。
     * 提供给 ParticleBatchNode 内部使用的方法。
     * 当 newIndex + 移动的矩形数据个数超过容量上限时，这个方法不会扩大数组的容量。
     * @param index @~english The current index of the quads will be moved from.
     * @~chinese 需要移动的矩形数据的当前索引值位置。
     * @param newIndex @~english The new index of the quads will be moved to.
     * @~chinese 矩形数据需要移动到的新的索引值位置。
     * @since 1.1
     */
    void moveQuadsFromIndex(ssize_t index, ssize_t newIndex);

    /**@~english
     * Ensures that after a realloc quads are still empty.
     * Used internally by ParticleBatchNode.
     * @~chinese 
     * 使用指定数量的空矩形数据，覆盖指定索引值位置之后的相应个数的矩形数据。
     * 提供给 ParticleBatchNode 内部使用的方法。
     * @param index @~english The start index of the empty quads will be filled in.
     * @~chinese 需要覆盖空矩形数据的起始索引值位置。
     * @param amount @~english The amount of the quads will be filled.
     * @~chinese 需要覆盖的矩形数据个数。
     * @since 1.1
     */
    void fillWithEmptyQuadsFromIndex(ssize_t index, ssize_t amount);

    /** @~english Draws n quads.
     * n can't be greater than the capacity of the Atlas.
     * @~chinese 绘制 n 个矩形数据。
     * n 不能大于矩形数据的个数上限。
     * @param n @~english The amount of the quads will be drawn.
     * @~chinese 需要绘制的矩形数据个数。
     */
    void drawNumberOfQuads(ssize_t n);

    /** @~english Draws n quads from an index (offset).
     * n + start can't be greater than the capacity of the atlas.
     * @~chinese 绘制指定索引值位置之后的 n 个矩形数据。
     * n + start 不能大于矩形数据的个数上限。
     * @param numberOfQuads @~english The amount of the quads will be drawn.
     * @~chinese 需要绘制的矩形数据个数。
     * @param start @~english The start index of the quads will be drawn.
     * @~chinese 需要绘制的矩形数据的起始索引值位置。
     * @since v1.0
     */
    void drawNumberOfQuads(ssize_t numberOfQuads, ssize_t start);

    /** @~english Draws all the Atlas's Quads.
     * @~chinese 绘制所有矩形数据。
     */
    void drawQuads();
    /** @~english Listen the event that renderer was recreated on Android.
     * @~chinese 在 Android 平台监听渲染器被重新创建的事件。
     */
    void listenRendererRecreated(EventCustom* event);

    /** @~english Whether or not the array buffer of the VBO needs to be updated.
     * @~chinese 判断 VBO 的数组缓冲区是否需要更新。
     * @return @~english If need update return true; else return false.
     * @~chinese 如果需要更新返回 true；否则返回 false。
     */
    inline bool isDirty(void) { return _dirty; }
    /** @~english Specify if the array buffer of the VBO needs to be updated.
     * @~chinese 设置 VBO 数组缓冲区是否需要更新。
     * @param bDirty @~english If it's need update, use true; else use false.
     * @~chinese 如果需要更新，使用 true；否则使用 false。
     */
    inline void setDirty(bool bDirty) { _dirty = bDirty; }

    /**@~english Get the description of the object.
     * @~chinese 获取对象的描述信息。
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

    /** @~english Gets the quantity of quads that are going to be drawn.
     * @~chinese 获得矩形数据的总个数。
     * @return @~english Return the amount of the quads.
     * @~chinese 返回矩形数据的总个数。
     */
    ssize_t getTotalQuads() const;
    
    /** @~english Gets the quantity of quads that can be stored with the current texture atlas size.
     * @~chinese 获取矩形数据的个数上限。
     * @return @~english Return the capacity of the quads.
     * @~chinese 返回矩形数据的个数上限。
     */
    ssize_t getCapacity() const;
    
    /** @~english Gets the texture of the texture atlas.
     * @~chinese 获取当前使用的纹理。
     * @return @~english Return the texture object is using.
     * @~chinese 返回当前使用的纹理对象。
     */
    Texture2D* getTexture() const;
    
    /** @~english Sets the texture for the texture atlas.
     * @~chinese 设置使用的纹理对象。
     * @param texture @~english The texture will be used.
     * @~chinese 需要使用的纹理对象。
     */
    void setTexture(Texture2D* texture);
    
    /** @~english Gets the quads that are going to be rendered.
     * @~chinese 获取要被渲染的矩形数据。
     * @return @~english The quads will be rendered.
     * @~chinese 要被渲染的矩形数据。
     */
    V3F_C4B_T2F_Quad* getQuads();
    
    /** @~english Sets the quads that are going to be rendered.
     * @~chinese 设置要被渲染的矩形数据。
     * @param quads @~english The quads will be rendered.
     * @~chinese 需要渲染的矩形数据。
     */
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
    /** @~english quantity of quads that are going to be drawn  @~chinese 要绘制的矩形数据个数。*/
    ssize_t _totalQuads;
    /** @~english quantity of quads that can be stored with the current texture atlas size.
     * @~chinese 可以绘制的矩形数据个数上限。
     */
    ssize_t _capacity;
    /** @~english Texture of the texture atlas  @~chinese 使用的纹理。*/
    Texture2D* _texture;
    /** @~english Quads that are going to be rendered  @~chinese 保存所有的矩形数据。*/
    V3F_C4B_T2F_Quad* _quads;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _rendererRecreatedListener;
#endif
};

// end of textures group
/// @}

NS_CC_END

#endif //__CCTEXTURE_ATLAS_H__


