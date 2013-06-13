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

class CCTextureAtlas;

/** @brief CCAtlasNode is a subclass of CCNode that implements the CCRGBAProtocol and CCTextureProtocol protocol

It knows how to render a TextureAtlas object.
If you are going to render a TextureAtlas consider subclassing CCAtlasNode (or a subclass of CCAtlasNode)

All features from CCNode are valid, plus the following features:
- opacity and RGB colors
*/
class CC_DLL CCAtlasNode : public CCNodeRGBA, public CCTextureProtocol
{
protected:

    //! chars per row
    unsigned int m_uItemsPerRow;
    //! chars per column
    unsigned int m_uItemsPerColumn;

    //! width of each char
    unsigned int    m_uItemWidth;
    //! height of each char
    unsigned int    m_uItemHeight;

    ccColor3B    m_tColorUnmodified;

    CC_PROPERTY(CCTextureAtlas*, m_pTextureAtlas, TextureAtlas);

    // protocol variables
    bool m_bIsOpacityModifyRGB;
    
    CC_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc);

    // quads to draw
    CC_PROPERTY(unsigned int, m_uQuadsToDraw, QuadsToDraw);
    // color uniform
    GLint    m_nUniformColor;
    // This varible is only used for CCLabelAtlas FPS display. So plz don't modify its value.
    bool m_bIgnoreContentScaleFactor;
    
public:
    CCAtlasNode();
    virtual ~CCAtlasNode();

	/** creates a CCAtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
	static CCAtlasNode * create(const char* tile,unsigned int tileWidth, unsigned int tileHeight, 
		unsigned int itemsToRender);

    /** initializes an CCAtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
    bool initWithTileFile(const char* tile, unsigned int tileWidth, unsigned int tileHeight, unsigned int itemsToRender);

    /** initializes an CCAtlasNode  with a texture the width and height of each item measured in points and the quantity of items to render*/
    bool initWithTexture(CCTexture2D* texture, unsigned int tileWidth, unsigned int tileHeight, unsigned int itemsToRender);
    
    /** updates the Atlas (indexed vertex array).
    * Shall be overridden in subclasses
    */
    virtual void updateAtlasValues();

    virtual void draw(void);

    // CC Texture protocol

    /** returns the used texture*/
    virtual CCTexture2D* getTexture(void);

    /** sets a new texture. it will be retained*/
    virtual void setTexture(CCTexture2D *texture);
    
    virtual bool isOpacityModifyRGB();
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB);
    virtual const ccColor3B& getColor(void);
    virtual void setColor(const ccColor3B& color);
    virtual void setOpacity(GLubyte opacity);

private :
    void calculateMaxItems();
    void updateBlendFunc();
    void updateOpacityModifyRGB();
    
    friend class CCDirector;
    void setIgnoreContentScaleFactor(bool bIgnoreContentScaleFactor);
};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCATLAS_NODE_H__


