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

#include "CCNode.h"

using namespace std;

CCNode::CCNode(void)
:m_bIsRunning(false)
,m_fRotation(0.0f)
,m_fScaleX(1.0f)
,m_fScaleY(1.0f)
,m_tPosition(CGPoint(0,0))
,m_tAnchorPointInPixels(CGPoint(0,0))
,m_tAnchorPoint(CGPoint(0,0))
,m_tContentSize(CGSize(0,0))
// "whole screen" objects. like Scenes and Layers, should set isRelativeAnchorPoint to false
,m_bIsRelativeAnchorPoint(true)
,m_bIsTransformDirty(true)
,m_bIsInverseDirty(true)
#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
,m_bIsTransformGLDirty(true)
#endif
,m_fVertexZ(0.0f)
,m_pGrid(NULL)
,m_bIsVisible(true)
,m_iTag(kCCNodeTagInvalid)
,m_iZOrder(0)
// lazy alloc
,m_pCamera(NULL)
// children (lazy allocs)
,m_pChildren(NULL)
// userData is always inited as nil
,m_pUserData(NULL)
{}

/*initialize*/
bool CCNode::init(void)
{
	return true;
}

float CCNode::getRotation()
{
	return m_fRotation;
}

CGPoint CCNode::getPosition()
{
	return m_tPosition;
}

float CCNode::getScaleX()
{
	return m_fScaleX;
}

float CCNode::getScaleY()
{
	return m_fScaleY;
}

void CCNode::setVisibility(bool bIsVisible)
{
	m_bIsVisible = bIsVisible;
}

bool CCNode::getVisibility()
{
	return m_bIsVisible;
}
//
//CCGridBase* CCNode::getGrid()
//{
//	return m_pGrid;
//}
//
//void CCNode::setGrid(CCGridBase* pGrid)
//{
//	if(/*!pGrid &&*/ m_pGrid)
//		m_pGrid->release();
//
//	m_pGrid = pGrid;
//
//	if(m_pGrid)
//		m_pGrid->retain();
//}


// getters synthesized, setters explicit
void CCNode::setRotation(float newRotation)
{
	m_fRotation = newRotation;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
	#endif
}

void CCNode::setScaleX(float newScaleX)
{
	m_fScaleX = newScaleX;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
	#endif
}

void CCNode::setScaleY(float newScaleY)
{
	m_fScaleY = newScaleY;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
	#endif
}

void CCNode::setPosition(CGPoint newPosition)
{
	m_tPosition = newPosition;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
	#endif
}

void CCNode::setIsRelativeAnchorPoint(bool newValue)
{
	m_bIsRelativeAnchorPoint = newValue;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
	#endif
}

bool CCNode::getIsRelativeAnchorPoint()
{
	return m_bIsRelativeAnchorPoint;
}

void CCNode::setAnchorPoint(CGPoint point)
{
	/*if( ! CGPointEqualToPoint(point, m_anchorPoint) ) 
	{
		m_anchorPoint = point;
		this->m_anchorPointInPixels = ccp( m_contentSize.width * m_anchorPoint.x, m_contentSize.height * m_anchorPoint.y );
		m_isTransformDirty = m_isInverseDirty = true;
		#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
			m_bIsTransformGLDirty = true;
		#endif
	}*/
}

CGPoint CCNode::getAnchorPoint()
{
	return m_tAnchorPoint;
}

void CCNode::setContentSize(CGSize size)
{
	//if( ! CGSizeEqualToSize(size, m_contentSize) ) 
	//{
	//	m_contentSize = size;
	//	m_anchorPointInPixels = ccp( m_contentSize.width * m_anchorPoint.x, m_contentSize.height * m_anchorPoint.y );
	//	m_isTransformDirty = m_isInverseDirty = true;
	//	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
	//		m_bIsTransformGLDirty = true;
	//	#endif
	//}
}

CGSize CCNode::getContentSize()
{
	return m_tContentSize;
}
//
//CGRect CCNode::boundingBox()
//{
//	CGRect rect = CGRectMake(0, 0, m_contentSize.width, m_contentSize.height);
//	return CGRectApplyAffineTransform(rect, nodeToParentTransform());
//}
//
//float CCNode::scale()
//{
//	UXAssert( m_scaleX == m_scaleY, L"CocosNode#scale. ScaleX != ScaleY. Don't know which one to return");
//	return m_scaleX;
//}

void CCNode::setScale(float scale)
{
	m_fScaleX = m_fScaleY = scale;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
	#endif
}

//
//UxMutableArray* CCNode::children()
//{
//	return m_pChildrenArray;
//}

void CCNode::setParent(CCNode* pParentNode)
{
	m_pParent = pParentNode;
}

CCNode* CCNode::getParent()
{
	return m_pParent;
}

int CCNode::getTag()
{
	return m_iTag;
}

void CCNode::setTag(int tag)
{
	m_iTag = tag;   
}

int CCNode::getZOrder()
{
	return m_iZOrder;
}

void CCNode::setVertexZ(float z)
{
	m_fVertexZ = z;
}

float CCNode::getVertexZ()
{
	return m_fVertexZ;
}

CGPoint CCNode::getAnchorPointInPixels()
{
	return m_tAnchorPointInPixels;
}

bool CCNode::getIsRunning()
{
	return m_bIsRunning;
}

