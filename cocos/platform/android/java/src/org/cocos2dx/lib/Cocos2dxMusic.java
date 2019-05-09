/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
import android.content.res.AssetFileDescriptor;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.util.Log;

import java.io.FileInputStream;

public class Cocos2dxMusic {
    // ===========================================================
    // Constants
    // ===========================================================

    private static final String TAG = Cocos2dxMusic.class.getSimpleName();

    // ===========================================================
    // Fields
    // ===========================================================

    private final Context mContext;
    private MediaPlayer mBackgroundMediaPlayer;
    private float mLeftVolume;
    private float mRightVolume;
    private boolean mPaused; // whether music is paused state.
    private boolean mIsLoop = false;
    private boolean mManualPaused = false; // whether music is paused manually before the program is switched to the background.
    private boolean mIsAudioFocus = true;
    private String mCurrentPath;

    // ===========================================================
    // Constructors
    // ===========================================================

    public Cocos2dxMusic(final Context context) {
        this.mContext = context;

        this.initData();
    }

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    // ===========================================================
    // Methods
    // ===========================================================

    public void preloadBackgroundMusic(final String path) {
        if ((this.mCurrentPath == null) || (!this.mCurrentPath.equals(path))) {
            // preload new background music

            // release old resource and create a new one
            if (this.mBackgroundMediaPlayer != null) {
                this.mBackgroundMediaPlayer.release();
            }

            this.mBackgroundMediaPlayer = this.createMediaPlayer(path);

            // record the path
            this.mCurrentPath = path;
        }
    }

    public void playBackgroundMusic(final String path, final boolean isLoop) {
        if (mCurrentPath == null) {
            // it is the first time to play background music or end() was called
            mBackgroundMediaPlayer = createMediaPlayer(path);
            mCurrentPath = path;
        } else {
            if (!mCurrentPath.equals(path)) {
                // play new background music

                // release old resource and create a new one
                if (mBackgroundMediaPlayer != null) {
                    mBackgroundMediaPlayer.release();
                }
                mBackgroundMediaPlayer = createMediaPlayer(path);

                // record the path
                mCurrentPath = path;
            }
        }

        if (mBackgroundMediaPlayer == null) {
            Log.e(Cocos2dxMusic.TAG, "playBackgroundMusic: background media player is null");
        } else {
            try {
                // if the music is playing or paused, stop it
                if (mPaused) {
                    mBackgroundMediaPlayer.seekTo(0);
                    mBackgroundMediaPlayer.start();
                } else if (mBackgroundMediaPlayer.isPlaying()) {
                    mBackgroundMediaPlayer.seekTo(0);
                } else {
                    mBackgroundMediaPlayer.start();
                }
                mBackgroundMediaPlayer.setLooping(isLoop);
                mPaused = false;
                mIsLoop = isLoop;
            } catch (final Exception e) {
                Log.e(Cocos2dxMusic.TAG, "playBackgroundMusic: error state");
            }
        }
    }

    public void stopBackgroundMusic() {
        if (this.mBackgroundMediaPlayer != null) {
            mBackgroundMediaPlayer.release();
            mBackgroundMediaPlayer = createMediaPlayer(mCurrentPath);
            
            /**
             * should set the state, if not, the following sequence will be error
             * play -> pause -> stop -> resume
             */
            this.mPaused = false;
        }
    }

    public void pauseBackgroundMusic() {
        try {
            if (this.mBackgroundMediaPlayer != null && this.mBackgroundMediaPlayer.isPlaying()) {
                this.mBackgroundMediaPlayer.pause();
                this.mPaused = true;
                this.mManualPaused = true;
            }
        } catch (IllegalStateException e) {
            Log.e(TAG, "pauseBackgroundMusic, IllegalStateException was triggered!");
        }
    }

    public void resumeBackgroundMusic() {
        try {
            if (this.mBackgroundMediaPlayer != null && this.mPaused) {
                this.mBackgroundMediaPlayer.start();
                this.mPaused = false;
                this.mManualPaused = false;
            }
        } catch (IllegalStateException e) {
            Log.e(TAG, "resumeBackgroundMusic, IllegalStateException was triggered!");
        }
    }

    public void rewindBackgroundMusic() {
        if (this.mBackgroundMediaPlayer != null) {
            playBackgroundMusic(mCurrentPath, mIsLoop);
        }
    }

