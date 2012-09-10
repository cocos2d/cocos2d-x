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

import java.util.ArrayList;
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
	
	// sound path and stream ids map
	// a file may be played many times at the same time
	// so there is an array map to a file path
	private HashMap<String,ArrayList<Integer>> mPathStreamIDsMap;
	
	private HashMap<String, Integer> mPathSoundIdMap;
	
	private static final String TAG = "Cocos2dxSound";
	private static final int MAX_SIMULTANEOUS_STREAMS_DEFAULT = 5;
	private static final float SOUND_RATE = 1.0f;
	private static final int SOUND_PRIORITY = 1;
	private static final int SOUND_QUALITY = 5;
	
	private final static int INVALID_SOUND_ID = -1;
	private final static int INVALID_STREAM_ID = -1;
	
	public Cocos2dxSound(Context context){
		this.mContext = context;	
		initData();
	}
	
	public int preloadEffect(String path){
		Integer soundID = this.mPathSoundIdMap.get(path);
		
		if (soundID == null) {
			soundID = createSoundIdFromAsset(path);
			this.mPathSoundIdMap.put(path, soundID);
		}
			
		return soundID;
	}
	
	public void unloadEffect(String path){
		// stop effects
		ArrayList<Integer> streamIDs = this.mPathStreamIDsMap.get(path);
		if (streamIDs != null) {
			for (Integer streamID : streamIDs) {
				this.mSoundPool.stop(streamID);
			}
		}		
		this.mPathStreamIDsMap.remove(path);
		
		// unload effect
		Integer soundID = this.mPathSoundIdMap.get(path);
		this.mSoundPool.unload(soundID);
		this.mPathSoundIdMap.remove(path);
	}
	
	public int playEffect(String path, boolean isLoop){
		Integer soundId = this.mPathSoundIdMap.get(path);
		int streamId = INVALID_STREAM_ID;
		
		if (soundId != null){			
			// play sound
			streamId = this.mSoundPool.play(soundId.intValue(), this.mLeftVolume, 
					this.mRightVolume, SOUND_PRIORITY, isLoop ? -1 : 0, SOUND_RATE);
			
			// record stream id
			ArrayList<Integer> streamIds = this.mPathStreamIDsMap.get(path);
			if (streamIds == null) {
				streamIds = new ArrayList<Integer>();
				this.mPathStreamIDsMap.put(path, streamIds);
			}
			streamIds.add(streamId);
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
		
		return streamId;
	}
	
	public void stopEffect(int streamID){
        this.mSoundPool.stop(streamID);
        
        // remove record
        for (String path : this.mPathStreamIDsMap.keySet()) {
        	if (this.mPathStreamIDsMap.get(path).contains(streamID)) {
        		this.mPathStreamIDsMap.get(path).remove(this.mPathStreamIDsMap.get(path).indexOf(streamID));
        		break;
        	}
        }
	}
	
	public void pauseEffect(int streamID){
        this.mSoundPool.pause(streamID);
	}
	
	public void resumeEffect(int streamID){
        this.mSoundPool.resume(streamID);
	}
	
	public void pauseAllEffects(){
		this.mSoundPool.autoPause();
	}
	
	public void resumeAllEffects(){
		// autoPause() is available since level 8
		this.mSoundPool.autoResume();
	}
	
	@SuppressWarnings("unchecked")
	public void stopAllEffects(){
		// stop effects
		if (! this.mPathStreamIDsMap.isEmpty()) {
			Iterator<?> iter = this.mPathStreamIDsMap.entrySet().iterator();
			while (iter.hasNext()){
				Map.Entry<String, ArrayList<Integer>> entry = (Map.Entry<String, ArrayList<Integer>>)iter.next();
				for (int streamID : entry.getValue()) {
					this.mSoundPool.stop(streamID);
				}
			}
		}		
		
		// remove records
		this.mPathStreamIDsMap.clear();
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
		if (! this.mPathStreamIDsMap.isEmpty()) {
			Iterator<?> iter = this.mPathStreamIDsMap.entrySet().iterator();
			while (iter.hasNext()){
				Map.Entry<String, ArrayList<Integer>> entry = (Map.Entry<String, ArrayList<Integer>>)iter.next();
				for (int streamID : entry.getValue()) {
					this.mSoundPool.setVolume(streamID, mLeftVolume, mRightVolume);
				}
			}
		}		
	}
	
	public void end(){		
		this.mSoundPool.release();	
		this.mPathStreamIDsMap.clear();
		this.mPathSoundIdMap.clear();
		
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
		this.mPathStreamIDsMap = new HashMap<String,ArrayList<Integer>>();
		this.mPathSoundIdMap = new HashMap<String, Integer>();
		mSoundPool = new SoundPool(MAX_SIMULTANEOUS_STREAMS_DEFAULT, AudioManager.STREAM_MUSIC, SOUND_QUALITY);
		
		this.mLeftVolume = 0.5f;
		this.mRightVolume = 0.5f;
	}
}
