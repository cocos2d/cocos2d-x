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
	private Context mContext;
	private SoundPool mSoundPool;
	private float mLeftVolume;
	private float mRightVolume;
	
	// sound id and stream id map
	private HashMap<Integer,Integer> mSoundIdStreamIdMap;
	// sound path and sound id map
	private HashMap<String,Integer> mPathSoundIDMap;	
	
	private static final String TAG = "Cocos2dxSound";
	private static final int MAX_SIMULTANEOUS_STREAMS_DEFAULT = 5;
	private static final float SOUND_RATE = 1.0f;
	private static final int SOUND_PRIORITY = 1;
	private static final int SOUND_LOOP_TIME = 0;
	private static final int SOUND_QUALITY = 5;
	
	private final int INVALID_SOUND_ID = -1;
	private final int INVALID_STREAM_ID = -1;
	
	public Cocos2dxSound(Context context){
		this.mContext = context;	
		initData();
	}
	
	public int preloadEffect(String path){
		int soundId = INVALID_SOUND_ID;
		
		// if the sound is preloaded, pass it
		if (this.mPathSoundIDMap.get(path) != null){
			soundId =  this.mPathSoundIDMap.get(path).intValue();
		} else {
			soundId = createSoundIdFromAsset(path);
			
			if (soundId != INVALID_SOUND_ID){
				// the sound is loaded but has not been played
				this.mSoundIdStreamIdMap.put(soundId, INVALID_STREAM_ID);
				
				// record path and sound id map
				this.mPathSoundIDMap.put(path, soundId);
			}
		}
		
		
		
		return soundId;
	}
	
	public void unloadEffect(String path){
		// get sound id and remove from mPathSoundIDMap
		Integer soundId = this.mPathSoundIDMap.remove(path);
		
		if (soundId != null){
			// unload effect
			this.mSoundPool.unload(soundId.intValue());
			
			// remove record from mSoundIdStreamIdMap
			this.mSoundIdStreamIdMap.remove(soundId);
		}
	}
	
	public int playEffect(String path){
		Integer soundId = this.mPathSoundIDMap.get(path);
		
		if (soundId != null){
			// the sound is preloaded
			
			// play sound
			int streamId = this.mSoundPool.play(soundId.intValue(), this.mLeftVolume, 
					this.mRightVolume, SOUND_PRIORITY, SOUND_LOOP_TIME, SOUND_RATE);
			
			// record sound id and stream id map
			this.mSoundIdStreamIdMap.put(soundId, streamId);
		} else {
			// the effect is not prepared
			soundId = preloadEffect(path);	
			if (soundId == INVALID_SOUND_ID){
				// can not preload effect
				return INVALID_SOUND_ID;
			}
			
			/*
			 * Someone reports that, it can not play effect for the
			 * first time. If you are lucky to meet it. There are two
			 * ways to resolve it.
			 * 1. Add some delay here. I don't know how long it is, so
			 *    I don't add it here.
			 * 2. If you use 2.2(API level 8), you can call 
			 *    SoundPool.setOnLoadCompleteListener() to play the effect.
			 *    Because the method is supported from 2.2, so I can't use
			 *    it here.
			 */
			playEffect(path);
		}
		
		return soundId.intValue();
	}
	
	public void stopEffect(int soundId){
        Integer streamId = this.mSoundIdStreamIdMap.get(soundId);
        
        if (streamId != null && streamId.intValue() != INVALID_STREAM_ID){
        	this.mSoundPool.stop(streamId.intValue());
        }
	}
	
	public float getEffectsVolume(){
		return (this.mLeftVolume + this.mRightVolume) / 2;
	}
	
	public void setEffectsVolume(float volume){
		this.mLeftVolume = this.mRightVolume = volume;
	}
	
	public void end(){		
		this.mSoundPool.release();	
		this.mPathSoundIDMap.clear();	
		this.mSoundIdStreamIdMap.clear();
		
		initData();
	}
	
	public int createSoundIdFromAsset(String path){
		int soundId = INVALID_SOUND_ID;
		
		try {
			soundId = mSoundPool.load(mContext.getAssets().openFd(path), 0);
		} catch(Exception e){
			 Log.e(TAG, "error: " + e.getMessage(), e);
		}
		
		return soundId;
	}
	
	private void initData(){
		this.mSoundIdStreamIdMap = new HashMap<Integer,Integer>();
		mSoundPool = new SoundPool(MAX_SIMULTANEOUS_STREAMS_DEFAULT, AudioManager.STREAM_MUSIC, SOUND_QUALITY);
		mPathSoundIDMap = new HashMap<String,Integer>();
		
		this.mLeftVolume = 0.5f;
		this.mRightVolume = 0.5f;
	}
}
