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

#include "CCAtlasNode.h"

ccColor3B CCAtlasNode::getColor(void)
{
	if(m_bOpacityModifyRGB)
	{
		return m_tColorUnmodified;
	}

	return m_tColor;
}

void CCAtlasNode::setColor(ccColor3B color3)
{
	m_tColor = m_tColorUnmodified = color3;

	if( m_bOpacityModifyRGB )
	{
		m_tColor.r = color3.r * m_cOpacity/255;
		m_tColor.g = color3.g * m_cOpacity/255;
		m_tColor.b = color3.b * m_cOpacity/255;
	}	
}

GLubyte CCAtlasNode::getOpacity()
{
	return m_cOpacity;
}

void CCAtlasNode::setOpacity(GLubyte opacity)
{
	// special opacity for premultiplied textures
	m_cOpacity = opacity;

	// special opacity for premultiplied textures
	// special opacity for premultiplied textures
	if( m_bOpacityModifyRGB )		  //v0.99.1
		setColor( m_bOpacityModifyRGB ? m_tColorUnmodified : m_tColor );	 //--> win32 :  alwyas used m_colorUnmodified color. "if" state no required( issue )
}



