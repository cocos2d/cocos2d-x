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

NS_CC_BEGIN

const Vector2 CCPointZero = Vector2::ZERO;

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
const char* kCCUniformSampler_s	= GLProgram::UNIFORM_NAME_SAMPLER;
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

void ccDrawPoint( const Vector2& point )
{
    DrawPrimitives::drawPoint(point);
}

void ccDrawPoints( const Vector2 *points, unsigned int numberOfPoints )
{
    DrawPrimitives::drawPoints(points, numberOfPoints);
}

void ccDrawLine( const Vector2& origin, const Vector2& destination )
{
    DrawPrimitives::drawLine(origin, destination);
}

void ccDrawRect( Vector2 origin, Vector2 destination )
{
    DrawPrimitives::drawRect(origin, destination);
}

void ccDrawSolidRect( Vector2 origin, Vector2 destination, Color4F color )
{
    DrawPrimitives::drawSolidRect(origin, destination, color);
}

void ccDrawPoly( const Vector2 *vertices, unsigned int numOfVertices, bool closePolygon )
{
    DrawPrimitives::drawPoly(vertices, numOfVertices, closePolygon);
}

void ccDrawSolidPoly( const Vector2 *poli, unsigned int numberOfPoints, Color4F color )
{
    DrawPrimitives::drawSolidPoly(poli, numberOfPoints, color);
}

void ccDrawCircle( const Vector2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY)
{
    DrawPrimitives::drawCircle(center, radius, angle, segments, drawLineToCenter, scaleX, scaleY);
}

void ccDrawCircle( const Vector2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter)
{
    DrawPrimitives::drawCircle(center, radius, angle, segments, drawLineToCenter);
}

void ccDrawSolidCircle( const Vector2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY)
{
    DrawPrimitives::drawSolidCircle(center, radius, angle, segments, scaleX, scaleY);
}

void ccDrawSolidCircle( const Vector2& center, float radius, float angle, unsigned int segments)
{
    DrawPrimitives::drawSolidCircle(center, radius, angle, segments);
}

void ccDrawQuadBezier(const Vector2& origin, const Vector2& control, const Vector2& destination, unsigned int segments)
{
    DrawPrimitives::drawQuadBezier(origin, control, destination, segments);
}

void ccDrawCubicBezier(const Vector2& origin, const Vector2& control1, const Vector2& control2, const Vector2& destination, unsigned int segments)
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

void CC_DLL kmGLLoadMatrix(const Matrix* pIn)
{
    Director::getInstance()->loadMatrix(currentActiveStackType, *pIn);
}

void CC_DLL kmGLMultMatrix(const Matrix* pIn)
{
    Director::getInstance()->multiplyMatrix(currentActiveStackType, *pIn);
}

void CC_DLL kmGLTranslatef(float x, float y, float z)
{
    Matrix mat;
    Matrix::createTranslation(Vector3(x, y, z), &mat);
    Director::getInstance()->multiplyMatrix(currentActiveStackType, mat);
}

void CC_DLL kmGLRotatef(float angle, float x, float y, float z)
{
    Matrix mat;
    Matrix::createRotation(Vector3(x, y, z), angle, &mat);
    Director::getInstance()->multiplyMatrix(currentActiveStackType, mat);
}

void CC_DLL kmGLScalef(float x, float y, float z)
{
    Matrix mat;
    Matrix::createScale(x, y, z, &mat);
    Director::getInstance()->multiplyMatrix(currentActiveStackType, mat);
}

void CC_DLL kmGLGetMatrix(unsigned int mode, Matrix* pOut)
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

Matrix* kmMat4Fill(Matrix* pOut, const float* pMat)
{
    pOut->set(pMat);
    return pOut;
}

Matrix* kmMat4Assign(Matrix* pOut, const Matrix* pIn)
{
    pOut->set(pIn->m);
    return pOut;
}

Matrix* kmMat4Identity(Matrix* pOut)
{
    *pOut = Matrix::identity();
    return pOut;
}

Matrix* kmMat4Inverse(Matrix* pOut, const Matrix* pM)
{
    pM->invert(pOut);
    return pOut;
}

Matrix* kmMat4Transpose(Matrix* pOut, const Matrix* pIn)
{
    pIn->transpose(pOut);
    return pOut;
}

