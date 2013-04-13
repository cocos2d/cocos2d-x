//
//  MobClick.h
//  MobClick
//
//  Created by Aladdin on 2010-03-25.
//  Updated by Minghua on 2012-09-11.
//  Copyright 2010-2012 Umeng.com . All rights reserved.
//  Version 2.1.0 , updated_at 2012-09-11.

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#define UMOnlineConfigDidFinishedNotification @"OnlineConfigDidFinishedNotification"

typedef enum {
    REALTIME = 0,       //实时发送
    BATCH = 1,          //启动发送
    SENDDAILY = 4,      //每日发送
    SENDWIFIONLY = 5    //仅在WIFI下启动时发送
} ReportPolicy;

@protocol MobClickDelegate;
@class CLLocation;

@interface MobClick : NSObject <UIAlertViewDelegate> {
@private
    id _internal;
}
#pragma mark basics
//开启友盟统计,以BATCH方式发送log.
+ (void)startWithAppkey:(NSString *)appKey;
// channelId 为nil或@""时,默认会被被当作@"App Store"渠道
+ (void)startWithAppkey:(NSString *)appKey reportPolicy:(ReportPolicy)rp channelId:(NSString *)cid;

/*
    自定义app版本信息，如果不设置，默认从CFBundleVersion里取,取得的是build version,和xcode3工程兼容.
    如果需要和xcode4版本保持一致，请使用下面的方法
    NSString *version = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    [MobClick setAppVersion:version];
 */
+ (void)setAppVersion:(NSString *)appVersion;
+ (NSString *)getAgentVersion;  //获取友盟sdk 版本号

/*方法名:
 *		setCrashReportEnabled:(BOOL)value
 *介绍:
 *		类方法设置是否让umeng SDK 捕捉和记录您的crash log
 *参数说明:
 *		(BOOL)value:默认值为YES
 *	    设置为NO,umeng SDK 不再捕捉和记录您的crash log,需要在setDelegate方法之前调用
 */
+ (void)setCrashReportEnabled:(BOOL)value;
/*方法名:
 *		setLogEnabled:(BOOL)value
 *介绍:
 *		类方法设置是否打印sdk的log信息
 *参数说明:
 *		(BOOL)value:默认值为NO
 *	    设置为YES,umeng SDK 会输出log信息,记得release产品时要设置回NO
 */
+ (void)setLogEnabled:(BOOL)value;

/*方法名:
 *		logPageView:seconds:
 *介绍:
 *		类方法，记录某个view打开多长时间.
 *
 *参数说明:
 *      pageName NSString * 类型
 *      seconds  秒数，int型
 *
 *      这个方法记录的信息将在下次启动时发送
 *
 *返回值:
 *      无返回值
 *
 *文档地址: http://dev.umeng.com/doc/document_ana_ios.html#8
 */
+ (void)logPageView:(NSString *)pageName seconds:(int)seconds;
+ (void)beginLogPageView:(NSString *)pageName;
+ (void)endLogPageView:(NSString *)pageName;

#pragma mark event logs
/*方法名:
 *		event:(NSString *)eventId
 *		event:(NSString *)eventId label:(NSString *)label
 *		event:(NSString *)eventId acc:(NSInteger)accumulation
 *		event:(NSString *)eventId label:(NSString *)label acc:(NSInteger)accumulation
 *介绍:
 *       使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID即可 
 *		类方法，生成一条事件记录，并保存到本地缓存
 *参数说明:
 *		无参数版本可以方便的生成一条事件记录，并将分类标签设为空，计数设为1
 *		label:为某事件ID添加该事件的分类标签统计。在友盟的统计后台中，可以通过同一事件ID进行统计和整理。同一事件ID的不同的标签，也会分别进行统计，方便同一事件的不同标签的对比。
 *		accumulation:为某一事件的某一分类进行累加统计。为减少网络交互，可以自行对某一事件ID的某一分类标签进行累加，再传入次数作为参数即可。
 *		
 *文档地址: http://dev.umeng.com/doc/document_ana_ios.html#3
 */

