/****************************************************************************
Copyright (c) 2010-2011  cocos2d-x.org
Copyright (c) 2008, 2009 Jason Booth

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
#ifndef __CCMOTION_STREAK_H__
#define __CCMOTION_STREAK_H__

#include "CCNode.h"
#include "CCProtocols.h"

namespace cocos2d {

class CCRibbon;
/**
* @brief CCMotionStreak manages a Ribbon based on it's motion in absolute space.
* You construct it with a fadeTime, minimum segment size, texture path, texture
* length and color. The fadeTime controls how long it takes each vertex in
* the streak to fade out, the minimum segment size it how many pixels the
* streak will move before adding a new ribbon segement, and the texture
* length is the how many pixels the texture is stretched across. The texture
* is vertically aligned along the streak segemnts. 
*
* Limitations:
*   CCMotionStreak, by default, will use the GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA blending function.
*   This blending function might not be the correct one for certain textures.
*   But you can change it by using:
*     [obj setBlendFunc: (ccBlendfunc) {new_src_blend_func, new_dst_blend_func}];
*
* @since v0.8.1
*/
class CC_DLL CCMotionStreak : public CCNode, public CCTextureProtocol
{
	/** Ribbon used by MotionStreak (weak reference) */
	CC_PROPERTY_READONLY(CCRibbon*, m_pRibbon, Ribbon)
	//CCTextureProtocol methods
	CC_PROPERTY(CCTexture2D*, m_pTexture, Texture)
	CC_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc)
public:
	CCMotionStreak()
		: m_pRibbon(NULL)
        , m_pTexture(NULL)
        , m_fSegThreshold(0.0)
		, m_fWidth(0.0)		
	{}
	virtual ~CCMotionStreak(){}
	/** creates the a MotionStreak. The image will be loaded using the TextureMgr. */
	static CCMotionStreak * streakWithFade(float fade, float seg, const char *imagePath, float width, float length, ccColor4B color);

	/** initializes a MotionStreak. The file will be loaded using the TextureMgr. */
	bool initWithFade(float fade, float seg, const char *imagePath, float width, float length, ccColor4B color);

	/** polling function */
	void update(ccTime delta);
protected:
	float		m_fSegThreshold;
	float		m_fWidth;
	CCPoint		m_tLastLocation;
};

} // namespace cocos2d

#endif //__CCMOTION_STREAK_H__