Matrix* kmMat4Multiply(Matrix* pOut, const Matrix* pM1, const Matrix* pM2)
{
    *pOut = (*pM1) * (*pM2);
    return pOut;
}

Matrix* kmMat4Translation(Matrix* pOut, const float x, const float y, const float z)
{
    Matrix::createTranslation(x, y, z, pOut);
    return pOut;
}

Matrix* kmMat4RotationX(Matrix* pOut, const float radians)
{
    Matrix::createRotationX(radians, pOut);
    return pOut;
}

Matrix* kmMat4RotationY(Matrix* pOut, const float radians)
{
    Matrix::createRotationY(radians, pOut);
    return pOut;
}

Matrix* kmMat4RotationZ(Matrix* pOut, const float radians)
{
    Matrix::createRotationZ(radians, pOut);
    return pOut;
}

Matrix* kmMat4RotationAxisAngle(Matrix* pOut, const struct Vector3* axis, float radians)
{
    Matrix::createRotation(*axis, radians, pOut);
    return pOut;
}

Matrix* kmMat4Scaling(Matrix* pOut, const float x, const float y, const float z)
{
    Matrix::createScale(x, y, z, pOut);
    return pOut;
}

Matrix* kmMat4PerspectiveProjection(Matrix* pOut, float fovY, float aspect, float zNear, float zFar)
{
    Matrix::createPerspective(fovY, aspect, zNear, zFar, pOut);
    return pOut;
}

Matrix* kmMat4OrthographicProjection(Matrix* pOut, float left, float right, float bottom, float top, float nearVal, float farVal)
{
    Matrix::createOrthographicOffCenter(left, right, bottom, top, nearVal, farVal, pOut);
    return pOut;
}

Matrix* kmMat4LookAt(Matrix* pOut, const struct Vector3* pEye, const struct Vector3* pCenter, const struct Vector3* pUp)
{
    Matrix::createLookAt(*pEye, *pCenter, *pUp, pOut);
    return pOut;
}

Vector3* kmVec3Fill(Vector3* pOut, float x, float y, float z)
{
    pOut->x = x;
    pOut->y = y;
    pOut->z = z;
    return pOut;
}

float kmVec3Length(const Vector3* pIn)
{
    return pIn->length();
}

float kmVec3LengthSq(const Vector3* pIn)
{
    return pIn->lengthSquared();
}

CC_DLL Vector3* kmVec3Lerp(Vector3* pOut, const Vector3* pV1, const Vector3* pV2, float t)
{
    pOut->x = pV1->x + t * ( pV2->x - pV1->x );
    pOut->y = pV1->y + t * ( pV2->y - pV1->y );
    pOut->z = pV1->z + t * ( pV2->z - pV1->z );
    return pOut;
}

Vector3* kmVec3Normalize(Vector3* pOut, const Vector3* pIn)
{
    pIn->normalize(pOut);
    return pOut;
}

Vector3* kmVec3Cross(Vector3* pOut, const Vector3* pV1, const Vector3* pV2)
{
    Vector3::cross(*pV1, *pV2, pOut);
    return pOut;
}

float kmVec3Dot(const Vector3* pV1, const Vector3* pV2)
{
    return Vector3::dot(*pV1, *pV2);
}

Vector3* kmVec3Add(Vector3* pOut, const Vector3* pV1, const Vector3* pV2)
{
    Vector3::add(*pV1, *pV2, pOut);
    return pOut;
}

Vector3* kmVec3Subtract(Vector3* pOut, const Vector3* pV1, const Vector3* pV2)
{
    Vector3::subtract(*pV1, *pV2, pOut);
    return pOut;
}

Vector3* kmVec3Transform(Vector3* pOut, const Vector3* pV1, const Matrix* pM)
{
    pM->transformPoint(*pV1, pOut);
    return pOut;
}

Vector3* kmVec3TransformNormal(Vector3* pOut, const Vector3* pV, const Matrix* pM)
{
    pM->transformVector(*pV, pOut);
    return pOut;
}

Vector3* kmVec3TransformCoord(Vector3* pOut, const Vector3* pV, const Matrix* pM)
{
    Vector4 v(pV->x, pV->y, pV->z, 1);
    pM->transformVector(&v);
    v = v * (1/v.w);
    pOut->set(v.x, v.y, v.z);
    return pOut;
}

