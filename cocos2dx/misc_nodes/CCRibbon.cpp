/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2009 Jason Booth

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

#include "CCRibbon.h"
#include "CCTextureCache.h"
#include "CCPointExtension.h"
#include "CCDirector.h"

namespace cocos2d {

/*
* A ribbon is a dynamically generated list of polygons drawn as a single or series
* of triangle strips. The primary use of Ribbon is as the drawing class of Motion Streak,
* but it is quite useful on it's own. When manually drawing a ribbon, you can call addPointAt
* and pass in the parameters for the next location in the ribbon. The system will automatically
* generate new polygons, texture them accourding to your texture width, etc, etc.
*
* Ribbon data is stored in a RibbonSegment class. This class statically allocates enough verticies and
* texture coordinates for 50 locations (100 verts or 48 triangles). The ribbon class will allocate
* new segments when they are needed, and reuse old ones if available. The idea is to avoid constantly
* allocating new memory and prefer a more static method. However, since there is no way to determine
* the maximum size of some ribbons (motion streaks), a truely static allocation is not possible.
*
*/

//
// Ribbon
//
CCRibbon * CCRibbon::ribbonWithWidth(float w, const char *path, float length, const ccColor4B& color, float fade)
{
	CCRibbon *pRet = new CCRibbon();
	if(pRet && pRet->initWithWidth(w, path, length, color, fade))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet)
	return NULL;
}

bool CCRibbon::initWithWidth(float w, const char *path, float length, const ccColor4B& color, float fade)
{
	m_pSegments = new CCMutableArray<CCRibbonSegment*>();
	m_pDeletedSegments = new CCMutableArray<CCRibbonSegment*>();

	/* 1 initial segment */
	CCRibbonSegment* seg = new CCRibbonSegment();
	seg->init();
	m_pSegments->addObject(seg);
	seg->release();

	m_fTextureLength = length;

	m_tColor = color;
	m_fFadeTime = fade;
	m_tLastLocation = CCPointZero;
	m_fLastWidth = w/2;
	m_fTexVPos = 0.0f;

	m_fCurTime = 0;
	m_bPastFirstPoint = false;

	/* XXX:
	Ribbon, by default uses this blend function, which might not be correct
	if you are using premultiplied alpha images,
	but 99% you might want to use this blending function regarding of the texture
	*/
	m_tBlendFunc.src = GL_SRC_ALPHA;
	m_tBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;

	m_pTexture = CCTextureCache::sharedTextureCache()->addImage(path);
	CC_SAFE_RETAIN(m_pTexture);

	/* default texture parameter */
	ccTexParams params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	m_pTexture->setTexParameters(&params);
	return true;
}

CCRibbon::~CCRibbon()
{
    CC_SAFE_RELEASE(m_pSegments);
    CC_SAFE_RELEASE(m_pDeletedSegments);
    CC_SAFE_RELEASE(m_pTexture);
}

CCPoint CCRibbon::rotatePoint(const CCPoint& vec, float rotation)
{
	CCPoint ret;
	ret.x = (vec.x * cosf(rotation)) - (vec.y * sinf(rotation));
	ret.y = (vec.x * sinf(rotation)) + (vec.y * cosf(rotation));
	return ret;
}

void CCRibbon::update(ccTime delta)
{
	m_fCurTime += delta;
	m_fDelta = delta;
}

float CCRibbon::sideOfLine(const CCPoint& p, const CCPoint& l1, const CCPoint& l2)
{
	CCPoint vp = ccpPerp(ccpSub(l1, l2));
	CCPoint vx = ccpSub(p, l1);
	return ccpDot(vx, vp);
}

