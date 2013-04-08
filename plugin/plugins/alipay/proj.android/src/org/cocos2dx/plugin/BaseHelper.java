/*
 * Copyright (C) 2010 The MobileSecurePay Project
 * All right reserved.
 * author: shiqun.shi@alipay.com
 */

package org.cocos2dx.plugin;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import org.json.JSONObject;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;

/**
 * 工具类
 * 
 */
public class BaseHelper {

	/**
	 * 流转字符串方法
	 * 
	 * @param is
	 * @return
	 */
	public static String convertStreamToString(InputStream is) {
		BufferedReader reader = new BufferedReader(new InputStreamReader(is));
		StringBuilder sb = new StringBuilder();
		String line = null;
		try {
			while ((line = reader.readLine()) != null) {
				sb.append(line);
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				is.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return sb.toString();
	}

	/**
	 * 显示dialog
	 * 
	 * @param context
	 *            环境
	 * @param strTitle
	 *            标题
	 * @param strText
	 *            内容
	 * @param icon
	 *            图标
	 */
	public static void showDialog(Activity context, String strTitle,
			String strText, int icon) {
		AlertDialog.Builder tDialog = new AlertDialog.Builder(context);
		tDialog.setIcon(icon);
		tDialog.setTitle(strTitle);
		tDialog.setMessage(strText);
		tDialog.setPositiveButton("确定", null);
		tDialog.show();
	}

	/**
	 * 打印信息
	 * 
	 * @param tag
	 *            标签
	 * @param info
	 *            信息
	 */
	public static void log(String tag, String info) {
		// Log.d(tag, info);
	}

	/**
	 * 获取权限
	 * 
	 * @param permission
	 *            权限
	 * @param path
	 *            路径
	 */
	public static void chmod(String permission, String path) {
		try {
			String command = "chmod " + permission + " " + path;
			Runtime runtime = Runtime.getRuntime();
			runtime.exec(command);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	//
	// show the progress bar.
	/**
	 * 显示进度条
	 * 
	 * @param context
	 *            环境
	 * @param title
	 *            标题
	 * @param message
	 *            信息
	 * @param indeterminate
	 *            确定性
	 * @param cancelable
	 *            可撤销
	 * @return
	 */
	public static ProgressDialog showProgress(Context context,
			CharSequence title, CharSequence message, boolean indeterminate,
			boolean cancelable) {
		ProgressDialog dialog = new ProgressDialog(context);
		dialog.setTitle(title);
		dialog.setMessage(message);
		dialog.setIndeterminate(indeterminate);
		dialog.setCancelable(false);
		// dialog.setDefaultButton(false);
		dialog.setOnCancelListener(new IAPAlipay.AlixOnCancelListener(
				(Activity) context));

		dialog.show();
		return dialog;
	}

	/**
	 * 字符串转json对象
	 * @param str
	 * @param split
	 * @return
	 */
	public static JSONObject string2JSON(String str, String split) {
		JSONObject json = new JSONObject();
		try {
			String[] arrStr = str.split(split);
			for (int i = 0; i < arrStr.length; i++) {
				String[] arrKeyValue = arrStr[i].split("=");
				json.put(arrKeyValue[0],
						arrStr[i].substring(arrKeyValue[0].length() + 1));
			}
		}

		catch (Exception e) {
			e.printStackTrace();
		}

		return json;
	}
}