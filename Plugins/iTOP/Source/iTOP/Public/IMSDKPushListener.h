/*!
 *  @header    IMSDKPushListener.h
 *  @abstract  推送回调类
 *  @author    Created by brightwan on 15/8/11.
 *  @copyright Copyright (c) 2015年 Tencent. All rights reserved.
 */

#ifndef IMSDK_IMSDKPushListener_h
#define IMSDK_IMSDKPushListener_h

#include "IMSDKComm.h"
#include "IMSDKJson.h"
/*!
 *  @class IMSDKPushListener
 *
 *  @abstract 推送回调类
 */
class IMSDKPushListener {
public:
    /*!
     *  @abstract   注册推送回调
     *
     *  @param result   注册推送结果
     */
    virtual void OnRegister(IMSDKResult result) {
        printf("you must override onRegister method");
    }
    
    /*!
     *  @abstract   注销推送回调
     *
     *  @param result   注销推送结果
     */
    virtual void OnUnregister(IMSDKResult result) {
        printf("you must override onUnregister method");
    }
    
    /*!
     *  @abstract   设置标签回调
     *
     *  @param result   设置标签结果
     */
    virtual void OnSetTag(IMSDKResult result) {
        printf("you must override onSetTag method");
    }
    
    /*!
     *  @abstract   删除标签回调
     *
     *  @param result   删除标签结果
     */
    virtual void OnDelTag(IMSDKResult result) {
        printf("you must override onDeleteTag method");
    }
    
    /*!
     *  @abstract   推送接收回调
     *  @discussion 当应用处于前台时，收到的通知是无法进行展示的（iOS 10+除外）
     *
     *  @param jsonMessage   推送自定义内容
     */
    virtual void OnNotification(std::string jsonMessage) {
        printf("you must override OnNotification method");
    }
    
    /*!
     *  @abstract   推送点击接收回调。
     *  @discussion 当应用处于前台时，通过点击通知将 APP 恢复到前台
     *
     *  @param jsonMessage   推送自定义内容
     */
    virtual void OnNotifactionClick(std::string jsonMessage) {
        printf("you must override onNotifactionClick method");
    }

#ifdef ANDROID
    virtual void OnNotifactionShow(std::string jsonMessage) {
        printf("you must override onNotifactionShow method");
    }
#endif
    
    virtual ~IMSDKPushListener() {
    }
};

#endif
