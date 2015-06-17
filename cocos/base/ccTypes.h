/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#ifndef __BASE_CCTYPES_H__
#define __BASE_CCTYPES_H__

#include <string>

#include "math/CCGeometry.h"
#include "math/CCMath.h"
#include "base/CCRef.h"
#include "platform/CCGL.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

struct Color4B;
struct Color4F;

/**@~english
 * RGB color composed of bytes 3 bytes.
 * @~chinese 
 * 由 3 个字节表示的 RGB 颜色数据。
 * @since v3.0
 */
struct CC_DLL Color3B
{
    Color3B();
    Color3B(GLubyte _r, GLubyte _g, GLubyte _b);
    explicit Color3B(const Color4B& color);
    explicit Color3B(const Color4F& color);

    bool operator==(const Color3B& right) const;
    bool operator==(const Color4B& right) const;
    bool operator==(const Color4F& right) const;
    bool operator!=(const Color3B& right) const;
    bool operator!=(const Color4B& right) const;
    bool operator!=(const Color4F& right) const;

    bool equals(const Color3B& other)
    {
        return (*this == other);
    }

    GLubyte r;
    GLubyte g;
    GLubyte b;

    static const Color3B WHITE;
    static const Color3B YELLOW;
    static const Color3B BLUE;
    static const Color3B GREEN;
    static const Color3B RED;
    static const Color3B MAGENTA;
    static const Color3B BLACK;
    static const Color3B ORANGE;
    static const Color3B GRAY;
};

/**@~english
 * RGBA color composed of 4 bytes.
 * @~chinese 
 * 由 4 个字节表示的 RGBA 颜色数据。
 * @since v3.0
 */
struct CC_DLL Color4B
{
    Color4B();
    Color4B(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a);
    explicit Color4B(const Color3B& color);
    explicit Color4B(const Color4F& color);

    bool operator==(const Color4B& right) const;
    bool operator==(const Color3B& right) const;
    bool operator==(const Color4F& right) const;
    bool operator!=(const Color4B& right) const;
    bool operator!=(const Color3B& right) const;
    bool operator!=(const Color4F& right) const;

    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;

    static const Color4B WHITE;
    static const Color4B YELLOW;
    static const Color4B BLUE;
    static const Color4B GREEN;
    static const Color4B RED;
    static const Color4B MAGENTA;
    static const Color4B BLACK;
    static const Color4B ORANGE;
    static const Color4B GRAY;
};


/**@~english
 * RGBA color composed of 4 floats.
 * @~chinese 
 * 由 4 个浮点数表示的 RGBA 颜色数据。
 * @since v3.0
 */
struct CC_DLL Color4F
{
    Color4F();
    Color4F(float _r, float _g, float _b, float _a);
    explicit Color4F(const Color3B& color);
    explicit Color4F(const Color4B& color);

    bool operator==(const Color4F& right) const;
    bool operator==(const Color3B& right) const;
    bool operator==(const Color4B& right) const;
    bool operator!=(const Color4F& right) const;
    bool operator!=(const Color3B& right) const;
    bool operator!=(const Color4B& right) const;

    bool equals(const Color4F &other)
    {
        return (*this == other);
    }

    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;

    static const Color4F WHITE;
    static const Color4F YELLOW;
    static const Color4F BLUE;
    static const Color4F GREEN;
    static const Color4F RED;
    static const Color4F MAGENTA;
    static const Color4F BLACK;
    static const Color4F ORANGE;
    static const Color4F GRAY;
};

// struct Vertex2F
// {
//     Vertex2F(float _x, float _y) :x(_x), y(_y) {}

//     Vertex2F(): x(0.f), y(0.f) {}

//     GLfloat x;
//     GLfloat y;
// };


// struct Vertex3F
// {
//     Vertex3F(float _x, float _y, float _z)
//         : x(_x)
//         , y(_y)
//         , z(_z)
//     {}

//     Vertex3F(): x(0.f), y(0.f), z(0.f) {}

//     GLfloat x;
//     GLfloat y;
//     GLfloat z;
// };

