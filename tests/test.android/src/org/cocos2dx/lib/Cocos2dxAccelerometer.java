package org.cocos2dx.lib;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

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

	public Cocos2dxAccelerometer(Context context){
		mContext = context;

		//Get an instance of the SensorManager
	    mSensorManager = (SensorManager) mContext.getSystemService(Context.SENSOR_SERVICE);
	    mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
	}

	public void enable() {
		mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_GAME);
	}

	public void disable () {
		mSensorManager.unregisterListener(this);
	}

	@Override
	public void onSensorChanged(SensorEvent event) {

		if (event.sensor.getType() != Sensor.TYPE_ACCELEROMETER)
            return;

        onSensorChanged(event.values[0], event.values[1], event.values[2], event.timestamp);
        
	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
	}

	private static native void onSensorChanged(float x, float y, float z, long timeStamp);
}
