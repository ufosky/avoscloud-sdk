//
//  paas.h
//  paas
//
//  Created by Zhu Zeng on 2/25/13.
//  Copyright (c) 2013 AVOS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AVConstants.h"
#import "AVGeoPoint.h"
#import "AVObject.h"
#import "AVQuery.h"
#import "AVSearchQuery.h"
#import "AVUser.h"
#import "AVFile.h"
#import "AVAnonymousUtils.h"
#import "AVACL.h"
#import "AVInstallation.h"
#import "AVPush.h"
#import "AVOSCloud.h"
#import "AVCloud.h"
#import "AVRelation.h"
#import "AVSubclassing.h"
#import "AVStatus.h"
#import "AVUserFeedbackThread.h"
#import "AVUserFeedbackAgent.h"
#import "AVSession.h"
#import "AVSignature.h"

#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
#import "AVAnalytics.h"
#endif

/**
 *  Storage Type
 */
typedef NS_ENUM(int, AVStorageType){
    /// QiNiu
    AVStorageTypeQiniu = 0,
    
    /* Parse */
    AVStorageTypeParse,
    
    /* AWS S3 */
    AVStorageTypeS3,
    
} ;

typedef enum AVLogLevel : NSUInteger {
    AVLogLevelNone      = 0,
    AVLogLevelError     = 1 << 0,
    AVLogLevelWarning   = 1 << 1,
    AVLogLevelInfo      = 1 << 2,
    AVLogLevelVerbose   = 1 << 3,
    AVLogLevelDefault   = AVLogLevelError | AVLogLevelWarning
} AVLogLevel;

#define kAVDefaultNetworkTimeoutInterval 10.0


/**
 *  AVOSCloud is the main Class for AVOSCloud SDK
 */
@interface AVOSCloud : NSObject

/** @name Connecting to AVOS Cloud */

/*!
 Sets the applicationId and clientKey of your application.
 @param applicationId The applicaiton id for your AVOS Cloud application.
 @param clientKey The client key for your AVOS Cloud application.
 */
+ (void)setApplicationId:(NSString *)applicationId clientKey:(NSString *)clientKey;

/**
 *  get Application Id
 *
 *  @return Application Id
 */
+ (NSString *)getApplicationId;

/**
 *  get Client Key
 *
 *  @return Client Key
 */
+ (NSString *)getClientKey;


/**
 *  开启LastModify支持, 减少流量消耗
 *
 *  @param enabled 开启
 */
+ (void)setLastModifyEnabled:(BOOL)enabled;

/**
 *  获取是否开启LastModify支持
 */
+ (BOOL)getLastModifyEnabled;

/**
 *  清空LastModify缓存
 */
+(void)clearLastModifyCache;

+ (void)useAVCloud AVDeprecated("2.3.3以后废除");
+ (void)setStorageType:(AVStorageType)type;

/**
 *  Use AVOS US data center
 */
+ (void)useAVCloudUS AVDeprecated("2.3.3以后废除");

/**
 *  Use AVOS China data center. the default option is China
 */
+ (void)useAVCloudCN AVDeprecated("2.3.3以后废除");

/**
 *  *  get the timeout interval for AVOS request
 *
 *  @return timeout interval
 */
+ (NSTimeInterval)networkTimeoutInterval;

/**
 *  set the timeout interval for AVOS request
 *
 *  @param time  timeout interval
 */
+ (void)setNetworkTimeoutInterval:(NSTimeInterval)time;

// log
+ (void)setLogLevel:(AVLogLevel)level;
+ (AVLogLevel)logLevel;

#pragma mark Schedule work

/**
 *  get the query cache expired days
 *
 *  @return the query cache expired days
 */
+ (NSInteger)queryCacheExpiredDays;

/**
 *  set Query Cache Expired Days, default is 30 days
 *
 *  @param days the days you want to set
 */
+ (void)setQueryCacheExpiredDays:(NSInteger)days;

/**
 *  get the file cache expired days
 *
 *  @return the file cache expired days
 */
+ (NSInteger)fileCacheExpiredDays;


/**
 *  set File Cache Expired Days, default is 30 days
 *
 *  @param days the days you want to set
 */
+ (void)setFileCacheExpiredDays:(NSInteger)days;

/*!
 *  请求短信验证码，需要开启手机短信验证 API 选项。
 *  发送短信到指定的手机上，发送短信到指定的手机上，获取6位数字验证码。
 *  @param phoneNumber 11位电话号码
 *  @param callback 回调结果
 */
+(void)requestSmsCodeWithPhoneNumber:(NSString *)phoneNumber
                            callback:(AVBooleanResultBlock)callback;
/*!
 *  请求短信验证码，需要开启手机短信验证 API 选项。
 *  发送短信到指定的手机上，获取6位数字验证码。
 *  @param phoneNumber 11位电话号码
 *  @param appName 应用名称，传nil为默认值您的应用名称
 *  @param operation 操作名称，传nil为默认值"短信认证"
 *  @param ttl 短信过期时间，单位分钟，传0为默认值10分钟
 *  @param callback 回调结果
 */
+(void)requestSmsCodeWithPhoneNumber:(NSString *)phoneNumber
                             appName:(NSString *)appName
                           operation:(NSString *)operation
                          timeToLive:(NSUInteger)ttl
                            callback:(AVBooleanResultBlock)callback;

/*!
 *  验证短信验证码，需要开启手机短信验证 API 选项。
 *  发送验证码给服务器进行验证。
 *  @param code 6位手机验证码
 *  @param callback 回调结果
 */
+(void)verifySmsCode:(NSString *)code callback:(AVBooleanResultBlock)callback;


typedef AVUser PFUser;
typedef AVObject PFObject;
typedef AVGeoPoint PFGeoPoint;
typedef AVQuery PFQuery;
typedef AVFile PFFile;
typedef AVAnonymousUtils PFAnonymousUtils;
typedef AVACL PFACL;
typedef AVRole PFRole;
typedef AVInstallation PFInstallation;
typedef AVPush PFPush;
typedef AVOSCloud Parse;
typedef AVCloud PFCloud;

typedef AVRelation PFRelation;

#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
typedef AVAnalytics PFAnalytics;
#endif

@end
