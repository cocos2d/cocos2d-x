/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "2d/CCActionGrid3D.h"
#include "base/CCDirector.h"

NS_CC_BEGIN
// implementation of Waves3D

Waves3D* Waves3D::create(float duration, const Size& gridSize, unsigned int waves, float amplitude)
{
    Waves3D *pAction = new (std::nothrow) Waves3D();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, waves, amplitude))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;    
}

bool Waves3D::initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude)
{
    if (Grid3DAction::initWithDuration(duration, gridSize))
    {
        _waves = waves;
        _amplitude = amplitude;
        _amplitudeRate = 1.0f;

        return true;
    }

    return false;
}

Waves3D* Waves3D::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) Waves3D();
    a->initWithDuration(_duration, _gridSize, _waves, _amplitude);
    a->autorelease();
    return a;
}

void Waves3D::update(float time)
{
    int i, j;
    for (i = 0; i < _gridSize.width + 1; ++i)
    {
        for (j = 0; j < _gridSize.height + 1; ++j)
        {
            Vec3 v = getOriginalVertex(Vec2(i ,j));
            v.z += (sinf((float)M_PI * time * _waves * 2 + (v.y+v.x) * 0.01f) * _amplitude * _amplitudeRate);
            //CCLOG("v.z offset is %f\n", (sinf((float)M_PI * time * _waves * 2 + (v.y+v.x) * .01f) * _amplitude * _amplitudeRate));
            setVertex(Vec2(i, j), v);
        }
    }
}

// implementation of FlipX3D

FlipX3D* FlipX3D::create(float duration)
{
    FlipX3D *action = new (std::nothrow) FlipX3D();

    if (action)
    {
        if (action->initWithDuration(duration))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool FlipX3D::initWithDuration(float duration)
{
    return Grid3DAction::initWithDuration(duration, Size(1, 1));
}

bool FlipX3D::initWithSize(const Size& gridSize, float duration)
{
    if (gridSize.width != 1 || gridSize.height != 1)
    {
        // Grid size must be (1,1)
        CCASSERT(0, "Grid size must be (1,1)");

        return false;
    }

    return Grid3DAction::initWithDuration(duration, gridSize);
}

FlipX3D* FlipX3D::clone() const
{
    // no copy constructor    
    auto a = new (std::nothrow) FlipX3D();
    a->initWithSize(_gridSize, _duration);
    a->autorelease();
    return a;
}

void FlipX3D::update(float time)
{
    float angle = (float)M_PI * time; // 180 degrees
    float mz = sinf(angle);
    angle = angle / 2.0f; // x calculates degrees from 0 to 90
    float mx = cosf(angle);

    Vec3 v0, v1, v, diff;

    v0 = getOriginalVertex(Vec2(1.0f, 1.0f));
    v1 = getOriginalVertex(Vec2());

    float    x0 = v0.x;
    float    x1 = v1.x;
    float    x;
    Vec2    a, b, c, d;

    if ( x0 > x1 )
    {
        // Normal Grid
        a.setZero();
        b.set(0.0f, 1.0f);
        c.set(1.0f, 0.0f);
        d.set(1.0f, 1.0f);
        x = x0;
    }
    else
    {
        // Reversed Grid
        c.setZero();
        d.set(0.0f, 1.0f);
        a.set(1.0f, 0.0f);
        b.set(1.0f, 1.0f);
        x = x1;
    }
    
    diff.x = ( x - x * mx );
    diff.z = fabsf( floorf( (x * mz) / 4.0f ) );

    // bottom-left
    v = getOriginalVertex(a);
    v.x = diff.x;
    v.z += diff.z;
    setVertex(a, v);
    
    // upper-left
    v = getOriginalVertex(b);
    v.x = diff.x;
    v.z += diff.z;
    setVertex(b, v);
    
    // bottom-right
    v = getOriginalVertex(c);
    v.x -= diff.x;
    v.z -= diff.z;
    setVertex(c, v);
    
    // upper-right
    v = getOriginalVertex(d);
    v.x -= diff.x;
    v.z -= diff.z;
    setVertex(d, v);
}

// implementation of FlipY3D

FlipY3D* FlipY3D::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) FlipY3D();
    a->initWithSize(_gridSize, _duration);
    a->autorelease();
    return a;
}

