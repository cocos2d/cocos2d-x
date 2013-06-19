/****************************************************************************
 Copyright (c) 2011      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) 2011      Максим Аксенов
 Copyright (c) 2011      Giovanni Zito, Francis Styck
 
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
#include "ccMacros.h"

namespace cocos2d
{

CCAccelerometer* CCAccelerometer::_spCCAccelerometer = NULL;

CCAccelerometer::CCAccelerometer() : _function(nullptr)
{
}

CCAccelerometer::~CCAccelerometer() 
{
//	if( _spCCAccelerometer ) {
//		delete _spCCAccelerometer ;
		_spCCAccelerometer = NULL;
//	}
}

CCAccelerometer* CCAccelerometer::sharedAccelerometer() 
{

	if (_spCCAccelerometer == NULL)
	{
		_spCCAccelerometer = new CCAccelerometer();
	}

	return _spCCAccelerometer;
}

void CCAccelerometer::setDelegate(std::function<void(CCAcceleration*)> function) 
{
	_function = function;

	if (_function)
	{		
		if (s3eAccelerometerStart() != S3E_RESULT_SUCCESS)
		{
			CCLog("s3eAccelerometerStart() - ERROR");
		}
	}
	else
	{
		s3eAccelerometerStop();
	}
}

void CCAccelerometer::update(float x, float y, float z, uint64 sensorTimeStamp) 
{
	if (_function)
	{
		_accelerationValue.x = ((double)x)/S3E_ACCELEROMETER_1G ;
		_accelerationValue.y = ((double)y)/S3E_ACCELEROMETER_1G ;
		_accelerationValue.z = ((double)z)/S3E_ACCELEROMETER_1G ;
		_accelerationValue.timestamp = (double)(sensorTimeStamp / 1000.0);

		_function(&_accelerationValue);
	}	
}

} // end of namespace cococs2d

