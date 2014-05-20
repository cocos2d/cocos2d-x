/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "cocos2d.h"

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif

NS_CC_BEGIN

const Vec2 CCPointZero = Vec2::ZERO;

/* The "zero" size -- equivalent to Size(0, 0). */
const Size CCSizeZero = Size::ZERO;

/* The "zero" rectangle -- equivalent to Rect(0, 0, 0, 0). */
const Rect CCRectZero = Rect::ZERO;


const Color3B ccWHITE = Color3B::WHITE;
const Color3B ccYELLOW = Color3B::YELLOW;
const Color3B ccGREEN = Color3B::GREEN;
const Color3B ccBLUE = Color3B::BLUE;
const Color3B ccRED = Color3B::RED;
const Color3B ccMAGENTA = Color3B::MAGENTA;
const Color3B ccBLACK = Color3B::BLACK;
const Color3B ccORANGE = Color3B::ORANGE;
const Color3B ccGRAY = Color3B::GRAY;

const BlendFunc kCCBlendFuncDisable = BlendFunc::DISABLE;

const char* kCCShader_PositionTextureColor = GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR;
const char* kCCShader_PositionTextureColorAlphaTest = GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST;
const char* kCCShader_PositionColor = GLProgram::SHADER_NAME_POSITION_COLOR;
const char* kCCShader_PositionTexture = GLProgram::SHADER_NAME_POSITION_TEXTURE;
const char* kCCShader_PositionTexture_uColor = GLProgram::SHADER_NAME_POSITION_TEXTURE_U_COLOR;
const char* kCCShader_PositionTextureA8Color = GLProgram::SHADER_NAME_POSITION_TEXTURE_A8_COLOR;
const char* kCCShader_Position_uColor = GLProgram::SHADER_NAME_POSITION_U_COLOR;
const char* kCCShader_PositionLengthTexureColor = GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR;

// uniform names
const char* kCCUniformPMatrix_s = GLProgram::UNIFORM_NAME_P_MATRIX;
const char* kCCUniformMVMatrix_s = GLProgram::UNIFORM_NAME_MV_MATRIX;
const char* kCCUniformMVPMatrix_s = GLProgram::UNIFORM_NAME_MVP_MATRIX;
const char* kCCUniformTime_s = GLProgram::UNIFORM_NAME_TIME;
const char* kCCUniformSinTime_s = GLProgram::UNIFORM_NAME_SIN_TIME;
const char* kCCUniformCosTime_s	= GLProgram::UNIFORM_NAME_COS_TIME;
const char* kCCUniformRandom01_s = GLProgram::UNIFORM_NAME_RANDOM01;
const char* kCCUniformSampler_s	= GLProgram::UNIFORM_NAME_SAMPLER0;
const char* kCCUniformAlphaTestValue = GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE;

// Attribute names
const char* kCCAttributeNameColor = GLProgram::ATTRIBUTE_NAME_COLOR;
const char* kCCAttributeNamePosition = GLProgram::ATTRIBUTE_NAME_POSITION;
const char* kCCAttributeNameTexCoord = GLProgram::ATTRIBUTE_NAME_TEX_COORD;

void ccDrawInit()
{
    DrawPrimitives::init();
}

void ccDrawFree()
{
    DrawPrimitives::free();
}

void ccDrawPoint( const Vec2& point )
{
    DrawPrimitives::drawPoint(point);
}

void ccDrawPoints( const Vec2 *points, unsigned int numberOfPoints )
{
    DrawPrimitives::drawPoints(points, numberOfPoints);
}

void ccDrawLine( const Vec2& origin, const Vec2& destination )
{
    DrawPrimitives::drawLine(origin, destination);
}

void ccDrawRect( Vec2 origin, Vec2 destination )
{
    DrawPrimitives::drawRect(origin, destination);
}

void ccDrawSolidRect( Vec2 origin, Vec2 destination, Color4F color )
{
    DrawPrimitives::drawSolidRect(origin, destination, color);
}

void ccDrawPoly( const Vec2 *vertices, unsigned int numOfVertices, bool closePolygon )
{
    DrawPrimitives::drawPoly(vertices, numOfVertices, closePolygon);
}

void ccDrawSolidPoly( const Vec2 *poli, unsigned int numberOfPoints, Color4F color )
{
    DrawPrimitives::drawSolidPoly(poli, numberOfPoints, color);
}

void ccDrawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY)
{
    DrawPrimitives::drawCircle(center, radius, angle, segments, drawLineToCenter, scaleX, scaleY);
}

void ccDrawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter)
{
    DrawPrimitives::drawCircle(center, radius, angle, segments, drawLineToCenter);
}

