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
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.inputmethod.InputMethodManager;

import java.util.ArrayList;
import java.util.LinkedList;

@SuppressWarnings("unused")
public class Cocos2dxGLSurfaceView extends GLSurfaceView {
    // ===========================================================
    // Constants
    // ===========================================================

    private static final String TAG = Cocos2dxGLSurfaceView.class.getSimpleName();

    private final static int HANDLER_OPEN_IME_KEYBOARD = 2;
    private final static int HANDLER_CLOSE_IME_KEYBOARD = 3;

    // ===========================================================
    // Fields
    // ===========================================================

    // TODO Static handler -> Potential leak!
    private static Handler sHandler;

    private static Cocos2dxGLSurfaceView mCocos2dxGLSurfaceView;
    private static Cocos2dxTextInputWraper sCocos2dxTextInputWraper;

    private Cocos2dxRenderer mCocos2dxRenderer;
    private Cocos2dxEditText mCocos2dxEditText;

    private class TouchInfo {
        public int id;
        public float x;
        public float y;
    }
    private class TouchEvent {
        public int action = Integer.MAX_VALUE;
        public long timestamp = 0;

        private ArrayList<TouchInfo> mInfo = new ArrayList<>();
        private int mTop;

        // this function should called in main thread
        public int addTouchInfo(int id, float x, float y) {
            if (mTop == mInfo.size()) {
                mInfo.add(new TouchInfo());
            }
            // get top
            TouchInfo info = mInfo.get(mTop);
            mTop = mTop + 1;
            info.id = id;
            info.x = x;
            info.y = y;

            return mTop;
        }

        // this function should called in GL thread
        private void sendTouchEvent() {
            final int num = mTop;
            // Log.d("cocos2d-x", "sendTouchEvent[ action: " + action + ", num: " + num + ", delay: " + (System.currentTimeMillis() - timestamp) + "]");
            if (0 >= num && action != Integer.MAX_VALUE) {
                Log.w("cocos2d-x", "Cocos2dxGLSurfaceView.TouchEvent.sendTouchEvent called but no info in it.");
                return;
            }
            // convert touch info to native format
            final int[] ids = new int[num];
            final float[] xs = new float[num];
            final float[] ys = new float[num];
            for (int i = 0; i < num; i++) {
                TouchInfo info = mInfo.get(i);
                ids[i] = info.id;
                xs[i] = info.x;
                ys[i] = info.y;
            }
            // send event
            // MotionEvent.ACTION_POINTER_DOWN has been covert to ACTION_DOWN in onTouchEvent
            if (action == MotionEvent.ACTION_POINTER_UP) {
                action = MotionEvent.ACTION_UP;
            }
            Cocos2dxGLSurfaceView.this.mCocos2dxRenderer.handleTouchEvent(action, ids, xs, ys);
            // clear touch info
            mTop = 0;
            action = Integer.MAX_VALUE;
        }
    }
    private final LinkedList<TouchEvent> mProductQueue = new LinkedList<>();
    private final LinkedList<TouchEvent> mConsumerQueue = new LinkedList<>();

    // ===========================================================
    // Constructors
    // ===========================================================

    public Cocos2dxGLSurfaceView(final Context context) {
        super(context);

        this.initView();
    }

    public Cocos2dxGLSurfaceView(final Context context, final AttributeSet attrs) {
        super(context, attrs);
        
        this.initView();
    }