FlipY3D* FlipY3D::create(float duration)
{
    FlipY3D *action = new (std::nothrow) FlipY3D();

    if (action)
    {
        if (action->initWithDuration(duration))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

void FlipY3D::update(float time)
{
    float angle = (float)M_PI * time; // 180 degrees
    float mz = sinf( angle );
    angle = angle / 2.0f;     // x calculates degrees from 0 to 90
    float my = cosf(angle);
    
    Vec3    v0, v1, v, diff;
    
    v0 = getOriginalVertex(Vec2(1.0f, 1.0f));
    v1 = getOriginalVertex(Vec2());
    
    float    y0 = v0.y;
    float    y1 = v1.y;
    float y;
    Vec2    a, b, c, d;
    
    if (y0 > y1)
    {
        // Normal Grid
        a.setZero();
        b.set(0.0f, 1.0f);
        c.set(1.0f, 0.0f);
        d.set(1.0f, 1.0f);
        y = y0;
    }
    else
    {
        // Reversed Grid
        b.setZero();
        a.set(0.0f, 1.0f);
        d.set(1.0f, 0.0f);
        c.set(1.0f, 1.0f);
        y = y1;
    }
    
    diff.y = y - y * my;
    diff.z = fabsf(floorf((y * mz) / 4.0f));
    
    // bottom-left
    v = getOriginalVertex(a);
    v.y = diff.y;
    v.z += diff.z;
    setVertex(a, v);
    
    // upper-left
    v = getOriginalVertex(b);
    v.y -= diff.y;
    v.z -= diff.z;
    setVertex(b, v);
    
    // bottom-right
    v = getOriginalVertex(c);
    v.y = diff.y;
    v.z += diff.z;
    setVertex(c, v);
    
    // upper-right
    v = getOriginalVertex(d);
    v.y -= diff.y;
    v.z -= diff.z;
    setVertex(d, v);
}


// implementation of Lens3D

Lens3D* Lens3D::create(float duration, const Size& gridSize, const Vec2& position, float radius)
{
    Lens3D *action = new (std::nothrow) Lens3D();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize, position, radius))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool Lens3D::initWithDuration(float duration, const Size& gridSize, const Vec2& position, float radius)
{
    if (Grid3DAction::initWithDuration(duration, gridSize))
    {
        _position.set(-1.0f, -1.0f);
        setPosition(position);
        _radius = radius;
        _lensEffect = 0.7f;
        _concave = false;
        _dirty = true;

        return true;
    }

    return false;
}

Lens3D* Lens3D::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) Lens3D();
    a->initWithDuration(_duration, _gridSize, _position, _radius);
    a->autorelease();
    return a;
}

void Lens3D::setPosition(const Vec2& pos)
{
    if( !pos.equals(_position))
    {
        _position = pos;
        _dirty = true;
    }
}

void Lens3D::update(float time)
{
    CC_UNUSED_PARAM(time);
    if (_dirty)
    {
        int i, j;
        
        for (i = 0; i < _gridSize.width + 1; ++i)
        {
            for (j = 0; j < _gridSize.height + 1; ++j)
            {
                Vec3 v = getOriginalVertex(Vec2(i, j));
                Vec2 vect = _position - Vec2(v.x, v.y);
                float r = vect.getLength();
                
                if (r < _radius)
                {
                    r = _radius - r;
                    float pre_log = r / _radius;
                    if ( pre_log == 0 ) 
                    {
                        pre_log = 0.001f;
                    }

                    float l = logf(pre_log) * _lensEffect;
                    float new_r = expf( l ) * _radius;
                    
                    if (vect.getLength() > 0)
                    {
                        vect.normalize();
                        Vec2 new_vect = vect * new_r;
                        v.z += (_concave ? -1.0f : 1.0f) * new_vect.getLength() * _lensEffect;
                    }
                }
                
                setVertex(Vec2(i, j), v);
            }
        }
        
        _dirty = false;
    }
}

