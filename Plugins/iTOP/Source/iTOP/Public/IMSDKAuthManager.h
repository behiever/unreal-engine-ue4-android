/*!
 @header    IMSDKAuthManager.h
 @abstract  IMSDK Auth鉴权处理类声明头文件
 @author    Created by Hillson Song on 7/26/16.
 @copyright Copyright © 2016 Tencent. All rights reserved.
 */

#ifndef IMSDKAuthManager_h
#define IMSDKAuthManager_h

#include "IMSDKComm.h"
#include "IMSDKJson.h"

/*!
 *  @brief IMSDK Auth模块授权、强关联渠道恢复、迁移等功能的回调。
 *
 *  @param authResult 回调函数
 */
typedef void (*IMSDKAuthCallBack)(IMSDKAuthResult authResult);

/*!
 *  @brief IMSDK挂靠渠道功能回调
 *
 *  @param authResult 回调函数
 */
typedef void (*IMSDKConnectCallBack)(IMSDKAuthConnectResult authResult);

/*!
 *  @brief IMSDK迁移码功能回调
 *
 *  @param migrateResult 回调函数
 */
typedef void (*IMSDKMigrateCallBack)(IMSDKAuthMigrateResult migrateResult);


/*!
 @class IMSDKAuthManager
 @abstract IMSDK Auth鉴权处理类
 */
class IMSDKAuthManager {
    
public:
    
    /*!
     *  @brief 获取IMSDKAuthManager处理单例
     *
     *  @return 单例对象
     */
    static IMSDKAuthManager* getInstance();
    
    /*!
     *  @brief 功能模块初始化。
     */
    void initailize();
    
    /*!
     *  @brief 获取授权结果
     *
     *  @return 授权结果
     */
    IMSDKAuthResult getAuthResult();
    
    /*!
     *  @brief 授权
     *  @param callback 授权回调
     */
    void auth(IMSDKAuthCallBack callback);
    
    /*!
     *  @brief 挂靠第三方渠道
     *
     *  @param callback 挂靠回调
     *  @param channel 渠道名，例如GameCenter, Facebook
     *  @param permissions 第三方渠道登录权限，默认为空
     *  @param confirmCode 通过确认码进行绑定
     */
    void connect(std::string channel, IMSDKConnectCallBack callback, const std::vector<std::string> &permissions = std::vector<std::string>(), std::string confirmCode = "");
    
    /*!
     *  @brief 恢复进度（弱关联渠道)
     *
     *  @param callback 恢复进度回调
     *  @param confirmCode 确认时的挂载码，选填参数。<br>
     *  connect失败时，会返回confirmCode（thirdRetCode为2）。<br>
     *  此时直接调用reconnect接口，可以不传confirmCode，此接口会默认读取connect返回的确认码。
     */
    void reconnect(IMSDKCallBack callback, std::string confirmCode = "");
    
    /*!
     *  @brief 恢复进度（强关联渠道）
     *
     *  @param callback 恢复进度回调
     *  @param confirmCode 确认时的挂载码，选填参数。<br>
     *  connect失败时，会返回confirmCode（thirdRetCode为3）。<br>
     *  此时直接调用restore接口，可以不传confirmCode，此接口会默认读取connect返回的确认码。
     */
    void restore(IMSDKAuthCallBack callback, std::string confirmCode = "");
    
    /*!
     *  @brief 无登录态恢复账号
     *
     *  @param channel  恢复账号的渠道
     *  @param callback 恢复账号回调
     */
    void recover(std::string channel, IMSDKAuthCallBack callback, const std::vector<std::string> &permissions = std::vector<std::string>());
    
    /*!
     *  @brief 获取当前当前账号已绑定的渠道信息
     *
     *  @param callback 查询回调
     */
    void getConncetInfo(IMSDKAuthCallBack callback);
    
    /*!
     *  @brief 获取迁移码
     *
     *  @param callback 回调
     */
    void getMigrateCode(IMSDKMigrateCallBack callback);
    
    /*!
     *  @brief 账号迁移。需要确保彼此没有挂载过相互渠道的账户（如Android设备下的账户没有挂载过GameCenter渠道的账户， iOS设备下的账户没有挂载过Google Play渠道的账户）；<br>
     *  迁移时，舍弃当前设备的openid， 而将当前设备及对应自动登录的sns渠道（如果当前设备是ios则GameCenter渠道，如果当前设备是android则为Google Play渠道）账户挂载到迁移过来的openid上。
     *
     *  @param callback 恢复进度回调
     *  @param code 迁移码，可以不传，此接口会默认读取getMigrateCode返回的迁移码。
     */
    void migrate(IMSDKAuthCallBack callback, std::string code = "");
    
    /*!
     *  @brief  查询迁移Code信息
     *
     *  @param callback 查询回调
     *  @param code 迁移码，可以不传，此接口会默认读取getMigrateCode返回的迁移码。
     */
    void getMigrateInfo(IMSDKMigrateCallBack callback, std::string code = "");
    
    /*!
     *  @brief 登出指定渠道，方便切换该渠道账号
     *
     *  @param channel 要登出的渠道，例如GameCenter, Facebook
     
     *  @param callback  登出操作回调
     */
    void signOut(std::string channel ,IMSDKCallBack callback);
    
    /*!
     *  @brief 客户端到平台Server断开账号关联
     *
     *  @param channel 要断开关联的渠道，例如GameCenter, Facebook

     *  @param callback  断开操作回调
     */
    void disconnect(std::string channel ,IMSDKCallBack callback);

    /*!
     *  @brief 客户端到平台Server删除设备对应账号
     *
     *  @param callback 删除回调
     */
    void deleteDeviceAccount(IMSDKCallBack callback);
    
    /*!
     *  @brief 客户端到平台Server删除登录态Openid对应的所有账号
     *
     *  @param callback 删除回调
     */
    void deleteAllAccount(IMSDKCallBack callback);
    
private:
    static IMSDKAuthManager* m_authInst;
    
    std::string m_confirmCode;
    
    std::string m_migrateCode;
    
    void connectRequest(std::string query, std::string channelId, std::string extraJson, IMSDKConnectCallBack callback, std::string channel="", std::string uid="");
    
    IMSDKAuthManager();
    
    virtual ~IMSDKAuthManager();

#ifdef ANDROID
private:
	JavaVM* m_pVM;

public:
	void init(JavaVM* pVM);
	void setVM(JavaVM* pVM);
	JavaVM* getVM();
	IMSDKAuthResult getAuthResultFromJava(JNIEnv * env, jclass jclassResult, jobject jobjectResult); //解析Java侧返回的AuthResult数据，并填充到C++侧的对应类
#endif
    
};

#endif /* IMSDKAuthManager_h */
