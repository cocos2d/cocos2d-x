/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
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


#ifndef __CC_PU_PARTICLE_3D_BOX_EMITTER_H__
#define __CC_PU_PARTICLE_3D_BOX_EMITTER_H__

#include "extensions/Particle3D/PU/CCPUEmitter.h"

NS_CC_BEGIN

class  CC_DLL CCPUBoxEmitter : public PUEmitter
{
public:
    // Constants
    static const float DEFAULT_WIDTH;
    static const float DEFAULT_HEIGHT;
    static const float DEFAULT_DEPTH;

    static CCPUBoxEmitter* create();

    /** 
    */
    const float getHeight(void) const;
    void setHeight(const float height);

    /** 
    */
    const float getWidth(void) const;
    void setWidth(const float width);

    /** 
    */
    const float getDepth(void) const;
    void setDepth(const float depth);

    virtual CCPUBoxEmitter* clone() override;
    virtual void copyAttributesTo (PUEmitter* emitter) override;

CC_CONSTRUCTOR_ACCESS:
    CCPUBoxEmitter(void);
    virtual ~CCPUBoxEmitter(void) {};

protected:

    /** 
    */
    virtual void initParticlePosition(PUParticle3D* particle) override;

protected:
    float _height;
    float _width;
    float _depth;

    float _xRange;
    float _yRange;
    float _zRange;


};
NS_CC_END

#endif