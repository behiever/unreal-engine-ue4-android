/*!
 *  @header    IMSDKApplicationDelegate.h
 *  @abstract  IMSDK应用入口处理头文件
 *  @author    Created by Hillson Song on 4/29/15.
 *  @copyright Copyright (c) 2015 Tencent. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/*!
 @class IMSDKApplicationDelegate
 @abstract IMSDK应用入口类
 */
@interface IMSDKApplicationDelegate : NSObject

/*!
 @abstract 获取单例对象
 @result 单例对象
 */
+ (instancetype)sharedInstance;

/*!
 @abstract iMSDK 应用入口
 @discussion 需要在应用 [UIApplicationDelegate application:didFinishLaunchingWithOptions:] 内调用
 @param application     UIApplication
 @param launchOptions   launchOptions
 @param gameSecret      launchOptions
 @result YES
 */
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions withGameSecret:(NSString  *)gameSecret;

/*!
 @abstract 处理应用之间切换
 @discussion 需要在应用 [UIApplicationDelegate application:openURL:sourceApplication:annotation:] 内调用
 @param application       The application as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].
 @param url               The URL as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].
 @param sourceApplication The sourceApplication as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].
 @param annotation        The annotation as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].
 @result YES
 */
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation;

//for iOS9+
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
            options:(NSDictionary *)options;

/*!
 @property application
 @abstract application
 */
@property (nonatomic, strong, readonly) UIApplication *application;

/*!
 @property launchOptions
 @abstract launchOptions
 */
@property (nonatomic, strong, readonly) NSDictionary *launchOptions;

/*!
 @property gameSecret
 @abstract gameSecret
 */
@property (nonatomic, strong, readonly) NSString *gameSecret;

/*!
 *  @brief 通过 application:open:options: 打开 APP，iMSDK 对 URL 参数进行解析处理后的回调
 *
 *  @param launchData 回调参数
 *  @param launchURL 透传 application:open:options: 中完整的 URL 参数
 */
typedef void(^IMSDKUrlLaunchHandle)(NSDictionary *launchData, NSURL *launchURL);

/*!
 @property urlLaunchhandle
 @abstract URL 数据处理回调，插件处理完 URL 处理后，通过 IMSDKUrlLaunchHandle 将 launchData 和 launchURL 带回，并赋值
 */
@property (nonatomic, copy, readonly) IMSDKUrlLaunchHandle urlLaunchHandle;

/*!
 @property launchData
 @abstract 参考 IMSDKUrlLaunchHandle 回调参数 launchData
 */
@property (nonatomic, strong, readonly)  NSDictionary* launchData;

/*!
 @property launchURL
 @abstract 参考 IMSDKUrlLaunchHandle 回调参数 launchURL
 */
@property (nonatomic, strong, readonly) NSURL *launchURL;

/*!
 @abstract 清空 launchData 和 launchURL 缓存数据
 */
- (void)resetHandleResult;

///--------------------
/// @name dictionary keys
///--------------------
FOUNDATION_EXPORT NSString *const IMSDKApplication;
FOUNDATION_EXPORT NSString *const IMSDKUrl;
FOUNDATION_EXPORT NSString *const IMSDKSourceApplication;
FOUNDATION_EXPORT NSString *const IMSDKAnnotation;
FOUNDATION_EXPORT NSString *const IMSDKOptions;
///--------------------
/// @name notifition
///--------------------
FOUNDATION_EXPORT NSString *const IMSDKApplicationOpenUrlNotification;

#pragma mark - APNS Push

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;
- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary*)userInfo;//收到通知的回调
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;//建议使用此函数代替 application:didReceiveRemoteNotification:
- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification;

#pragma mark - Orientation

- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window;

///--------------------
/// @name dictionary keys
///--------------------
FOUNDATION_EXPORT NSString *const IMSDKDeviceToken;
///--------------------
/// @name notifition
///--------------------
FOUNDATION_EXPORT NSString *const IMSDKApplicationFinishLaunchingWithOptionsNotification DEPRECATED_ATTRIBUTE; //NSNotification中userInfo[IMSDKDeviceToken] => deviceToken
FOUNDATION_EXPORT NSString *const IMSDKApplicationRegisterForRemoteNotificationsNotification;//NSNotification中userInfo => error.userInfo
FOUNDATION_EXPORT NSString *const IMSDKApplicationRegisterForRemoteNotificationsFailedNotification; //NSNotification中userInfo => userInfo
FOUNDATION_EXPORT NSString *const IMSDKApplicationDidReceiveRemoteNotificationNotification; //NSNotification中userInfo => userInfo
FOUNDATION_EXPORT NSString *const IMSDKApplicationDidReceiveRemoteNotificationWithFetchCompletionHandlerNotification; //NSNotification中userInfo => userInfo, obj => completionHandler
FOUNDATION_EXPORT NSString *const IMSDKApplicationDidReceiveLocalNotificationNotification; ////NSNotification中object => notification

FOUNDATION_EXPORT NSString *const IMSDKRefreshConfigNotification;
@end
