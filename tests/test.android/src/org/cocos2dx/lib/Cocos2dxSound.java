package org.cocos2dx.lib;

import java.util.HashMap;

import android.content.Context;
import android.media.AudioManager;
import android.media.SoundPool;
import android.util.Log;

/**
 * 
 * This class is used for controlling effect
 *
 */

public class Cocos2dxSound {
	private Context context;
	private HashMap<Integer,Integer> mSoundIdStreamIdMap;
	private HashMap<String,Integer> mPathSoundIDMap;
	private static final int MAX_SIMULTANEOUS_STREAMS_DEFAULT = 5;
	private final SoundPool mSoundPool;
	private static final String TAG = "Cocos2dxSound";
	private final int INVALID_SOUND_ID = -1;
	private final int INVALID_STREAM_ID = -1;
	
	public Cocos2dxSound(Context context){
		this.context = context;
		this.mSoundIdStreamIdMap = new HashMap<Integer,Integer>();
		mSoundPool = new SoundPool(MAX_SIMULTANEOUS_STREAMS_DEFAULT, AudioManager.STREAM_MUSIC, 0);
		mPathSoundIDMap = new HashMap<String,Integer>();
	}
	
	void preloadEffect(String path){
		int soundId = createSoundIdFromAsset(path);
		
		if (soundId != INVALID_SOUND_ID){
			// the sound is loaded but has not been played
			this.mSoundIdStreamIdMap.put(soundId, INVALID_STREAM_ID);
			
			this.mPathSoundIDMap.put(path, soundId);
		}
	}
	
	void unloadEffect(String path){
		// get sound id and remove from mPathSoundIDMap
		Integer soundId = this.mPathSoundIDMap.remove(path);
		
		if (soundId != null){
			// unload effect
			this.mSoundPool.unload(soundId.intValue());
			
			// remove record from mSoundIdStreamIdMap
			this.mSoundIdStreamIdMap.remove(soundId);
		}
	}
	
	void playEffect(String path){
		Integer soundId = this.mPathSoundIDMap.get(path);
		
		if (soundId != null){
			// the sound is preloaded
			
			// play sound
			int streamId = this.mSoundPool.play(soundId.intValue(), 1.0f, 1.0f, 1, 1, 1.0f);
			
			// record 
			this.mSoundIdStreamIdMap.put(soundId, streamId);
		} else {
			// the effect is not prepared
			preloadEffect(path);	
			playEffect(path);
		}
	}
	
	void stopEffect(int soundId){
        Integer streamId = this.mSoundIdStreamIdMap.get(soundId);
        
        if (streamId != null){
        	this.mSoundPool.stop(streamId.intValue());
        }
	}
	
	public int createSoundIdFromAsset(String path){
		int soundId = INVALID_SOUND_ID;
		
		try {
			soundId = mSoundPool.load(context.getAssets().openFd(path), 1);
		} catch(Exception e){
			 Log.e(TAG, "error: " + e.getMessage(), e);
		}
		
		return soundId;
	}
}
