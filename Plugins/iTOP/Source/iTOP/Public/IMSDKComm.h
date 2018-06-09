/*!
 *  @header    IMSDKComm.h
 *  @abstract  IMSDK自定义类型头文件
 *  @author    Created by brightwan on 15-5-20.
 *  @copyright Copyright (c) 2015年 Tencent. All rights reserved.
 */

#ifndef IMSDK_IMSDKComm_h
#define IMSDK_IMSDKComm_h
 
#include <string>
#include <vector>
#include <map>
  
#if PLATFORM_ANDROID
#include "IMSDKJni.h"
#include <android/log.h>  
#define  LOG_TAG "NATIVE_TAG"
#define  iTOPLOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  iTOPLOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)  
#define  iTOPLOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)  
#define  iTOPLOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__) 

jobject initListener(JNIEnv *env, long metadataPointer, long resultPointer, int tag);
#endif  

#define IMSDK_LOGIN_API_CLASSPATH     "com/tencent/imsdk/android/api/login/IMSDKLogin"
#define IMSDK_AUTH_API_CLASSPATH      "com/tencent/imsdk/android/api/auth/IMSDKAuth"
#define IMSDK_FRIEND_API_CLASSPATH    "com/tencent/imsdk/android/api/relation/IMSDKFriend"
#define IMSDK_STAT_API_CLASSPATH      "com/tencent/imsdk/android/api/stat/IMSDKStat"
#define IMSDK_PUSH_API_CLASSPATH      "com/tencent/imsdk/android/api/push/IMSDKPush"
#define IMSDK_NOTICE_API_CLASSPATH    "com/tencent/imsdk/android/api/notice/IMSDKNotice"
#define IMSDK_LBS_API_CLASSPATH       "com/tencent/imsdk/android/api/lbs/IMSDKLbs"
#define IMSDK_WEBVIEW_API_CLASSPATH   "com/tencent/imsdk/android/api/webview/IMSDKWebView" 
#define IMSDK_GAMESERVICE_API_CLASSPATH   "com/tencent/imsdk/android/api/gameservice/IMSDKGameService"
#define IMSDK_TOOL_API_CLASSPATH "com/tencent/imsdk/android/tools/DeviceUtils"
#define IMSDK_T_API_CLASSPATH "com/tencent/imsdk/android/tools/T"
#define IMSDK_APK_TOOL_API_CLASSPATH "com/tencent/imsdk/android/tools/APKUtils"
#define IMSDK_ADJUST_EXTEND_CLASSPATH      "com/tencent/imsdk/android/extend/adjust/AdjustExtend"