/** @struct Tex2F
 * @brief @~english
 * A TEXCOORD composed of 2 floats: u, y
 * @~chinese
 * 两个浮点数表示的纹理坐标数据。
 * @since v3.0
 */
struct CC_DLL Tex2F {
    Tex2F(float _u, float _v): u(_u), v(_v) {}

    Tex2F(): u(0.f), v(0.f) {}

    GLfloat u;
    GLfloat v;
};

/** @struct PointSprite
 * @brief @~english
 * The point data of Sprite which contains position, color & szie.
 * @~chinese
 * 包含位置，颜色和大小信息的 Sprite 数据。
 */
struct CC_DLL PointSprite
{
    Vec2   pos;        // 8 bytes
    Color4B    color;      // 4 bytes
    GLfloat    size;       // 4 bytes
};

/** @struct Quad2
 * @brief @~english A 2D Quad. 4 * 2 floats.
 * @~chinese 一个 2D 的矩形顶点数据。
 */
struct CC_DLL Quad2
{
    Vec2        tl;
    Vec2        tr;
    Vec2        bl;
    Vec2        br;
};

/** @struct Quad3
 * @brief @~english A 3D Quad. 4 * 3 floats.
 * @~chinese 一个 3D 的矩形顶点数据。
 */
struct CC_DLL Quad3 {
    Vec3        bl;
    Vec3        br;
    Vec3        tl;
    Vec3        tr;
};

/** @struct V2F_C4B_T2F
 * @brief @~english 
 * A Vec2 with a vertex point, a tex coord point and a color 4B.
 * @~chinese
 * Vec2 顶点坐标 + Color4B 颜色 + 纹理坐标
 */
struct V2F_C4B_T2F
{
    /**@~english vertices (2F)
     * @~chinese 顶点坐标 (2F)
     */
    Vec2       vertices;
    /**@~english colors (4B)
     * @~chinese 颜色 (4B)
     */
    Color4B        colors;
    /**@~english tex coords (2F)
     * @~chinese 纹理坐标 (2F)
     */
    Tex2F          texCoords;
};

/** @struct V2F_C4B_PF
 * @brief @~english
 * A Vec2 with a vertex point, a color 4B and point size.
 * @~chinese 
 * Vec2 顶点坐标 + Color4B 颜色 + 点的大小
 */
struct V2F_C4B_PF
{
    /**@~english vertices (2F)
     * @~chinese 顶点坐标 (2F)
     */
    Vec2       vertices;
    /**@~english colors (4B)
     * @~chinese 颜色 (4B)
     */
    Color4B        colors;
    /**@~english pointsize
     * @~chinese 点大小
     */
    float      pointSize;
};

/** @struct V2F_C4F_T2F
 * @brief @~english
 * A Vec2 with a vertex point, a tex coord point and a color 4F.
 * @~chinese
 * Vec2 顶点坐标 + Color4F 颜色 + 纹理坐标
 */
struct CC_DLL V2F_C4F_T2F
{
    /**@~english vertices (2F)
     * @~chinese 顶点坐标 (2F)
     */
    Vec2       vertices;
    /**@~english colors (4F)
     * @~chinese 颜色 (4F)
     */
    Color4F        colors;
    /**@~english tex coords (2F)
     * @~chinese 纹理坐标 (2F)
     */
    Tex2F          texCoords;
};

/** @struct V3F_C4B_T2F
 * @brief @~english
 * A Vec2 with a vertex point, a tex coord point and a color 4B.
 * @~chinese
 * Vec3 顶点坐标 + Color4B 颜色 + 纹理坐标
 */
struct CC_DLL V3F_C4B_T2F
{
    /**@~english vertices (3F)
     * @~chinese 顶点坐标 (3F)
     */
    Vec3     vertices;            // 12 bytes

    /**@~english colors (4B)
     * @~chinese 颜色 (4B)
     */
    Color4B      colors;              // 4 bytes