void ccDrawSolidCircle( const Vec2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY)
{
    DrawPrimitives::drawSolidCircle(center, radius, angle, segments, scaleX, scaleY);
}

void ccDrawSolidCircle( const Vec2& center, float radius, float angle, unsigned int segments)
{
    DrawPrimitives::drawSolidCircle(center, radius, angle, segments);
}

void ccDrawQuadBezier(const Vec2& origin, const Vec2& control, const Vec2& destination, unsigned int segments)
{
    DrawPrimitives::drawQuadBezier(origin, control, destination, segments);
}

void ccDrawCubicBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments)
{
    DrawPrimitives::drawCubicBezier(origin, control1, control2, destination, segments);
}

void ccDrawCatmullRom( PointArray *arrayOfControlPoints, unsigned int segments )
{
    DrawPrimitives::drawCatmullRom(arrayOfControlPoints, segments);
}

void ccDrawCardinalSpline( PointArray *config, float tension,  unsigned int segments )
{
    DrawPrimitives::drawCardinalSpline(config, tension, segments);
}

void ccDrawColor4B( GLubyte r, GLubyte g, GLubyte b, GLubyte a )
{
    DrawPrimitives::setDrawColor4B(r, g, b, a);
}

void ccDrawColor4F( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
    DrawPrimitives::setDrawColor4F(r, g, b, a);
}

void ccPointSize( GLfloat pointSize )
{
    DrawPrimitives::setPointSize(pointSize);
}

MATRIX_STACK_TYPE currentActiveStackType = MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW;

void CC_DLL kmGLFreeAll(void)
{
    Director::getInstance()->resetMatrixStack();
}

void CC_DLL kmGLPushMatrix(void)
{
    Director::getInstance()->pushMatrix(currentActiveStackType);
}

void CC_DLL kmGLPopMatrix(void)
{
    Director::getInstance()->popMatrix(currentActiveStackType);
}

void CC_DLL kmGLMatrixMode(unsigned int mode)
{
    if(KM_GL_MODELVIEW == mode)
        currentActiveStackType = MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW;
    else if(KM_GL_PROJECTION == mode)
        currentActiveStackType = MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION;
    else if(KM_GL_TEXTURE == mode)
        currentActiveStackType = MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE;
    else
    {
        CC_ASSERT(false);
    }
}

void CC_DLL kmGLLoadIdentity(void)
{
    Director::getInstance()->loadIdentityMatrix(currentActiveStackType);
}

void CC_DLL kmGLLoadMatrix(const Mat4* pIn)
{
    Director::getInstance()->loadMatrix(currentActiveStackType, *pIn);
}

void CC_DLL kmGLMultMatrix(const Mat4* pIn)
{
    Director::getInstance()->multiplyMatrix(currentActiveStackType, *pIn);
}

void CC_DLL kmGLTranslatef(float x, float y, float z)
{
    Mat4 mat;
    Mat4::createTranslation(Vec3(x, y, z), &mat);
    Director::getInstance()->multiplyMatrix(currentActiveStackType, mat);
}

void CC_DLL kmGLRotatef(float angle, float x, float y, float z)
{
    Mat4 mat;
    Mat4::createRotation(Vec3(x, y, z), angle, &mat);
    Director::getInstance()->multiplyMatrix(currentActiveStackType, mat);
}

void CC_DLL kmGLScalef(float x, float y, float z)
{
    Mat4 mat;
    Mat4::createScale(x, y, z, &mat);
    Director::getInstance()->multiplyMatrix(currentActiveStackType, mat);
}

void CC_DLL kmGLGetMatrix(unsigned int mode, Mat4* pOut)
{
    if(KM_GL_MODELVIEW == mode)
        *pOut = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    else if(KM_GL_PROJECTION == mode)
        *pOut = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    else if(KM_GL_TEXTURE == mode)
        *pOut = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE);
    else
    {
        CC_ASSERT(false);
    }
}

Mat4* kmMat4Fill(Mat4* pOut, const float* pMat)
{
    pOut->set(pMat);
    return pOut;
}

Mat4* kmMat4Assign(Mat4* pOut, const Mat4* pIn)
{
    pOut->set(pIn->m);
    return pOut;
}

Mat4* kmMat4Identity(Mat4* pOut)
{
    *pOut = Mat4::IDENTITY;
    return pOut;
}

Mat4* kmMat4Inverse(Mat4* pOut, const Mat4* pM)
{
    *pOut = pM->getInversed();
    return pOut;
}

Mat4* kmMat4Transpose(Mat4* pOut, const Mat4* pIn)
{
    *pOut = pIn->getTransposed();
    return pOut;
}

Mat4* kmMat4Multiply(Mat4* pOut, const Mat4* pM1, const Mat4* pM2)
{
    *pOut = (*pM1) * (*pM2);
    return pOut;
}