// implementation of Ripple3D

Ripple3D* Ripple3D::create(float duration, const Size& gridSize, const Vec2& position, float radius, unsigned int waves, float amplitude)
{
    Ripple3D *action = new (std::nothrow) Ripple3D();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize, position, radius, waves, amplitude))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool Ripple3D::initWithDuration(float duration, const Size& gridSize, const Vec2& position, float radius, unsigned int waves, float amplitude)
{
    if (Grid3DAction::initWithDuration(duration, gridSize))
    {
        setPosition(position);
        _radius = radius;
        _waves = waves;
        _amplitude = amplitude;
        _amplitudeRate = 1.0f;

        return true;
    }

    return false;
}

void Ripple3D::setPosition(const Vec2& position)
{
    _position = position;
}


Ripple3D* Ripple3D::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) Ripple3D();
    a->initWithDuration(_duration, _gridSize, _position, _radius, _waves, _amplitude);
    a->autorelease();
    return a;
}

void Ripple3D::update(float time)
{
    int i, j;

    for (i = 0; i < (_gridSize.width+1); ++i)
    {
        for (j = 0; j < (_gridSize.height+1); ++j)
        {
            Vec3 v = getOriginalVertex(Vec2(i, j));
            Vec2 vect = _position - Vec2(v.x,v.y);
            float r = vect.getLength();
            
            if (r < _radius)
            {
                r = _radius - r;
                float rate = powf(r / _radius, 2);
                v.z += (sinf( time*(float)M_PI * _waves * 2 + r * 0.1f) * _amplitude * _amplitudeRate * rate);
            }
            
            setVertex(Vec2(i, j), v);
        }
    }
}

// implementation of Shaky3D

Shaky3D* Shaky3D::create(float duration, const Size& gridSize, int range, bool shakeZ)
{
    Shaky3D *action = new (std::nothrow) Shaky3D();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize, range, shakeZ))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool Shaky3D::initWithDuration(float duration, const Size& gridSize, int range, bool shakeZ)
{
    if (Grid3DAction::initWithDuration(duration, gridSize))
    {
        _randrange = range;
        _shakeZ = shakeZ;

        return true;
    }

    return false;
}

Shaky3D* Shaky3D::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) Shaky3D();
    a->initWithDuration(_duration, _gridSize, _randrange, _shakeZ);
    a->autorelease();
    return a;
}

void Shaky3D::update(float time)
{
    CC_UNUSED_PARAM(time);
    int i, j;

    for (i = 0; i < (_gridSize.width+1); ++i)
    {
        for (j = 0; j < (_gridSize.height+1); ++j)
        {
            Vec3 v = getOriginalVertex(Vec2(i ,j));
            v.x += (rand() % (_randrange*2)) - _randrange;
            v.y += (rand() % (_randrange*2)) - _randrange;
            if (_shakeZ)
            {
                v.z += (rand() % (_randrange*2)) - _randrange;
            }
            
            setVertex(Vec2(i, j), v);
        }
    }
}

// implementation of Liquid

Liquid* Liquid::create(float duration, const Size& gridSize, unsigned int waves, float amplitude)
{
    Liquid *action = new (std::nothrow) Liquid();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize, waves, amplitude))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool Liquid::initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude)
{
    if (Grid3DAction::initWithDuration(duration, gridSize))
    {
        _waves = waves;
        _amplitude = amplitude;
        _amplitudeRate = 1.0f;

        return true;
    }

    return false;
}

Liquid* Liquid::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) Liquid();
    a->initWithDuration(_duration, _gridSize, _waves, _amplitude);
    a->autorelease();
    return a;
}

