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
	private Context context;
	private MediaPlayer mBackgroundMediaPlayer;
	
	public Cocos2dxMusic(Context context){
		this.context = context;
		mBackgroundMediaPlayer = null;
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
		assert(mBackgroundMediaPlayer != null);
		
		if (mBackgroundMediaPlayer != null){
			mBackgroundMediaPlayer.stop();
		}
	}
	
	public void pauseBackgroundMusic(){
		assert(mBackgroundMediaPlayer != null);
		
		if (mBackgroundMediaPlayer != null){
			mBackgroundMediaPlayer.pause();
		}
	}
	
	public void resumeBackgroundMusic(){
		assert(mBackgroundMediaPlayer != null);
		
		if (mBackgroundMediaPlayer != null){
			mBackgroundMediaPlayer.start();
		}
	}
	
	public void rewindBackgroundMusic(){
		assert(mBackgroundMediaPlayer != null);
		
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
	
	
	/*
	public int getBackgroundVolume(){
		
	}
	
	public void setBackgroundVolume(int volume){
	
	}
	*/
	
	/**
	 * create mediaplayer for music
	 * @param path the path relative to assets
	 * @return 
	 */
	private MediaPlayer createMediaplayerFromAssets(String path){
		MediaPlayer mediaPlayer = null;
		
		try{
			mediaPlayer = new MediaPlayer();
			AssetFileDescriptor assetFileDescritor = context.getAssets().openFd(path);    
	        mediaPlayer.setDataSource(assetFileDescritor.getFileDescriptor(), 
	        		assetFileDescritor.getStartOffset(), assetFileDescritor.getLength());
	        mediaPlayer.prepare();
		}catch (Exception e) {
            Log.e(TAG, "error: " + e.getMessage(), e);
        }
		
        return mediaPlayer;
	}
}
