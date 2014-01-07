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
#include "CCActionGrid3D.h"
#include "CCDirector.h"
#include <stdlib.h>

NS_CC_BEGIN
// implementation of Waves3D

Waves3D* Waves3D::create(float duration, const Size& gridSize, unsigned int waves, float amplitude)
{
    Waves3D *pAction = new Waves3D();

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
	auto a = new Waves3D();
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
            Vertex3F v = getOriginalVertex(Point(i ,j));
            v.z += (sinf((float)M_PI * time * _waves * 2 + (v.y+v.x) * 0.01f) * _amplitude * _amplitudeRate);
            //CCLOG("v.z offset is %f\n", (sinf((float)M_PI * time * _waves * 2 + (v.y+v.x) * .01f) * _amplitude * _amplitudeRate));
            setVertex(Point(i, j), v);
        }
    }
}

// implementation of FlipX3D

FlipX3D* FlipX3D::create(float duration)
{
    FlipX3D *action = new FlipX3D();

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
	auto a = new FlipX3D();
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

    Vertex3F v0, v1, v, diff;

    v0 = getOriginalVertex(Point(1, 1));
    v1 = getOriginalVertex(Point(0, 0));

    float    x0 = v0.x;
    float    x1 = v1.x;
    float    x;
    Point    a, b, c, d;

    if ( x0 > x1 )
    {
        // Normal Grid
        a = Point(0,0);
        b = Point(0,1);
        c = Point(1,0);
        d = Point(1,1);
        x = x0;
    }
    else
    {
        // Reversed Grid
        c = Point(0,0);
        d = Point(0,1);
        a = Point(1,0);
        b = Point(1,1);
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
	auto a = new FlipY3D();
    a->initWithSize(_gridSize, _duration);
	a->autorelease();
	return a;
}

FlipY3D* FlipY3D::create(float duration)
{
    FlipY3D *action = new FlipY3D();

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
    
    Vertex3F    v0, v1, v, diff;
    
    v0 = getOriginalVertex(Point(1, 1));
    v1 = getOriginalVertex(Point(0, 0));
    
    float    y0 = v0.y;
    float    y1 = v1.y;
    float y;
    Point    a, b, c, d;
    
    if (y0 > y1)
    {
        // Normal Grid
        a = Point(0,0);
        b = Point(0,1);
        c = Point(1,0);
        d = Point(1,1);
        y = y0;
    }
    else
    {
        // Reversed Grid
        b = Point(0,0);
        a = Point(0,1);
        d = Point(1,0);
        c = Point(1,1);
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

Lens3D* Lens3D::create(float duration, const Size& gridSize, const Point& position, float radius)
{
    Lens3D *action = new Lens3D();

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

bool Lens3D::initWithDuration(float duration, const Size& gridSize, const Point& position, float radius)
{
    if (Grid3DAction::initWithDuration(duration, gridSize))
    {
        _position = Point(-1, -1);
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
	auto a = new Lens3D();
	a->initWithDuration(_duration, _gridSize, _position, _radius);
	a->autorelease();
	return a;
}

void Lens3D::setPosition(const Point& pos)
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
                Vertex3F v = getOriginalVertex(Point(i, j));
                Point vect = _position - Point(v.x, v.y);
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
                        vect = vect.normalize();
                        Point new_vect = vect * new_r;
                        v.z += (_concave ? -1.0f : 1.0f) * new_vect.getLength() * _lensEffect;
                    }
                }
                
                setVertex(Point(i, j), v);
            }
        }
        
        _dirty = false;
    }
}

// implementation of Ripple3D

