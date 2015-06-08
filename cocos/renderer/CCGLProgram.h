/****************************************************************************
Copyright 2011 Jeff Lamarche
Copyright 2012 Goffredo Marocchi
Copyright 2012 Ricardo Quesada
Copyright 2012 cocos2d-x.org
Copyright 2013-2014 Chukong Technologies Inc.


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

#ifndef __CCGLPROGRAM_H__
#define __CCGLPROGRAM_H__

#include <unordered_map>
#include <string>

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "platform/CCGL.h"
#include "math/CCMath.h"

/**
 * @addtogroup support
 * @{
 */

NS_CC_BEGIN

class GLProgram;
class Director;
//FIXME: these two typedefs would be deprecated or removed in version 4.0.
typedef void (*GLInfoFunction)(GLuint program, GLenum pname, GLint* params);
typedef void (*GLLogFunction) (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);

/**
@struct VertexAttrib
@brief
@~english VertexAttrib is a structure to encapsulate data got from glGetActiveAttrib. 
@~chinese VertexAttrib用于封装顶点属性，该属性从glGetActiveAttrib中获取。
*/
struct VertexAttrib
{
    /**
    @~english Index of attribute, start from 0. 
    @~chinese 索引的属性,从0开始。
    */
    GLuint index;
    /**
    @~english Number of Data type in the attribute, could range from 1-4. 
    @~chinese 属性值数组的个数,范围从1 - 4。
    */
    GLint size;
    /**
    @~english Data type of the attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc. 
    @~chinese 数据类型,可以是GL_FLOAT，GL_UNSIGNED_BYTE等等。
    */
    GLenum type;
    /**
    @~english The string name in vertex shader. 
    @~chinese 在vertex shader中的字符串.
    */
    std::string name;
};
/**
@struct Uniform
@brief
@~english Uniform is a structure to encapsulate data got from glGetActiveUniform and glGetUniformLocation. 
@~chinese Uniform是一个结构，用来来封装从glGetActiveUniform，glGetUniformLocation中获得的数据。
*/
struct Uniform
{
    /**
    @~english The place where the uniform placed, starts from 0. 
    @~chinese Uniform在shader中的存储位置,从0开始。
    */
    GLint location;
    /**
    @~english Number of data type in Uniform. 
    @~chinese Unifrom数值中的数据个数。
    */
    GLint size;
    /**
    @~english Data type of the Uniform. 
    @~chinese 数据类型。
    */
    GLenum type;
    /**
    @~english String of the uniform name. 
    @~chinese Shader中的Unifrom名字。*/
    std::string name;
};

/** 
@class GLProgram
@brief
@~english 
 Class that implements a openGL Program


 * @~chinese
 * 封装openGL Program的类
 * 
 * 
 @since v2.0.0
 */
class CC_DLL GLProgram : public Ref
{
    friend class GLProgramState;
    friend class VertexAttribBinding;

public:
    /**
    @~english Enum the preallocated vertex attribute.  
    @~chinese 枚举预先分配的顶点属性。*/
    enum
    {
        /**@~english Index 0 will be used as Position. @~chinese 索引0将被用作位置。*/
        VERTEX_ATTRIB_POSITION,
        /**@~english Index 1 will be used as Color. @~chinese 指数1将被用作颜色。*/
        VERTEX_ATTRIB_COLOR,
        /**@~english Index 2 will be used as Tex coord unit 0. @~chinese 指数2将被用作第0套纹理坐标。*/
        VERTEX_ATTRIB_TEX_COORD,
        /**@~english Index 3 will be used as Tex coord unit 1. @~chinese 指数3将被用作第1套纹理坐标。*/
        VERTEX_ATTRIB_TEX_COORD1,
        /**@~english Index 4 will be used as Tex coord unit 2. @~chinese 指数4将被用作第2套纹理坐标。*/
        VERTEX_ATTRIB_TEX_COORD2,
        /**@~english Index 5 will be used as Tex coord unit 3. @~chinese 指数5将被用作第3套纹理坐标。*/
        VERTEX_ATTRIB_TEX_COORD3,
        /**@~english Index 6 will be used as Normal. @~chinese 指数6将被用作法线。*/
        VERTEX_ATTRIB_NORMAL,
        /**@~english Index 7 will be used as Blend weight for hardware skin. @~chinese 指数7将被用作Blend Weight,用于蒙皮计算。*/
        VERTEX_ATTRIB_BLEND_WEIGHT,
        /**@~english Index 8 will be used as Blend index. @~chinese 指数8将被用作Blend Index，用于蒙皮计算。*/
        VERTEX_ATTRIB_BLEND_INDEX,
        VERTEX_ATTRIB_MAX,

