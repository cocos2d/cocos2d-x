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

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

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
	
	public int playEffect(String path, boolean isLoop){
		Integer soundId = this.mPathSoundIDMap.get(path);
		
		if (soundId != null){
			// the sound is preloaded, stop it first
			
			this.mSoundPool.stop(soundId);
			
			// play sound
			int streamId = this.mSoundPool.play(soundId.intValue(), this.mLeftVolume, 
					this.mRightVolume, SOUND_PRIORITY, isLoop ? -1 : 0, SOUND_RATE);
			
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
			playEffect(path, isLoop);
		}
		
		return soundId.intValue();
	}
	
	public void stopEffect(int soundId){
        Integer streamId = this.mSoundIdStreamIdMap.get(soundId);
        
        if (streamId != null && streamId.intValue() != INVALID_STREAM_ID){
        	this.mSoundPool.stop(streamId.intValue());
        	this.mPathSoundIDMap.remove(soundId);
        }
	}
	
	public void pauseEffect(int soundId){
        Integer streamId = this.mSoundIdStreamIdMap.get(soundId);
        
        if (streamId != null && streamId.intValue() != INVALID_STREAM_ID){
        	this.mSoundPool.pause(streamId.intValue());
        	this.mPathSoundIDMap.remove(soundId);
        }
	}
	
	public void resumeEffect(int soundId){
        Integer streamId = this.mSoundIdStreamIdMap.get(soundId);
        
        if (streamId != null && streamId.intValue() != INVALID_STREAM_ID){
        	this.mSoundPool.resume(streamId.intValue());
        	this.mPathSoundIDMap.remove(soundId);
        }
	}
	
	public void pauseAllEffects(){
		// autoResume is available since level 8
		pauseOrResumeAllEffects(true);
	}
	
	public void resumeAllEffects(){
		// autoPause() is available since level 8
		pauseOrResumeAllEffects(false);
	}
	
	@SuppressWarnings("unchecked")
	public void stopAllEffects(){
		Iterator<?> iter = this.mSoundIdStreamIdMap.entrySet().iterator();
		while (iter.hasNext()){
			Map.Entry<Integer, Integer> entry = (Map.Entry<Integer, Integer>)iter.next();
			int soundId = entry.getKey();
			this.stopEffect(soundId);
		}
	}
	
	public float getEffectsVolume(){
		return (this.mLeftVolume + this.mRightVolume) / 2;
	}
	
	@SuppressWarnings("unchecked")
	public void setEffectsVolume(float volume){
		// volume should be in [0, 1.0]
		if (volume < 0){
			volume = 0;
		}	
		if (volume > 1){
			volume = 1;
		}
		
		this.mLeftVolume = this.mRightVolume = volume;
		
		// change the volume of playing sounds
		Iterator<?> iter = this.mSoundIdStreamIdMap.entrySet().iterator();
		while (iter.hasNext()){
			Map.Entry<Integer, Integer> entry = (Map.Entry<Integer, Integer>)iter.next();
			this.mSoundPool.setVolume(entry.getValue(), mLeftVolume, mRightVolume);
		}
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
			if (path.startsWith("/")){
				soundId = mSoundPool.load(path, 0);
			}
			else {
				soundId = mSoundPool.load(mContext.getAssets().openFd(path), 0);
			}			
		} catch(Exception e){
			soundId = INVALID_SOUND_ID;
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
	
	@SuppressWarnings("unchecked")
	private void pauseOrResumeAllEffects(boolean isPause){
		Iterator<?> iter = this.mSoundIdStreamIdMap.entrySet().iterator();
		while (iter.hasNext()){
			Map.Entry<Integer, Integer> entry = (Map.Entry<Integer, Integer>)iter.next();
			int soundId = entry.getKey();
			if (isPause) {
				this.pauseEffect(soundId);
			} else {
				this.resumeEffect(soundId);
			}
		}
	}
}
