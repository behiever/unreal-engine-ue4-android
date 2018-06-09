/*!
 *  @header    IMSDKFriendManager.h
 *  @abstract  好友操作类
 *  @author    Created by Hillson Song on 7/3/15.
 *  @Copyright (c) 2015 Tencent. All rights reserved.
 */

#ifndef IMSDK_IMSDKFriendManager_h
#define IMSDK_IMSDKFriendManager_h
  
#include "IMSDKFriendListener.h"

/*!
 *  @class IMSDKFriendManager
 *
 *  @abstract 好友功能模块处理类，包括向好友发消息、邀请好友、拉取好友列表、分享等
 */
class IMSDKFriendManager{
private:
    static IMSDKFriendManager* m_pInst;
    const IMSDKFriendListener* m_pFriendListener;
    std::string m_channel;
    
    int listenerTag;
    std::map<int, const IMSDKFriendListener*> *listenerMap; 

    IMSDKFriendManager();
    virtual ~IMSDKFriendManager();
    
public:
    /*!
     *  @abstract  获取Friend处理类单例
     *
     *  @return Friend处理类单例
     */
    static IMSDKFriendManager* getInstance();
    
    /*!
     *  @abstract  设置回调
     *
     *  @param listener 回调
     */
    void setFriendListener(const IMSDKFriendListener* listener);
    
    /*!
     *  @abstract  获取回调实例
     *
     *  @return 回调实例
     */
    const IMSDKFriendListener* getFriendListener() const;
    
    /*!
     *  @abstract  设置渠道
     *
     *  @param channel 渠道名称（Facebook、WeChat等）
     */
    bool setChannel(const std::string channel);
    
    /*!
     *  @abstract  获取当前渠道
     *
     *  @return 渠道名称
     */
    const std::string getChannel();
    
    /*!
     *  @abstract  拉取当前登录渠道用户好友列表
     *
     *  @param page     分页数
     *  @param count    每页记录条数
     *  @param type     好友类型：-1：表示兼容老接口；0：同玩好友；1：非同玩好友
     *  @param extend   扩展字段，方便以后扩展
     */
    void getFriends(int page, int count, int type = -1, std::string extend = "");
    
    
    /*!
     *  @abstract  邀请好友
     *
     *  @param requestInfo 邀请的数据
     */
    void invite(IMSDKFriendRequestInfo requestInfo);
    
    
    /*!
     *  @abstract   向好友发消息(WeChat发消息功能与分享相同)
     * 
     *  @param requestInfo 发送的数据
     */
    void sendMessage(IMSDKFriendRequestInfo requestInfo);
    
    /*!
     *  @abstract 分享
     *
     *  @param requestInfo 分享的数据
     */
    void share(IMSDKFriendRequestInfo requestInfo);
    
#ifdef ANDROID
private:
    JavaVM* m_pVM;
    
public:
    void init(JavaVM* pVM); 
    
    IMSDKFriendResult getFriendResultFromJava(JNIEnv * env, jclass jclassResult, jobject jobjectResult);
    
    const std::map<int, const IMSDKFriendListener*> getListenerMap(){
        return *listenerMap;
    }
#endif
    
};

#endif
