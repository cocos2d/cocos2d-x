/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

class CCAtlasNode : public CCNode, public CCRGBAProtocol, public CCTextureProtocol
{
protected:
	// texture atlas
	//CCTextureAtlas	*textureAtlas_;

	// chars per row
	int m_iItemsPerRow;
	// chars per column
	int m_iItemsPerColumn;

	// texture coordinate x increment
	float m_fTexStepX;
	// texture coordinate y increment
	float m_fTexStepY;

	// width of each char
	int	m_iItemWidth;
	// height of each char
	int	m_iItemHeight;

	// blend function
	//ccBlendFunc		blendFunc_;

	// texture RGBA. 
	//GLubyte		opacity_;
	//ccColor3B	color_;
	ccColor3B	m_tColorUnmodified;
	bool m_bOpacityModifyRGB;

	/** conforms to CCTextureProtocol protocol */
	DECLARE_VAR_READWRITE(CCTextureAtlas *, m_tTextureAtlas, TextureAtlas)

	/** conforms to CCTextureProtocol protocol */
	DECLARE_VAR_READWRITE(ccBlendFunc, m_tBlendFunc, BlendFunc)

	/** conforms to CCRGBAProtocol protocol */
	DECLARE_VAR_READWRITE(GLubyte, m_cOpacity, Opacity)

	/** conforms to CCRGBAProtocol protocol */
	DECLARE_VAR_READWRITE(ccColor3B, m_tColor, Color)

private:

	void calculateMaxItems(void);
	void calculateTexCoordsSteps(void);
	void updateBlendFunc(void);
	void updateOpacityModifyRGB(void);

public:

	CCAtlasNode();

	virtual ~CCAtlasNode();

	/** creates a CCAtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
	static void* atlasWithTileFile(NSString* tile, int tileWidth, int tileHeight, int itemsToRender);

	/** initializes an CCAtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
	void* initWithTileFile(NSString* tile, int tileWidth, int tileHeight, int itemsToRender;

	/** updates the Atlas (indexed vertex array).
	* Shall be overriden in subclasses
	*/
	void updateAtlasValues(void);

public: //CCNode methods
	virtual void draw(void);

public: //CCRGBAProtocol methods

};

#endif // __CCATLAS_NODE_H__


