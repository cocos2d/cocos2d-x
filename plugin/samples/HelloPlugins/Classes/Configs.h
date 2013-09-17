#ifndef __CONFIGS_H__
#define __CONFIGS_H__

/** @warning
 * The file UCGameSDK.jar conflicts with weiboSDK.jar
 * if you want test the login/logout of UC,
 * modify the android project config: remove the weiboSDK.jar, and add UCGameSDK.jar
*/
#define TEST_UC             0

#define APP_NAME                "HelloPlugins"

/**
 @brief Developer information of flurry
 */
#define FLURRY_KEY_IOS          "KMGG7CD9WPK2TW4X9VR8"
#define FLURRY_KEY_ANDROID      "SPKFH8KMPGHMMBWRBT5W"

/**
 @brief Developer information of Umeng
 */
#define UMENG_KEY_IOS           "50d2b18c5270152187000097"
#define UMENG_KEY_ANDROID       ""          // umeng key for android is setted in AndroidManifest.xml

/**
 @brief Developer information of Admob
 */
#define ADMOB_ID_IOS            "a1517500cc8f794"
#define ADMOB_ID_ANDROID        "a1516fb6b16b12f"

/**
 @brief Developer information of Nd91
 */
#define ND91_APPID              "100010"
#define ND91_APPKEY             "C28454605B9312157C2F76F27A9BCA2349434E546A6E9C75";
#define ND91_ORIENTATION        "landscape"

/**
 @brief Developer information of QH360
 */
#define QH360_EXCHANGE_RATE     "1"

/**
 @brief Developer information of UC
 */
#define UC_CPID                 "20087"
#define UC_GAME_ID              "119474"
#define UC_SERVER_ID            "1333"

#endif // __CONFIGS_H__
