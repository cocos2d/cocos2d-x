package org.cocos2dx.utils;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxLuaJavaBridge;
import org.json.JSONObject;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.drawable.Drawable;

public class PSDialog {
	public interface PSDialogListener {
		void onDismiss(PSDialog dialog);
	}

	private AlertDialog mDialog = null;

	private int mDialogLuaListener = 0;
	private Cocos2dxActivity mContext = null;
	private DialogInterface.OnClickListener mDialogClickListener = null;
	private PSDialogListener mPSDialogListener = null;

	private boolean mCancelable = true;
	private String mTitle = null;
	private String mMessage = null;
	private Drawable mIcon = null;
	private Vector<String> mButtonLabels = new Vector<String>();

	public PSDialog(Cocos2dxActivity context) {
		mContext = context;

		mDialogClickListener = new DialogInterface.OnClickListener() {
			@Override
			public void onClick(final DialogInterface dialog, final int which) {
				if (mDialogLuaListener != 0) {
					mContext.runOnGLThread(new Runnable() {
						@Override
						public void run() {
							Map<String, String> map = new HashMap<String, String>();
							map.put("buttonIndex", String.valueOf(-which));
							System.out.println(-which);
							JSONObject jObject = new JSONObject(map);
							Cocos2dxLuaJavaBridge.callLuaFunctionWithString(
									mDialogLuaListener, jObject.toString());
							Cocos2dxLuaJavaBridge
									.releaseLuaFunction(mDialogLuaListener);
						}
					});
				}
				dismiss();
			}
		};
	}

	public PSDialog setListener(PSDialogListener listener) {
		mPSDialogListener = listener;
		return this;
	}

	public PSDialog setCancelable(boolean flag) {
		mCancelable = flag;
		return this;
	}

	public PSDialog setTitle(String title) {
		mTitle = title;
		return this;
	}

	public PSDialog setMessage(String msg) {
		mMessage = msg;
		return this;
	}

	public PSDialog setLuaListener(int listener) {
		mDialogLuaListener = listener;
		return this;
	}

	public PSDialog setIcon(Drawable icon) {
		mIcon = icon;
		return this;
	}

	public int getButtonsCount() {
		return mButtonLabels.size();
	}

	public int addAlertButton(String buttonTitle) {
		if (mButtonLabels.size() >= 3)
			return mButtonLabels.size();

		mButtonLabels.add(buttonTitle);
		return mButtonLabels.size();
	}

	public boolean isShowing() {
		if (mDialog == null)
			return false;
		return mDialog.isShowing();
	}

	public void hide() {
		if (mDialog == null || !isShowing())
			return;
		mDialog.dismiss();
		mDialog = null;
	}

	public void dismiss() {
		if (mDialog == null || !isShowing())
			return;
		mDialog.dismiss();

		if (mPSDialogListener != null) {
			mPSDialogListener.onDismiss(this);
		}

		mDialog = null;
	}

	public void show() {
		if (mDialog != null && isShowing()) {
			mDialog.dismiss();
			return;
		}

		mDialog = new AlertDialog.Builder(mContext).setCancelable(mCancelable)
				.setTitle(mTitle).setMessage(mMessage).create();
		if (mTitle != null && mTitle.length() > 0 && mIcon != null) {
			mDialog.setIcon(mIcon);
		}

		for (int i = 0; i < mButtonLabels.size(); i++) {
			switch (i) {
			case 0:
				mDialog.setButton(mButtonLabels.elementAt(i),
						mDialogClickListener);
				break;
			case 1:
				mDialog.setButton2(mButtonLabels.elementAt(i),
						mDialogClickListener);
				break;
			case 2:
				mDialog.setButton3(mButtonLabels.elementAt(i),
						mDialogClickListener);
				break;
			default:
				break;
			}
		}

		mDialog.show();
	}
}
