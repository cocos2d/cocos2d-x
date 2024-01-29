/****************************************************************************
 * Copyright (c) 2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 *
 * http://www.cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
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
import android.media.AudioManager;
import android.util.Log;

class Cocos2dxAudioFocusManager {

    private final static String TAG = "AudioFocusManager";
    // Audio focus values synchronized with which in cocos/platform/android/javaactivity-android.cpp
    private final static int AUDIOFOCUS_GAIN = 0;
    private final static int AUDIOFOCUS_LOST = 1;
    private final static int AUDIOFOCUS_LOST_TRANSIENT = 2;
    private final static int AUDIOFOCUS_LOST_TRANSIENT_CAN_DUCK = 3;

    private static AudioManager.OnAudioFocusChangeListener sAfChangeListener =
            new AudioManager.OnAudioFocusChangeListener() {
                public void onAudioFocusChange(int focusChange) {

                    Log.d(TAG, "onAudioFocusChange: " + focusChange + ", thread: " + Thread.currentThread().getName());

                    if (focusChange == AudioManager.AUDIOFOCUS_LOSS) {
                        // Permanent loss of audio focus
                        // Pause playback immediately
                        Log.d(TAG, "Pause music by AUDIOFOCUS_LOSS");
                        Cocos2dxHelper.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {
                                nativeOnAudioFocusChange(AUDIOFOCUS_LOST);
                                Cocos2dxHelper.setAudioFocus(false);
                            }
                        });

                    } else if (focusChange == AudioManager.AUDIOFOCUS_LOSS_TRANSIENT) {
                        // Pause playback
                        Log.d(TAG, "Pause music by AUDIOFOCUS_LOSS_TRANSILENT");
                        Cocos2dxHelper.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {
                                nativeOnAudioFocusChange(AUDIOFOCUS_LOST_TRANSIENT);
                                Cocos2dxHelper.setAudioFocus(false);
                            }
                        });
                    } else if (focusChange == AudioManager.AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK) {
                        // Lower the volume, keep playing
                        Log.d(TAG, "Lower the volume, keep playing by AUDIOFOCUS_LOSS_TRANSILENT_CAN_DUCK");
                        Cocos2dxHelper.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {
                                nativeOnAudioFocusChange(AUDIOFOCUS_LOST_TRANSIENT_CAN_DUCK);
                                Cocos2dxHelper.setAudioFocus(false);
                            }
                        });
                    } else if (focusChange == AudioManager.AUDIOFOCUS_GAIN) {
                        // Your app has been granted audio focus again
                        // Raise volume to normal, restart playback if necessary
                        Log.d(TAG, "Resume music by AUDIOFOCUS_GAIN");
                        Cocos2dxHelper.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {
                                nativeOnAudioFocusChange(AUDIOFOCUS_GAIN);
                                Cocos2dxHelper.setAudioFocus(true);
                            }
                        });
                    }
                }
            };

    static boolean registerAudioFocusListener(Context context) {
        AudioManager am = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);

        // Request audio focus for playback
        int result = am.requestAudioFocus(sAfChangeListener,
                // Use the music stream.
                AudioManager.STREAM_MUSIC,
                // Request permanent focus.
                AudioManager.AUDIOFOCUS_GAIN);

        if (result == AudioManager.AUDIOFOCUS_REQUEST_GRANTED) {
            Log.d(TAG, "requestAudioFocus succeed");
            return true;
        }

        Log.e(TAG, "requestAudioFocus failed!");
        return false;
    }

    static void unregisterAudioFocusListener(Context context) {
        AudioManager am = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
        int result = am.abandonAudioFocus(sAfChangeListener);
        if (result == AudioManager.AUDIOFOCUS_REQUEST_GRANTED) {
            Log.d(TAG, "abandonAudioFocus succeed!");
        } else {
            Log.e(TAG, "abandonAudioFocus failed!");
        }

        Cocos2dxHelper.runOnGLThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxHelper.setAudioFocus(true);
                nativeOnAudioFocusChange(AUDIOFOCUS_GAIN);
            }
        });
    }

    private static native void nativeOnAudioFocusChange(int focusChange);
}
