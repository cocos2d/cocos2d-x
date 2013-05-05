/*
 * Copyright (C) 2010 The MobileSecurePay Project
 * All right reserved.
 * author: shiqun.shi@alipay.com
 */

package org.cocos2dx.plugin;

public final class AlixId
{
	public static final int BASE_ID 			= 0;
	public static final int RQF_PAY 			= BASE_ID + 1;
	public static final int RQF_INSTALL_CHECK = RQF_PAY + 1;
}

final class AlixDefine
{
	public static final String IMEI 			= "imei";
	public static final String IMSI 			= "imsi";
	public static final String KEY 			= "key";
	public static final String USER_AGENT	= "user_agent";
	public static final String VERSION		= "version";
	public static final String DEVICE		= "device";
	public static final String SID			= "sid";
	public static final String partner		= "partner";
	public static final String charset		= "charset";
	public static final String sign_type		= "sign_type";
	public static final String sign			= "sign";
	
	
	public static final String URL		= "URL";
	public static final String split		= "&";
	
	public static final String AlixPay	=  "AlixPay";

	public static final String action		=  "action";
	public static final String actionUpdate=  "update";
	public static final String data		=  "data";
	public static final String platform	=  "platform";
}