    protected void initView() {
        this.setEGLContextClientVersion(2);
        this.setFocusableInTouchMode(true);

        Cocos2dxGLSurfaceView.mCocos2dxGLSurfaceView = this;
        Cocos2dxGLSurfaceView.sCocos2dxTextInputWraper = new Cocos2dxTextInputWraper(this);

        Cocos2dxGLSurfaceView.sHandler = new Handler() {
            @Override
            public void handleMessage(final Message msg) {
                switch (msg.what) {
                    case HANDLER_OPEN_IME_KEYBOARD:
                        if (null != Cocos2dxGLSurfaceView.this.mCocos2dxEditText && Cocos2dxGLSurfaceView.this.mCocos2dxEditText.requestFocus()) {
                            Cocos2dxGLSurfaceView.this.mCocos2dxEditText.removeTextChangedListener(Cocos2dxGLSurfaceView.sCocos2dxTextInputWraper);
                            Cocos2dxGLSurfaceView.this.mCocos2dxEditText.setText("");
                            final String text = (String) msg.obj;
                            Cocos2dxGLSurfaceView.this.mCocos2dxEditText.append(text);
                            Cocos2dxGLSurfaceView.sCocos2dxTextInputWraper.setOriginText(text);
                            Cocos2dxGLSurfaceView.this.mCocos2dxEditText.addTextChangedListener(Cocos2dxGLSurfaceView.sCocos2dxTextInputWraper);
                            final InputMethodManager imm = (InputMethodManager) Cocos2dxGLSurfaceView.mCocos2dxGLSurfaceView.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
                            imm.showSoftInput(Cocos2dxGLSurfaceView.this.mCocos2dxEditText, 0);
                            Log.d("GLSurfaceView", "showSoftInput");
                        }
                        break;

                    case HANDLER_CLOSE_IME_KEYBOARD:
                        if (null != Cocos2dxGLSurfaceView.this.mCocos2dxEditText) {
                            Cocos2dxGLSurfaceView.this.mCocos2dxEditText.removeTextChangedListener(Cocos2dxGLSurfaceView.sCocos2dxTextInputWraper);
                            final InputMethodManager imm = (InputMethodManager) Cocos2dxGLSurfaceView.mCocos2dxGLSurfaceView.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
                            imm.hideSoftInputFromWindow(Cocos2dxGLSurfaceView.this.mCocos2dxEditText.getWindowToken(), 0);
                            Cocos2dxGLSurfaceView.this.requestFocus();
                            Log.d("GLSurfaceView", "HideSoftInput");
                        }
                        break;
                }
            }
        };
    }

    // ===========================================================
    // Getter & Setter
    // ===========================================================


       public static Cocos2dxGLSurfaceView getInstance() {
       return mCocos2dxGLSurfaceView;
       }

       public static void queueAccelerometer(final float x, final float y, final float z, final long timestamp) {   
       mCocos2dxGLSurfaceView.queueEvent(new Runnable() {
        @Override
            public void run() {
                Cocos2dxAccelerometer.onSensorChanged(x, y, z, timestamp);
        }
        });
    }

    public void setCocos2dxRenderer(final Cocos2dxRenderer renderer) {
        this.mCocos2dxRenderer = renderer;
        this.setRenderer(this.mCocos2dxRenderer);
    }

    private String getContentText() {
        return this.mCocos2dxRenderer.getContentText();
    }

    public Cocos2dxEditText getCocos2dxEditText() {
        return this.mCocos2dxEditText;
    }

    public void setCocos2dxEditText(final Cocos2dxEditText pCocos2dxEditText) {
        this.mCocos2dxEditText = pCocos2dxEditText;
        if (null != this.mCocos2dxEditText && null != Cocos2dxGLSurfaceView.sCocos2dxTextInputWraper) {
            this.mCocos2dxEditText.setOnEditorActionListener(Cocos2dxGLSurfaceView.sCocos2dxTextInputWraper);
            this.mCocos2dxEditText.setCocos2dxGLSurfaceView(this);
            this.requestFocus();
        }
    }

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    @Override
    public void onResume() {
        super.onResume();
        this.setRenderMode(RENDERMODE_CONTINUOUSLY);
        this.queueEvent(new Runnable() {
            @Override
            public void run() {
                Cocos2dxGLSurfaceView.this.mCocos2dxRenderer.handleOnResume();
            }
        });
    }

    @Override
    public void onPause() {
        this.queueEvent(new Runnable() {
            @Override
            public void run() {
                Cocos2dxGLSurfaceView.this.mCocos2dxRenderer.handleOnPause();
            }
        });
        this.setRenderMode(RENDERMODE_WHEN_DIRTY);
        //super.onPause();
    }

