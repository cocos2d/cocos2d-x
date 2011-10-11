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

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.os.Message;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.inputmethod.InputMethodManager;
import android.widget.TextView;
import android.widget.TextView.OnEditorActionListener;

class TextInputWraper implements TextWatcher, OnEditorActionListener {
	
	private static final Boolean debug = false;
	private void LogD(String msg) {
		if (debug) Log.d("TextInputFilter", msg);
	}
	
	private Cocos2dxGLSurfaceView mMainView;
	private String mText;
	private String mOriginText;
	
	private Boolean isFullScreenEdit() {
		InputMethodManager imm = (InputMethodManager)mMainView.getTextField().getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
		return imm.isFullscreenMode();
	}

	public TextInputWraper(Cocos2dxGLSurfaceView view) {
		mMainView = view;
	}
	
	public void setOriginText(String text) {
		mOriginText = text;
	}
	
	@Override
	public void afterTextChanged(Editable s) {
		if (isFullScreenEdit()) {
			return;
		}
		
		LogD("afterTextChanged: " + s);
		int nModified = s.length() - mText.length();
		if (nModified > 0) {
			final String insertText = s.subSequence(mText.length(), s.length()).toString();
			mMainView.insertText(insertText);
			LogD("insertText(" + insertText + ")");
		}
		else {
			for (; nModified < 0; ++nModified) {
				mMainView.deleteBackward();
				LogD("deleteBackward");
			}
		}
		mText = s.toString();
	}

	@Override
	public void beforeTextChanged(CharSequence s, int start, int count,
			int after) {
		LogD("beforeTextChanged(" + s + ")start: " + start + ",count: " + count + ",after: " + after);
		mText = s.toString();
	}

	@Override
	public void onTextChanged(CharSequence s, int start, int before, int count) {
	}

	@Override
	public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
		if (mMainView.getTextField() == v && isFullScreenEdit()) {
			// user press the action button, delete all old text and insert new text
			for (int i = mOriginText.length(); i > 0; --i) {
				mMainView.deleteBackward();
				LogD("deleteBackward");
			}
			String text = v.getText().toString();
			
			/*
			 * If user input nothing, translate "\n" to engine.
			 */
			if (text.compareTo("") == 0){
				text = "\n";
			}
			
			if ('\n' != text.charAt(text.length() - 1)) {
				text += '\n';
			}
			
			final String insertText = text;
			mMainView.insertText(insertText);
			LogD("insertText(" + insertText + ")");
		}
		return false;
	}
}

public class Cocos2dxGLSurfaceView extends GLSurfaceView {
    
    static private Cocos2dxGLSurfaceView mainView;

    private static final String TAG = Cocos2dxGLSurfaceView.class.getCanonicalName();
    private Cocos2dxRenderer mRenderer;
    
    private static final boolean debug = false;
	
    ///////////////////////////////////////////////////////////////////////////
    // for initialize
	///////////////////////////////////////////////////////////////////////////
    public Cocos2dxGLSurfaceView(Context context) {
        super(context);
        initView(false, 0, 0);
    }

