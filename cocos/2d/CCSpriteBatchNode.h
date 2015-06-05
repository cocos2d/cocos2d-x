/****************************************************************************
Copyright (c) 2009-2010 Ricardo Quesada
Copyright (c) 2009      Matt Oswald
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

#ifndef __CC_SPRITE_BATCH_NODE_H__
#define __CC_SPRITE_BATCH_NODE_H__

#include <vector>

#include "2d/CCNode.h"
#include "base/CCProtocols.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCBatchCommand.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */


class Sprite;

/** @~english SpriteBatchNode is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
 * (often known as "batch draw").
 *
 * A SpriteBatchNode can reference one and only one texture (one image file, one texture atlas).
 * Only the Sprites that are contained in that texture can be added to the SpriteBatchNode.
 * All Sprites added to a SpriteBatchNode are drawn in one OpenGL ES draw call.
 * If the Sprites are not added to a SpriteBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient.
 *
 *
 * Limitations:
 *  - The only object that is accepted as child (or grandchild, grand-grandchild, etc...) is Sprite or any subclass of Sprite. eg: particles, labels and layer can't be added to a SpriteBatchNode.
 *  - Either all its children are Aliased or Antialiased. It can't be a mix. This is because "alias" is a property of the texture, and all the sprites share the same texture.
 *
 * @~chinese SpriteBatchNode 是批处理节点:如果它包含子节点，它将通过一次 OpenGL 调用绘制所有子节点。
 * (通常被称为“批处理绘制”)。
 * 
 * 一个 SpriteBatchNode 可以引用一个且只有一个纹理(一个图像文件, 或者一个纹理地图集)。
 * 只有当 Sprite 使用的纹理与 SpriteBatchNode 一致时才能添加为 SpriteBatchNode 的子节点。
 * 所有添加到 SpriteBatchNode 的子节点会通过一次 OpenGL 调用全部绘制出来。
 * 如果 Sprite 没有添加到 SpriteBatchNode，那么一次 OpenGL 调用只能绘制一个 Sprite，这样效率是很低的。
 * 
 * 
 * 限制:
 * - 只有 Sprite 或者 Sprite 子类的实例化对象可以做为 SpriteBatchNode 的子节点。比如：particle，label 和 layer 不能做为 SpriteBatchNode 的子节点。
 * - 所有的子节点要么都有别名，要么都没有别名，不能混合使用。因为“别名”是纹理的属性，而所有的子节点共用同一个纹理。
 * 
 * @since v0.7.1
 */
class CC_DLL SpriteBatchNode : public Node, public TextureProtocol
{
    static const int DEFAULT_CAPACITY = 29;

public:
    /** @~english Creates a SpriteBatchNode with a texture2d and capacity of children.
     * The capacity will be increased in 33% in runtime if it runs out of space.
     *
     * @~chinese 使用指定的纹理与子节点数量创建一个 SpriteBatchNode。
     * 如果运行过程中添加的子节点数超过指定的上限，则上限增加 33%%。
     * 
     * @param tex @~english A texture2d.
     * @~chinese 指定的纹理实例。
     * @param capacity @~english The capacity of children.
     * @~chinese 子节点数量上限。
     * @return @~english Return an autorelease object.
     * @~chinese 返回一个 SpriteBatchNode 实例（已被 autorelease ）。
     */
    static SpriteBatchNode* createWithTexture(Texture2D* tex, ssize_t capacity = DEFAULT_CAPACITY);

    /** @~english Creates a SpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and capacity of children.
     * The capacity will be increased in 33% in runtime if it runs out of space.
     * The file will be loaded using the TextureMgr.
     *
     * @~chinese 使用指定的图片文件（.png，.jpeg，.pvr等）和子节点上限创建一个 SpriteBatchNode。
     * 如果运行过程中添加的子节点数超过指定的上限，则上限增加 33%%。
     * 图片文件会通过 TextureMgr 加载。
     * 
     * @param fileImage @~english A file image (.png, .jpeg, .pvr, etc).
     * @~chinese 图片文件路径（.png，.jpeg，.pvr等）。
     * @param capacity @~english The capacity of children.
     * @~chinese 子节点数量上限。
     * @return @~english Return an autorelease object.
     * @~chinese 返回一个 SpriteBatchNode 实例（已被 autorelease ）。
     */
    static SpriteBatchNode* create(const std::string& fileImage, ssize_t capacity = DEFAULT_CAPACITY);


