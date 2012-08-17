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

int	CCAccelerometer::m_initialOrientationAngle = 0;

CCAccelerometer::CCAccelerometer()
{
	m_pAccelDelegate = NULL;
	m_initialOrientationAngle = atoi(getenv("ORIENTATION"));
}

CCAccelerometer::~CCAccelerometer()
{

}

void CCAccelerometer::setDelegate(CCAccelerometerDelegate* pDelegate)
{
	m_pAccelDelegate = pDelegate;
}

void CCAccelerometer::update(long timeStamp, double x, double y, double z)
{
	if ( m_pAccelDelegate != NULL)
	{
		if (getenv("WIDTH"))
		{
			m_accelerationValue.x = x;
			m_accelerationValue.y = y;
		}
		else // for PlayBook we need to take into account the initial orientation
		{
			if (m_initialOrientationAngle == 270)
			{
				m_accelerationValue.x = y;
				m_accelerationValue.y = -x;
			}
			else if (m_initialOrientationAngle == 90)
			{
				m_accelerationValue.x = -y;
				m_accelerationValue.y = x;
			}
			else if (m_initialOrientationAngle == 0)
			{
				m_accelerationValue.x = x;
				m_accelerationValue.y = y;
			}
			else if (m_initialOrientationAngle == 180)
			{
				m_accelerationValue.x = -x;
				m_accelerationValue.y = -y;
			}
		}

		m_accelerationValue.z = z;
		m_accelerationValue.timestamp = (double)timeStamp;

		m_pAccelDelegate->didAccelerate(&m_accelerationValue);
	}
}

NS_CC_END

