/*!
 *  @header    IMSDKLoginListener.h
 *  @abstract  登录回调类
 *  @author    Created by brightwan on 15-5-20.
 *  @copyright Copyright (c) 2015年 Tencent. All rights reserved.
 */

#ifndef IMSDK_IMSDKLoginListener_h
#define IMSDK_IMSDKLoginListener_h
 
#include "IMSDKComm.h"
#include "IMSDKJson.h"
/*!
 *  @class IMSDKLoginListener
 *  @abstract 登录回调类
 */
class IMSDKLoginListener {
public:
    /*!
     *  @brief 登录回调
     *  @param loginRet 登录结果
     */
    virtual void OnLoginNotify(IMSDKLoginResult loginRet) {
        printf("you must override OnLoginNotify method");
    }
    
    /*!
     *  @brief 绑定回调
     *  @param bindInfo 绑定信息
     */
    virtual void OnGetBindInfoNotify(IMSDKBindInfo bindInfo) {
        printf("you must override OnLoginNotify method");
    }
    
    /*!
     *  @brief 登出回调
     *  @param result 登出结果
     */
    virtual void OnLogoutNotify (IMSDKResult result) {
        printf("you must override OnLogoutNotify method");
    }
}; 
#endif
