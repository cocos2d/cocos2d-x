/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#ifndef __CCCOLLIDERDETECTOR_H__
#define __CCCOLLIDERDETECTOR_H__

#include "../utils/CCArmatureDefine.h"
#include "../datas/CCDatas.h"

class b2Body;
struct b2Filter;

NS_CC_EXT_BEGIN

class CCBone;

class ColliderBody : public CCObject
{
public:
	ColliderBody(b2Body *b2b, CCContourData *contourData)
		:m_pB2b(NULL)
		,m_pContourData(NULL)
	{
		this->m_pB2b = b2b;
		this->m_pContourData = contourData;
		CC_SAFE_RETAIN(m_pContourData);
	}

	~ColliderBody()
	{
		CC_SAFE_RELEASE(m_pContourData);
	}

	inline b2Body *getB2Body()
	{
		return m_pB2b;
	}

	inline CCContourData *getContourData()
	{
		return m_pContourData;
	}

private:
	b2Body *m_pB2b;
	CCContourData *m_pContourData;
};

/*
 *  @brief  ContourSprite used to draw the contour of the display
 */
class CCColliderDetector : public CCObject
{
public:
	static CCColliderDetector *create();
    static CCColliderDetector *create(CCBone *bone);
public:
	CCColliderDetector();
	~CCColliderDetector(void);
    
    virtual bool init();
	virtual bool init(CCBone *bone);
    
    void addContourData(CCContourData *contourData);
    void addContourDataList(CCArray *contourDataList);
    
	void removeContourData(CCContourData *contourData);
	void removeAll();
    
    void updateTransform(CCAffineTransform &t);

	void setColliderFilter(b2Filter &filter);

    void setActive(bool active);
private:
    CCArray *m_pColliderBodyList;
    
	CC_SYNTHESIZE(CCBone*, m_pBone, Bone);

};
		
NS_CC_EXT_END

#endif /*__CCCOLLIDERDETECTOR_H__*/
