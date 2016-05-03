//
//  MobClick.h
//  MobClick
//
//  Created by Aladdin on 2010-03-25.
//  Updated by Minghua on 2013-08-08.
//  Copyright 2010-2012 Umeng.com . All rights reserved.
//  Version 2.2.1.OpenUDID, updated_at 2013-09-12.

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#define UMOnlineConfigDidFinishedNotification @"OnlineConfigDidFinishedNotification"
#define XcodeAppVersion [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]

typedef enum {
    REALTIME = 0,       //实时发送
    BATCH = 1,          //启动发送
    SENDDAILY = 4,      //每日发送
    SENDWIFIONLY = 5,   //仅在WIFI下启动时发送
    SEND_INTERVAL = 6,   //按最小间隔发送
    SEND_ON_EXIT = 7        //退出或进入后台时发送
} ReportPolicy;

@protocol MobClickDelegate;
@class CLLocation;

/** MobClick是统计的核心类，本身不需要实例化，所有方法以类方法的形式提供.
    目前发送策略有REALTIME,BATCH,SENDDAILY,SENDWIFIONLY,SEND_INTERVAL,SEND_ON_EXIT。
    其中REALTIME,SENDWIFIONLY 只在模拟器和DEBUG模式下生效，真机release模式会自动改成BATCH。
    关于发送策略的调整，请参见关于发送策略及发送策略变更的说明
    http://blog.umeng.com/index.php/2012/12/0601/
    SEND_INTERVAL 为按最小间隔发送,默认为10秒,取值范围为10 到 86400(一天)， 如果不在这个区间的话，会按10设置。
    SEND_ON_EXIT 为退出或进入后台时发送,这种发送策略在App运行过程中不发送，对开发者和用户的影响最小。
    不过这种发送策略只在iOS > 4.0时才会生效, iOS < 4.0 会被自动调整为BATCH。

 */
@interface MobClick : NSObject <UIAlertViewDelegate> {
@private
    id _internal;
}
#pragma mark basics

///---------------------------------------------------------------------------------------
/// @name  设置
///---------------------------------------------------------------------------------------

/** 设置app版本号。由于历史原因需要和xcode3工程兼容,友盟提取的是Build号(CFBundleVersion),如果需要和App Store上的版本一致,需要调用此方法。
 
 @param appVersion 版本号，例如设置成`XcodeAppVersion`.
 @return void.
*/
+ (void)setAppVersion:(NSString *)appVersion;


/** 开启CrashReport收集, 默认是开启状态.
 
 @param value 设置成NO,就可以关闭友盟CrashReport收集.
 @return void.
*/
+ (void)setCrashReportEnabled:(BOOL)value;


/** 设置是否打印sdk的log信息,默认不开启
 @param value 设置为YES,umeng SDK 会输出log信息,记得release产品时要设置回NO.
 @return .
 @exception .
 */

+ (void)setLogEnabled:(BOOL)value;


///---------------------------------------------------------------------------------------
/// @name  开启统计
///---------------------------------------------------------------------------------------


/** 开启友盟统计,默认以BATCH方式发送log.
 
 @param appKey 友盟appKey.
 @param reportPolicy 发送策略.
 @param channelId 渠道名称,为nil或@""时,默认会被被当作@"App Store"渠道
 @return void
*/
+ (void)startWithAppkey:(NSString *)appKey;
+ (void)startWithAppkey:(NSString *)appKey reportPolicy:(ReportPolicy)rp channelId:(NSString *)cid;

/** 当reportPolicy == SEND_INTERVAL 时设定log发送间隔
 
 @param second 单位为秒,最小为10,最大为86400(一天).
 @return void.
*/

+ (void)setLogSendInterval:(double)second;


///---------------------------------------------------------------------------------------
/// @name  页面计时
///---------------------------------------------------------------------------------------


/** 页面时长统计,记录某个view被打开多长时间,可以自己计时也可以调用beginLogPageView,endLogPageView自动计时
 
 @param pageName 需要记录时长的view名称.
 @param seconds 秒数，int型.
 @return void.
*/

+ (void)logPageView:(NSString *)pageName seconds:(int)seconds;
+ (void)beginLogPageView:(NSString *)pageName;
+ (void)endLogPageView:(NSString *)pageName;

#pragma mark event logs