    /** @~english Returns the TextureAtlas object. 
     *
     * @~chinese 获取使用的 TextureAtlas 实例。
     * 
     * @return @~english The TextureAtlas object.
     * @~chinese TextureAtlas 实例。
     */
    inline TextureAtlas* getTextureAtlas() { return _textureAtlas; }

    /** @~english Sets the TextureAtlas object. 
     *
     * @~chinese 设置 TextureAtlas 实例。
     * 
     * @param textureAtlas @~english The TextureAtlas object.
     * @~chinese TextureAtlas 实例。
     */
    inline void setTextureAtlas(TextureAtlas* textureAtlas)
    { 
        if (textureAtlas != _textureAtlas)
        {
            CC_SAFE_RETAIN(textureAtlas);
            CC_SAFE_RELEASE(_textureAtlas);
            _textureAtlas = textureAtlas;
        }
    }

    /** @~english Returns an array with the descendants (children, gran children, etc.).
     * This is specific to BatchNode. In order to use the children, use getChildren() instead.
     * 
     * @~chinese 返回子节点树的平铺数组（子节点，子节点的子节点...）。
     * 这是 SpriteBatchNode 的定制接口。如果要获取子节点，请使用 getChildren()。
     * 
     * @return @~english An array with the descendants (children, gran children, etc.).
     * @~chinese 子节点树的平铺数组。
     */
    inline const std::vector<Sprite*>& getDescendants() const { return _descendants; }

    /** @~english Increase the Atlas Capacity.  @~chinese 增加 Atlas 的数量上限。*/
    void increaseAtlasCapacity();

    /** @~english Removes a child given a certain index. It will also cleanup the running actions depending on the cleanup parameter.
     *
     * @~chinese 删除指定索引值的子节点。可以通过参数 doCleanup 指定是否清理子节点相关的 action。
     * 
     * @param index @~english A certain index.
     * @~chinese 需要删除的子节点索引值。
     * @param doCleanup @~english Whether or not to cleanup the running actions.
     * @~chinese 是否要清理子节点相关的 action。
     * @warning @~english Removing a child from a SpriteBatchNode is very slow.
     * @~chinese 从 SpriteBatchNode 删除子节点比较慢。
     */
    void removeChildAtIndex(ssize_t index, bool doCleanup);
    
    /** @~english Append the child. 
     *
     * @~chinese 增加子节点。
     * 
     * @param sprite @~english A Sprite.
     * @~chinese 需要增加的子节点。
     */
    void appendChild(Sprite* sprite);
    
    /** @~english Remove a sprite from Atlas. 
     *
     * @~chinese 从 Atlas 中删除一个 Sprite。
     * 
     * @param sprite @~english A Sprite.
     * @~chinese 需要删除的 Sprite。
     */
    void removeSpriteFromAtlas(Sprite *sprite);
    
    /** @~english Rebuild index with a sprite all child. 
     *
     * @~chinese 重新构建所有子节点的索引。
     * 
     * @param parent @~english The parent sprite.
     * @~chinese 需要更新的 Sprite。
     * @param index @~english The child index.
     * @~chinese 需要更新的索引值
     * @return @~english Index.
     * @~chinese 返回更新后的索引值
     */
    ssize_t rebuildIndexInOrder(Sprite *parent, ssize_t index);
    
    /** @~english Get the Max image block index,in all child.
     *
     * @~chinese 获取所有子节点中，Atlas 的最大索引值。
     * 
     * @param sprite @~english The parent sprite.
     * @~chinese 父节点
     * @return @~english Index.
     * @~chinese 索引值
     */
    ssize_t highestAtlasIndexInChild(Sprite *sprite);
    
    /** @~english Get the Min image block index,in all child. 
     *
     * @~chinese 获取所有子节点中，Atlas 的最小索引值。
     * 
     * @param sprite @~english The parent sprite.
     * @~chinese 父节点
     * @return @~english Index.
     * @~chinese 索引值
     */
    ssize_t lowestAtlasIndexInChild(Sprite *sprite);
    
