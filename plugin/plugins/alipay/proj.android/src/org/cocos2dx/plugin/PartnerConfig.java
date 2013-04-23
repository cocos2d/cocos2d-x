package org.cocos2dx.plugin;

public class PartnerConfig {

	// 合作商户ID。用签约支付宝账号登录ms.alipay.com后，在账户信息页面获取。
	public static String PARTNER = "";
	// 商户收款的支付宝账号
	public static String SELLER = "";
	// 商户（RSA）私钥
	public static String RSA_PRIVATE = "";
	// 支付宝（RSA）公钥 用签约支付宝账号登录ms.alipay.com后，在密钥管理页面获取。
	public static String RSA_ALIPAY_PUBLIC = "";
	// 支付宝安全支付服务apk的名称，必须与assets目录下的apk名称一致
	public static String ALIPAY_PLUGIN_NAME = "";

}
