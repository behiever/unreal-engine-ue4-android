/*!
 *  @header    IMSDKLoginManager.h
 *  @abstract  登录处理类
 *  @author    Created by brightwan on 15-5-21.
 *  @copyright Copyright (c) 2015年 Tencent. All rights reserved.
 */

#ifndef IMSDK_IMSDKLoginManager_h
#define IMSDK_IMSDKLoginManager_h
 
#include "IMSDKLoginListener.h"

/*!
 *  @class IMSDKLoginManager
 *  @abstract 登录调用类
 */
class IMSDKLoginManager {
private:
    static IMSDKLoginManager* m_pInst;
    const IMSDKLoginListener* m_LoginListener;
    std::string m_channel;
    std::string m_reportChannel;
    std::string m_logintype;
    std::string m_extraJson;

    int listenerTag;
    std::map<int,const IMSDKLoginListener*> *listenerMap; 
    IMSDKLoginManager();
    virtual ~IMSDKLoginManager();
    
public:
    /*!
     *  @abstract 获取登录类单例
     *
     *  @return IMSDKLoginManager单例
     */
    static IMSDKLoginManager* getInstance();
    
    /*!
     *  @abstract 设置登录回调
     *
     *  @param pLoginListener 登录回调
     */
    void setLoginListener(const IMSDKLoginListener* pLoginListener);
    
    /*!
     *  @abstract 获取登录回调指针
     *
     *  @return 登录回调指针
     */
    const IMSDKLoginListener* getLoginListener() const;
    
    /*!
     *  @abstract 设置登录渠道
     *
     *  @param channel 渠道名称（Facebook, WeChat, GameCenter, Guest...）
     */
    void setChannel(const std::string channel);
    
    /*!
     *  @abstract 获取登录渠道
     *
     *  @return 登录渠道
     */
    const std::string getChannel();
    
    /*!
     *  @abstract 设置登录类型
     *
     *  @param loginType 登录类型，每个渠道的类型不同，参见渠道说明
     */
    void setLoginType(std::string loginType);
    
    /*！
     *  @abstract 获取登录类型
     *
     *  @return 登录类型
     */
    const std::string getLoginType();
    
    /*！
     *  @abstract 自动登录，以最近一次登录渠道重新登录
     */
    void autoLogin();
    
    /*!
     *  @abstract 快速登录，以最近一次登录态返回
     */
    void quickLogin();
    
    /*!
     *  @abstract 登录指定渠道
     *
     *  @param permissions 权限
     *  @param needGuid    是否需要获取guid平台数据
     */
    void login(const std::vector<std::string> *permissions = NULL, bool needGuid = true);
    
    /*!
     *  @abstract 检测第三方渠道账户对应的 iMSDK openID 是否存在；如果存在则登录，否则返回错误
     *
     *  @param permissions 权限
     *  @param needGuid    是否需要获取guid平台数据
     */
    void checkAndLogin(const std::vector<std::string> *permissions = NULL, bool needGuid = true);
    
    /*!
     *  @abstract 通过确认码完成登录
     *
     *  @param code 登录确认码；checkAndLogin 返回错误的确认码
     */
    void loginWithConfirmCode(std::string code);
    
    /*!
     *  @abstract 判断当前渠道是否登录并且登录态是否有效
     *
     *  @return 是否登录并且登录态有效
     */
    bool isLogin();
    
    /*!
     *  @abstract 登出
     */
    void logout();
    
    /*!
     *  @abstract 返回当前 channel 的应用是否安装
     *
     *  @return 是否安装
     */
    bool isChannelInstalled();
    
    /*!
     *  @abstract 返回当前 channel 是否支持 SDK API接口
     *
     *  @return 是否支持。true 表示支持该渠道 SDK API，false 表示不支持
     */
    bool isChannelSupportApi();
    
    /*!
     *  @abstract 绑定账户。将当前渠道账户绑定到目标渠道，拉起目标渠道登录
     *  @discussion channel 不能为 Guest
     *
     *  @param channel       目标渠道
     *  @param subChannel    登录子渠道，同 loginType
     *  @param extraJson     扩展字段
     */
    void bind(std::string channel, std::string subChannel = "", std::string extraJson = "{}");
    
    /*!
     *  @abstract 获取当前登录态信息
     *
     *  @return 登录结果类
     */
    const IMSDKLoginResult getLoginResult();
    
    /*!
     *  @abstract 获取当前登录账号的绑定信息
     */
    void getBindInfo();
    
    /*!
     *  King 登录模块使用
     *  @abstract 设置扩展参数
     *
     *  @param extraJson 扩展 JSON 数据
     */
    void setExtraJson(std::string extraJson);
    
    /*!
     *  @abstract 获取扩展字段
     *
     *  @return 扩展字段
     */
    std::string getExtraJson();

    
#ifdef ANDROID
private:
    JavaVM* m_pVM;
    
public:
    void init(JavaVM* pVM); 
    IMSDKLoginResult getLoginResultFromJava(JNIEnv * env, jclass jclassResult, jobject jobjectResult);//解析Java侧返回的LoginResult数据，并填充到C++侧的对应类
    const std::map<int, const IMSDKLoginListener*> getListenerMap(){
        return *listenerMap;
    }
#endif 
};
#endif
