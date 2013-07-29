/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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
#include "cocoa/CCGeometry.h"
#include "CCGL.h"


NS_CC_BEGIN

/** RGB color composed of bytes 3 bytes
@since v3.0
 */
struct Color3B
{
    Color3B(): r(0), g(0), b(0) {}
    
    Color3B(GLubyte _r, GLubyte _g, GLubyte _b)
        : r(_r)
        , g(_g)
        , b(_b)
    {}
    
    bool equals(const Color3B &other)
    {
        return (this->r == other.r &&
                this->g == other.g &&
                this->b == other.b);
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

struct Color4F;

/** RGBA color composed of 4 bytes
@since v3.0
*/
struct Color4B
{
    Color4B(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a)
        : r(_r)
        , g(_g)
        , b(_b)
        , a(_a)
    {}
    
    Color4B(): r(0), g(0), b(0), a(0) {}
    
    // This function should use Color4F, so implement it in .cpp file.
    explicit Color4B(const Color4F &color4F);

    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};


/** RGBA color composed of 4 floats
@since v3.0
*/
struct Color4F
{
    Color4F(float _r, float _g, float _b, float _a)
        : r(_r)
        , g(_g)
        , b(_b)
        , a(_a)
    {}
    
    explicit Color4F(const Color3B &color3B)
        : r(color3B.r)
        , g(color3B.g)
        , b(color3B.b)
        , a(1.f)
    {}
    
    explicit Color4F(const Color4B &color4B)
        : r(color4B.r / 255.0f)
        , g(color4B.g / 255.0f)
        , b(color4B.b / 255.0f)
        , a(color4B.a / 255.0f)
    {}
    
    Color4F(): r(0.f), g(0.f), b(0.f), a(0.f) {}
    
    bool equals(const Color4F &other)
    {
        return (this->r == other.r &&
                this->g == other.g &&
                this->b == other.b &&
                this->a == other.a);
    }
    
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

/** A vertex composed of 2 floats: x, y
 @since v3.0
 */
struct Vertex2F
{
    Vertex2F(float _x, float _y) :x(_x), y(_y) {}
    
    Vertex2F(): x(0.f), y(0.f) {}
    
    GLfloat x;
    GLfloat y;
};


/** A vertex composed of 2 floats: x, y
 @since v3.0
 */
struct Vertex3F
{
    Vertex3F(float _x, float _y, float _z)
        : x(_x)
        , y(_y)
        , z(_z)
    {}
    
    Vertex3F(): x(0.f), y(0.f), z(0.f) {}
    
    GLfloat x;
    GLfloat y;
    GLfloat z;
};
        
/** A texcoord composed of 2 floats: u, y
 @since v3.0
 */
struct Tex2F {
    Tex2F(float _u, float _v): u(_u), v(_v) {}
    
    Tex2F(): u(0.f), v(0.f) {}
    
    GLfloat u;
    GLfloat v;
};

 
//! Point Sprite component
struct PointSprite
{
    Vertex2F   pos;        // 8 bytes
    Color4B    color;      // 4 bytes
    GLfloat    size;       // 4 bytes
};

//!    A 2D Quad. 4 * 2 floats
struct Quad2
{
    Vertex2F        tl;
    Vertex2F        tr;
    Vertex2F        bl;
    Vertex2F        br;
};


//!    A 3D Quad. 4 * 3 floats
struct Quad3 {
    Vertex3F        bl;
    Vertex3F        br;
    Vertex3F        tl;
    Vertex3F        tr;
};

//! a Point with a vertex point, a tex coord point and a color 4B
struct V2F_C4B_T2F
{
    //! vertices (2F)
    Vertex2F       vertices;
    //! colors (4B)
    Color4B        colors;
    //! tex coords (2F)
    Tex2F          texCoords;
};

//! a Point with a vertex point, a tex coord point and a color 4F
struct V2F_C4F_T2F
{
    //! vertices (2F)
    Vertex2F       vertices;
    //! colors (4F)
    Color4F        colors;
    //! tex coords (2F)
    Tex2F          texCoords;
};

//! a Point with a vertex point, a tex coord point and a color 4B
struct V3F_C4B_T2F
{
    //! vertices (3F)
    Vertex3F     vertices;            // 12 bytes

    //! colors (4B)
    Color4B      colors;              // 4 bytes

    // tex coords (2F)
    Tex2F        texCoords;           // 8 bytes
};

//! A Triangle of V2F_C4B_T2F
struct V2F_C4B_T2F_Triangle
{
	//! Point A
	V2F_C4B_T2F a;
	//! Point B
	V2F_C4B_T2F b;
	//! Point B
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
};

class Label : public Object
{
public:
    // XXX: If any of these enums are edited and/or reordered, update Texture2D.m
    //! Vertical text alignment type
    enum class VAlignment
    {
        TOP,
        CENTER,
        BOTTOM,
    };
    
    // XXX: If any of these enums are edited and/or reordered, update Texture2D.m
    //! Horizontal text alignment type
    enum class HAlignment
    {
        LEFT,
        CENTER,
        RIGHT,
    };
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
    
    FontDefinition()
        : _fontSize(0)
        , _alignment(Label::HAlignment::CENTER)
        , _vertAlignment(Label::VAlignment::TOP)
    	, _dimensions(Size::ZERO)
        , _fontFillColor(Color3B::WHITE)
    {}
    
    // font name
    std::string           _fontName;
    // font size
    int                   _fontSize;
    // horizontal alignment
    Label::HAlignment         _alignment;
    // vertical alignment
    Label::VAlignment _vertAlignment;
    // renering box
    Size                  _dimensions;
    // font color
    Color3B               _fontFillColor;
    // font shadow
    FontShadow            _shadow;
    // font stroke
    FontStroke            _stroke;
    
};


NS_CC_END

#endif //__CCTYPES_H__