///---------------------------------------------------------------------------------------
/// @name  事件统计
///---------------------------------------------------------------------------------------


/** 自定义事件,数量统计.
    使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID
 
 @param  eventId 网站上注册的事件Id.
 @param  label 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为nil或空字符串时后台会生成和eventId同名的标签.
 @param  accumulation 累加值。为减少网络交互，可以自行对某一事件ID的某一分类标签进行累加，再传入次数作为参数。
 @return void.
 */
+ (void)event:(NSString *)eventId; //等同于 event:eventId label:eventId;
/** 自定义事件,数量统计.
 使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID
 */
+ (void)event:(NSString *)eventId label:(NSString *)label; // label为nil或@""时，等同于 event:eventId label:eventId;
/** 自定义事件,数量统计.
 使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID
 */
+ (void)event:(NSString *)eventId acc:(NSInteger)accumulation;
/** 自定义事件,数量统计.
 使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID
 */
+ (void)event:(NSString *)eventId label:(NSString *)label acc:(NSInteger)accumulation;
/** 自定义事件,数量统计.
 使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID
 */
+ (void)event:(NSString *)eventId attributes:(NSDictionary *)attributes;

/** 自定义事件,时长统计.
    使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
    beginEvent,endEvent要配对使用,也可以自己计时后通过durations参数传递进来
 
 @param  eventId 网站上注册的事件Id.
 @param  label 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为nil或空字符串时后台会生成和eventId同名的标签.
 @param  primarykey 这个参数用于和event_id一起标示一个唯一事件，并不会被统计；对于同一个事件在beginEvent和endEvent 中要传递相同的eventId 和 primarykey
 @param millisecond 自己计时需要的话需要传毫秒进来
 @return void.
 
 
 @warning 每个event的attributes不能超过10个
    eventId、attributes中key和value都不能使用空格和特殊字符，eventId、attributes的key最大为128个bytes(128个英文及数字或42个左右汉字)。label、attributes的value最大为256个bytes(256个英文及数字或84个左右汉字),
       超过后将被截短。其中eventId超过的将抛弃不再发送。
    id， ts， du是保留字段，不能作为eventId及key的名称

*/
+ (void)beginEvent:(NSString *)eventId;
/** 自定义事件,时长统计.
 使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
 */
+ (void)endEvent:(NSString *)eventId;
/** 自定义事件,时长统计.
 使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
 */

+ (void)beginEvent:(NSString *)eventId label:(NSString *)label;
/** 自定义事件,时长统计.
 使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
 */

+ (void)endEvent:(NSString *)eventId label:(NSString *)label;
/** 自定义事件,时长统计.
 使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
 */

+ (void)beginEvent:(NSString *)eventId primarykey :(NSString *)keyName attributes:(NSDictionary *)attributes;
/** 自定义事件,时长统计.
 使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
 */

+ (void)endEvent:(NSString *)eventId primarykey:(NSString *)keyName;
/** 自定义事件,时长统计.
 使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
 */

+ (void)event:(NSString *)eventId durations:(int)millisecond;
/** 自定义事件,时长统计.
 使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
 */

+ (void)event:(NSString *)eventId label:(NSString *)label durations:(int)millisecond;
/** 自定义事件,时长统计.
 使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
 */

+ (void)event:(NSString *)eventId attributes:(NSDictionary *)attributes durations:(int)millisecond;


///---------------------------------------------------------------------------------------
/// @name  按渠道自动更新
///---------------------------------------------------------------------------------------


/** 按渠道自动更新检测
    检查当前app是否有更新，有更新弹出UIAlertView提示用户,当用户点击升级按钮时app会跳转到您预先设置的网址。
    无更新不做任何操作。
    您需要先在服务器端设置app版本信息，默认渠道是App Store.
    如果您想自己控制自动更新操作流程，请实现MobClickDelegate的appUpdate方法。
 
 @param title 对应UIAlertView的title.
 @param cancelTitle 对应UIAlertView的cancelTitle.
 @param otherTitle 对应UIAlertView的otherTitle.
 @param delegate 需要自定义checkUpdate的对象.
 @param callBackSelectorWithDictionary 当checkUpdate事件完成时此方法会被调用,同时标记app更新信息的字典被传回.
 @return void.
 */

+ (void)checkUpdate;
/** 按渠道自动更新检测
 */

