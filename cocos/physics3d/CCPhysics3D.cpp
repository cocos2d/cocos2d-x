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

#include "CCPhysics3D.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)



NS_CC_BEGIN

CC_DLL const char* physics3dVersion()
{
#if CC_ENABLE_BULLET_INTEGRATION
    return "bullet2.82";
#endif
}

NS_CC_END


cocos2d::Vec3 convertbtVector3ToVec3( const btVector3 &btVec3 )
{
    return cocos2d::Vec3(btVec3.x(), btVec3.y(), btVec3.z());
}

btVector3 convertVec3TobtVector3( const cocos2d::Vec3 &vec3 )
{
    return btVector3(vec3.x, vec3.y, vec3.z);
}

cocos2d::Mat4 convertbtTransformToMat4( const btTransform &btTrans )
{
    cocos2d::Mat4 mat;
    auto rot = btTrans.getBasis();
    auto row = rot.getRow(0);
    mat.m[0] = row.getX();
    mat.m[4] = row.getY();
    mat.m[8] = row.getZ();
    row = rot.getRow(1);
    mat.m[1] = row.getX();
    mat.m[5] = row.getY();
    mat.m[9] = row.getZ();
    row = rot.getRow(2);
    mat.m[2] = row.getX();
    mat.m[6] = row.getY();
    mat.m[10] = row.getZ();
    
    row = btTrans.getOrigin();
    mat.m[12] = row.getX();
    mat.m[13] = row.getY();
    mat.m[14] = row.getZ();
    return mat;
}

btTransform convertMat4TobtTransform( const cocos2d::Mat4 &mat4 )
{
    btTransform btTrans;
    btTrans.setFromOpenGLMatrix(mat4.m);
    return btTrans;
}

cocos2d::Quaternion convertbtQuatToQuat( const btQuaternion &btQuat )
{
    return cocos2d::Quaternion(btQuat.x(), btQuat.y(), btQuat.z(), btQuat.w());
}

btQuaternion convertQuatTobtQuat( const cocos2d::Quaternion &quat )
{
    return btQuaternion(quat.x, quat.y, quat.z, quat.w);
}

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif //CC_USE_3D_PHYSICS