Ripple3D* Ripple3D::create(float duration, const Size& gridSize, const Point& position, float radius, unsigned int waves, float amplitude)
{
    Ripple3D *action = new Ripple3D();

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

bool Ripple3D::initWithDuration(float duration, const Size& gridSize, const Point& position, float radius, unsigned int waves, float amplitude)
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

void Ripple3D::setPosition(const Point& position)
{
    _position = position;
}


Ripple3D* Ripple3D::clone() const
{
	// no copy constructor
	auto a = new Ripple3D();
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
            Vertex3F v = getOriginalVertex(Point(i, j));
            Point vect = _position - Point(v.x,v.y);
            float r = vect.getLength();
            
            if (r < _radius)
            {
                r = _radius - r;
                float rate = powf(r / _radius, 2);
                v.z += (sinf( time*(float)M_PI * _waves * 2 + r * 0.1f) * _amplitude * _amplitudeRate * rate);
            }
            
            setVertex(Point(i, j), v);
        }
    }
}

// implementation of Shaky3D

Shaky3D* Shaky3D::create(float duration, const Size& gridSize, int range, bool shakeZ)
{
    Shaky3D *action = new Shaky3D();

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
	auto a = new Shaky3D();
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
            Vertex3F v = getOriginalVertex(Point(i ,j));
            v.x += (rand() % (_randrange*2)) - _randrange;
            v.y += (rand() % (_randrange*2)) - _randrange;
            if (_shakeZ)
            {
                v.z += (rand() % (_randrange*2)) - _randrange;
            }
            
            setVertex(Point(i, j), v);
        }
    }
}

// implementation of Liquid

Liquid* Liquid::create(float duration, const Size& gridSize, unsigned int waves, float amplitude)
{
    Liquid *action = new Liquid();

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
	auto a = new Liquid();
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
            Vertex3F v = getOriginalVertex(Point(i, j));
            v.x = (v.x + (sinf(time * (float)M_PI * _waves * 2 + v.x * .01f) * _amplitude * _amplitudeRate));
            v.y = (v.y + (sinf(time * (float)M_PI * _waves * 2 + v.y * .01f) * _amplitude * _amplitudeRate));
            setVertex(Point(i, j), v);
        }
    }
}

// implementation of Waves

Waves* Waves::create(float duration, const Size& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical)
{
    Waves *action = new Waves();

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
	auto a = new Waves();
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
            Vertex3F v = getOriginalVertex(Point(i, j));

            if (_vertical)
            {
                v.x = (v.x + (sinf(time * (float)M_PI * _waves * 2 + v.y * .01f) * _amplitude * _amplitudeRate));
            }

            if (_horizontal)
            {
                v.y = (v.y + (sinf(time * (float)M_PI * _waves * 2 + v.x * .01f) * _amplitude * _amplitudeRate));
            }

            setVertex(Point(i, j), v);
        }
    }
}

// implementation of Twirl

Twirl* Twirl::create(float duration, const Size& gridSize, Point position, unsigned int twirls, float amplitude)
{
    Twirl *action = new Twirl();

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

bool Twirl::initWithDuration(float duration, const Size& gridSize, Point position, unsigned int twirls, float amplitude)
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

void Twirl::setPosition(const Point& position)
{
    _position = position;
}

Twirl *Twirl::clone() const
{
	// no copy constructor	
	auto a = new Twirl();
	a->initWithDuration(_duration, _gridSize, _position, _twirls, _amplitude);
	a->autorelease();
	return a;
}

void Twirl::update(float time)
{
    int i, j;
    Point    c = _position;
    
    for (i = 0; i < (_gridSize.width+1); ++i)
    {
        for (j = 0; j < (_gridSize.height+1); ++j)
        {
            Vertex3F v = getOriginalVertex(Point(i ,j));
            
            Point    avg = Point(i-(_gridSize.width/2.0f), j-(_gridSize.height/2.0f));
            float r = avg.getLength();
            
            float amp = 0.1f * _amplitude * _amplitudeRate;
            float a = r * cosf( (float)M_PI/2.0f + time * (float)M_PI * _twirls * 2 ) * amp;
            
            Point d = Point(
                sinf(a) * (v.y-c.y) + cosf(a) * (v.x-c.x),
                cosf(a) * (v.y-c.y) - sinf(a) * (v.x-c.x));
            
            v.x = c.x + d.x;
            v.y = c.y + d.y;

            setVertex(Point(i ,j), v);
        }
    }
}

NS_CC_END

