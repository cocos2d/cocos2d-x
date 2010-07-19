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
#include "CCTextureAtlas.h"

/** CCAtlasNode is a subclass of CCNode that implements the CCRGBAProtocol and
CCTextureProtocol protocol

It knows how to render a TextureAtlas object.
If you are going to render a TextureAtlas consider subclassing CCAtlasNode (or a subclass of CCAtlasNode)

All features from CCNode are valid, plus the following features:
- opacity and RGB colors
*/
class CCAtlasNode : public CCNode, public CCRGBAProtocol, public CCTextureProtocol
{
protected:

	// chars per row
	int m_nItemsPerRow;
	// chars per column
	int m_nItemsPerColumn;

	// texture coordinate x increment
	float m_fTexStepX;
	// texture coordinate y increment
	float m_fTexStepY;

	// width of each char
	int	m_nItemWidth;
	// height of each char
	int	m_nItemHeight;

	ccColor3B	m_tColorUnmodified;

	// protocol variables
	bool m_bOpacityModifyRGB;
	ccBlendFunc m_tBlendFunc;
	GLubyte m_cOpacity;
	ccColor3B m_tColor;
	CCTextureAtlas * m_pTextureAtlas;

public:
	CCAtlasNode();
	~CCAtlasNode();

	/** creates a CCAtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
	static CCAtlasNode * atlasWithTileFile(std::string & tile,int tileWidth, int tileHeight, int itemsToRender);

	/** initializes an CCAtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
	CCAtlasNode * initWithTileFile(std::string & tile, int tileWidth, int tileHeight, int itemsToRender);

	/** updates the Atlas (indexed vertex array).
	* Shall be overriden in subclasses
	*/
	void updateAtlasValues();

	virtual void draw();

public:
	// CC RGBA protocol

	/** sets Color
	@since v0.8
	*/
	virtual void setColor(ccColor3B color);

	/** returns the color
	@since v0.8
	*/
	virtual ccColor3B color(void);

	// returns the opacity
	virtual GLubyte opacity(void);

	/** sets the opacity.
	@warning If the the texture has premultiplied alpha then, the R, G and B channels will be modifed.
	Values goes from 0 to 255, where 255 means fully opaque.
	*/
	virtual void setOpacity(GLubyte opacity);

	// optional

	/** sets the premultipliedAlphaOpacity property.
	If set to NO then opacity will be applied as: glColor(R,G,B,opacity);
	If set to YES then oapcity will be applied as: glColor(opacity, opacity, opacity, opacity );
	Textures with premultiplied alpha will have this property by default on YES. Otherwise the default value is NO
	@since v0.8
	*/
	virtual void setOpacityModifyRGB(bool bValue);

	/** returns whether or not the opacity will be applied using glColor(R,G,B,opacity) or glColor(opacity, opacity, opacity, opacity);
	@since v0.8
	*/
	virtual bool doesOpacityModifyRGB(void);

	// CC Blend protocol

	// set the source blending function for the texture
	virtual void setBlendFunc(ccBlendFunc blendFunc);

	// returns the blending function used for the texture
	virtual ccBlendFunc blendFunc(void);

	// CC Texture protocol

	// returns the used texture
	virtual CCTexture2D* texture(void);

	// sets a new texture. it will be retained
	virtual void setTexture(CCTexture2D *texture);

private :
	void calculateMaxItems();
	void calculateTexCoordsSteps();
	void updateBlendFunc();
	void updateOpacityModifyRGB();

};

#endif // __CCATLAS_NODE_H__