        // backward compatibility
        VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
    };

    /**@~english Preallocated uniform handle. @~chinese 预先分配的uniform句柄.*/
    enum
    {
        /**@~english Ambient color. @~chinese 环境光颜色。*/
        UNIFORM_AMBIENT_COLOR,
        /**@~english Projection matrix. @~chinese 投影矩阵。*/
        UNIFORM_P_MATRIX,
        /**@~english Model view matrix. @~chinese ModelView矩阵。*/
        UNIFORM_MV_MATRIX,
        /**@~english Model view projection matrix. @~chinese ModelView和投影连乘矩阵。*/
        UNIFORM_MVP_MATRIX,
        /**@~english Normal matrix. @~chinese 法线的变换矩阵。*/
        UNIFORM_NORMAL_MATRIX,
        /**@~english Time. @~chinese 时间。*/
        UNIFORM_TIME,
        /**@~english sin(Time). @~chinese 时间的sin值。*/
        UNIFORM_SIN_TIME,
        /**@~english cos(Time). @~chinese 时间的cos值。*/
        UNIFORM_COS_TIME,
        /**@~english Random number. @~chinese 随机数。*/
        UNIFORM_RANDOM01,
        /** @{@~english
        * Sampler 0-3, used for texture.
         * @~chinese 
         * 采样器 0-3, 用于纹理采样.
        */
        UNIFORM_SAMPLER0,
        UNIFORM_SAMPLER1,
        UNIFORM_SAMPLER2,
        UNIFORM_SAMPLER3,
        /**@}*/
        UNIFORM_MAX,
    };

    /**
    @name Built Shader types
    @{
    */