void Liquid::update(float time)
{
    int i, j;

    for (i = 1; i < _gridSize.width; ++i)
    {
        for (j = 1; j < _gridSize.height; ++j)
        {
            Vec3 v = getOriginalVertex(Vec2(i, j));
            v.x = (v.x + (sinf(time * (float)M_PI * _waves * 2 + v.x * .01f) * _amplitude * _amplitudeRate));
            v.y = (v.y + (sinf(time * (float)M_PI * _waves * 2 + v.y * .01f) * _amplitude * _amplitudeRate));
            setVertex(Vec2(i, j), v);
        }
    }
}

// implementation of Waves

Waves* Waves::create(float duration, const Size& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical)
{
    Waves *action = new (std::nothrow) Waves();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize, waves, amplitude, horizontal, vertical))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool Waves::initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical)
{
    if (Grid3DAction::initWithDuration(duration, gridSize))
    {
        _waves = waves;
        _amplitude = amplitude;
        _amplitudeRate = 1.0f;
        _horizontal = horizontal;
        _vertical = vertical;

        return true;
    }

    return false;
}

Waves* Waves::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) Waves();
    a->initWithDuration(_duration, _gridSize, _waves, _amplitude, _horizontal, _vertical);
    a->autorelease();
    return a;
}

void Waves::update(float time)
{
    int i, j;

    for (i = 0; i < _gridSize.width + 1; ++i)
    {
        for (j = 0; j < _gridSize.height + 1; ++j)
        {
            Vec3 v = getOriginalVertex(Vec2(i, j));

            if (_vertical)
            {
                v.x = (v.x + (sinf(time * (float)M_PI * _waves * 2 + v.y * .01f) * _amplitude * _amplitudeRate));
            }

            if (_horizontal)
            {
                v.y = (v.y + (sinf(time * (float)M_PI * _waves * 2 + v.x * .01f) * _amplitude * _amplitudeRate));
            }

            setVertex(Vec2(i, j), v);
        }
    }
}

// implementation of Twirl

Twirl* Twirl::create(float duration, const Size& gridSize, Vec2 position, unsigned int twirls, float amplitude)
{
    Twirl *action = new (std::nothrow) Twirl();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize, position, twirls, amplitude))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool Twirl::initWithDuration(float duration, const Size& gridSize, Vec2 position, unsigned int twirls, float amplitude)
{
    if (Grid3DAction::initWithDuration(duration, gridSize))
    {
        setPosition(position);
        _twirls = twirls;
        _amplitude = amplitude;
        _amplitudeRate = 1.0f;

        return true;
    }

    return false;
}

void Twirl::setPosition(const Vec2& position)
{
    _position = position;
}

Twirl *Twirl::clone() const
{
    // no copy constructor    
    auto a = new (std::nothrow) Twirl();
    a->initWithDuration(_duration, _gridSize, _position, _twirls, _amplitude);
    a->autorelease();
    return a;
}

void Twirl::update(float time)
{
    int i, j;
    Vec2    c = _position;
    
    for (i = 0; i < (_gridSize.width+1); ++i)
    {
        for (j = 0; j < (_gridSize.height+1); ++j)
        {
            Vec3 v = getOriginalVertex(Vec2(i ,j));
            
            Vec2 avg(i-(_gridSize.width/2.0f), j-(_gridSize.height/2.0f));
            float r = avg.getLength();
            
            float amp = 0.1f * _amplitude * _amplitudeRate;
            float a = r * cosf( (float)M_PI/2.0f + time * (float)M_PI * _twirls * 2 ) * amp;
            
            Vec2 d(
                sinf(a) * (v.y-c.y) + cosf(a) * (v.x-c.x),
                cosf(a) * (v.y-c.y) - sinf(a) * (v.x-c.x));
            
            v.x = c.x + d.x;
            v.y = c.y + d.y;

            setVertex(Vec2(i ,j), v);
        }
    }
}

NS_CC_END
