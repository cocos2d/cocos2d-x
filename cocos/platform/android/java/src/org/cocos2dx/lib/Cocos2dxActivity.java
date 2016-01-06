/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org

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

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.preference.PreferenceManager.OnActivityResultListener;
import android.util.AttributeSet;
import android.util.Log;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.FrameLayout;

import com.chukong.cocosplay.client.CocosPlayClient;

import org.cocos2dx.lib.Cocos2dxHelper.Cocos2dxHelperListener;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLDisplay;

public abstract class Cocos2dxActivity extends Activity implements Cocos2dxHelperListener {
    // ===========================================================
    // Constants
    // ===========================================================

    private final static String TAG = Cocos2dxActivity.class.getSimpleName();

    // ===========================================================
    // Fields
    // ===========================================================
    
    private Cocos2dxGLSurfaceView mGLSurfaceView = null;
    private int[] mGLContextAttrs = null;
    private Cocos2dxHandler mHandler = null;   
    private static Cocos2dxActivity sContext = null;
    private Cocos2dxVideoHelper mVideoHelper = null;
    private Cocos2dxWebViewHelper mWebViewHelper = null;
    private Cocos2dxEditBoxHelper mEditBoxHelper = null;
    private boolean hasFocus = false;

    public Cocos2dxGLSurfaceView getGLSurfaceView(){
        return  mGLSurfaceView;
    }

    public class Cocos2dxEGLConfigChooser implements GLSurfaceView.EGLConfigChooser
    {
        protected int[] configAttribs;
        public Cocos2dxEGLConfigChooser(int redSize, int greenSize, int blueSize, int alphaSize, int depthSize, int stencilSize)
        {
            configAttribs = new int[] {redSize, greenSize, blueSize, alphaSize, depthSize, stencilSize};
        }
        public Cocos2dxEGLConfigChooser(int[] attribs)
        {
            configAttribs = attribs;
        }

        private int findConfigAttrib(EGL10 egl, EGLDisplay display,
                EGLConfig config, int attribute, int defaultValue) {
            int[] value = new int[1];
            if (egl.eglGetConfigAttrib(display, config, attribute, value)) {
                return value[0];
            }
            return defaultValue;
        }

        class ConfigValue implements Comparable<ConfigValue> {

            public EGLConfig config = null;
            public int[] configAttribs = null;
            public int value = 0;
            private void calcValue() {
                // depth factor 29bit and [6,12)bit
                if (configAttribs[4] > 0) {
                    value = value + (1 << 29) + ((configAttribs[4]%64) << 6);
                }
                // stencil factor 28bit and [0, 6)bit
                if (configAttribs[5] > 0) {
                    value = value + (1 << 28) + ((configAttribs[5]%64));
                }
                // alpha factor 30bit and [24, 28)bit
                if (configAttribs[3] > 0) {
                    value = value + (1 << 30) + ((configAttribs[3]%16) << 24);
                }
                // green factor [20, 24)bit
                if (configAttribs[1] > 0) {
                    value = value + ((configAttribs[1]%16) << 20);
                }
                // blue factor [16, 20)bit
                if (configAttribs[2] > 0) {
                    value = value + ((configAttribs[2]%16) << 16);
                }
                // red factor [12, 16)bit
                if (configAttribs[0] > 0) {
                    value = value + ((configAttribs[0]%16) << 12);
                }
            }

            public ConfigValue(int[] attribs) {
                configAttribs = attribs;
                calcValue();
            }

            public ConfigValue(EGL10 egl, EGLDisplay display, EGLConfig config) {
                this.config = config;
                configAttribs = new int[6];
                configAttribs[0] = findConfigAttrib(egl, display, config, EGL10.EGL_RED_SIZE, 0);
                configAttribs[1] = findConfigAttrib(egl, display, config, EGL10.EGL_GREEN_SIZE, 0);
                configAttribs[2] = findConfigAttrib(egl, display, config, EGL10.EGL_BLUE_SIZE, 0);
                configAttribs[3] = findConfigAttrib(egl, display, config, EGL10.EGL_ALPHA_SIZE, 0);
                configAttribs[4] = findConfigAttrib(egl, display, config, EGL10.EGL_DEPTH_SIZE, 0);
                configAttribs[5] = findConfigAttrib(egl, display, config, EGL10.EGL_STENCIL_SIZE, 0);
                calcValue();
            }

