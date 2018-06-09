/*!
 @header    IMSDKAdjustManager.h
 @abstract  IMSDK位置信息处理类声明文件
 @author    Created by Hillson Song on 9/8/15.
 @copyright Copyright (c) 2015 Tencent. All rights reserved.
 */

#ifndef __IMSDK__IMSDKAdjustManager__
#define __IMSDK__IMSDKAdjustManager__

#include "IMSDKComm.h"
#include "IMSDKJson.h"

/*!
 @class IMSDKAdjustManager
 @abstract IMSDK位置信息处理类
 */
class IMSDKAdjustManager {
private:
    static IMSDKAdjustManager *m_pInst;
    
    IMSDKAdjustManager();
    
    virtual ~IMSDKAdjustManager();
    
public:
    
    /*!
     *  @brief 获取 IMSDKAdjustManager 处理单例
     *
     *  @return 单例对象
     */
    static IMSDKAdjustManager* getInstance();
    
    /**
     * @brief 添加标准 Adjust Deep Linking 功能
     * @return 是否添加成功
     */
    bool addStandardDeepLink(std::string uri);
    
    /**
     * @brief 获取标准 Adjust Deep Linking 功能
     * @return
     */
    std::string pollStandardDeepLink();
    
    
    /**
     * @brief 添加延滞 Adjust Deep Linking 功能
     * @return 是否添加成功
     */
    bool addDeferredDeepLink(std::string uri);
    
    /**
     * @brief 获取延滞 Adjust Deep Linking 功能
     * @return
     */
    std::string pollDeferredDeepLink();
    
private:
    static IMSDKAdjustManager* m_adjustInst;
#ifdef ANDROID
 
public:
    void init();
#endif
};

#endif /* defined(__IMSDK__IMSDKAdjustManager__) */
