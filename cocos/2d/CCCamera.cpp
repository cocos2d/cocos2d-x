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
#include "CCString.h"
#include "CCGL.h"

#include "CCDrawingPrimitives.h"
#include "CCDirector.h"
#include "kazmath/GL/matrix.h"

using namespace std;

NS_CC_BEGIN

Camera::Camera(void)
{
    init();
}

Camera::~Camera(void)
{
}

const char* Camera::description(void) const
{
    return String::createWithFormat("<Camera | center = (%.2f,%.2f,%.2f)>", _centerX, _centerY, _centerZ)->getCString();
}

void Camera::init(void)
{
    restore();
}

void Camera::restore(void)
{
    _eyeX = _eyeY = 0.0f;
    _eyeZ = getZEye();

    _centerX = _centerY = _centerZ = 0.0f;

    _upX = 0.0f;
    _upY = 1.0f;
    _upZ = 0.0f;

    kmMat4Identity(&_lookupMatrix);

    _dirty = false;
}

void Camera::locate(void)
{
    if (_dirty)
    {
        kmVec3 eye, center, up;

        kmVec3Fill(&eye, _eyeX, _eyeY , _eyeZ);
        kmVec3Fill(&center, _centerX, _centerY, _centerZ);

        kmVec3Fill(&up, _upX, _upY, _upZ);
        kmMat4LookAt(&_lookupMatrix, &eye, &center, &up);

        _dirty = false;
    }
    kmGLMultMatrix(&_lookupMatrix);
}

float Camera::getZEye(void)
{
    return FLT_EPSILON;
}

void Camera::setEye(float eyeX, float eyeY, float eyeZ)
{
    _eyeX = eyeX;
    _eyeY = eyeY;
    _eyeZ = eyeZ;

    _dirty = true;
}

void Camera::setCenter(float centerX, float centerY, float centerZ)
{
    _centerX = centerX;
    _centerY = centerY;
    _centerZ = centerZ;

    _dirty = true;
}

void Camera::setUp(float upX, float upY, float upZ)
{
    _upX = upX;
    _upY = upY;
    _upZ = upZ;

    _dirty = true;
}

void Camera::getEye(float *eyeX, float *eyeY, float *eyeZ) const
{
    *eyeX = _eyeX;
    *eyeY = _eyeY;
    *eyeZ = _eyeZ;
}

void Camera::getCenter(float *centerX, float *centerY, float *centerZ) const
{
    *centerX = _centerX;
    *centerY = _centerY;
    *centerZ = _centerZ;
}

void Camera::getUp(float *upX, float *upY, float *upZ) const
{
    *upX = _upX;
    *upY = _upY;
    *upZ = _upZ;
}

NS_CC_END