    /**@~english tex coords (2F)
     * @~chinese 纹理坐标 (2F)
     */
    Tex2F        texCoords;           // 8 bytes
};

/** @struct V3F_T2F
 * @brief @~english
 * A Vec3 with a vertex point, a tex coord point.
 * @~chinese
 * Vec3 顶点坐标 + 纹理坐标
 */
struct CC_DLL V3F_T2F
{
    /**@~english vertices (3F)
     * @~chinese 顶点坐标 (3F)
     */
    Vec3       vertices;
    /**@~english tex coords (2F)
     * @~chinese 纹理坐标 (2F)
     */
    Tex2F          texCoords;
};

/** @struct V2F_C4B_T2F_Triangle
 * @~english
 * A Triangle of `V2F_C4B_T2F`.
 * @~chinese
 * 顶点数据为 `V2F_C4B_T2F` 的三角形。
 */
struct CC_DLL V2F_C4B_T2F_Triangle
{
	V2F_C4B_T2F a;
	V2F_C4B_T2F b;
	V2F_C4B_T2F c;
};

/** @struct V2F_C4B_T2F_Quad
 * @brief @~english 
 * A Quad of `V2F_C4B_T2F`.
 * @~chinese
 * 顶点数据为 `V2F_C4B_T2F` 的矩形。
 */
struct CC_DLL V2F_C4B_T2F_Quad
{
    /**@~english bottom left
     * @~chinese 左下角
     */
    V2F_C4B_T2F    bl;
    /**@~english bottom right
     * @~chinese 右下角
     */
    V2F_C4B_T2F    br;
    /**@~english top left
     * @~chinese 左上角
     */
    V2F_C4B_T2F    tl;
    /**@~english top right
     * @~chinese 右上角
     */
    V2F_C4B_T2F    tr;
};

/** @struct V3F_C4B_T2F_Quad
 * @brief @~english
 * A Quad of `Vertex3FTex2FColor4B`.
 * @~chinese
 * 顶点数据为 `Vertex3FTex2FColor4B` 的矩形。
 */
struct CC_DLL V3F_C4B_T2F_Quad
{
    /**@~english top left
     * @~chinese 左上角
     */
    V3F_C4B_T2F    tl;
    /**@~english bottom left
     * @~chinese 左下角
     */
    V3F_C4B_T2F    bl;
    /**@~english top right
     * @~chinese 右上角
     */
    V3F_C4B_T2F    tr;
    /**@~english bottom right
     * @~chinese 右下角
     */
    V3F_C4B_T2F    br;
};

/** @struct V2F_C4F_T2F_Quad
 * @brief @~english
 * A Quad of `Vertex2FTex2FColor4F`.
 * @~chinese
 * 顶点数据为 `Vertex2FTex2FColor4F` 的矩形。
 */
struct CC_DLL V2F_C4F_T2F_Quad
{
    /**@~english bottom left
     * @~chinese 左下角
     */
    V2F_C4F_T2F    bl;
    /**@~english bottom right
     * @~chinese 右下角
     */
    V2F_C4F_T2F    br;
    /**@~english top left
     * @~chinese 左上角
     */
    V2F_C4F_T2F    tl;
    /**@~english top right
     * @~chinese 右上角
     */
    V2F_C4F_T2F    tr;
};

/** @struct V3F_T2F_Quad
 * @brief @~english
 * A Quad with `V3F_T2F`
 * @~chinese
 * 顶点数据为 `V3F_T2F` 的矩形。
 */
struct CC_DLL V3F_T2F_Quad
{
    /**@~english bottom left
     * @~chinese 左下角
     */
    V3F_T2F    bl;
    /**@~english bottom right
     * @~chinese 右下角
     */
    V3F_T2F    br;
    /**@~english top left
     * @~chinese 左上角
     */
    V3F_T2F    tl;
    /**@~english top right
     * @~chinese 右上角
     */
    V3F_T2F    tr;
};

/** @struct BlendFunc
 * @~english
 * Blend Function used for textures.
 * @~chinese
 * 用于纹理的混合函数。
 */
