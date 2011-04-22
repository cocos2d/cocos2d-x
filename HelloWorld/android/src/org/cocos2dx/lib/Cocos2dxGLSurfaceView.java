package org.cocos2dx.lib;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.inputmethod.CompletionInfo;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.ExtractedText;
import android.view.inputmethod.ExtractedTextRequest;
import android.view.inputmethod.InputConnection;
import android.view.inputmethod.InputMethodManager;

class Cocos2dxInputConnection implements InputConnection {

	@Override
	public boolean beginBatchEdit() {
		return false;
	}

	@Override
	public boolean clearMetaKeyStates(int states) {
		return false;
	}

	@Override
	public boolean commitCompletion(CompletionInfo text) {
		return false;
	}

	@Override
	public boolean commitText(CharSequence text, int newCursorPosition) {
		if (null != mView) {
			final String insertText = text.toString();
			mView.insertText(insertText);
		}
        return false;
	}

	@Override
	public boolean deleteSurroundingText(int leftLength, int rightLength) {
		return false;
	}

	@Override
	public boolean endBatchEdit() {
		return false;
	}

	@Override
	public boolean finishComposingText() {
		return false;
	}

	@Override
	public int getCursorCapsMode(int reqModes) {
		return 0;
	}

	@Override
	public ExtractedText getExtractedText(ExtractedTextRequest request,
			int flags) {
		return null;
	}

	@Override
	public CharSequence getTextAfterCursor(int n, int flags) {
		return null;
	}

	@Override
	public CharSequence getTextBeforeCursor(int n, int flags) {
		return null;
	}

	@Override
	public boolean performContextMenuAction(int id) {
		return false;
	}

	@Override
	public boolean performEditorAction(int editorAction) {
		if (null != mView) {
			final String insertText = "\n";
			mView.insertText(insertText);
		}
		return false;
	}

	@Override
	public boolean performPrivateCommand(String action, Bundle data) {
		return false;
	}

	@Override
	public boolean reportFullscreenMode(boolean enabled) {
		return false;
	}

	@Override
	public boolean sendKeyEvent(KeyEvent event) {
		if (null != mView) {
			switch (event.getKeyCode()) {
			
			case KeyEvent.KEYCODE_DEL:
				mView.deleteBackward();
				break;
			}
		}
		return false;
	}

	@Override
	public boolean setComposingText(CharSequence text, int newCursorPosition) {
		return false;
	}

	@Override
	public boolean setSelection(int start, int end) {
		return false;
	}
	
	public void setGLSurfaceView(Cocos2dxGLSurfaceView view) {
		mView = view;
	}
	
    private Cocos2dxGLSurfaceView mView;
}

public class Cocos2dxGLSurfaceView extends GLSurfaceView {
    
    static private Cocos2dxGLSurfaceView mainView;

    private static final String TAG = Cocos2dxGLSurfaceView.class.getCanonicalName();
    private Cocos2dxRenderer mRenderer;
    private final boolean debug = false;

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

    private void initView() {
        mRenderer = new Cocos2dxRenderer();
        setFocusableInTouchMode(true);
        setRenderer(mRenderer);
        mainView = this;
    }

    ///////////////////////////////////////////////////////////////////////////
    // for text input
	///////////////////////////////////////////////////////////////////////////

    public static void openIMEKeyboard() {
    	if (null == mainView) {
    		return;
    	}
    	InputMethodManager imm = (InputMethodManager)mainView.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
        if (imm == null) {
        	return;
        }
        imm.showSoftInput(mainView, InputMethodManager.SHOW_IMPLICIT);
    }
    
    public static void closeIMEKeyboard() {
    	if (null != mainView) {
        	Log.d("Cocos2dxGLSurfaceView", "closeIMEKeyboard");
    	}
    	InputMethodManager imm = (InputMethodManager)mainView.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
        if (imm == null) {
        	return;
        }
        imm.hideSoftInputFromWindow(mainView.getWindowToken(), 0);
    }
	
    @Override 
    public boolean onCheckIsTextEditor() {
    	if (null == mainView)
    	{
    		return false;
    	}
        return true;
    }
    
    private Cocos2dxInputConnection ic;
    @Override 
    public InputConnection onCreateInputConnection(EditorInfo outAttrs) {
        if (onCheckIsTextEditor()) {

            outAttrs.inputType = EditorInfo.TYPE_CLASS_TEXT;
            outAttrs.imeOptions = EditorInfo.IME_NULL;
            outAttrs.initialSelStart = -1;
            outAttrs.initialSelEnd = -1;
            outAttrs.initialCapsMode = 0;

        	if (null == ic)
        	{
        		ic = new Cocos2dxInputConnection();
        		ic.setGLSurfaceView(this);
        	}
            return ic;
        }
        return null;
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