    /**
    @~english Built in shader for 2d. Support Position, Texture and Color vertex attribute. 
    @~chinese 内置shader。支持位置，颜色，纹理坐标。
    */
    static const char* SHADER_NAME_POSITION_TEXTURE_COLOR;
    /**
    @~english Built in shader for 2d. Support Position, Texture and Color vertex attribute, but without multiply vertex by MVP matrix. 
    @~chinese 内置shader。支持位置，颜色，纹理坐标,但顶点不需要乘以MVP矩阵。
    */
    static const char* SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP;
    /**
    @~english Built in shader for 2d. Support Position, Texture vertex attribute, but include alpha test. 
    @~chinese 内置shader。支持位置，纹理坐标，包含alpha测试。
    */
    static const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST;
    /**
    @~english Built in shader for 2d. Support Position, Texture and Color vertex attribute, include alpha test and without multiply vertex by MVP matrix. 
    @~chinese 内置shader。支持位置，纹理坐标，包含alpha测试。顶点不需要乘以MVP矩阵。
    */
    static const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV;
    /**
    @~english Built in shader for 2d. Support Position, Color vertex attribute. 
    @~chinese 内置shader。支持位置，颜色。
    */
    static const char* SHADER_NAME_POSITION_COLOR;
    /**
    @~english Built in shader for 2d. Support Position, Color, Texture vertex attribute. texture coordinate will used as point size. 
    @~chinese 内置shader。支持位置，颜色，纹理坐标，纹理坐标会被当作point size使用，用于画点。
    */
    static const char* SHADER_NAME_POSITION_COLOR_TEXASPOINTSIZE;
    /**
    @~english Built in shader for 2d. Support Position, Color vertex attribute, without multiply vertex by MVP matrix. 
    @~chinese 内置shader。支持位置，颜色，顶点不需要乘以MVP矩阵。
    */
    static const char* SHADER_NAME_POSITION_COLOR_NO_MVP;
    /**
    @~english Built in shader for 2d. Support Position, Texture vertex attribute. 
    @~chinese 内置shader。支持位置，纹理坐标。
    */
    static const char* SHADER_NAME_POSITION_TEXTURE;
    /**
    @~english Built in shader for 2d. Support Position, Texture vertex attribute. with a specified uniform as color 
    @~chinese 内置shader。支持位置，纹理坐标，颜色通过uniform指定。
    */
    static const char* SHADER_NAME_POSITION_TEXTURE_U_COLOR;
    /**
    @~english Built in shader for 2d. Support Position, Texture and Color vertex attribute. but alpha will be the multiplication of color attribute and texture. 
    @~chinese 内置shader。支持位置，颜色，纹理坐标，但是alpha是颜色属性和纹理的乘值。
    */
    static const char* SHADER_NAME_POSITION_TEXTURE_A8_COLOR;
    /**
    @~english Built in shader for 2d. Support Position, with color specified by a uniform. 
    @~chinese 内置shader。支持位置，颜色通过uniform指定。
    */
    static const char* SHADER_NAME_POSITION_U_COLOR;
    /**
    @~english Built in shader for draw a sector with 90 degrees with center at bottom left point. 
    @~chinese 内置shader。用于画一个90扇形，圆心在左下角。
    */
    static const char* SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR;

    /**
    @~english Built in shader for ui effects.
    @~chinese 内置shader。用于渲染UI的变灰效果。
    */
    static const char* SHADER_NAME_POSITION_GRAYSCALE;
    /** @{@~english
        Built in shader for label and label with effects.
     * @~chinese 
     * 内置shader。用于Label和Label特效的渲染。
    */
    static const char* SHADER_NAME_LABEL_NORMAL;
    static const char* SHADER_NAME_LABEL_OUTLINE;
    static const char* SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL;
    static const char* SHADER_NAME_LABEL_DISTANCEFIELD_GLOW;

    /**
    @~english Built in shader used for 3D, support Position vertex attribute, with color specified by a uniform. 
    @~chinese 内置shader。支持位置。颜色通过uniform指定。
    */
    static const char* SHADER_3D_POSITION;
    /**
    @~english Built in shader used for 3D, support Position and Texture vertex attribute, with color specified by a uniform. 
    @~chinese 内置shader。支持位置，纹理坐标。颜色通过uniform指定。
    */
    static const char* SHADER_3D_POSITION_TEXTURE;
    /**@~english
    Built in shader used for 3D, support Position (Skeletal animation by hardware skin) and Texture vertex attribute,
    with color specified by a uniform.
     * @~chinese 
     * 内置shader。支持位置，纹理坐标，和硬件的蒙皮。颜色通过uniform指定。
    */
    static const char* SHADER_3D_SKINPOSITION_TEXTURE;
    /**@~english
    Built in shader used for 3D, support Position and Normal vertex attribute, used in lighting. with color specified by a uniform.
     * @~chinese 
     * 内置shader，用于3D光照渲染。支持顶点，法线。颜色通过uniform指定。
    */
    static const char* SHADER_3D_POSITION_NORMAL;
    /**@~english
    Built in shader used for 3D, support Position, Normal, Texture vertex attribute, used in lighting. with color specified by a uniform.
     * @~chinese 
     * 内置shader，用于3D光照渲染。支持位置，法线，纹理坐标。颜色通过uniform指定。
    */
    static const char* SHADER_3D_POSITION_NORMAL_TEXTURE;
    /**@~english
    Built in shader used for 3D, support Position(skeletal animation by hardware skin), Normal, Texture vertex attribute,
    used in lighting. with color specified by a uniform.
     * @~chinese 
     * 内置shader，用于3D光照渲染。支持顶点，法线，纹理坐标，和硬件的蒙皮。颜色通过uniform指定。
    */
    static const char* SHADER_3D_SKINPOSITION_NORMAL_TEXTURE;
    /**@~english
    Built in shader for particles, support Position and Texture, with a color specified by a uniform.
     * @~chinese 
     * 内置shader，用于3D粒子（贴图）渲染。
    */
    static const char* SHADER_3D_PARTICLE_TEXTURE;
    /**@~english
    Built in shader for particles, support Position, with a color specified by a uniform.
     * @~chinese 
     * 内置shader，用于3D粒子（颜色）渲染。
    */
    static const char* SHADER_3D_PARTICLE_COLOR;

