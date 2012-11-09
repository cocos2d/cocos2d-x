/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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

#include "CCCamera.h"
#include "cocoa/CCString.h"
#include "CCGL.h"

#include "CCDrawingPrimitives.h"
#include "CCDirector.h"
#include "kazmath/GL/matrix.h"

using namespace std;

NS_CC_BEGIN

CCCamera::CCCamera(void)
{
    init();
}

CCCamera::~CCCamera(void)
{
}

const char* CCCamera::description(void)
{
    return CCString::createWithFormat("<CCCamera | center = (%.2f,%.2f,%.2f)>", m_fCenterX, m_fCenterY, m_fCenterZ)->getCString();
}

void CCCamera::init(void)
{
    restore();
}

void CCCamera::restore(void)
{
    m_fEyeX = m_fEyeY = 0.0f;
    m_fEyeZ = getZEye();

    m_fCenterX = m_fCenterY = m_fCenterZ = 0.0f;

    m_fUpX = 0.0f;
    m_fUpY = 1.0f;
    m_fUpZ = 0.0f;

    kmMat4Identity( &m_lookupMatrix );

    m_bDirty = false;
}

void CCCamera::locate(void)
{
    if (m_bDirty)
    {
        kmVec3 eye, center, up;

        kmVec3Fill( &eye, m_fEyeX, m_fEyeY , m_fEyeZ );
        kmVec3Fill( &center, m_fCenterX, m_fCenterY, m_fCenterZ );

        kmVec3Fill( &up, m_fUpX, m_fUpY, m_fUpZ);
        kmMat4LookAt( &m_lookupMatrix, &eye, &center, &up);

        m_bDirty = false;
    }
    kmGLMultMatrix( &m_lookupMatrix );
}

float CCCamera::getZEye(void)
{
    return FLT_EPSILON;
}

void CCCamera::setEyeXYZ(float fEyeX, float fEyeY, float fEyeZ)
{
    m_fEyeX = fEyeX;
    m_fEyeY = fEyeY;
    m_fEyeZ = fEyeZ;

    m_bDirty = true;
}

void CCCamera::setCenterXYZ(float fCenterX, float fCenterY, float fCenterZ)
{
    m_fCenterX = fCenterX;
    m_fCenterY = fCenterY;
    m_fCenterZ = fCenterZ;

    m_bDirty = true;
}

void CCCamera::setUpXYZ(float fUpX, float fUpY, float fUpZ)
{
    m_fUpX = fUpX;
    m_fUpY = fUpY;
    m_fUpZ = fUpZ;

    m_bDirty = true;
}

void CCCamera::getEyeXYZ(float *pEyeX, float *pEyeY, float *pEyeZ)
{
    *pEyeX = m_fEyeX;
    *pEyeY = m_fEyeY;
    *pEyeZ = m_fEyeZ;
}

void CCCamera::getCenterXYZ(float *pCenterX, float *pCenterY, float *pCenterZ)
{
    *pCenterX = m_fCenterX;
    *pCenterY = m_fCenterY;
    *pCenterZ = m_fCenterZ;
}

void CCCamera::getUpXYZ(float *pUpX, float *pUpY, float *pUpZ)
{
    *pUpX = m_fUpX;
    *pUpY = m_fUpY;
    *pUpZ = m_fUpZ;
}

NS_CC_END

