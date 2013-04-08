package org.cocos2dx.plugin;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.util.Log;


public class PluginWrapper {
	
	public static native void nativeInitPlugin(Object instance, String className);
	
	protected static Context sContext = null;
	protected static GLSurfaceView sGLSurfaceView = null; 
	protected static Handler sMainThreadHandler = null;
	private static final String TAG = "PluginWrapper";
	
	public static void init(Context context)
	{
		sContext = context;
		if (null == sMainThreadHandler) {
			sMainThreadHandler = new Handler();
		}
	}

	public static void setGLSurfaceView(GLSurfaceView value) {
		sGLSurfaceView = value;
	}
	
	protected static boolean initPlugin(String classFullName)
	{
		Log.i(TAG, "class name : ----" + classFullName + "----");
        Class<?> c = null;
        try {  
            c = Class.forName(classFullName);
        } catch (ClassNotFoundException e) {  
            Log.e(TAG, "Class " + classFullName + " not found.");
            e.printStackTrace();
            return false;
        }  

        try {
        	Context ctx = getContext();
			if (ctx != null) {
	        	Object o = c.getDeclaredConstructor(Context.class).newInstance(ctx);
				PluginWrapper.nativeInitPlugin(o, classFullName.replace('.', '/'));
				return true;
			} else {
				Log.e(TAG, "Plugin " + classFullName + " wasn't initialized.");
			}
        } catch (Exception e) {
			e.printStackTrace();
		}
        return false;
	}
	
	public static Context getContext() {
		return sContext;
	}
	
	public static void runOnGLThread(Runnable r) {
		if (null != sGLSurfaceView) {
			sGLSurfaceView.queueEvent(r);
		} else {
			Log.i(TAG, "runOnGLThread sGLSurfaceView is null");
			r.run();
		}
	}

	public static void runOnMainThread(Runnable r) {
		if (null == sMainThreadHandler) return;
		sMainThreadHandler.post(r);
	}
}
