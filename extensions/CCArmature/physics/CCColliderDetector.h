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

namespace cocos2d { namespace extension { namespace armature {

class Bone;

class ColliderBody : public Object
{
public:
	ColliderBody(b2Body *b2b, ContourData *contourData)
		:_pB2b(NULL)
		,_contourData(NULL)
	{
		this->_pB2b = b2b;
		this->_contourData = contourData;
		CC_SAFE_RETAIN(_contourData);
	}

	~ColliderBody()
	{
		CC_SAFE_RELEASE(_contourData);
	}

	inline b2Body *getB2Body()
	{
		return _pB2b;
	}

	inline ContourData *getContourData()
	{
		return _contourData;
	}

private:
	b2Body *_pB2b;
	ContourData *_contourData;
};

/*
 *  @brief  ContourSprite used to draw the contour of the display
 */
class ColliderDetector : public Object
{
public:
	static ColliderDetector *create();
    static ColliderDetector *create(Bone *bone);
public:
	ColliderDetector();
	~ColliderDetector(void);
    
    virtual bool init();
	virtual bool init(Bone *bone);
    
    void addContourData(ContourData *contourData);
    void addContourDataList(Array *contourDataList);
    
	void removeContourData(ContourData *contourData);
	void removeAll();
    
    void updateTransform(AffineTransform &t);

	void setColliderFilter(b2Filter &filter);

    void setActive(bool active);
private:
    Array *_colliderBodyList;
    
	CC_SYNTHESIZE(Bone*, _bone, Bone);

};
		
}}} // namespace cocos2d { namespace extension { namespace armature {

#endif /*__CCCOLLIDERDETECTOR_H__*/
