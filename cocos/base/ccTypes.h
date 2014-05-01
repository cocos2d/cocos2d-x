/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCTYPES_H__
#define __CCTYPES_H__

#include <string>
#include "math/CCGeometry.h"
#include "math/CCMath.h"
#include "CCGL.h"

NS_CC_BEGIN

USING_NS_CC_MATH;

struct Color4B;
struct Color4F;

/** RGB color composed of bytes 3 bytes
@since v3.0
 */
struct Color3B
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
    
    const static Color3B WHITE;
    const static Color3B YELLOW;
    const static Color3B BLUE;
    const static Color3B GREEN;
    const static Color3B RED;
    const static Color3B MAGENTA;
    const static Color3B BLACK;
    const static Color3B ORANGE;
    const static Color3B GRAY;
};

/** RGBA color composed of 4 bytes
@since v3.0
*/
struct Color4B
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

    const static Color4B WHITE;
    const static Color4B YELLOW;
    const static Color4B BLUE;
    const static Color4B GREEN;
    const static Color4B RED;
    const static Color4B MAGENTA;
    const static Color4B BLACK;
    const static Color4B ORANGE;
    const static Color4B GRAY;
};


/** RGBA color composed of 4 floats
@since v3.0
*/
struct Color4F
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

    const static Color4F WHITE;
    const static Color4F YELLOW;
    const static Color4F BLUE;
    const static Color4F GREEN;
    const static Color4F RED;
    const static Color4F MAGENTA;
    const static Color4F BLACK;
    const static Color4F ORANGE;
    const static Color4F GRAY;
};

/** A vertex composed of 2 floats: x, y
 @since v3.0
 */
// struct Vertex2F
// {
//     Vertex2F(float _x, float _y) :x(_x), y(_y) {}
    
//     Vertex2F(): x(0.f), y(0.f) {}
    
//     GLfloat x;
//     GLfloat y;
// };


/** A vertex composed of 2 floats: x, y
 @since v3.0
 */
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
        
/** A texcoord composed of 2 floats: u, y
 @since v3.0
 */
struct Tex2F {
    Tex2F(float _u, float _v): u(_u), v(_v) {}
    
    Tex2F(): u(0.f), v(0.f) {}
    
    GLfloat u;
    GLfloat v;
};

 
//! Vector2 Sprite component
struct PointSprite
{
    Vector2   pos;        // 8 bytes
    Color4B    color;      // 4 bytes
    GLfloat    size;       // 4 bytes
};

//!    A 2D Quad. 4 * 2 floats
struct Quad2
{
    Vector2        tl;
    Vector2        tr;
    Vector2        bl;
    Vector2        br;
};


//!    A 3D Quad. 4 * 3 floats
struct Quad3 {
    Vector3        bl;
    Vector3        br;
    Vector3        tl;
    Vector3        tr;
};

//! a Vector2 with a vertex point, a tex coord point and a color 4B
struct V2F_C4B_T2F
{
    //! vertices (2F)
    Vector2       vertices;
    //! colors (4B)
    Color4B        colors;
    //! tex coords (2F)
    Tex2F          texCoords;
};

//! a Vector2 with a vertex point, a tex coord point and a color 4F
struct V2F_C4F_T2F
{
    //! vertices (2F)
    Vector2       vertices;
    //! colors (4F)
    Color4F        colors;
    //! tex coords (2F)
    Tex2F          texCoords;
};

//! a Vector2 with a vertex point, a tex coord point and a color 4B
struct V3F_C4B_T2F
{
    //! vertices (3F)
    Vector3     vertices;            // 12 bytes

    //! colors (4B)
    Color4B      colors;              // 4 bytes

    // tex coords (2F)
    Tex2F        texCoords;           // 8 bytes
};

//! A Triangle of V2F_C4B_T2F
struct V2F_C4B_T2F_Triangle
{
	//! Vector2 A
	V2F_C4B_T2F a;
	//! Vector2 B
	V2F_C4B_T2F b;
	//! Vector2 B
	V2F_C4B_T2F c;
};

//! A Quad of V2F_C4B_T2F
struct V2F_C4B_T2F_Quad
{
    //! bottom left
    V2F_C4B_T2F    bl;
    //! bottom right
    V2F_C4B_T2F    br;
    //! top left
    V2F_C4B_T2F    tl;
    //! top right
    V2F_C4B_T2F    tr;
};

