/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
import java.util.Map.Entry;
import java.util.concurrent.Semaphore;

import android.content.Context;
import android.media.AudioManager;
import android.media.SoundPool;
import android.util.Log;

public class Cocos2dxSound {
	// ===========================================================
	// Constants
	// ===========================================================

	private static final String TAG = "Cocos2dxSound";

	// ===========================================================
	// Fields
	// ===========================================================

	private final Context mContext;
	private SoundPool mSoundPool;
	private float mLeftVolume;
	private float mRightVolume;

	// sound path and stream ids map
	// a file may be played many times at the same time
	// so there is an array map to a file path
	private final HashMap<String, ArrayList<Integer>> mPathStreamIDsMap = new HashMap<String, ArrayList<Integer>>();

	private final HashMap<String, Integer> mPathSoundIDMap = new HashMap<String, Integer>();

	private final ArrayList<SoundInfoForLoadedCompleted> mEffecToPlayWhenLoadedArray = new ArrayList<SoundInfoForLoadedCompleted>();

	private int mStreamIdSyn;
	private Semaphore mSemaphore;

	private static final int MAX_SIMULTANEOUS_STREAMS_DEFAULT = 5;
	private static final int MAX_SIMULTANEOUS_STREAMS_I9100 = 3;
	private static final float SOUND_RATE = 1.0f;
	private static final int SOUND_PRIORITY = 1;
	private static final int SOUND_QUALITY = 5;

	private final static int INVALID_SOUND_ID = -1;
	private final static int INVALID_STREAM_ID = -1;

	// ===========================================================
	// Constructors
	// ===========================================================

	public Cocos2dxSound(final Context pContext) {
		this.mContext = pContext;

		this.initData();
	}

