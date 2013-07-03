/****************************************************************************
Copyright (c) 2010-2012  cocos2d-x.org
Copyright (c) 2011 ForzeField Studios S.L.

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
#ifndef __CCMOTION_STREAK_H__
#define __CCMOTION_STREAK_H__

#include "CCProtocols.h"
#include "textures/CCTexture2D.h"
#include "ccTypes.h"
#include "base_nodes/CCNode.h"
#ifdef EMSCRIPTEN
#include "base_nodes/CCGLBufferedNode.h"
#endif // EMSCRIPTEN

NS_CC_BEGIN

/**
 * @addtogroup misc_nodes
 * @{
 */

/** MotionStreak.
 Creates a trailing path.
 */
class CC_DLL MotionStreak : public NodeRGBA, public TextureProtocol
#ifdef EMSCRIPTEN
, public GLBufferedNode
#endif // EMSCRIPTEN
{
public:
    MotionStreak();
    virtual ~MotionStreak();

    /** creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture filename */
    static MotionStreak* create(float fade, float minSeg, float stroke, const ccColor3B& color, const char* path);
    /** creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture */
    static MotionStreak* create(float fade, float minSeg, float stroke, const ccColor3B& color, Texture2D* texture);

    /** initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture filename */
    bool initWithFade(float fade, float minSeg, float stroke, const ccColor3B& color, const char* path);
    /** initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture  */
    bool initWithFade(float fade, float minSeg, float stroke, const ccColor3B& color, Texture2D* texture);

    /** color used for the tint */
    void tintWithColor(const ccColor3B& colors);

    /** Remove all living segments of the ribbon */
    void reset();

    /** Override super methods */
    virtual void setPosition(const Point& position);
    virtual void draw();
    virtual void update(float delta);

    /* Implement interfaces */
    virtual Texture2D* getTexture(void);
    virtual void setTexture(Texture2D *texture);
    virtual void setBlendFunc(ccBlendFunc blendFunc);
    virtual ccBlendFunc getBlendFunc(void);
    virtual GLubyte getOpacity(void);
    virtual void setOpacity(GLubyte opacity);
    virtual void setOpacityModifyRGB(bool bValue);
    virtual bool isOpacityModifyRGB(void);

    /** When fast mode is enabled, new points are added faster but with lower precision */
    inline bool isFastMode() { return _fastMode; }
    inline void setFastMode(bool bFastMode) { _fastMode = bFastMode; }

    inline bool isStartingPositionInitialized() { return _startingPositionInitialized; }
    inline void setStartingPositionInitialized(bool bStartingPositionInitialized) 
    { 
        _startingPositionInitialized = bStartingPositionInitialized; 
    }
protected:
    bool _fastMode;
    bool _startingPositionInitialized;
private:
    /** texture used for the motion streak */
    Texture2D* _texture;
    ccBlendFunc _blendFunc;
    Point _positionR;

    float _stroke;
    float _fadeDelta;
    float _minSeg;

    unsigned int _maxPoints;
    unsigned int _nuPoints;
    unsigned int _previousNuPoints;

    /** Pointers */
    Point* _pointVertexes;
    float* _pointState;

    // Opengl
    ccVertex2F* _vertices;
    GLubyte* _colorPointer;
    ccTex2F* _texCoords;
};

// end of misc_nodes group
/// @}

NS_CC_END

#endif //__CCMOTION_STREAK_H__