    /**@~english
     Built in shader for skybox
     * @~chinese 
     * 内置shader，用于天空盒。
     */
    static const char* SHADER_3D_SKYBOX;

    /**@~english
     Built in shader for terrain
     * @~chinese 
     * 内置shader，用于地形。
     */
    static const char* SHADER_3D_TERRAIN;
    
    /**@~english
     Built in shader for camera clear
     * @~chinese 
     * 内置shader，用于camera清除背景。
     */
    static const char* SHADER_CAMERA_CLEAR;
    /**
    end of built shader types.
    @}
    */

    /**
    @name Built uniform names
    @{
    */
    /**@~english Ambient Color uniform. @~chinese Uniform值: 环境光颜色。*/
    static const char* UNIFORM_NAME_AMBIENT_COLOR;
    /**@~english Projection Matrix uniform. @~chinese Uniform值: 投影矩阵。*/
    static const char* UNIFORM_NAME_P_MATRIX;
    /**@~english Model view matrix uniform. @~chinese Uniform值: ModelView矩阵。*/
    static const char* UNIFORM_NAME_MV_MATRIX;
    /**@~english Model view projection uniform. @~chinese Uniform值: ModelView和投影矩阵的连乘。*/
    static const char* UNIFORM_NAME_MVP_MATRIX;
    /**@~english Normal matrix uniform. @~chinese Uniform值: 法线的变换矩阵。*/
    static const char* UNIFORM_NAME_NORMAL_MATRIX;
    /**@~english Time uniform. @~chinese Uniform值: 时间。*/
    static const char* UNIFORM_NAME_TIME;
    /**@~english Sin time uniform. @~chinese Uniform值: 时间的sin值。*/
    static const char* UNIFORM_NAME_SIN_TIME;
    /**@~english Cos time uniform. @~chinese Uniform值: 时间的cos值。*/
    static const char* UNIFORM_NAME_COS_TIME;
    /**@~english Random number uniform. @~chinese Uniform值: 随机数。*/
    static const char* UNIFORM_NAME_RANDOM01;
    /**
    @{ @~englishSampler uniform 0-3, used for textures. @~chinese Uniform值: 采样器0-3。
    */
    static const char* UNIFORM_NAME_SAMPLER0;
    static const char* UNIFORM_NAME_SAMPLER1;
    static const char* UNIFORM_NAME_SAMPLER2;
    static const char* UNIFORM_NAME_SAMPLER3;
    /**
    @}
    */
    /**@~english Alpha test value uniform. @~chinese Uniform值: Alpha Test。*/
    static const char* UNIFORM_NAME_ALPHA_TEST_VALUE;
    /**
    end of Built uniform names
    @}
    */

