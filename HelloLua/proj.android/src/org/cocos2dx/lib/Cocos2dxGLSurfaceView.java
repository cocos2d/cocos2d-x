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
        initView();
    }

    public Cocos2dxGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    protected void initView() {
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
    private Cocos2dxEditText mTextField;
    
    public TextView getTextField() {
    	return mTextField;
    }
    
    public void setTextField(Cocos2dxEditText view) {
    	mTextField = view;
    	if (null != mTextField && null != textInputWraper) {
    		mTextField.setOnEditorActionListener(textInputWraper);
    		mTextField.setMainView(this);
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
        	final int indexPointerDown = event.getAction() >> MotionEvent.ACTION_POINTER_ID_SHIFT;
        	final int idPointerDown = event.getPointerId(indexPointerDown);
            final float xPointerDown = event.getX(indexPointerDown);
            final float yPointerDown = event.getY(indexPointerDown);

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
            final float xDown = xs[0];
            final float yDown = ys[0];
            
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
        	final int indexPointUp = event.getAction() >> MotionEvent.ACTION_POINTER_ID_SHIFT;
        	final int idPointerUp = event.getPointerId(indexPointUp);
            final float xPointerUp = event.getX(indexPointUp);
            final float yPointerUp = event.getY(indexPointUp);
            
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
            final float xUp = xs[0];
            final float yUp = ys[0];
            
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
    
    /*
     * This function is called before Cocos2dxRenderer.nativeInit(), so the width and height is correct.
     */
    protected void onSizeChanged(int w, int h, int oldw, int oldh){
    	this.mRenderer.setScreenWidthAndHeight(w, h);
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
