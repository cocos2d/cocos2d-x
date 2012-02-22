package org.cocos2dx.lib;

import android.app.Activity;
import android.app.Dialog;
import android.content.res.AssetFileDescriptor;
import android.graphics.Color;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.util.Log;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;
import android.widget.VideoView;

public class Cocos2dxVideo {

	private Activity mContext;
	private MediaPlayer mediaPlayer = null;
	private OnCompletionListener complitionListener;
	private Dialog dialog = null;
	private Cocos2dxGLSurfaceView mGLView;
	private static Cocos2dxVideo mSharedVideoPlayer;
	
	public Cocos2dxVideo(Activity context){
		this.mContext = context;
		mSharedVideoPlayer = this;
	}
	
	public void playVideoInt(final String fileName, boolean showControls,
			final boolean skipByTap) {

		mContext.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				if (mediaPlayer != null) {
					try {
						mediaPlayer.stop();
						mediaPlayer.release();
						mediaPlayer = null;
					} catch (Exception e) {
					}
				}

				dialog = new Dialog(mContext,
						android.R.style.Theme_Black_NoTitleBar_Fullscreen);
				/*
				 * dialog.getWindow().requestFeature(Window.FEATURE_NO_TITLE);
				 * dialog
				 * .getWindow().setLayout(ViewGroup.LayoutParams.MATCH_PARENT,
				 * ViewGroup.LayoutParams.MATCH_PARENT);
				 * dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
				 * dialog.getWindow
				 * ().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
				 */
				dialog.setCancelable(false);

				LinearLayout layout = new LinearLayout(mContext);
				layout.setLayoutParams(new LinearLayout.LayoutParams(
						LinearLayout.LayoutParams.MATCH_PARENT,
						LinearLayout.LayoutParams.MATCH_PARENT));
				layout.setGravity(Gravity.CENTER);
				dialog.setContentView(layout);

				layout.setBackgroundColor(Color.BLACK);

				final VideoView mSurface = new VideoView(mContext);
				layout.addView(mSurface, new LayoutParams(
						LinearLayout.LayoutParams.MATCH_PARENT,
						LinearLayout.LayoutParams.MATCH_PARENT));

				if (skipByTap) {
					mSurface.setOnTouchListener(new OnTouchListener() {

						@Override
						public boolean onTouch(View v, MotionEvent event) {
							completedVideo();
							return false;
						}
					});
					mSurface.setOnClickListener(new OnClickListener() {

						@Override
						public void onClick(View v) {
							completedVideo();
						}
					});
				}

				SurfaceHolder holder = mSurface.getHolder();
				holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
				holder.addCallback(new Callback() {

					@Override
					public void surfaceDestroyed(SurfaceHolder holder) {
					}

					@Override
					public void surfaceCreated(SurfaceHolder holder) {
						if (mediaPlayer != null) {
							int width = mSurface.getWidth();
							int height = mSurface.getHeight();
							float boxWidth = width;
							float boxHeight = height;

							float videoWidth = mediaPlayer.getVideoWidth();
							float videoHeight = mediaPlayer.getVideoHeight();

							float wr = boxWidth / videoWidth;
							float hr = boxHeight / videoHeight;
							float ar = videoWidth / videoHeight;

							if (wr > hr)
								width = (int) (boxHeight * ar);
							else
								height = (int) (boxWidth / ar);

							mediaPlayer.setDisplay(holder);
							mSurface.setLayoutParams(new LinearLayout.LayoutParams(
									width, height));

							mediaPlayer.start();
						}
					}

					@Override
					public void surfaceChanged(SurfaceHolder holder,
							int format, int width, int height) {
					}
				});

				try {
					AssetFileDescriptor assetFileDescritor = mContext
							.getAssets().openFd(fileName);
					mediaPlayer = new MediaPlayer();
					mediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
					mediaPlayer.setScreenOnWhilePlaying(true);

					mediaPlayer.setDataSource(
							assetFileDescritor.getFileDescriptor(),
							assetFileDescritor.getStartOffset(),
							assetFileDescritor.getLength());

					complitionListener = new OnCompletionListener() {
						@Override
						public void onCompletion(MediaPlayer mp) {
							Log.d("video", "onCompletion");
							mp.release();
							mediaPlayer = null;
							// mGLView.setVisibility(View.VISIBLE);
							dialog.dismiss();

							mGLView.queueEvent(new Runnable() {
								@Override
								public void run() {
									onVideoCompleted();
								}
							});

						}
					};

					mediaPlayer.setOnCompletionListener(complitionListener);

					mediaPlayer.setDisplay(mSurface.getHolder());
					mediaPlayer.prepare();
					mediaPlayer.seekTo(0);

					// mGLView.setVisibility(View.INVISIBLE);
					// mSurface.setVisibility(View.VISIBLE);

					mediaPlayer.start();

					dialog.show();
				} catch (Exception e) {
					mediaPlayer = null;
					onVideoCompleted();

					if (dialog != null) {
						dialog.dismiss();
					}
					// Log.e(TAG, "error: " + e.getMessage(), e);
				}
			}
		});
	}

	private void completedVideo() {
		if (mediaPlayer == null)
			return;
		mediaPlayer.stop();
		complitionListener.onCompletion(mediaPlayer);
	}

	public static void playVideo(String fileName, boolean showControls,
			boolean skipByTap) {
		mSharedVideoPlayer.playVideoInt(fileName, showControls, skipByTap);
	}

	public void onResume() {
		if (mediaPlayer != null) {
    		try {
    		mediaPlayer.stop();
    		} catch (Exception e) {}
    	}
	}
	
	public void onPause() {
		if (mediaPlayer != null) {
    		try {
    			completedVideo();
    		} catch (Exception e){}
    	}
	}


	private static native void onVideoCompleted();

	public void setGLView(Cocos2dxGLSurfaceView GLView) {
		mGLView = GLView;
	}

}
