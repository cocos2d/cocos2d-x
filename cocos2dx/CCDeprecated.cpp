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

#include "cocos2d.h"

NS_CC_BEGIN

const Point CCPointZero = Point::ZERO;

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

const BlendFunc kCCBlendFuncDisable = BlendFunc::BLEND_FUNC_DISABLE;

const int kCCVertexAttrib_Position = GLProgram::VERTEX_ATTRIB_POSITION;
const int kCCVertexAttrib_Color = GLProgram::VERTEX_ATTRIB_COLOR;
const int kCCVertexAttrib_TexCoords = GLProgram::VERTEX_ATTRIB_TEX_COORDS;
const int kCCVertexAttrib_MAX = GLProgram::VERTEX_ATTRIB_MAX;

const int kCCUniformPMatrix = GLProgram::UNIFORM_P_MATRIX;
const int kCCUniformMVMatrix = GLProgram::UNIFORM_MV_MATRIX;
const int kCCUniformMVPMatrix = GLProgram::UNIFORM_MVP_MATRIX;
const int kCCUniformTime = GLProgram::UNIFORM_TIME;
const int kCCUniformSinTime = GLProgram::UNIFORM_SIN_TIME;
const int kCCUniformCosTime = GLProgram::UNIFORM_COS_TIME;
const int kCCUniformRandom01 = GLProgram::UNIFORM_RANDOM01;
const int kCCUniformSampler = GLProgram::UNIFORM_SAMPLER;
const int kCCUniform_MAX = GLProgram::UNIFORM_MAX;

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
const char*    kCCAttributeNameColor = GLProgram::ATTRIBUTE_NAME_COLOR;
const char*    kCCAttributeNamePosition = GLProgram::ATTRIBUTE_NAME_POSITION;
const char*    kCCAttributeNameTexCoord = GLProgram::ATTRIBUTE_NAME_TEX_COORD;

const int kCCVertexAttribFlag_None = VERTEX_ATTRIB_FLAT_NONE;
const int kCCVertexAttribFlag_Position = VERTEX_ATTRIB_FLAG_POSITION;
const int kCCVertexAttribFlag_Color = VERTEX_ATTRIB_FLAG_COLOR;
const int kCCVertexAttribFlag_TexCoords = VERTEX_ATTRIB_FLAG_TEX_COORDS;
const int kCCVertexAttribFlag_PosColorTex = VERTEX_ATTRIB_FLAG_POS_COLOR_TEX;

const int kCCProgressTimerTypeRadial = ProgressTimer::RADIAL;
const int kCCProgressTimerTypeBar = ProgressTimer::BAR;

const int kCCDirectorProjection2D = Director::PROJECTION_2D;
const int kCCDirectorProjection3D = Director::PROJECTION_3D;
const int kCCDirectorProjectionCustom = Director::PROJECTION_CUSTOM;
const int kCCDirectorProjectionDefault = Director::PROJECTION_DEFAULT;

const int ConfigurationError = Configuration::ERROR;
const int ConfigurationString = Configuration::STRING;
const int ConfigurationInt = Configuration::INT;
const int ConfigurationDouble = Configuration::DOUBLE;
const int ConfigurationBoolean = Configuration::BOOLEAN;

const int kCCParticleDurationInfinity = ParticleSystem::DURATION_INFINITY;
const int kCCParticleStartSizeEqualToEndSize = ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE;
const int kCCParticleStartRadiusEqualToEndRadius = ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS;

const int kCCParticleModeGravity = ParticleSystem::MODE_GRAVITY;
const int kCCParticleModeRadius = ParticleSystem::MODE_RADIUS;

const int kCCPositionTypeFree =  ParticleSystem::POSITION_TYPE_FREE;
const int kCCPositionTypeRelative =  ParticleSystem::POSITION_TYPE_RELATIVE;
const int kCCPositionTypeGrouped =  ParticleSystem::POSITION_TYPE_GROUPED;

const int kCCVerticalTextAlignmentTop = Label::VERTICAL_TEXT_ALIGNMENT_TOP;
const int kCCVerticalTextAlignmentCenter = Label::VERTICAL_TEXT_ALIGNMENT_CENTER;
const int kCCVerticalTextAlignmentBottom = Label::VERTICAL_TEXT_ALIGNMENT_BOTTOM;

const int kCCTextAlignmentLeft = Label::TEXT_ALIGNMENT_LEFT;
const int kCCTextAlignmentCenter = Label::TEXT_ALIGNMENT_CENTER;
const int kCCTextAlignmentRight = Label::TEXT_ALIGNMENT_RIGHT;

const int kCCTexture2DPixelFormat_RGBA8888 = Texture2D::PIXEL_FORMAT_RGBA8888;
const int kCCTexture2DPixelFormat_RGB888 = Texture2D::PIXEL_FORMAT_RGB888;
const int kCCTexture2DPixelFormat_RGB565 = Texture2D::PIXEL_FORMAT_RGB565;
const int kCCTexture2DPixelFormat_A8 = Texture2D::PIXEL_FORMAT_A8;
const int kCCTexture2DPixelFormat_I8 = Texture2D::PIXEL_FORMAT_I8;
const int kCCTexture2DPixelFormat_AI88 = Texture2D::PIXEL_FORMAT_AI88;
const int kCCTexture2DPixelFormat_RGBA4444 = Texture2D::PIXEL_FORMAT_RGBA4444;
const int kCCTexture2DPixelFormat_RGB5A1 = Texture2D::PIXEL_FORMAT_RGB5A1;
const int kCCTexture2DPixelFormat_PVRTC4 = Texture2D::PIXEL_FORMAT_PRVTC4;
const int kCCTexture2DPixelFormat_PVRTC2 = Texture2D::PIXEL_FORMAT_PRVTC2;
const int kCCTexture2DPixelFormat_Default = Texture2D::PIXEL_FORMAT_DEFAULT;

const int kCCMenuHandlerPriority = Menu::HANDLER_PRIORITY;
const int kCCMenuStateWaiting = Menu::STATE_WAITING;
const int kCCMenuStateTrackingTouch = Menu::STATE_TRACKING_TOUCH;

const int kCCTouchesOneByOne = Layer::TOUCHES_ONE_BY_ONE;
const int kCCTouchesAllAtOnce = Layer::TOUCHES_ALL_AT_ONCE;

const int kCCImageFormatPNG = Image::FORMAT_PNG;
const int kCCImageFormatJPEG = Image::FORMAT_JPG;

NS_CC_END