// 获取某个java对象的值(String), 再赋值给本地对象
#define JniGetAndSetStringField(fieldName, fieldNameStr, jOriginClass, jOriginObj, targetObj) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "Ljava/lang/String;"); \
jstring j##fieldName##FieldValue = (jstring) (env->GetObjectField(jOriginObj, j##fieldName##FieldId)); \
if (j##fieldName##FieldValue == NULL) {\
    targetObj.fieldName = ""; \
} else { \
    char const * c##fieldName##FieldValue = env->GetStringUTFChars(j##fieldName##FieldValue, NULL); \
    targetObj.fieldName = c##fieldName##FieldValue; \
    iTOPLOGD("c%sFieldValue %s", fieldNameStr, c##fieldName##FieldValue); \
    env->ReleaseStringUTFChars(j##fieldName##FieldValue, c##fieldName##FieldValue); \
} \
env->DeleteLocalRef(j##fieldName##FieldValue);

#define JniGetAndSetIntField(fieldName, fieldNameStr, jOriginClass, jOriginObj, targetObj) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "I"); \
targetObj.fieldName = (int) (env->GetIntField(jOriginObj, j##fieldName##FieldId));

// 获取某个java对象的值(long), 再赋值给本地对象
#define JniGetAndSetLongField(fieldName, fieldNameStr, jOriginClass, jOriginObj, targetObj) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "J"); \
targetObj.fieldName = (int) (env->GetLongField(jOriginObj, j##fieldName##FieldId));

// 获取某个java对象的值(float), 再赋值给本地对象
#define JniGetAndSetFloatField(fieldName, fieldNameStr, jOriginClass, jOriginObj, targetObj) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "F"); \
targetObj.fieldName = (int) (env->GetFloatField(jOriginObj, j##fieldName##FieldId));

//获取某个java对象的值(boolean), 再赋值给本地对象
#define JniGetAndSetBooleanField(fieldName, fieldNameStr, jOriginClass, jOriginObj, targetObj) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "Z"); \
targetObj.fieldName = (int) (env->GetBooleanField(jOriginObj, j##fieldName##FieldId));

// 获取某个java对象的值(double), 再赋值给本地对象
#define JniGetAndSetDoubleField(fieldName, fieldNameStr, jOriginClass, jOriginObj, targetObj) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "D"); \
targetObj.fieldName = (double) (env->GetDoubleField(jOriginObj, j##fieldName##FieldId));

// 将本地对象(string)赋值给java对象(jstring)
#define JniSetStringField(jOriginClass, jObject, fieldName, fieldNameStr, target) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "Ljava/lang/String;"); \
jstring j##fieldName##FieldValue = env->NewStringUTF(target.c_str()); \
env->SetObjectField(jObject, j##fieldName##FieldId, j##fieldName##FieldValue ); \
env->DeleteLocalRef(j##fieldName##FieldValue);

// 将本地对象(int)赋值给java对象(int)
#define JniSetIntField(jOriginClass, jObject,fieldName, fieldNameStr, target) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "I"); \
jint j##fieldName##FieldValue = target; \
env->SetIntField(jObject, j##fieldName##FieldId, j##fieldName##FieldValue ); \

// 将本地对象(bool)赋值给java对象(boolean)
#define JniSetBooleanField(jOriginClass, jObject,fieldName, fieldNameStr, target) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "Z"); \
jboolean j##fieldName##FieldValue = target; \
env->SetBooleanField(jObject, j##fieldName##FieldId, j##fieldName##FieldValue ); \

// 将本地对象(long)赋值给java对象(long)
#define JniSetLongField(jOriginClass, jObject,fieldName, fieldNameStr, target) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "J"); \
jlong j##fieldName##FieldValue = target; \
env->SetLongField(jObject, j##fieldName##FieldId, j##fieldName##FieldValue ); \



class IMSDKJson;

/*!
 @class IMSDKResult
 @abstract 结果类
 */
class IMSDKResult {
public:
    /*!
     @property retCode
     @abstract result code
     */
    int retCode;
    
    /*!
     @property retMsg
     @abstract result messsage
     */
    std::string retMsg;
    
    /*!
     @property imsdkRetCode
     @abstract imsdk result code
     */
    int imsdkRetCode;
    
    /*!
     @property imsdkRetMsg
     @abstract imsdk result message
     */
    std::string imsdkRetMsg;
    
    /*!
     @property thirdRetCode
     @abstract third result code
     */
    int thirdRetCode;
    
    /*!
     @property thirdRetMsg
     @abstract third result message
     */
    std::string thirdRetMsg;
    
    /*!
     @property retExtraJson
     @abstract extend result json param
     */
    std::string retExtraJson;
    
    IMSDKResult();
    IMSDKResult(int _retCode);
#if PLATFORM_ANDROID 
    IMSDKResult(std::string _jsonData);
#endif  
    IMSDKResult(int _retCode, std::string _retMsg);
    //新增构造函数，初始化imsdk、third错误码以及错误信息
    IMSDKResult(int _imsdkRetCode, int _thirdRetCode);
    IMSDKResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg);

public:
    /*!
     *  @brief 便于将结果对象转换成json,传至unity层
     *
     *  @return json字符串
     */
    std::string toJsonString();
    
protected:
    // 返回存储属性的json对象
    IMSDKJson fillJsonObject();

private:
#if PLATFORM_ANDROID  
    void initialProperties();
#endif  
};


/**
 IMSDK基础回调

 @param result 回调参数
 */
typedef void(*IMSDKCallBack)(IMSDKResult result);
 
/*!
 @class IMSDKLoginResult
 @abstract 登录结果类
 */
class IMSDKLoginResult : public IMSDKResult{
public:
    /*!
     @property guid_channel_id
     @abstract 登录 channel id
     */
    int guid_channel_id;
    
    /*!
     @property guid_game_id
     @abstract 登录 game id
     */
    int guid_game_id;
    
    /*!
     @property guid
     @abstract 用户 guid
     */
    std::string guid;
    
    /*!
     @property guid_open_id
     @abstract 用户 openid
     */
    std::string guid_open_id;
    
    /*!
     @property guid_token
     @abstract 用户 token
     */
    std::string guid_token;
    
    /*!
     @property guid_token_expire
     @abstract 用户登录态有效时间（linux 时间戳）
     */
    long long guid_token_expire;
    
    /*!
     @property guid_user_gender
     @abstract 用户性别（0-未定义，1-男，2-女）
     */
    int guid_user_gender;
    
    /*!
     @property guid_user_nick
     @abstract 用户昵称
     */
    std::string guid_user_nick;
    
    /*!
     @property guid_user_birthday
     @abstract 用户出生日期，比如 1987-2-23 11:33:33
     */
    std::string guid_user_birthday;
    
    /*!
     @property guid_user_portrait
     @abstract 用户头像（url）
     */
    std::string guid_user_portrait;
    
    /*!
     @property channel
     @abstract 登录渠道名，比如 Facebook／WeChat/Google/Guest 等
     */
    std::string channel;
    
    /*!
     @property channel_userid
     @abstract 第三方登录渠道用户 id
     */
    std::string channel_userid;
    
    /*!
     @property channel_token
     @abstract 第三方登录渠道用户 token
     */
    std::string channel_token;
    
    /*!
     @property channel_permissions
     @abstract 第三方渠道用户权限
     */
    std::vector<std::string> channel_permissions;
    
    /*!
     @property channel_expire
     @abstract 第三方渠道登录态有效时间
     */
    long long channel_expire;
    
    /*!
     @property method_tag
     @abstract 操作名，用于回调时区分回调来源
     */
    std::string method_tag;
    
    IMSDKLoginResult();
    IMSDKLoginResult(int);
#if PLATFORM_ANDROID  
    IMSDKLoginResult(std::string _jsonData);
#endif 
    IMSDKLoginResult(int, std::string);
    
    //新增构造函数，初始化imsdk、third错误码以及错误信息
    IMSDKLoginResult(int _imsdkRetCode, int _thirdRetCode);
    IMSDKLoginResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg);
    
private:

#if PLATFORM_ANDROID  
    void initialProperties(int errCode, std::string message);
#endif 

#if PLATFORM_IOS 
	void InitIMSDKLoginResult(int errCode, std::string message);
#endif
    
public:
    //便于将结果转换成json,传至unity层
    std::string toJsonString();
protected:
    IMSDKJson fillJsonObject();
};

/**
 IMSDK登录回调回调
 
 @param result 回调参数
 */
typedef void(*IMSDKLoginCallBack)(IMSDKLoginResult result);

/*!
 @class IMSDKChannelInfo
 @abstract 第三方登录渠道信息
 */
struct IMSDKChannelInfo {
    /*!
     @property channel_id
     @abstract 渠道 id
     */
    int channel_id;
    
//    std::string channel;            //当前登陆渠道
//    std::string channel_userid;     //用户id，channel用户的唯一标示，类似openid
//    std::string channel_token;
//    std::vector<std::string> channel_permissions;
    
    /*!
     @property nick
     @abstract 用户昵称
     */
    std::string nick;
    
    /*!
     @property birthday
     @abstract 用户出生日期
     */
    std::string birthday;
    
    /*!
     @property portrait
     @abstract 用户头像（url）
     */
    std::string portrait;
    
    /*!
     @property gender
     @abstract 用户性别（0-未定义，1-男，2-女）
     */
    int gender;
    
    /*!
     @property email
     @abstract 自有账号体系绑定的邮箱账号(Account模块,为空表示没有绑定邮箱)
     */
    std::string email;
    
    /*!
     @property phone
     @abstract 自有账号体系绑定的手机账号(Account模块,为空表示没有手机邮箱)
     */
    std::string phone;
#if PLATFORM_ANDROID  
    IMSDKChannelInfo();
    IMSDKChannelInfo(std::string _jsonData);

private:
    void initialProperties();
#endif 
};

/*!
 @class IMSDKBindInfo
 @abstract 用户绑定信息类
 */
class IMSDKBindInfo {
public:
    /*!
     @property login_info
     @abstract 登录信息
     */
    IMSDKLoginResult login_info;
    
    /*!
     @property channel_info
     @abstract 渠道信息
     */
    std::vector<IMSDKChannelInfo> channel_info;
#if PLATFORM_ANDROID 
	IMSDKBindInfo();
    IMSDKBindInfo(std::string _jsonData);
#endif 
    IMSDKBindInfo(int code, std::string msg);
    //upgrade error code
    IMSDKBindInfo(int _imsdkCode,int thirdCode);
    IMSDKBindInfo(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg);

};

/*!
 @class IMSDKUserInfo
 @abstract 用户信息类
 */
class IMSDKUserInfo : public IMSDKResult {
public:
    /*!
     @property guid_channel_id
     @abstract 登录 channel id
     */
    int guid_channel_id;
    
    /*!
     @property guid_game_id
     @abstract 游戏 game id
     */
    int guid_game_id;
    
    /*!
     @property guid
     @abstract 用户 guid
     */
    std::string guid;
    
    /*!
     @property guid_open_id
     @abstract 用户 openid
     */
    std::string guid_open_id;
    
    /*!
     @property guid_token
     @abstract 用户登录 token
     */
    std::string guid_token;
    
    /*!
     @property guid_token_expire
     @abstract 用户登录态有效时间（linux 时间戳）
     */
    long long guid_token_expire;
    
    /*!
     @property guid_user_gender
     @abstract 用户性别（0-未定义，1-男，2-女）
     */
    int guid_user_gender;
    
    /*!
     @property guid_user_nick
     @abstract 用户昵称
     */
    std::string guid_user_nick;
    
    /*!
     @property guid_user_birthday
     @abstract 用户出生日期，比如 1987-2-23 11:33:33
     */
    std::string guid_user_birthday;
    
    /*!
     @property guid_user_portrait
     @abstract 用户头像（url）
     */
    std::string guid_user_portrait;
    
    /*!
     @property channel
     @abstract 登录渠道名，比如 Facebook／WeChat/Google/Guest 等
     */
    std::string channel_userid;
    
    /*!
     @class personal
     @abstract 个人信息
     */
    struct {
        /*!
         @property guid
         @abstract guid
         */
        std::string guid;
        
        /*!
         @property nick
         @abstract 昵称
         */
        std::string nick;
        
        /*!
         @property birthday
         @abstract 出生日期，比如 1987-2-23 11:33:33
         */
        std::string birthday;
        
        /*!
         @property portrait
         @abstract 头像（url）
         */
        std::string portrait;
        
        /*!
         @property gender
         @abstract 性别（0-未定义，1-男，2-女）
         */
        int gender;
        
        /*!
         @property country_no
         @abstract 国家编号
         */
        int country_no;
        
        /*!
         @property city_no
         @abstract 城市编号
         */
        int city_no;
        
        /*!
         @property address
         @abstract 地址
         */
        std::string address;
        
        /*!
         @property email
         @abstract 邮箱
         */
        std::string email;
        
        /*!
         @property ip
         @abstract IP 地址
         */
        std::string ip;
        
        /*!
         @property mobile
         @abstract 手机
         */
        std::string mobile;
        
        /*!
         @property telephone
         @abstract 电话
         */
        std::string telephone;
        
        /*!
         @property create_time
         @abstract 创建时间
         */
        long long create_time;
        
        /*!
         @property update_time
         @abstract 修改时间
         */
        long long update_time;
        
        /*!
         @property default_portrait
         @abstract 默认头像数组
         */
        std::vector<std::string> default_portrait;
    } personal;
    
    IMSDKUserInfo(int code, std::string msg);
};

/*!
 @class IMSDKLocationInfo
 @abstract 位置信息类
 */
class IMSDKLocationInfo : public IMSDKResult{
public:
    /*!
     @property guid_open_id
     @abstract 用户 openid
     */
    std::string guid_open_id;
    
    /*!
     @property guid_token
     @abstract 用户 token
     */
    std::string guid_token;
    
    /*!
     @property guid
     @abstract 用户 guid
     */
    std::string guid;
    
    /*!
     @property guid_channel_id
     @abstract 登录 channel id
     */
    int guid_channel_id;
    
    /*!
     @property guid_game_id
     @abstract 登录 game id
     */
    int guid_game_id;
    
    /*!
     @property guid_token_expire
     @abstract 用户登录态有效时间（linux 时间戳）
     */
    long long guid_token_expire;
    
    /*!
     @property guid_user_nick
     @abstract 用户昵称
     */
    std::string guid_user_nick;
    
    /*!
     @property guid_user_gender
     @abstract 用户性别（0-未定义，1-男，2-女）
     */
    int guid_user_gender;
    
    /*!
     @property guid_user_birthday
     @abstract 用户出生日期，比如 1987-2-23 11:33:33
     */
    std::string guid_user_birthday;
    
    /*!
     @property guid_user_portrait
     @abstract 用户头像（url）
     */
    std::string guid_user_portrait;

    /*!
     @property country_no
     @abstract 国家编号
     */
    int country_no;
    
    /*!
     @property country_name
     @abstract 国家名称
     */
    std::string country_name;
    
    /*!
     @property province_no
     @abstract 省份编号
     */
    int province_no;
    
    /*!
     @property province_name
     @abstract 省份名称
     */
    std::string province_name;
    
    /*!
     @property city_no
     @abstract 城市编号
     */
    int city_no;
    
    /*!
     @property city_name
     @abstract 城市名称
     */
    std::string city_name;
    
#if PLATFORM_ANDROID
     IMSDKLocationInfo();
    IMSDKLocationInfo(std::string _jsonData);
    
#endif
};

/*!
 @enum IMSDKShareType
 @abstract 分享类型
 @constant IMSDKShareTextSilence    文字静默分享
 @constant IMSDKShareTextDialog     文字弹框分享
 @constant IMSDKShareLinkSilence    链接静默分享
 @constant IMSDKShareLinkDialog     链接弹框分享
 @constant IMSDKShareImageSilence   图片静默分享
 @constant IMSDKShareImageDialog    图片弹框分享
 */
typedef enum {
    IMSDKShareTextSilence = 0,
    IMSDKShareTextDialog,
    IMSDKShareLinkSilence,
    IMSDKShareLinkDialog,
    IMSDKShareImageSilence,
    IMSDKShareImageDialog,
}IMSDKShareType;

/*!
 @class IMSDKShareRequestInfo
 @abstract 分享内容类（deprecated）
 */
class   IMSDKShareRequestInfo {
public:
    /*!
     @property type
     @abstract 分享类型
     */
    IMSDKShareType type;
    
    /*!
     @property title
     @abstract 分享标题
     */
    std::string title;
    
    /*!
     @property content
     @abstract 分享内容，WeChat link 分享时表示 description
     */
    std::string content;
    
    /*!
     @property link
     @abstract 分享链接
     */
    std::string link;
    
    /*!
     @property thumb_path
     @abstract 分享的缩略图，文件路径或者url，微信分享时大小不能超32k，
     */
    std::string thumb_path;
    
    /*!
     @property image_path
     @abstract 分享的图片，文件路径或者url，微信分享时大小不能超10M，
     */
    std::string image_path;
    
    /*!
     @property extra_json
     @abstract 扩展字段，json格式，用于@好友功能（支持Facebook链接静默和弹窗分享，以及Facebook图片弹窗分享），传值为好友facebook原始id列表，如 "{\"friends\":[\"1643576025872508\", \"1486009061711068\"]}"
     */
    std::string extra_json;
    
    IMSDKShareRequestInfo();
    IMSDKShareRequestInfo(IMSDKShareType _type, std::string _title="", std::string _content="", std::string _link="", std::string _thumb_path="", std::string _image_path="", std::string _extra_json="");
};

/*!
 @class IMSDKFriendRequestInfo
 @abstract 好友请求类
 */
class IMSDKFriendRequestInfo {
public:
    /*!
     @property user
     @abstract 消息接收者
     */
    std::string user;
    
    /*!
     @property type
     @abstract 分享类型
     */
    IMSDKShareType type;
    
    /*!
     @property title
     @abstract 标题
     */
    std::string title;
    
    /*!
     @property content
     @abstract 内容
     */
    std::string content;    // 分享内容，WeChat link 分享时表示 description
    
    /*!
     @property link
     @abstract 链接
     */
    std::string link;
    
    /*!
     @property thumb_path
     @abstract 缩略图，文件路径或者url
     */
    std::string thumb_path;
    
    /*!
     @property image_path
     @abstract 图片，文件路径或者url
     */
    std::string image_path;
    
    /*!
     @property extra_json
     @abstract 扩展字段，json格式
     */
    std::string extra_json;
    
    IMSDKFriendRequestInfo();
    IMSDKFriendRequestInfo(IMSDKShareType _type, std::string _user="", std::string _title="", std::string _content="", std::string _link="", std::string _thumb_path="", std::string _image_path="", std::string _extra_json="");
#if PLATFORM_ANDROID 
	IMSDKFriendRequestInfo(std::string _jsonData);
private:
    void initialProperties();
#endif  
};

/*!
 @class IMSDKFriendInfo
 @abstract 好友个人信息类
 */
class IMSDKFriendInfo{
public:
    /*!
     @property guid_open_id
     @abstract 好友openid
     */
    std::string guid_open_id;
    
    /*!
     @property channel_userid
     @abstract 好友第三方渠道userid
     */
    std::string channel_userid;
    
    /*!
     @property guid_user_nick
     @abstract 好友昵称
     */
    std::string guid_user_nick;
    
    /*!
     @property guid_user_portrait
     @abstract 好友头像
     */
    std::string guid_user_portrait;
    
    /*!
     @property guid_user_gender
     @abstract 好友性别
     */
    int guid_user_gender;
#if PLATFORM_ANDROID  
    IMSDKFriendInfo();
    IMSDKFriendInfo(std::string _jsonData);

private:
    void initialProperties();
#endif 
};

/*!
 @class IMSDKFriendResult
 @abstract 好友信息结果类
 */
class IMSDKFriendResult : public IMSDKResult {
public:
    /*!
     @property guid
     @abstract 用户 guid
     */
    std::string guid;
    
    /*!
     @property guid_open_id
     @abstract 用户 openid
     */
    std::string guid_open_id;
    
    /*!
     @property guid_token
     @abstract 用户 token
     */
    std::string guid_token;
    
    /*!
     @property guid_channel_id
     @abstract 登录 channel id
     */
    int guid_channel_id;
    
    /*!
     @property guid_game_id
     @abstract 登录 game id
     */
    std::string guid_game_id;
    
    /*!
     @property guid_token_expire
     @abstract 用户登录态有效时间（linux 时间戳）
     */
    long long guid_token_expire;
    
    /*!
     @property guid_user_nick
     @abstract 用户昵称
     */
    std::string guid_user_nick;
    
    /*!
     @property guid_user_gender
     @abstract 用户性别（0-未定义，1-男，2-女）
     */
    int guid_user_gender;
    
    /*!
     @property guid_user_birthday
     @abstract 用户出生日期，比如 1987-2-23 11:33:33
     */
    std::string guid_user_birthday;
    
    /*!
     @property guid_user_portrait
     @abstract 用户头像（url）
     */
    std::string guid_user_portrait;
    
    /*!
     @property channel_userid
     @abstract 第三方登录渠道用户 id
     */
    std::string channel_userid;
    
    /*!
     @property count
     @abstract 好友数量
     */
    int count;
    
    /*!
     @property friends
     @abstract 好友信息数组
     */
    std::vector<IMSDKFriendInfo> friends;
    
    IMSDKFriendResult();
    IMSDKFriendResult(int _retCode, std::string _retMsg);
    
    //upgrade error code
public:
    IMSDKFriendResult(int _imsdkRetCode, int _thirdRetCode);
    IMSDKFriendResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg);

#if PLATFORM_ANDROID
	IMSDKFriendResult(std::string _jsonData);
private:
    void initialProperties();
#endif  
};

/*!
 @class IAPPayRequestInfo
 @abstract IAP请求结构体（可参考Midas说明:http://unipay.boss.com/uniphpwiki/index.php?title=RequestInfo%E5%B1%9E%E6%80%A7%E8%A1%A8）
 */
typedef struct
{
    /*!
     @property openId
     @abstract 用户帐号id，对应登录返回的guid_open_id
     */
    std::string openId;
    
    /*!
     @property openKey
     @abstract 用户账户token，校验登录态则填对登录返回的guid_token，否则不传空就行，建议传"OpenKey"
     */
    std::string openKey;
    
    /*!
     @property session_id
     @abstract 用户账户类型，这里固定为"hy_gameid"
     */
    std::string session_id;
    
    /*!
     @property session_type
     @abstract session类型，校验登录态则填"st_overseas"，否则填"st_dummy"
     */
    std::string session_type;
    
    /*!
     @property payItem
     @abstract 支付信息 <br />
        1.如果应用使用道具购买类支付模式，该参数由应用方按照“物品ID*单价（单位“角”）*数量”定义 <br />
        2.如果应用使用包月类支付模式，传开通包月的月数（QQ会员这类） <br />
        3.如果游戏币支付模式，传充值游戏币的个数 <br />
        4.如果应用使用月卡类支付模式，传开通月卡天数
     */
    std::string payItem;
    
    /*!
     @property productId
     @abstract 苹果的物品id，在Midas管理端配置
     */
    std::string productId;
    
    /*!
     @property pf
     @abstract 平台来源，pf格式：平台字段(IEG_iTOP)-注册渠道-系统平台-安装渠道-登录渠道-GameID-OpenID-业务标识 <br />
        eg: IEG_iTOP-2001-iap-2011-FB-11-1000043-XD
     */
    std::string pf;
    
    /*!
     @property pfKey
     @abstract 支付密钥串，这里固定为"pfkey"
     */
    std::string pfKey;
    
    /*!
     @property isDepositGameCoin
     @abstract 是否是托管游戏币
     */
    bool isDepositGameCoin;
    
    /*!
     @property productType
     @abstract 苹果物品的类型<br />
        0.消费类产品，比如游戏币购买
        1.非消费类产品
        2.包月+自动续费
        3.免费
        4.包月+非自动续费
     */
    int productType;
    
    /*!
     @property zoneId
     @abstract 账户分区ID <br />
        应用如果没有分区，传zoneid=1 <br />
        若游戏为支持角色，zoneId需要传分区ID_角色ID
     */
    std::string zoneId;
    
    /*!
     @property varItem
     @abstract 业务的扩展字段
     */
    std::string varItem;
    
    /*!
     @property billno
     @abstract 订单号
     */
    std::string billno;
    
    /*!
     @property transactionIdentifier
     @abstract 票据编号
     */
    std::string transactionIdentifier;
    
    /*!
     @property isReprovide
     @abstract 是否补发货
     */
    bool isReprovide;
} IAPPayRequestInfo; 


/*!
 @class IMSDKHelpFeedbackResult
 @abstract 最新未读反馈信息类
 */
class IMSDKHelpFeedbackResult: public IMSDKResult {
public:
    /*!
     @property amount
     @abstract 未读反馈信息数
     */
    int amount;
    
    IMSDKHelpFeedbackResult();
    IMSDKHelpFeedbackResult(int _retCode);
    IMSDKHelpFeedbackResult(int _retCode, std::string _retMsg);
    IMSDKHelpFeedbackResult(int _imsdkRetCode, int _thirdRetCode);
    IMSDKHelpFeedbackResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg);
    
    std::string toJsonString();
protected:
    IMSDKJson fillJsonObject();

#if PLATFORM_ANDROID    
	IMSDKHelpFeedbackResult(std::string _jsonData);
private:
    void initialProperties();
#endif
};

/*!
 @class IMSDKHelpCenterResult
 @abstract HelpCenter通用返回结构体
 */
class IMSDKHelpCenterResult: public IMSDKResult {
public:
    int state;         // 状态码
    IMSDKHelpCenterResult();
    IMSDKHelpCenterResult(int _retCode);
#if PLATFORM_ANDROID 
    IMSDKHelpCenterResult(std::string _jsonData);
#endif
    IMSDKHelpCenterResult(int _retCode, std::string _retMsg);
    IMSDKHelpCenterResult(int _imsdkRetCode, int _thirdRetCode);
    IMSDKHelpCenterResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg);
    
    std::string toJsonString();
protected:
    IMSDKJson fillJsonObject();
};

/*!
 @class KVPair
 @abstract Key-Value对结构体
 */
typedef struct {
    /*!
     @property key
     @abstract key of value
     */
    std::string key;
    
    /*!
     @property value
     @abstract value of key
     */
    std::string value;
} KVPair;

/*!
 @class IMSDKBaseStyle
 @abstract IMSDK Json 序列化基类
 */
class IMSDKBaseStyle {
    
public:
    /*!
     @abstract  将对象成员变量值转换为Json字符串
     @result    Json字符串
     */
    virtual std::string toJsonString() {
        return "";
    };
    
    /*!
     @abstract  根据Json字符串创建类对象并赋值成员变量
     @param     jsonString 序列化字符串
     @result    IMSDKBaseStyle 对象
     */
    virtual IMSDKBaseStyle& toBaseStyle(std::string &jsonString) {
        return *this;
    };
};

/*!
 @class IMSDKNoticePicInfo
 @abstract Notice中图片相关信息
 */
class IMSDKNoticePicInfo {
public:
    
    /*!
     *  @brief 公告id
     */
    int noticeId;
    
    /*!
     *  @brief 图片url：网络路径（当本地没有图片时），本地图片路径
     */
    std::string picUrl;
    
    /*!
     *  @brief 1:横竖屏 2:竖屏 3:横屏
     */
    int screenDir ;
    
    /*!
     *  @brief 图片的哈希值，用于校验图片是否被篡改
     */
    std::string mPicHash;
    
    /*!
     *  @brief 图片的标题
     */
    std::string picTitle;
    
    /*!
     *  @brief 图片尺寸大小
     */
    std::string picSize;
    
    /*!
     *  @brief 附加字段
     */
    std::string extraJson;
    std::string toJsonString();

#if PLATFORM_ANDROID  
public:
    IMSDKNoticePicInfo();
    IMSDKNoticePicInfo(std::string _jsonData);

private:
    void initialProperties();
#endif 
};

/*!
 @class IMSDKNoticeInfo
 @abstract 加载公告时返回公告信息
 */
class IMSDKNoticeInfo{
public:
    /*!
     *  @brief 状态码用以标记 展示公告流程 1.展示公告 2.点击公告内容 3.关闭公告
     */
    std::string stateCode;
    
    /*!
     *  @brief 屏幕名称
     */
    std::string screenName;
    
    /*!
     *  @brief 公告id
     */
    int noticeId;
    
    /*!
     *  @brief appid
     */
    std::string appId;
    
    /*!
     *  @brief 用户open id
     */
    std::string openId;
    
    /*!
     *  @brief 公告跳转链接
     */
    std::string url;
    
    /*!
     *  @brief 公告展示的场景，管理端后台配置
     */
    int scene ;
    
    /*!
     *  @brief 公告有效期开始时间
     */
    long startTime ;
    
    /*!
     *  @brief 公告有效期结束时间
     */
    long endTime ;
    
    /*!
     *  @brief 公告更新时间
     */
    long updateTime ;
    
    /*!
     *  @brief 公告内容类型 1:文本公告 2:图片公告 3:网页公告
     */
    int contentType ;
    
    /*!
     *  @brief 公告的分类，登陆前的强制更新公告、登陆后的普通公告等等
     */
    std::string category ;
    
    /*!
     *  @brief 公告标题
     */
    std::string title ;
    
    /*!
     *  @brief 公告内容
     */
    std::string content ;
    
    /*!
     *  @brief 序列号，表示公告的顺序
     */
    int sequenceId ;
    
    /*!
     *  @brief 公告语种
     */
    std::string language ;
    
    /*!
     *  @brief 发布版本号
     */
    std::string publishVersion;
    
    /*!
     *  @brief 公告图片
     */
    std::vector<IMSDKNoticePicInfo> pics;
    
    /*!
     *  @brief 公告weburl
     */
    std::string contentWebUrl ;
    
    /*!
     *  @brief 扩展
     */
    std::string extraJson ;
    
public:
    
    IMSDKNoticeInfo();
#if PLATFORM_ANDROID 
    IMSDKNoticeInfo(std::string _jsonData);
#endif 
    
    /*!
     *  @brief 便于将结果对象转换成json,传至unity层
     *
     *  @return json字符串
     */
    std::string toJsonString();
    
protected:
    // 返回存储属性的json对象
    IMSDKJson fillJsonObject();
    
private:
    void initialProperties();
    
};  

/*!
@class IMWebViewStatusResult
@abstract IMSDK webview操作回调结果类
*/
class IMWebViewStatusResult : public IMSDKResult {

public:
	/*!
	*  @brief action状态码, 1.打开浏览器(暂未实现) 2.关闭浏览器 3.js 调用Objective-c函数
	*/
	int stateCode;

	/*!
	*  @brief 将结果对象转换成标准json字符串
	*
	*  @return json字符串
	*/
	IMWebViewStatusResult();
	IMWebViewStatusResult(std::string _jsonData);

	std::string toJsonString();
};


/*!
 @class IMSDKNoticeResult
 @abstract 加载公告时返回公告结果类
 */
class IMSDKNoticeResult: public IMSDKResult{
public:
    /*!
     *  @brief notice的数量
     */
    int number;
    
    /*!
     *  @brief notice列表
     */
    std::vector<IMSDKNoticeInfo> list;
	
public:
    IMSDKNoticeResult();
#if PLATFORM_ANDROID 
    IMSDKNoticeResult(std::string _jsonData);
#endif 
    IMSDKNoticeResult(int _imsdkRetCode, int _thirdRetCode);
    IMSDKNoticeResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg);
public:
    
    /*!
     *  @brief 便于将结果对象转换成json,传至unity层
     *
     *  @return json字符串
     */
    std::string toJsonString();
    
protected:
    // 返回存储属性的json对象
    IMSDKJson fillJsonObject();
    
private:
    void initialProperties();
    
};

//#pragma mark - Auth

/*!
 @class IMSDKAuthSNSInfo
 @abstract 绑定的平台账号信息
 */
class IMSDKAuthSNSInfo {
    
public:
    
    /*!
     *  @brief 渠道ID
     */
    int channelId;
    
    /*!
     *  @brief 用户ID
     */
    std::string openId;
    
    /*!
     *  @brief 用户名
     */
    std::string userName;
    
    /*!
     *  @brief 用户性别
     */
    int gender;
    
    /*!
     *  @brief 用户头像链接
     */
    std::string pictureUrl;
    
public:
    
    /*!
     *  @brief 将结果对象转换成json
     *
     *  @return json字符串
     */
    std::string toJsonString();
 
protected:
	// 返回存储属性的json对象
	IMSDKJson fillJsonObject();

public:
    IMSDKAuthSNSInfo();

#if PLATFORM_ANDROID   
    IMSDKAuthSNSInfo(std::string _jsonData); 
private:
    void initialProperties();
#endif
};


/*!
@class IMSDKStatChannelInterface
@abstract 数据上报渠道初始化结构体
*/
typedef struct
{   /*!
	@property eventReportChannels
	@abstract 自定义事件上报渠道
	*/
	std::vector<std::string> eventReportChannels;

	/*!
	@property purchaseReportChannels
	@abstract 购买行为上报渠道
	*/
	std::vector<std::string> purchaseReportChannels;

	/*!
	@property trackEventChannels
	@abstract 自定义事件追踪渠道
	*/
	std::vector<std::string> trackEventChannels;

	/*!
	@property trackPageChannels
	@abstract 页面统计渠道
	*/
	std::vector<std::string> trackPageChannels;

	/*!
	@property testSpeedChannels
	@abstract 网络测速渠道
	*/
	std::vector<std::string> testSpeedChannels;

	/*!
	@property exceptionReportChannels
	@abstract 异常上报渠道
	*/
	std::vector<std::string> exceptionReportChannels;

	/*!
	@property crashReportChannels
	@abstract 崩溃上报渠道
	*/
	std::vector<std::string> crashReportChannels;
} IMSDKStatChannelInterface;

/*!
@class IMSDKWebViewTicketResult
@abstract WebView票据结果类
*/
class IMSDKWebViewTicketResult : public IMSDKResult {
public:
	/*!
	@property ticket
	@abstract 登录票据
	*/
	std::string ticket;

	/*!
	@property domain
	@abstract 服务器域名，比如 sdkapi-beta.itop.qq.com
	*/
	std::string domain;
	IMSDKWebViewTicketResult();
	IMSDKWebViewTicketResult(std::string _jsonData);
	IMSDKWebViewTicketResult(int _retCode, std::string _retMsg);

	/*!
	*  @brief 便于将结果对象转换成json,传至unity层
	*
	*  @return json字符串
	*/
	std::string toJsonString();

protected:
	IMSDKJson fillJsonObject();

private:
	void initialProperties();
};

/*!
 @class IMSDKAuthResult
 @abstract IMSDK Auth结构体
 */
class IMSDKAuthResult : public IMSDKResult {
    
public:
    
    /*!
     *  @brief 渠道ID
     */
    int channelId;
    
    /*!
     *  @brief 游戏Id
     */
    int gameId;
    
    /*!
     *  @brief 游戏账号id
     */
    std::string openId;
    
    /*!
     *  @brief 内部Token标识，在后台系统通行的key
     */
    std::string innerToken;
    
    /*!
     *  @brief 设备标示
     */
    std::string deviceId;
    
    /*!
     *  @brief Token有效期，linux时间戳
     */
    long long tokenExpireTime;
    
    /*!
     *  @brief 是否首次登陆
     */
    bool isFirstLogin;
    
    /*!
     *  @brief 当前账户已绑定的SNS账号信息
     */
    std::vector<IMSDKAuthSNSInfo> snsInfoVec;
    
/**********************************************
* those five properties is decrepted in this veiosn
*
***********************************************/
    
    /*!
     *  @brief 全球统一用户标识
     */
//        std::string guid;
    
    /*!
     *  @brief 用户名
     */
//    std::string userName;
    
    /*!
     *  @brief 头像链接
     */
//    std::string pictureUrl;
    
    /*!
     *  @brief 性别(int) 0未定义,1男,2女2
     */
//    int gender;
    
    /*!
     *  @brief 出生日期(1987-2-23 11:33:33)
     */
//    std::string birthday; 
    
public:
    /*!
     *  @brief 便于将结果对象转换成json,传至unity层
     *
     *  @return json字符串
     */
    std::string toJsonString();
    
protected:
    // 返回存储属性的json对象
    IMSDKJson fillJsonObject();

public:
	IMSDKAuthResult();
	IMSDKAuthResult(int _imsdkRetCode, int _thirdRetCode);
	IMSDKAuthResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg);

#if PLATFORM_ANDROID 
	IMSDKAuthResult(std::string _jsonData);
private:
    void initialProperties();
#endif 
};

/*!
 @class IMSDKAuthConnectResult
 @abstract 第三方平台挂靠或恢复账号的结果类
 */
class IMSDKAuthConnectResult: public IMSDKResult {
    
public:
    
    /*!
     *  @brief 恢复进度码确认码
     */
    std::string confirmCode;
    
    /*!
     *  @brief sns之前对应的账户openid，用来给客户端展示进度
     */
    std::string openId;
    
    /*!
     *  @brief 目标平台标识
     */
    int channelId;
    
    /*!
     *  @brief 用户名
     */
    std::string userName;
    
    /*!
     *  @brief 用户头像
     */
    std::string pictureUrl;
    
    /*!
     *  @brief 用户性别。0未定义,1男,2女
     */
    int gender;
    
    /*!
     *  @brief 便于将结果对象转换成json,传至unity层
     *
     *  @return json字符串
     */
    std::string toJsonString(); 

protected:
    // 返回存储属性的json对象
    IMSDKJson fillJsonObject(); 

public:
	IMSDKAuthConnectResult();
	IMSDKAuthConnectResult(int _imsdkRetCode, int _thirdRetCode);
	IMSDKAuthConnectResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg); 

#if PLATFORM_ANDROID   
	IMSDKAuthConnectResult(std::string _jsonData);
private:
	void initialProperties();
#endif
};

/*!
 @class IMSDKAuthMigrateResult
 @abstract 第三方平台挂靠或恢复账号的结果类
 */
class IMSDKAuthMigrateResult: public IMSDKResult {
    
public:
    
    /*!
     *  @brief IMSDK平台迁移码
     */
    std::string migrateCode;
    
    /*!
     *  @brief 迁移码有效时长，单位秒
     */
    int validTime;
    
    /*!
     *  @brief 当前账户已绑定的SNS账号信息
     */
    std::vector<IMSDKAuthSNSInfo> snsInfoVec;
    
    /*!
     *  @brief 便于将结果对象转换成json,传至unity层
     *
     *  @return json字符串
     */
    std::string toJsonString(); 
    
protected:
    // 返回存储属性的json对象
    IMSDKJson fillJsonObject();

public:
	IMSDKAuthMigrateResult();
	IMSDKAuthMigrateResult(int _imsdkRetCode, int _thirdRetCode);
	IMSDKAuthMigrateResult(int _imsdkRetCode, std::string _imsdkRetMsg, int _thirdRetCode, std::string _thirdRetMsg);

#if PLATFORM_ANDROID   
	IMSDKAuthMigrateResult(std::string _jsonData);
private:
    void initialProperties();
#endif
};

//#pragma mark - push

class IMSDKLocalNotification {
public:
    
    /*!
     *  @brief 推送触发的时间，时间戳
     */
    long long fireTime;
    
    /*!
     *  @brief 推送重复发送周期。 1-分钟，2-小时，3-天，4-星期，5-月，6-年，默认是0代表不重复。
     *  如果设置此属性, 那么调度池不会用完释放改推送！需要手动删除通知对象
     */
    int repeatTpye;
    
    /*!
     *  @brief 推送的内容
     */
    std::string content;
    
    /*!
     *  @brief 设置App的角标，如果为-1，则不改变。
     */
    int badge;
    
    /*!
     *  @brief 推送的右侧按钮的文字，默认为“查看”或者“启动”。设置提醒的按钮文字 / 锁屏时界面底部的闪光文字（滑动来...）
     */
    std::string alertAction;
    
    /*!
     *  @brief 自定义的用户信息，删除推送时需指定key值。
     */
    std::map<std::string, std::string> userInfo;



#if PLATFORM_ANDROID
    int type;
    std::string title;
    int actionType;
    std::string actionContent;
    bool isRinging;
    std::string ringRaw;
    bool isVibrate;
    int light;
    std::string iconRes;
    std::string apkDownloadUrl;
    long builderId;
    int styleId;
#endif




    
    /*!
     *  @brief 便于将结果对象转换成json,传至unity层
     *
     *  @return json字符串
     */
//    std::string toJsonString();
    
    IMSDKLocalNotification();

//protected:
//    // 返回存储属性的json对象
//    IMSDKJson fillJsonObject();
};

//#pragma mark - IMSDKAccount
/*!
 @class IMSDKAccount
 @abstract AccountManager中的登录态信息类
 */
class IMSDKAccount {
public:
    /*!
     *  @brief 账号信息(邮箱账号或者手机号)
     */
    std::string account;
    
    /*!
     *  @brief 账号类型, IMSDKAccountType, 1 Email , 2 Mobile , ...
     */
    int         accountType;
    
    /*!
     *  @brief 账号ID
     */
    std::string uid;
    
    /*!
     *  @brief 登录态Token
     */
    std::string token;
    
    /*!
     *  @brief 扩展json字段
     */
    std::string extraJson;
public:
    IMSDKAccount();
    IMSDKAccount(std::string _account, int _accountType);
    IMSDKAccount(std::string _account, int _accountType, std::string _uid, std::string _token);
public:
    /*!
     *  @brief 便于将结果对象转换成json,传至unity层
     *
     *  @return json字符串
     */
    std::string toJsonString();
protected:
    IMSDKJson fillJsonObject();
};

/*!
 @class IMSDKAccountVerifyCodeInfo
 @abstract AccountManager中的验证码信息类
 */
class IMSDKAccountVerifyCodeInfo {
public:
    /*!
     *  @brief 账号信息(邮箱账号或者手机号)
     */
    std::string account;
    
    /*!
     *  @brief 账号类型, IMSDKAccountType, 1 Email , 2 Mobile , ...
     */
    int         accountType;
    
    /*!
     *  @brief 手机区号(只针对手机账号)
     */
    std::string areaCode;
    
    /*!
     *  @brief 校验码的MD5
     */
    std::string verifyCode;
    
    /*!
     *  @brief 后台返回的时间戳
     */
    int         timeStamp;
    
    /*!
     *  @brief 扩展json字段
     */
    std::string extraJson;
public:
    IMSDKAccountVerifyCodeInfo();
    IMSDKAccountVerifyCodeInfo(std::string _verifyCode);
    IMSDKAccountVerifyCodeInfo(std::string _account, int _accountType, std::string _areaCode, std::string _verifyCode);
public:
    std::string toJsonString();
protected:
    IMSDKJson fillJsonObject();
};  
#endif