// adds a new segment to the ribbon
void CCRibbon::addPointAt(CCPoint location, float width)
{
    location.x *= CC_CONTENT_SCALE_FACTOR();
    location.y *= CC_CONTENT_SCALE_FACTOR();

    width = width * 0.5f;
	// if this is the first point added, cache it and return
	if (!m_bPastFirstPoint)
	{
		m_fLastWidth = width;
		m_tLastLocation = location;
		m_bPastFirstPoint = true;
		return;
	}

	CCPoint sub = ccpSub(m_tLastLocation, location);
	float r = ccpToAngle(sub) + (float)M_PI_2;
	CCPoint p1 = ccpAdd(this->rotatePoint(ccp(-width, 0), r), location);
	CCPoint p2 = ccpAdd(this->rotatePoint(ccp(+width, 0), r), location);
	float len = sqrtf(powf(m_tLastLocation.x - location.x, 2) + powf(m_tLastLocation.y - location.y, 2));
	float tend = m_fTexVPos + len/m_fTextureLength;
	CCRibbonSegment* seg;
	// grab last segment
	seg = m_pSegments->getLastObject();
	// lets kill old segments
	if (m_pSegments && m_pSegments->count()>0)
	{
		CCMutableArray<CCRibbonSegment*>::CCMutableArrayIterator it;
		for (it = m_pSegments->begin(); it != m_pSegments->end(); ++it)
		{
			if (*it != seg && (*it)->m_bFinished)
			{
				m_pDeletedSegments->addObject(*it);
			}
		}
	}
	
	m_pSegments->removeObjectsInArray(m_pDeletedSegments);
	// is the segment full?
	if (seg->m_uEnd >= 50)
	{
		m_pSegments->removeObjectsInArray(m_pDeletedSegments);
	}
	// grab last segment and append to it if it's not full
	seg = m_pSegments->getLastObject();
	// is the segment full?
	if (seg->m_uEnd >= 50)
	{
		CCRibbonSegment* newSeg;
		// grab it from the cache if we can
		if (m_pDeletedSegments->count() > 0)
		{
			newSeg = m_pDeletedSegments->getObjectAtIndex(0);
			newSeg->retain();							// will be released later
			m_pDeletedSegments->removeObject(newSeg);
			newSeg->reset();
		}
		else
		{
			newSeg = new CCRibbonSegment(); // will be released later
			newSeg->init();
		}

		newSeg->m_pCreationTime[0] = seg->m_pCreationTime[seg->m_uEnd- 1];
		int v = (seg->m_uEnd-1)*6;
		int c = (seg->m_uEnd-1)*4;	
		newSeg->m_pVerts[0] = seg->m_pVerts[v];
		newSeg->m_pVerts[1] = seg->m_pVerts[v+1];
		newSeg->m_pVerts[2] = seg->m_pVerts[v+2];
		newSeg->m_pVerts[3] = seg->m_pVerts[v+3];
		newSeg->m_pVerts[4] = seg->m_pVerts[v+4];
		newSeg->m_pVerts[5] = seg->m_pVerts[v+5];

		newSeg->m_pCoords[0] = seg->m_pCoords[c];
		newSeg->m_pCoords[1] = seg->m_pCoords[c+1];
		newSeg->m_pCoords[2] = seg->m_pCoords[c+2];
		newSeg->m_pCoords[3] = seg->m_pCoords[c+3];	  
		newSeg->m_uEnd++;
		seg = newSeg;
		m_pSegments->addObject(seg);
		newSeg->release();// it was retained before
	}  
	if (seg->m_uEnd == 0)
	{
		// first edge has to get rotation from the first real polygon
		CCPoint lp1 = ccpAdd(this->rotatePoint(ccp(-m_fLastWidth, 0), r), m_tLastLocation);
		CCPoint lp2 = ccpAdd(this->rotatePoint(ccp(+m_fLastWidth, 0), r), m_tLastLocation);
		seg->m_pCreationTime[0] = m_fCurTime - m_fDelta;
		seg->m_pVerts[0] = lp1.x;
		seg->m_pVerts[1] = lp1.y;
		seg->m_pVerts[2] = 0.0f;
		seg->m_pVerts[3] = lp2.x;
		seg->m_pVerts[4] = lp2.y;
		seg->m_pVerts[5] = 0.0f;
		seg->m_pCoords[0] = 0.0f;
		seg->m_pCoords[1] = m_fTexVPos;
		seg->m_pCoords[2] = 1.0f;
		seg->m_pCoords[3] = m_fTexVPos;
		seg->m_uEnd++;
	}

	int v = seg->m_uEnd*6;
	int c = seg->m_uEnd*4;
	// add new vertex
	seg->m_pCreationTime[seg->m_uEnd] = m_fCurTime;
	seg->m_pVerts[v] = p1.x;
	seg->m_pVerts[v+1] = p1.y;
	seg->m_pVerts[v+2] = 0.0f;
	seg->m_pVerts[v+3] = p2.x;
	seg->m_pVerts[v+4] = p2.y;
	seg->m_pVerts[v+5] = 0.0f;


	seg->m_pCoords[c] = 0.0f;
	seg->m_pCoords[c+1] = tend;
	seg->m_pCoords[c+2] = 1.0f;
	seg->m_pCoords[c+3] = tend;

	m_fTexVPos = tend;
	m_tLastLocation = location;
	m_tLastPoint1 = p1;
	m_tLastPoint2 = p2;
	m_fLastWidth = width;
	seg->m_uEnd++;
}