//如果label为nil或@""时，服务器端会生成一个unknown的默认label,
//为避免这种情况,2.0.0之后label为nil或@""时,label将被赋值为eventId
//详细文档参见 iOS统计分析SDK开发指南.html 或在线文档
//http://dev.umeng.com/doc/document_ana_ios.html#3
+ (void)event:(NSString *)eventId; //等同于 event:eventId label:eventId;
+ (void)event:(NSString *)eventId label:(NSString *)label; // label为nil或@""时，等同于 event:eventId label:eventId;
+ (void)event:(NSString *)eventId acc:(NSInteger)accumulation;
+ (void)event:(NSString *)eventId label:(NSString *)label acc:(NSInteger)accumulation;
+ (void)event:(NSString *)eventId attributes:(NSDictionary *)attributes;

+ (void)beginEvent:(NSString *)eventId;
+ (void)endEvent:(NSString *)eventId;
+ (void)beginEvent:(NSString *)eventId label:(NSString *)label;
+ (void)endEvent:(NSString *)eventId label:(NSString *)label;

//primarykey这个参数用于和event_id一起标示一个唯一事件，并不会被统计；
//对于同一个事件在beginEvent和endEvent 中要传递相同的eventId 和 primarykey
//每个event的attributes不能超过10个
//eventId、attributes中key和value都不能使用空格和特殊字符，且长度不能超过255个字符（否则将截取前255个字符）
//id， ts， du是保留字段，不能作为eventId及key的名称
+ (void)beginEvent:(NSString *)eventId primarykey :(NSString *)keyName attributes:(NSDictionary *)attributes;
+ (void)endEvent:(NSString *)eventId primarykey:(NSString *)keyName;

//时间单位为毫秒 microseconds
+ (void)event:(NSString *)eventId durations:(int)microseconds;
+ (void)event:(NSString *)eventId label:(NSString *)label durations:(int)microseconds;
+ (void)event:(NSString *)eventId attributes:(NSDictionary *)attributes durations:(int)microseconds;


#pragma mark feedback Default GUI
/*方法名:	  	
  - *    showFeedback:(UIViewController *)rootViewcontroller 	
  - *介绍:
  - *    类方法，弹出一个默认的反馈界面，生成一条反馈记录，并保存到本地缓存 	
  - *参数说明:
  - *    rootViewController:会用来弹出presentModalViewController方法来展示反馈界面
  - *    请确保rootViewController非空
  - *
  - * 此方法将在下一次更新中删除，请使用独立的用户反馈SDK
  - */


+ (void)showFeedback:(UIViewController *)rootViewController;

#pragma mark feedback data api
/*方法名:
 *		feedbackWithDictionary:(NSDictionary * )feedbackDict
 *介绍:
 *		类方法，生成一条反馈记录，并保存到本地缓存。这是自定义反馈的数据接口，视图方面请自己定义，调用该接口传送数据即可。
 *参数说明:
 *		Dictionary中应该有以下三个键名:
 *      @"UMengFeedbackGender" @"UMengFeedbackAge" @"UMengFeedbackContent"
 *		键值部分:
 *		都是NSString类型的，其中性别和年龄是填写数字代表
 *		对应关系是 1=>男 2=>女
 *		年龄部分的对应关系是 
 *		1=>18岁以下(不含18岁),2=>18-24岁,3=>25-30岁,
 *		4=>31-35岁,5=>36-40岁,6=>41-50岁,7=>51-59岁,8=>60岁及60岁以上
 *
 *       请在调用该方法之前自行判断键值的完整性和正确性，否则会保存失败
 *       这些键值会保存到本地中，并在下次提交数据时上传到服务器
 *返回值:
 *      无
 *
 *
 * 此方法将在下一次更新中删除，请使用独立的用户反馈SDK
 */
