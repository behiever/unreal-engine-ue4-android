/*!
 
 @header IMSDKNoticeListener_h
 @abstract Notice监听
 @author Created by yuanchengsu 16/6/16.
 @version 1.0.0
 @copyright Copyright © 2016年 Tencent. All rights reserved.
 */

#ifndef IMSDKNoticeListener_h
#define IMSDKNoticeListener_h

#include"IMSDKComm.h"
#include "IMSDKJson.h"
/*!
 @class IMSDKNoticeListener
 @abstract Notice监听类
 */
class IMSDKNoticeListener{
public:
    /*!
     *  @brief 加载公告数据回调
     *
     *  @param result 返回公告数据
     */
    virtual void OnLoadNotice(IMSDKNoticeResult result){
        printf("you shoule override this function for your purpose");
    }
    
    /*!
     *  @brief 展示公告回调
     *
     *  @param result 展示公告结果
     */
    virtual void OnShowNotice(IMSDKNoticeResult result){
        printf("you shoule override this function for your purpose");
    }
};

#endif /* IMSDKNoticeListener_h */