    public Cocos2dxGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView(false, 0, 0);
    }

    protected void initView(boolean translucent, int depth, int stencil) {
        /* By default, GLSurfaceView() creates a RGB_565 opaque surface.
         * If we want a translucent one, we should change the surface's
         * format here, using PixelFormat.TRANSLUCENT for GL Surfaces
         * is interpreted as any 32-bit surface with alpha by SurfaceFlinger.
         */
        if (translucent) {
            this.getHolder().setFormat(PixelFormat.TRANSLUCENT);
        }
		
        /* Setup the context factory for 2.0 rendering.
         * See ContextFactory class definition below
         */
        setEGLContextFactory(new ContextFactory());
		
        /* We need to choose an EGLConfig that matches the format of
         * our surface exactly. This is going to be done in our
         * custom config chooser. See ConfigChooser class definition
         * below.
         */
        setEGLConfigChooser( translucent ?
							new ConfigChooser(8, 8, 8, 8, depth, stencil) :
							new ConfigChooser(5, 6, 5, 0, depth, stencil) );

    	mRenderer = new Cocos2dxRenderer();
        setFocusableInTouchMode(true);
        setRenderer(mRenderer);
        
        textInputWraper = new TextInputWraper(this);

        handler = new Handler(){
        	public void handleMessage(Message msg){
        		switch(msg.what){
        		case HANDLER_OPEN_IME_KEYBOARD:
        			if (null != mTextField && mTextField.requestFocus()) {
        				mTextField.removeTextChangedListener(textInputWraper);
        				mTextField.setText("");
        				String text = (String)msg.obj;
        				mTextField.append(text);
        				textInputWraper.setOriginText(text);
        				mTextField.addTextChangedListener(textInputWraper);
                        InputMethodManager imm = (InputMethodManager)mainView.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
                        imm.showSoftInput(mTextField, 0);
                        Log.d("GLSurfaceView", "showSoftInput");
        			}
        			break;
        			
        		case HANDLER_CLOSE_IME_KEYBOARD:
        			if (null != mTextField) {
        				mTextField.removeTextChangedListener(textInputWraper);
                        InputMethodManager imm = (InputMethodManager)mainView.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
                        imm.hideSoftInputFromWindow(mTextField.getWindowToken(), 0);
                        Log.d("GLSurfaceView", "HideSoftInput");
        			}
        			break;
        		}
        	}
        };

        mainView = this;
    }
    
    private static class ContextFactory implements GLSurfaceView.EGLContextFactory {
        private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
        public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) {
            Log.w(TAG, "creating OpenGL ES context");
            checkEglError("Before eglCreateContext", egl);
            int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE };
            EGLContext context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
            checkEglError("After eglCreateContext", egl);
            return context;
        }
		
        public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
            Log.w(TAG, "egl.eglDestroyContext");
            egl.eglDestroyContext(display, context);
        }
    }
	
    private static void checkEglError(String prompt, EGL10 egl) {
        int error;
		Log.w(TAG, "checkEglError");
        while ((error = egl.eglGetError()) != EGL10.EGL_SUCCESS) {
            Log.e(TAG, String.format("%s: EGL error: 0x%x", prompt, error));
        }
    }
	
    private static class ConfigChooser implements GLSurfaceView.EGLConfigChooser {
		
        public ConfigChooser(int r, int g, int b, int a, int depth, int stencil) {
            mRedSize = r;
            mGreenSize = g;
            mBlueSize = b;
            mAlphaSize = a;
            mDepthSize = depth;
            mStencilSize = stencil;
        }
		
        /* This EGL config specification is used to specify 2.0 rendering.
         * We use a minimum size of 4 bits for red/green/blue, but will
         * perform actual matching in chooseConfig() below.
         */
        private static int EGL_OPENGL_ES2_BIT = 4;
        private static int[] s_configAttribs2 =
        {
		EGL10.EGL_RED_SIZE, 4,
		EGL10.EGL_GREEN_SIZE, 4,
		EGL10.EGL_BLUE_SIZE, 4,
		EGL10.EGL_DEPTH_SIZE, 24,
		EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL10.EGL_NONE
        };
		
        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {
			Log.w(TAG, "chooseConfig");
			
            /* Get the number of minimally matching EGL configurations
             */
            int[] num_config = new int[1];
            egl.eglChooseConfig(display, s_configAttribs2, null, 0, num_config);
			
            int numConfigs = num_config[0];
			
            if (numConfigs <= 0) {
                throw new IllegalArgumentException("No configs match configSpec");
            }
			
            /* Allocate then read the array of minimally matching EGL configs
             */
            EGLConfig[] configs = new EGLConfig[numConfigs];
            egl.eglChooseConfig(display, s_configAttribs2, configs, numConfigs, num_config);
			
            if (debug) {
				printConfigs(egl, display, configs);
            }
            /* Now return the "best" one
             */
            return chooseConfig(egl, display, configs);
        }
		
        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display,
									  EGLConfig[] configs) {
			Log.w(TAG, "chooseConfig");
			
            for(EGLConfig config : configs) {
                int d = findConfigAttrib(egl, display, config,
										 EGL10.EGL_DEPTH_SIZE, 0);
                int s = findConfigAttrib(egl, display, config,
										 EGL10.EGL_STENCIL_SIZE, 0);
				
                // We need at least mDepthSize and mStencilSize bits
                if (d < mDepthSize || s < mStencilSize)
                    continue;
				
                // We want an *exact* match for red/green/blue/alpha
                int r = findConfigAttrib(egl, display, config,
										 EGL10.EGL_RED_SIZE, 0);
                int g = findConfigAttrib(egl, display, config,
										 EGL10.EGL_GREEN_SIZE, 0);
                int b = findConfigAttrib(egl, display, config,
										 EGL10.EGL_BLUE_SIZE, 0);
                int a = findConfigAttrib(egl, display, config,
										 EGL10.EGL_ALPHA_SIZE, 0);
				
                if (r == mRedSize && g == mGreenSize && b == mBlueSize && a == mAlphaSize)
                    return config;
            }
            return null;
        }
		
        private int findConfigAttrib(EGL10 egl, EGLDisplay display,
									 EGLConfig config, int attribute, int defaultValue) {
			Log.w(TAG, "findConfigAttrib");
			
            if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) {
                return mValue[0];
            }
            return defaultValue;
        }
		
        private void printConfigs(EGL10 egl, EGLDisplay display,
								  EGLConfig[] configs) {
            int numConfigs = configs.length;
            Log.w(TAG, String.format("%d configurations", numConfigs));
            for (int i = 0; i < numConfigs; i++) {
                Log.w(TAG, String.format("Configuration %d:\n", i));
                printConfig(egl, display, configs[i]);
            }
        }
		
        private void printConfig(EGL10 egl, EGLDisplay display,
								 EGLConfig config) {
            int[] attributes = {
				EGL10.EGL_BUFFER_SIZE,
				EGL10.EGL_ALPHA_SIZE,
				EGL10.EGL_BLUE_SIZE,
				EGL10.EGL_GREEN_SIZE,
				EGL10.EGL_RED_SIZE,
				EGL10.EGL_DEPTH_SIZE,
				EGL10.EGL_STENCIL_SIZE,
				EGL10.EGL_CONFIG_CAVEAT,
				EGL10.EGL_CONFIG_ID,
				EGL10.EGL_LEVEL,
				EGL10.EGL_MAX_PBUFFER_HEIGHT,
				EGL10.EGL_MAX_PBUFFER_PIXELS,
				EGL10.EGL_MAX_PBUFFER_WIDTH,
				EGL10.EGL_NATIVE_RENDERABLE,
				EGL10.EGL_NATIVE_VISUAL_ID,
				EGL10.EGL_NATIVE_VISUAL_TYPE,
				0x3030, // EGL10.EGL_PRESERVED_RESOURCES,
				EGL10.EGL_SAMPLES,
				EGL10.EGL_SAMPLE_BUFFERS,
				EGL10.EGL_SURFACE_TYPE,
				EGL10.EGL_TRANSPARENT_TYPE,
				EGL10.EGL_TRANSPARENT_RED_VALUE,
				EGL10.EGL_TRANSPARENT_GREEN_VALUE,
				EGL10.EGL_TRANSPARENT_BLUE_VALUE,
				0x3039, // EGL10.EGL_BIND_TO_TEXTURE_RGB,
				0x303A, // EGL10.EGL_BIND_TO_TEXTURE_RGBA,
				0x303B, // EGL10.EGL_MIN_SWAP_INTERVAL,
				0x303C, // EGL10.EGL_MAX_SWAP_INTERVAL,
				EGL10.EGL_LUMINANCE_SIZE,
				EGL10.EGL_ALPHA_MASK_SIZE,
				EGL10.EGL_COLOR_BUFFER_TYPE,
				EGL10.EGL_RENDERABLE_TYPE,
				0x3042 // EGL10.EGL_CONFORMANT
            };
            String[] names = {
				"EGL_BUFFER_SIZE",
				"EGL_ALPHA_SIZE",
				"EGL_BLUE_SIZE",
				"EGL_GREEN_SIZE",
				"EGL_RED_SIZE",
				"EGL_DEPTH_SIZE",
				"EGL_STENCIL_SIZE",
				"EGL_CONFIG_CAVEAT",
				"EGL_CONFIG_ID",
				"EGL_LEVEL",
				"EGL_MAX_PBUFFER_HEIGHT",
				"EGL_MAX_PBUFFER_PIXELS",
				"EGL_MAX_PBUFFER_WIDTH",
				"EGL_NATIVE_RENDERABLE",
				"EGL_NATIVE_VISUAL_ID",
				"EGL_NATIVE_VISUAL_TYPE",
				"EGL_PRESERVED_RESOURCES",
				"EGL_SAMPLES",
				"EGL_SAMPLE_BUFFERS",
				"EGL_SURFACE_TYPE",
				"EGL_TRANSPARENT_TYPE",
				"EGL_TRANSPARENT_RED_VALUE",
				"EGL_TRANSPARENT_GREEN_VALUE",
				"EGL_TRANSPARENT_BLUE_VALUE",
				"EGL_BIND_TO_TEXTURE_RGB",
				"EGL_BIND_TO_TEXTURE_RGBA",
				"EGL_MIN_SWAP_INTERVAL",
				"EGL_MAX_SWAP_INTERVAL",
				"EGL_LUMINANCE_SIZE",
				"EGL_ALPHA_MASK_SIZE",
				"EGL_COLOR_BUFFER_TYPE",
				"EGL_RENDERABLE_TYPE",
				"EGL_CONFORMANT"
            };
            int[] value = new int[1];
            for (int i = 0; i < attributes.length; i++) {
                int attribute = attributes[i];
                String name = names[i];
                if ( egl.eglGetConfigAttrib(display, config, attribute, value)) {
                    Log.w(TAG, String.format("  %s: %d\n", name, value[0]));
                } else {
                    Log.w(TAG, String.format("  %s: failed\n", name));
//                    while (egl.eglGetError() != EGL10.EGL_SUCCESS);
                }
            }
        }
        
        // Subclasses can adjust these values:
        protected int mRedSize;
        protected int mGreenSize;
        protected int mBlueSize;
        protected int mAlphaSize;
        protected int mDepthSize;
        protected int mStencilSize;
        private int[] mValue = new int[1];
    }

    public void onPause(){    	
    	queueEvent(new Runnable() {
            @Override
            public void run() {
                mRenderer.handleOnPause();
            }
        });
    	
    	super.onPause();
    }
    
    public void onResume(){
    	super.onResume();
    	
    	queueEvent(new Runnable() {
            @Override
            public void run() {
                mRenderer.handleOnResume();
            }
        });
    }

    ///////////////////////////////////////////////////////////////////////////
    // for text input
	///////////////////////////////////////////////////////////////////////////
    private final static int HANDLER_OPEN_IME_KEYBOARD = 2;
    private final static int HANDLER_CLOSE_IME_KEYBOARD = 3;
    private static Handler handler;
    private static TextInputWraper textInputWraper;
    private TextView mTextField;
    
    public TextView getTextField() {
    	return mTextField;
    }
    
    public void setTextField(TextView view) {
    	mTextField = view;
    	if (null != mTextField && null != textInputWraper) {
    		mTextField.setOnEditorActionListener(textInputWraper);
    		this.requestFocus();
    	}
    }
    
    public static void openIMEKeyboard() {
    	Message msg = new Message();
    	msg.what = HANDLER_OPEN_IME_KEYBOARD;
    	msg.obj = mainView.getContentText();
    	handler.sendMessage(msg);
    	
    }
    
    private String getContentText() {
		return mRenderer.getContentText();
	}

	public static void closeIMEKeyboard() {
    	Message msg = new Message();
    	msg.what = HANDLER_CLOSE_IME_KEYBOARD;
    	handler.sendMessage(msg);
    }
    
    public void insertText(final String text) {
        queueEvent(new Runnable() {
            @Override
            public void run() {
                mRenderer.handleInsertText(text);
            }
        });
    }
    
    public void deleteBackward() {
        queueEvent(new Runnable() {
            @Override
            public void run() {
                mRenderer.handleDeleteBackward();
            }
        });
    }

	///////////////////////////////////////////////////////////////////////////
    // for touch event
    ///////////////////////////////////////////////////////////////////////////

    public boolean onTouchEvent(final MotionEvent event) {
    	// these data are used in ACTION_MOVE and ACTION_CANCEL
    	final int pointerNumber = event.getPointerCount();
    	final int[] ids = new int[pointerNumber];
    	final float[] xs = new float[pointerNumber];
    	final float[] ys = new float[pointerNumber];

    	for (int i = 0; i < pointerNumber; i++) {
            ids[i] = event.getPointerId(i);
            xs[i] = event.getX(i);
            ys[i] = event.getY(i);
        }
        
        switch (event.getAction() & MotionEvent.ACTION_MASK) {
        case MotionEvent.ACTION_POINTER_DOWN:
        	final int idPointerDown = event.getAction() >> MotionEvent.ACTION_POINTER_ID_SHIFT;
            final float xPointerDown = event.getX(idPointerDown);
            final float yPointerDown = event.getY(idPointerDown);

            queueEvent(new Runnable() {
                @Override
                public void run() {
                    mRenderer.handleActionDown(idPointerDown, xPointerDown, yPointerDown);
                }
            });
            break;
            
        case MotionEvent.ACTION_DOWN:
        	// there are only one finger on the screen
        	final int idDown = event.getPointerId(0);
            final float xDown = event.getX(idDown);
            final float yDown = event.getY(idDown);
            
            queueEvent(new Runnable() {
                @Override
                public void run() {
                    mRenderer.handleActionDown(idDown, xDown, yDown);
                }
            });
            break;

        case MotionEvent.ACTION_MOVE:
            queueEvent(new Runnable() {
                @Override
                public void run() {
                    mRenderer.handleActionMove(ids, xs, ys);
                }
            });
            break;

        case MotionEvent.ACTION_POINTER_UP:
        	final int idPointerUp = event.getAction() >> MotionEvent.ACTION_POINTER_ID_SHIFT;
            final float xPointerUp = event.getX(idPointerUp);
            final float yPointerUp = event.getY(idPointerUp);
            
            queueEvent(new Runnable() {
                @Override
                public void run() {
                    mRenderer.handleActionUp(idPointerUp, xPointerUp, yPointerUp);
                }
            });
            break;
            
        case MotionEvent.ACTION_UP:  
        	// there are only one finger on the screen
        	final int idUp = event.getPointerId(0);
            final float xUp = event.getX(idUp);
            final float yUp = event.getY(idUp);
            
            queueEvent(new Runnable() {
                @Override
                public void run() {
                    mRenderer.handleActionUp(idUp, xUp, yUp);
                }
            });
            break;

        case MotionEvent.ACTION_CANCEL:
            queueEvent(new Runnable() {
               @Override
                public void run() {
                    mRenderer.handleActionCancel(ids, xs, ys);
                }
            });
            break;
        }
      
        if (debug){
        	dumpEvent(event);
        }
        return true;
    }
    
 @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
    	final int kc = keyCode;
    	if (keyCode == KeyEvent.KEYCODE_BACK || keyCode == KeyEvent.KEYCODE_MENU) {
    		queueEvent(new Runnable() {
	            @Override
	            public void run() {
	                mRenderer.handleKeyDown(kc);
	            }
    		});
    		return true;
    	}
        return super.onKeyDown(keyCode, event);
    }
    // Show an event in the LogCat view, for debugging
    private void dumpEvent(MotionEvent event) {
       String names[] = { "DOWN" , "UP" , "MOVE" , "CANCEL" , "OUTSIDE" ,
          "POINTER_DOWN" , "POINTER_UP" , "7?" , "8?" , "9?" };
       StringBuilder sb = new StringBuilder();
       int action = event.getAction();
       int actionCode = action & MotionEvent.ACTION_MASK;
       sb.append("event ACTION_" ).append(names[actionCode]);
       if (actionCode == MotionEvent.ACTION_POINTER_DOWN
             || actionCode == MotionEvent.ACTION_POINTER_UP) {
          sb.append("(pid " ).append(
          action >> MotionEvent.ACTION_POINTER_ID_SHIFT);
          sb.append(")" );
       }
       sb.append("[" );
       for (int i = 0; i < event.getPointerCount(); i++) {
          sb.append("#" ).append(i);
          sb.append("(pid " ).append(event.getPointerId(i));
          sb.append(")=" ).append((int) event.getX(i));
          sb.append("," ).append((int) event.getY(i));
          if (i + 1 < event.getPointerCount())
             sb.append(";" );
       }
       sb.append("]" );
       Log.d(TAG, sb.toString());
    }
}
