/*!
 *  @header    IMSDKPushManager.h
 *  @abstract  推送类
 *  @author    Created by brightwan on 15/6/30.
 *  @copyright Copyright (c) 2015年 Tencent. All rights reserved.
 */

#ifndef __IMSDK__IMSDKPushManager__
#define __IMSDK__IMSDKPushManager__
 
#include "IMSDKPushListener.h"

/*!
 *  @class IMSDKPushManager
 *
 *  @abstract 推送类
 */
class IMSDKPushManager {
private:
    static IMSDKPushManager* m_pInst;
    const IMSDKPushListener* m_pPushListener;

	int listenerTag;
	std::map<int, const IMSDKPushListener*> *listenerMap;
    std::string m_channel;
    
    IMSDKPushManager();
    virtual ~IMSDKPushManager();
    
public:
    
    /*!
     *  @brief 获取推送模块处理类单例
     *
     *  @return 单例
     */
    static IMSDKPushManager* getInstance();
    
    /*!
     *  @brief 设置推送回调
     *
     *  @param pPushListener 推送回调处理实例对象
     */
    void setPushListener(const IMSDKPushListener* pPushListener);
    
    /*!
     *  @brief 设置推送渠道（默认XG，信鸽）
     *
     *  @param channel 渠道名字
     */
    void setChannel(std::string channel);
    
    /*!
     *  @brief 获取当前渠道。
     *
     *  @return 渠道名字
     */
    std::string getChannel();
    
    /*!
     *  @brief 获取当前回调处理实例
     *
     *  @return 实例
     */
    const IMSDKPushListener* getPushListener() const;
    
    /*!
     *  @brief 注册指定渠道推送模块，包括注销设备后，重新注册设备的情况
     *
     */
    void registerPush();
    
    /*!
     *  @brief 注册指定渠道推送模块，包括注销设备后，重新注册设备的情况
     *
     *  @param account 用户的别名（账户）。上报用户的帐号（别名），以便支持按帐号（别名）推送。
     */
    void registerPush(std::string account);
    
    /*!
     * @brief 注销设备,此台设备不接收推送
     */
    void unregisterPush();
    
    /*!
     *  @brief 设置标签，针对不同用户设置不同标签
     *
     *  @param tag 标签内容
     */
    void setTag(std::string tag);
    
    /*!
     *  @brief 设置标签，针对不同用户设置不同标签
     *
     *  @param tagList   标签列表
     */
    void setTag(std::vector<std::string> tagList);
    
    /*!
     *  @brief 删除标签，删除设置过的标签，要求用户必须处于登陆状态
     *
     *  @param tag       设置过的标签
     */
    void delTag(std::string tag);
    
    /*!
     *  @brief 删除标签，删除设置过的标签，要求用户必须处于登陆状态
     *
     *  @param tagList   设置过的标签列表
     */
    void delTag(std::vector<std::string> tagList);
    
    /*!
     *  @brief 新增本地推送
     *  本地通知的数量是有限制的，最近的本地通知最多只能有64个，超过将被系统忽略
     *
     *  @param notification 本地推送对象
     */
    void addLocalNotification(IMSDKLocalNotification notification);
    
    /*!
     *  @brief 删除指定本地推送
     *
     *  @param key 设置通知参数时userInfo指定的key
     */
    void deleteLocalNotification(std::string key);
    
    /*!
     *  @brief 清空全部本地推送
     */
    void clearLocalNotification();

#ifdef ANDROID
private:
    JavaVM* m_pVM;
    void activeNotify();
    
public:
    void init(JavaVM* pVM);
    void setVM(JavaVM* pVM);
    JavaVM* getVm();

	const std::map<int, const IMSDKPushListener*> getListenerMap() {
		return *listenerMap;
	}
	 
#endif
};

#endif /* defined(__IMSDK__IMSDKPushManager__) */
