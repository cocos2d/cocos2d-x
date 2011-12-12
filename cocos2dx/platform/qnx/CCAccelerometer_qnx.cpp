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
#include "CCAccelerometer_qnx.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bps/accelerometer.h>
#include <fcntl.h>

#define BUFFER_SIZE 			30

namespace cocos2d
{
	CCAccelerometer* CCAccelerometer::m_spCCAccelerometer = NULL;

	CCAccelerometer::CCAccelerometer()
	{
		m_pAccelDelegate = NULL;

		accelerometer_set_update_frequency(FREQ_40_HZ);
	}

    CCAccelerometer::~CCAccelerometer()
    {

    }

    CCAccelerometer* CCAccelerometer::sharedAccelerometer()
    {
    	if (m_spCCAccelerometer == NULL)
    		m_spCCAccelerometer = new CCAccelerometer();
    	
    	return m_spCCAccelerometer;
    }

    void CCAccelerometer::setDelegate(CCAccelerometerDelegate* pDelegate)
    {
    	m_pAccelDelegate = pDelegate;
    }

	void CCAccelerometer::update(long timeStamp)
	{
		if ( m_pAccelDelegate != NULL)
		{
			double x, y, z;

			accelerometer_read_forces(&x, &y, &z);

			m_accelerationValue.x = x;
			m_accelerationValue.y = y;
			m_accelerationValue.z = z;
			m_accelerationValue.timestamp = (double)timeStamp;

			m_pAccelDelegate->didAccelerate(&m_accelerationValue);
		}
	}

} // end of namespace cococs2d