    public boolean willPlayBackgroundMusic() {
        // We will play our own background music, if there isn't already some
        // music active from some other app (eg the user playing their own
        // music).
        AudioManager manager =
            (AudioManager)mContext.getSystemService(Context.AUDIO_SERVICE);
        return !manager.isMusicActive();
    }

    public boolean isBackgroundMusicPlaying() {
        boolean ret = false;
        try {
            if (this.mBackgroundMediaPlayer == null) {
                ret = false;
            } else {
                ret = this.mBackgroundMediaPlayer.isPlaying();
            }
        } catch (IllegalStateException e) {
            Log.e(TAG, "isBackgroundMusicPlaying, IllegalStateException was triggered!");
        }

        return ret;
    }

    public void end() {
        if (this.mBackgroundMediaPlayer != null) {
            this.mBackgroundMediaPlayer.release();
        }

        this.initData();
    }

    public float getBackgroundVolume() {
        if (this.mBackgroundMediaPlayer != null) {
            return (this.mLeftVolume + this.mRightVolume) / 2;
        } else {
            return 0.0f;
        }
    }

    public void setBackgroundVolume(float volume) {
        if (volume < 0.0f) {
            volume = 0.0f;
        }

        if (volume > 1.0f) {
            volume = 1.0f;
        }

        this.mLeftVolume = this.mRightVolume = volume;
        if (this.mBackgroundMediaPlayer != null && mIsAudioFocus) {
            this.mBackgroundMediaPlayer.setVolume(this.mLeftVolume, this.mRightVolume);
        }
    }

    public void onEnterBackground(){
        try {
            if (this.mBackgroundMediaPlayer != null && this.mBackgroundMediaPlayer.isPlaying()) {
                this.mBackgroundMediaPlayer.pause();
                this.mPaused = true;
            }
        } catch (IllegalStateException e) {
            Log.e(TAG, "onEnterBackground, IllegalStateException was triggered!");
        }
    }
    
    public void onEnterForeground(){
        try {
            if (!this.mManualPaused) {
                if (this.mBackgroundMediaPlayer != null && this.mPaused) {
                    this.mBackgroundMediaPlayer.start();
                    this.mPaused = false;
                }
            }
        } catch (IllegalStateException e) {
            Log.e(TAG, "onEnterForeground, IllegalStateException was triggered!");
        }
    }
    
    private void initData() {
        this.mLeftVolume = 0.5f;
        this.mRightVolume = 0.5f;
        this.mBackgroundMediaPlayer = null;
        this.mPaused = false;
        this.mCurrentPath = null;
    }

    /**
     * create MediaPlayer for music
     * 
     * @param path The path relative to assets
     * @return
     */
    private MediaPlayer createMediaPlayer(final String path) {
        MediaPlayer mediaPlayer = new MediaPlayer();

        try {
            if (path.startsWith("/")) {
                final FileInputStream fis = new FileInputStream(path);
                mediaPlayer.setDataSource(fis.getFD());
                fis.close();
            } else {
                if (Cocos2dxHelper.getObbFile() != null && Cocos2dxHelper.getObbFile().getAssetFileDescriptor(path) != null) {
                    final AssetFileDescriptor assetFileDescriptor = Cocos2dxHelper.getObbFile().getAssetFileDescriptor(path);
                    mediaPlayer.setDataSource(assetFileDescriptor.getFileDescriptor(), assetFileDescriptor.getStartOffset(), assetFileDescriptor.getLength());
                } else {
                    final AssetFileDescriptor assetFileDescriptor = this.mContext.getAssets().openFd(path);
                    mediaPlayer.setDataSource(assetFileDescriptor.getFileDescriptor(), assetFileDescriptor.getStartOffset(), assetFileDescriptor.getLength());
                }
            }

            mediaPlayer.prepare();

            mediaPlayer.setVolume(this.mLeftVolume, this.mRightVolume);
        } catch (final Exception e) {
            mediaPlayer = null;
            Log.e(Cocos2dxMusic.TAG, "error: " + e.getMessage(), e);
        }

        return mediaPlayer;
    }

    void setAudioFocus(boolean isFocus) {
        mIsAudioFocus = isFocus;

        if (mBackgroundMediaPlayer != null) {
            float lVolume = mIsAudioFocus ? mLeftVolume : 0.0f;
            float rVolume = mIsAudioFocus ? mRightVolume : 0.0f;
            mBackgroundMediaPlayer.setVolume(lVolume, rVolume);
        }
    }

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================
}
