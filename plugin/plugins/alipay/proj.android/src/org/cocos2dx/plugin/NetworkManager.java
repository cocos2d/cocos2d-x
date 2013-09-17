/*
 * Copyright (C) 2010 The MobileSecurePay Project
 * All right reserved.
 * author: shiqun.shi@alipay.com
 */

package org.cocos2dx.plugin;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.InetSocketAddress;
import java.net.Proxy;
import java.net.URL;
import java.util.ArrayList;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLSession;

import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.message.BasicNameValuePair;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

/**
 * 网络连接工具类
 * 
 */
public class NetworkManager {
	static final String TAG = "NetworkManager";

	private int connectTimeout = 30 * 1000;
	private int readTimeout = 30 * 1000;
	Proxy mProxy = null;
	Context mContext;

	public NetworkManager(Context context) {
		this.mContext = context;
		setDefaultHostnameVerifier();
	}

	/**
	 * 检查代理，是否cnwap接入
	 */
	private void detectProxy() {
		ConnectivityManager cm = (ConnectivityManager) mContext
				.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo ni = cm.getActiveNetworkInfo();
		if (ni != null && ni.isAvailable()
				&& ni.getType() == ConnectivityManager.TYPE_MOBILE) {
			String proxyHost = android.net.Proxy.getDefaultHost();
			int port = android.net.Proxy.getDefaultPort();
			if (proxyHost != null) {
				final InetSocketAddress sa = new InetSocketAddress(proxyHost,
						port);
				mProxy = new Proxy(Proxy.Type.HTTP, sa);
			}
		}
	}

	private void setDefaultHostnameVerifier() {
		//
		HostnameVerifier hv = new HostnameVerifier() {
			public boolean verify(String hostname, SSLSession session) {
				return true;
			}
		};

		HttpsURLConnection.setDefaultHostnameVerifier(hv);
	}

	/**
	 * 发送和接收数据
	 * 
	 * @param strReqData
	 *            请求数据
	 * @param strUrl
	 *            请求地址
	 * @return
	 */
	public String SendAndWaitResponse(String strReqData, String strUrl) {
		//
		detectProxy();

		String strResponse = null;
		ArrayList<BasicNameValuePair> pairs = new ArrayList<BasicNameValuePair>();
		pairs.add(new BasicNameValuePair("requestData", strReqData));

		HttpURLConnection httpConnect = null;
		UrlEncodedFormEntity p_entity;
		try {
			p_entity = new UrlEncodedFormEntity(pairs, "utf-8");
			URL url = new URL(strUrl);

			if (mProxy != null) {
				httpConnect = (HttpURLConnection) url.openConnection(mProxy);
			} else {
				httpConnect = (HttpURLConnection) url.openConnection();
			}
			httpConnect.setConnectTimeout(connectTimeout);
			httpConnect.setReadTimeout(readTimeout);
			httpConnect.setDoOutput(true);
			httpConnect.addRequestProperty("Content-type",
					"application/x-www-form-urlencoded;charset=utf-8");

			httpConnect.connect();

			OutputStream os = httpConnect.getOutputStream();
			p_entity.writeTo(os);
			os.flush();

			InputStream content = httpConnect.getInputStream();
			strResponse = BaseHelper.convertStreamToString(content);
			BaseHelper.log(TAG, "response " + strResponse);
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			httpConnect.disconnect();
		}

		return strResponse;
	}

	/**
	 * 下载文件
	 * 
	 * @param context
	 *            上下文环境
	 * @param strurl
	 *            下载地址
	 * @param path
	 *            下载路径
	 * @return
	 */
	public boolean urlDownloadToFile(Context context, String strurl, String path) {
		boolean bRet = false;

		//
		detectProxy();

		try {
			URL url = new URL(strurl);
			HttpURLConnection conn = null;
			if (mProxy != null) {
				conn = (HttpURLConnection) url.openConnection(mProxy);
			} else {
				conn = (HttpURLConnection) url.openConnection();
			}
			conn.setConnectTimeout(connectTimeout);
			conn.setReadTimeout(readTimeout);
			conn.setDoInput(true);

			conn.connect();
			InputStream is = conn.getInputStream();

			File file = new File(path);
			file.createNewFile();
			FileOutputStream fos = new FileOutputStream(file);

			byte[] temp = new byte[1024];
			int i = 0;
			while ((i = is.read(temp)) > 0) {
				fos.write(temp, 0, i);
			}

			fos.close();
			is.close();

			bRet = true;

		} catch (IOException e) {
			e.printStackTrace();
		}

		return bRet;
	}
}