+ (void)feedbackWithDictionary:(NSDictionary *)feedbackDict;


#pragma mark check app update
/*方法名:
 *		checkUpdate
 *	    checkUpdateWithTitle:CancelButtonTitle:OtherButtonTitle:
 *介绍:
 *		类方法，检查当前app是否有更新，有更新弹出UIAlertView提示用户,当用户点击升级按钮时app会跳转到您预先设置的网址。
 *		无更新不做任何操作。
 *	    您需要先在服务器端设置app版本信息，默认渠道是App Store.
 *	    checkUpdate 会发送和渠道相关的更新请求.
 *
 *参数说明:
 *      checkUpdate 无参数。
 *		checkUpdate:cancelButtonTitle:otherButtonTitles: 有三个参数:
 *	    title 对应UIAlertView的title
 *	    cancelTitle 对应UIAlertView的cancelTitle
 *	    otherTitle 对应UIAlertView的otherTitle
 *	    
 *      请在[MobClick setDelegate:reportPolicy:]方法之后调用;
 *      如果您想自己控制自动更新操作流程，请实现MobClickDelegate的appUpdate方法。
 *
 *返回值:
 *      无
 *
 *文档地址: http://dev.umeng.com/doc/document_ana_ios.html#5
 */
+ (void)checkUpdate;
+ (void)checkUpdate:(NSString *)title cancelButtonTitle:(NSString *)cancelTitle otherButtonTitles:(NSString *)otherTitle;
+ (void)checkUpdateWithDelegate:(id)delegate selector:(SEL)callBackSelectorWithDictionary;


#pragma mark online config params
/*方法名:
 *		updateOnlineConfig
 *介绍:
 *		类方法，检查并更新服务器端配置的在线参数,缓存在[NSUserDefaults standardUserDefaults]里.
 *	    调用此方法您将自动拥有在线更改SDK端发送策略的功能。
 *	    您需要先在服务器端设置好在线参数.
 *
 *参数说明:
 *      无参数。
 *
 *      请在[MobClick setDelegate:reportPolicy:]方法之后调用;
 *      如果您要使用友盟的在线参数，此方法必不可少。
 *
 *返回值:
 *      无
 *
 *文档地址: http://dev.umeng.com/doc/document_ana_ios.html#6
 */
+ (void)updateOnlineConfig;

/*方法名:
 *		getConfigParams
 *		getConfigParams:
 *介绍:
 *		类方法，从[NSUserDefaults standardUserDefaults]获取缓存的在线参数的数值.
 *	    带参数的方法获取某个key的值，不带参数的获取所有的在线参数.
 *
 *参数说明:
 *      NSString * 类型或无参数
 *
 *      这两个方法都是从[NSUserDefaults standardUserDefaults]获取缓存的值,
 *      所以上面的updateOnlineConfig方法要先在app启动时被调用。
 *
 *返回值:
 *      (NSString *) 或 (NSDictionary *)
 *
 *文档地址: http://dev.umeng.com/doc/document_ana_ios.html#6
 */
+ (NSString *)getConfigParams:(NSString *)key;
+ (NSDictionary *)getConfigParams;

// 为了更精确的统计用户地理位置，可以调用此方法传入经纬度信息
// 需要链接 CoreLocation.framework 并且 #import <CoreLocation/CoreLocation.h>
+ (void)setLatitude:(double)latitude longitude:(double)longitude;
+ (void)setLocation:(CLLocation *)location;


#pragma mark helper
/*方法名:
 *		isJailbroken
 *介绍:
 *		类方法，判断设备是否越狱，判断方法根据 apt和Cydia.app的path来判断
 *参数说明:
 *		无
 *		
 *
 */

#pragma mark utils api
// 类方法，判断当前设备是否已经越狱
+ (BOOL)isJailbroken;
// 类方法，判断你的App是否被破解
+ (BOOL)isPirated;