Mat4* kmMat4Translation(Mat4* pOut, const float x, const float y, const float z)
{
    Mat4::createTranslation(x, y, z, pOut);
    return pOut;
}

Mat4* kmMat4RotationX(Mat4* pOut, const float radians)
{
    Mat4::createRotationX(radians, pOut);
    return pOut;
}

Mat4* kmMat4RotationY(Mat4* pOut, const float radians)
{
    Mat4::createRotationY(radians, pOut);
    return pOut;
}

Mat4* kmMat4RotationZ(Mat4* pOut, const float radians)
{
    Mat4::createRotationZ(radians, pOut);
    return pOut;
}

Mat4* kmMat4RotationAxisAngle(Mat4* pOut, const Vec3* axis, float radians)
{
    Mat4::createRotation(*axis, radians, pOut);
    return pOut;
}

Mat4* kmMat4Scaling(Mat4* pOut, const float x, const float y, const float z)
{
    Mat4::createScale(x, y, z, pOut);
    return pOut;
}

Mat4* kmMat4PerspectiveProjection(Mat4* pOut, float fovY, float aspect, float zNear, float zFar)
{
    Mat4::createPerspective(fovY, aspect, zNear, zFar, pOut);
    return pOut;
}

Mat4* kmMat4OrthographicProjection(Mat4* pOut, float left, float right, float bottom, float top, float nearVal, float farVal)
{
    Mat4::createOrthographicOffCenter(left, right, bottom, top, nearVal, farVal, pOut);
    return pOut;
}

Mat4* kmMat4LookAt(Mat4* pOut, const Vec3* pEye, const Vec3* pCenter, const Vec3* pUp)
{
    Mat4::createLookAt(*pEye, *pCenter, *pUp, pOut);
    return pOut;
}

Vec3* kmVec3Fill(Vec3* pOut, float x, float y, float z)
{
    pOut->x = x;
    pOut->y = y;
    pOut->z = z;
    return pOut;
}

float kmVec3Length(const Vec3* pIn)
{
    return pIn->length();
}

float kmVec3LengthSq(const Vec3* pIn)
{
    return pIn->lengthSquared();
}

CC_DLL Vec3* kmVec3Lerp(Vec3* pOut, const Vec3* pV1, const Vec3* pV2, float t)
{
    pOut->x = pV1->x + t * ( pV2->x - pV1->x );
    pOut->y = pV1->y + t * ( pV2->y - pV1->y );
    pOut->z = pV1->z + t * ( pV2->z - pV1->z );
    return pOut;
}

Vec3* kmVec3Normalize(Vec3* pOut, const Vec3* pIn)
{
    *pOut = pIn->getNormalized();
    return pOut;
}

Vec3* kmVec3Cross(Vec3* pOut, const Vec3* pV1, const Vec3* pV2)
{
    Vec3::cross(*pV1, *pV2, pOut);
    return pOut;
}

float kmVec3Dot(const Vec3* pV1, const Vec3* pV2)
{
    return Vec3::dot(*pV1, *pV2);
}

Vec3* kmVec3Add(Vec3* pOut, const Vec3* pV1, const Vec3* pV2)
{
    Vec3::add(*pV1, *pV2, pOut);
    return pOut;
}

Vec3* kmVec3Subtract(Vec3* pOut, const Vec3* pV1, const Vec3* pV2)
{
    Vec3::subtract(*pV1, *pV2, pOut);
    return pOut;
}

Vec3* kmVec3Transform(Vec3* pOut, const Vec3* pV1, const Mat4* pM)
{
    pM->transformPoint(*pV1, pOut);
    return pOut;
}

Vec3* kmVec3TransformNormal(Vec3* pOut, const Vec3* pV, const Mat4* pM)
{
    pM->transformVector(*pV, pOut);
    return pOut;
}

Vec3* kmVec3TransformCoord(Vec3* pOut, const Vec3* pV, const Mat4* pM)
{
    Vec4 v(pV->x, pV->y, pV->z, 1);
    pM->transformVector(&v);
    v = v * (1/v.w);
    pOut->set(v.x, v.y, v.z);
    return pOut;
}

Vec3* kmVec3Scale(Vec3* pOut, const Vec3* pIn, const float s)
{
    *pOut = *pIn * s;
    return pOut;
}

Vec3* kmVec3Assign(Vec3* pOut, const Vec3* pIn)
{
    *pOut = *pIn;
    return pOut;
}

Vec3* kmVec3Zero(Vec3* pOut)
{
    pOut->set(0, 0, 0);
    return pOut;
}

Vec2* kmVec2Fill(Vec2* pOut, float x, float y)
{
    pOut->set(x, y);
    return pOut;
}

