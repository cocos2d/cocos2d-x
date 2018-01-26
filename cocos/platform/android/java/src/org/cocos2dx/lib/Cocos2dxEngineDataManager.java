/****************************************************************************
 * Copyright (c) 2016 Chukong Technologies Inc.
 * <p/>
 * http://www.cocos2d-x.org
 * <p/>
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * <p/>
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * <p/>
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ****************************************************************************/

package org.cocos2dx.lib;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.util.Log;

import org.cocos2dx.enginedata.EngineDataManager;
import org.cocos2dx.enginedata.IEngineDataManager;

public class Cocos2dxEngineDataManager {
    private static final String TAG = "CCEngineDataManager";
    private static EngineDataManager sManager = new EngineDataManager();
    private static boolean sIsEnabled = true;
    private static boolean sIsInited = false;

    private Cocos2dxEngineDataManager() {

    }

    // Whether to disable Cocos2dxEngineDataManager, invoke it if you don't wanna
    // this optimization. You could invoke `Cocos2dxEngineDataManager.disable` before
    // `super.onCreate` in game's Activity. The following code snippet demonstrates how to disable it.
    /*
    public class AppActivity extends Cocos2dxActivity {
        @Override
        protected void onCreate(Bundle savedInstanceState) {
            Cocos2dxEngineDataManager.disable(); // disable before `super.onCreate`
            super.onCreate(savedInstanceState);
            ...
            ...
        }
    }
     */
    // Currently, it only supports HuaWei mobile phones.
    public static void disable() {
        sIsEnabled = false;
    }

    public static boolean isInited() {
        return sIsInited;
    }

    // Lifecycle functions
    public static boolean init(Context context, final GLSurfaceView glSurfaceView) {
        if (context == null) {
            Log.e(TAG, "Context is null");
            return false;
        }

        if (glSurfaceView == null) {
            Log.e(TAG, "glSurfaceView is null");
            return false;
        }

        final IEngineDataManager.OnSystemCommandListener listener = new IEngineDataManager.OnSystemCommandListener() {

            @Override
            public void onQueryFps(final int[] expectedFps, final int[] realFps) {
                //@note Query FPS should not post it to GL thread since `expectedFps` and `realFps`
                //      need to be filled immediately.
//                glSurfaceView.queueEvent(new Runnable() {
//                    @Override
//                    public void run() {
                        nativeOnQueryFps(expectedFps, realFps);
//                    }
//                });
            }

            @Override
            public void onChangeContinuousFrameLostConfig(final int cycle, final int maxFrameMissed) {
                glSurfaceView.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        nativeOnChangeContinuousFrameLostConfig(cycle, maxFrameMissed);
                    }
                });
            }

            @Override
            public void onChangeLowFpsConfig(final int cycle, final float maxFrameDx) {
                glSurfaceView.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        nativeOnChangeLowFpsConfig(cycle, maxFrameDx);
                    }
                });
            }

            @Override
            public void onChangeExpectedFps(final int fps) {
                glSurfaceView.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        nativeOnChangeExpectedFps(fps);
                    }
                });
            }

            @Override
            public void onChangeSpecialEffectLevel(final int level) {
                glSurfaceView.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        nativeOnChangeSpecialEffectLevel(level);
                    }
                });
            }

            @Override
            public void onChangeMuteEnabled(final boolean enabled) {
                glSurfaceView.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        nativeOnChangeMuteEnabled(enabled);
                    }
                });
            }
        };

        if (sIsEnabled) {
            sIsInited = sManager.init(listener);
        }

        nativeSetSupportOptimization(sIsInited);

        return sIsInited;
    }

    public static void destroy() {
        if (sIsEnabled) {
            sManager.destroy();
        }
    }

    public static void pause() {
        if (sIsEnabled) {
            sManager.pause();
        }
    }

    public static void resume() {
        if (sIsEnabled) {
            sManager.resume();
        }
    }
    //

    public static String getVendorInfo() {
        if (sIsEnabled) {
            return sManager.getVendorInfo();
        }
        return "";
    }

    private static IEngineDataManager.GameStatus convertIntegerToGameStatus(int gameStatus) {
        IEngineDataManager.GameStatus[] values = IEngineDataManager.GameStatus.values();
        for (IEngineDataManager.GameStatus status : values) {
            if (gameStatus == status.ordinal()) {
                return status;
            }
        }

        return IEngineDataManager.GameStatus.INVALID;
    }
    /*
     * @brief Notify game overhead changed
     * @param gameStatus Which situation current game is in
     * @param cpuLevel Current game wastes how much CPU resources, the range is [0,10]
     * @param gpuLevel Current game wastes how much GPU resources, the range is [0,10]
     */
    public static void notifyGameStatus(int gameStatus, int cpuLevel, int gpuLevel) {
        if (!sIsEnabled) {
            nativeSetSupportOptimization(false);
            return;
        }

        IEngineDataManager.GameStatus status = convertIntegerToGameStatus(gameStatus);
        if (status == IEngineDataManager.GameStatus.INVALID) {
            Log.e(TAG, "Invalid game status: " + gameStatus);
            return;
        }
        sManager.notifyGameStatus(status, cpuLevel, gpuLevel);
    }

    /*
     * @brief Notify an event that some frames are lost.
     * @param cycle The statistic cycle of 'Continuous Frame Lost Event', value is in millisecond, default value is 5000ms
     * @param continuousFrameLostThreshold The threshold of 'Continuous Frame Lost', default value is 3,
     *                       if there're 3 times of frame lost in 100ms, then mark a
     *                       'continuous frame lost', it's set by system.
     * @times How many times of `Continuous Frame Lost` event happens in a `cycle'
     */
    public static void notifyContinuousFrameLost(int cycle, int continuousFrameLostThreshold, int times) {
        if (!sIsEnabled) {
            nativeSetSupportOptimization(false);
            return;
        }

        sManager.notifyContinuousFrameLost(cycle, continuousFrameLostThreshold, times);
    }

    /*
     * @brief Notify an event that game FPS is too low
     * @param cycle The statistic cycle of 'FPS Too Low Event', value is in millisecond, default value is 1000ms
     * @param lowFpsThreshold The threshold of fps rate to indicate low fps, 'fps rate' = 'real fps' / 'excepted fps',
      *                  default value is 0.3. if 'fps rate' is larger than 0.3, mark a 'low fps', it's set by system.
     *
     * @param lostFrameCount How many frames are lost in a 'cycle'
     */
    public static void notifyLowFps(int cycle, float lowFpsThreshold, int lostFrameCount) {
        if (!sIsEnabled) {
            nativeSetSupportOptimization(false);
            return;
        }

        sManager.notifyLowFps(cycle, lowFpsThreshold, lostFrameCount);
    }

    public static void notifyFpsChanged(float oldFps, float newFps) {
        if (!sIsEnabled) {
            nativeSetSupportOptimization(false);
            return;
        }

        sManager.notifyFpsChanged(oldFps, newFps);
    }

    // Native methods
    private native static void nativeSetSupportOptimization(boolean isSupported);
    private native static void nativeOnQueryFps(/*out*/ int[] expectedFps, /*out*/ int[] realFps);
    private native static void nativeOnChangeContinuousFrameLostConfig(int cycle, int continuousFrameLostThreshold);
    private native static void nativeOnChangeLowFpsConfig(int cycle, float lowFpsThreshold);
    private native static void nativeOnChangeExpectedFps(int fps);
    private native static void nativeOnChangeSpecialEffectLevel(int level);
    private native static void nativeOnChangeMuteEnabled(boolean enabled);
}
