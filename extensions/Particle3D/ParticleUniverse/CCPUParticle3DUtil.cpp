/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "CCPUParticle3DUtil.h"
#include "base/ccMacros.h"

NS_CC_BEGIN

cocos2d::Vec3 PUParticle3DUtil::randomDeviant( const Vec3 &src, float angle, const Vec3& up /*= Vec3::ZERO*/ )
{
    Vec3 newUp;

    if (up == Vec3::ZERO)
    {
        // Generate an up vector
        newUp = perpendicular(src);
    }
    else
    {
        newUp = up;
    }

    // Rotate up vector by random amount around this
    //Quaternion q;
    //q.FromAngleAxis( Radian(Math::UnitRandom() * Math::TWO_PI), *this );
    //newUp = q * newUp;

    //// Finally rotate this by given angle around randomised up
    //q.FromAngleAxis( angle, newUp );
    //return q * (*this);

	Quaternion q;
	Mat4 mat;
	Quaternion::createFromAxisAngle(src, CCRANDOM_0_1() * M_PI * 2.0f, &q);
    Mat4::createRotation(q, &mat);

	//{
	//	Vec3 uv, uuv;
	//	Vec3 qvec(q.x, q.y, q.z);
	//	Vec3::cross(qvec, newUp, &uv);
	//	Vec3::cross(qvec, uv, &uuv);
	//	uv *= (2.0f * q.w);
	//	uuv *= 2.0f;
	//	newUp = newUp + uv + uuv;
	//}

    newUp = mat * newUp;
	Quaternion::createFromAxisAngle(newUp, angle, &q);
    Mat4::createRotation(q, &mat);
    return  mat * src;

	//{
	//	Vec3 uv, uuv;
	//	Vec3 qvec(q.x, q.y, q.z);
	//	Vec3::cross(qvec, src, &uv);
	//	Vec3::cross(qvec, uv, &uuv);
	//	uv *= (2.0f * q.w);
	//	uuv *= 2.0f;
	//	return src + uv + uuv;
	//}
}

cocos2d::Vec3 PUParticle3DUtil::perpendicular( const Vec3 &src )
{
    //static const float fSquareZero = (float)(1e-06 * 1e-06);

    //Vector3 perp = this->crossProduct( Vector3::UNIT_X );

    //// Check length
    //if( perp.squaredLength() < fSquareZero )
    //{
    //	/* This vector is the Y axis multiplied by a scalar, so we have
    //		to use another axis.
    //	*/
    //	perp = this->crossProduct( Vector3::UNIT_Y );
    //}
    //perp.normalise();

    //return perp;

    static const float fSquareZero = (float)(1e-06 * 1e-06);
    Vec3 perp;
    Vec3::cross(src, Vec3::UNIT_X, &perp);
    // Check length
    if( perp.lengthSquared() < fSquareZero )
    {
        /* This vector is the Y axis multiplied by a scalar, so we have
            to use another axis.
        */
        Vec3::cross(src, Vec3::UNIT_Y, &perp);
    }
    perp.normalize();
    return perp;
}

NS_CC_END