+ (void)checkUpdate:(NSString *)title cancelButtonTitle:(NSString *)cancelTitle otherButtonTitles:(NSString *)otherTitle;
/** 按渠道自动更新检测
 */

+ (void)checkUpdateWithDelegate:(id)delegate selector:(SEL)callBackSelectorWithDictionary;


///---------------------------------------------------------------------------------------
/// @name  在线参数
///---------------------------------------------------------------------------------------


/** 使用在线参数功能，可以让你动态修改应用中的参数值,
    检查并更新服务器端配置的在线参数,缓存在[NSUserDefaults standardUserDefaults]里,
    调用此方法您将自动拥有在线更改SDK端发送策略的功能,您需要先在服务器端设置好在线参数.
    请在[MobClick startWithAppkey:]方法之后调用;
    如果想知道在线参数是否完成完成，请监听UMOnlineConfigDidFinishedNotification
 @param 无.
 @return void.
 */

+ (void)updateOnlineConfig;

/** 从[NSUserDefaults standardUserDefaults]获取缓存的在线参数的数值
    带参数的方法获取某个key的值，不带参数的获取所有的在线参数.
    需要先调用updateOnlineConfig才能使用,如果想知道在线参数是否完成完成，请监听UMOnlineConfigDidFinishedNotification
 
 @param key
 @return (NSString *) .
 */

+ (NSString *)getConfigParams:(NSString *)key;

/** 从[NSUserDefaults standardUserDefaults]获取缓存的在线参数
  @return (NSDictionary *).
 */

+ (NSDictionary *)getConfigParams;


///---------------------------------------------------------------------------------------
/// @name 地理位置设置
///---------------------------------------------------------------------------------------


/** 为了更精确的统计用户地理位置，可以调用此方法传入经纬度信息
    需要链接 CoreLocation.framework 并且 #import <CoreLocation/CoreLocation.h>
 @param latitude 纬度.
 @param longitude 经度.
 @param location CLLocation *型的地理信息
 @return void
 */

+ (void)setLatitude:(double)latitude longitude:(double)longitude;
/** 为了更精确的统计用户地理位置，可以调用此方法传入经纬度信息
 */

+ (void)setLocation:(CLLocation *)location;


///---------------------------------------------------------------------------------------
/// @name helper方法
///---------------------------------------------------------------------------------------


/** 判断设备是否越狱，判断方法根据 apt和Cydia.app的path来判断
 */
+ (BOOL)isJailbroken;
/** 判断你的App是否被破解
 */
+ (BOOL)isPirated;

#pragma mark DEPRECATED methods from version 1.7


/** 设置MobClick代理,已经startWithAppkey:所取代,不要再使用，原有代码可以删除
*/

+ (void)setDelegate:(id)delegate;
+ (void)setDelegate:(id)delegate reportPolicy:(ReportPolicy)rp;

/** 记录启动时间，模块开始启用,不要再使用，原有代码可以删除
*/

+ (void)appLaunched;

/** 记录软件终止时间，模块终止,不要再使用，原有代码可以删除
 */

+ (void)appTerminated;

/** 友盟模块启动
 [MobClick startWithAppkey:]通常在application:didFinishLaunchingWithOptions:里被调用监听
 App启动和退出事件，如果你没法在application:didFinishLaunchingWithOptions:里添加友盟的[MobClick startWithAppkey:]
 方法，App的启动事件可能会无法监听，此时你就可以手动调用[MobClick startSession:nil]来启动友盟的session。
 通常发生在某些第三方框架生成的app里，普通app使用不到.
 
 */

+ (void)startSession:(NSNotification *)notification;


/** 获取友盟sdk 版本号,目前友盟模块启动时自动调用,不要再使用，原有代码可以删除
 */

+ (NSString *)getAgentVersion;  //
@end

/** MobClickDelegate protocol
    此协议的三个方法不再建议使用，建议用新方法代替
    + (void)startWithAppkey:(NSString *)appKey reportPolicy:(ReportPolicy)rp channelId:(NSString *)cid;
    + (void)checkUpdate:(id)delegate selector:(SEL)callBackSelector;

 */


@protocol MobClickDelegate <NSObject>
@optional
- (NSString *)appKey;
- (NSString *)channelId;
- (void)appUpdate:(NSDictionary *)appUpdateInfo;

@end