    private void postTouchEventProcessRunable() {
        this.queueEvent(new Runnable() {
            @Override
            public void run() {
                TouchEvent event;
                synchronized (mConsumerQueue) {
                    event = mConsumerQueue.pollFirst();
                    if (event == null) {
                        Log.w("cocos2d-x", "Cocos2dxGLSurfaceView.onTouchEvent post an event GL thread, but missed.");
                    } else if (0 == mConsumerQueue.size() &&    // no more event
                            (event.action == MotionEvent.ACTION_DOWN || // action down/pointer up event need buffer
                                    event.action == MotionEvent.ACTION_POINTER_UP)) {
                        // if the time interval less than designed delay time, push event back
                        if (16 > (System.currentTimeMillis() - event.timestamp)) {
                            mConsumerQueue.offerFirst(event);
                            event = null;
                            mCocos2dxGLSurfaceView.postTouchEventProcessRunable();
                        }
                    }
                }
                if (null == event) {
                    return;
                }
                event.sendTouchEvent();
                synchronized (mProductQueue) {
                    mProductQueue.offerLast(event);
                }
            }
        });
    }

    @Override
    public boolean onTouchEvent(@SuppressWarnings("NullableProblems") final MotionEvent pMotionEvent) {
        int action = pMotionEvent.getAction() & MotionEvent.ACTION_MASK;
        // Log.d("cocos2d-x", "Cocos2dxGLSurfaceView.onTouchEvent: " + action);

        // treat ACTION_POINTER_DOWN as ACTION_DOWN
        if (action == MotionEvent.ACTION_POINTER_DOWN) {
            action = MotionEvent.ACTION_DOWN;
        }

        boolean isActionUp = false;
        // treat ACTION_UP as ACTION_POINTER_UP
        if (action == MotionEvent.ACTION_UP) {
            action = MotionEvent.ACTION_POINTER_UP;
            isActionUp = true;
        }

        TouchEvent event = null;
        // if event is down/pointer up/up, try to merge it to last event
        if (action == MotionEvent.ACTION_DOWN || action == MotionEvent.ACTION_POINTER_UP) {
            // try get last event in consumer queue
            synchronized (mConsumerQueue) {
                event = mConsumerQueue.peekLast();
                if (null != event && action == event.action) {
                    // the last event same as current event, merge them
                    int i = pMotionEvent.getAction() >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
                    event.addTouchInfo(pMotionEvent.getPointerId(i), pMotionEvent.getX(i), pMotionEvent.getY(i));
                    if (isActionUp) {
                        event.action = MotionEvent.ACTION_UP;
                    }
                } else {
                    event = null;
                }
            }
        }

        // if the current event has been merged in to last one, return immediately
        if (null != event){
            return true;
        }

        // get empty TouchEvent from product queue
        synchronized (mProductQueue) {
            event = mProductQueue.pollFirst();
        }
        // if product queue empty, create a new instance
        if (null == event) {
            event = new TouchEvent();
        }

        // fill touch event with data
        event.action = action;
        event.timestamp = System.currentTimeMillis();
        if (action == MotionEvent.ACTION_MOVE || action == MotionEvent.ACTION_CANCEL) {
            int pointerNumber = pMotionEvent.getPointerCount();
            for (int i = 0; i < pointerNumber; i++) {
                event.addTouchInfo(pMotionEvent.getPointerId(i), pMotionEvent.getX(i), pMotionEvent.getY(i));
            }
        } else {
            // ACTION_DOWN, ACTION_POINTER_UP, ACTION_UP
            int i = pMotionEvent.getAction() >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
            event.addTouchInfo(pMotionEvent.getPointerId(i), pMotionEvent.getX(i), pMotionEvent.getY(i));
            if (isActionUp) {
                event.action = MotionEvent.ACTION_UP;
            }
        }

        // add event to consumer queue
        synchronized (mConsumerQueue) {
            mConsumerQueue.offerLast(event);
        }

        // post event
        postTouchEventProcessRunable();

        /*
        if (BuildConfig.DEBUG) {
            Cocos2dxGLSurfaceView.dumpMotionEvent(pMotionEvent);
        }
        */
        return true;
    }

    /*
     * This function is called before Cocos2dxRenderer.nativeInit(), so the
     * width and height is correct.
     */
    @Override
    protected void onSizeChanged(final int pNewSurfaceWidth, final int pNewSurfaceHeight, final int pOldSurfaceWidth, final int pOldSurfaceHeight) {
        if(!this.isInEditMode()) {
            this.mCocos2dxRenderer.setScreenWidthAndHeight(pNewSurfaceWidth, pNewSurfaceHeight);
        }
    }

