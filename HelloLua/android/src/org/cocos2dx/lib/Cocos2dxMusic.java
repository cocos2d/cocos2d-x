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
import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.util.Log;

/**
 * 
 * This class is used for controlling background music
 *
 */
public class Cocos2dxMusic {
	
	private static final String TAG = "Cocos2dxMusic";
	private float mLeftVolume;
	private float mRightVolume;
	private Context mContext;
	private MediaPlayer mBackgroundMediaPlayer;
	private boolean mIsPaused;
	private String mCurrentPath;
	
	public Cocos2dxMusic(Context context){
		this.mContext = context;
		initData();
	}
	
	public void preloadBackgroundMusic(String path){
		if ((mCurrentPath == null) || (! mCurrentPath.equals(path))){
			// preload new background music
			
			// release old resource and create a new one
			if (mBackgroundMediaPlayer != null){
				mBackgroundMediaPlayer.release();				
			}				

			mBackgroundMediaPlayer = createMediaplayerFromAssets(path);
			
			// record the path
			mCurrentPath = path;
		}
	}
	
	public void playBackgroundMusic(String path, boolean isLoop){
		if (mCurrentPath == null){
			// it is the first time to play background music
			// or end() was called
			mBackgroundMediaPlayer = createMediaplayerFromAssets(path);	
			mCurrentPath = path;
		} 
		else {
			if (! mCurrentPath.equals(path)){
				// play new background music
				
				// release old resource and create a new one
				if (mBackgroundMediaPlayer != null){
					mBackgroundMediaPlayer.release();				
				}				
				mBackgroundMediaPlayer = createMediaplayerFromAssets(path);
				
				// record the path
				mCurrentPath = path;
			}
		}
		
		if (mBackgroundMediaPlayer == null){
			Log.e(TAG, "playBackgroundMusic: background media player is null");
		} else {		
			// if the music is playing or paused, stop it
			mBackgroundMediaPlayer.stop();			
			
			mBackgroundMediaPlayer.setLooping(isLoop);
			
			try {
				mBackgroundMediaPlayer.prepare();
				mBackgroundMediaPlayer.seekTo(0);
				mBackgroundMediaPlayer.start();
				
				this.mIsPaused = false;
			} catch (Exception e){
				Log.e(TAG, "playBackgroundMusic: error state");
			}			
		}
	}
	
	public void stopBackgroundMusic(){
		if (mBackgroundMediaPlayer != null){
			mBackgroundMediaPlayer.stop();
			
			// should set the state, if not , the following sequence will be error
			// play -> pause -> stop -> resume
			this.mIsPaused = false;
		}
	}
	
	public void pauseBackgroundMusic(){		
		if (mBackgroundMediaPlayer != null && mBackgroundMediaPlayer.isPlaying()){
			mBackgroundMediaPlayer.pause();
			this.mIsPaused = true;
		}
	}
	
	public void resumeBackgroundMusic(){
		if (mBackgroundMediaPlayer != null && this.mIsPaused){
			mBackgroundMediaPlayer.start();
			this.mIsPaused = false;
		}
	}
	
	public void rewindBackgroundMusic(){		
		if (mBackgroundMediaPlayer != null){
			mBackgroundMediaPlayer.stop();			
			
			try {
				mBackgroundMediaPlayer.prepare();
				mBackgroundMediaPlayer.seekTo(0);
				mBackgroundMediaPlayer.start();
				
				this.mIsPaused = false;
			} catch (Exception e){
				Log.e(TAG, "rewindBackgroundMusic: error state");
			}			
		}
	}
	
	public boolean isBackgroundMusicPlaying(){
		boolean ret = false;
		
		if (mBackgroundMediaPlayer == null){
			ret = false;
		} else {
			ret = mBackgroundMediaPlayer.isPlaying();
		}
		
		return ret;
	}
	
	public void end(){
		if (mBackgroundMediaPlayer != null){
			mBackgroundMediaPlayer.release();
		}

		initData();
	}
	
	public float getBackgroundVolume(){
		if (this.mBackgroundMediaPlayer != null){
			return (this.mLeftVolume + this.mRightVolume) / 2;
		} else {
			return 0.0f;
		}
	}
	
	public void setBackgroundVolume(float volume){
		if (volume < 0.0f){
			volume = 0.0f;
		}
		
		if (volume > 1.0f){
			volume = 1.0f;
		}
		
	    this.mLeftVolume = this.mRightVolume = volume;
		if (this.mBackgroundMediaPlayer != null){
			this.mBackgroundMediaPlayer.setVolume(this.mLeftVolume, this.mRightVolume);
		}
	}
	
	private void initData(){
		mLeftVolume =0.5f;
		mRightVolume = 0.5f;
		mBackgroundMediaPlayer = null;
		mIsPaused = false;
		mCurrentPath = null;
	}
	
	/**
	 * create mediaplayer for music
	 * @param path the path relative to assets
	 * @return 
	 */
	private MediaPlayer createMediaplayerFromAssets(String path){
		MediaPlayer mediaPlayer = null;
		
		try{			
			AssetFileDescriptor assetFileDescritor = mContext.getAssets().openFd(path);
			
			mediaPlayer = new MediaPlayer();
	        mediaPlayer.setDataSource(assetFileDescritor.getFileDescriptor(), 
	        		assetFileDescritor.getStartOffset(), assetFileDescritor.getLength());
	        mediaPlayer.prepare();
	        
	        mediaPlayer.setVolume(mLeftVolume, mRightVolume);
		}catch (Exception e) {
			mediaPlayer = null;
            Log.e(TAG, "error: " + e.getMessage(), e);
        }
		
        return mediaPlayer;
	}
}
