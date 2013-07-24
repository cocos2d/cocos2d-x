/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CCATLAS_NODE_H__
#define __CCATLAS_NODE_H__

#include "CCNode.h"
#include "CCProtocols.h"
#include "ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup base_nodes
 * @{
 */

class TextureAtlas;

/** @brief AtlasNode is a subclass of Node that implements the RGBAProtocol and TextureProtocol protocol

It knows how to render a TextureAtlas object.
If you are going to render a TextureAtlas consider subclassing AtlasNode (or a subclass of AtlasNode)

All features from Node are valid, plus the following features:
- opacity and RGB colors
*/
class CC_DLL AtlasNode : public NodeRGBA, public TextureProtocol
{    
public:
	/** creates a AtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
	static AtlasNode * create(const char* tile,unsigned int tileWidth, unsigned int tileHeight,
                              unsigned int itemsToRender);
    AtlasNode();
    virtual ~AtlasNode();

    /** initializes an AtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
    bool initWithTileFile(const char* tile, unsigned int tileWidth, unsigned int tileHeight, unsigned int itemsToRender);

    /** initializes an AtlasNode  with a texture the width and height of each item measured in points and the quantity of items to render*/
    bool initWithTexture(Texture2D* texture, unsigned int tileWidth, unsigned int tileHeight, unsigned int itemsToRender);
    
    /** updates the Atlas (indexed vertex array).
    * Shall be overridden in subclasses
    */
    virtual void updateAtlasValues();

    void setTextureAtlas(TextureAtlas* textureAtlas);
    TextureAtlas* getTextureAtlas() const;
    
    void setQuadsToDraw(unsigned int quadsToDraw);
    unsigned int getQuadsToDraw() const;

    
    // Overrides
    virtual void draw() override;
    virtual Texture2D* getTexture() const override;
    virtual void setTexture(Texture2D *texture) override;
    virtual bool isOpacityModifyRGB() const override;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB) override;
    virtual const Color3B& getColor(void) const override;
    virtual void setColor(const Color3B& color) override;
    virtual void setOpacity(GLubyte opacity) override;
    virtual void setBlendFunc(const BlendFunc& blendFunc) override;
    virtual const BlendFunc& getBlendFunc() const override;

private :
    void calculateMaxItems();
    void updateBlendFunc();
    void updateOpacityModifyRGB();
    
    friend class Director;
    void setIgnoreContentScaleFactor(bool bIgnoreContentScaleFactor);

protected:
    //! chars per row
    unsigned int _itemsPerRow;
    //! chars per column
    unsigned int _itemsPerColumn;

    //! width of each char
    unsigned int    _itemWidth;
    //! height of each char
    unsigned int    _itemHeight;
    
    Color3B    _colorUnmodified;
    
    TextureAtlas* _textureAtlas;
    // protocol variables
    bool _isOpacityModifyRGB;
    BlendFunc _blendFunc;

    // quads to draw
    unsigned int _quadsToDraw;
    // color uniform
    GLint    _uniformColor;
    // This varible is only used for LabelAtlas FPS display. So plz don't modify its value.
    bool _ignoreContentScaleFactor;
};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCATLAS_NODE_H__


