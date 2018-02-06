/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#ifndef __CC_PU_PARTICLE_3D_NOISE_H__
#define __CC_PU_PARTICLE_3D_NOISE_H__

#include "base/CCRef.h"
#include "math/CCMath.h"

NS_CC_BEGIN

class PUNoise3D
{
public:
    /* Constructor / Destructor */
    PUNoise3D(void);
    virtual ~PUNoise3D(void);

    /* Inititialises the noise function */
    void initialise(unsigned short octaves, double frequency = 1.0, double amplitude = 1.0, double persistence = 1.0);

    /* Returns a noise value between [0, 1]
    @remarks
        The noise is calculated in realtime
    */
    double noise(double x, double y, double z);

    /* Returns a noise value between [0, 1]
    @remarks
        The noise is calculated in realtime
    */
    double noise(const Vec3& position);

    ///* Creates an image file to test the noise */
    //void noise2img(unsigned short dimension = 255);

protected:

        /* Returns a noise value between [0, 1]
    @remarks
        The noise is calculated in realtime
    */
    double genNoise(double x, double y, double z);

    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);

protected:

    int _p[512];
    unsigned short _octaves;
    double _frequency;
    double _amplitude;
    double _persistence;
};

NS_CC_END

#endif
