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
	
	public Cocos2dxMusic(Context context){
		this.mContext = context;
		initData();
	}
	
	public void playBackgroundMusic(String path, boolean isLoop){
		if (mBackgroundMediaPlayer == null){
			mBackgroundMediaPlayer = createMediaplayerFromAssets(path);
		}
		
		if (mBackgroundMediaPlayer == null){
			Log.e(TAG, "playBackgroundMusic: background media player is null");
		} else{		
			// if the music is playing or paused, stop it
			mBackgroundMediaPlayer.stop();
			
			mBackgroundMediaPlayer.setLooping(isLoop);
			
			try {
				mBackgroundMediaPlayer.prepare();
				mBackgroundMediaPlayer.start();
			} catch (Exception e){
				Log.e(TAG, "playBackgroundMusic: error state");
			}			
		}
	}
	
	public void stopBackgroundMusic(){
		if (mBackgroundMediaPlayer != null){
			mBackgroundMediaPlayer.stop();
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
		}
	}
	
	public void rewindBackgroundMusic(){		
		if (mBackgroundMediaPlayer != null){
			mBackgroundMediaPlayer.stop();
			
			try {
				mBackgroundMediaPlayer.prepare();
				mBackgroundMediaPlayer.start();
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
		if (mBackgroundMediaPlayer != null)
		{
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
		if (this.mBackgroundMediaPlayer != null){
			this.mLeftVolume = this.mRightVolume = volume;
			this.mBackgroundMediaPlayer.setVolume(this.mLeftVolume, this.mRightVolume);
		}
	}
	
	private void initData(){
		mLeftVolume =1.0f;
		mRightVolume = 1.0f;
		mBackgroundMediaPlayer = null;
		mIsPaused = false;
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
            Log.e(TAG, "error: " + e.getMessage(), e);
        }
		
        return mediaPlayer;
	}
}
