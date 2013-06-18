/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCAccelerometer.h"

#include <stdlib.h>

NS_CC_BEGIN

int	CCAccelerometer::_initialOrientationAngle = 0;

CCAccelerometer::CCAccelerometer()
{
	_accelDelegate = NULL;
	_initialOrientationAngle = atoi(getenv("ORIENTATION"));
}

CCAccelerometer::~CCAccelerometer()
{

}

void CCAccelerometer::setDelegate(CCAccelerometerDelegate* pDelegate)
{
	_accelDelegate = pDelegate;
}

void CCAccelerometer::update(long timeStamp, double x, double y, double z)
{
	if ( _accelDelegate != NULL)
	{
		if (getenv("WIDTH"))
		{
			_accelerationValue.x = x;
			_accelerationValue.y = y;
		}
		else // for PlayBook we need to take into account the initial orientation
		{
			if (_initialOrientationAngle == 270)
			{
				_accelerationValue.x = y;
				_accelerationValue.y = -x;
			}
			else if (_initialOrientationAngle == 90)
			{
				_accelerationValue.x = -y;
				_accelerationValue.y = x;
			}
			else if (_initialOrientationAngle == 0)
			{
				_accelerationValue.x = x;
				_accelerationValue.y = y;
			}
			else if (_initialOrientationAngle == 180)
			{
				_accelerationValue.x = -x;
				_accelerationValue.y = -y;
			}
		}

		_accelerationValue.z = z;
		_accelerationValue.timestamp = (double)timeStamp;

		_accelDelegate->didAccelerate(&_accelerationValue);
	}
}

NS_CC_END

