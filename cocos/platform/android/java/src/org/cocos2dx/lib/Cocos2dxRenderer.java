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

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
public class Cocos2dxRenderer implements GLSurfaceView.Renderer {
    // ===========================================================
    // Constants
    // ===========================================================

    private final static long NANOSECONDSPERSECOND = 1000000000L;
    private final static long NANOSECONDSPERMICROSECOND = 1000000L;

    // The final animation interval which is used in 'onDrawFrame'
    private static long sAnimationInterval = (long) (1.0 / 60 * Cocos2dxRenderer.NANOSECONDSPERSECOND);

    // ===========================================================
    // Fields
    // ===========================================================

    private long mLastTickInNanoSeconds;
    private int mScreenWidth;
    private int mScreenHeight;
    private boolean mNativeInitCompleted = false;

    // ===========================================================
    // Constructors
    // ===========================================================

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    public static void setAnimationInterval(float interval) {
        sAnimationInterval = (long) (interval * Cocos2dxRenderer.NANOSECONDSPERSECOND);
    }

    public void setScreenWidthAndHeight(final int surfaceWidth, final int surfaceHeight) {
        this.mScreenWidth = surfaceWidth;
        this.mScreenHeight = surfaceHeight;
    }

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    @Override
    public void onSurfaceCreated(final GL10 GL10, final EGLConfig EGLConfig) {
        Cocos2dxRenderer.nativeInit(this.mScreenWidth, this.mScreenHeight);
        this.mLastTickInNanoSeconds = System.nanoTime();
        mNativeInitCompleted = true;
    }

    @Override
    public void onSurfaceChanged(final GL10 GL10, final int width, final int height) {
        Cocos2dxRenderer.nativeOnSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(final GL10 gl) {
        /*
         * No need to use algorithm in default(60 FPS) situation,
         * since onDrawFrame() was called by system 60 times per second by default.
         */
        if (Cocos2dxRenderer.sAnimationInterval <= 1.0 / 60 * Cocos2dxRenderer.NANOSECONDSPERSECOND) {
            Cocos2dxRenderer.nativeRender();
        } else {
            final long now = System.nanoTime();
            final long interval = now - this.mLastTickInNanoSeconds;
        
            if (interval < Cocos2dxRenderer.sAnimationInterval) {
                try {
                    Thread.sleep((Cocos2dxRenderer.sAnimationInterval - interval) / Cocos2dxRenderer.NANOSECONDSPERMICROSECOND);
                } catch (final Exception e) {
                }
            }
            /*
             * Render time MUST be counted in, or the FPS will slower than appointed.
            */
            this.mLastTickInNanoSeconds = System.nanoTime();
            Cocos2dxRenderer.nativeRender();
        }
    }

    // ===========================================================
    // Methods
    // ===========================================================

    private static native void nativeTouchesBegin(final int id, final float x, final float y);
    private static native void nativeTouchesEnd(final int id, final float x, final float y);
    private static native void nativeTouchesMove(final int[] ids, final float[] xs, final float[] ys);
    private static native void nativeTouchesCancel(final int[] ids, final float[] xs, final float[] ys);
    private static native boolean nativeKeyEvent(final int keyCode,boolean isPressed);
    private static native void nativeRender();
    private static native void nativeInit(final int width, final int height);
    private static native void nativeOnSurfaceChanged(final int width, final int height);
    private static native void nativeOnPause();
    private static native void nativeOnResume();

    public void handleActionDown(final int id, final float x, final float y) {
        Cocos2dxRenderer.nativeTouchesBegin(id, x, y);
    }

    public void handleActionUp(final int id, final float x, final float y) {
        Cocos2dxRenderer.nativeTouchesEnd(id, x, y);
    }

    public void handleActionCancel(final int[] ids, final float[] xs, final float[] ys) {
        Cocos2dxRenderer.nativeTouchesCancel(ids, xs, ys);
    }

    public void handleActionMove(final int[] ids, final float[] xs, final float[] ys) {
        Cocos2dxRenderer.nativeTouchesMove(ids, xs, ys);
    }

    public void handleKeyDown(final int keyCode) {
        Cocos2dxRenderer.nativeKeyEvent(keyCode, true);
    }

    public void handleKeyUp(final int keyCode) {
        Cocos2dxRenderer.nativeKeyEvent(keyCode, false);
    }

    public void handleOnPause() {
        /**
         * onPause may be invoked before onSurfaceCreated, 
         * and engine will be initialized correctly after
         * onSurfaceCreated is invoked. Can not invoke any
         * native method before onSurfaceCreated is invoked
         */
        if (! mNativeInitCompleted)
            return;

        Cocos2dxHelper.onEnterBackground();
        Cocos2dxRenderer.nativeOnPause();
    }

    public void handleOnResume() {
        Cocos2dxHelper.onEnterForeground();
        Cocos2dxRenderer.nativeOnResume();
    }

    private static native void nativeInsertText(final String text);
    private static native void nativeDeleteBackward();
    private static native String nativeGetContentText();

    public void handleInsertText(final String text) {
        Cocos2dxRenderer.nativeInsertText(text);
    }

    public void handleDeleteBackward() {
        Cocos2dxRenderer.nativeDeleteBackward();
    }

    public String getContentText() {
        return Cocos2dxRenderer.nativeGetContentText();
    }

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================
}