Vector3* kmVec3Scale(Vector3* pOut, const Vector3* pIn, const float s)
{
    *pOut = *pIn * s;
    return pOut;
}

Vector3* kmVec3Assign(Vector3* pOut, const Vector3* pIn)
{
    *pOut = *pIn;
    return pOut;
}

Vector3* kmVec3Zero(Vector3* pOut)
{
    pOut->set(0, 0, 0);
    return pOut;
}

Vector2* kmVec2Fill(Vector2* pOut, float x, float y)
{
    pOut->set(x, y);
    return pOut;
}

float kmVec2Length(const Vector2* pIn)
{
    return pIn->length();
}

float kmVec2LengthSq(const Vector2* pIn)
{
    return pIn->lengthSquared();
}

Vector2* kmVec2Normalize(Vector2* pOut, const Vector2* pIn)
{
    pIn->normalize(pOut);
    return pOut;
}

Vector2* kmVec2Lerp(Vector2* pOut, const Vector2* pV1, const Vector2* pV2, float t)
{
    pOut->x = pV1->x + t * ( pV2->x - pV1->x );
    pOut->y = pV1->y + t * ( pV2->y - pV1->y );
    return pOut;
}

Vector2* kmVec2Add(Vector2* pOut, const Vector2* pV1, const Vector2* pV2)
{
    Vector2::add(*pV1, *pV2, pOut);
    return pOut;
}

float kmVec2Dot(const Vector2* pV1, const Vector2* pV2)
{
    return Vector2::dot(*pV1, *pV2);
}

Vector2* kmVec2Subtract(Vector2* pOut, const Vector2* pV1, const Vector2* pV2)
{
    Vector2::subtract(*pV1, *pV2, pOut);
    return pOut;
}

Vector2* kmVec2Scale(Vector2* pOut, const Vector2* pIn, const float s)
{
    *pOut = *pIn * s;
    return pOut;
}

Vector2* kmVec2Assign(Vector2* pOut, const Vector2* pIn)
{
    *pOut = *pIn;
    return pOut;
}

Vector4* kmVec4Fill(Vector4* pOut, float x, float y, float z, float w)
{
    pOut->set(x, y, z, w);
    return pOut;
}

Vector4* kmVec4Add(Vector4* pOut, const Vector4* pV1, const Vector4* pV2)
{
    Vector4::add(*pV1, *pV2, pOut);
    return pOut;
}

float kmVec4Dot(const Vector4* pV1, const Vector4* pV2)
{
    return Vector4::dot(*pV1, *pV2);
}

float kmVec4Length(const Vector4* pIn)
{
    return pIn->length();
}

float kmVec4LengthSq(const Vector4* pIn)
{
    return pIn->lengthSquared();
}

Vector4* kmVec4Lerp(Vector4* pOut, const Vector4* pV1, const Vector4* pV2, float t)
{
    pOut->x = pV1->x + t * ( pV2->x - pV1->x );
    pOut->y = pV1->y + t * ( pV2->y - pV1->y );
    pOut->z = pV1->z + t * ( pV2->z - pV1->z );
    pOut->w = pV1->w + t * ( pV2->w - pV1->w );
    return pOut;
}

Vector4* kmVec4Normalize(Vector4* pOut, const Vector4* pIn)
{
    pIn->normalize(pOut);
    return pOut;
}

Vector4* kmVec4Scale(Vector4* pOut, const Vector4* pIn, const float s)
{
    *pOut = *pIn * s;
    return pOut;
}

Vector4* kmVec4Subtract(Vector4* pOut, const Vector4* pV1, const Vector4* pV2)
{
    Vector4::subtract(*pV1, *pV2, pOut);
    return pOut;
}

Vector4* kmVec4Assign(Vector4* pOut, const Vector4* pIn)
{
    *pOut = *pIn;
    return pOut;
}

Vector4* kmVec4MultiplyMat4(Vector4* pOut, const Vector4* pV, const Matrix* pM)
{
    pM->transformVector(*pV, pOut);
    return pOut;
}

Vector4* kmVec4Transform(Vector4* pOut, const Vector4* pV, const Matrix* pM)
{
    pM->transformVector(*pV, pOut);
    return pOut;
}

NS_CC_END
