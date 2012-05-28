/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

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
package org.cocos2dx.lib;

import android.content.Context;
import android.content.res.Configuration;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.view.Display;
import android.view.Surface;
import android.view.WindowManager;

/**
 * 
 * This class is used for controlling the Accelerometer
 *
 */
public class Cocos2dxAccelerometer implements SensorEventListener {
	
	private static final String TAG = "Cocos2dxAccelerometer";
	private Context mContext;
	private SensorManager mSensorManager;
	private Sensor mAccelerometer;
	private int mNaturalOrientation;

	public Cocos2dxAccelerometer(Context context){
		mContext = context;

		//Get an instance of the SensorManager
	    mSensorManager = (SensorManager) mContext.getSystemService(Context.SENSOR_SERVICE);
	    mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
	    
	    Display display = ((WindowManager)mContext.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();
	    mNaturalOrientation = display.getOrientation();
	}

	public void enable() {
		mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_GAME);
	}

	public void disable () {
		mSensorManager.unregisterListener(this);
	}

	@Override
	public void onSensorChanged(SensorEvent event) {

		if (event.sensor.getType() != Sensor.TYPE_ACCELEROMETER){
            return;
		}

		float x = event.values[0];
		float y = event.values[1];
		float z = event.values[2];
		
		/*
		 * Because the axes are not swapped when the device's screen orientation changes. 
		 * So we should swap it here.
		 * In tablets such as Motorola Xoom, the default orientation is landscape, so should
		 * consider this.
		 */
		int orientation = mContext.getResources().getConfiguration().orientation;
		if ((orientation == Configuration.ORIENTATION_LANDSCAPE) && (mNaturalOrientation != Surface.ROTATION_0)){
			float tmp = x;
			x = -y;
			y = tmp;
		}
		else if ((orientation == Configuration.ORIENTATION_PORTRAIT) && (mNaturalOrientation != Surface.ROTATION_0))
		{
			 float tmp = x;
	         x = y;
	         y = -tmp;
		}
				
        onSensorChanged(x, y, z, event.timestamp);
        // Log.d(TAG, "x = " + event.values[0] + " y = " + event.values[1] + " z = " + event.values[2]);
	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
	}

	private static native void onSensorChanged(float x, float y, float z, long timeStamp);
}
