/*!
 @header    IMSDKLocationListener.h
 @abstract  IMSDK位置信息处理回调类声明文件
 @author    Created by Hillson Song on 9/8/15.
 @copyright Copyright (c) 2015 Tencent. All rights reserved.
 */

#ifndef IMSDK_IMSDKLocationListener_h
#define IMSDK_IMSDKLocationListener_h

#include "IMSDKComm.h"
#include "IMSDKJson.h"

/*!
 @class IMSDKLocationListener
 @abstract IMSDK位置信息处理回调类
 */
class IMSDKLocationListener {
public:

    /*!
     *  @brief 获取位置信息回调
     *
     *  @param locationInfo 当前位置信息
     */
    virtual void OnGetLocationInfo(IMSDKLocationInfo &locationInfo) {
        printf("you must override OnGetUserInfo method");
    }
};

#endif
