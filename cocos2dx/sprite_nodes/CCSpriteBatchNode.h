/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009-2010 Ricardo Quesada
Copyright (C) 2009      Matt Oswald
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

#ifndef __CC_SPRITE_BATCH_NODE_H__
#define __CC_SPRITE_BATCH_NODE_H__

#include "base_nodes/CCNode.h"
#include "CCProtocols.h"
#include "textures/CCTextureAtlas.h"
#include "ccMacros.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

/**
 * @addtogroup sprite_nodes
 * @{
 */

#define kDefaultSpriteBatchCapacity   29

class CCSprite;

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
class CC_DLL CCSpriteBatchNode : public CCNode, public CCTextureProtocol
{
public:
    /**
     *  @js ctor
     */
    CCSpriteBatchNode();
    /**
     * @js NA
     * @lua NA
     */
    ~CCSpriteBatchNode();

    // property
    
    // retain
    inline CCTextureAtlas* getTextureAtlas(void) { return m_pobTextureAtlas; }
    inline void setTextureAtlas(CCTextureAtlas* textureAtlas) 
    { 
        if (textureAtlas != m_pobTextureAtlas)
        {
            CC_SAFE_RETAIN(textureAtlas);
            CC_SAFE_RELEASE(m_pobTextureAtlas);
            m_pobTextureAtlas = textureAtlas;
        }
    }

    inline CCArray* getDescendants(void) { return m_pobDescendants; }

    /** creates a CCSpriteBatchNode with a texture2d and capacity of children.
    The capacity will be increased in 33% in runtime if it run out of space.
    */
    static CCSpriteBatchNode* createWithTexture(CCTexture2D* tex, unsigned int capacity);
    static CCSpriteBatchNode* createWithTexture(CCTexture2D* tex) {
        return CCSpriteBatchNode::createWithTexture(tex, kDefaultSpriteBatchCapacity);
    }

    /** creates a CCSpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and capacity of children.
    The capacity will be increased in 33% in runtime if it run out of space.
    The file will be loaded using the TextureMgr.
    */
    static CCSpriteBatchNode* create(const char* fileImage, unsigned int capacity);
    static CCSpriteBatchNode* create(const char* fileImage) {
        return CCSpriteBatchNode::create(fileImage, kDefaultSpriteBatchCapacity);
    }

    /** initializes a CCSpriteBatchNode with a texture2d and capacity of children.
    The capacity will be increased in 33% in runtime if it run out of space.
    */
    bool initWithTexture(CCTexture2D *tex, unsigned int capacity);
    /** initializes a CCSpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and a capacity of children.
    The capacity will be increased in 33% in runtime if it run out of space.
    The file will be loaded using the TextureMgr.
    */
    bool initWithFile(const char* fileImage, unsigned int capacity);
    bool init();

    void increaseAtlasCapacity();

    /** removes a child given a certain index. It will also cleanup the running actions depending on the cleanup parameter.
    @warning Removing a child from a CCSpriteBatchNode is very slow
    */
    void removeChildAtIndex(unsigned int index, bool doCleanup);

    void insertChild(CCSprite *child, unsigned int index);
    void appendChild(CCSprite* sprite);
    void removeSpriteFromAtlas(CCSprite *sprite);

    unsigned int rebuildIndexInOrder(CCSprite *parent, unsigned int index);
    unsigned int highestAtlasIndexInChild(CCSprite *sprite);
    unsigned int lowestAtlasIndexInChild(CCSprite *sprite);
    unsigned int atlasIndexForChild(CCSprite *sprite, int z);
    /* Sprites use this to start sortChildren, don't call this manually */
    void reorderBatch(bool reorder);
    // CCTextureProtocol
    virtual CCTexture2D* getTexture(void);
    virtual void setTexture(CCTexture2D *texture);
    virtual void setBlendFunc(ccBlendFunc blendFunc);
    /**
     * @js NA
     */
    virtual ccBlendFunc getBlendFunc(void);

    virtual void visit(void);
    virtual void addChild(CCNode * child);
    virtual void addChild(CCNode * child, int zOrder);
    virtual void addChild(CCNode * child, int zOrder, int tag);
    virtual void reorderChild(CCNode * child, int zOrder);
        
    virtual void removeChild(CCNode* child, bool cleanup);
    virtual void removeAllChildrenWithCleanup(bool cleanup);
    virtual void sortAllChildren();
    virtual void draw(void);

protected:
    /** Inserts a quad at a certain index into the texture atlas. The CCSprite won't be added into the children array.
     This method should be called only when you are dealing with very big AtlasSrite and when most of the CCSprite won't be updated.
     For example: a tile map (CCTMXMap) or a label with lots of characters (CCLabelBMFont)
     */
    void insertQuadFromSprite(CCSprite *sprite, unsigned int index);
    /** Updates a quad at a certain index into the texture atlas. The CCSprite won't be added into the children array.
     This method should be called only when you are dealing with very big AtlasSrite and when most of the CCSprite won't be updated.
     For example: a tile map (CCTMXMap) or a label with lots of characters (CCLabelBMFont)
     */
    void updateQuadFromSprite(CCSprite *sprite, unsigned int index);
    /* This is the opposite of "addQuadFromSprite.
    It add the sprite to the children and descendants array, but it doesn't update add it to the texture atlas
    */
    CCSpriteBatchNode * addSpriteWithoutQuad(CCSprite*child, unsigned int z, int aTag);

private:
    void updateAtlasIndex(CCSprite* sprite, int* curIndex);
    void swap(int oldIndex, int newIndex);
    void updateBlendFunc();

protected:
    CCTextureAtlas *m_pobTextureAtlas;
    ccBlendFunc m_blendFunc;

    // all descendants: children, gran children, etc...
    CCArray* m_pobDescendants;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __CC_SPRITE_BATCH_NODE_H__
