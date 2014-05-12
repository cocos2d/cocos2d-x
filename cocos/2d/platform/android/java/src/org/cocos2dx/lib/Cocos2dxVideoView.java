/*
 * Copyright (C) 2006 The Android Open Source Project
 * Copyright (c) 2014 Chukong Technologies Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.cocos2dx.lib;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.AssetFileDescriptor;
import android.content.res.Resources;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnErrorListener;
import android.net.Uri;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.FrameLayout;
import android.widget.MediaController.MediaPlayerControl;

import java.io.IOException;
import java.util.Map;

public class Cocos2dxVideoView extends SurfaceView implements MediaPlayerControl {
    private String TAG = "VideoView";
    
    private Uri         mUri;   
    private int         mDuration;

    // all possible internal states
    private static final int STATE_ERROR              = -1;
    private static final int STATE_IDLE               = 0;
    private static final int STATE_PREPARING          = 1;
    private static final int STATE_PREPARED           = 2;
    private static final int STATE_PLAYING            = 3;
    private static final int STATE_PAUSED             = 4;
    private static final int STATE_PLAYBACK_COMPLETED = 5;

    // mCurrentState is a VideoView object's current state.
    // mTargetState is the state that a method caller intends to reach.
    // For instance, regardless the VideoView object's current state,
    // calling pause() intends to bring the object to a target state
    // of STATE_PAUSED.
    private int mCurrentState = STATE_IDLE;
    private int mTargetState  = STATE_IDLE;

    // All the stuff we need for playing and showing a video
    private SurfaceHolder mSurfaceHolder = null;
    private MediaPlayer mMediaPlayer = null;
    private int         mVideoWidth = 0;
    private int         mVideoHeight = 0;
    
    private OnVideoEventListener mOnVideoEventListener;
    private MediaPlayer.OnPreparedListener mOnPreparedListener;
    private int         mCurrentBufferPercentage;
    private OnErrorListener mOnErrorListener;
    
    // recording the seek position while preparing
    private int         mSeekWhenPrepared;  

    protected Context mContext = null;
    
    protected int mViewLeft = 0;
    protected int mViewTop = 0;
    protected int mViewWidth = 0;
    protected int mViewHeight = 0;
    
    protected int mVisibleLeft = 0;
    protected int mVisibleTop = 0;
    protected int mVisibleWidth = 0;
    protected int mVisibleHeight = 0;
    
    private int mViewTag = 0;
    
    public Cocos2dxVideoView(Context context,int tag) {
        super(context);
        
        mViewTag = tag;
        mContext = context;
        initVideoView();
    }

    public Cocos2dxVideoView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
        
        mContext = context;
        initVideoView();
    }
    
    public Cocos2dxVideoView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        
        mContext = context;
        initVideoView();
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
    	if (mVideoWidth == 0 || mVideoHeight == 0) {
    		setMeasuredDimension(mViewWidth, mViewHeight);
    		Log.e(TAG, ""+mViewWidth+ ":" +mViewHeight);
		}
        else {
        	setMeasuredDimension(mVisibleWidth, mVisibleHeight);
        	Log.e(TAG, ""+mVisibleWidth+ ":" +mVisibleHeight);
		}
    	
    }
    
    public void setVideoRect(int left,int top,int maxWidth,int maxHeight) {
    	mViewLeft = left;
		mViewTop = top;
		mViewWidth = maxWidth;
		mViewHeight = maxHeight;
		
		if (mVideoWidth != 0 && mVideoHeight != 0) {
			fixSize();
		}
	}
    
    public int resolveAdjustedSize(int desiredSize, int measureSpec) {
        int result = desiredSize;
        int specMode = MeasureSpec.getMode(measureSpec);
        int specSize =  MeasureSpec.getSize(measureSpec);

        switch (specMode) {
            case MeasureSpec.UNSPECIFIED:
                /* Parent says we can be as big as we want. Just don't be larger
                 * than max size imposed on ourselves.
                 */
                result = desiredSize;
                break;

            case MeasureSpec.AT_MOST:
                /* Parent says we can be as big as we want, up to specSize.
                 * Don't be larger than specSize, and don't be larger than
                 * the max size imposed on ourselves.
                 */
                result = Math.min(desiredSize, specSize);
                break;

            case MeasureSpec.EXACTLY:
                // No choice. Do what we are told.
                result = specSize;
                break;
        }
        return result;
}

    private boolean mNeedResume = false;
    
    @Override
    public void setVisibility(int visibility) {
    	if (visibility == INVISIBLE) {
			mNeedResume = isPlaying();
			if (mNeedResume) {
				mSeekWhenPrepared = getCurrentPosition();
			}
		}
    	else if (mNeedResume){
    		start();
			mNeedResume = false;
		}
    	super.setVisibility(visibility);
    }
    
    private void initVideoView() {
        mVideoWidth = 0;
        mVideoHeight = 0;
        getHolder().addCallback(mSHCallback);
        setFocusable(true);
        setFocusableInTouchMode(true);
        mCurrentState = STATE_IDLE;
        mTargetState  = STATE_IDLE;
    }
    
    @Override
    public boolean onTouchEvent(MotionEvent event) {
    	if((event.getAction() & MotionEvent.ACTION_MASK) == MotionEvent.ACTION_UP)
    	{
    		if (isPlaying()) {
    			pause();
    		} else if(mCurrentState == STATE_PAUSED){
    			resume();
    		}
    	}
    	
    	return true;
    }
    
    private boolean isAssetRouse = false;
    private String fileName = null;
    
    public void setVideoFileName(String path) {
    	if (path.startsWith("/")) {
    		isAssetRouse = false;
			setVideoURI(Uri.parse(path),null);
		}
		else {
			fileName = path;
			isAssetRouse = true;
			setVideoURI(Uri.parse(path),null);
		}
    }
    
    public void setVideoURL(String url) {
    	isAssetRouse = false;
    	setVideoURI(Uri.parse(url), null);
    }

    /**
     * @hide
     */
    private void setVideoURI(Uri uri, Map<String, String> headers) {
        mUri = uri;
        mSeekWhenPrepared = 0;
        mVideoWidth = 0;
        mVideoHeight = 0;
        openVideo();
        requestLayout();
        invalidate();
    }
    
    public void stopPlayback() {
        if (mMediaPlayer != null) {
            mMediaPlayer.stop();
            mMediaPlayer.release();
            mMediaPlayer = null;
            mCurrentState = STATE_IDLE;
            mTargetState  = STATE_IDLE;
        }
    }

    private void openVideo() {
    	if (mSurfaceHolder == null) {
    		// not ready for playback just yet, will try again later
			return;
		}
    	if (isAssetRouse) {
			if(fileName == null)
				return;
		} else {
			if(mUri == null)
				return;
		}
        
        // Tell the music playback service to pause
        // TODO: these constants need to be published somewhere in the framework.
        Intent i = new Intent("com.android.music.musicservicecommand");
        i.putExtra("command", "pause");
        mContext.sendBroadcast(i);

        // we shouldn't clear the target state, because somebody might have
        // called start() previously
        release(false);
        
        try {
        	//if (mMediaPlayer == null) {
        		mMediaPlayer = new MediaPlayer();
                mMediaPlayer.setOnPreparedListener(mPreparedListener);
                mMediaPlayer.setOnVideoSizeChangedListener(mSizeChangedListener);                
                mMediaPlayer.setOnCompletionListener(mCompletionListener);
                mMediaPlayer.setOnErrorListener(mErrorListener);
                mMediaPlayer.setOnBufferingUpdateListener(mBufferingUpdateListener);
                
                mMediaPlayer.setDisplay(mSurfaceHolder);
                mMediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
                mMediaPlayer.setScreenOnWhilePlaying(true);
			//}
        	
        	mDuration = -1;
            mCurrentBufferPercentage = 0;
            if (isAssetRouse) {
            	AssetFileDescriptor afd = mContext.getAssets().openFd(fileName);
            	mMediaPlayer.setDataSource(afd.getFileDescriptor(),afd.getStartOffset(),afd.getLength());
			} else {
				mMediaPlayer.setDataSource(mContext, mUri);
			}
            
            mMediaPlayer.prepareAsync();
            // we don't set the target state here either, but preserve the
            // target state that was there before.
            mCurrentState = STATE_PREPARING;
        } catch (IOException ex) {
            Log.w(TAG, "Unable to open content: " + mUri, ex);
            mCurrentState = STATE_ERROR;
            mTargetState = STATE_ERROR;
            mErrorListener.onError(mMediaPlayer, MediaPlayer.MEDIA_ERROR_UNKNOWN, 0);
            return;
        } catch (IllegalArgumentException ex) {
            Log.w(TAG, "Unable to open content: " + mUri, ex);
            mCurrentState = STATE_ERROR;
            mTargetState = STATE_ERROR;
            mErrorListener.onError(mMediaPlayer, MediaPlayer.MEDIA_ERROR_UNKNOWN, 0);
            return;
        }
    }
    
    private boolean mKeepRatio = false;
    
    public void setKeepRatio(boolean enabled) {
    	mKeepRatio = enabled;
    	fixSize();
	}

    public void fixSize() {
    	if (mViewWidth != 0 && mViewHeight != 0) {
    		if (mKeepRatio) {
    			if ( mVideoWidth * mViewHeight  > mViewWidth * mVideoHeight ) {
    				mVisibleWidth = mViewWidth;
    				mVisibleHeight = mViewWidth * mVideoHeight / mVideoWidth;
                } else if ( mVideoWidth * mViewHeight  < mViewWidth * mVideoHeight ) {
                	mVisibleWidth = mViewHeight * mVideoWidth / mVideoHeight;
                	mVisibleHeight = mViewHeight;
                }
    			mVisibleLeft = mViewLeft + (mViewWidth - mVisibleWidth) / 2;
    			mVisibleTop = mViewTop + (mViewHeight - mVisibleHeight) / 2;
			} else {
				mVisibleLeft = mViewLeft;
	    		mVisibleTop = mViewTop;
				mVisibleWidth = mViewWidth;
				mVisibleHeight = mViewHeight;
			}
		}
    	else {
    		mVisibleLeft = mViewLeft;
    		mVisibleTop = mViewTop;
			mVisibleWidth = mVideoWidth;
			mVisibleHeight = mVideoHeight;
		}
    	
    	getHolder().setFixedSize(mVisibleWidth, mVisibleHeight);
    	
    	FrameLayout.LayoutParams lParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
				FrameLayout.LayoutParams.WRAP_CONTENT);
		lParams.leftMargin = mVisibleLeft;
		lParams.topMargin = mVisibleTop;
		setLayoutParams(lParams);
	}

    protected 
    MediaPlayer.OnVideoSizeChangedListener mSizeChangedListener =
        new MediaPlayer.OnVideoSizeChangedListener() {
            public void onVideoSizeChanged(MediaPlayer mp, int width, int height) {
                mVideoWidth = mp.getVideoWidth();
                mVideoHeight = mp.getVideoHeight();
                if (mVideoWidth != 0 && mVideoHeight != 0) {
                    getHolder().setFixedSize(mVideoWidth, mVideoHeight);
                }
            }
    };
    

    MediaPlayer.OnPreparedListener mPreparedListener = new MediaPlayer.OnPreparedListener() {
        public void onPrepared(MediaPlayer mp) {
            mCurrentState = STATE_PREPARED;

            if (mOnPreparedListener != null) {
                mOnPreparedListener.onPrepared(mMediaPlayer);
            }
            
            mVideoWidth = mp.getVideoWidth();
            mVideoHeight = mp.getVideoHeight();

            int seekToPosition = mSeekWhenPrepared;  // mSeekWhenPrepared may be changed after seekTo() call
            if (seekToPosition != 0) {
                seekTo(seekToPosition);
            }
            if (mVideoWidth != 0 && mVideoHeight != 0) {
            	fixSize();
            } 
            
            if (mTargetState == STATE_PLAYING) {
                start();
            }
        }
    };

    private MediaPlayer.OnCompletionListener mCompletionListener =
        new MediaPlayer.OnCompletionListener() {
        public void onCompletion(MediaPlayer mp) {
            mCurrentState = STATE_PLAYBACK_COMPLETED;
            mTargetState = STATE_PLAYBACK_COMPLETED;
            
            mp.release();
            if (mOnVideoEventListener != null) {
                mOnVideoEventListener.onVideoEvent(mViewTag,EVENT_COMPLETED);
            }
        }
    };
    
    
    private static final int EVENT_PLAYING = 0;
    private static final int EVENT_PAUSED = 1;
    private static final int EVENT_STOPPED = 2;
    private static final int EVENT_COMPLETED = 3;
    
    public interface OnVideoEventListener
    {
    	void onVideoEvent(int tag,int event);
    }

    private MediaPlayer.OnErrorListener mErrorListener =
        new MediaPlayer.OnErrorListener() {
        public boolean onError(MediaPlayer mp, int framework_err, int impl_err) {
            Log.d(TAG, "Error: " + framework_err + "," + impl_err);
            mCurrentState = STATE_ERROR;
            mTargetState = STATE_ERROR;

            /* If an error handler has been supplied, use it and finish. */
            if (mOnErrorListener != null) {
                if (mOnErrorListener.onError(mMediaPlayer, framework_err, impl_err)) {
                    return true;
                }
            }

            /* Otherwise, pop up an error dialog so the user knows that
             * something bad has happened. Only try and pop up the dialog
             * if we're attached to a window. When we're going away and no
             * longer have a window, don't bother showing the user an error.
             */
            if (getWindowToken() != null) {
                Resources r = mContext.getResources();
                int messageId;
                
                if (framework_err == MediaPlayer.MEDIA_ERROR_NOT_VALID_FOR_PROGRESSIVE_PLAYBACK) {
                    //messageId = com.android.internal.R.string.VideoView_error_text_invalid_progressive_playback;
                	messageId = r.getIdentifier("VideoView_error_text_invalid_progressive_playback", "string", "android");
                } else {
                    //messageId = com.android.internal.R.string.VideoView_error_text_unknown;
                	messageId = r.getIdentifier("VideoView_error_text_unknown", "string", "android");
                }
                
                int titleId = r.getIdentifier("VideoView_error_title", "string", "android");
                int buttonStringId = r.getIdentifier("VideoView_error_button", "string", "android");
                
                new AlertDialog.Builder(mContext)
                        .setTitle(r.getString(titleId))
                        .setMessage(messageId)
                        .setPositiveButton(r.getString(buttonStringId),
                                new DialogInterface.OnClickListener() {
                                    public void onClick(DialogInterface dialog, int whichButton) {
                                        /* If we get here, there is no onError listener, so
                                         * at least inform them that the video is over.
                                         */
                                        if (mOnVideoEventListener != null) {
                                            mOnVideoEventListener.onVideoEvent(mViewTag,EVENT_COMPLETED);
                                        }
                                    }
                                })
                        .setCancelable(false)
                        .show();
            }
            return true;
        }
    };

    private MediaPlayer.OnBufferingUpdateListener mBufferingUpdateListener =
        new MediaPlayer.OnBufferingUpdateListener() {
        public void onBufferingUpdate(MediaPlayer mp, int percent) {
            mCurrentBufferPercentage = percent;
        }
    };

    /**
     * Register a callback to be invoked when the media file
     * is loaded and ready to go.
     *
     * @param l The callback that will be run
     */
    public void setOnPreparedListener(MediaPlayer.OnPreparedListener l)
    {
        mOnPreparedListener = l;
    }

    /**
     * Register a callback to be invoked when the end of a media file
     * has been reached during playback.
     *
     * @param l The callback that will be run
     */
    public void setOnCompletionListener(OnVideoEventListener l)
    {
        mOnVideoEventListener = l;
    }

    /**
     * Register a callback to be invoked when an error occurs
     * during playback or setup.  If no listener is specified,
     * or if the listener returned false, VideoView will inform
     * the user of any errors.
     *
     * @param l The callback that will be run
     */
    public void setOnErrorListener(OnErrorListener l)
    {
        mOnErrorListener = l;
    }

    SurfaceHolder.Callback mSHCallback = new SurfaceHolder.Callback()
    {
        public void surfaceChanged(SurfaceHolder holder, int format,
                                    int w, int h)
        {
            boolean isValidState =  (mTargetState == STATE_PLAYING);
            boolean hasValidSize = (mVideoWidth == w && mVideoHeight == h);
            if (mMediaPlayer != null && isValidState && hasValidSize) {
                if (mSeekWhenPrepared != 0) {
                    seekTo(mSeekWhenPrepared);
                }
                start();
            }
        }

        public void surfaceCreated(SurfaceHolder holder)
        {
            mSurfaceHolder = holder;
            openVideo();
        }

        public void surfaceDestroyed(SurfaceHolder holder)
        {
            // after we return from this we can't use the surface any more
            mSurfaceHolder = null;
            
            release(true);
        }
    };

    /*
     * release the media player in any state
     */
    private void release(boolean cleartargetstate) {
        if (mMediaPlayer != null) {
            mMediaPlayer.reset();
            mMediaPlayer.release();
            mMediaPlayer = null;
            mCurrentState = STATE_IDLE;
            if (cleartargetstate) {
                mTargetState  = STATE_IDLE;
            }
        }
    }
    
    public void start() {
    	if (isInPlaybackState()) {
            mMediaPlayer.start();
            mCurrentState = STATE_PLAYING;
            if (mOnVideoEventListener != null) {
            	mOnVideoEventListener.onVideoEvent(mViewTag, EVENT_PLAYING);
			}
        }
        mTargetState = STATE_PLAYING;
    }

    public void pause() {
        if (isInPlaybackState()) {
            if (mMediaPlayer.isPlaying()) {
                mMediaPlayer.pause();
                mCurrentState = STATE_PAUSED;
                if (mOnVideoEventListener != null) {
                	mOnVideoEventListener.onVideoEvent(mViewTag, EVENT_PAUSED);
				}
            }
        }
        mTargetState = STATE_PAUSED;
    }
    
    public void stop() {
        if (isInPlaybackState()) {
            if (mMediaPlayer.isPlaying()) {
               stopPlayback();
                if (mOnVideoEventListener != null) {
                	mOnVideoEventListener.onVideoEvent(mViewTag, EVENT_STOPPED);
				}
            }
        }
    }

    public void suspend() {
        release(false);
    }

    public void resume() {
    	if (isInPlaybackState()) {
    		if (mCurrentState == STATE_PAUSED) {
				mMediaPlayer.start();
				mCurrentState = STATE_PLAYING;
				if (mOnVideoEventListener != null) {
                	mOnVideoEventListener.onVideoEvent(mViewTag, EVENT_PLAYING);
				}
			}
    	}
    }

    public void restart() {
    	if (isInPlaybackState()) {
    		mMediaPlayer.seekTo(0);
    		mMediaPlayer.start();
            mCurrentState = STATE_PLAYING;
    		mTargetState = STATE_PLAYING;
    	}
	}
    // cache duration as mDuration for faster access
    public int getDuration() {
        if (isInPlaybackState()) {
            if (mDuration > 0) {
                return mDuration;
            }
            mDuration = mMediaPlayer.getDuration();
            return mDuration;
        }
        mDuration = -1;
        return mDuration;
    }

    public int getCurrentPosition() {
        if (isInPlaybackState()) {
            return mMediaPlayer.getCurrentPosition();
        }
        return 0;
    }

    public void seekTo(int msec) {
        if (isInPlaybackState()) {
            mMediaPlayer.seekTo(msec);
            mSeekWhenPrepared = 0;
        } else {
            mSeekWhenPrepared = msec;
        }
    }

    public boolean isPlaying() {
        return isInPlaybackState() && mMediaPlayer.isPlaying();
    }

    public int getBufferPercentage() {
        if (mMediaPlayer != null) {
            return mCurrentBufferPercentage;
        }
        return 0;
    }

    public boolean isInPlaybackState() {
        return (mMediaPlayer != null &&
                mCurrentState != STATE_ERROR &&
                mCurrentState != STATE_IDLE &&
                mCurrentState != STATE_PREPARING);
    }

	@Override
	public boolean canPause() {
		// TODO Auto-generated method stub
		return true;
	}

	@Override
	public boolean canSeekBackward() {
		// TODO Auto-generated method stub
		return true;
	}

	@Override
	public boolean canSeekForward() {
		// TODO Auto-generated method stub
		return true;
	}
    	
    public int getAudioSessionId () {
       // TODO Auto-generated method stub
       return mMediaPlayer.getAudioSessionId();
    }
}