//! 4 Vertex3FTex2FColor4B
struct V3F_C4B_T2F_Quad
{
    //! top left
    V3F_C4B_T2F    tl;
    //! bottom left
    V3F_C4B_T2F    bl;
    //! top right
    V3F_C4B_T2F    tr;
    //! bottom right
    V3F_C4B_T2F    br;
};

//! 4 Vertex2FTex2FColor4F Quad
struct V2F_C4F_T2F_Quad
{
    //! bottom left
    V2F_C4F_T2F    bl;
    //! bottom right
    V2F_C4F_T2F    br;
    //! top left
    V2F_C4F_T2F    tl;
    //! top right
    V2F_C4F_T2F    tr;
};

//! Blend Function used for textures
struct BlendFunc
{
    //! source blend function
    GLenum src;
    //! destination blend function
    GLenum dst;

    //! Blending disabled. Uses {GL_ONE, GL_ZERO}
    const static BlendFunc DISABLE;
    //! Blending enabled for textures with Alpha premultiplied. Uses {GL_ONE, GL_ONE_MINUS_SRC_ALPHA}
    const static BlendFunc ALPHA_PREMULTIPLIED;
    //! Blending enabled for textures with Alpha NON premultiplied. Uses {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}
    const static BlendFunc ALPHA_NON_PREMULTIPLIED;
    //! Enables Additive blending. Uses {GL_SRC_ALPHA, GL_ONE}
    const static BlendFunc ADDITIVE;

    bool operator==(const BlendFunc &a) const
    {
        return src == a.src && dst == a.dst;
    }

    bool operator<(const BlendFunc &a) const
    {
        return src < a.src || (src < a.src && dst < a.dst);
    }
};

// Label::VAlignment
// Label::HAlignment

// XXX: If any of these enums are edited and/or reordered, update Texture2D.m
//! Vertical text alignment type
enum class TextVAlignment
{
    TOP,
    CENTER,
    BOTTOM,
};

// XXX: If any of these enums are edited and/or reordered, update Texture2D.m
//! Horizontal text alignment type
enum class TextHAlignment
{
    LEFT,
    CENTER,
    RIGHT,
};

// types for animation in particle systems

// texture coordinates for a quad
struct T2F_Quad
{
    //! bottom left
    Tex2F    bl;
    //! bottom right
    Tex2F    br;
    //! top left
    Tex2F    tl;
    //! top right
    Tex2F    tr;
};

// struct that holds the size in pixels, texture coordinates and delays for animated ParticleSystemQuad
struct AnimationFrameData
{
    T2F_Quad texCoords;
    float delay;
    Size size; 
};

/**
 types used for defining fonts properties (i.e. font name, size, stroke or shadow)
 */


// shadow attributes
struct FontShadow
{
public:
    
    // shadow is not enabled by default
    FontShadow()
        : _shadowEnabled(false)
        , _shadowBlur(0)
        , _shadowOpacity(0)
    {}

    // true if shadow enabled
    bool   _shadowEnabled;
    // shadow x and y offset
	Size   _shadowOffset;
    // shadow blurrines
	float  _shadowBlur;
    // shadow opacity
	float  _shadowOpacity;
};

// stroke attributes
struct FontStroke
{
public:
    
    // stroke is disabled by default
    FontStroke()
	    : _strokeEnabled(false)
        , _strokeColor(Color3B::BLACK)
        , _strokeSize(0)
    {}
    
    // true if stroke enabled
    bool      _strokeEnabled;
    // stroke color
	Color3B   _strokeColor;
    // stroke size
    float     _strokeSize;
    
};

// font attributes
struct FontDefinition
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
    {}
    
    // font name
    std::string           _fontName;
    // font size
    int                   _fontSize;
    // horizontal alignment
    TextHAlignment        _alignment;
    // vertical alignment
    TextVAlignment _vertAlignment;
    // renering box
    Size                  _dimensions;
    // font color
    Color3B               _fontFillColor;
    // font shadow
    FontShadow            _shadow;
    // font stroke
    FontStroke            _stroke;
    
};

/**
 @brief The device accelerometer reports values for each axis in units of g-force
 */
class Acceleration
{
public:
    double x;
    double y;
    double z;
    
    double timestamp;
    
    Acceleration(): x(0), y(0), z(0), timestamp(0) {}
};

extern const std::string STD_STRING_EMPTY;
extern const ssize_t CC_INVALID_INDEX;

NS_CC_END

#endif //__CCTYPES_H__