    /**
        @name Built Attribute names
        @{
    */
    /**@~english Attribute color. @~chinese 颜色属性。*/
    static const char* ATTRIBUTE_NAME_COLOR;
    /**@~english Attribute position. @~chinese 位置属性。*/
    static const char* ATTRIBUTE_NAME_POSITION;
    /**@{ @~english Attribute Texcoord 0-3. @~chinese 纹理坐标属性(0-3).*/
    static const char* ATTRIBUTE_NAME_TEX_COORD;
    static const char* ATTRIBUTE_NAME_TEX_COORD1;
    static const char* ATTRIBUTE_NAME_TEX_COORD2;
    static const char* ATTRIBUTE_NAME_TEX_COORD3;
    /**@}*/
    /**@~english Attribute normal. @~chinese 法线属性。*/
    static const char* ATTRIBUTE_NAME_NORMAL;
    /**@~english Attribute blend weight. @~chinese Blend Weight属性。*/
    static const char* ATTRIBUTE_NAME_BLEND_WEIGHT;
    /**@~english Attribute blend index. @~chinese Blend index属性。*/
    static const char* ATTRIBUTE_NAME_BLEND_INDEX;
    /**
    end of Built Attribute names
    @}
    */

    /**@~english Constructor. @~chinese 构造函数。*/
    GLProgram();
    /**@~english Destructor. @~chinese 析构函数。*/
    virtual ~GLProgram();

