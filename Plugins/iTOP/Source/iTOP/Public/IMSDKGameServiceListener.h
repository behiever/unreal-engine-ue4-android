
#ifndef IMSDK_ANDROID_IMSDKGAMESERVICELISTENER_H
#define IMSDK_ANDROID_IMSDKGAMESERVICELISTENER_H

#include "IMSDKComm.h"
#include "IMSDKJson.h"

/*!
 *  @class IMSDKFriendListener
 *
 *  @abstract 好友模块回调处理类
 */
class IMSDKGameServiceListener{

public:
    /*!
     *  @abstract GameService回调函数
     *
     *  @param result 分享结果
     */
    virtual void OnGameServiceNotify(IMSDKResult result){

    }

    virtual ~IMSDKGameServiceListener(){
    }
};

#endif //IMSDK_ANDROID_IMSDKGAMESERVICELISTENER_H
