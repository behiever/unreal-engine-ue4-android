/*!
 *  @header    IMSDKFriendListener.h
 *  @abstract  好友操作回调类
 *  @author    Created by Hillson Song on 7/3/15.
 *  @copyright Copyright (c) 2015 Tencent. All rights reserved.
 */

#ifndef IMSDK_IMSDKFriendListener_h
#define IMSDK_IMSDKFriendListener_h

#include "IMSDKComm.h"
#include "IMSDKJson.h"

/*!
 *  @class IMSDKFriendListener
 *
 *  @abstract 好友模块回调处理类
 */
class IMSDKFriendListener{
    
public:
    /*!
     *  @abstract 好友功能回调函数, 包括向好友发消息、邀请好友、拉取好友列表。
     *
     *  @param result 好友信息结果
     */
    virtual void OnFriendNotify(IMSDKFriendResult result){
        printf("you must override OnFriendNotify method");
    }
    
    /*!
     *  @abstract 分享回调函数
     *
     *  @param result 分享结果
     */
    virtual void OnShareNotify(IMSDKResult result){
        printf("you must override OnShareNotify method");
    }
    
    virtual ~IMSDKFriendListener(){
    }
};

#endif