#pragma mark DEPRECATED methods from version 1.7
/*方法名:
 *		setDelegate:(id<MobClickDelegate>)delegate
 *		setDelegate:(id<MobClickDelegate>)delegate reportPolicy:(ReportPolicy)rp;
 *介绍:
 *      此方法已经被更间接的startWithAppkey:(NSString *)appKey 所取代，建议开发者修改;
 *      好处是可以完全舍去MobClickDelegate实现，使集成更简单.
 *		类方法设置MobClick代理，并初始化MobClick实例，请在调用appLaunched方法前，调用本方法
 *参数说明:
 *		delegate:实现了MobClickDelegate协议的实例
 *		ReportPolicy:发送统计信息的策略设置，有两种可选的发送策略
 *					1.BATCH		:批量发送。每次发送的时机在软件开启的时候进行发送
 *					2.REALTIME	:实时发送。每当有事件（event）产生时，进行发送
 *
 */
+ (void)setDelegate:(id)delegate;
+ (void)setDelegate:(id)delegate reportPolicy:(ReportPolicy)rp;

/*方法名:
 *		appLaunched
 *介绍:
 *		类方法，记录启动时间，模块开始启用。请在调用本方法前，调用setDelegate:或 setDelegate: reportPolicy: 方法
 *参数说明:
 *		无
 *
 * 此方法在1.6.7及以后的版本中废弃，不再需要手动调用.
 */
+ (void)appLaunched;
/*方法名:
 *		appTerminated
 *介绍:
 *		类方法，记录软件终止时间，模块终止。
 *参数说明:
 *		无
 * 此方法在1.6.7及以后的版本中废弃，不再需要手动调用.
 */
+ (void)appTerminated;

/*
    这两个方法是友盟SDK内部使用的监听方法，在App启动（或进入前台）和退出（或进入后台）时自动调用。
    一般情况是不需要手动干预的。
    [MobClick startWithAppkey:]通常在application:didFinishLaunchingWithOptions:里被调用监听
    App启动和退出事件，如果你没法在application:didFinishLaunchingWithOptions:里添加友盟的[MobClick startWithAppkey:]
    方法，App的启动事件可能会无法监听，此时你就可以手动调用[MobClick startSession:nil]来启动友盟的session。
 */
+ (void)startSession:(NSNotification *)notification;
@end

//此协议的三个方法不再建议使用，建议用新方法代替
//+ (void)startWithAppkey:(NSString *)appKey reportPolicy:(ReportPolicy)rp channelId:(NSString *)cid;
//+ (void)checkUpdate:(id)delegate selector:(SEL)callBackSelector;
@protocol MobClickDelegate <NSObject>
@optional
/*方法名:
 *		- (NSString *)appKey;
 *介绍:
 *		返回Appkey，如果Appkey错误，统计后台不会对log进行记录
 *参数说明:
 *		请确保您的Appkey是从友盟后台注册新App得到的
 *
 */
- (NSString *)appKey;
/*方法名:
 *		- (NSString *)channelId;
 *介绍:
 *		返回ChannelID
 *参数说明:
 *		返回的是渠道名，例如@"Apple Store",或者@"产品主页"等
 *       注意：服务器端对设备只进行一次统计，以后更改渠道名对该设备并不进行更新。所以再测试不同的渠道的时候，请使用不同的设备来分别测试。
 *
 */
- (NSString *)channelId;
/*方法名:
 *		- (void)appUpdate:(NSMutableDictionary *)updateInfo;
 *介绍:
 *
 *参数说明:
 *		 当您调用[MobClick checkUpdate]方法后，系统会自动调用此方法appUpdate，
 *		 updateInfo是与此app版本信息相关的参数。
 *		 
 *
 *
 */
- (void)appUpdate:(NSDictionary *)appUpdateInfo;

@end