struct CC_DLL BlendFunc
{
    /** @~english source blend factor  @~chinese 源混合因子 */
    GLenum src;
    /** @~english destination blend factor  @~chinese 目标混合因子 */
    GLenum dst;

    /** @~english Blending disabled. Uses {GL_ONE, GL_ZERO}
     * @~chinese 不进行混合。使用 {GL_ONE, GL_ZERO}
     */
    static const BlendFunc DISABLE;
    /** @~english Blending enabled for textures with Alpha premultiplied. Uses {GL_ONE, GL_ONE_MINUS_SRC_ALPHA}
     * @~chinese 混合源颜色不变，混合目标颜色预乘 (1 - 源的透明度)。使用 {GL_ONE, GL_ONE_MINUS_SRC_ALPHA}
     */
    static const BlendFunc ALPHA_PREMULTIPLIED;
    /** @~english Blending enabled for textures with Alpha NON premultiplied. Uses {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}
     * @~chinese 混合源颜色预乘透明度，混合目标颜色预乘 (1 - 源的透明度)。使用 {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}
     */
    static const BlendFunc ALPHA_NON_PREMULTIPLIED;
    /** @~english Enables Additive blending. Uses {GL_SRC_ALPHA, GL_ONE}
     * @~chinese 线性加亮混合。使用 {GL_SRC_ALPHA, GL_ONE}
     */
    static const BlendFunc ADDITIVE;

    bool operator==(const BlendFunc &a) const
    {
        return src == a.src && dst == a.dst;
    }

    bool operator!=(const BlendFunc &a) const
    {
        return src != a.src || dst != a.dst;
    }

    bool operator<(const BlendFunc &a) const
    {
        return src < a.src || (src == a.src && dst < a.dst);
    }
};

/** @struct TextVAlignment
 * @~english Vertical text alignment type.
 *
 * @~chinese
 * 文本垂直对齐的类型。
 * 
 * @note @~english If any of these enums are edited and/or reordered, update Texture2D.m.
 * @~chinese 如果这些枚举值被编辑或者重新排序，需要更新 Texture2D.m。
 */
enum class CC_DLL TextVAlignment
{
    TOP,
    CENTER,
    BOTTOM
};

/** @struct TextHAlignment
 * @~english 
 * Horizontal text alignment type.
 *
 * @~chinese
 * 文本水平对齐的类型。
 * 
 * @note @~english If any of these enums are edited and/or reordered, update Texture2D.m.
 * @~chinese 如果这些枚举值被编辑或者重新排序，需要更新 Texture2D.m。
 */
enum class CC_DLL TextHAlignment
{
    LEFT,
    CENTER,
    RIGHT
};

// Types for animation in particle systems

/** @struct T2F_Quad
 * @~english
 * Texture coordinates for a quad.
 * @~chinese 
 * 矩形四个顶点的纹理坐标
 */
struct CC_DLL T2F_Quad
{
    /**@~english bottom left
     * @~chinese 左下角
     */
    Tex2F    bl;
    /**@~english bottom right
     * @~chinese 右下角
     */
    Tex2F    br;
    /** @~english top left
     * @~chinese 左上角
     */
    Tex2F    tl;
    /**@~english top right
     * @~chinese 右上角
     */
    Tex2F    tr;
};

/** @struct AnimationFrameData
 * @~english
 * Struct that holds the size in pixels, texture coordinates and delays for animated ParticleSystemQuad.
 * @~chinese
 * 为 `ParticleSystemQuad` 的动画而设计的包含像素的大小，纹理坐标，延迟时间的结构体。
 */
struct CC_DLL AnimationFrameData
{
    T2F_Quad texCoords;
    float delay;
    Size size;
};

/**@~english
 * types used for defining fonts properties (i.e. font name, size, stroke or shadow)
 * @~chinese 
 * 用于定义字体属性的结构体(如字体名称、大小、描边或阴影)
 */

/** @struct FontShadow
 * @~english Shadow attributes.
 * @~chinese 字体的阴影效果属性。
 */
struct CC_DLL FontShadow
{
public:

    // shadow is not enabled by default
    FontShadow()
        : _shadowEnabled(false)
        , _shadowBlur(0)
        , _shadowOpacity(0)
    {}

    /**@~english true if shadow enabled
     * @~chinese 如果阴影效果开启，则为 true；否则为 false。
     */
    bool   _shadowEnabled;
    /**@~english shadow x and y offset
     * @~chinese 阴影的 x 与 y 轴偏移量。
     */
	Size   _shadowOffset;
    /**@~english shadow blurriness
     * @~chinese 阴影的模糊度。
     */
	float  _shadowBlur;
    /**@~english shadow opacity
     * @~chinese 阴影的不透明度。
     */
	float  _shadowOpacity;
};

/** @struct FontStroke
 * @~english Stroke attributes.
 * @~chinese 字体的描边效果属性。
 */
struct CC_DLL FontStroke
{
public:

    // stroke is disabled by default
    FontStroke()
	    : _strokeEnabled(false)
        , _strokeColor(Color3B::BLACK)
        , _strokeAlpha(255)
        , _strokeSize(0)
    {}

    /**@~english true if stroke enabled
     * @~chinese 如果启用了描边效果，则为 true；否则为 false。
     */
    bool      _strokeEnabled;
    /**@~english stroke color
     * @~chinese 描边的颜色。
     */
	Color3B   _strokeColor;
    /**@~english stroke alpha
     * @~chinese 描边的透明度。
     */
    GLubyte   _strokeAlpha;
    /**@~english stroke size
     * @~chinese 描边的大小。
     */
    float     _strokeSize;

};

/** @struct FontDefinition
 * @~english Font attributes.
 * @~chinese 定义字体基本属性的结构体。
 */
struct CC_DLL FontDefinition
{
public:
    /**
     * @js NA
     * @lua NA
     */
    FontDefinition()
        : _fontSize(0)
        , _alignment(TextHAlignment::CENTER)
        , _vertAlignment(TextVAlignment::TOP)
    	, _dimensions(Size::ZERO)
        , _fontFillColor(Color3B::WHITE)
        , _fontAlpha(255)
    {}

    /**@~english font name
     * @~chinese 字体名称。
     */
    std::string           _fontName;
    /**@~english font size
     * @~chinese 字体大小。
     */
    int                   _fontSize;
    /**@~english horizontal alignment
     * @~chinese 水平对齐类型。
     */
    TextHAlignment        _alignment;
    /**@~english vertical alignment
     * @~chinese 垂直对齐类型。
     */
    TextVAlignment _vertAlignment;
    /**@~english renering box
     * @~chinese 渲染盒大小。
     */
    Size                  _dimensions;
    /**@~english font color
     * @~chinese 字体颜色。
     */
    Color3B               _fontFillColor;
    /**@~english font alpha
     * @~chinese 字体透明度。
     */
    GLubyte               _fontAlpha;
    /**@~english font shadow
     * @~chinese 字体阴影效果。
     */
    FontShadow            _shadow;
    /**@~english font stroke
     * @~chinese 字体描边效果。
     */
    FontStroke            _stroke;

};

/**
 * @brief @~english Possible LabelEffect used by Label.
 *
 * @~chinese 可能被 `Label` 使用到的字体效果类型。
 * 
 */
enum class LabelEffect {
    NORMAL,
    OUTLINE,
    SHADOW,
    GLOW,
    ALL
};

/** @struct Acceleration
 * @~english The device accelerometer reports values for each axis in units of g-force.
 * @~chinese 设备重力传感器传递的各个轴的数据。
 */
class CC_DLL Acceleration
    : public Ref
{
public:
    double x;
    double y;
    double z;

    double timestamp;

    Acceleration(): x(0), y(0), z(0), timestamp(0) {}
};

extern const std::string CC_DLL STD_STRING_EMPTY;
extern const ssize_t CC_DLL CC_INVALID_INDEX;

NS_CC_END
// end group
/// @}
#endif //__BASE_CCTYPES_H__