    /** @~english Get the nearest index from the sprite in z.
     *
     * @~chinese 获取与指定的 z 值最接近的 Atlas 索引值。
     * 
     * @param sprite @~english The parent sprite.
     * @~chinese 父节点
     * @param z @~english Z order for drawing priority.
     * @~chinese 控制绘制顺序的 z 值
     * @return @~english Index.
     * @~chinese 索引值
     */
    ssize_t atlasIndexForChild(Sprite *sprite, int z);
    /* @~english Sprites use this to start sortChildren, don't call this manually.  @~chinese 精灵使用这个sortChildren开始,不称之为手动。*/
    void reorderBatch(bool reorder);

    //
    // Overrides
    //
    // TextureProtocol
    virtual Texture2D* getTexture() const override;
    virtual void setTexture(Texture2D *texture) override;
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    /**
    * @lua NA
    */
    virtual const BlendFunc& getBlendFunc() const override;

    /**
     * @js NA
     */
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    
    using Node::addChild;
    virtual void addChild(Node * child, int zOrder, int tag) override;
    virtual void addChild(Node * child, int zOrder, const std::string &name) override;
    virtual void reorderChild(Node *child, int zOrder) override;
        
	virtual void removeChild(Node *child, bool cleanup) override;
    /**
     * @js NA
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
	virtual void sortAllChildren() override;
	/**
	* @js NA
	*/
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	/**
	* @js NA
	*/
    virtual std::string getDescription() const override;

    /** @~english Inserts a quad at a certain index into the texture atlas. The Sprite won't be added into the children array.
     * This method should be called only when you are dealing with very big AtlasSrite and when most of the Sprite won't be updated.
     * For example: a tile map (TMXMap) or a label with lots of characters (LabelBMFont).
     * @~chinese 从指定的 Sprite 对象获取 Atlas 数据并插入到指定的索引值位置，Sprite 对象不会被添加为子节点。
     * 只有当需要处理很大的 AtlasSrite 并且其中大部分 Sprite 都不会更新的情况，可以调用这个方法。
     * 例如：一个 tile map(TMXMap) 或者包含很多字符的 label (LableBMFont)。
     */
    void insertQuadFromSprite(Sprite *sprite, ssize_t index);
    /* @~english This is the opposite of "addQuadFromSprite".
     * It add the sprite to the children and descendants array, but it doesn't update add it to the texture atlas
     * @~chinese 这是与 "addQuadFromSprite" 相反的方法.
     * 此方法将 Sprite 添加到子节点中，但是并不会更新 Atlas 数据。
     */
    SpriteBatchNode * addSpriteWithoutQuad(Sprite *child, int z, int aTag);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    SpriteBatchNode();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~SpriteBatchNode();
    
    /** @~english initializes a SpriteBatchNode with a texture2d and capacity of children.
     The capacity will be increased in 33% in runtime if it runs out of space.
     * @~chinese 使用指定的纹理与子节点数量上限初始化一个 SpriteBatchNode。
     * 如果运行过程中添加的子节点数超过指定的上限，则上限增加 33%%。
     */
    bool initWithTexture(Texture2D *tex, ssize_t capacity = DEFAULT_CAPACITY);
    /** @~english initializes a SpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and a capacity of children.
     The capacity will be increased in 33% in runtime if it runs out of space.
     The file will be loaded using the TextureMgr.
     * @~chinese 使用指定的图片文件（.png，.jpeg，.pvr等）和子节点上限初始化一个 SpriteBatchNode。
     * 如果运行过程中添加的子节点数超过指定的上限，则上限增加 33%%。
     * 图片文件会通过 TextureMgr 加载。
     * @js init
     * @lua init
     */
    bool initWithFile(const std::string& fileImage, ssize_t capacity = DEFAULT_CAPACITY);
    bool init() override;
    
protected:
    void updateQuadFromSprite(Sprite *sprite, ssize_t index);   

    void updateAtlasIndex(Sprite* sprite, ssize_t* curIndex);
    void swap(ssize_t oldIndex, ssize_t newIndex);
    void updateBlendFunc();

    TextureAtlas *_textureAtlas;
    BlendFunc _blendFunc;
    BatchCommand _batchCommand;     // render command

    // all descendants: children, grand children, etc...
    // There is not need to retain/release these objects, since they are already retained by _children
    // So, using std::vector<Sprite*> is slightly faster than using cocos2d::Array for this particular case
    std::vector<Sprite*> _descendants;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __CC_SPRITE_BATCH_NODE_H__