	private void initData() {
		if (Cocos2dxHelper.getDeviceModel().indexOf("GT-I9100") != -1) {
			this.mSoundPool = new SoundPool(Cocos2dxSound.MAX_SIMULTANEOUS_STREAMS_I9100, AudioManager.STREAM_MUSIC, Cocos2dxSound.SOUND_QUALITY);
		}
		else {
			this.mSoundPool = new SoundPool(Cocos2dxSound.MAX_SIMULTANEOUS_STREAMS_DEFAULT, AudioManager.STREAM_MUSIC, Cocos2dxSound.SOUND_QUALITY);
		}
		
		this.mSoundPool.setOnLoadCompleteListener(new OnLoadCompletedListener());

		this.mLeftVolume = 0.5f;
		this.mRightVolume = 0.5f;

		this.mSemaphore = new Semaphore(0, true);
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

	public int preloadEffect(final String pPath) {
		Integer soundID = this.mPathSoundIDMap.get(pPath);

		if (soundID == null) {
			soundID = this.createSoundIDFromAsset(pPath);
			// save value just in case if file is really loaded
			if (soundID != Cocos2dxSound.INVALID_SOUND_ID) {
				this.mPathSoundIDMap.put(pPath, soundID);
			}
		}

		return soundID;
	}

	public void unloadEffect(final String pPath) {
		// stop effects
		final ArrayList<Integer> streamIDs = this.mPathStreamIDsMap.get(pPath);
		if (streamIDs != null) {
			for (final Integer pStreamID : streamIDs) {
				this.mSoundPool.stop(pStreamID);
			}
		}
		this.mPathStreamIDsMap.remove(pPath);

		// unload effect
		final Integer soundID = this.mPathSoundIDMap.get(pPath);
		if(soundID != null){
			this.mSoundPool.unload(soundID);
			this.mPathSoundIDMap.remove(pPath);
		}
	}

	public int playEffect(final String pPath, final boolean pLoop, float pitch, float pan, float gain){
		Integer soundID = this.mPathSoundIDMap.get(pPath);
		int streamID = Cocos2dxSound.INVALID_STREAM_ID;

		if (soundID != null) {
			// parameters; pan = -1 for left channel, 1 for right channel, 0 for both channels

			// play sound
			streamID = this.doPlayEffect(pPath, soundID.intValue(), pLoop, pitch, pan, gain);
		} else {
			// the effect is not prepared
			soundID = this.preloadEffect(pPath);
			if (soundID == Cocos2dxSound.INVALID_SOUND_ID) {
				// can not preload effect
				return Cocos2dxSound.INVALID_SOUND_ID;
			}

			// only allow one playEffect at a time, or the semaphore will not work correctly
			synchronized(this.mSoundPool) {
				// add this effect into mEffecToPlayWhenLoadedArray, and it will be played when loaded completely
				mEffecToPlayWhenLoadedArray.add(new SoundInfoForLoadedCompleted(pPath, soundID.intValue(), pLoop,
																								pitch, pan, gain));

				try {
					// wait OnloadedCompleteListener to set streamID
					this.mSemaphore.acquire();

					streamID = this.mStreamIdSyn;
				} catch(Exception e) {
					return Cocos2dxSound.INVALID_SOUND_ID;
				}
			}
		}

		return streamID;
	}

	public void stopEffect(final int pStreamID) {
		this.mSoundPool.stop(pStreamID);

		// remove record
		for (final String pPath : this.mPathStreamIDsMap.keySet()) {
			if (this.mPathStreamIDsMap.get(pPath).contains(pStreamID)) {
				this.mPathStreamIDsMap.get(pPath).remove(this.mPathStreamIDsMap.get(pPath).indexOf(pStreamID));
				break;
			}
		}
	}

	public void pauseEffect(final int pStreamID) {
		this.mSoundPool.pause(pStreamID);
	}

	public void resumeEffect(final int pStreamID) {
		this.mSoundPool.resume(pStreamID);
	}

	public void pauseAllEffects() {
		this.mSoundPool.autoPause();
	}

	public void resumeAllEffects() {
		// can not only invoke SoundPool.autoResume() here, because
		// it only resumes all effects paused by pauseAllEffects()
		if (!this.mPathStreamIDsMap.isEmpty()) {
			final Iterator<Entry<String, ArrayList<Integer>>> iter = this.mPathStreamIDsMap.entrySet().iterator();
			while (iter.hasNext()) {
				final Entry<String, ArrayList<Integer>> entry = iter.next();
				for (final int pStreamID : entry.getValue()) {
					this.mSoundPool.resume(pStreamID);
				}
			}
		}
	}

	@SuppressWarnings("unchecked")
	public void stopAllEffects() {
		// stop effects
		if (!this.mPathStreamIDsMap.isEmpty()) {
			final Iterator<?> iter = this.mPathStreamIDsMap.entrySet().iterator();
			while (iter.hasNext()) {
				final Map.Entry<String, ArrayList<Integer>> entry = (Map.Entry<String, ArrayList<Integer>>) iter.next();
				for (final int pStreamID : entry.getValue()) {
					this.mSoundPool.stop(pStreamID);
				}
			}
		}

		// remove records
		this.mPathStreamIDsMap.clear();
	}

	public float getEffectsVolume() {
		return (this.mLeftVolume + this.mRightVolume) / 2;
	}

	public void setEffectsVolume(float pVolume) {
		// pVolume should be in [0, 1.0]
		if (pVolume < 0) {
			pVolume = 0;
		}
		if (pVolume > 1) {
			pVolume = 1;
		}

		this.mLeftVolume = this.mRightVolume = pVolume;

		// change the volume of playing sounds
		if (!this.mPathStreamIDsMap.isEmpty()) {
			final Iterator<Entry<String, ArrayList<Integer>>> iter = this.mPathStreamIDsMap.entrySet().iterator();
			while (iter.hasNext()) {
				final Entry<String, ArrayList<Integer>> entry = iter.next();
				for (final int pStreamID : entry.getValue()) {
					this.mSoundPool.setVolume(pStreamID, this.mLeftVolume, this.mRightVolume);
				}
			}
		}
	}

	public void end() {
		this.mSoundPool.release();
		this.mPathStreamIDsMap.clear();
		this.mPathSoundIDMap.clear();
		this.mEffecToPlayWhenLoadedArray.clear();

		this.mLeftVolume = 0.5f;
		this.mRightVolume = 0.5f;

		this.initData();
	}

	public int createSoundIDFromAsset(final String pPath) {
		int soundID = Cocos2dxSound.INVALID_SOUND_ID;

		try {
			if (pPath.startsWith("/")) {
				soundID = this.mSoundPool.load(pPath, 0);
			} else {
				soundID = this.mSoundPool.load(this.mContext.getAssets().openFd(pPath), 0);
			}
		} catch (final Exception e) {
			soundID = Cocos2dxSound.INVALID_SOUND_ID;
			Log.e(Cocos2dxSound.TAG, "error: " + e.getMessage(), e);
		}

		// mSoundPool.load returns 0 if something goes wrong, for example a file does not exist
		if (soundID == 0) {
			soundID = Cocos2dxSound.INVALID_SOUND_ID;
		}

		return soundID;
	}

		private float clamp(float value, float min, float max) {
			return Math.max(min, (Math.min(value, max)));
		}

	private int doPlayEffect(final String pPath, final int soundId, final boolean pLoop, float pitch, float pan, float gain) {
		float leftVolume = this.mLeftVolume * gain * (1.0f - this.clamp(pan, 0.0f, 1.0f));
		float rightVolume = this.mRightVolume * gain * (1.0f - this.clamp(-pan, 0.0f, 1.0f));
		float soundRate = this.clamp(SOUND_RATE * pitch, 0.5f, 2.0f);

		// play sound
		int streamID = this.mSoundPool.play(soundId, this.clamp(leftVolume, 0.0f, 1.0f), this.clamp(rightVolume, 0.0f, 1.0f), Cocos2dxSound.SOUND_PRIORITY, pLoop ? -1 : 0, soundRate);

		// record stream id
		ArrayList<Integer> streamIDs = this.mPathStreamIDsMap.get(pPath);
		if (streamIDs == null) {
			streamIDs = new ArrayList<Integer>();
			this.mPathStreamIDsMap.put(pPath, streamIDs);
		}
		streamIDs.add(streamID);

		return streamID;
	}

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

	public class SoundInfoForLoadedCompleted {
		public int soundID;
		public boolean isLoop;
		public float pitch;
		public float pan;
		public float gain;
		public String path;

		public SoundInfoForLoadedCompleted(String path, int soundId, boolean isLoop,
											   float pitch, float pan, float gain) {
			this.path = path;
			this.soundID = soundId;
			this.isLoop = isLoop;
			this.pitch = pitch;
			this.pan = pan;
			this.gain = gain;
		}
	}

	public class OnLoadCompletedListener implements SoundPool.OnLoadCompleteListener {

		@Override
		public void onLoadComplete(SoundPool soundPool, int sampleId, int status) {
			if (status == 0)
			{
				// only play effect that are in mEffecToPlayWhenLoadedArray
				for ( SoundInfoForLoadedCompleted info : mEffecToPlayWhenLoadedArray) {
					if (sampleId == info.soundID) {
						// set the stream id which will be returned by playEffect()
						mStreamIdSyn = doPlayEffect(info.path, info.soundID, info.isLoop, info.pitch, info.pan, info.gain);

						// remove it from array, because we will break here
						// so it is safe to do
						mEffecToPlayWhenLoadedArray.remove(info);

						break;
					}
				}
			} else {
				mStreamIdSyn = Cocos2dxSound.INVALID_SOUND_ID;
			}

			mSemaphore.release();
		}
	}
}
