/*!
 *  @header    IMSDKWebViewListener.h
 *  @abstract  IMSDK内置浏览器回调类声明头文件
 *  @author    Created by brightwan on 15/9/17.
 *  @copyright Copyright (c) 2015年 Tencent. All rights reserved.
 */
#ifndef IMSDK_IMSDKWebViewListener_h
#define IMSDK_IMSDKWebViewListener_h

#include "IMSDKComm.h"
#include "IMSDKJson.h"

/*!
 *  @class IMSDKWebViewListener
 *  @abstract IMSDK内置浏览器回调处理类
 */
class IMSDKWebViewListener {
    
public:
    
    /*!
     *  @brief 获取当前登录态对应WebView票据的回调
     *
     *  @param ticketRet WebView票据
     */
    virtual void OnGetTicket(IMSDKWebViewTicketResult &ticketRet) {
        printf("you must override OnGetTicket method");
    }
    
    /*!
     *  @brief webview操作回调。
     *
     *  @param statuResult webview操作回调结果类
     */
    virtual void OnWebviewAction(IMWebViewStatusResult statuResult) {
        printf("you must override OnWebviewAction method");
    };
};

#endif