void CCRibbon::draw()
{
	CCNode::draw();

	if (m_pSegments->count() > 0)
	{
		// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Unneeded states: GL_COLOR_ARRAY
		glDisableClientState(GL_COLOR_ARRAY);

		glBindTexture(GL_TEXTURE_2D, m_pTexture->getName());

        bool newBlend = ( m_tBlendFunc.src != CC_BLEND_SRC || m_tBlendFunc.dst != CC_BLEND_DST ) ? true : false;
        if( newBlend )
        {
            glBlendFunc( m_tBlendFunc.src, m_tBlendFunc.dst );
        }

		if(m_pSegments && m_pSegments->count() > 0)
		{
			CCRibbonSegment* seg;
			CCMutableArray<CCRibbonSegment*>::CCMutableArrayIterator it;
			for( it = m_pSegments->begin(); it != m_pSegments->end(); it++)
			{
				seg = (CCRibbonSegment*)*it;
				seg->draw(m_fCurTime, m_fFadeTime, m_tColor);
			}
		}

		if( newBlend )
		{
			glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
		}

		// restore default GL state
		glEnableClientState( GL_COLOR_ARRAY );
	}
}

// Ribbon - CocosNodeTexture protocol
void CCRibbon::setTexture(CCTexture2D* var)
{
	CC_SAFE_RETAIN(var);
	CC_SAFE_RELEASE(m_pTexture);
	m_pTexture = var;
	this->setContentSize(m_pTexture->getContentSizeInPixels());
	/* XXX Don't update blending function in Ribbons */
}

CCTexture2D *CCRibbon::getTexture()
{
	return m_pTexture;
}

void CCRibbon::setTextureLength(float var)
{
	m_fTextureLength = var;
}

float CCRibbon::getTextureLength()
{
	return m_fTextureLength;
}
void CCRibbon::setBlendFunc(ccBlendFunc var)
{
	m_tBlendFunc = var;
}

ccBlendFunc CCRibbon::getBlendFunc()
{
	return m_tBlendFunc;
}

void CCRibbon::setColor(const ccColor4B& var)
{
	m_tColor = var;
}
const ccColor4B& CCRibbon::getColor()
{
	return m_tColor;
} 

//
//RibbonSegment
//
bool CCRibbonSegment::init()
{
	this->reset();
	return true;
}

char * CCRibbonSegment::description()
{
	char *ret = new char[100] ;
	sprintf(ret, "<CCRibbonSegment | end = %u, begin = %u>", m_uEnd, m_uBegin);
	return ret;
}

CCRibbonSegment::~CCRibbonSegment()
{
	CCLOGINFO("cocos2d: deallocing.");
}

void CCRibbonSegment::reset()
{
	m_uEnd = 0;
	m_uBegin = 0;
	m_bFinished = false;
}

void CCRibbonSegment::draw(float curTime, float fadeTime, const ccColor4B& color)
{
	GLubyte r = color.r;
	GLubyte g = color.g;
	GLubyte b = color.b;
	GLubyte a = color.a;

	if (m_uBegin < 50)
	{
		// the motion streak class will call update and cause time to change, thus, if curTime_ != 0
		// we have to generate alpha for the ribbon each frame.
		if (curTime == 0)
		{
			// no alpha over time, so just set the color
            // glColor4ub isn't implement on some android devices
			// glColor4ub(r,g,b,a);
            glColor4f(((GLfloat)r) / 255, ((GLfloat)g) / 255, ((GLfloat)b) / 255, ((GLfloat)a) / 255);
		}
		else
		{
			// generate alpha/color for each point
			glEnableClientState(GL_COLOR_ARRAY);
			unsigned int i = m_uBegin;
			for (; i < m_uEnd; ++i)
			{
				int idx = i*8;
				m_pColors[idx] = r;
				m_pColors[idx+1] = g;
				m_pColors[idx+2] = b;
				m_pColors[idx+4] = r;
				m_pColors[idx+5] = g;
				m_pColors[idx+6] = b;
				float alive = ((curTime - m_pCreationTime[i]) / fadeTime);
				if (alive > 1)
				{
					m_uBegin++;
					m_pColors[idx+3] = 0;
					m_pColors[idx+7] = 0;
				}
				else
				{
					m_pColors[idx+3] = (GLubyte)(255.f - (alive * 255.f));
					m_pColors[idx+7] = m_pColors[idx+3];
				}
			}
			glColorPointer(4, GL_UNSIGNED_BYTE, 0, &m_pColors[m_uBegin*8]);
		}
		glVertexPointer(3, GL_FLOAT, 0, &m_pVerts[m_uBegin*6]);
		glTexCoordPointer(2, GL_FLOAT, 0, &m_pCoords[m_uBegin*4]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, (m_uEnd - m_uBegin) * 2);
	}
	else
	{
		m_bFinished = true;
	}
}

}// namespace cocos2d