    /** @{@~english
    Create or Initializes the GLProgram with a vertex and fragment with bytes array.
     * @~chinese 
     * 从给定的源代码字符串中创建和初始化GLProgram。
     * @js initWithString.
     * @lua initWithString.
     */
    static GLProgram* createWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    bool initWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    static GLProgram* createWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray, const std::string& compileTimeDefines);
    bool initWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray, const std::string& compileTimeDefines);

    /**
    @}
    */
    /** @{@~english
    Create or Initializes the GLProgram with a vertex and fragment with contents of filenames.
     * @~chinese 
     * 从给定的数据文件中创建和初始化GLProgram。
     * @js init
     * @lua init
     */
    static GLProgram* createWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename);
    bool initWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename);

    static GLProgram* createWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename, const std::string& compileTimeDefines);
    bool initWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename, const std::string& compileTimeDefines);
    /**
    @}
    */

    /**
    @~english Get the uniform by string name in shader, return null if it does not exist.
    @~chinese 按照名字检索Uniform, 如果不存在，将返回null
    */
    Uniform* getUniform(const std::string& name);
    /**
    @~english Get the vertex attribute by string name in shader, return null if it does not exist.
    @~chinese 按照名字检索顶点属性, 如果不存在，将返回null
    */
    VertexAttrib* getVertexAttrib(const std::string& name);

    /**  
    @~english It will add a new attribute to the shader by calling glBindAttribLocation.  
    @~chinese 调用glBindAttribLocation，将顶点属性绑定给给定的位置。
    @param attributeName @~english the name of vertex attribute. @~chinese 顶点属性的名字。
    @param index @~english the index location. @~chinese 给定的位置。
    */
    void bindAttribLocation(const std::string& attributeName, GLuint index) const;

    /** @~english Calls glGetAttribLocation.  @~chinese 调用glGetAttribLocation。*/
    GLint getAttribLocation(const std::string& attributeName) const;

    /** @~english Calls glGetUniformLocation().  @~chinese 调用glGetUniformLocation()。*/
    GLint getUniformLocation(const std::string& attributeName) const;

    /** @~english links the glProgram  @~chinese 链接openGL Program。*/
    bool link();
    /** @~english it will call glUseProgram()  @~chinese 它将调用glUseProgram()。*/
    void use();
    /** @~english update the locations for built in uniforms.
    @~chinese 更新预定义的Uniform参数的位置。*/
    void updateUniforms();

    /** 
    @~english calls retrieves the named uniform location for this shader program.  
    @~chinese 按照名字去检索Uniform的位置。
    */
    GLint getUniformLocationForName(const char* name) const;

    /** @~english calls glUniform1i only if the values are different than the previous call for this same shader program.
     * @~chinese 当数据值有更新时，调用glUniform1i。
     * @js setUniformLocationI32
     * @lua setUniformLocationI32
     */
    void setUniformLocationWith1i(GLint location, GLint i1);

    /** 
    @~english calls glUniform2i only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniform2i。
    */
    void setUniformLocationWith2i(GLint location, GLint i1, GLint i2);

    /** 
    @~english calls glUniform3i only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniform3i。
    */
    void setUniformLocationWith3i(GLint location, GLint i1, GLint i2, GLint i3);

    /** 
    @~english calls glUniform4i only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniform4i。
    */
    void setUniformLocationWith4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4);

    /** 
    @~english calls glUniform2iv only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniform2iv。
    */
    void setUniformLocationWith2iv(GLint location, GLint* ints, unsigned int numberOfArrays);

    /** 
    @~english calls glUniform3iv only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniform3iv。
    */
    void setUniformLocationWith3iv(GLint location, GLint* ints, unsigned int numberOfArrays);

    /** 
    @~english calls glUniform4iv only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniform4iv。
    */

    void setUniformLocationWith4iv(GLint location, GLint* ints, unsigned int numberOfArrays);

    /** @~english calls glUniform1f only if the values are different than the previous call for this same shader program.
     * In js or lua,please use setUniformLocationF32
     * @~chinese 当数据值有更新时，调用glUniform1f。
     * 在js或lua,请使用setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith1f(GLint location, GLfloat f1);

    /** @~english calls glUniform2f only if the values are different than the previous call for this same shader program.
     * In js or lua,please use setUniformLocationF32
     * @~chinese 当数据值有更新时，调用glUniform2f。
     * 在js或lua,请使用setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2);

    /** @~english calls glUniform3f only if the values are different than the previous call for this same shader program.
     * In js or lua,please use setUniformLocationF32
     * @~chinese 当数据值有更新时，调用glUniform3f。
     * 在js或lua,请使用setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3);

    /** @~english calls glUniform4f only if the values are different than the previous call for this same shader program.
     * In js or lua,please use setUniformLocationF32
     * @~chinese 当数据值有更新时，调用glUniform4f。
     * 在js或lua,请使用setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

    /** 
    @~english calls glUniformfv only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniformfv。
    */
    void setUniformLocationWith1fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** 
    @~english calls glUniform2fv only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniform2fv。
    */
    void setUniformLocationWith2fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** 
    @~english calls glUniform3fv only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniform3fv。
    */
    void setUniformLocationWith3fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** 
    @~english calls glUniform4fv only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniform4fv。
    */
    void setUniformLocationWith4fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** 
    @~english calls glUniformMatrix2fv only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniformMatrix2fv。
    */
    void setUniformLocationWithMatrix2fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);

    /** 
    @~english calls glUniformMatrix3fv only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniformMatrix3fv。
    */
    void setUniformLocationWithMatrix3fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);

    /** 
    @~english calls glUniformMatrix4fv only if the values are different than the previous call for this same shader program.  
    @~chinese 当数据值有更新时，调用glUniformMatrix4fv。
    */
    void setUniformLocationWithMatrix4fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);

    /**@~english
     Update the builtin uniforms if they are different than the previous call for this same shader program.
     * @~chinese 
     * 更新Shader中预先定义的Uniform,如果它们的数据有更新。
     */
    void setUniformsForBuiltins();
    /**@~english
     Update the builtin uniforms if they are different than the previous call for this same shader program.
     * @~chinese 
     * 更新Shader中预先定义的Uniform,如果它们的数据有更新。
     @param modelView @~english modelView matrix applied to the built in uniform of the shader.
     * @~chinese 更新需要的ModelView矩阵。
     */
    void setUniformsForBuiltins(const Mat4 &modelView);

    /** @~english returns the vertexShader error log  @~chinese 返回vertexShader错误日志*/
    std::string getVertexShaderLog() const;

    /** @~english returns the fragmentShader error log  @~chinese 返回fragmentShader错误日志*/
    std::string getFragmentShaderLog() const;

    /** @~english returns the program error log  @~chinese 返回程序错误日志*/
    std::string getProgramLog() const;

    /** @~english Reload all shaders, this function is designed for android
    when opengl context lost, so don't call it.
     * @~chinese 重新加载所有Shader,这个函数是为android设计的
     * 当opengl上下文丢失,所以不要自行调用。
    */
    void reset();
    /*
    @~english Get the built in openGL handle of the program. 
    @~chinese 得到openGL Program的句柄。
    @return @~english openGL Program handle.
    @~chinese openGL Program的句柄。
    */
    inline const GLuint getProgram() const { return _program; }

    //DEPRECATED
    CC_DEPRECATED_ATTRIBUTE bool initWithVertexShaderByteArray(const GLchar* vertexByteArray, const GLchar* fragByteArray)
    { return initWithByteArrays(vertexByteArray, fragByteArray); }
    CC_DEPRECATED_ATTRIBUTE bool initWithVertexShaderFilename(const std::string &vertexFilename, const std::string& fragFilename)
    { return initWithFilenames(vertexFilename, fragFilename); }
    CC_DEPRECATED_ATTRIBUTE void addAttribute(const std::string &attributeName, GLuint index) const { return bindAttribLocation(attributeName, index); }