float kmVec2Length(const Vec2* pIn)
{
    return pIn->length();
}

float kmVec2LengthSq(const Vec2* pIn)
{
    return pIn->lengthSquared();
}

Vec2* kmVec2Normalize(Vec2* pOut, const Vec2* pIn)
{
    *pOut = pIn->getNormalized();
    return pOut;
}

Vec2* kmVec2Lerp(Vec2* pOut, const Vec2* pV1, const Vec2* pV2, float t)
{
    pOut->x = pV1->x + t * ( pV2->x - pV1->x );
    pOut->y = pV1->y + t * ( pV2->y - pV1->y );
    return pOut;
}

Vec2* kmVec2Add(Vec2* pOut, const Vec2* pV1, const Vec2* pV2)
{
    Vec2::add(*pV1, *pV2, pOut);
    return pOut;
}

float kmVec2Dot(const Vec2* pV1, const Vec2* pV2)
{
    return Vec2::dot(*pV1, *pV2);
}

Vec2* kmVec2Subtract(Vec2* pOut, const Vec2* pV1, const Vec2* pV2)
{
    Vec2::subtract(*pV1, *pV2, pOut);
    return pOut;
}

Vec2* kmVec2Scale(Vec2* pOut, const Vec2* pIn, const float s)
{
    *pOut = *pIn * s;
    return pOut;
}

Vec2* kmVec2Assign(Vec2* pOut, const Vec2* pIn)
{
    *pOut = *pIn;
    return pOut;
}

Vec4* kmVec4Fill(Vec4* pOut, float x, float y, float z, float w)
{
    pOut->set(x, y, z, w);
    return pOut;
}

Vec4* kmVec4Add(Vec4* pOut, const Vec4* pV1, const Vec4* pV2)
{
    Vec4::add(*pV1, *pV2, pOut);
    return pOut;
}

float kmVec4Dot(const Vec4* pV1, const Vec4* pV2)
{
    return Vec4::dot(*pV1, *pV2);
}

float kmVec4Length(const Vec4* pIn)
{
    return pIn->length();
}

float kmVec4LengthSq(const Vec4* pIn)
{
    return pIn->lengthSquared();
}

Vec4* kmVec4Lerp(Vec4* pOut, const Vec4* pV1, const Vec4* pV2, float t)
{
    pOut->x = pV1->x + t * ( pV2->x - pV1->x );
    pOut->y = pV1->y + t * ( pV2->y - pV1->y );
    pOut->z = pV1->z + t * ( pV2->z - pV1->z );
    pOut->w = pV1->w + t * ( pV2->w - pV1->w );
    return pOut;
}

Vec4* kmVec4Normalize(Vec4* pOut, const Vec4* pIn)
{
    *pOut = pIn->getNormalized();
    return pOut;
}

Vec4* kmVec4Scale(Vec4* pOut, const Vec4* pIn, const float s)
{
    *pOut = *pIn * s;
    return pOut;
}

Vec4* kmVec4Subtract(Vec4* pOut, const Vec4* pV1, const Vec4* pV2)
{
    Vec4::subtract(*pV1, *pV2, pOut);
    return pOut;
}

Vec4* kmVec4Assign(Vec4* pOut, const Vec4* pIn)
{
    *pOut = *pIn;
    return pOut;
}

Vec4* kmVec4MultiplyMat4(Vec4* pOut, const Vec4* pV, const Mat4* pM)
{
    pM->transformVector(*pV, pOut);
    return pOut;
}

Vec4* kmVec4Transform(Vec4* pOut, const Vec4* pV, const Mat4* pM)
{
    pM->transformVector(*pV, pOut);
    return pOut;
}

const Vec3 KM_VEC3_NEG_Z = Vec3(0, 0, -1);
const Vec3 KM_VEC3_POS_Z = Vec3(0, 0, 1);
const Vec3 KM_VEC3_POS_Y = Vec3(0, 1, 0);
const Vec3 KM_VEC3_NEG_Y = Vec3(0, -1, 0);
const Vec3 KM_VEC3_NEG_X = Vec3(-1, 0, 0);
const Vec3 KM_VEC3_POS_X = Vec3(1, 0, 0);
const Vec3 KM_VEC3_ZERO = Vec3(0, 0, 0);

const Vec2 KM_VEC2_POS_Y = Vec2(0, 1);
const Vec2 KM_VEC2_NEG_Y = Vec2(0, -1);
const Vec2 KM_VEC2_NEG_X = Vec2(-1, 0);
const Vec2 KM_VEC2_POS_X = Vec2(1, 0);
const Vec2 KM_VEC2_ZERO = Vec2(0, 0);

NS_CC_END

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