    @Override
    public boolean onKeyDown(final int pKeyCode, @SuppressWarnings("NullableProblems") final KeyEvent pKeyEvent) {
        switch (pKeyCode) {
            case KeyEvent.KEYCODE_BACK:
                Cocos2dxVideoHelper.mVideoHandler.sendEmptyMessage(Cocos2dxVideoHelper.KeyEventBack);
            case KeyEvent.KEYCODE_MENU:
            case KeyEvent.KEYCODE_DPAD_LEFT:
            case KeyEvent.KEYCODE_DPAD_RIGHT:
            case KeyEvent.KEYCODE_DPAD_UP:
            case KeyEvent.KEYCODE_DPAD_DOWN:
            case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE:
            case KeyEvent.KEYCODE_DPAD_CENTER:
                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        Cocos2dxGLSurfaceView.this.mCocos2dxRenderer.handleKeyDown(pKeyCode);
                    }
                });
                return true;
            default:
                return super.onKeyDown(pKeyCode, pKeyEvent);
        }
    }

    @Override
    public boolean onKeyUp(final int keyCode, KeyEvent event) {
        switch (keyCode) {
            case KeyEvent.KEYCODE_BACK:
            case KeyEvent.KEYCODE_MENU:
            case KeyEvent.KEYCODE_DPAD_LEFT:
            case KeyEvent.KEYCODE_DPAD_RIGHT:
            case KeyEvent.KEYCODE_DPAD_UP:
            case KeyEvent.KEYCODE_DPAD_DOWN:
            case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE:
            case KeyEvent.KEYCODE_DPAD_CENTER:
                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        Cocos2dxGLSurfaceView.this.mCocos2dxRenderer.handleKeyUp(keyCode);
                    }
                });
                return true;
            default:
                return super.onKeyUp(keyCode, event);
        }
    }

    // ===========================================================
    // Methods
    // ===========================================================

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================

    public static void openIMEKeyboard() {
        final Message msg = new Message();
        msg.what = Cocos2dxGLSurfaceView.HANDLER_OPEN_IME_KEYBOARD;
        msg.obj = Cocos2dxGLSurfaceView.mCocos2dxGLSurfaceView.getContentText();
        Cocos2dxGLSurfaceView.sHandler.sendMessage(msg);
    }

    public static void closeIMEKeyboard() {
        final Message msg = new Message();
        msg.what = Cocos2dxGLSurfaceView.HANDLER_CLOSE_IME_KEYBOARD;
        Cocos2dxGLSurfaceView.sHandler.sendMessage(msg);
    }

    public void insertText(final String pText) {
        this.queueEvent(new Runnable() {
            @Override
            public void run() {
                Cocos2dxGLSurfaceView.this.mCocos2dxRenderer.handleInsertText(pText);
            }
        });
    }

    public void deleteBackward() {
        this.queueEvent(new Runnable() {
            @Override
            public void run() {
                Cocos2dxGLSurfaceView.this.mCocos2dxRenderer.handleDeleteBackward();
            }
        });
    }

    private static void dumpMotionEvent(final MotionEvent event) {
        final String names[] = { "DOWN", "UP", "MOVE", "CANCEL", "OUTSIDE", "POINTER_DOWN", "POINTER_UP", "7?", "8?", "9?" };
        final StringBuilder sb = new StringBuilder();
        final int action = event.getAction();
        final int actionCode = action & MotionEvent.ACTION_MASK;
        sb.append("event ACTION_").append(names[actionCode]);
        if (actionCode == MotionEvent.ACTION_POINTER_DOWN || actionCode == MotionEvent.ACTION_POINTER_UP) {
            sb.append("(pid ").append(action >> MotionEvent.ACTION_POINTER_INDEX_SHIFT);
            sb.append(")");
        }
        sb.append("[");
        for (int i = 0; i < event.getPointerCount(); i++) {
            sb.append("#").append(i);
            sb.append("(pid ").append(event.getPointerId(i));
            sb.append(")=").append((int) event.getX(i));
            sb.append(",").append((int) event.getY(i));
            if (i + 1 < event.getPointerCount()) {
                sb.append(";");
            }
        }
        sb.append("]");
        Log.d(Cocos2dxGLSurfaceView.TAG, sb.toString());
    }
}
