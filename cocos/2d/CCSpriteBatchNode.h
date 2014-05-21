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
#include "2d/CCProtocols.h"
#include "2d/CCTextureAtlas.h"
#include "base/ccMacros.h"
#include "renderer/CCBatchCommand.h"

NS_CC_BEGIN

/**
 * @addtogroup sprite_nodes
 * @{
 */


class Sprite;

/** SpriteBatchNode与批量节点类似，如果包含子节点会在一次OpenGL调用内绘制完成(一般称为"batch draw")
*
* 一个SpriteBatchNode可以引用一个且只有一个纹理(一个图像文件或一个纹理集)，只有包含该纹理的Sprite可以加入到SpriteBatchNode中。
* 加入SpriteBatchNode的所有Sprite在一次OpenGL ES调用内绘制完成，而未加入SpriteBatchNode的Sprite每一个都需要单独调用OpenGL ES绘制，这样效率比较低。
*
*
* 限制：
*  - 只有Sprite或Sprite的子类对象才允许作为子节点(或孙子节点，等等)加入到SpriteBatchNode中，例如：particles、labels和layer不能加入SpriteBatchNode。
*  - 所有子节点的"alias"属性必须统一为Aliased或Antialiased，不能二者同时存在，因为"alias"是纹理的属性，而SpriteBatchNode全部的子节点共用一个纹理。
* 
* @since v0.7.1
*/
class CC_DLL SpriteBatchNode : public Node, public TextureProtocol
{
    static const int DEFAULT_CAPACITY = 29;

public:
    /** 创建一个指定子节点纹理(texture2d)和容量(capacity)参数的SpriteBatchNode。
     在运行期如超出预设容量则扩容33%。
     */
    static SpriteBatchNode* createWithTexture(Texture2D* tex, ssize_t capacity = DEFAULT_CAPACITY);

    /** 创建一个指定子节点纹理图像文件(.png、.jpeg、.pvr等)和容量(capacity)参数的SpriteBatchNode。
     在运行期如超出预设容量则扩容33%。
     使用TextureMgr加载图像文件。
     */
    static SpriteBatchNode* create(const std::string& fileImage, ssize_t capacity = DEFAULT_CAPACITY);


    /** 返回纹理集(TextureAtlas)对象 */
    inline TextureAtlas* getTextureAtlas(void) { return _textureAtlas; }

    /** 设置纹理集(TextureAtlas)对象 */
    inline void setTextureAtlas(TextureAtlas* textureAtlas)
    { 
        if (textureAtlas != _textureAtlas)
        {
            CC_SAFE_RETAIN(textureAtlas);
            CC_SAFE_RELEASE(_textureAtlas);
            _textureAtlas = textureAtlas;
        }
    }

    /** 返回后代节点(子节点，孙子节点，等等)数组。 
     此函数为BatchNode特有，如需要返回子节点则使用getChildren函数替代。 */
    inline const std::vector<Sprite*>& getDescendants() const { return _descendants; }

    void increaseAtlasCapacity();

    /** 删除指定索引值(index)的子节点，根据doCleanup参数确定是否同时释放该节点。
    @warning 从SpriteBatchNode删除一个子节点非常慢
    */
    void removeChildAtIndex(ssize_t index, bool doCleanup);

    void appendChild(Sprite* sprite);
    void removeSpriteFromAtlas(Sprite *sprite);

    ssize_t rebuildIndexInOrder(Sprite *parent, ssize_t index);
    ssize_t highestAtlasIndexInChild(Sprite *sprite);
    ssize_t lowestAtlasIndexInChild(Sprite *sprite);
    ssize_t atlasIndexForChild(Sprite *sprite, int z);
    /* Sprite使用这个函数执行sortChildren，不要手工调用此函数 */
    void reorderBatch(bool reorder);

    //
    // Overrides
    //
    // TextureProtocol
    virtual Texture2D* getTexture() const override;
    virtual void setTexture(Texture2D *texture) override;
    /**
    *@code
    *当此函数绑定到js或lua时，函数参数将被改变
    *js函数声明: var setBlendFunc(var src, var dst)
    *@endcode
    * @lua NA 
    */
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    /**
    * @js NA
    * @lua NA
    */
    virtual const BlendFunc& getBlendFunc() const override;

    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;
    
    using Node::addChild;
    virtual void addChild(Node * child, int zOrder, int tag) override;
    virtual void reorderChild(Node *child, int zOrder) override;
        
    virtual void removeChild(Node *child, bool cleanup) override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void sortAllChildren() override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
    virtual std::string getDescription() const override;

    /** 在指定索引位置插入一个quad(顶点的坐标位置，纹理的坐标位置和颜色信息)到纹理集，参数中的Sprite不会添加到子节点数组。
     此方法仅在处理一个很大的AtlasSprite且大部分Sprite不改变时调用。
     例如：瓦片地图(TMXMap)或包含非常多字符的标签(LabelBMFont)
     */
    void insertQuadFromSprite(Sprite *sprite, ssize_t index);
    /* 与insertQuadFromSprite相反，此函数添加Sprite到子节点数组但不添加到纹理集中。
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
    
    /** 指定子节点纹理(texture2d)和容量(capacity)参数初始化SpriteBatchNode。
     在运行期如超出预设容量则扩容33%。
     */
    bool initWithTexture(Texture2D *tex, ssize_t capacity);
    /** 指定子节点纹理图像文件(.png、.jpeg、.pvr等)和容量(capacity)参数初始化SpriteBatchNode。
     在运行期如超出预设容量则扩容33%。
     使用TextureMgr加载图像文件。
     * @js init
     * @lua init
     */
    bool initWithFile(const std::string& fileImage, ssize_t capacity);
    bool init();
    
protected:
    /** 在指定索引位置更新一个quad(顶点的坐标位置，纹理的坐标位置和颜色信息)到纹理集，参数中的Sprite不会添加到子节点数组。
     此方法仅在处理一个很大的AtlasSprite且大部分Sprite不改变时调用。
     例如：瓦片地图(TMXMap)或包含非常多字符的标签(LabelBMFont)
     */
    void updateQuadFromSprite(Sprite *sprite, ssize_t index);   

    void updateAtlasIndex(Sprite* sprite, ssize_t* curIndex);
    void swap(ssize_t oldIndex, ssize_t newIndex);
    void updateBlendFunc();

    TextureAtlas *_textureAtlas;
    BlendFunc _blendFunc;
    BatchCommand _batchCommand;     // render command

    // 所有后代节点：子节点，孙子节点，等等
    // 不需要保持/释放(retain/release)这些对象，因为它们已经在_children保持了
    // 因此，在这种特殊情况下使用std::vector<Sprite*>比使用cocos2d::Array稍快
    std::vector<Sprite*> _descendants;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __CC_SPRITE_BATCH_NODE_H__