            @Override
            public int compareTo(ConfigValue another) {
                if (value < another.value) {
                    return -1;
                } else if (value > another.value) {
                    return 1;
                } else {
                    return 0;
                }
            }

            @Override
            public String toString() {
                return "{ color: " + configAttribs[3] + configAttribs[2] + configAttribs[1] + configAttribs[0] +
                        "; depth: " + configAttribs[4] + "; stencil: " + configAttribs[5] + ";}";
            }
        }

        @Override
        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) 
        {
            int[] EGLattribs = {
                    EGL10.EGL_RED_SIZE, configAttribs[0],
                    EGL10.EGL_GREEN_SIZE, configAttribs[1],
                    EGL10.EGL_BLUE_SIZE, configAttribs[2],
                    EGL10.EGL_ALPHA_SIZE, configAttribs[3],
                    EGL10.EGL_DEPTH_SIZE, configAttribs[4],
                    EGL10.EGL_STENCIL_SIZE,configAttribs[5],
                    EGL10.EGL_RENDERABLE_TYPE, 4, //EGL_OPENGL_ES2_BIT
                    EGL10.EGL_NONE
            };
            EGLConfig[] configs = new EGLConfig[1];
            int[] numConfigs = new int[1];
            boolean eglChooseResult = egl.eglChooseConfig(display, EGLattribs, configs, 1, numConfigs);
            if (eglChooseResult && numConfigs[0] > 0)
            {
                return configs[0];
            }

            // there's no config match the specific configAttribs, we should choose a closest one
            int[] EGLV2attribs = {
                    EGL10.EGL_RENDERABLE_TYPE, 4, //EGL_OPENGL_ES2_BIT
                    EGL10.EGL_NONE
            };
            eglChooseResult = egl.eglChooseConfig(display, EGLV2attribs, null, 0, numConfigs);
            if(eglChooseResult && numConfigs[0] > 0) {
                int num = numConfigs[0];
                ConfigValue[] cfgVals = new ConfigValue[num];

                // convert all config to ConfigValue
                configs = new EGLConfig[num];
                egl.eglChooseConfig(display, EGLV2attribs, configs, num, numConfigs);
                for (int i = 0; i < num; ++i) {
                    cfgVals[i] = new ConfigValue(egl, display, configs[i]);
                }

                ConfigValue e = new ConfigValue(configAttribs);
                // bin search
                int lo = 0;
                int hi = num;
                int mi;
                while (lo < hi - 1) {
                    mi = (lo + hi) / 2;
                    if (e.compareTo(cfgVals[mi]) < 0) {
                        hi = mi;
                    } else {
                        lo = mi;
                    }
                }
                if (lo != num - 1) {
                    lo = lo + 1;
                }
                Log.w("cocos2d", "Can't find EGLConfig match: " + e + ", instead of closest one:" + cfgVals[lo]);
                return cfgVals[lo].config;
            }

            Log.e(DEVICE_POLICY_SERVICE, "Can not select an EGLConfig for rendering.");
            return null;
        }

    }
    
    public static Context getContext() {
        return sContext;
    }
    
    public void setKeepScreenOn(boolean value) {
        final boolean newValue = value;
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mGLSurfaceView.setKeepScreenOn(newValue);
            }
        });
    }
    
    protected void onLoadNativeLibraries() {
        try {
            ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
            Bundle bundle = ai.metaData;
            String libName = bundle.getString("android.app.lib_name");
            System.loadLibrary(libName);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    // ===========================================================
    // Constructors
    // ===========================================================

    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        CocosPlayClient.init(this, false);

        onLoadNativeLibraries();

        sContext = this;
        this.mHandler = new Cocos2dxHandler(this);
        
        Cocos2dxHelper.init(this);
        
        this.mGLContextAttrs = getGLContextAttrs();
        this.init();

        if (mVideoHelper == null) {
            mVideoHelper = new Cocos2dxVideoHelper(this, mFrameLayout);
        }
        
        if(mWebViewHelper == null){
            mWebViewHelper = new Cocos2dxWebViewHelper(mFrameLayout);
        }

        if(mEditBoxHelper == null){
            mEditBoxHelper = new Cocos2dxEditBoxHelper(mFrameLayout);
        }

        Window window = this.getWindow();
        window.setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_ADJUST_PAN);
    }

    //native method,call GLViewImpl::getGLContextAttrs() to get the OpenGL ES context attributions
    private static native int[] getGLContextAttrs();
    
    // ===========================================================
    // Getter & Setter
    // ===========================================================

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    @Override
    protected void onResume() {
    	Log.d(TAG, "onResume()");
        super.onResume();
       	resumeIfHasFocus();
    }
    
    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
    	Log.d(TAG, "onWindowFocusChanged() hasFocus=" + hasFocus);
        super.onWindowFocusChanged(hasFocus);
        
        this.hasFocus = hasFocus;
        resumeIfHasFocus();
    }
    
    private void resumeIfHasFocus() {
        if(hasFocus) {
        	Cocos2dxHelper.onResume();
        	mGLSurfaceView.onResume();
        }
    }

    @Override
    protected void onPause() {
    	Log.d(TAG, "onPause()");
        super.onPause();
        Cocos2dxHelper.onPause();
        mGLSurfaceView.onPause();
    }
    
    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    @Override
    public void showDialog(final String pTitle, final String pMessage) {
        Message msg = new Message();
        msg.what = Cocos2dxHandler.HANDLER_SHOW_DIALOG;
        msg.obj = new Cocos2dxHandler.DialogMessage(pTitle, pMessage);
        this.mHandler.sendMessage(msg);
    }
    
    @Override
    public void runOnGLThread(final Runnable pRunnable) {
        this.mGLSurfaceView.queueEvent(pRunnable);
    }
    
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        for (OnActivityResultListener listener : Cocos2dxHelper.getOnActivityResultListeners()) {
            listener.onActivityResult(requestCode, resultCode, data);
        }

        super.onActivityResult(requestCode, resultCode, data);
    }


    protected ResizeLayout mFrameLayout = null;
    // ===========================================================
    // Methods
    // ===========================================================
    public void init() {
        
        // FrameLayout
        ViewGroup.LayoutParams framelayout_params =
            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                       ViewGroup.LayoutParams.MATCH_PARENT);

        mFrameLayout = new ResizeLayout(this);

        mFrameLayout.setLayoutParams(framelayout_params);

        // Cocos2dxEditText layout
        ViewGroup.LayoutParams edittext_layout_params =
            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                       ViewGroup.LayoutParams.WRAP_CONTENT);
        Cocos2dxEditBox edittext = new Cocos2dxEditBox(this);
        edittext.setLayoutParams(edittext_layout_params);


        mFrameLayout.addView(edittext);

        // Cocos2dxGLSurfaceView
        this.mGLSurfaceView = this.onCreateView();

        // ...add to FrameLayout
        mFrameLayout.addView(this.mGLSurfaceView);

        // Switch to supported OpenGL (ARGB888) mode on emulator
        if (isAndroidEmulator())
           this.mGLSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);

        this.mGLSurfaceView.setCocos2dxRenderer(new Cocos2dxRenderer());
        this.mGLSurfaceView.setCocos2dxEditText(edittext);

        // Set framelayout as the content view
        setContentView(mFrameLayout);
    }

    
    public Cocos2dxGLSurfaceView onCreateView() {
        Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
        //this line is need on some device if we specify an alpha bits
        if(this.mGLContextAttrs[3] > 0) glSurfaceView.getHolder().setFormat(PixelFormat.TRANSLUCENT);

        Cocos2dxEGLConfigChooser chooser = new Cocos2dxEGLConfigChooser(this.mGLContextAttrs);
        glSurfaceView.setEGLConfigChooser(chooser);

        return glSurfaceView;
    }

   private final static boolean isAndroidEmulator() {
      String model = Build.MODEL;
      Log.d(TAG, "model=" + model);
      String product = Build.PRODUCT;
      Log.d(TAG, "product=" + product);
      boolean isEmulator = false;
      if (product != null) {
         isEmulator = product.equals("sdk") || product.contains("_sdk") || product.contains("sdk_");
      }
      Log.d(TAG, "isEmulator=" + isEmulator);
      return isEmulator;
   }

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================
}