protected:
    /**@~english
    Update the uniform data in location.
     * @~chinese 
     * 更新Uniform数据的位置。
    @param location @~english The location of the uniform.
     * @~chinese Uniform的位置。
    @param data @~english Updated data.
     * @~chinese 更新的数据。
    @oaram @~english bytes Data length in bytes to update.
     * @~chinese 要更新的数据长度，以字节为单位。
    */
    bool updateUniformLocation(GLint location, const GLvoid* data, unsigned int bytes);
    /**@~english Get a general description of the shader. @~chinese 着色器的简单描述。*/
    virtual std::string getDescription() const;

    /**@~english Bind the predefined vertex attributes to their specific slot. @~chinese 将顶点属性绑定到预先定义的位置。*/
    void bindPredefinedVertexAttribs();
    /**@~english Parse user defined Vertex Attributes automatically. @~chinese 自动解析用户定义的顶点属性。*/
    void parseVertexAttribs();
    /**@~english Parse user defined uniform automatically. @~chinese 自动解析用户定义的Uniform。*/
    void parseUniforms();
    /**@~english Compile the shader sources. @~chinese 编译Shader的源代码。*/
    bool compileShader(GLuint * shader, GLenum type, const GLchar* source, const std::string& convertedDefines);
    bool compileShader(GLuint * shader, GLenum type, const GLchar* source);

    /** OpenGL handle for program. */
    GLuint            _program;
    /** OpenGL handle for vertex shader.*/
    GLuint            _vertShader;
    /** OpenGL handle for fragment shader. */
    GLuint            _fragShader;
    /** Built in uniforms.*/
    GLint             _builtInUniforms[UNIFORM_MAX];
    /** Indicate whether it has a offline shader compiler or not.*/
    bool              _hasShaderCompiler;

    struct flag_struct {
        unsigned int usesTime:1;
        unsigned int usesNormal:1;
        unsigned int usesMVP:1;
        unsigned int usesMV:1;
        unsigned int usesP:1;
        unsigned int usesRandom:1;
        // handy way to initialize the bitfield
        flag_struct() { memset(this, 0, sizeof(*this)); }
    } _flags;

    /** User defined Uniforms.*/
    std::unordered_map<std::string, Uniform> _userUniforms;
    /** User defined vertex attributes.*/
    std::unordered_map<std::string, VertexAttrib> _vertexAttribs;
    /** Hash value of uniforms for quick access.*/
    std::unordered_map<GLint, std::pair<GLvoid*, unsigned int>> _hashForUniforms;
    //cached director pointer for calling
    Director* _director;
};

NS_CC_END
/**
 end of support group
 @}
 */
#endif /* __CCGLPROGRAM_H__ */
