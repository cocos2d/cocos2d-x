/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#pragma once

#include "2d/CCNode.h"
#include "base/CCProtocols.h"
#include "base/ccTypes.h"
#include "renderer/CCQuadCommand.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

class TextureAtlas;

/** @brief AtlasNode is a subclass of Node that implements the RGBAProtocol and TextureProtocol protocol.
 * It knows how to render a TextureAtlas object.
 * If you are going to render a TextureAtlas consider subclassing AtlasNode (or a subclass of AtlasNode).
 * All features from Node are valid, plus the following features:
 * - opacity and RGB colors.
 */
class CC_DLL AtlasNode : public Node, public TextureProtocol
{    
public:
	/** creates a AtlasNode  with an Atlas file the width and height of each item and the quantity of items to render.
     *
     * @param filename The path of Atlas file.
     * @param tileWidth The width of the item.
     * @param tileHeight The height of the item.
     * @param itemsToRender The quantity of items to render.
     */
	static AtlasNode * create(const std::string& filename, int tileWidth, int tileHeight, int itemsToRender);

    /** updates the Atlas (indexed vertex array).
    * Shall be overridden in subclasses.
    */
    virtual void updateAtlasValues();
    
    // Overrides
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    virtual Texture2D* getTexture() const override;
    virtual void setTexture(Texture2D *texture) override;
    virtual bool isOpacityModifyRGB() const override;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB) override;
    virtual const Color3B& getColor() const override;
    virtual void setColor(const Color3B& color) override;
    virtual void setOpacity(uint8_t opacity) override;
    
    /**
     * @code
     * When this function bound into js or lua,the parameter will be changed
     * In js: var setBlendFunc(var src, var dst)
     * @endcode
     * @lua NA
     */
    virtual void setBlendFunc(const BlendFunc& blendFunc) override;
    /**
     * @lua NA
     */
    virtual const BlendFunc& getBlendFunc() const override;
    
    /** Set an buffer manager of the texture vertex. */
    void setTextureAtlas(TextureAtlas* textureAtlas);
    
    /** Return the buffer manager of the texture vertex. 
     *
     * @return Return A TextureAtlas.
     */
    TextureAtlas* getTextureAtlas() const;
    
    void setQuadsToDraw(ssize_t quadsToDraw);
    size_t getQuadsToDraw() const;

CC_CONSTRUCTOR_ACCESS:
    AtlasNode();
    virtual ~AtlasNode();

    /** Initializes an AtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
    bool initWithTileFile(const std::string& tile, int tileWidth, int tileHeight, int itemsToRender);
    
    /** Initializes an AtlasNode  with a texture the width and height of each item measured in points and the quantity of items to render*/
    bool initWithTexture(Texture2D* texture, int tileWidth, int tileHeight, int itemsToRender);

protected:
    friend class Director;
    
    void calculateMaxItems();
    void updateBlendFunc();
    void updateOpacityModifyRGB();
    void setIgnoreContentScaleFactor(bool bIgnoreContentScaleFactor);

    /** Chars per row. */
    int    _itemsPerRow = 0;
    /** Chars per column. */
    int    _itemsPerColumn = 0;

    /** Width of each char. */
    int    _itemWidth = 0;
    /** Height of each char. */
    int    _itemHeight = 0;
    
    Color3B    _colorUnmodified;
    
    TextureAtlas* _textureAtlas = nullptr;
    /** Protocol variables. */
    bool _isOpacityModifyRGB = false;
    BlendFunc _blendFunc;

    /** Quads to draw. */
    size_t _quadsToDraw = 0;

    /** This variable is only used for LabelAtlas FPS display. So plz don't modify its value. */
    bool _ignoreContentScaleFactor = false;
    
    QuadCommand _quadCommand;
    backend::UniformLocation _textureLocation;
    backend::UniformLocation _mvpMatrixLocation;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(AtlasNode);

};

// end of base_node group
/// @}

NS_CC_END
